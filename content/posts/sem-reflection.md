---
categories: [ "code" ]
date: "2011-05-18"
tags: [ "draft",  ]
title: "Sem reflection"
---
Em C++ não temos (ainda) a possibilidade de listarmos, por exemplo, a lista de métodos de um determinado tipo, a fim de chamá-lo pelo nome em tempo de execução. Algo assim:


OK, foi apenas um exemplo tosco de como seria um reflection em C++.

Porém, existem algumas maneiras de contornar esse problema. A solução, é claro, depende de qual problema você está tentando resolver.

Vamos supor, por exemplo, que você queira cadastrar funções para serem chamadas de maneira uniforme pelo prompt de comando. Vamos chamar nossa classe tratadora de CommandPrompt.


Internamente, para armazenar as funções de acordo com o nome dado, basta criarmos um mapeamento entre esses dois tipos e fazemos a amarração necessária para o método principal de parseamento:


Essa solução não é exatamente um reflection, mas apenas parte do que o verdadeiro reflection possibilita. Existem outras funcionalidades, como traits, que a STL já consegue se virar razoavelmente bem, por exemplo.
