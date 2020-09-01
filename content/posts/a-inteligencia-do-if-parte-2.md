---
categories: [ "code" ]
date: "2007-06-29"
tags: [ "draft",  ]
title: "A inteligência do if - parte 2"
---
Vimos na primeira parte desse artigo, "A inteligência do if - parte 1", como o if revolucionou o mundo da computação ao trazer um salto que depende de condições anteriores e, portanto, depende do estado do programa. A ele chamamos de salto condicional. Também vimos como o resto das construções lógicas de uma linguagem são apenas derivações montadas a partir de saltos condicionais e incondicionais. Neste artigo veremos como implementar um saldo condicional baseando-se no fato de que o computador pode apenas realizar operações matemáticas. Afinal de contas, um computador não "pensa".

Uma condição, item necessário para o funcionamento do salto condicional, nada mais é do que o conjunto de um cálculo matemático e o seu resultado, sendo o salto dependente desse resultado. Geralmente o resultado usado é uma flag definida pela arquitetura como o armazenador de resultado para comparações de igualdade. Na plataforma 8086, por exemplo, as instruções que comparam memória definem uma flag chamada de Zero Flag (ZF) que é modificada sempre logo após de executada uma instrução dessa categoria.

É comum nas arquitetura o resultado de uma comparação ser igual a zero se os elementos são iguais e diferente de zero se são diferentes. O resultado, então, denota a diferença entre as memórias comparadas, e se não há diferença o resultado é zero.

    set memA, 1
    set memB, 1
    cmp memA, memB # ZF=0

    set memA, 1
    set memB, 0
    cmp memA, memB # ZF=1

Mas como de fato comparar? Aí é que reside a mágica das portas lógicas e operações booleanas. A comparação acima pode ser feita com uma porta lógica XOR, o OU-eXclusivo, por exemplo, e o resultado pode ser obtido e armazenado se a saída for conectada a um flip-flop (um flip-flop, ou multivibrador biestável, é um circuito de computador capaz de armazenar o valor de 1 bit, o necessário para o nosso salto). Vamos por partes.

Uma porta lógica é uma série de circuitos que recebe uma ou mais entradas e que resulta em uma saída, sendo as entradas e a saída representadas pelo sinal 1 e 0. As portas lógicas costumam ser nomeadas pela sua função na lógica booleana. Dessa forma, uma porta AND, ou E, é uma porta em que a saída será 1 se todas as suas entradas forem 1, e 0 se pelo menos uma de suas entradas for 0.

Um flip-flop é o circuito que é usado para armazenar os resultados das portas lógicas de forma que após ter sido alimentado o valor não se perde. É o bloco mais fundamental de memória de um computador. Ele não se esquece depois que as entradas foram zeradas e pode ser resetado quando novas entradas forem fornecidas. É a maneira de gravar dados temporários na memória RAM da placa-mãe ou na memória cache do processador.

         +---+
    memA | _ |
         +---+
         +---+
    memB | _ |
         +---+
         +---+
     XOR | _ |
         +---+
         +---+
     NOT | _ |
         +---+
     +-----------+
     | flip-flop |
     +-----------+
           | 0     
        +----+    
        | ZF |    
        +----+    

O flip-flop serve para que o valor do ZF permaneça após a instrução XOR entre os registradores que serão comparados. Eis como funciona: é feito um XOR em cada um dos bits dos valores comparados, fazendo com que qualquer bit diferente tenha uma saída 1. Se todos os bits dos valores comparados forem iguais a zero, significa que os valores são idênticos. Para agrupar todas essas saídas é usada uma porta lógica OR, fazendo com que um único bit diferente de zero (ou mais) reflita na saída. A saída da porta OR, por sua vez, é invertida através da porta NOT colocada antes do flip-flop. Ou seja, se os valores forem idênticos (saída zero da porta OR) a saída final será 1, do contrário será zero.

No final das contas, esse valor será armazenado na flag ZF. Se houver alguma diferença entre os valores, como foi o caso no exemplo acima, o valor final será o um invertido, ou seja, zero. Esse valor armazenado pode ser usado nas próximas instruções para realizar o salto, que dependerá do que estiver nessa flag.

Dessa forma temos o nosso resultado realizado automaticamente através de um cálculo matemático. Agora, para executar o salto condicional, precisamos de um array de dois elementos, cada elemento com um endereço de memória. Podemos definir o primeiro elemento (índice zero) como o armazenador do salto se a condição for falsa, o que quer dizer que seu endereço vai ser o da próxima instrução seqüencial.



Já o segundo elemento irá conter o endereço do salto não-seqüencial, que será feito se a condição for verdadeira.

Dessa forma, para executar o salto baseado em um resultado de 0 ou 1 (o Zero Flag), só temos que alterar o endereço da próxima instrução para o valor do nosso array na posição resultado (0 para falso, 1 para verdadeiro). Note que se o resultado for falso o valor da próxima instrução não muda.



Lembre-se que essa é apenas uma demonstração de como pode funcionar um salto condicional através de cálculos matemáticos. De maneira alguma estou afirmando que é feito dessa forma. Aliás, existem inúmeras formas de realizar esse salto. Uma segunda solução seria adicionar a defasagem (offset) entre o endereço da próxima instrução e o endereço do salto. Nesse caso podemos:

1. Usar o ZF para multiplicar a defasagem e somar ao valor de Próxima Instrução.


2. Continuar usando a técnica do array, sendo o primeiro elemento (`false`) igual a 0.


Acredito ser a solução da multiplicação a pior das três citadas, e a solução da defasagem a mais intuitiva por analogia (se você já programou em assembly). Meu objetivo foi apenas ilustrar que, dado um problema, pode haver várias soluções. Talvez mais para a frente veremos como é implementado um if em assembly, subindo mais um nível de abstração.
