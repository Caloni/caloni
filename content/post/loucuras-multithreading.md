---
date: "2011-03-18"
title: Loucuras multithreading
categories: [ "blog" ]
---
Estava eu depurando um sistema cliente/servidor com um tantão de threads e me veio à cabeça na volta pra casa como que um programador iniciante entenderia aquela bagunça de dar F10 em uma função e cair no meio de outra, dar outro F10 na outra e voltar pra primeira.

Loucura, não?

Nem tanto. O multithreading de um sistema operacional está aí pra isso. O que ocorre, no caso de depurações em uma única IDE, é que os breakpoints temporários que são definidos ao usar o comando de step into/over podem ser ativados em paralelo, simultaneamente.

!](http://i.imgur.com/VIZxPX9.jpg)Quando um breakpoint é ativado, seja um pontinho vermelho no começo da linha ou o efeito de um F10, que gera um breakpoint temporário para a próxima linha de execução, o depurador recebe a mensagem e automaticamente, no próximo resume de execução, pára na linha onde ocorreu o evento. Aliás, [uma das minhas soluções anti-debugging pode ser aproveitada para capturar os breakpoints de step into.

Mas confesso que, de vez em quando, depurar múltiplas threads fica parecendo coisa de maluco.
