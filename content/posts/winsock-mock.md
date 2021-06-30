---
categories:
- code
date: '2020-04-10'
title: Winmock
---

Testar sistemas com rede simulada pode ser muito complexo ou muito simples. Se for feito em C ou se os endpoints forem em C é muito simples: basta trocar as funções originais pelas suas. Como tudo em C são funções com nome bem definido e assinatura flexível você não precisa declarar a assinatura da função, ou pode mudar no meio do caminho.

Existe um recurso interessante da winsock, um define chamado INCLWINSOCKAPIPROTOTYPES, que pode desabilitar a publicação das assinaturas das funções de socket do header winsock2.h. E por que isso é importante? Porque essas assinaturas já possuem a informação que essas funções deverão ser importadas de uma DLL (no caso a Ws232.dll). Isso muda o nome da função C. Além disso, a convenção de chamada da API do Windows é baseada em Pascal, e não cdecl, sendo a desvantagem não existir número de argumentos variáveis na pilha.

As funções C do winsock/socket, connect, send, recv, select, etc, são apenas funções C cujos nomes são conhecidíssimos. Elas são linkadas com programas que usam alguma biblioteca de socket. Nada impede que nós mesmos sobrescrevamos essas funções para implementá-las em nosso programa. É isso o que o uso do define acima possibilita: ele evita a importação direto da DLL da Microsoft e com isso você pode usar uma implementação de terceiros ou a sua própria, que não precisa se comunicar com a rede.