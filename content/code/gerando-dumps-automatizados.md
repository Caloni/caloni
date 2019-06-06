---
date: "2010-08-26"
title: Gerando dumps automatizados
categories: [ "code" ]
---
Agora que a temporada das telas azuis passou estou às voltas com o nosso sistema de detecção de crashes, além de alguns dumps e logs pra relaxar de vez em quando.

Fiquei impressionado com a simplicidade com que podemos capturar qualquer exceção que ocorra em um programa, independente da thread, e gravar um minidump com o contexto exato em que o problema ocorreu. O uso da função API [SetUnhandledExceptionFilter](http://msdn.microsoft.com/en-us/library/ms680634%28VS.85%29.aspx) aliado com a já citada na palestra [MiniDumpWriteDump](http://msdn.microsoft.com/en-us/library/ms680360%28VS.85%29.aspx) pode agilizar muito a correção de crashes triviais como Access Violation.

A mágica é tão bela que resolvi gravar um vídeo do que ocorreu quando compilei e testei o programa abaixo. Note que o tamanho do arquivo de dump ficou em torno dos 10 KB, ridículos nessa era de barateamento de espaço.

```cpp
/** @file OnCrash

@brief Exemplo de como capturar exceções no seu programa.

@author Wanderley Caloni <wanderley@caloni.com.br>
@date 2010-08
*/
#include <windows.h>
#include <dbghelp.h>
#include <time.h>

#pragma comment(lib, "dbghelp.lib")

LONG WINAPI CrashHandler(_EXCEPTION_POINTERS* ExceptionInfo)
{
	LONG ret = EXCEPTION_CONTINUE_SEARCH;
	MINIDUMP_EXCEPTION_INFORMATION minidumpInfo;

	minidumpInfo.ClientPointers = FALSE;
	minidumpInfo.ThreadId = GetCurrentThreadId();
	minidumpInfo.ExceptionPointers = ExceptionInfo;

	HANDLE hFile = CreateFile("OnCrash.dmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

	if( hFile != INVALID_HANDLE_VALUE )
	{
		MINIDUMP_TYPE dumpType = MiniDumpNormal;

		if( MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), 
			hFile, MiniDumpNormal, &minidumpInfo, NULL, NULL) )
		{
			ret = EXCEPTION_EXECUTE_HANDLER;
		}

		CloseHandle(hFile);
	}

	return ret;
}

DWORD WINAPI CrashThread(PVOID)
{
	int* x = 0;
	*x = 13;
	return 0;
}

int main()
{
	SetUnhandledExceptionFilter(CrashHandler);
	HANDLE crashThread = CreateThread(NULL, 0, CrashThread, NULL, 0, NULL);
	WaitForSingleObject(crashThread, INFINITE);
}
 

```

[![oncrash.png](http://i.imgur.com/D5keozk.png)](/images/finddump.htm)

Espero com isso aliviar a carga pesada de A.V.s que sempre aparece quando menos se espera. Cuidar de toneladas de código legado exige algumas pitadas de automatização nos lugares certos. Como já dizia meu primeiro chefe: se a mente não pensa...
