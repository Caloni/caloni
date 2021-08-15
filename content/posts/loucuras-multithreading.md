---
categories:
- blog
date: '2011-03-18'
tags:
title: Loucuras multithreading
---

Estava eu depurando um sistema cliente/servidor com um tantão de threads e me veio à cabeça na volta pra casa como que um programador iniciante entenderia aquela bagunça de dar F10 em uma função e cair no meio de outra, dar outro F10 na outra e voltar pra primeira.

Loucura, não?

Nem tanto. O multithreading de um sistema operacional está aí pra isso. O que ocorre, no caso de depurações em uma única IDE, é que os breakpoints temporários que são definidos ao usar o comando de step into/over podem ser ativados em paralelo, simultaneamente.

Mas confesso que, de vez em quando, depurar múltiplas threads fica parecendo coisa de maluco.
