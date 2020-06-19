---
categories: [ "code" ]
date: "2014-03-28"
tags: [ "draft",  ]
title: "A moda agora é levar lambda na função"
---

A nova moda de programar C++ nos últimos anos com certeza é usar lambda. Mas, afinal, o que é lambda? Bom, pra começar, é um nome muito feio.

O que esse nome quer dizer basicamente é que agora é possível criar função dentro de função. Não só isso, mas passar funções inteiras, com protótipo, corpo e retorno, como parâmetro de função.

Isso significa que finalmente os algoritmo da STL vão ser úteis e não um "pain in the ass".

Por exemplo, antes, tínhamos que fazer o seguinte malabarismo para mexer com arrays/vetores/listas:


Imagine que para cada interação devíamos criar uma função que manipulasse os elementos do vetor.

Uma alternativa que costumava utilizar era a de roubar na brincadeira e criar um tipo dentro da função (permitido) e dentro desse tipo criar uma função (permitido):


Apesar disso gerar INTERNALCOMPILERERROR em muitos builds com o Visual Studio 2003 (e o rápido, mas anos noventa, Visual Studio 6) na maioria das vezes o código compilava e rodava sem problemas. No entanto, deixava um rastro sutil de gambi no ar...

Agora isso não é mais necessário. Desde o Visual Studio 2010 (que eu uso) a Microsoft tem trabalhado essas novidades do padrão no compilador, e aos poucos podemos nos sentir mais confortáveis em usar essas modernices sem medo. Por exemplo:


"Caraca, mas o que é esse código alienígena?", diria alguém como eu alguns anos atrás (talvez até meses). Bom, nada vem de graça em C++ e dessa vez houve algumas mudanças meio drásticas na sintaxe para acomodar o uso dessa lambida inline.


E não é só isso. Tem muito mais esquisitices de onde veio essa.
