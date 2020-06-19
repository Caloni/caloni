---
categories: [ "code" ]
date: "2018-08-30"
tags: [ "draft",  ]
title: "GetArg: the ultimate badass argv/argc parser"
---
Sim, eu acho que já resumi o suficiente meu parseador de argv/argc no meu último artigo sobre o tema. Sim, eu também acho que a versão com STL bonitinha (mas ordinária). A questão agora não são as dependências, mas o uso no dia-a-dia: precisa ter o argc nessa equação?

A resposta é não. Pois, como sabemos, o padrão C/C++ nos informa que o argv é um array de ponteiros de strings C que termina em nulo. Sabemos que ele termina, então o argc é apenas um helper para sabermos de antemão onde ele termina. Mas quando precisamos, por exemplo, passar o argv/argc para uma thread Windows, que aceita apenas um argumento mágico, talvez minha versão antiga não seja tão eficaz, pois isso vai exibir que eu aloque memória de um struct que contenha ambas as variáveis, etc. Por que não simplesmente utilizar apenas o argv?


Nessa versão elminamos a necessidade do argc e de brinde ganhamos a possibilidade de usar um único ponteiro como start de um parseamento de argumentos.
