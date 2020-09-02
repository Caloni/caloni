---
date: "2018-10-01"
tags: [ "code", "draft",  ]
title: "Boost.Bind e os Erros Escrotos"
---
Estou voltando a programar algumas coisas no boost. Algo que eu perdi ao me isolar do movimento de modernização do C++ foi a capacidade brilhante da biblioteca boost em encapsular e abstrair conceitos de engenharia de software de maneira portável e mantendo a filosofia por trás da STL, que ainda é a melhor maneira de trabalhar algoritmos já criada em qualquer linguagem de programação séria.

Isso não quer dizer que a linguagem C++ está indo para um bom caminho. Muito pelo contrário. Uma miríade de questões semânticas dividem opiniões e nunca resolvem de fato problemas do mundo real. Verdadeiros arcabouços masturbatórios, o comitê da linguagem se debate em vão quando tenta buscar maneiras de tornar uma linguagem arcaica em um exemplo de expressividade.

Isso às vezes não importa muito para o dia-a-dia, mas outras vezes importa. Veja o caso da biblioteca Boost.Bind, uma das mais antigas a entrar para o projeto. Sua função é simples: expandir o conceito do std::bind para quantos argumentos for necessário. Isso foi criado na época com a ajuda de inúmeros overloads da função (em modo template), mas hoje é possível fazer com variadic templates. Seu uso é simples, intuitivo, direto, e resolve muitos problemas de encaixe de código:


No entanto, o que era para ser um uso simples e direto de uma feature bem-vinda ao cinto de utilidades do programador C++ se transforma em um pesadelo quando as coisas não se encaixam tão bem:


Vou plotar aqui todas as mensagens de erro para sentir o drama:


Este é o erro encontrado usando o último Visual Studio (2017 15.9.0 Preview 2.0) e o Boost 1.68.0. A primeira linha deveria significar alguma coisa (que é para onde todo programador C++ deve olhar):


Mas não. Se olharmos para o código-fonte onde ocorreu o problema, a caixa de encaixe perfeito se quebra:



O que isso quer dizer? O que aconteceu? Onde que eu errei?

Claro que ao final da longa listagem de erros (que se torna ainda mais longa, dependendo de quantos argumentos sua função tem) há alguma luz no fim do túnel:


Mas claro que essa luz pode estar ofuscada quando os tipos dos argumentos são templates de templates de templates... enfim. Deu pra entender onde o caos consegue chegar quando se trata de harmonizar uma biblioteca perfeita com uma linguagem em constante construção.
