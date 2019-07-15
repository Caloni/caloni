---
date: "2009-07-07"
title: Strings
categories: [ "code" ]
---
Como já vimos [centenas](http://www.caloni.com.br/basico-do-basico-tipos) e [centenas](http://www.caloni.com.br/guia-basico-para-programadores-de-primeiro-int-main) de vezes, memória é apenas memória até que alguém diga que isso vale alguma coisa. Em seu estado latente é o que chamamos formalmente de **dados**. E dados são bytes armazenados na memória.

No entanto, quando esses dados viram algo de útil em um determinado contexto, não necessariamente alterando-se seu conteúdo na memória, passamos a lidar com informação. Ou seja, é um dado com **significado**. E informação é a interpretação desses mesmos dados.

A conclusão óbvia para isso, falando de strings, é: uma série de bytes enfileirados na memória pode ser uma string.

Para tanto precisamos apenas de dados (os bytes enfileirados) e significado (uma tabela de símbolos que traduza esses bytes para caracteres e a definição de como a string se organiza).

Por exemplo, uma série de bytes diferentes de zero com valores que representam índices de uma tabela de tradução de caracteres e que termina sua sequência em um byte com o valor zero nele é considerada uma string C, ou string terminada em nulo.

[![String C](http://i.imgur.com/ZbgWXK7.png)](/images/stringc.png)

Já uma mesma sequência de bytes no mesmo molde só que sem o byte final com o valor zero, mas com um byte inicial que tem como valor não um índice de caractere, mas o número de bytes subsequentes, isso é uma string Pascal, ou uma string com contador de tamanho.

[![String Pascal](http://i.imgur.com/SwcbASJ.png)](/images/stringpascal.png)

Agora note por que tanto uma string vazia em Pascal e em C possuem os mesmos dados, mas informação diferente.

Outras strings que não necessariamente possuem terminador nulo: [std::string](http://www.cplusplus.com/reference/string/string/), [UNICODE_STRING](http://msdn.microsoft.com/en-us/library/aa380518(VS.85).aspx), [strings no kernel](http://www.driverentry.com.br/2009/07/strings-no-kernel.html).
