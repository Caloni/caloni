---
date: "2007-06-29"
categories: [ "code" ]
title: "A Inteligência do if: Parte 2"
---
Vimos na [primeira parte] desse artigo como o if revolucionou o mundo da computação ao trazer um salto que depende de condições anteriores e, portanto, depende do estado do programa. A ele chamamos de salto condicional. Também vimos como o resto das construções lógicas de uma linguagem são apenas derivações montadas a partir de saltos condicionais e incondicionais. Nesta segunda parte veremos como implementar um saldo condicional baseando-se no fato de que o computador pode apenas realizar operações matemáticas. Afinal de contas, um computador não "pensa".

Uma condição, item necessário para o funcionamento do salto condicional, nada mais é do que o conjunto de um cálculo matemático e o seu resultado, sendo o salto dependente desse resultado. Geralmente o resultado usado é uma flag, um indicador, definida pela arquitetura, como o armazenador de resultado para comparações de igualdade. Na plataforma 8086, por exemplo, as instruções que comparam memória definem uma flag chamada de Zero Flag (ZF) que é modificada sempre logo após executada uma instrução da categoria de comparações de valores.

É comum nas arquitetura o resultado de uma comparação ser igual a zero se os elementos são iguais e diferente de zero se são diferentes. O resultado, então, denota a diferença entre as memórias comparadas, e se não há diferença o resultado é zero.

    set memA, 1
    set memB, 1
    cmp memA, memB # ZF=0

    set memA, 1
    set memB, 0
    cmp memA, memB # ZF=1

Mas como de fato comparar? Aí é que reside a mágica das portas lógicas e operações booleanas. A comparação acima pode ser feita com uma porta lógica XOR, o OU-eXclusivo, por exemplo, e o resultado pode ser obtido e armazenado se a saída for conectada a um flip-flop (um flip-flop, ou multivibrador biestável, é um circuito de computador capaz de armazenar o valor de 1 bit, o necessário para o nosso salto). Vamos por partes.

Uma porta lógica é uma série de circuitos que recebe uma ou mais entradas e que resulta em uma saída, sendo as entradas e a saída representadas pelo sinal 1 e 0. As portas lógicas costumam ser nomeadas pela sua função na lógica booleana. Dessa forma, uma porta AND, ou E, é uma porta em que a saída será 1 se todas as suas entradas forem 1, e 0 se pelo menos uma de suas entradas for 0.

Um flip-flop é o circuito que é usado para armazenar os resultados das portas lógicas de forma que após ter sido alimentado o valor não se perde. É o bloco mais fundamental de memória de um computador. Ele não se esquece depois que as entradas foram zeradas e pode ser reiniciado quando novas entradas forem fornecidas. É a maneira de gravar dados temporários na memória RAM da placa-mãe ou na memória cache do processador.

O flip-flop serve para que o valor do ZF permaneça após a instrução XOR entre os registradores que serão comparados. Eis como funciona: é usada uma porta lógica XOR para cada um dos bits dos valores comparados, fazendo com que qualquer bit diferente tenha uma saída 1. Se todos os bits dos valores comparados forem iguais a zero, significa que os valores são idênticos. Para agrupar todas essas saídas é usada uma porta lógica OR, fazendo com que um único bit diferente de zero (ou mais) reflita na saída. A saída da porta OR, por sua vez, é invertida através da porta NOT colocada antes do flip-flop. Ou seja, se os valores forem idênticos (saída zero da porta OR) a saída final será 1, do contrário será zero.

No final das contas, esse valor armazenado por um flip-flop é a flag ZF da arquitetura 8086. Se houver alguma diferença entre os valores, como foi o caso no exemplo acima, o valor final será o um invertido, ou seja, zero. Esse valor armazenado pode ser usado nas próximas instruções para realizar o salto, que dependerá do que estiver nessa flag. Dessa forma temos o nosso resultado realizado automaticamente através de um cálculo matemático.

Um salto incondicional, como vimos na parte um, é um salto para um outro ponto no código que vai ser feito de qualquer forma. Pode ser uma instrução do processador saltar para um endereço definido em algum lugar da memória. O goto possui como destino o endereço X, sendo que X depende do que estiver em seu próprio endereço.

    001 set memA, 004
    002 jump memA
    003 code # not executed
    004 code
    005 ...

Agora, para executar o salto condicional, precisamos não apenas de um, mas de dois endereços de destino, cada um deles com um endereço de memória. Podemos definir o primeiro endereço como o armazenador do salto se a condição for falsa, e o segundo endereço se a condição for verdadeira.

    001 set memA, 006
    002 set memB, 005
    003 cmp memC, memD
    004 jz memA
    005 code # ZF=1
    006 code # ZF=0
    007 ...

Se os valores em memC e memD forem iguais a comparação feita na linha 003 deixará o ZF igual a 0 e portanto o comando jz (jump if zero, saltar se zero) irá realizar o salto para a linha 006, que é o endereço contido em memA. Caso contrário não será feito o salto, ou seja, a próxima instrução será a da linha 005, a mesma contida em memB.

Agora você pode estar se perguntando por que existe o endereço em memB, já que se a condição for falsa o código simplesmente seguirá o fluxo normal. Bom, este memB é meramente figurativo, pois estou tentando demonstrar como não existe, de fato, uma "inteligência" na instrução de comparação que determine a igualdade de dois valores. Tudo se resume a circuitos realizando cálculos matemáticos.

Para isso continue imaginando o memB sendo usado como o endereço a ser usado caso a condição falhe. Esse endereço está localizado logo após o memA na memória. Se memA estiver em 080, memB estará em 081.

    080 memA # 006
    081 memB # 005

Dessa forma, para executar o salto baseado em um resultado de 0 ou 1 (o Zero Flag) só temos que alterar o endereço da próxima instrução para o valor do endereço de comparação mais o valor de ZF, que pode ser 1 ou 0. Se for 0 será o próprio endereço da condição (memA), mas se for 1 será esse endereço mais 1 (ZF), ou seja, memB.

    001 set memA, 006
    002 set memB, 005
    003 cmp memC, memD # muda ZF
    004 jump [memA + ZF]
    005 code # ZF=1
    006 code # ZF=0
    007 ...

Lembre-se que essa é apenas uma demonstração de como pode funcionar um salto condicional através de cálculos matemáticos. De maneira alguma estou afirmando que é feito dessa forma. Aliás, existem inúmeras formas de realizar esse salto. Uma segunda solução seria adicionar a defasagem (offset) entre o endereço da próxima instrução e o endereço do salto. Meu objetivo foi apenas ilustrar que, dado um problema, pode haver várias soluções. Talvez mais para a frente veremos como é implementado um if em assembly, subindo mais um nível de abstração. Por enquanto estamos apenas trabalhando no nível filosófico. O mais importante de todos.

[primeira parte]: /a-inteligencia-do-if-parte-1
