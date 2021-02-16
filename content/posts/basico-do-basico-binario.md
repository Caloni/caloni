---
date: "2008-12-18"
title: "Básico do básico: binário"
tags: [ "draft", "code" ]
---
[![Número um e zero caindo do computador.](http://i.imgur.com/lj26csA.png)](http://www.illustrationsof.com/details/clipart/8741.html)Apesar do tema binário, o assunto de hoje no fundo remete-nos a todo e qualquer tipo de **representação**. É o faz-de-conta um pouco mais intenso, vindo das profundezas da matemática e dominado com maestria pela nossa mente e sua capacidade lógica de abstrair.

Como todos sabemos, nós, seres humanos, somos dotados de dez dedos: cinco em cada mão. Isso influenciou fortemente nosso sistema de contagem de coisas, e, como consequência, nossa forma de representar números.

No entanto, números serão sempre números, independente de seres humanos e de dedos. Outros seres inteligentes de outras galáxias poderiam representar os mesmo números, sendo um conceito lógico independente de raça, usando qualquer outra forma e quantidade de símbolos. Por falar em símbolos, nós temos **dez**, a saber:

    
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9

Outros seres poderiam usar, sei lá, dois:

    
    0, 1

É lógico que esse '0' e esse '1' podem ser representados por outros sinais, como pedra e pau, cara e coroa, tico e teco, e por aí vai a valsa.

O importante é que seriam na quantidade de **dois**.

#### Último detalhe

O nosso sistema de representação ainda possui algumas características singulares, como o **valor posicional**. Os mesmos dez símbolos, quando colocados em **posições diversas**, assumem **valores diversos**.

Dessa forma, quando esgotamos todos os símbolos e chegamos a nove, para irmos ao dez começamos a repetir os símbolos, mas em outra posição:

    
     7,
     8,
     9,
    10!

A nova posição do símbolo '1' possui o próximo valor após o nove. O zero, como sabemos, apenas **marca posições** e não possui valor algum. Se valesse algo, seria somado, como no número 111, que é uma **soma de três valores distintos posicionados de acordo**:

    
    100 +
     10 +
      1
    ===
    111

Pronto! Eis toda a base de nosso sistema numérico. O resto é historinha pra boi dormir. Com isso é possível até mudarmos de base, ou seja, o número de símbolos usados, conforme nos convier.

#### Mudando de base

Para nos comunicarmos com a raça alienígena que usa dois símbolos poderíamos contar seguindo o mesmo princípio:

    
      0,
      1,
     10,
     11,
    100,
    101,
    110,
    111,
    ...

[![Os bichos-preguiça possuem dois dedos!](http://i.imgur.com/jQTGnH6.gif)](http://www.colegiosaofrancisco.com.br/alfa/animais/bicho-preguica.php)O valor do número, como sabemos, depende de sua posição. Mas, calma lá! O 111 logo acima não é idêntico ao 111 que vimos anteriormente, pois **mudamos a base**! Agora só temos dois símbolos para representar números, quando antes tínhamos dez.

O "segredo" do valor posicional também está na base, pois o zero, apesar de não possuir valor, marca a quantidade de símbolos que foram utilizados para se esgotar uma posição qualquer. Dessa forma, enquanto o nosso conhecido 10 (dez) vale todos os símbolos não-nulos (nove) mais um (nove + um = dez), o outro 10 (um-zero) da raça alienígena de dois dedos também vale todos os símbolos deles nã-nulos (um) mais um (um + um = dois).

#### Contando em binário?

Como não faz parte do tema, não vou explicar como o sistema binário foi importante para a definição de uma arquitetura simples o suficiente para ser expandida a níveis nunca antes imaginados de processamento e comprimida em espaços que muitos diriam não caber qualquer coisa de útil que fosse. No entanto, apesar de brilhante, o binário no dia-a-dia do programador gera alguns problemas. Principalmente se o programador escreve seus cálculos de **ponteiros em binário**.

Para entender isso, basta lembrar que, atualmente, a quantidade de memória RAM que é contada e, portanto, valor dos ponteiros que apontam para ela, é muito grande **até **para nosso sistema decimal, que possui, relembrando, dez símbolos. O que dirá, então, um sistema que possui meros dois símbolos para representar, digamos, **três gigabytes**:

    
    11000000000000000000000000000000

São tantos zeros que aqueles bugs de _leak _de memória, famosos por levar tempo para ser corrigidos, seriam mais famosos ainda, pois o tempo gasto para se entender alguma coisa no meio de ponteiros dessa magnitude seria astronômico!

E, claro, ainda poderia ficar pior, se fosse depurado um desses novíssimos sistemas de 64 bits:

    
    10011101101101101101101101101101101101101101

#### Contando de dezesseis em dezesseis

Eu sei que não vou conseguir explicar tudo sobre bases numéricas em apenas um miniartigo. Porém, vamos dar uma rápida olhada no famoso hexadecimal, que foi o que nos salvou de lidar com os numerozinhos acima.

Nesse sistema, a representação dos número ocupa **menos espaço ainda** que o sistema decimal, pois usa **dezesseis **símbolos distintos, usando as letras de A a F após os já conhecidos símbolos decimais:

    
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F

A grande vantagem de contar as coisas em dezesseis é que sua representação **será sempre um múltiplo de dois**, o que facilita a conversão para o sistema binário: em um único número hexadecimal cabem quatro números binários, ou **quatro bits**.

    
    Bin.  Hexa  Dec.
    0000  0     0
    0001  1     1
    0010  2     2
    0011  3     3
    0100  4     4
    0101  5     5
    0110  6     6
    0111  7     7
    1000  8     8
    1001  9     9
    1010  A     10
    1011  B     11
    1100  C     12
    1101  D     13
    1110  E     14
    1111  F     15

Tabelinha básica, fácil de achar em qualquer lugar da internet, mas colocada aqui apenas para relembrar a relação entre as três bases.

Bom, acho que é isso. Já ultrapassei o limite do teórico, porque na verdade o que importa aqui, para captar de fato o binário dos fatos, é **praticar**:

#### Coisas para pensar a dois

	
  * Conte em binário quando não estiver fazendo nada. É simples e ajuda a fixar. Dessa forma: um, um-zero, um-um, um-zero-zero, um-um-zero, um-um-um, ...

	
  * Decore a relação entre os números hexadecimal e binário. Você pode até esquecer isso depois, mas o esforço para decorar será útil para fixar. E nunca se sabe quando você terá que [reaver a MBR](http://www.caloni.com.br/depuracao-da-mbr) de um cliente seu.

	
  * Estude a lógica por trás da tabela ASCII e seus valores binários. Irá descobrir que existem relações muito óbvias entre letras, números (maíusculos e minúsculos) e sinais. Tente decorar.

