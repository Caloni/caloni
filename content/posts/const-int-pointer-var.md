---
date: 2019-04-29T20:56:48-03:00
title: "Const Int Pointer Var"
tags: [ "draft", "code" ]
desc: "Uma explicação de por que não aproximar o asterisco nem to tipo nem da variável na declaração de ponteiros é uma forma neutra de resolver essa questão de estilo."
---
A melhor forma de declarar variáveis ponteiros (constante ou não, mas segue o exemplo) é `const int * var`. Explicação:

Quem diz o asterisco fazer parte do tipo e não da variável tem razão. Pensando dessa forma ele tem que ficar próximo do tipo.

```
const int* var
```

Porém, outra forma de interpretar a variável é que ela equivale a um inteiro quando usado com asterisco, o que também é verdade. Ou seja, `int *var` significa que `*var` equivale a um `int` (constante ou não, mas preciso dessa variável não-const para o exemplo). É por isso que `*var = 10` possui o mesmo valor de atribuição do que `int var; var = 10`, ou seja, `*var` é sinônimo do l-value `var` (se var fosse um inteiro e não um ponteiro).

Além disso, outro argumento pró-proximidade da variável é que declarações de múltiplas variáveis na mesma linha precisam de múltiplos asteriscos: `const int *var1, *var2, *var3`.

Portanto, como ambos os lados estão certos, separar o asterisco de ambos não dá prioridade a nenhuma forma que o programador poderá interpretar essa decisão, seja como parte do tipo ou da variável. Cada programador com seu próprio estilo irá enxergar em `const int * var` a proximidade com `int` ou com `var` de acordo com seu próprio bias (e estará certo em sua análise).

Ergo:

```
qualifier type * name;
```
