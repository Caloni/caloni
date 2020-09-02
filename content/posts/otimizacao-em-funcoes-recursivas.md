---
date: "2008-01-18"
tags: [ "code", "draft",  ]
title: "Otimização em funções recursivas"
---
O livro que estou lendo fala sobre algoritmos em C. Os primeiros capítulos são praticamente uma revisão para quem já programou em C, pois tratam de coisas que programadores com mais de cinco anos de casa devem ter na memória cachê (listas, pilhas, recursão, etc). Porém, tive uma agradável surpresa de achar um truque muito sabido que não conhecia, chamado de tail recursion. Fiz questão de testar nos dois compiladores mais conhecidos e eis o resultado.

Imagine uma função recursiva que calcula o fatorial de um número. Apenas para lembrar, o fatorial de um número n é igual a n * n-1 * n-2 * n-3 até o número 1. Existem implementações iterativas (com um laço for, por exeplo) e recursivas, que no caso chamam a mesma função n vezes.


Para ver o overhead de uma função dessas, compilamos com a opção de debug e depuramos no CDB.




Ou seja, conforme chamamos a função recursivamente, a pilha tende a crescer. Agora imagine todo o overhead da execução, que precisa, a cada chamada, gerar um stack frame.

A mesma coisa podemos notar se compilarmos o mesmo fonte no GCC e depurarmos pelo GDB. Aliás, a primeira participação especial do GDB nesse blogue =)


Isso acontece porque o compilador é obrigado a montar um novo stack frame para cada chamada da mesma função, já que os valores locais precisam manter-se intactos até o retorno recursivo da função. Porém, existe uma otimização chamada de tail recursion, que ocorre se, e somente se (de acordo com meu livro):

  * A chamada recursiva é a última instrução que será executada no corpo da função.

  * O valor de retorno da chamada não é parte de uma expressão.

Note que ser a última instrução não implica em ser a última linha da função, o importante é que seja a última linha executada. No nosso exemplo, isso já é fato, só que usamos o retorno em uma expressão.


Por isso é necessário desenvolver uma segunda versão do código, que utiliza dois parâmetros para que aconteça a situação de tail recursion.


Nessa segunda versão, a chamada da função recursiva não mais é parte de uma expressão, e continua sendo a última instrução executada. Agora só temos que compilar com a opção de otimização certa em ambos os compiladores e testar.

Para o Visual Studio, podemos usar a flag /Og (otimização global).




Como podemos ver, após n chamadas, a pilha continua apenas com uma chamada a factorial.

Para o GCC, a opção é mais explítica, e funciona da mesma forma.



Voilà!

PS: De brinde uma versão que permite passar o número via linha de comando para facilitar os testes (e você vai reparar que há um problema em calcular o fatorial de 1000: ele é estupidamente grande! Resolver isso fica como exercício =).


