---
date: "2016-01-11"
tags: [ "code", "draft",  ]
title: "Classe, objeto, contexto, método"
---
No post anterior falamos como a passagem de um endereço de uma struct consegue nos passar o contexto de um "objeto", seja em C (manualmente) ou em C++ (automagicamente pelo operador implícito this). Trocamos uma propriedade desse "objeto" em C, mas ainda não chamamos um método.

Hoje faremos isso.

Isso é relativamente simples quando se conhece ponteiros de função, existentes tanto em C quanto em C++. Ponteiros de função são tipos que contém endereço de uma função com assinatura específica (tipo de retorno e de argumentos). Através de um ponteiro de função é possível chamar uma função e passar alguns argumentos. Como o contexto nada mais é que um argumento, será só passá-lo como parâmetro.


No exemplo anterior não sabíamos como chamar um método de nosso "objeto" em C:


Isso se torna fácil se tivermos uma nova "propriedade" na nossa struct que é um ponteiro para a função que queremos chamar.




Parece muito trabalho para algo que é feito "automagicamente" em C++, certo? Certo. Porém, agora sabemos o que acontece por baixo dos panos em C++ e que pode ser feito em C (ainda que "na mão"). Você provavelmente nunca fará esse tipo de código em C para emular C++, mas o objetivo desse código é entender como funciona, por exemplo, a vtable do C++, que permite polimorfismo.

Mas esse é assunto para outro post.
