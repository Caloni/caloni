---
categories:
- code
date: '2010-01-11'
tags:
- draft
title: Importando tipos de outros projetos
---

A engenharia reversa das entranhas do kernel não tem limites se você sabe o que está fazendo. No entanto, algumas facilidades do depurador podem ajudar a minimizar o tempo que gastamos para analisar uma simples estrutura. Por exemplo, o [Process Environment Block](http://msdn.microsoft.com/en-us/library/aa813706%28VS.85%29.aspx) de um processo específico.

    
    windbg -kl
    
    Microsoft (R) Windows Debugger Version 6.9.0003.113 X86
    Copyright (c) Microsoft Corporation. All rights reserved.
    
    Connected to Windows XP 2600 x86 compatible target, ptr64 FALSE
    Symbol search path is: SRV*c:\tools\symbols*http://msdl.microsoft.com/download/symbols
    Executable search path is:
    *******************************************************************************
    WARNING: Local kernel debugging requires booting with kernel
    debugging support (/debug or bcdedit -debug on) to work optimally.
    *******************************************************************************
    Windows XP Kernel Version 2600 (Service Pack 3) MP (2 procs) Free x86 compatible
    Product: WinNt, suite: TerminalServer SingleUserTS
    Built by: 2600.xpsp_sp3_gdr.090804-1435
    Kernel base = 0x804d7000 PsLoadedModuleList = 0x8055d720
    Debug session time: Mon Jan 11 10:36:50.061 2010 (GMT-2)
    System Uptime: 5 days 1:05:24.958
    
    Microsoft (R) Windows Debugger Version 6.9.0003.113 X86
    Copyright (c) Microsoft Corporation. All rights reserved.
    
    lkd> !process 0 0 notepad.exe
    <font color="#0000ff">PROCESS 89068700 </font> SessionId: 0  Cid: 0ec4   <font color="#0000ff"> Peb: 7ffda000</font>  ParentCid: 0b0c
        DirBase: 0ac80a80  ObjectTable: e143a7d8  HandleCount: 152.
        Image: notepad.exe

O comando [!peb](http://windbg.info/doc/1-common-cmds.html#11_process) traz inúmeras informações sobre essa estrutura. Mas talvez estivéssemos interessados em coisas não mostradas por esse comando, mas [que existem na estrutura](http://undocumented.ntinternals.net/UserMode/Undocumented%20Functions/NT%20Objects/Process/PEB.html).

![PEB ¿não-documentado¿](http://i.imgur.com/L3E4KSS.png)

Nesse caso, podemos criar um projeto vazio que contenha a definição da estrutura **como acreditamos** que esteja na versão do kernel que estamos depurando.

![MyPEB](http://i.imgur.com/l4oLJHR.png)

Compilamos e geramos um PDB (arquivo de símbolos) que contém a definição desse tipo. Tudo que precisamos fazer agora é carregar esse símbolo na sessão que estivermos depurando.

É claro que nosso executável não vai existir na sessão de kernel local, mas isso não importa. Podemos usar qualquer módulo carregado e usá-lo como _host _de nosso conjunto de símbolos:

    
    lkd> lm
    start    end        module name
    804d7000 806e5000   nt         (pdb symbols)          c:\tools\symbols\ntkrpamp.pdb\D8743252F83B4F59985D6E19F33BFCAF1\ntkrpamp.pdb
    
    Unloaded modules:
    a5513000 a553e000   kmixer.sys
    <font color="#0000ff">bac50000 bac57000   USBSTOR.SYS</font>
    a5711000 a5746000   truecrypt.sys
    a5731000 a5746000   wudfrd.sys
    a5a19000 a5a23000   wpdusb.sys
    ...
    a5731000 a5746000   wudfrd.sys
    a57a9000 a57b3000   wpdusb.sys
    a571b000 a5746000   kmixer.sys
    babf0000 babf5000   Cdaudio.SYS
    ba489000 ba48c000   Sfloppy.SYS
    babe8000 babed000   Flpydisk.SYS
    babe0000 babe7000   Fdc.SYS 
    
    ------ Build started: Project: KernelTypes, Configuration: Debug Win32 ------
    Compiling...
    KernelTypes.cpp
    Linking...
    LINK : program database c:\Tests\KernelTypes\Debug\<font color="#0000ff">KernelTypes.pdb</font> missing; performing full link
    Embedding manifest...
    Build log was saved at "file://c:\Tests\KernelTypes\Debug\BuildLog.htm"
    KernelTypes - 0 error(s), 0 warning(s)
    ========== Build: 1 succeeded, 0 failed, 0 up-to-date, 0 skipped ==========
    
    Microsoft Windows XP [versÎáÎ÷Îýo 5.1.2600]
    (C) Copyright 1985-2001 Microsoft Corp.
    
    C:\Tests\KernelTypes\Debug>ren KernelTypes.pdb <font color="#0000ff">usbstor.pdb</font>
    
    lkd> .sympath C:\Tests\KernelTypes\Debug
    Symbol search path is: C:\Tests\KernelTypes\Debug
    <font color="#0000ff">lkd> .reload /i /f usbstor.sys</font>
    lkd> lm m usb*
    start    end        module name
    bac60000 bac66700   USBSTOR  M (private pdb symbols)  <font color="#0000ff">C:\Tests\KernelTypes\Debug\usbstor.pdb</font>

Depois que o símbolo foi carregado em nosso módulo de mentirinha, tudo que temos a fazer é alterar o contexto do processo atual (para que os endereços de user mode façam sentido) e moldar nossa memória com o comando [dt](http://windbg.info/doc/1-common-cmds.html#12_thread), usando o tipo importado do símbolo carregado.

    
    lkd> .process 89068700
    Implicit process is now 89068700
    lkd> dt <font color="#0000ff">usbstor!_peb</font> 7ffda000
       +0x000 InheritedAddressSpace : 0xdc ''
       +0x001 ReadImageFileExecOptions : 0xff ''
       +0x002 BeingDebugged    : 0x35 '5'
       +0x003 SpareBool        : 0x1 ''
       +0x004 Mutant           : 0x01360000
       +0x008 ImageBaseAddress : 0x0135e000
       +0x00c Ldr              : (null)
       +0x010 ProcessParameters : 0x00001e00 _RTL_USER_PROCESS_PARAMETERS
       +0x014 SubSystemData    : (null)
       +0x018 ProcessHeap      : 0x7ffda000
       +0x01c FastPebLock      : (null)
       +0x020 SparePtr1        : 0x00000efc
       +0x024 SparePtr2        : 0x000008b8
       +0x028 EnvironmentUpdateCount : 0
       +0x02c KernelCallbackTable : (null)
       +0x030 SystemReserved   : [1] 0x7ffde000
       +0x034 ExecuteOptions   : 0y00
       +0x034 SpareBits        : 0y000000000000000000000011111100 (0xfc)
       +0x038 FreeList         : (null)
       +0x03c TlsExpansionCounter : 0
    ...

Para que isso funcione, a estrutura definida tem que bater offset por offset com os dados na memória, o que envolve alinhamento (se lembre do [pragma pack](http://msdn.microsoft.com/en-us/library/2e70t5y1%28VS.80%29.aspx)) e versionamento corretos. Se isso não ocorrer, logo aparecerá algum lixo nos membros da estrutura que não fará sentido. Se isso ocorrer, detecte onde o lixo começa e verifique se o membro existe nessa versão do sistema operacional, ou se o alinhamento está de acordo com o módulo analisado.

Acho que não é preciso dizer que isso não serve apenas para kernel mode =)