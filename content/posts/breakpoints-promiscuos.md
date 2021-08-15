---
categories:
- blog
date: '2010-07-26'
tags:
title: Breakpoints promíscuos
---

Ontem falei sobre como "brincar" com os breakpoints promíscuos, ou seja, aqueles que topam qualquer processo. Isso

é muito simples de se fazer:

- [Configure uma VM para bootar em kernel debug](http://driverentry.com.br/blog/?p=433).
- Encontre um processo qualquer (vamos usar o notepad pra variar?).
- Reabra os símbolos de user mode nele.
- Defina um breakpoint em alguma DLL de user mode.

Como meus leitores são muito espertos foi partir para o momento após rodarmos um notepad.exe:

    
    kd> !process 0 0 notepad.exe
    PROCESS 81681be0  SessionId: 0  Cid: 0598    Peb: 7ffd7000  ParentCid: 0200
        DirBase: 08740260  ObjectTable: e18ee8d8  HandleCount:  29.
        Image: notepad.exe
    
    kd> .process /i 81681be0
    You need to continue execution (press 'g' <enter>) for the context
    to be switched. When the debugger breaks in again, you will be in
    the new process context.
    kd> g
    Break instruction exception - code 80000003 (first chance)
    nt!RtlpBreakWithStatusInstruction:
    80527bdc cc              int     3
    kd> .reload /user
    Loading User Symbols
    .......................
    kd> bp user32!MessageBoxExW
    kd> g
    Breakpoint 0 hit
    USER32!MessageBoxExW:
    001b:7e3a0838 8bff            mov     edi,edi
    kd> du poi(esp+8)
    0007cfb8  "naoexistetralala.txt.Arquivo não"
    0007cff8  " encontrado..Verifique se o nome"
    0007d038  " do arquivo correto foi especifi"
    0007d078  "cado."
    kd> ezu poi(esp+8) "Esse arquivo não existe! Mas é muito mané, não é mesmo?"
    kd> g

O screenshot diz tudo:

[![Debug do notepad pelo kernel](http://i.imgur.com/fHldlXA.png)](/images/debug-notepad-kernel.png)

Agora a parte mais divertida: experimente com outro notepad, ou com o explorer =)
