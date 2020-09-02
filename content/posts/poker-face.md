---
date: "2014-05-06"
tags: [ "code", "draft",  ]
title: "Poker Face"
---
O segundo round da segunda fase do Code Jam passou nesse sábado. Disléxico que sou, consegui fazer apenas 8 pontos ¿ como todo mundo ¿ no teste small do problema B, que envolvia apenas dois loops aninhados (a versão large fica para outro post). Na verdade, estou aqui para expressar minha gratidão ao campeonato por ter aprendido mais uma bela lição vendo o código do primeiro colocado do primeiro round, vulgo Kaizero, um coreano que deu uma solução simples, rápida e prática para um problema de probabilidade tão error-prone que até os juízes do Google deram uma lambuja de alguns testes errados (sem contar que houve apenas a categoria small), e me fez pensar em quantas vezes pensamos em demasiado tentando encontrar a solução perfeita para algo que simplesmente... não precisa.

Basta um hack e commit.

O problema reza que existem dois algoritmos para embaralhar uma sequência numérica (de 0 a N): o bom e o ruim. Ambos traçam um loop do iníco ao fim pegando aleatoriamente um elemento da lista e trocando de lugar com o elemento que está sendo varrido no momento.

A diferença entre o bom e o ruim é que o bom pega aleatoriamente apenas os elementos DEPOIS do elemento que está sendo varrido, enquanto o algoritmo ruim pega qualquer um dos elementos SEMPRE. Isso aparentemente e intuitivamente não parece interferir na aleatoriedade do embaralhamento, mas se levarmos ao extremo de embaralhar repetidas vezes somando a lista resultante percebemos uma tendência gritante do algoritmo ruim em manter o ordenamento inicial, ou pelo menos na média sempre tender para números menores no início e números maiores no fim, como pode ser visto nesse teste que fiz, gerado pelo Excel:

O que eu tentei fazer durante meu fim-de-semana retrasado e o feriado foi encontrar um detector de aleatoriedade (aliás, encontrei um bem interessante chamado ent), tanto "na mão" quanto pesquisando. O que eu não imaginava foi que o teste que eu tinha feito no início usando uma simples planilha Excel era a solução óbvia (naquelas de é óbvio só depois que você vê). E foi essa a solução adotada por Kaizero.


O que ele basicamente faz é acumular os resultados de três milhões de embaralhamentos feitos pelo algoritmo ruim e inferir através dos resultados que metade é bom e metade é ruim. O ruim fica do lado desbalanceado da sequência.

Tão óbvio, tão simples, tão elegante.

