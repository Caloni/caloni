---
date: "2013-11-07"
tags: [ "code", "draft",  ]
title: "Ponto Flutuante Afundando"
---
Quando armazenamos valores monetários em doubles seus cálculos conseguem manter a precisão e na maioria das vezes o ajuste de precisão funciona. Porém, encontrei alguns casos onde a subtração de dois valores fazia "perder" um centavo (ou comparações exatas) justamente pela limitação da precisão do ponto flutuante. Nesse exemplo os valores são 2.358,93 - 1.386,93, que em uma conta de padaria (mas correta) dá 972,00 (até a Calc do Windows e o Excel funcionam), mas pelo Visual Studio 2010 chega perto, mas erra o alvo:


Isso ocorre porque sua representação dentro da variável double é diferente de 272.0 do outro double. Depurando vemos mais claramente:

Ou seja, quando fazemos a subtração de d2 em d1, nossa precisão raspa um pouquinho e escapa pela beirada:


Na comparação com o valor redondo aparece a falha, mas note que isso não ocorre com os outros valores d1 e d2, já que o armazenamento adquire o mesmo formato:

Há uma forma de arredondamento já disponível no C99 (mas não no Visual Studio 2010) que pode ser útil para esses casos. A única coisa que é preciso fazer é arredondar os valores antes do cálculo:


É uma decisão arbitrária essa de arredondar para cima, mas se for adotada em todo o sistema (e já fazendo parte de um padrão, no caso, o C99), não deverão existir problemas de interpretação de cálculos entre os componentes.

O mercado financeiro agradece =).

UPDATE: Não estou de acordo com o armazenamento de valores monetários em doubles em vez de inteiros pelo simples motivo que não há moedas no sistema financeiro com unidades que se dividem ad infinitum. Por consequência, existe sempre uma unidade básica e indivisível (que no caso do Brasil é o centavo de real). Ou seja, como o objetivo é contar o total dessas unidades que não se dividem, o uso de inteiros é brainless.

UPDATE: Existe uma discussão exatamente sobre isso no Grupo C/C++ Brasil, que recomendo a leitura, o que me levou a escrever o post. Particularmente, sigo o raciocínio do Pedro Lamarão.
