---
categories: [ "code" ]
date: "2009-06-18"
tags: [ "draft",  ]
title: "Bugs Difíceis de Achar"
---
Saiu um artigo na Wired News sobre os piores bugs da história. Entre eles estão a explosão de um oleoduto soviético em plena guerra-fria (como se não bastasse chernobyl), o primeiro worm da Internet (que se aproveita de um buffer overflow da função gets) e o famoso erro de divisão em ponto flutuante do Pentium; um erro de cálculo de cerca de 0,006% que causou um prejuízo de 457 milhões de dólares para a Intel.

Mas o que achei mais legal, apesar de não estar na lista, estava relacionado com o Mariner 1, primeira espaçonave de um programa da NASA para pesquisar Marte, Vênus e Mercúrio em voos automatizados. Mariner 1 não chegou a sair de órbita, pois houve uma falha na antena de comunicação entre módulos e um bug no programa do computador de bordo.

Falava-se que o bug havia sido gerado ao trocar uma vírgula por um ponto em um loop escrito em FORTRAN. Apesar de não ter sido esse o causador da falha do computador da nave do projeto Mariner, ele existiu de fato em outro projeto da NASA, o Mercury. A linha fatal no caso era essa:


É óbvio que a intenção do programador foi fazer um loop até o label 17 dez vezes, pois a instrução para isso é:


Mas pela troca da vírgula pelo ponto, e como em FORTRAN os caracteres de espaço não são significativos, a linha com o bug não representa mais um loop, mas uma atribuição à uma variável chamada "DO17I":


Esse detalhe esdrúxulo de uma das linguagens mais famosas da época nos leva a crer que antigamente os programadores deveriam estar muito mais atentos durante a digitação de código do que os programadores de hoje em dia, com seus ambientes com verificação sintática embutida. Existe inclusive um texto humorístico de longa data comparando programadores de verdade e programadores de linguagens estruturadas como PASCAL recém-saídos da faculdade, carinhosamente citados no texto como "Quiche Eaters" (comedores de pastelão).

O tipo de erro de falta de atenção do programa da NASA lembra uma das mais duras críticas às linguagem C e C++: é fácil escrever um código errado do ponto de vista lógico mas sintaticamente correto (compilável). Alguns exemplos famosos:


Dessa coleção de problemas, o compilador nos brinda com dois warnings:


Agora imagine o número de horas noturnas em frente ao micro que você não poderia ter economizado em sua vida se aumentasse o nível de warning e lêsse-os de vez em quando? =)

Colaborando com a lista de bugs difíceis de achar do artigo ai vai código/piadinha:


Esse não é pego pelos alertas dos compiladores (pelo menos não pelos que eu uso)... É um bom motivo para usar const no lugar de define em alguns casos, ou no mínimo cercar o define por parênteses "(" e ")"

Outro bug muito comum entre iniciantes é o de templates aninhados, apesar de que compiladores mais novos lidam melhor com o bug e trazem mensagens de erro mais claras:

