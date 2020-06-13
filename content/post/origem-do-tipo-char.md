---
categories: [ "code" ]
date: "2015-01-26"
tags: [ "draft",  ]
title: "Origem do tipo char"
---
Programadores C e C++, preparem-se para explodir as cabeças!

No princípio... não, não, não. Antes do princípio, quando C era considerada a terceira letra do alfabeto e o que tínhamos eram linguagens experimentais para todos os lados, dois famigerados srs. dos Laboratórios Bell, K. Thompson e D. Ritchie, criaram uma linguagem chamada B. E B era bom.

O bom de B estava em sua rica expressividade. Sua gramática extremamente simples. Tão simples que o manual da linguagem consistia de apenas 30 páginas. Isso é menos do que as 32 palavras reservadas de C.

As instruções eram definidas em termos de if's e goto's e as variáveis eram definidas em termos de um padrão de bits de tamanho fixo -- geralmente a word da plataforma -- que utilizada em expressões definiam seu tipo; esse padrão de bits era chamado rvalue.

Como esse padrão de bits nunca muda de tamanho, todas as rotinas da biblioteca recebiam e retornavam sempre valores do mesmo tamanho na memória. Isso na linguagem C quer dizer que o char da época ocupava tanto quanto o int. Existia inclusive uma função que retornava o caractere de uma string na posição especificada:

    c = char(string, i); // the i-th character of the string is returned

Sim! Char era uma função, um conversor de "tipos". No entanto a própria variável que armazenava um char tinha o tamanho de qualquer objeto da linguagem. Esse é o motivo pelo qual, tradicionalmente, as seguintes funções recebem e retornam ints em C:

    int getchar( void ); // read a character from stdin
    int putchar( int c ); // writes a character to stdout
    void *memset( void *dest, int c, size_t count ); // sets buffers to a specified character

Links interessantes para filólogos de plantão:

 - Dennis Ritchie Home Page
 - BCPL Reference Manual by Martin Richards
 - Users' Reference to B by Ken Thompson
