---
categories: [ "code" ]
date: "2007-06-18"
tags: [ "draft",  ]
title: "A inteligência do if - parte 1"
---
No nível mais baixo, podemos dizer que as instruções de um computador se baseiam simplesmente em cálculos matemáticos e manipulação de memória. E entre os tipos de manipulação existe aquela que muda o endereço da próxima instrução que será executada. A essa manipulação damos o nome de salto.

O salto simples e direto permite a organização do código em subrotinas e assim seu reaproveitamento, o que economiza memória, mas computacionalmente é inútil, já que pode ser implementado simplesmente pela repetição das subrotinas. O que eu quero dizer é que, do ponto de vista da execução, a mesma seqüência de instruções será executada. Pense no fluxo de execução de uma rotina que chama várias vezes a mesma subrotina.



Ela é, na prática, equivalente à uma rotina que contém várias cópias da subrotina na memória, uma seguida da outra.



A grande sacada computacional, motivo pelo qual hoje os computadores hoje são tão úteis para os seres humanos, é a invenção de um conceito chamado salto condicional. Ou seja, não é um salto certo, mas um salto que será executado caso a condição sob a qual ele está subordinado for verdadeira.


Os saltos condicionais, vulgarmente conhecidos como if's, permitiram às linguagens de programação possuírem construções de execução mais sofisticadas: laços, iterações e seleção de caso. Claro que no fundo elas não passam de um conjunto formado por saltos condicionais e incondicionais.

O while e seu bloco não passa de um salto no final do bloco para o começo de um if.


O for não passa de um contador que é incrementado a cada passada por esse mesmo if do while. Quer dizer, do bloco de código que se segue.

E um switch-case nada mais é que vários ifs seguidos, unidos por um else (que torna a comparação exclusiva).



Em um próximo artigo veremos como o salto condicional pode ser implementado apenas com operações matemáticas (afinal, é só isso que temos).
