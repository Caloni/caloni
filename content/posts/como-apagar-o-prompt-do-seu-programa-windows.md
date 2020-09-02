---
date: "2018-01-23"
tags: [ "code", "draft",  ]
title: "Como Apagar o Prompt do seu Programa Windows"
---
Geralmente se cria um projeto console/prompt quando há a necessidade de interfacear com o usuário com o uso da tela preta, saída padrão, etc. E no caso do Windows também há a possibilidade de criar um programa Win32 onde não há prompt, pois a função do programa ou é ser invisível ou criar, sabe como é, janelas. Mas nenhum dos dois possibilita ambos ao mesmo tempo. Este snippet permite que você faça isso.


Para isso funcionar você criar um projeto console no Visual Studo. Essa opção está no Linker, System, Heap Reserve Size.
