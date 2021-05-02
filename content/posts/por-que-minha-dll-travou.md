---
date: "2007-10-18"
title: "Por que minha DLL travou?"
categories: [ "code" ]
---
O resumo da ópera é que o código do Windows chamador do DllMain das DLLs carregadas/descarregadas utiliza um objeto de acesso exclusivo (leia "mutex") para sincronizar as chamadas. O resultado é que, em um processo, apenas um DllMain é chamado em um dado momento. Esse objeto é chamado de loader lock na documentação da Microsoft.

![Loader Lock explicado](/img/loader_lock.gif)

Escrevi um [código besta] para exemplificar, mas representa o que já vi em muito código-fonte, e muitas vezes não consegui perceber o que estava acontecendo (tanto porque desconhecia a existência desse loader lock quanto o código estava obscuro demais pra entender mesmo).

Uma simples vítima disso pode ser um pobre executável usando uma pobremente escrita DLL, assim como no código abaixo:

    int main()
    {
      printf("load dll");
    	HMODULE lockDll = LoadLibrary(_T("dll_lock.dll"));
    
    	if( lockDll )
    	{
    		Sleep(2000);
        printf("free dll");
    		FreeLibrary(lockDll), lockDll  = NULL;
        printf("done");
    	}
    }

É importante sempre lembrar que a Microsoft acha feio, muito feio você ficar dependendo do DllMain pra fazer alguma coisa, mas admite que em alguns casos o único lugar onde podemos rodar código é no DllMain. Nesses casos -- e em alguns outros -- utilize uma comunicação paralela com sua thread travadona, por meio de um evento ou algo do gênero, antes que ela realmente saia. Com isso a thread pode ainda não ter saído, mas pode avisar a thread principal que o que ela precisava fazer já foi feito.

Entre os clássicos e inestimáveis artigos de Matt Pietrek no Microsoft Journal há na [edição de setembro de 1999] um bem curto a respeito da inicialização de DLLs. Essa é a leitura mais sucinta, didática e esclarecedora sobre a questão.

[código besta]: /code/dll_lock.cpp
[edição de setembro de 1999]: http://bytepointer.com/resources/pietrek_debug_init_routines.htm
