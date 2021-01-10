---
date: "2007-10-22"
tags: [ "code" ]
title: "Guia básico para programadores de primeiro breakpoint"
---
Aproveitando um dos últimos artigos que fala sobre [conceitos básicos de programação], lembro que, tão importante quanto programar é possuir habilidades básicas de depuração, uma arte por muitos programadores ignorada.

É interessante notar como muitos ignoram a utilidade e conveniência das tradicionais e poderosas ferramentas de depuração passo-a-passo. O motivo pode ser puro desdém ou ignorância (no sentido de desconhecimento). Se for pelo segundo, aí vão algumas dicas para dar uma passada geral no seu programa e, quem sabe, encontrar um ou outro bug pelo caminho.

![](/img/debug.png)

Os comandos mais comuns de debug são: Start/Continue, Break, Stop, Restart, Show Next Statement, Step Into, Step Over e Step Out.

Run ou Debug é o comando primário. Simplesmente inicia uma nova execução de seu programa. Geralmente você deve utilizar esse comando quando já tiver definido seus breakpoints (mais sobre isso abaixo). Do contrário o programa vai iniciar, executar e sair, sem sequer você notar.

O comando Step Over avança uma linha de código-fonte, parando na seguinte, de uma maneira iterativa. É a chamada execução passo-a-passo. Com ele você consegue, com a ajuda das janelas de watch e variáveis locais, analisar passo-a-passo a execução do fluxo de seu programa variando de acordo com as condições do sistema.

Stop Into é um parente bem próximo do Step Over, com a importante diferença de entrar dentro das funções que são chamadas em cada linha de execução. Geralmente é usado quando você pretende revisar todo o fluxo de execução porque escreveu código novo ou porque ainda não chegou na situação que pretende simular ou ainda porque usou o Step Over antes e descobriu que existe algum problema na função X que você passou direto.

Já o Step Out é o complemento dos dois Steps acima. Ele vai sair executar todo o resto da função onde você está e parar exatamente uma linha após a chamada dessa função. Em suma: você já viu o que queria ver dentro da função atual e quer continuar a execução um ou mais níveis acima na pilha de chamadas.

Você não precisa passar por todo o seu código e todos os seus loops/laços de 500 iterações até chegar ao ponto que quer analisar. O breakpoint é um comando nativo do sistema que é dos mais úteis para o programador, capaz de parar o fluxo de execução em um ponto específico do código. O depurador torna disponível para você esse comando que pode ser engatilhado em qualquer linha, geralmente em uma quantidade razoável. Para controlar todos os breakpoints definidos existe uma janela com essa lista que indica, entre outras coisas, se estão habilitados ou não, se possuem alguma condição de quebra, quantas vezes devem parar, etc. Costuma existir um ótimo controle sobre breakpoints nos depuradores, pois esse é um comando muito usado em programação (e dos mais antigos).

Praticamente qualquer ferramenta de debug possui um mecanismo para que você consiga ver o que está dentro das variáveis de seu programa. Basicamente temos uma janela ou comando de watch, ou inspection, onde podemos inserir as variáveis que queremos espiar. Em um nível mais sofisticado, temos as janelas de locals e autos (o nome pode variar), onde podemos ver, respectivamente, as variáveis dentro da função e as variáveis mais próximas do ponto onde o código está parado (as que foram usadas na última linha e as que serão usadas na próxima, por exemplo). Claro que cada ambiente te fornece o que melhor ajudar durante a depuração, assim como o Delphi e o C++ Builder possuem o magnífico Object Inspector, uma janela com todas as propriedades de um objeto qualquer do sistema (uma janela, um botão, uma classe, etc).

Seguindo as janelas e comandos úteis de debug, a pilha de chamadas ou stack trace mostra a pilha da thread atual sendo depurada. Com ela você consegue ver o nome da função que chamou a função que chamou a função que chamou... até a função inicial (por exemplo, o nosso conhecido main, a primeira função de um programa "normal" em C/C++).

No caso de seu programa ser multithreading, ou seja, possuir várias linhas de execução, fluxos distintos de código rodando, existirá uma janela ou comando onde você pode ver qual a thread atual (a que está sendo depurada e destrinchada nas outras janelas) e quais as outras threads. Muitos ambientes permitem que com essa janela seja feito um switch de threads, que é a troca da thread atual, o que irá alterar a janela de pilha de chamadas, de variáveis locais, e muito provavelmente a janela do código-fonte atualmente em execução.

Depurar esteve sempre ligado à programação desde os primórdios da humanidade. Por isso hoje em dia os depuradores estão muito evoluídos, geralmente integrados em um ambiente de desenvolvimento (exs: Visual Studio, KDE Develop) e possuem comandos e mais comandos e mais comandos. Existem comandos, por exemplo, para pular fluxo sem executar, definir um breakpoint temporário, visualizar registradores da máquina, visualizar páginas de memória, controle de exceções, misturar assembly com código-fonte, etc. Enfim, cada comando deve ser usado conforme a necessidade e conveniência. Não adianta querer usar tudo e entender tudo de uma vez. Os comandos acima já são um ótimo começo para uma depuração poderosa o suficiente para pegar alguns bugs.

[conceitos básicos de programação]: /guia-basico-para-programadores-de-primeiro-int-main
