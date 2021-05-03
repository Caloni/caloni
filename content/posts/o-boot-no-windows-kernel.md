---
categories:
- draft
- code
date: '2009-12-04'
title: 'O boot no Windows: Kernel'
---

Finalmente chegamos em um pouco onde podemos usar o WinDbg.

Podemos espetar o depurador e fazê-lo parar assim que conectado. Se estiver rodando antes do próprio sistema operacional, teremos um sistema sem processos e sem threads, pois ele irá parar assim que o executivo puder enviar o sinal de início pela porta serial, após carregar na memória os módulos básicos.

    
    windbg -k com:pipe,port=\\.\pipe\com_1 <strong><font color="#000000">-b</font></strong>

    
    Microsoft (R) Windows Debugger Version 6.11.0001.404 AMD64
    Copyright (c) Microsoft Corporation. All rights reserved.
    
    Opened \\.\pipe\com_1
    Waiting to reconnect...
    Connected to Windows XP 2600 x86 compatible target at (Tue Sep  8 22:33:27.267 2009 (GMT-3)), ptr64 FALSE
    Kernel Debugger connection established.  (Initial Breakpoint requested)
    Symbol search path is: *** Invalid ***
    ****************************************************************************
    * Symbol loading may be unreliable without a symbol search path.           *
    * Use .symfix to have the debugger choose a symbol path.                   *
    * After setting your symbol path, use .reload to refresh symbol locations. *
    ****************************************************************************
    Executable search path is:
    *********************************************************************
    * Symbols can not be loaded because symbol path is not initialized. *
    *                                                                   *
    * The Symbol Path can be set by:                                    *
    *   using the _NT_SYMBOL_PATH environment variable.                 *
    *   using the -y <symbol_path> argument when starting the debugger. *
    *   using .sympath and .sympath+                                    *
    *********************************************************************
    *** ERROR: Symbol file could not be found.  Defaulted to export symbols for ntkrnlpa.exe -
    Windows XP Kernel Version 2600 UP Free x86 compatible
    Built by: 2600.xpsp_sp2_rtm.040803-2158
    Machine Name:
    Kernel base = 0x804d7000 PsLoadedModuleList = 0x805531a0
    System Uptime: not available
    Break instruction exception - code 80000003 (first chance)
    *******************************************************************************
    *                                                                             *
    *   You are seeing this message because you pressed either                    *
    *       CTRL+C (if you run kd.exe) or,                                        *
    *       CTRL+BREAK (if you run WinDBG),                                       *
    *   on your debugger machine's keyboard.                                      *
    *                                                                             *
    *                   THIS IS NOT A BUG OR A SYSTEM CRASH                       *
    *                                                                             *
    * If you did not intend to break into the debugger, press the "g" key, then   *
    * press the "Enter" key now.  This message might immediately reappear.  If it *
    * does, press "g" and "Enter" again.                                          *
    *                                                                             *
    *******************************************************************************
    *** ERROR: Symbol file could not be found.  Defaulted to export symbols for ntkrnlpa.exe -
    nt!DbgBreakPointWithStatus+0x4:
    80526da8 cc              int     3
    kd> lm
    start    end        module name
    804d7000 806ce300   nt         (export symbols)       ntkrnlpa.exe
    806cf000 806ef380   hal        (deferred)
    f96f0000 f970a580   Mup        (deferred)
    f970b000 f9737a80   NDIS       (deferred)
    f9738000 f97c4480   Ntfs       (deferred)
    f97c5000 f97db780   KSecDD     (deferred)
    f97dc000 f97edf00   sr         (deferred)
    f97ee000 f980c780   fltMgr     (deferred)
    f980d000 f9824800   SCSIPORT   (deferred)
    f9825000 f983c480   atapi      (deferred)
    f983d000 f985bb80   ftdisk     (deferred)
    f985c000 f986cd80   pci        (deferred)
    f986d000 f989b000   ACPI       (deferred)
    f999c000 f99a4d80   isapnp     (deferred)
    f99ac000 f99b6500   MountMgr   (deferred)
    f99bc000 f99c9000   VolSnap    (deferred)
    f99cc000 f99d4e00   disk       (deferred)
    f99dc000 f99e8200   CLASSPNP   (deferred)
    f99ec000 f99f6580   agp440     (deferred)
    f9c1c000 f9c22200   PCIIDEX    (deferred)
    f9c24000 f9c28900   PartMgr    (deferred)
    f9dac000 f9daf000   BOOTVID    (deferred)
    f9db0000 f9db2480   compbatt   (deferred)
    f9db4000 f9db7700   BATTC      (deferred)
    f9db8000 f9dbab00   vmscsi     (deferred)
    f9e9c000 f9e9db80   kdcom      (deferred)
    f9e9e000 f9e9f100   WMILIB     (deferred)
    f9ea0000 f9ea1600   intelide   (deferred)
    kd> .sympath
    Symbol search path is: <empty>
    Expanded Symbol search path is: <empty>
    kd> .symfix
    kd> .sympath
    Symbol search path is: srv*
    Expanded Symbol search path is: cache*C:\Tools\DbgTools\sym;SRV*http://msdl.microsoft.com/download/symbols
    kd> !process 0 0
    **** NT ACTIVE PROCESS DUMP ****
    NT symbols are incorrect, please fix symbols
    kd> .reload
    Connected to Windows XP 2600 x86 compatible target at (Tue Sep  8 22:34:41.661 2009 (GMT-3)), ptr64 FALSE
    Loading Kernel Symbols
    ...........................
    Loading User Symbols
    
    kd> !process 0 0
    **** NT ACTIVE PROCESS DUMP ****
    NULL value in PsActiveProcess List<font color="#ff0000"> <strong><font color="#000000"> <-- Nenhum processo por aqui</font></strong></font>
    kd> !thread0 0
    No export thread0 found
    kd> !thread 0 0
    00000000: Unable to get thread content<font color="#000000">s</font><font color="#000000"> <strong> <-- Nenhuma thread também!</strong></font>
    kd> r
    eax=00000001 ebx=80087000 ecx=80548c74 edx=80548c44 esi=80087000 edi=00000000
    eip=80526da8 esp=80548c60 ebp=80548de8 iopl=0         nv up ei pl nz na po nc
    cs=0008  ss=0010  ds=0023  es=0023  fs=0030  gs=0000             efl=00000202
    nt!RtlpBreakWithStatusInstruction:
    80526da8 cc              int     3
    kd> k
    ChildEBP RetAddr
    80548c5c 80682baa nt!RtlpBreakWithStatusInstruction
    80548de8 8068fd48 nt!ExpInitializeExecutive+0x350
    80548e3c 8068d99b nt!KiInitializeKernel+0x3b2
    00000000 00000000 nt!KiSystemStartup+0x2bf
    kd> kv
    ChildEBP RetAddr  Args to Child
    80548c5c 80682baa 00000001 80551920 00000000 nt!RtlpBreakWithStatusInstruction (FPO: [1,0,0])
    80548de8 8068fd48 00000000 80087000 8003fc00 nt!ExpInitializeExecutive+0x350 (FPO: [2,93,4])
    80548e3c 8068d99b 80551b80 80551920 80549100 nt!KiInitializeKernel+0x3b2 (FPO: [Non-Fpo])
    00000000 00000000 00000000 00000000 00000000 nt!KiSystemStartup+0x2bf

