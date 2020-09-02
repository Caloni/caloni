---
date: "2014-06-24"
tags: [ "code", "draft",  ]
title: "Se iterando com os pseudo-ponteiros: uma breve introdução"
---
Como já vimos algumas vezes, a STL não prima por interfaces intuitivas, preferindo abstrações que criem um leque de ferramentas genéricas para tratamento uniformizado de coleções de dados através de algoritmos. O problema disso é que novos programadores da linguagem terão que aprender uma maneira nova de lidar com problemas baseada na percepção dos criadores do padrão na época em que foi lançado de como seria a evolução da ciência da computação nos próximos anos. Muitos dos conceitos ali abordados realmente se tornaram padrão de facto, mas na briga pela expansão da linguagem quem perdeu por muito tempo foi o próprio desenvolvedor, que teve que se contentar com uma lista de algoritmos genéricos parcialmente compilado.

Dito isto, a abstração dos iteradores é a coisa mais linda do mundo.

Os dois únicos conceitos que é preciso se lembrar para sempre quando se trata de iteradores é que ele:

  * Um iterador se comporta como um ponteiro opaco.

  * O final de um contêiner está sempre um elemento além do último.

Um ponteiro pode ser iterador, mas não o contrário!

Tudo que um ponteiro faz de útil em C/C++ foi emprestado para a STL usar em seus contêiners, e tudo em que ele é prejudicial tentou ficar de fora. E o que um ponteiro faz de útil?

  * Um ponteiro pode apontar para elementos sem conhecermos sua posição.

  * Podemos incrementar ou decrementar ponteiros para caminhar em listas.

  * Dois ponteiros podem ser subtraídos para sabermos a distância entre dois elementos.


Da mesma forma, operações como cópia, movimentação, ordenação, caotização, pode ser feito usando dois ponteiros/iteradores de dois contêiners distintos, desde que algumas regras básicas sejam seguidas, como um iterador deve sempre apontar para algo válido (ou disponibilizar alguma abstração que insira novos elementos em um contêiner menor). Veremos essas regras em um próximo post sobre o tema. Apontarei para ele aqui.

