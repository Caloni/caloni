---
date: "2007-06-18"
title: "A inteligência do if - parte 1"
categories: [ "code" ]
---
No nível mais baixo, podemos dizer que as instruções de um computador se baseiam simplesmente em cálculos matemáticos e manipulação de memória. E entre os tipos de manipulação existe aquela que muda o endereço da próxima instrução que será executada. A essa manipulação damos o nome de **salto**.

O salto simples e direto permite a organização do código em subrotinas e assim seu reaproveitamento, o que economiza memória, mas computacionalmente é inútil, já que pode ser implementado simplesmente pela repetição das subrotinas. O que eu quero dizer é que, do ponto de vista da execução, **a mesma seqüência de instruções será executada**.

![Chamada de subrotina](http://i.imgur.com/sLro0Lb.gif)]

A grande sacada computacional, motivo pelo qual hoje os computadores hoje são tão úteis para os seres humanos, é a invenção de um conceito chamado **salto condicional**. Ou seja, **não é um salto certo**, mas um salto que será executado caso a condição sob a qual ele está subordinado for verdadeira.

[![Chamada de subrotina condicionalmente](http://i.imgur.com/FPzteM3.gif)](/images/salto-condicional.gif)

Os saltos condicionais, vulgarmente conhecidos como _ifs_, permitiram às linguagens de programação possuírem construções de execução mais sofisticadas: laços, iterações e seleção de caso. Claro que no fundo elas não passam de um conjunto formado por saltos condicionais e incondicionais.

[![Construções de programação](http://i.imgur.com/m6rIvJP.png)](/images/programming-constructions.png)

Em um [próximo artigo](http://www.caloni.com.br/a-inteligencia-do-if-parte-2) veremos como o salto condicional pode ser implementado apenas com operações matemáticas (afinal, é só isso que temos).
