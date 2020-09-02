---
date: "2010-07-26"
tags: [ "code", "draft",  ]
title: "Breakpoints promíscuos"
---
Ontem falei sobre como "brincar" com os breakpoints promíscuos, ou seja, aqueles que topam qualquer processo. Isso

é muito simples de se fazer:

- Configure uma VM para bootar em kernel debug.
- Encontre um processo qualquer (vamos usar o notepad pra variar?).
- Reabra os símbolos de user mode nele.
- Defina um breakpoint em alguma DLL de user mode.

Como meus leitores são muito espertos foi partir para o momento após rodarmos um notepad.exe:


O screenshot diz tudo:

Agora a parte mais divertida: experimente com outro notepad, ou com o explorer =)
