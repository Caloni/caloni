---
categories: [ "code" ]
date: "2011-07-26"
tags: [ "draft",  ]
title: "Depuração de emergência"
---
O programa está rodando no servidor do cliente, que é acessível por sessão remota do Windows, mas de repente ele capota. Existem aí duas possibilidades fora o debug remoto (que, nesse caso, não é possível):

	
  1. Analisar um dump gerado.

	
  2. Depurar localmente o problema.

Para a primeira opção, basta abrir o Gerenciador de Tarefas, localizar o processo e gerar o dump através do menu de contexto.

Com o dump e o Windbg em mãos, basta analisá-lo. Porém, se o seu processo é 32 bits e o servidor é 64 bits (geralmente é), o dump gerado será de 64 bits, EMBORA seja de um process 32. Ou seja, ao abri-lo, o sistema vai mostrar as threads de manipulação do SO para sistemas 32 (todos com o nosso amigo wow64cpu).

    
    Microsoft (R) Windows Debugger Version 6.12.0002.633 AMD64
     Copyright (c) Microsoft Corporation. All rights reserved.

    
    Loading Dump File [C:\Tests\CrashOnServer.DMP]
     User Mini Dump File with Full Memory: Only application data is available

    
    Executable search path is:
     Windows 7 Version 7600 MP (2 procs) <span style="color: #ff0000;">Free x64</span>
     Product: WinNt, suite: SingleUserTS
     Machine Name:
     Debug session time: Tue Jul 26 09:26:23.000 2011 (UTC - 3:00)
     System Uptime: 0 days 0:35:47.425
     Process Uptime: 0 days 0:00:42.000
     ...........WARNING: MSVCR100D overlaps MSVCP100D

    
    *** ERROR: Symbol file could not be found. Defaulted to export symbols for ntdll.dll -
     *** ERROR: Symbol file could not be found. Defaulted to export symbols for wow64cpu.dll -
     wow64cpu!TurboDispatchJumpAddressEnd+0x690:
     00000000`745d2dd9 c3 ret
     0:000> kv
     Child-SP RetAddr : Args to Child : Call Site
     00000000`001ce6c8 00000000`745d282c :  : wow64cpu!TurboDispatchJumpAddressEnd+0x690
     *** ERROR: Symbol file could not be found. Defaulted to export symbols for wow64.dll -
     00000000`001ce6d0 00000000`7464d07e :  : wow64cpu!TurboDispatchJumpAddressEnd+0xe3
     00000000`001ce790 00000000`7464c549 :  : wow64!Wow64SystemServiceEx+0x1ce
     00000000`001ce7e0 00000000`76deae27 :  : wow64!Wow64LdrpInitialize+0x429
     00000000`001ced30 00000000`76de72f8 :  : ntdll!LdrGetKnownDllSectionHandle+0x1a7
     00000000`001cf230 00000000`76dd2ace :  : ntdll!RtlInitCodePageTable+0xe8
     00000000`001cf2a0 00000000`00000000 : : ntdll!LdrInitializeThunk+0xe

    
    Para entrar dentro do Inception, é necessário usar a extensão wow64exts e usar o comando ".effmach x86".

    
    0:000> .load wow64exts
     0:000> .effmach x86
     Effective machine: x86 compatible (x86)
     0:000:x86> kv
     ChildEBP RetAddr Args to Child
     ..
     0035ec98 0035ecac 0035ecfc 0035ecac 0035ecfc ntdll_76f80000!KiUserExceptionDispatcher+0xf (FPO: [2,0,0])
     *** WARNING: Unable to verify checksum for CrashOnServer.exe
     WARNING: Frame IP not in any known module. Following frames may be wrong.
     0035f0bc 01181ca9 0035f198 0035f19c 00000000 0x35ecac
     0035f190 01181b7d 009d80a0 5fb4d717 00000000 CrashOnServer!Log::LogError+0x29
     0035fb08 01186f1f 00000001 009d1410 009d1c68 CrashOnServer!main+0x12d
     0035fb58 01186d4f 0035fb6c 76543677 7efde000 CrashOnServer!__tmainCRTStartup+0x1bf
     0035fb60 76543677 7efde000 0035fbac 76fb9f02 CrashOnServer!mainCRTStartup+0xf
     0035fb6c 76fb9f02 7efde000 771dc110 00000000 kernel32!BaseThreadInitThunk+0xe
     0035fbac 76fb9ed5 01181316 7efde000 00000000 ntdll_76f80000!__RtlUserThreadStart+0x70
     0035fbc4 00000000 01181316 7efde000 00000000 ntdll_76f80000!_RtlUserThreadStart+0x1b

Após esse último passo, siga para o último passo desse tutorial. Ou escolha a segunda opção:

Para depurar localmente, supondo que seja um executável simples, você precisa dos seguintes itens:

	
  * Pasta do WinDbg copiado (a Debugging Tools instalada pelo SDK, ou sua pastinha particular guardada no PenDrive).

	
  * Símbolos dos binários envolvidos (em sincronia com os binários que iremos analisar).

	
  * Fontes da compilação dos binários (a versão exata seria ideal; grave o revno do controle de fonte pra facilitar).

Os fontes, no caso de uma conexão por Terminal Server, podem ser disponibilizados através do mapeamento de drives entre as máquinas. Os símbolos, no entanto, por serem usados extensivamente pelo WinDbg, é recomendável que estejam locais na máquina depurada, pois do contrário você terá que tomar uma quantidade excessiva de cafés para executar meia-dúzia de instruções.

Supondo que temos tudo isso, só precisamos executar alguns passos básicos para o setup:

    
    <span style="font-family: Consolas, Monaco, monospace; font-size: 12px; line-height: 18px; white-space: pre;" class="Apple-style-span">.symfix 
    .sympath+ 
    .reload
    </span><span style="font-family: Consolas, Monaco, monospace; font-size: 12px; line-height: 18px; white-space: pre;" class="Apple-style-span">.srcpath 
    </span><span style="font-family: Consolas, Monaco, monospace; font-size: 12px; line-height: 18px; white-space: pre;" class="Apple-style-span">.reload /f CrashOnServer.exe</span>

    
    0:000> .symfix c:\tools\symbols
     0:000> .sympath+ C:\Projetos\Caloni\Posts\Debug
     Symbol search path is: srv*;C:\Projetos\Caloni\Posts\Debug
     Expanded Symbol search path is: SRV*c:\tools\symbols*http://msdl.microsoft.com/download/symbols;c:\projetos\caloni\posts\debug
     0:000> .reload
     Reloading current modules
     ......
     0:000> .srcpath C:\Projetos\Caloni\Posts
     Source search path is: C:\Projetos\Caloni\Posts
     0:000> .reload /f CrashOnServer.exe
     *** WARNING: Unable to verify checksum for CrashOnServer.exe
     0:000> lm
     start end module name
     00000000`01170000 00000000`01193000 CrashOnServer C (private pdb symbols) C:\Projetos\Caloni\Posts\Debug\CrashOnServer.pdb
     00000000`745d0000 00000000`745d8000 wow64cpu (deferred)
     00000000`745e0000 00000000`7463c000 wow64win (deferred)
     00000000`74640000 00000000`7467f000 wow64 (deferred)
     00000000`76da0000 00000000`76f4c000 ntdll (pdb symbols) c:\tools\symbols\ntdll.pdb\\ntdll.pdb
     00000000`76f80000 00000000`77100000 ntdll32 (deferred)

Por último, execute o seguinte comando na tela de comandos do WinDbg:

    
    .hh

E boa sorte =)
