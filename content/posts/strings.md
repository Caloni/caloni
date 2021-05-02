---
date: "2009-07-07"
categories: [ "code", "draft",  ]
title: "Strings"
---
Como já vimos centenas e centenas de vezes, memória é apenas memória até que alguém diga que isso vale alguma coisa. Em seu estado latente é o que chamamos formalmente de dados. E dados são bytes armazenados na memória.

No entanto, quando esses dados viram algo de útil em um determinado contexto, não necessariamente alterando-se seu conteúdo na memória, passamos a lidar com informação. Ou seja, é um dado com significado. E informação é a interpretação desses mesmos dados.

A conclusão óbvia para isso, falando de strings, é: uma série de bytes enfileirados na memória pode ser uma string.

Para tanto precisamos apenas de dados (os bytes enfileirados) e significado (uma tabela de símbolos que traduza esses bytes para caracteres e a definição de como a string se organiza).

Por exemplo, uma série de bytes diferentes de zero com valores que representam índices de uma tabela de tradução de caracteres e que termina sua sequência em um byte com o valor zero nele é considerada uma string C, ou string terminada em nulo.

Já uma mesma sequência de bytes no mesmo molde só que sem o byte final com o valor zero, mas com um byte inicial que tem como valor não um índice de caractere, mas o número de bytes subsequentes, isso é uma string Pascal, ou uma string com contador de tamanho.

Agora note por que tanto uma string vazia em Pascal e em C possuem os mesmos dados, mas informação diferente.

Outras strings que não necessariamente possuem terminador nulo: std::string, UNICODESTRING.aspx), strings no kernel.
