---
date: "2007-08-15"
tags: [ "code", "draft",  ]
title: "História da linguagem C - parte 2"
---
No princípio... não, não, não. Antes do princípio, quando C era considerada a terceira letra do alfabeto e o que tínhamos eram linguagens experimentais para todos os lados, dois famigerados Srs. dos Laboratórios Bell, K. Thompson e D. Ritchie, criaram uma linguagem chamada B. E B era bom.

O bom de B era sua rica expressividade e sua simples gramática. Tão simples que o manual da linguagem consistia de apenas 30 páginas. Isso é menos do que as 32 palavras reservadas de C. As instruções eram definidas em termos de if's e goto's e as variáveis eram definidas em termos de um padrão de bits de tamanho fixo - geralmente a word da plataforma - que utilizada em expressões definiam seu tipo; esse padrão de bits era chamado rvalue. Imagine a linguagem C de hoje em dia com apenas um tipo: int.

Como esse padrão de bits nunca muda de tamanho, todas as rotinas da biblioteca recebiam e retornavam sempre valores do mesmo tamanho na memória. Isso na linguagem C quer dizer que o char da época ocupava tanto quanto o int. Existia inclusive uma função que retornava o caractere de uma string na posição especificada:


Sim! Char era uma função, um conversor de "tipos". No entanto a própria variável que armazenava um char tinha o tamanho de qualquer objeto da linguagem. Esse é o motivo pelo qual, tradicionalmente, as seguintes funções recebem e retornam ints em C e C++:


Segue o exemplo de uma função na linguagem B, hoje muito famosa:

Como podemos ver, vários elementos (se não todos) da linguagem C já estão presentes na B.
