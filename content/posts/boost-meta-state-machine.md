---
date: "2018-05-21"
tags: [ "code", "draft",  ]
title: "Boost Meta State Machine"
---
O Boost Meta State Machine (MSM for short) é uma das duas bibliotecas mais famosinhas de state machine do Boost. Ela é uma versão estática que permite incluir chamadas para as entradas e saídas de um estado baseado em eventos. A sua principal vantagem é poder visualizar toda a máquina de estado em um só lugar, e sua principal desvantagem é pertecer ao Boost, o que quer dizer que você vai precisar fazer seu terceiro doutorado e ler uma documentação imensa sobre UML antes de conseguir produzir alguma coisa. Ou ler este artigo de 10 minutos tops.


A parte bonitinha de se ver é os eventos e estados completamente ordenados:


Claro que a indentação ajuda. Para cada entrada e saída de um estado é possível utilizar os métodos onentry e onexit de cada struct que define um estado, seja este método um template totalmente genérico ou especificado por evento (e cada evento também é um struct, com direito a dados específicos).


Quando é criada uma nova máquina de estados o estado inicial é chamado pelo evento onentry genérico. Como sabemos qual é o estado inicial? Isso é definido pelo typedef initialstate dentro da classe da máquina de estado (que deve herdar de statemachinedef no estilo WTL, com sobrecarga estática):


O estado final também é definido, mas por herança. O estado final, que também é uma struct, deve herdar de terminatestate:


A partir daí o método processevent serve para enviar eventos à máquina de estado que irá alterar seu estado dependendo do fluxo criado no nome transitiontable dentro da máquina de estado (a tabelinha que vimos acima). A partir daí tudo é possível; a máquina de estado está à solta:


Mas nesse exemplo didático está comportada em uma função apenas. Claro que cada método recebe a própria máquina de estado para ter a chance de alterá-la, ou guardá-la para uso futuro. Ela é recebida como parâmetro assim como o evento. E o evento, por ser uma struct também, pode conter outros dados relevantes para a transição.