Todos os módulos carregados antes dessa fase são os drivers que tiveram seu Start definido em zero no registro. Todos os programadores que desenvolvem esses drivers gostariam de um dia poder usar o WinDbg. Mas não podem. Quem inicia a comunicação serial com o depurador é o kernel, que só recebe o controle do ntldr depois que os drivers básicos foram carregados.

Brincadeira. É claro que esses programadores usam o WinDbg, usam [até demais](http://www.driverentry.com.br/blog/2007/07/bug-em-meu-driver-de-boot-j-posso.html). Mas só a partir desse ponto. Se algum problema evitar que o sistema chegue nessa fase, o desenvolvedor terá que usar métodos alternativos de depuração, como [teste de mesa](http://br.answers.yahoo.com/question/index?qid=20090203065437AAYWuPo) (risos incontroláveis).

De qualquer forma, estamos aí. Agora podemos depurar a criação de qualquer thread, qualquer processo, o carregamento de qualquer módulo, e a chamada a qualquer função do kernel.

Para depurar a criação de qualquer thread: coloque um breakpoint na função **PsCreateSystemThread**.

    
    kd> bp PsCreateSystemThread
    kd> bl
     0 e 805c732e     0001 (0001) nt!PsCreateSystemThread
    
    kd> g
    Breakpoint 0 hit
    nt!PsCreateSystemThread:
    805c732e 8bff            mov     edi,edi
    kd> k
    ChildEBP RetAddr
    805499a8 8069c17e nt!PsCreateSystemThread
    80549a4c 8069c419 nt!PspInitPhase0+0x3f0
    <strong>80549a58 8068509c nt!PsInitSystem+0x33</strong>
    80549be8 80691f28 nt!ExpInitializeExecutive+0x742
    80549c3c 8068fa9f nt!KiInitializeKernel+0x3b2
    00000000 00000000 nt!KiSystemStartup+0x2bf

Para depurar a criação de qualquer processo: coloque um breakpoint na função **PspCreateProcess**, logo no começo. Será possível capturar a criação do processo System, o processo onde roda a primeira thread do kernel, que inicializa o resto dos componentes.

    
    kd> bp PspCreateProcess
    kd> bl
     0 e 805c6a8c     0001 (0001) nt!PspCreateProcess
    
    kd> g
    Breakpoint 0 hit
    nt!PspCreateProcess:
    805c6a8c 681c010000      push    11Ch
    kd> k
    ChildEBP RetAddr
    805499a0 8069c0dc nt!PspCreateProcess
    <strong>80549a4c 8069c419 nt!PspInitPhase0+0x34e</strong>
    80549a58 8068509c nt!PsInitSystem+0x33
    80549be8 80691f28 nt!ExpInitializeExecutive+0x742
    80549c3c 8068fa9f nt!KiInitializeKernel+0x3b2
    00000000 00000000 nt!KiSystemStartup+0x2bf

E não é lindo ver que, após a chamada ao Process Manager o processo REALMENTE foi criado e está na lista de processos?

    
    kd> !process 0 0
    **** NT ACTIVE PROCESS DUMP ****
    TYPE mismatch for process object at 8055a0d0
    kd> gu
    nt!PspInitPhase0+0x34e:
    8069c0dc 85c0            test    eax,eax
    kd> !process 0 0
    **** NT ACTIVE PROCESS DUMP ****
    PROCESS 81bcc830  SessionId: none  Cid: 0004    Peb: 00000000  ParentCid: 0000
        DirBase: 00319000  ObjectTable: e1000cc0  HandleCount:   1.
    <strong>    Image: System Process</strong>

É nesse momento que percebemos que um processo, uma thread, um qualquer-coisa dentro do kernel não é nada mais nada menos que **um item em uma lista**. Quase tudo no kernel será um item numa lista com um monte de ponteiros referenciando outras estruturas. É isso que mantém a lógica e a coerência no sistema inteiro. Tudo isso é basicamente software, construído como castelos no ar.

O próximo processo a ser criado, logo após carregar todos os drivers, é o nosso amigo SMSS, o Gerenciador de Sessão, o primeiro pedacinho do iceberg que desponta no oceano. É ele que irá iniciar toda a "parte user-mode do kernel".

<blockquote>_Nota: Apesar de parecer contraditório, algumas partes do kernel são de fato implementadas em user mode. Os motivos podem variar, mas geralmente são maior segurança (código que não precisa rodar em um ring privilegiado) e desempenho (código que não precisa de muita prioridade)._</blockquote>

    
    Breakpoint 0 hit
    nt!PspCreateProcess:
    805c6a8c 681c010000      push    11Ch
    kd> kv
    ChildEBP RetAddr  Args to Child
    f9dc365c 805c73e1 f9dc3858 001f0fff f9dc37c0 nt!PspCreateProcess (FPO: [Non-Fpo])
    f9dc36b0 805c745d f9dc3858 001f0fff f9dc37c0 nt!NtCreateProcessEx+0x77 (FPO: [Non-Fpo])
    f9dc36dc 8053d638 f9dc3858 001f0fff f9dc37c0 nt!NtCreateProcess+0x3d (FPO: [Non-Fpo])
    f9dc36dc 804fe155 f9dc3858 001f0fff f9dc37c0 nt!KiFastCallEntry+0xf8 (FPO: [0,0] TrapFrame @ f9dc3704)
    f9dc3774 8069caa3 f9dc3858 001f0fff f9dc37c0 nt!ZwCreateProcess+0x11 (FPO: [8,0,0])
    f9dc3818 80686681 <strong>f9dc38b0</strong> 00000040 00040000 nt!RtlCreateUserProcess+0x125 (FPO: [Non-Fpo])
    f9dc3dac 805c6160 80087000 00000000 00000000 nt!Phase1Initialization+0x1059 (FPO: [Non-Fpo])
    f9dc3ddc 80541dd2 80685628 80087000 00000000 nt!PspSystemThreadStartup+0x34 (FPO: [Non-Fpo])
    00000000 00000000 00000000 00000000 00000000 nt!KiThreadStartup+0x16
    kd> !ustr <strong>f9dc38b0</strong>
    <strong>String(58,520) at f9dc38b0: \SystemRoot\System32\smss.exe</strong>
    
    kd> gu
    kd> !process 0 0
    **** NT ACTIVE PROCESS DUMP ****
    PROCESS 81bcc830  SessionId: none  Cid: 0004    Peb: 00000000  ParentCid: 0000
        DirBase: 00319000  ObjectTable: e1000cc0  HandleCount:  52.
        Image: System
    
    PROCESS 81a2a430  SessionId: none  Cid: 0218    Peb: 7ffd6000  ParentCid: 0004
        DirBase: 08500020  ObjectTable: e1584818  HandleCount:   0.
    <strong>    Image: smss.exe</strong>

Como podemos ver, isso é muito divertido e muito extenso. Poderíamos ir para qualquer lado da evolução do boot. Talvez em artigos futuros daremos uma olhada no processo de logon de um usuário, o que nos obrigaria a ter uma leve noção de como o Windows autentica e autoriza as pessoas. ou talvez daremos uma passadinha no sistema de escalonamento de threads do kernel, um assunto pra lá de complicado e esotérico.

<blockquote>_Nota: Eu pessoalmente recomendo acompanhar o processo de boot descrito por Russinovich e depurar passo-a-passo um boot de verdade. Serão horas e mais horas de puro conhecimento empírico catalogado em seu cérebro-depurador._</blockquote>

Então até lá. Com licença que eu preciso ver a criação do System mais uma vez.

    
    .reboot