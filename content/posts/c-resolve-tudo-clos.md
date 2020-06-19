---
categories: [ "code" ]
date: "2019-05-17"
link:"https://github.com/Caloni/cdefgeneric"
tags: [ "draft",  ]
title: "C Resolve Tudo Clos"
---
Continuando nossa série, conforme sugerido pelo @colemaker do grupo C/C++/42/Império do Brasil, a próxima ideia a ser implementada em C é o sistema polimórfico de chamadas do Lisp orientado a objetos. Esse sistema permite realizar a seguinte manobra:


O aspecto-chave aqui, conforme eu descobri, é implementar a estratégia de prioridades entre as sobrecargas dos métodos de acordo com os tipos passados. Analisando bem por cima devemos sempre priorizar os métodos com os tipos mais específicos e ir realizando underpromotion até chegarmos no menos específico (se houver).

A implementação está no GitHub. Para o sistema de tipos em C nada como fazer do zero:


As estruturas estão usando STL. O quê? Mas não era C? Sim, você tem toda razão. Porém, estou usando uma lib mais conhecida. Há milhares de libs containers em C para você escolher para trocar a implementação. Lembre-se que o mais importante não é ser purista, mas atingir os objetivos. Como eventualmente veremos nessa série de artigos, o próprio C++ e toda a sua biblioteca pode ser implementada em C. Este é apenas um atalho para fins didáticos e de produtividade (como eu já falei, produtividade não é o foco aqui, mas enxergar por debaixo dos panos).

Inicialmente feito em STL pela produtividade, a solução atual no GitHub é feita inteiramente em C usando a glib (lib comum em Linux com estrutura de dados, etc). O legal dessa biblioteca é que ela tem 20 anos (desde 1998) e já foi muito usada e testada, além de possuir estruturas e algoritmos simples que fazem parte do pacote básico de qualquer programador, como arrays, strings, hash tables.


O código é bem simples. Mapas e listas com strings e ponteiros para organizar as estruturas por detrás do sistema de tipos que estamos implementando e seus métodos sobrecarregados. Cada método possui um nome, um endereço de ponteiro e o número dos seus argumentos. Todos os argumentos são do tipo polimórfico, seguindo o que provavelmente existe por detrás da própria implementação do Lisp.

O código que utiliza a clos.c é bem direto e enxuto. Como no Lisp.


Futuros posts sobre C Resolve Tudo poderão utilizar a glib ou qualquer outra. Uma outra vantagem da linguagem C é que sua biblioteca padrão é muito enxuta, sendo fácil de ter disponível em seu ambiente um compilador C com a clib, e em cima dela você pode utilizar qualquer biblioteca de sua escolha para estruturas e algoritmos mais complexos. Ou fazer a sua própria.
