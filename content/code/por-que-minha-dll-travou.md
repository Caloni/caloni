---
date: "2007-10-18"
title: Por que minha DLL travou?
categories: [ "code" ]
---
Saiu um [documento da Microsoft](http://www.microsoft.com/whdc/driver/kernel/DLL_bestprac.mspx) alertando sobre os perigos em colocar código no **DllMain**. É algo mais completo e didático do que as simples observações do [help do MSDN](http://msdn.microsoft.com/library/en-us/dllproc/base/dllmain.asp). Vale a pena dar uma lida, especialmente por causa das explicações sobre o _loader lock_ e seus efeitos colaterais.

#### O conceito

O resumo da ópera é que o código do Windows chamador do DllMain das DLLs carregadas/descarregadas utiliza um objeto de acesso exclusivo (leia "_mutex_") para sincronizar as chamadas. O resultado é que, em um processo, **apenas um DllMain é chamado em um dado momento**. Esse objeto é chamado de "_loader lock_" na documentação da Microsoft.

[![Loader Lock explained](http://i.imgur.com/mjJ0Xmm.gif)](/images/loaderlock.gif)

#### O código

O código abaixo é besta, mas representa o que já vi em muito código-fonte, e muitas vezes não consegui perceber o que estava acontecendo (tanto porque desconhecia a existência desse _loader lock_ quanto o código estava obscuro demais pra entender mesmo). Os comentários dizem tudo:

```cpp
//
// LoaderLock.dll
//
#include <windows.h>

HANDLE g_thrLock = NULL; // locked thread handle
BOOL g_getOut = FALSE; // it would be useful to unlock the thread, but it's not

/** The thread locker

The function of this thread is to lock. It tries to call DllMain (indirectly). 
In order to do this, it needs the loader lock. Unfortunately the main thread 
has got it before. The obvious result: this secondary thread is going to 
wait forever for a resource that will be never released.
*/
DWORD WINAPI ThreadLock(PVOID)
{
	while( true )
	{
		// I'm here to hinder, not to help
		Sleep(1000);
		if( g_getOut ) 
			break;
	}

	return ERROR_ACCESS_DENIED; // this does not work
}

/** The DllMain locker

The function of this DllMain is to show how not to code an DllMain. It creates 
a thread on the PROCESS_ATTACH event (bad sign). Not happy yet, it waits 
for the thread on the PROCESS_DETACH event (bad bad sign). As this thead has 
got the loader lock, the secondary thread will never reach the point 
where it returns.
*/
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if( fdwReason == DLL_PROCESS_ATTACH )
	{
		// creates the locked thread
		DWORD tid = 0;
		g_thrLock = CreateThread(NULL, 0, ThreadLock, NULL, 0, &tid);
	}
	else if( fdwReason == DLL_PROCESS_DETACH )
	{
		// waits for the thread for ever and ever
		g_getOut = TRUE;
		WaitForSingleObject(g_thrLock, INFINITE);
		CloseHandle(g_thrLock), g_thrLock = NULL;
	}
} 

```

Uma simples vítima disso pode ser um pobre executável usando uma pobremente escrita DLL, assim como no código abaixo:

```cpp
//
// Victim.exe
//
#include <windows.h>
#include <tchar.h>

int main()
{
	HMODULE lockDll = LoadLibrary(_T("LoaderLock.dll"));

	if( lockDll )
	{
		Sleep(5000);
		FreeLibrary(lockDll), lockDll  = NULL;
	}
} 

```

Para ver o problema de _lock_ em ação, baixe os fontes da [DLL](/images/loaderlock.cpp) e do [EXEcutável](/images/loaderlock-exe.cpp) e use os comandos abaixo para gerar os arquivos:

    
    cl /c loaderlock.cpp loaderlock-exe.cpp
    link loaderlock-exe.obj
    link /dll loaderlock.obj

#### E a solução é...

É importante sempre lembrar que a Microsoft acha feio, muito feio você ficar dependendo do DllMain pra fazer alguma coisa, **mas** admite que em alguns casos o único lugar onde podemos rodar código é no DllMain. Nesses casos - e em alguns outros - **utilize uma comunicação paralela com sua _thread_ travadona**, por meio de um evento ou algo do gênero, antes que ela realmente saia. Com isso a _thread_ pode ainda não ter saído, mas pode avisar a _thread_ principal que o que ela precisava fazer já foi feito.

#### Mais informações

    
  1. [NT Loader (MSJ Sep 99)](http://www.microsoft.com/msj/0999/hood/hood0999.aspx) - Matt Pietrek

    
  2. [mgrier's WebLog](http://blogs.msdn.com/mgrier/default.aspx) - NT Loader team participant

