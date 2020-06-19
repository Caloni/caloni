---
categories: [ "code" ]
date: "2010-08-30"
tags: [ "draft",  ]
title: "Como ofuscar strings"
---
Já fiz ofuscamento e embaralhamento de dados acho que umas três ou quatro vezes. Dessa vez, parti para o batidíssimo esquema de fazer o pré-processamento de um header com defines que irão virar estruturas reaproveitadas por uma função padrão que desofusca e ofusca aquela tripa de bytes em algo legível: a string original.

Vamos ver um exemplo:


Conseguimos capturar os três elementos desse define (um descartável) por um simples scanf:


A função scanf retorna o número de argumentos capturados. Então se a coisa funcionou é só comparar com 2.

Depois de capturado, imprimimos na saída (o arquivo pós-processado) uma estrutura que irá conter nosso amigo embaralhado:


Pronto. Agora o usuário da string precisa abri-la usando uma macro esperta que irá chamar uma função esperta para desofuscar a string e entregar o ponteiro de buffer devidamente "casteado":


Uma vez que a abertura se faz "inplace", ou seja, a memória da própria variável da estrutura original é alterada, pode-se fechar a variável novamente, se quiser, após o uso.


A GENERICSTRUCT do exemplo se trata apenas de um esqueleto para que todas as estruturas das 500 strings ofuscadas sejam entendidas a partir de um modelo. Sim, essa é uma solução usando linguagem C apenas, então não posso me dar ao luxo daqueles templates frescurentos.


Como a string é ofuscada? Sei lá, use um XOR:


Dessa forma abrir ou fechar a variável pode ser feito usando a mesma função.

Alguém aí gostaria de uma explicação didática sobre o operador XOR?

PS: Acho que, além das minhas palestras, meus artigos estão também parecendo um brainstorm. 
