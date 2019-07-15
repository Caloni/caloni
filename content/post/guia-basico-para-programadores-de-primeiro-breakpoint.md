---
date: "2007-10-22"
title: Guia básico para programadores de primeiro breakpoint
categories: [ "code" ]
---
Aproveitando um dos últimos artigos que fala sobre [conceitos básicos de programação](http://www.caloni.com.br/guia-basico-para-programadores-de-primeiro-int-main), lembro que, tão importante quanto, é possuir habilidades básicas de depuração, uma arte por muitos programadores ignorada.

É interessante notar como muitos programadores e instituições de ensino ignoram a utilidade e conveniência das tradicionais e poderosas ferramentas de depuração passo-a-passo. O motivo pode ser puro desdém ou ignorância (no sentido de desconhecimento). Se for pelo segundo, aí vão algumas dicas para dar uma passada geral no seu programa e, quem sabe, encontrar um ou outro _bug_ pelo caminho.

#### _Run_/_Debug_/Etc

É o comando primário. Simplesmente inicia uma nova execução de seu programa. Geralmente você deve utilizar esse comando quando já tiver definido seus _breakpoints_ (mais abaixo). Do contrário o programa vai iniciar, executar e sair, sem sequer você notar.

[![Debug Panel](http://i.imgur.com/f9EJ4F4.gif)](/images/debug-panel.gif)
Na ordem: _Start/Continue, Break, Stop, Restart, Show Next Statement, Step Into, Over _e_ Out_.

#### _Step Over_

[![Step Over](http://i.imgur.com/oezj3LH.gif)](/images/step-over.gif)

Esse comando avança uma linha de código-fonte, parando na seguinte, de uma maneira iterativa. É a chamada execução passo-a-passo. Com ele você consegue, com a ajuda das janelas de _watch_ e variáveis locais, analisar passo-a-passo a execução do fluxo de seu programa variando de acordo com as condições do sistema.

#### _Step Into_

[![Step Into](http://i.imgur.com/PZuIFOs.gif)](/images/step-into.gif)

Parente bem próximo do _Step Over_, com a importante diferença de entrar dentro das funções que são chamadas em cada linha de execução. Geralmente é usado quando você pretende revisar todo o fluxo de execução porque escreveu código novo ou porque ainda não chegou na situação que pretende simular ou ainda porque usou o _Step Over_ antes e descobriu que existe algum problema na função X que você passou direto.

#### _Step Out_

[![Step Out](http://i.imgur.com/ht6mZV2.gif)](/images/step-out.gif)

É o complemento dos dois comandos acima. Ele vai sair executar todo o resto da função onde você está e parar exatamente uma linha após a chamada dessa função. Em suma: você já viu o que queria ver dentro da função atual e quer continuar a execução um ou mais níveis acima na pilha de chamadas.

#### _Breakpoints_

Você não precisa passar por todo o seu código e todos os seus _loops_/laços de 500 iterações até chegar ao ponto que quer analisar. Existe um comando nativo do sistema que é dos mais úteis para o programador, capaz de parar o fluxo de execução em um ponto específico do código. O depurador torna disponível para você esse comando que pode ser engatilhado em qualquer linha, geralmente em uma quantidade razoável. Para controlar todos os _breakpoints_ definidos existe uma janela com essa lista que indica, entre outras coisas, se estão habilitados ou não, se possuem alguma condição de quebra, quantas vezes devem parar, etc. Costuma existir um ótimo controle sobre _breakpoints_ nos depuradores, pois esse é um comando muito usado em programação (e dos mais antigos).

#### _Watch_

[![Watch](http://i.imgur.com/xq6auvT.gif)](/images/watch.gif)

Praticamente qualquer ferramenta de _debug_ possui um mecanismo para que você consiga ver o que está dentro das variáveis de seu programa. Basicamente temos uma janela de _watch_, ou _inspection_, onde podemos inserir as variáveis que queremos espiar. Em um nível mais sofisticado, temos as janelas de _locals_ e _autos_ (o nome pode variar), onde podemos ver, respectivamente, as variáveis dentro da função e as variáveis mais próximas do ponto onde o código está parado (as que foram usadas na última linha e as que serão usadas na próxima, por exemplo). Claro que cada ambiente te fornece o que melhor ajudar durante a depuração, assim como o Delphi e o C++ Builder possuem o magnífico Object Inspector, uma janela com todas as propriedades de um objeto qualquer do sistema (uma janela, um botão, uma classe, etc).

#### _Call Stack_

[![Call Stack](http://i.imgur.com/UQEgb0r.gif)](/images/call-stack.gif)

Essa é a pilha de chamadas da _thread_ atual. Com ela você consegue ver o nome da função que chamou a função que chamou a função que chamou... até a função inicial (por exemplo, o nosso conhecido main, a primeira função de um programa "normal" em C/C++).

#### _Threads_

No caso de seu programa ser _multithreading_, ou seja, possuir várias linhas de execução, fluxos distintos de código rodando, existirá uma janela onde você pode ver qual a _thread_ atual (a que está sendo depurada e destrinchada nas outras janelas) e quais as outras _threads_. Muitos ambientes permitem que com essa janela seja feito um _switch_ de _threads_, que é a troca da _thread_ atual, o que irá alterar a janela de pilha de chamadas, de variáveis locais, e muito provavelmente a janela do código-fonte atualmente em execução.

#### _Advanced Mode_

Depurar esteve sempre ligado à programação desde os primórdios da humanidade. Por isso hoje em dia os depuradores estão muito evoluídos, geralmente integrados em um ambiente de desenvolvimento (exs: Visual Studio, KDE Develop) e possuem comandos e mais comandos e mais comandos. Existem comandos, por exemplo, para pular fluxo sem executar, definir um _breakpoint_ temporário, visualizar registradores da máquina, visualizar páginas de memória, controle de exceções, misturar _assembly_ com código-fonte, etc. Enfim, cada comando deve ser usado conforme a necessidade e conveniência. Não adianta querer usar tudo e entender tudo de uma vez. Os comandos acima já são um ótimo começo para uma depuração poderosa o suficiente para pegar alguns _bugs_.
