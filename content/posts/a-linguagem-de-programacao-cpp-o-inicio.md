---
date: "2016-11-29"
tags: [ "code", "draft",  ]
title: "A Linguagem de Programação C++: O Início"
---
O livro-base sobre a linguagem C++ e como programar nela tem o nome pouco criativo "The C++ Programming Language", e é de Bjarne Stroustrup, o criador da linguagem. Ele começou a desenhar a linguagem em 1979, quando ainda a chamada de "C com Classes". Havia um problema a ser resolvido na época em que Stroustrup estava fazendo sua tese de doutorado. Havia linguagens muito boas em abstração como Simula -- como o novo conceito de Orientação a Objetos -- que carecia do mais importante na época: velocidade (só na época?). Já linguagens mais antigas como BCPL eram bem rápidas, mas eram tão simples que pareciam mais um Assembly glorificado. Havia, portanto, a necessidade de preencher a área de computação com alguma coisa bem no meio.

Stroustrup não fez tudo do zero, nem fez tudo de uma vez. A primeira necessidade era apenas criar uma abstração já existente na linguagem C, mas que ainda não havia sido integrada à sintaxe: o contexto de uma estrutura, que se assemelha a uma proto-classe, ou para alguns já é até uma classe, pois possui membros e métodos:


A grande sacada é que no meio de toda essa sintaxe de chamada de método havia a passagem de um parâmetro escondido, o this, que se referia à uma instância específica da classe: um objeto.


Isso equivaleria a uma struct em C com funções que recebessem um this adaptado:


Esse tipo de abstração nem é tão complicada assim. O ojetivo eram vários: conseguir proteger os membros de acesso indevido, abstrair o comportamento de um objeto. Com o tempo Stroustrup foi realmente criando algo de novo e muito mais difícil de se manter em C.

Algo para um próximo post =)
