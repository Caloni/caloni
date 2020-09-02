---
date: "2018-02-20"
tags: [ "code", "draft",  ]
title: "Variáveis static local Nunca São Inicializadas Se Você Não Chama Sua Função"
---
Uma dúvida muito comum dos programadores iniciantes em C/C++ diz respeito às variáveis static que são declaradas dentro de um escopo, como uma função. Sabemos que se ela fosse declarada global, fora de qualquer escopo, ela seria inicializada antes do main ser chamado, como diz este trecho de alguém que pesquisou a respeito:

> "C++ Primer says. Each local static variable is initialized before the first time execution passes through the object's definition. Local statics are not destroyed when a function ends; they are destroyed when program terminates." - Someone that google it for but did not get it

Mas no caso de variáveis static declaradas dentro de uma função isso não acontece, e ela pode ser inicializada a qualquer momento. Basta alguém chamar a função onde ela foi definida.




Note que mesmo trocando static int para static const int a mesma coisa acontece. Apenas conseguimos forçar a inicialização antes do main quando há alguma variável global (static ou não) que chame a função.



O problema disso é que é possível que duas threads chamem func() "ao mesmo tempo", gerando uma dupla inicialização caso a implementação da libc não seja thread-safe. E a menos que o padrão especifique que essa inicialização deva ser thread safe, melhor fazer as coisas direito.

Mas, a título de curiosidade, é bom saber que o Visual Studio 2017 essa parte da libc já possui um mecanismo de proteção, como o sugestivo nome tlsindex já indica:



