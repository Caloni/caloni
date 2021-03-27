---
date: "2007-12-25"
title: "O que acontece quando o contador estoura"
tags: [ "code" ]
---
Dois conceitos de programação relacionados a limites computacionais são bem conhecidos do programador: o famigerado overflow e o não-tão-famoso underflow (embora seja fácil imaginar que ele é o oposto do primeiro). O primeiro ocorre quando somamos a uma variável inteira não-nula um valor cujo resultado não consegue ser representado pelo tamanho de memória usado para armazenar esse tipo inteiro (que pode ser um caractere, um inteiro curto, inteiro longo e por aí vai). O underflow, por outro lado (outro lado mesmo), é o resultado de uma subtração que não pode ser representado pelo número de bits do seu tipo inteiro.

Nada melhor que um código para ilustrar melhor esses dois ilustres acontecimentos:

    #include <limits.h>
    #include <iostream>
    
    int main()
    {
    	int x = INT_MAX;
    
    	std::cout << x << std::endl;
    	x = x + 1;
    	std::cout << x << std::endl;
    } 

    Saída:

     2147483647
    -2147483648

O indicador de que algo está errado é simples: como diabos foi um número positivo virar negativo, já que eu somei ao invés de subtrair? No entanto, computacionalmente parece extremamente correto: o próximo número após o maior valor positivo possível é o menor número negativo possível.

Nos computadores atuais tudo no final acaba sendo representado por zeros e uns, até o sinal de negativo dos números menores que zero. Por isso mesmo, para que consigamos usar números menores que zero, precisamos gastar um bit para indicar que este número é negativo. Existem muitas representações interessantes, dentre as quais a mais popular acabou sendo a de complemento de dois. A regra é simples:

> Toda representação binária que tiver o bit mais significativo ligado (o bit mais à esquerda) significa um número negativo cujo valor absoluto se obtém invertendo-se o resto dos bits e adicionando um.

Quando o bit mais à esquerda não está ligado o valor absoluto é ele mesmo; ou seja, é um número positivo, incluindo o zero. Como vamos ver, isso facilita em muito os cálculos para o computador. Para nós, a coisa não fica lá muito difícil. Só precisamos lembrar que, em hexadecimal, todos os valores que tiverem o byte mais significativo igual ou maior que 8 (que é 1000 em binário) é negativo e temos que aplicar o método de complemento de dois para obter seu valor absoluto. Vejamos o valor -8, por exemplo:

  1. Primeiro temos a representação real (em um byte): 1111 1000.
  2. O bit mais significativo está ligado: é um número negativo. Descartamos o sinal, fica 111 1000.
  3. Devemos agora inverter todos os bits: 111 1000 se torna 000 0111.
  4. Por fim, somamos um: 000 0111 + 1 = 000 1000.
  5. Como vimos no parágrafo anterior, 000 1000, ou simplesmente 1000, é 8. Na verdade, -8!

O que significa, na notação complemento de dois, a representação onde estão todos os bits ligados, independente do número de bytes?

Se alterarmos o código acima para imprimir na saída os números hexadecimais, obteremos a seguinte saída:

    7fffffff
    80000000

E o mais legal é que agora sabemos que o primeiro número é o maior valor positivo possível nesse tamanho de int, pois possui todos os bits ligados exceto o bit de sinal. Já o segundo número, o primeiro incrementado de 1, possui todos os bits desligados exceto o bit de sinal: é o menor número negativo possível!

Consegue imaginar como os cálculos são feitos pelo computador? Curioso? Então dê uma olhada na Wikipedia sobre [complemento de dois].

[complemento de dois]: http://en.wikipedia.org/wiki/Twos_complement
