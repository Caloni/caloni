---
date: "2007-08-15"
title: História da linguagem C - parte 2
tags: [ "draft", "blog" ]
---
No princípio... não, não, não. Antes do princípio, quando C era considerada a terceira letra do alfabeto e o que tínhamos eram linguagens experimentais para todos os lados, dois famigerados Srs. dos Laboratórios Bell, K. Thompson e D. Ritchie, criaram uma linguagem chamada B. E B era bom.

![](http://i.imgur.com/PMj2AF4.jpg)

*Ken Thompson (esquerda) e Dennis Ritchie (direita). Fonte: wikipedia.org.*

O bom de B era sua rica expressividade e sua simples gramática. Tão simples que o [manual da linguagem](http://cm.bell-labs.com/cm/cs/who/dmr/kbman.html) consistia de apenas 30 páginas. Isso é menos do que as [32 palavras reservadas de C](http://msdn.microsoft.com/library/en-us/vccelng/htm/eleme_5.asp). As instruções eram definidas em termos de if's e goto's e as variáveis eram definidas em termos de um padrão de bits de tamanho fixo - geralmente a [word](http://en.wikipedia.org/wiki/Word_%28computer_science%29) da plataforma - que utilizada em expressões definiam seu tipo; esse padrão de bits era chamado rvalue. Imagine a linguagem C de hoje em dia com apenas um tipo: **int**.

Como esse padrão de bits nunca muda de tamanho, todas as rotinas da biblioteca recebiam e retornavam sempre valores do mesmo tamanho na memória. Isso na linguagem C quer dizer que o **char** da época ocupava tanto quanto o **int**. Existia inclusive uma função que retornava o caractere de uma string na posição especificada:

```
c = char(string, i); /* the i-th character of the string is returned */
```

Sim! **Char** era uma função, um conversor de "tipos". No entanto a própria variável que armazenava um char tinha o tamanho de qualquer objeto da linguagem. Esse é o motivo pelo qual, tradicionalmente, as seguintes funções recebem e retornam ints em C e C++:

```
int getchar( void ); // read a character from stdin
int putchar( int c ); // writes a character to stdout
void *memset( void *dest, int c, size_t count ); // sets buffers to a specified character
```

Segue o exemplo de uma função na linguagem B, hoje muito famosa:

```c
/* The following function is a general formatting, printing, and
   conversion subroutine.  The first argument is a format string.
   Character sequences of the form `%x' are interpreted and cause
   conversion of type 'x' of the next argument, other character
   sequences are printed verbatim.   Thus

	printf("delta is %d*n", delta);

	will convert the variable delta to decimal (%d) and print the
	string with the converted form of delta in place of %d.   The
	conversions %d-decimal, %o-octal, *s-string and %c-character
	are allowed.

	This program calls upon the function `printn'. (see section
	9.1) */

printf(fmt, x1,x2,x3,x4,x5,x6,x7,x8,x9) {
	extrn printn, char, putchar;
	auto adx, x, c, i, j;

	i= 0;	/* fmt index */
	adx = &x1;	/* argument pointer */
loop :
	while((c=char(fmt,i++) ) != `%') {
		if(c == `*e')
			return;
		putchar(c);
	}
	x = *adx++;
	switch c = char(fmt,i++) {

	case `d': /* decimal */
	case `o': /* octal */
		if(x < O) {
			x = -x ;
			putchar('-');
		}
		printn(x, c=='o'?8:1O);
		goto loop;

	case 'c' : /* char */
		putchar(x);
		goto loop;

	case 's': /* string */
		while(c=char(x, j++)) != '*e')
			putchar(c);
		goto loop;
	}
	putchar('%') ;
	i--;
	adx--;
	goto loop;
} 

```

Como podemos ver, vários elementos (se não todos) da linguagem C já estão presentes na B.

**Links interessantes para filólogos de plantão**
    
 * [Dennis Ritchie Home Page](http://www.cs.bell-labs.com/who/dmr/)
 * [Users' Reference to B](http://cm.bell-labs.com/cm/cs/who/dmr/kbman.html), by Ken Thompson
 * [Parte 1](/historia-da-linguagem-c-parte-1)
 * [História do C++](/a-linguagem-de-programacao-cpp-o-inicio)

