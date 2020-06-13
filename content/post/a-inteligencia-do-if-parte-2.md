---
categories: [ "code" ]
date: "2007-06-29"
tags: [ "draft",  ]
title: "A inteligência do if - parte 2"
---
Vimos na primeira parte desse artigo como o if revolucionou o mundo da computação trazendo um salto que depende de condições anteriores e, portanto, depende do estado do programa. A ele chamamos de salto condicional. Agora veremos como implementar uma condição baseando-se no fato de que o computador pode apenas realizar operações matemáticas.

Uma condição, item necessário para o funcionamento do salto condicional, nada mais é do que um cálculo matemático e o seu resultado, sendo o salto dependente desse resultado. Geralmente o resultado usado é uma flag definida pela arquitetura como o armazenador de resultado para cálculo matemático. Na plataforma 8086, por exemplo, os cálculos matemáticos de comparação definem uma flag chamada de Zero Flag (ZF), que é modificada ao ser realizado um cálculo:

    ascii art:

    +------------+
    | A Register |----+
    +------------+    |    
                      |----
    +------------+    |   |
    | B Register |----+   |
    +------------+        |
                          |
         |----------------|
         |
    +---------+    +--------+  No    
    | Compare |----| Equal? |----+   
    +---------+    +---+----+    |   
                       |         |   
                   Yes |         |   
                  +----+         |   
                  |              |   
              +------+       +------+
              |ZF = 0|       |ZF = 1|
              +------+       +------+

Mas como comparar? Aí é que está a mágica das portas lógicas e operações booleanas. A comparação acima pode ser feita com um XOR, por exemplo, e o resultado pode ser obtido e armazenado se a saída for conectada a um flip-flop (um flip-flop, ou multivibrador biestável, é um circuito de computador capaz de armazenar o valor de 1 bit, o necessário para o nosso salto).

    ascii art:

    A        +---+ +---+ +---+ +---+
    Register | 1 | | 1 | | 0 | | 0 |
             +---+ +---+ +---+ +---+
    B        +---+ +---+ +---+ +---+
    Register | 1 | | 1 | | 0 | | 0 |
             +---+ +---+ +---+ +---+
    XOR      +---+ +---+ +---+ +---+
    Operator | X | | X | | X | | X |
             +---+ +---+ +---+ +---+
             +---+ +---+ +---+ +---+
    Result   | 0 | | 0 | | 0 | | 0 |
             +-+-+ +-+-+ +-+-+ +-+-+
               |     |     |     |  
             +-+-----+-----+-----+-+
             |       OR Door       |
             +---+-----------------+
                       | 1
                 +----------+ 
                 | NOT Door |
                 +----------+       
                       | 0
                 +-----------+
                 | Flip-flop |
                 +-----------+
                      | 0
                    +----+
                    | ZF |
                    +----+

O flip-flop serve para que o valor do ZF permaneça após a instrução XOR entre os registradores que serão comparados. Eis como funciona: é feito um XOR em cada um dos bits dos valores comparados, fazendo com que qualquer bit diferente tenha uma saída 1. Se todos os bits dos valores comparados forem iguais a zero, significa que os valores são idênticos. Para agrupar todas essas saídas é usada uma porta lógica OR, fazendo com que um único bit diferente de zero (ou mais) reflita na saída. A saída da porta OR, por sua vez, é invertida através da porta NOT colocada antes do flip-flop. Ou seja, se os valores forem idênticos (saída zero da porta OR) a saída final será 1, do contrário será zero.

No final das contas, esse valor será armazenado na flag ZF. Se houver alguma diferença entre os valores, como foi o caso no exemplo acima, o valor final será o um invertido, ou seja, zero. Esse valor armazenado pode ser usado nas próximas instruções para realizar o salto, que dependerá do que estiver nessa flag.

Dessa forma temos o nosso resultado realizado automaticamente através de um cálculo matemático. Agora, para executar o salto condicional, precisamos de um array de dois elementos, cada elemento com um endereço de memória. Podemos definir o primeiro elemento (índice zero) como o armazenador do salto se a condição for falsa, o que quer dizer que seu endereço vai ser o da próxima instrução seqüencial.

    ascii art:

                       +-----------+
                       |    Z F    |
                   +-->|  0     1  |
                   |   | 002 | 004 |
                   |   +--+-----+--+
    | 001 cond. jump      |     |
    | 002 code <----------+     |
    | 003 ...                   |
    | 004 code <----------------+
    | 005 ...         

Já o segundo elemento irá conter o endereço do salto não-seqüencial, que será feito se a condição for verdadeira.

Dessa forma, para executar o salto baseado em um resultado de 0 ou 1 (o Zero Flag), só temos que alterar o endereço da próxima instrução para o valor do nosso array na posição resultado (0 para falso, 1 para verdadeiro). Note que se o resultado for falso o valor da próxima instrução não muda.

    ascii art:

          +--------------------------+
          | Jump if A = B            |
          | {                        |
      |-->+     XOR A, B (change ZF) |
      |   |     Next instruction =   |
      |   |         Result[ZF];      |
      |   | }                        |
      |   +--------+-----+-----------+
      |            |     |  
      |          +-+-+ +-+-+
      |          |002| |004|
      |          +-+-+ +-+-+
      |            |     |         
      |            |     |---------|
      |            |               |
      |            |------------|  |
      |                         |  |
      |----------------------|  |  |   
                             |  |  |   
    | 001 conditional jump --+  |  |   
    | 002 code <----------------+  |
    | 003 ...                      |
    | 004 code <-------------------+
    | 005 ...              

Lembre-se que essa é apenas uma demonstração de como pode funcionar um salto condicional através de cálculos matemáticos. De maneira alguma estou afirmando que é feito dessa forma. Aliás, existem inúmeras formas de realizar esse salto. Uma segunda solução seria adicionar a defasagem (offset) entre o endereço da próxima instrução e o endereço do salto. Nesse caso podemos:

1. Usar o ZF para multiplicar a defasagem e somar ao valor de Próxima Instrução.

    Next instruction += ZF * offset;

2. Continuar usando a técnica do array, sendo o primeiro elemento (`false`) igual a 0.

    Next instruction = Next instruction + Result [ZF];

Acredito ser a solução da multiplicação a pior das três citadas, e a solução da defasagem a mais intuitiva por analogia (se você já programou em assembly). Meu objetivo foi apenas ilustrar que, dado um problema, pode haver várias soluções. Talvez mais para a frente veremos como é implementado um if em assembly, subindo mais um nível de abstração.
