---
categories:
- draft
- blog
date: '2010-08-16'
title: Evento C++
---

Esse fim-de-semana houve o tão falado evento C++, com a presença de dezenas de pessoas, algo que eu sinceramente não esperava. O bom desse evento foi saber que existem tantas pessoas interessadas em manter contato com quem gosta e pratica essa linguagem e também em saber que o nível técnico das palestras estão de alto para avançado.

Infelizmente em nenhuma das duas palestras práticas (minha e do Fernando) houve participação interativa, e ninguém que eu saiba abriu meu pacote-surpresa com os dumps a serem analisados. De qualquer forma, minha palestra ficou bagunçada pelo excesso de conteúdo e falta de tempo, o que me fez dar boas risadas ao ouvir no twitter que [minha palestra foi mais um brainstorm](http://twitter.com/nicolasgavlak/status/21201995301). A intenção não era essa, claro, mas meu claro despreparo para muito conteúdo gerou essa impressão. Espero que do pouco que consegui explicar alguém tenha achado utilidade.

E, pelo jeito, futuramente irei aplicar essa mesma metodologia brainstorm em um videocast, que ainda não decidi como irei preparar. A ideia é analisarmos alguns dumps em conjunto e, para os que acompanharem online, a interatividade de perguntas & respostas.

Mas enquanto isso não acontece vamos dar uma olhada no que tínhamos no [pacote-surpresa](http://www.caloni.com.br/nao-e-minha-culpa).

#### 1. NotMyFaultEither.exe.mdmp - Stack Trash

    
    0:000> kv
    ChildEBP RetAddr  Args to Child
    0012b200 7c90df3c 7c8025db 000000e8 00000000 ntdll!KiFastSystemCallRet
    0012b204 7c8025db 000000e8 00000000 0012b238 ntdll!NtWaitForSingleObject+0xc
    0012b268 7c802542 000000e8 000493e0 00000000 kernel32!WaitForSingleObjectEx+0xa8
    0012b27c 6998ada6 000000e8 000493e0 003a0043 kernel32!WaitForSingleObject+0x12
    0012bd70 6998aff1 000000c4 00000568 000000d0 faultrep!InternalGenerateMinidumpEx+0x335
    0012bd9c 6998b50a 000000c4 00000568 0012c698 faultrep!InternalGenerateMinidump+0x75
    0012c678 69986652 000000c4 00000568 0012c698 faultrep!InternalGenFullAndTriageMinidumps+0x8a
    0012dea0 69987d3d 0012df18 0015c300 00000000 faultrep!ReportFaultDWM+0x4e5
    0012e398 699882d8 0040a1dc 0012f1e0 ffffffff faultrep!StartManifestReportImmediate+0x268
    0012f404 7c8643c6 0040a1dc ffffffff 0012fc24 faultrep!ReportFault+0x55a
    Unable to load image C:\Documents and Settings\Administrador\Desktop\NotMyFaultEither.exe
    *** WARNING: Unable to verify timestamp for NotMyFaultEither.exe
    *** ERROR: Module load completed but symbols could not be loaded for NotMyFaultEither.exe
    0012f678 004018aa 0040a1dc e280eec4 1d7f113b kernel32!UnhandledExceptionFilter+0x55b
    WARNING: Stack unwind information not available. Following frames may be wrong.
    0012f9ac 00401357 <font color="#ff0000">dededede dededede dededede</font> NotMyFaultEither+0x18aa
    0012fbe8 <font color="#ff0000">dededede dededede dededede dededede</font> NotMyFaultEither+0x1357
    0012fbec <font color="#ff0000">dededede dededede dededede dededede</font> 0xdededede
    0012fbf4 <font color="#ff0000">dededede dededede dededede dededede</font> 0xdededede
    ...

Como foi visto na palestra, uma pilha nesse estado demonstra claramente alguma variável que estourou e corrompeu o resto da pilha de chamadas. Na hora de voltar para a função chamadora, o endereço usado foi o endereço reescrito por lixo, e daí temos o "crash-pattern" Stack Trash.

#### 2. NotMyFaultEither.mdmp - Dead Lock

    
    0:000> kv
    ChildEBP RetAddr  Args to Child
    0012f900 7c90df3c 7c8025db 0000007c 00000000 ntdll!KiFastSystemCallRet
    0012f904 7c8025db <font color="#ff0000">0000007c </font>00000000 00000000 ntdll!NtWaitForSingleObject+0xc
    0012f968 7c802542 0000007c ffffffff 00000000 kernel32!WaitForSingleObjectEx+0xa8
    0012f97c 00401176 0000007c ffffffff 00000111 kernel32!WaitForSingleObject+0x12
    WARNING: Stack unwind information not available. Following frames may be wrong.
    0012f9c0 7c910202 00000002 001506e8 00150000 NotMyFaultEither+0x1176
    0012f9f8 7e3746d3 01010050 00000000 00000000 ntdll!RtlpAllocateFromHeapLookaside+0x42
    0012fa5c 7e382672 01010050 01100068 7e3a4716 user32!DrawStateW+0x5cd
    0012fae8 7e382c75 001563ac 01010050 00000003 user32!xxxBNDrawText+0x313
    0012fb20 002d0036 00000000 00000020 0012fb3c user32!xxxDrawButton+0xbb
    0012fb30 7e3799d8 0000800a 0012fbc8 7e375ba2 0x2d0036
    0012fb3c 7e375ba2 0000800a 002d0036 fffffffc user32!NotifyWinEvent+0xd
    0012fbc8 00000000 002d0036 004011b0 dcbaabcd user32!ButtonWndProcWorker+0x79b
    0:000> !handle 0000007c
    Handle <font color="#ff0000">0000007c</font>
      Type         	<font color="#ff0000">Thread</font>
    0:000> ~* kv
    
    .  0  Id: 5e4.<font color="#008000">39c </font>Suspend: 0 Teb: 7ffdd000 Unfrozen
    ChildEBP RetAddr  Args to Child
    0012f900 7c90df3c 7c8025db 0000007c 00000000 ntdll!KiFastSystemCallRet
    0012f904 7c8025db 0000007c 00000000 00000000 ntdll!NtWaitForSingleObject+0xc
    0012f968 7c802542 0000007c ffffffff 00000000 kernel32!WaitForSingleObjectEx+0xa8
    0012f97c 00401176 0000007c ffffffff 00000111 kernel32!WaitForSingleObject+0x12
    WARNING: Stack unwind information not available. Following frames may be wrong.
    0012f9c0 7c910202 00000002 001506e8 00150000 NotMyFaultEither+0x1176
    0012f9f8 7e3746d3 01010050 00000000 00000000 ntdll!RtlpAllocateFromHeapLookaside+0x42
    0012fa5c 7e382672 01010050 01100068 7e3a4716 user32!DrawStateW+0x5cd
    0012fae8 7e382c75 001563ac 01010050 00000003 user32!xxxBNDrawText+0x313
    0012fb20 002d0036 00000000 00000020 0012fb3c user32!xxxDrawButton+0xbb
    0012fb30 7e3799d8 0000800a 0012fbc8 7e375ba2 0x2d0036
    0012fb3c 7e375ba2 0000800a 002d0036 fffffffc user32!NotifyWinEvent+0xd
    0012fbc8 00000000 002d0036 004011b0 dcbaabcd user32!ButtonWndProcWorker+0x79b
    
       1  Id: 5e4.6a4 Suspend: 0 Teb: 7ffdc000 Unfrozen
    ChildEBP RetAddr  Args to Child
    00b8ff10 7c90df3c 7c91b22b 00000080 00000000 ntdll!KiFastSystemCallRet
    00b8ff14 7c91b22b 00000080 00000000 00000000 ntdll!NtWaitForSingleObject+0xc
    00b8ff9c 7c901046 0040e940 004010e0 0040e940 ntdll!RtlpWaitForCriticalSection+0x132
    00b8ffa4 004010e0 <font color="#0000ff">0040e940 </font>00000000 00000000 ntdll!RtlEnterCriticalSection+0x46
    WARNING: Stack unwind information not available. Following frames may be wrong.
    00b8ffec 00000000 004010c0 0012f99c 00000000 NotMyFaultEither+0x10e0
    0:000> !cs <font color="#0000ff">0040e940</font>
    -----------------------------------------
    Critical section   = 0x0040e940 (NotMyFaultEither+0xE940)
    DebugInfo          = 0x00154498
    <font color="#0000ff">LOCKED</font>
    LockCount          = 0x1
    OwningThread       = <font color="#008000">0x0000039c</font>
    RecursionCount     = 0x1
    LockSemaphore      = 0x80
    SpinCount          = 0x00000000

A thread ativa no momento do dump aguardava por outra thread. Listando todas as threads do processo temos a primeira e a segunda, que tenta entrar em um critical section. Quando vemos que aquele CS estava sendo bloqueado pela primeira thread vemos claramente se tratar de um dead lock.

#### 3. NotMyFaultEither_100808_172407.dmp - Access Violation

    
    0:000> kv
    ChildEBP RetAddr  Args to Child
    WARNING: Stack unwind information not available. Following frames may be wrong.
    0012f9cc 7e37f916 01010052 005a0049 0012f9f4 NotMyFaultEither+0x10a3
    0012fa58 7e37f991 01010052 00000043 01100076 user32!ClientFrame+0xe0
    0012fa7c 7e382909 01010052 0012fa98 00000000 user32!DrawFocusRect+0x40
    0012fae8 7e382c75 00156304 01010052 00000003 user32!xxxBNDrawText+0x3e9
    0012fb20 001100a0 00000000 00000020 0012fb3c user32!xxxDrawButton+0xbb
    0012fb30 7e3799d8 0000800a 0012fbc8 7e375ba2 0x1100a0
    0012fb3c 7e375ba2 0000800a 001100a0 fffffffc user32!NotifyWinEvent+0xd
    0012fbc8 00000000 001100a0 004010f0 dcbaabcd user32!ButtonWndProcWorker+0x79b
    0:000> <font color="#ff0000">? eax+edx</font>
    Evaluate expression: 0 = <font color="#ff0000">00000000</font>
    0:000> u
    NotMyFaultEither+0x10a3:
    004010a3 66890c02        mov     word ptr [<font color="#ff0000">edx+eax</font>],cx
    004010a7 83c002          add     eax,2
    004010aa 6685c9          test    cx,cx

O disassemble da instrução inválida tenta escrever claramente em cima do endereço zerado (edx + eax). Dessa forma fica fácil saber que esse tipo de escrita não é permitido, constituindo nosso famosíssimo AV.

#### 4. NotMyFaultEither_100808_175404.dmp - Exception not Handled

    
    eax=00000000 ebx=00000111 ecx=7c91003d edx=00010000 esi=00330120 edi=7e374dfa
    eip=7c90120e esp=0012f9a0 ebp=00000001 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    ntdll!DbgBreakPoint:
    <font color="#ff0000">7c90120e cc              int     3</font>
    0:000> kv
    ChildEBP RetAddr  Args to Child
    0012f99c 004011ec 0012fc24 004010d0 0012fbe8 <font color="#ff0000">ntdll!DbgBreakPoint</font> (FPO: [0,0,0])
    WARNING: Stack unwind information not available. Following frames may be wrong.
    0012f9cc 7e37f916 01010054 005a0049 0012f9f4 NotMyFaultEither+0x11ec
    0012fa58 7e37f991 01010054 00000043 01100076 user32!ClientFrame+0xe0

Esse foi meio de brinde. Uma exceção de breakpoint (int 3, ntdll!DbgBreakPoint) lançada sem um depurador atachado implica em derrubamento do processo, pois é uma exceção como outra qualquer. O programador deve ter esquecido um DebugBreak ou algo que o valha no código de produção, que acabou sendo executado.

##### 5. ntdll_cliente.dll - Importação de símbolos

[![vm-sony-xp-2010-08-08-17-59-22.png](http://i.imgur.com/ETJrBGa.png)](/images/vm-sony-xp-2010-08-08-17-59-22.png)
Essa foi a DLL encontrada no cliente quando ocorreu o problema relatado na imagem, também em anexo. Isso foi demonstrado na palestra com a ajuda do meu script que carrega DLLs, além de um pouco de sorte. Podemos analisar esse caso com mais calma em outro artigo. Acho que já falei demais por aqui.

#### Slides

	
  * Download dos [slides](/images/crash-dump-analysis-slides.zip) usados na palestra.