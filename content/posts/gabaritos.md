---
date: "2016-01-13"
title: "Gabaritos"
tags: [ "draft", "code" ]
---
Um __template__ -- ou, como é na tradução da primeira edição de The C++ Programming Language, de Bjarne Stroustrup, aqui no Brasil: __gabarito__ -- é um molde que pode ser usado por diferentes tipos para traduzir o mesmo algoritmo, ou pelo menos a mesma intenção de algoritmo (por pela sobrecarga de operadores é possível que o comportamento de tipos diferentes pode ser diferente).

Em C++, fazer uma função template é muito simples:

```cpp
#include <iostream>

using namespace std;

template<typename T>
bool Compare(T& var1, T& var2)
{
	return var1 < var2;
}

int main()
{
	int x = 24, y = 42;
	double dx = 100.0, dy = 10.0;

	cout << "x is " << ( Compare(x, y) ? "lesser" : "bigger" ) << " than y\n";
	cout << "dx is " << ( Compare(dx, dy) ? "lesser" : "bigger" ) << " than dy\n";
}
```

![](http://i.imgur.com/84Ptrvk.png)

Continuando nosso tema de fazer as mesmas coisas em C, __templates__ não é tão simples, pois não existe de fato na linguagem. Templates são interpretados pelo compilador, que gera um esqueleto de algoritmo que é usado para preencher código de todos os tipos utilizados. Em C isso era feito usando macros. Porém, macros não fazem parte da linguagem C. É apenas uma ferramenta chamada pré-processador que substitui texto antes do programa ser compilado. É através do pré-processador que, por exemplo, os headers são incluídos em um código-fonte. Isso já foi explicado em um [artigo](/os-diferentes-erros-na-linguagem-c) bem velhinho, e mais recentemente em uma [palestra](/entendendo-a-compilacao).

```cpp
// qual o tipo de x e y? qualquer um que faça comparação
#define MACRO(x, y) x < y
```

Eu não recomendaria usar macros em C++, assim como não recomendo em C. Porém, em C é a única opção para reciclar algoritmos de maneira estática. Exceto se você usar ponteiros de função, o que adiciona pouco overhead, mas se perde, assim como a técnica de macro, a informação dos tipos. A própria libc contém uma função, [__qsort__](http://www.cplusplus.com/reference/cstdlib/qsort/), que é "genérica" através do uso de ponteiros sem tipo (void*) e ponteiro de função. A função ordena elementos de uma lista, mas para isso depende da função de comparação que é passada por parâmetro. Essa função recebe dois void* que deve comparar. Além disso, o leiaute na memória tem que ser fixo, contínuo, pois é assim que a função consegue mover os elementos. Ou seja, bem limitado.

![](http://i.imgur.com/3TkGFkN.png)

Dessa forma, não pretendo ensinar a usar "templates" em C, mas a usá-los em C++ com foco em C. Um amigo conhecido de vocês, o [Fernando/DriverEntry](http://driverentry.com.br/), utilizou essa técnica com maestria em alguns códigos kernel-mode que ele desenvolveu, e é uma maneira válida de se aproveitar de uma linguagem mais "alto nível" como C++ em ambientes limitados como o código que trabalha com o S.O.. Como a API do kernel lida com abstrações em C, seus objetos necessariamente não são objetos no sentido C++, mas os famigerados "ponteiros opacos".

Mais sobre isso em um próximo post.
