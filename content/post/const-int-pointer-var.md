---
categories: [ "code" ]
date: "2019-04-29"
tags: [ "draft",  ]
title: "Const Int Pointer Var"
---
A melhor forma de declarar variáveis ponteiros (constante ou não, mas segue o exemplo) é const int pointer var. Explicação:

Quem diz o asterisco fazer parte do tipo e não da variável tem razão. Pensando dessa forma ele tem que ficar próximo do tipo.

    const int* var

Porém, outra forma de interpretar a variável é que ela equivale a um inteiro quando usado com asterisco, o que também é verdade. Ou seja, int pointer var significa que pointer var equivale a um int (constante ou não, mas preciso dessa variável não-const para o exemplo). É por isso que pointer var igual a dez possui o mesmo valor de atribuição do que int var seguido de var igual a dez, ou seja, pointer var é sinônimo do l-value var (se var fosse um inteiro e não um ponteiro).

Além disso, outro argumento pró-proximidade da variável é que declarações de múltiplas variáveis na mesma linha precisam de múltiplos asteriscos: const int pointer var1, pointer var2, pointer var3.

Portanto, como ambos os lados estão certos, separar o asterisco de ambos não dá prioridade a nenhuma forma que o programador poderá interpretar essa decisão, seja como parte do tipo ou da variável. Cada programador com seu próprio estilo irá enxergar em const int pointer  var a proximidade com int ou com var de acordo com seu próprio bias (e estará certo em sua análise).

    qualifier type * name;
