---
date: "2015-01-26"
tags: [ "ccpp" ]
title: "Origem do Tipo char"
---
Programadores C e C++, preparem-se para explodir as cabeças! No princípio... não, não. Antes do princípio, quando C era considerada a terceira letra do alfabeto e o que tínhamos eram linguagens experimentais para todos os lados, dois famigerados srs. dos Laboratórios Bell, K. Thompson e [D. Ritchie], criaram uma linguagem chamada B. E B era bom.

O bom de B estava em sua rica expressividade. Sua gramática extremamente simples. Teoricamente a evolução da [linguagem BCPL] criada por Martin Richards, ela era tão simples que o [manual da linguagem B] consistia de apenas 30 páginas. Isso é menos do que as 32 palavras reservadas de C. As instruções eram definidas em termos de if's e goto's e as variáveis eram definidas em termos de um padrão de bits de tamanho fixo, geralmente a palavra da plataforma, que utilizada em expressões definiam seu tipo; esse padrão de bits era chamado rvalue.

Como esse padrão de bits nunca muda de tamanho, todas as rotinas da biblioteca recebiam e retornavam sempre valores do mesmo tamanho na memória. Isso na linguagem C quer dizer que o char da época ocupava o mesmo tamanho que um int. Existia inclusive uma função que retornava o caractere de uma string na posição especificada:

    // the i-th character 
    // of the string is returned
    c = char( string, i );

Sim! Char era uma função, um conversor de "tipos". No entanto a própria variável que armazenava um char tinha o tamanho de qualquer objeto da linguagem. Esse é o motivo pelo qual, tradicionalmente, as seguintes funções recebem e retornam ints em C:

    // read a character 
    // from stdin
    int getchar( void );

    // writes a character 
    // to stdout
    int putchar( int c );

    // sets buffers to a 
    // specified character
    void *memset( void *dest, 
      int c, 
      size_t count );

[D. Ritchie]: https://www.bell-labs.com/usr/dmr/www/
[linguagem BCPL]: https://www.bell-labs.com/usr/dmr/www/bcpl.html
[manual da linguagem B]: https://www.bell-labs.com/usr/dmr/www/kbman.html
