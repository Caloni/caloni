---
categories:
- code
date: '2021-05-13'
link:
tags:
- draft
title: Como Ordenar Três Números em Uma Entrevista
---
O primeiro exercício pedido ao candidato para a vaga de programação na [Intelitrader] é fazer uma função que receba três números e informe entre eles qual o maior, o menor e a média dos três. Sim, eu sei, absurdamente fácil, não? Porém, mesmo assim, a grande maioria dos "programadores" que entrevisto perde mais de meia-hora em um exercício simples desse. O motivo, acredito eu, é que a lógica de programação está cada vez mais em baixa. Pensar se tornou tristemente um requisito opcional em uma vaga de programação.

No meio de uma entrevista, entediado, resolvi eu mesmo ir resolvendo enquanto aguardava o candidato. Imaginei o que eu, como hipotético candidato, faria para resolver esse exercício da maneira mais rápida. Meu objetivo não era apenas cuspir código, mas entender qual o raciocínio envolvido na obtenção de uma lógica simples dessa.

Então vamos lá. A primeira coisa que eu pensei é fazer em Python. Porque programar em Python um código desses dá para fazer em qualquer editor, inclusive na web. Inclusive em um papel de pão.

A segunda coisa que eu pensei é em já criar a função recebendo os três números, mas em não usá-los no cálculo, porque usar três nomes de variáveis para decidir qual é o maior e menor seria um pé no saco cheio de ifs e elses. Melhor rodar um loop que alimenta o maior e o menor de todos. Sabendo disso eu crio duas variáveis, maior e menor:

    def func(a, b, c):
      maior = 0
      menor = 100000000
      nums = [ a, b, c ]

Eu inicializo maior com o "menor valor possível", zero, e menor com o "maior valor possível", no caso um número muito grande. É o maior possível? Não, mas já resolve o problema para números médios e grandes. Caso o entrevistador questionasse essa parte do código eu poderia simplesmente pesquisar qual o maior valor representável por um inteiro em Python para inicializar corretamente. Para um problema em que a resposta precisa ser dada em alguns minutos está de bom tamanho.

Por fim, meu loop que verifica qual o menor e maior varre o array que criei e no final eu sei que o menor e maior valor estarão nas variáveis de mesmo nome.

    for n in nums:
      if n > maior:
        maior = n
      if n < menor:
        menor = n

E a média é obtida somando os três números dividido por três, me lembrando que pode ser um número quebrado, então é melhor que seja um ponto flutuante, o que eu consigo dividindo por 3.0 em vez de 3.

    print("media: ", (a + b + c) / 3.0);

O conjunto da obra é bem simples e intuitivo. Não precisou de muito raciocínio. O maior desafio, em minha opinião, é manter a calma, entender o problema, e abordar da maneira que consuma menos tempo e esforço intelectual, os recursos escassos do desafio.

    def func(a, b, c):
      maior = 0
      menor = 100000000
      nums = [ a, b, c ]
      for n in nums:
        if n > maior:
          maior = n
        if n < menor:
          menor = n
      print("maior: ", maior);
      print("menor: ", menor);
      print("media: ", (a + b + c) / 3.0);

Não precisa ser a melhor solução do mundo, mas já é uma solução boa o suficiente. Justamente o que a Intelitrader pede aos seus candidatos e funcionários. =)

[Intelitrader]: http://www.intelitrader.com.br
