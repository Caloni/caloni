---
date: "2008-01-10"
title: Analisando dumps com WinDbg e IDA
categories: [ "code" ]
---
Apesar de ser recomendado que 100% dos componentes de um software esteja configurado corretamente para gerar símbolos na versão _release_, possibilitando assim a visualização do nome das funções internas através de um [arquivo de _dump_](http://support.microsoft.com/kb/315263) (despejo) gerado na ocorrência de um _crash_, essa verdade só ocorre em 80% das vezes. Quis Murphy que dessa vez a única parte não "simbolizada" fosse a que gerou a tela azul em um [Intel Quad Core](http://compare.buscape.com.br/categoria?id=22&lkout=1&kw=Intel+Quad+Core&site_origem=1293522) que estou analisando esses dias.

Para incluir um programa novo em nosso leque de opções, vamos usar dessa vez uma ferramenta chamada [IDA](http://www.hex-rays.com/idapro/overview.htm), um disassembler estático cujo nome é uma clara homenagem à nossa [primeira programadora da história](http://pt.wikipedia.org/wiki/Ada_Lovelace). E, é lógico, o WinDbg não poderá ficar de fora, já que ele será nosso analisador de dumps.

#### A primeira noite de um dump

Tecnicamente falando, um dump nada mais é do que o conjunto de informações relevantes de um sistema em um determinado momento da execução, geralmente logo após um _crash_, onde tudo pára e morre. No caso do Windows, o _crash_ é chamado de [BSOD](http://www.google.com/search?q=bsod), Blue Screen Of Death, ou Tela Azul da Morte (bem macabro, não?). Do ponto de vista do usuário, é aquela simpática tela azul que aparece logo após o travamento da máquina.

<blockquote>_Em algumas máquinas, essa tela nem mais é vista, pois o Windows XP é configurado automaticamente para exibir um simpático __reboot que joga todos os seus dados não-salvos naquele momento para o limbo (ou, como diria o [Thiago](http://codebehind.wordpress.com/), para o "céu dos dados não-salvos antes de uma tela azul")._</blockquote>

Dumps podem ser abertos por um depurador que entenda o tipo de dump gerado (Visual Studio, WinDbg, OllyDbg, IDA, sd, etc). Se estamos falando de aplicativos que travaram, o Visual Studio pode dar conta do recado. Se é realmente uma tela azul, o WinDbg é o mais indicado.

Para abrir um dump no WinDbg, tudo que temos que fazer é usar o item do menu "File, Open Crash Dump" ou digitar direto da linha de comando:

    
    windbg -z meu-crash-dump-do-coracao.dmp

Após alguns segundos, o WinDbg irá imprimir uma saída parecida com as linhas abaixo.

    
    Microsoft (R) Windows Debugger Version 6.8.0004.0 X86
    Copyright (c) Microsoft Corporation. All rights reserved.

    
    Loading Dump File [C:\BlaBlaBla\caloni\My Documents\My Dumps\cagou-geral.dmp]

Mini Kernel Dump File: Only registers and stack trace are available

    
    Symbol search path is: SRV*C:\Symbols*\\symbolserver\OSSYMBOLS*(...)

    
    Executable search path is:
    Windows XP Kernel Version 2600 (Service Pack 2) MP (4 procs) Free x86 compatible

    
    Product: WinNt, suite: TerminalServer SingleUserTS
    Built by: 2600.xpsp_sp2_rtm.040803-2158
    
    Kernel base = 0x804d7000 PsLoadedModuleList = 0x8055c700

    
    Debug session time: Sat Dec 29 07:47:12.734 2007 (GMT-3)
    System Uptime: 0 days 0:15:13.728
    
    Loading Kernel Symbols
    .............
    Loading User Symbols
    Loading unloaded module list
    .............

    
    *******************************************************************************
    *                                                                             *
    *                        Bugcheck Analysis                                    *
    *                                                                             *
    *******************************************************************************

Use !analyze -v to get detailed debugging information.

    
    BugCheck C, {0, 0, 0, 0}

    
    *** ERROR: Module load completed but symbols could not be loaded for mydriver.sys

    
    Probably caused by : psseckbd.sys ( mydriver+199e )

    
    Followup: MachineOwner
    ---------

Geralmente a melhor idéia agora é seguir o conselho do WinDbg e usar o comando **!analyze**.

    
    0: kd> !analyze -v
    ERROR: FindPlugIns 8007007b
    *******************************************************************************
    *                                                                             *
    *                        Bugcheck Analysis                                    *
    *                                                                             *
    *******************************************************************************

MAXIMUM_WAIT_OBJECTS_EXCEEDED

    
     (c)
    Arguments:
    Arg1: 00000000
    Arg2: 00000000
    Arg3: 00000000
    Arg4: 00000000
    
    Debugging Details:
    ------------------
    CUSTOMER_CRASH_COUNT:  1
    DEFAULT_BUCKET_ID:  DRIVER_FAULT
    BUGCHECK_STR:  0xC
    PROCESS_NAME:  System
    LAST_CONTROL_TRANSFER:  from 804fa83f to 804f9c12
    STACK_TEXT:
    bad17bc0 804fa83f 0000000c 00000004 883a8eac nt!KeBugCheck+0x14
    bad17bfc bac9199e 00000004 e32e8928 00000000 nt!KeWaitForMultipleObjects+0x37
    WARNING: Stack unwind information not available. Following frames may be wrong.
    bad17c50 bac914d7 88d851e8 00000000 883a8030

mydriver+0x199e

    
    bad17c7c bac94058 899c0f38 8058006a 899c0f38 mydriver+0x14d7
    bad17c84 8058006a 899c0f38 8836b000 00000000 mydriver+0x4058
    bad17d54 80580179 00000240 00000001 00000000

nt!IopLoadDriver+0x66c

    
    bad17d7c 80537757 00000240 00000000 89c3cda8 nt!IopLoadUnloadDriver+0x45
    bad17dac 805ce794 b5de6cf4 00000000 00000000 nt!ExpWorkerThread+0xef
    bad17ddc 805450ce 80537668 00000001 00000000 nt!PspSystemThreadStartup+0x34
    00000000 00000000 00000000 00000000 00000000 nt!KiThreadStartup+0x16
    STACK_COMMAND:  kb

    
    FOLLOWUP_IP:
    mydriver+199e
    bac9199e 8b44241c        mov     eax,dword ptr [esp+1Ch]
    
    SYMBOL_STACK_INDEX:  2
    SYMBOL_NAME:  mydriver+199e
    FOLLOWUP_NAME:  MachineOwner
    MODULE_NAME: mydriver
    IMAGE_NAME:  mydriver.sys
    DEBUG_FLR_IMAGE_TIMESTAMP:  42d2747c
    FAILURE_BUCKET_ID:  0xC_mydriver+199e
    BUCKET_ID:  0xC_mydriver+199e

    
    Followup: MachineOwner
    ---------

Esse é o resultado de um dos minidumps recebidos.

<blockquote>_Um minidump contém apenas a pilha de chamada que causou a tela azul, o estados dos registradores e algumas informações sobre módulos carregados no kernel._</blockquote>

A partir daí podemos extrair algumas informações úteis, que eu sublinhei na saída do WinDbg. Na ordem de chegada:

    
  1. **O código do Bug Check**. Esse é talvez o mais importante, pois pode resolver rapidamente o nosso problema. Procurando [na ajuda do WinDbg](http://www.caloni.com.br/blog/wp-admin/mk:@MSITStore:%programfiles%%5CDebugging%20Tools%20for%20Windows%5Cdebugger.chm::/hh/Debugger/t04_bugs_00_493ab992-8cee-4ee8-b39b-da780b6dcb7e.xml.htm) pelo código do erro (obs: execute o link pelo explorer) conseguimos ter algumas dicas de como evitar esse erro:
"_The MAXIMUM_WAIT_OBJECTS_EXCEEDED bug check has a value of 0x0000000C. This indicates that the current thread exceeded the permitted number of wait objects._"
Mais sobre isso pra depois.

    
  2. **Os dados da pilha**. Pela pilha de chamadas, podemos não apenas saber se nosso driver está no meio com cara de culpado, como, através dos _offsets_, descobrir em que função ele se enfiou para dar no que deu.

    
  3. **A última chamada do kernel** antes do nosso driver pode indicar-nos que evento foi o responsável por iniciar todo o processo de cabum. Nesse caso, **IopLoadDriver **nos dá uma ótima dica: **foi na hora de carregar o nosso driver**.

Com isso em mãos, mesmo sem símbolos e nomes de funções no código, conseguiríamos achar o código responsável pelo BSOD. Porém, vamos imaginar por um momento que não foi tão fácil assim e fazer entrar em cena outra ferramenta indispensável nessas horas: o Interactive Disassembler.

#### A primeira noite com IDA

No [sítio do IDA](http://www.datarescue.com/idabase/idadown.htm) podemos encontrar o download para uma versão gratuita do IDA, isso se usado com objetivos não-comerciais. Ou seja, para você que está lendo esse blogue por aprendizado, não terá nenhum problema você baixar essa versão e fazer alguns testes com seu _driver _favorito.

O funcionamento básico do IDA é bem básico, mesmo. Simplesmente escolhemos um executável para ele destrinchar e nos mostrar um assembly bem amigável, com todos os nomes de funções que ele puder deduzir. Como não temos os símbolos do próprio executável, as funções internas ganham "apelidos", como sub_6669, loc_13F35 e por aí vai. Isso não importa, já que temos nomes amigáveis de APIs para pesquisar no código-fonte e tentar encontrar as funções originais em C.

[![Driver na IDA](http://i.imgur.com/KExTNg9.png)](/images/driver-ida-01.png)

Pois bem. Como manda o figurino, o primeiro ponto do assembly que temos que procurar é o ponto em que uma função interna é chamada logo após IopLoadDriver, **mydriver+0x4058**. Por coincidência (ou não, já que essa é a função do IopLoadDriver), se trata da função inicial do executável, ou seja, provavelmente a função **DriverEntry** no código-fonte (obs: estamos analisando um driver feito para plataforma NT).

Como podemos ver pela imagem acima, o ponto de retorno é logo após uma chamada à função **sub_113F0**, que não sabemos qual é. No entanto, sabemos que logo no início é chamada a função **IoIsWdmVersionAvailable**, o que já nos permite fazer uma correlação com o código-fonte original. Após a chamada à IoIsWdmVersionAvailable, a próxima e última chamada de uma função é o que procuramos. Dessa forma, podemos ir caminhando até o ponto onde o driver chama o sistema operacional:

    
    mydriver+0x14d7:

    
    .text:000114B1                 call    ds:KeInitializeDpc
    .text:000114B7                 mov     edx, dword_13000
    ...
    .text:000114CA                 push    1
    .text:000114CC                 call    sub_11BE0
    .text:000114D1                 push    eax

.text:000114D2 call sub_117D0.text:000114D7

    
                     add     esi, 0D9Ch
    .text:000114DD                 push    esi
    ...

    
    mydriver+0x199e:

    
    .text:0001197C loc_1197C:
    .text:00011994                 push    0
    ...
    .text:00011996                 push    ebx
    .text:00011997                 push    edi

.text:00011998 call ds:KeWaitForMultipleObjects.text:0001199E 

    
    mov     eax, [esp+30h+var_14]
    .text:000119A2                 mov     edi, ds:ExFreePoolWithTag
    ...
    .text:000119AD                 mov     ecx, [esp+20h]
    .text:000119B1                 push    0

Voilà! O caminho não foi tão longo. Chegamos rapidamente no ponto onde é chamada a função [KeWaitForMultipleObject](http://www.osronline.com/DDKx/kmarch/k105_18oi.htm) que, de acordo com o WinDbg e com a OSR, pode gerar uma tela azul se esperarmos por mais de três objetos e não especificarmos um buffer no parâmetro **WaitBlockArray**. Agora podemos olhar no fonte e ver por quantos objetos esperamos e tirar nossa própria conclusão do que está acontecendo:

```c
//...
	processorCount = 0;
	processorsMask = KeQueryActiveProcessors();
	processorsMaskAux = processorsMask;

	while( processorsMaskAux )
	{
		if( processorsMaskAux & 1 )
			processorCount++;

		processorsMaskAux >>= 1;
	}

//...

	KeWaitForMultipleObjects(processorCount, waitObjects, WaitAll, 
		UserRequest, KernelMode, TRUE, NULL, NULL);

	ExFreePool(dpcVect);
	ExFreePool(eventVect);
	ExFreePool(waitObjects);
//... 

```

Ora, ora. O número de processadores influencia no número de objetos que estaremos esperando na função de espera. Esse seria um bom motivo para gerar um MAXIMUM_WAIT_OBJECTS_EXCEEDED em máquinas onde existe mais de 3 processadores ativos, não? Talvez seja uma boa hora para atualizar esse código e torná-lo compatível com os novos Quad Core.

#### Versão debug pra quê?

É importante, durantes os testes de desenvolvimento, sempre manter em dia uma versão _debug_ (para o mundo kernel mode, versões _checked_) para que os primeiros problemas, geralmente os mais bestinhas, sejam pêgos de forma rápida e eficiente. No entanto, um bom desenvolvedor não se limita a depurar com código-fonte. Ele deve estar sempre preparado para enfrentar problemas de falta da versão certa, informação pela metade, situação não-reproduzível. Para isso que servem as ferramentas maravilhosas que podemos usar no dia-a-dia. O IDA é mais uma das que deve estar sempre no cinto de utilidades do bom "debugador".
