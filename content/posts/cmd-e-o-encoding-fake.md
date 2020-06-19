---
categories: [ "code" ]
date: "2017-12-26"
tags: [ "draft",  ]
title: "Cmd e o encoding fake"
---
Qualquer um que já tenha mexido no prompt de comandos do Windows sabe que ele permite você escolher qual code page utilizar para enviar e receber comandos. O Windows é todo em UTF-16, mas as saídas podem vir de qualquer programa com qualquer encoding. A missão do cmd.exe é usar o encoding escolhido pelo usuário para exibir os caracteres na tela. Vamos supor que nós criemos uma pasta com acentos no nome (pelo Explorer para não ter erro):

Agora através de um cmd.exe podemos observar como esse nome acentuado aparece:

Note como o "a" acentuado com til aparece perfeitamente. Também note que o codepage utilizado é o 437.

Até aí tudo bem, certo?

Não! Não! Não!

O codepage 437 não possui ã. Nem õ.

Isso, meus amigos, é chamado tecnicamente na área de "muito louco".

Curioso a respeito disso, resolvi observar a saída padrão do cmd.exe, para ver o que diabos vem como resultado. Para isso desenvolvi um simples output redirector tabajara:


Simples, bonito e prático. Quando executamos Redirector.exe ele executa um cmd.exe, com a diferença que a saída dele vai parar no arquivo cmd.log, que podemos observar com um BareTail da vida.

Opa, opa, opa!

O til sumiu!

Se formos analisar os bytes que vieram de saída, vamos constatar que o byte referente ao ã foi enviado para a saída padrão como o byte 0x61, ou 97 em decimal. No codepage 437 (e em qualquer derivado da tabela ASCII, na verdade) o byte 97 é representado como "a", simplesmente, sem til.

Isso quer dizer que ao receber um "ã" o cmd.exe o reinterpreta como "a", mesmo estando sob o encoding 437. Esse é o resultado de um prompt user friendly que quer seu amigo.

Se analisarmos a memória do cmd.exe veremos que ele armazena as coisas em UTF-16, como qualquer programa Windows nativo unicode.


E com isso constatamos que não necessariamente no Windows, What You See Is What You Get. Ou, em termos mais filosóficos, What You See Is Not What I Get.
