---
date: "2007-12-31"
title: 'Gambi do dia: swap com apenas duas variáveis'
categories: [ "code" ]
---
<blockquote>_Este artigo é uma reedição de meu blogue antigo, guardado para ser republicado durante minhas miniférias. Esteja à vontade para sugerir outros temas obscuros sobre a linguagem C ou C++ de sua preferência no [formulário de contato](http://www.caloni.com.br/contato) do sítio. Boa leitura!_</blockquote>

Essa interessantíssima questão veio do meu amigo [Kabloc](http://www.kabloc.com.br/): como trocar o valor entre duas variáveis do tipo int **sem utilizar uma variável intermediária**? O algoritmo ordinário para um _swap_ entre tipos inteiros é:

```cpp
/** Troca o valor entre duas variáveis inteiras. Ou seja, ao final da função
a variável first irá conter o valor da variável second e vice-versa.
*/
void normalSwap(int &first, int& second)
{
	int third = first;
	first = second;
	second = third; // contém o valor de first
}

int main()
{
	int first = 13;
	int second = 42;

	cout << "first: " << first << ", second: " << second << endl;
	normalSwap(first, second);
	cout << "first: " << first << ", second: " << second << endl;
} 

```

    
    Saída:
    first: 13, second: 42
    first: 42, second: 13

Uma das soluções que eu conheço é utilizar o operador de **ou exclusivo**, o conhecido **XOR**. Esse operador binário tem a não pouco bizarra habilidade de armazenar dois padrões de bits dentro de um mesmo espaço de armazenamento. Se você tiver um dos dois padrões, conseguirá o segundo. Relembremos sua tabela verdade:

```cpp
void xorTable()
{
	cout << "XOR Table\n---------\n"
		<< "0 XOR 0 = " << ( 0 ^ 0 ) << '\n'
		<< "1 XOR 0 = " << ( 1 ^ 0 ) << '\n'
		<< "0 XOR 1 = " << ( 0 ^ 1 ) << '\n'
		<< "1 XOR 1 = " << ( 1 ^ 1 ) << '\n';
} 

/* 
Saída:
XOR Table
---------
0 XOR 0 = 0
1 XOR 0 = 1
0 XOR 1 = 1
1 XOR 1 = 0
*/

```

Ou seja, imagine que temos o valor 1 e o valor 0. Armazenando os dois juntos com XOR obtemos 1, já que:

    
    1 (primeiro padrão) XOR 0 (segundo padrão) = 1 (padrões juntos)

Mais tarde, se quisermos obter o primeiro padrão, usamos o segundo:

    
    1 (padrões juntos) XOR 0 (segundo padrão) = 1 (primeiro padrão)

Para obter o segundo padrão é só utilizar o primeiro obtido:

    
    1 (padrões juntos) XOR 1 (primeiro padrão) = 0 (segundo padrão)

Calcule a mesma operação com as quatro combinações possíveis e verá que podemos sempre reaver os dados partindo de um dos padrões. Como o cálculo independe do número de bits, já que operadores **bit a bit** operam um **bit de cada vez**, podemos usar a mesma técnica para juntar dois inteiros, duas _strings_, dois "qualquer coisa armazenada numa seqüência de zeros e uns":

```cpp
template<typename T1, typename T2, typename T3>
void universalXor(const T1& first, const T2& second, T3& result)
{
	typedef unsigned char byte;

	const byte* pFirst = reinterpret_cast<const byte*>( &first );
	const byte* pSecond = reinterpret_cast<const byte*>( &second );

	byte* pResult = reinterpret_cast<byte*>( &result );

	for( size_t i = 0; i < sizeof(first) && i < sizeof(second); ++i )
		pResult[i] = pFirst[i] ^ pSecond[i];
}

int main()
{
	// trocando ints
	int x = 13, y = 42;

	cout << "x: " << x << ", y: " << y << '\n';
	universalXor(x, y, x);
	universalXor(x, y, y);
	universalXor(x, y, x);
	cout << "x: " << x << ", y: " << y << "\n\n";

	// trocando strings em c
	char str1[50] = "teste de xor", str2[50] = "aceita strings!";

	cout << "str1: " << str1 << ", str2: " << str2 << '\n';
	universalXor(str1, str2, str1);
	universalXor(str1, str2, str2);
	universalXor(str1, str2, str1);
	cout << "str1: " << str1 << ", str2: " << str2 << '\n';

	return 0;
} 

```

    
    Saída:
    x: 13, y: 42
    x: 42, y: 13
    
    str1: teste de xor, str2: aceita strings!
    str1: aceita strings!, str2: teste de xor

Essa técnica é uma das mais básicas - se não for a mais - de **criptografia simétrica**. O primeiro padrão faz o papel de texto aberto, o segundo banca a senha e o terceiro será o texto encriptado. Para "desencriptar" o texto é necessária a senha (e se você souber qual o texto original, saberá a senha).

Mas, voltando ao nosso problema original, podemos trocar duas variáveis inteiras usando a técnica do XOR. Em claro:

```cpp
#include <iostream>

using namespace std;

/** Troca o valor entre duas variáveis inteiras. Ou seja, ao final da função
a variável first irá conter o valor da variável second e vice-versa.
*/
void anormalSwap(int &first, int& second)
{
	first = first ^ second; // first contém first e second juntos
	second = first ^ second; // firstXORsecond XOR second = first
	first = first ^ second; // second = first. logo, firstXORsecond XOR first = second
}

int main()
{
	int first = 13;
	int second = 42;

	cout << "first: " << first << ", second: " << second << endl;
	anormalSwap(first, second);
	cout << "first: " << first << ", second: " << second << endl;
} 

```

    
    Saída:
    first: 13, second: 42
    first: 42, second: 13

Bom, preciso dizer que isso é uma gambi das grossas? Preciso dizer que **NÃO** uso isso no meu dia a dia, até porque _swap_ é uma função [já consagrada da STL](http://msdn.microsoft.com/library/en-us/vcstdlib/%20html/vclrfSwap_map.asp)? Não? Então sem _Postscript _dessa vez. E sem [bois-cornetas](http://www.google.com.br/search?q=boi+corneta+site%3Asualingua.com.br) =).
