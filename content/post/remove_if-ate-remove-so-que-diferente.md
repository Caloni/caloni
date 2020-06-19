---
categories: [ "code" ]
date: "2014-01-21"
tags: [ "draft",  ]
title: "removeif até remove, só que diferente"
---
A surpresa de hoje foi descobrir (vejam só) que o removeif, como todo algoritmo da STL, deve ser olhado de perto antes de usado. Nesse caso em específico porque, apesar do nome, a função NÃO remove elementos, mas os sobrescreve.

Imagine uma função que usa removeif para remover todas as idades de potenciais lolitas:


Ou até sua contraparte usando um array C:


Um uso trivial pode não cuspir um resultado trivial, ou seja, os elementos não serão removidos como se espera:


Isso ocorre porque o comportamento do removeif é copiar todos os elementos que retornem false (não remova) e pular elementos que retornem true (remova). No entanto, o tamanho do contêiner, e consequentemente seu ponteiro end(), permanecem o mesmo.

De acordo com o saite cplusplus.com, o algoritmo STL é previsível, simples, e por isso mesmo sujeito a otimizações do compilador:


Para obtermos qual seria o "novo end()", precisamos obter esse valor do retorno de removeif. Com base nisso, podemos alterar o tamanho do contêiner ajustado:


Esse C++... intuitivo como nunca!
