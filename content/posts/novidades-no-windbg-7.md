---
date: "2010-04-01"
title: Novidades no Windbg 7
tags: [ "draft", "blog" ]
---
Semestre que vem deve sair uma nova versão do nosso depurador favorito. Alguns atrasos e novas definições do projeto fizeram com que tivéssemos mais um ou dois releases da finada versão 6 antes da revolução que será o **Depurador 2010**.

Entre as mudanças mais esperadas, e entre as mais inesperadas, encontramos essa pequena lista de novidades que, com certeza, deixarão o desenvolvedor de sistemas da Microsoft muito mais feliz:

#### Localizador automático de módulos

Hoje em dia é um trabalho um pouco tedioso encontrar qual dos drivers possuía a memória de endereço 0xB8915423, mas agora, juntando o interpretador de símbolos internos e o sistema de tooltips do Windbg, será possível passar o mouse sobre um endereço qualquer e ele mostrará imediatamente quem possui a memória, como ela foi alocada e qual seu conteúdo.

![windbg-tooltips.png](http://i.imgur.com/fb4hw4x.png)

Isso só é possível, é claro, com os símbolos corretamente carregados. Algo não muito difícil se você seguir as [recomendações de John Robbins](http://msdn.microsoft.com/en-us/magazine/cc301459.aspx). E é uma mão na roda na hora de dar um feedback instantâneo para o suporte técnico quando der uma tela azul.

#### Edit and Continue

Sim! Agora se o [ddkbuild](http://www.osronline.com/article.cfm?article=43)  estiver no path do WinDbg e você **editar o código-fonte** do seu driver durante a depuração (na próxima versão a visualização não será apenas read-only) e der um step-into, automaticamente o depurador irá perguntar se deseja recompilar o projeto. Depois de ativar o processo de build, através das conexões serial/firewire/usb-debug, a nova imagem irá parar diretamente na memória kernel da máquina target.

Algumas ressalvas são colocadas pela equipe da Microsoft, no entanto. Se existirem mudanças que dizem respeito a **alocação dinâmica de memória em nonpaged-pool**, o Edit and Continue não será possível naquele momento, apenas depois do reboot.

O último item, mais esotérico de todos, promete ser lançado a partir da versão 7.1:

#### The BugCheck Fix Tip

Resumidamente, é um !analyze mais esperto com o algoritmo heurístico do Visual Basic .NET. Assim que for aberto um dump de tela azul e carregados os símbolos e o caminho dos fontes, a nova versão do !analyze irá verificar os valores do BugCheck gerado e, caso seja detectado que o problema está em seu driver, irá sugerir uma correção na sua função que estiver na pilha.

    
    Microsoft (R) Windows Debugger Version 6.9.0003.113 X86
    Copyright (c) Microsoft Corporation. All rights reserved.
    
    Loading Dump File [C:\Tests\BSOD\BugCheck7F\2010-03-24ClientMemory.dmp]
    Kernel Complete Dump File: Full address space is available
    
    ************************************************************
    WARNING: Dump file has been truncated.  Data may be missing.
    ************************************************************
    Symbol search path is: SRV*c:\tools\symbols*http://msdl.microsoft.com/download/symbols
    Executable search path is:
    Windows XP Kernel Version 2600 (Service Pack 3) MP (2 procs) Free x86 compatible
    Product: WinNt, suite: TerminalServer SingleUserTS
    Built by: 2600.xpsp_sp3_gdr.090804-1435
    Kernel base = 0x804d7000 PsLoadedModuleList = 0x8055d720
    Debug session time: Wed Mar 24 17:51:39.216 2010 (GMT-3)
    System Uptime: 0 days 0:05:23.843
    Loading Kernel Symbols
    .........................................................................................
    Loading User Symbols
    ............
    Loading unloaded module list
    ..........................

    
    *******************************************************************************
    *                                                                             *
    *                        Bugcheck Analysis                                    *
    *                                                                             *
    *******************************************************************************
    
    Use !analyze -v to get detailed debugging information.
    
    BugCheck 7F, {d, 0, 0, 0}
    
    *** ERROR: Symbol file could not be found.  Defaulted to export symbols for MyDriver.sys -
    *** ERROR: Symbol file could not be found.  Defaulted to export symbols for mfehidk.sys -
    Probably caused by : MyDriver.sys ( MyDriver!KeBugCheckTest+2b )
    
    Followup: MachineOwner
    ---------

    
    0: kd> !analyze -v
    *******************************************************************************
    *                                                                             *
    *                        Bugcheck Analysis                                    *
    *                                                                             *
    *******************************************************************************
    
    UNEXPECTED_KERNEL_MODE_TRAP (7f)
    This means a trap occurred in kernel mode, and it's a trap of a kind
    that the kernel isn't allowed to have/catch (bound trap) or that
    is always instant death (double fault).  The first number in the
    bugcheck params is the number of the trap (8 = double fault, etc)
    Consult an Intel x86 family manual to learn more about what these
    traps are. Here is a *portion* of those codes:
    If kv shows a taskGate
            use .tss on the part before the colon, then kv.
    Else if kv shows a trapframe
            use .trap on that value
    Else
            .trap on the appropriate frame will show where the trap was taken
            (on x86, this will be the ebp that goes with the procedure KiTrap)
    Endif
    kb will then show the corrected stack.
    Arguments:
    Arg1: 0000000d, EXCEPTION_GP_FAULT
    Arg2: 00000000
    Arg3: 00000000
    Arg4: 00000000

    
    Debugging Details:
    ------------------
    BUGCHECK_STR:  0x7f_d
    
    DEFAULT_BUCKET_ID:  DRIVER_FAULT

    
    PROCESS_NAME:  cmd.eze

    
    LAST_CONTROL_TRANSFER:  from 80564dd2 to 80544e7b
    
    STACK_TEXT:
    a7f4b6a4 80564dd2 badb0d00 89679eb0 a7f40000 nt!KiSystemFatalException+0xf
    a7f4b774 ba182d80 e23bb528 00000002 a7f4b86c nt!NonPagedPoolDescriptor+0xb2
    WARNING: Stack unwind information not available. Following frames may be wrong.
    a7f4b870 804ef19f 8a03a2e0 89665008 8972c838 MyDriver!KeBugCheckTest+0x2b
    a7f4b880 b9da1876 89665008 8a0f3a80 00000000 nt!IopfCallDriver+0x31
    ...
    a7f4b940 b9c55e4d 00000002 896651e0 8972c838 mfehidk+0x9128
    a7f4b9d8 b9c70ef5 cccccccc 8a03b9f8 8a033ab0 mfehidk+0x9e4d
    0012f918 4ad02d98 0014efc0 00150b00 00000000 cmd!ExecPgm+0x22b
    ...
    0012fff0 00000000 4ad05046 00000000 78746341 kernel32!BaseProcessStart+0x23
    
    STACK_COMMAND:  kb
    
    FOLLOWUP_IP:
    MyDriver!KeBugCheckTest+0x2b
    ba182d80 668945a4        mov     word ptr [ebp-5Ch],ax
    
    SYMBOL_STACK_INDEX:  2
    
    SYMBOL_NAME:  MyDriver!KeBugCheckTest+0x2b
    
    FOLLOWUP_NAME:  MachineOwner
    
    MODULE_NAME: MyDriver
    
    IMAGE_NAME:  MyDriver.sys
    
    DEBUG_FLR_IMAGE_TIMESTAMP:  4baa49d3
    
    <font color="#0000ff">BugCheck Fix Tip:
    -----------------
    Try to remove the spin lock aquisition in MyDriver!KeBugCheckTest+2a. By doing this,
    the kernel IRQL priority system will not be in starvation mode.
    
    Tip Code: C:\Tests\MyDriver\dispatch-funcs.cpp+345</font>
    
    Followup: MachineOwner
    ---------

Existem um pouco de polêmica em torno dessa funcionalidade. Alguns dizem que ela vai mais atrapalhar do que ajudar os programadores de kernel com a vinda de [analistas de sistemas Júnior programando filtros de file system](http://groups.google.com/group/ccppbrasil/msg/f1f6d52aa167c1ab?dmode=source) sem a menor discrepância entre o que é um IRP assíncrono e uma ISR. Outros dizem que existirá uma versão paga do WinDbg com essa funcionalidade, nos mesmos moldes do Visual Studio 2010, que virá com a depuração reversa no Enterprise. Essas especulações só o tempo dirá se são verdade ou não. Se eu tiver que pagar mais caro por essas features, o lobby na empresa onde eu trabalho está garantido.
