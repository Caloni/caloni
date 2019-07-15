---
date: "2007-06-29"
title: A inteligência do if - parte 2
categories: [ "code" ]
---
Vimos na [primeira parte](http://www.caloni.com.br/a-inteligencia-do-if-parte-1) desse artigo como o _if_ revolucionou o mundo da computação trazendo um salto que **depende de condições anteriores** e, portanto, depende do estado do programa. A ele chamamos de **salto condicional**. Agora veremos como implementar uma condição baseando-se no fato de que o computador pode apenas realizar operações matemáticas.

Uma **condição**, item necessário para o funcionamento do salto condicional, nada mais é do que um cálculo matemático e o seu resultado, sendo o salto **dependente desse resultado**. Geralmente o resultado usado é uma _flag_ definida pela arquitetura como o armazenador de resultado para cálculo matemático. Na plataforma 8086, por exemplo, os cálculos matemáticos de comparação definem uma _flag_ chamada de **Zero Flag (ZF)**, que é modificada ao ser realizado um cálculo:

[![Zero Flag (ZF)](http://i.imgur.com/rSK6hdc.gif)](/images/zero-flag.gif)

Mas como comparar? Aí é que está a mágica das portas lógicas e operações booleanas. A comparação acima pode ser feita com um XOR, por exemplo, e o resultado pode ser obtido e armazenado se a saída for conectada a um **flip-flop** (um _flip-flop_, ou **multivibrador biestável**, é um circuito de computador capaz de armazenar o valor de 1 bit, o necessário para o nosso salto).

[![Xor and Zero Flag](http://i.imgur.com/dqOLmWR.gif)](/images/xor-flip-flop.gif)

O _flip-flop_ está aí apenas para ilustrar que **o valor do ZF irá permanecer após a instrução XOR**. Eis como funciona: é feito um XOR em cada um dos bits dos valores comparados, fazendo com que qualquer bit diferente tenha uma saída 1. Se todos os bits dos valores comparados forem iguais a zero, significa que os valores são **idênticos**. Para agrupar todas essas saídas é usada uma porta lógica OR, fazendo com que um único bit diferente de zero (ou mais) reflita na saída. A saída da porta OR, por sua vez, é invertida através da porta NOT colocada antes do _flip-flop_. Ou seja, se os valores forem idênticos (saída zero da porta OR) a saída final será 1, do contrário será zero.

No final das contas, esse valor será armazenado na _flag_ ZF. Se houver alguma diferença entre os valores, como foi o caso no exemplo acima, o valor final será o um invertido, ou seja, zero. Esse valor armazenado pode ser usado nas próximas instruções para realizar o salto, que dependerá do que estiver nessa _flag_.

Dessa forma temos o nosso resultado realizado automaticamente através de um cálculo matemático. Agora, para executar o salto condicional, precisamos de um _array_ de dois elementos, cada elemento com um endereço de memória. Podemos definir o **primeiro elemento** (índice zero) como o armazenador do salto se a condição for **falsa**, o que quer dizer que seu endereço vai ser o da **próxima instrução seqüencial**.

[![Código com salto condicional](http://i.imgur.com/ZgNRuRp.gif)](/images/codigo-salto-condicional.gif)

Já o segundo elemento irá conter o endereço do **salto não-seqüencial**, que será feito se a condição for **verdadeira**.

Dessa forma, para executar o salto baseado em um resultado de 0 ou 1 (o Zero Flag), só temos que alterar o endereço da próxima instrução para o valor do nosso_ array_ na posição resultado (**0 para falso, 1 para verdadeiro**). Note que se o resultado for falso o valor da próxima instrução **não muda**.

[![Código com salto condicional](http://i.imgur.com/vtMjqoh.gif)](/images/codigo-salto-condicional2.gif)

**É sempre assim que funciona?**

Lembre-se que essa é apenas uma demonstração de **como pode funcionar um salto condicional através de cálculos matemáticos**. De maneira alguma estou afirmando que é feito dessa forma. Aliás, existem inúmeras formas de realizar esse salto. Uma segunda solução seria adicionar a **defasagem** (_offset) _entre o endereço da próxima instrução e o endereço do salto. Nesse caso podemos:

1. Usar o ZF para multiplicar a defasagem e somar ao valor de Próxima Instrução.

**Próxima Instrução += ZF * offset;**

2. Continuar usando a técnica do _array_, sendo o primeiro elemento (_false_) igual a 0.

**Próxima Instrução = Próxima Instrução + Resultado [ZF];**

Acredito ser a solução da multiplicação a pior das três citadas, e a solução da defasagem a mais intuitiva por analogia (se você já programou em _assembly_). Meu objetivo foi apenas ilustrar que, dado um problema, **pode haver várias soluções**. Talvez mais para a frente veremos como é implementado um _if_ em _assembly_, subindo mais um nível de abstração.
