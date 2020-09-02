---
date: "2016-04-16"
tags: [ "code", "draft", "puzzle" ]
title: "Rank and File"
---
Passou o Round 1A do Code Jam, e para variar, fui muito mal, só respondendo a primeira questão. A segunda me fez ficar pensando um tempo desproporcional sobre como encaixar as diferentes linhas e colunas para achar a linha restante.

Basicamente, o problema pede que, dado um quadrado de tamanho N, e 2*N-1 linhas fornecidas (que podem ser linhas ou colunas), imprimir a Nésima linha. A regra das linhas é que ela possui números crescentes.

Bom, não consegui chegar numa solução para o problema errado (encaixar as linhas), mas fui, como sempre, dar uma espiada nas respostas dos competidores, em especial a do primeiro colocado. O grande barato de competições como essa é aprender com a inteligência e genialidade dos outros. Para mim, esse é um exemplo de genialidade:


Obs.: O código está higienizado, pois esse pessoal usa bastante macros, etc.

A solução basicamente decide isolar duas questões: achar os números que faltam nas sequência e imprimi-los na ordem. Para o primeiro, varre todas as sequências sinalizando qual deles tem a quantidade ímpar (ou seja, não está representado em todas as linhas e colunas, pois do contrário seria par). Depois ele resolve a segunda questão simplesmente imprimindo os números ímpares encontrados, já na ordem (no array de valores possíveis).

Simples, rápido, eficiente. E correto.

É esse tipo de coisa que faz valer a pena uma competição dessas.
