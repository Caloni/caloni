---
categories:
- draft
- code
date: '2016-01-12'
title: Classe, objeto, contexto, método, polimorfismo
---

No [post anterior](/classe-objeto-contexto-metodo) implementamos "métodos" em C usando ponteiros de função dentro de structs que eram passadas como parâmetro. Tudo isso embutido por um compilador que gera o que chamamos de instância de uma classe, ou objeto, em C++. Isso é possível graças ao contexto que é passado para uma função (que no caso de C++ é o operador implícito __this__, que sempre existe dentro de um método não-estático).

```cpp
ClasseCpp obj;
obj.Metodo(); // passando this implicitamente

ClasseC obj;
obj.Metodo = ClasseC_Metodo;
obj.Metodo(&obj); // passando this explicitamente
```

Para objetos não-polimórficos, o C++ não precisa mudar essa tabela de funções que os objetos de uma classe contém. No entanto, quando há pelo menos um método virtual, surge a necessidade de se criar a famigerada __vtable__, ou seja, justamente uma tabela de ponteiros de função, que dependem da classe instanciada (base ou algumas das derivadas). Se uma classe derivada sobrescreve um método de alguma classe base, é o endereço desse método que irá existir na _vtable_. Já vimos isso [há muito tempo atrás](/vtable) escovando os bits da vtable direto no assembly e na pilha.

```cpp
#include <iostream>

class MinhaClasse
{
    public:
        void MeuMetodo()
        {
            MeuOutroMetodo();
        }
        virtual void MeuOutroMetodo()
        {
            MinhaPropriedade = 42;
        }
        int MinhaPropriedade;
};

class MinhaClasseVersao75 : public MinhaClasse
{
    public:
        virtual void MeuOutroMetodo()
        {
            MinhaPropriedade = 75;
        }
};

int main()
{
    MinhaClasse obj;
    MinhaClasseVersao75 obj2;

    obj.MeuMetodo();
    obj2.MeuMetodo();

    std::cout << "MinhaPropriedade (obj) = " << obj.MinhaPropriedade << std::endl;
    std::cout << "MinhaPropriedade (obj2) = " << obj2.MinhaPropriedade << std::endl;
}
```

![](http://i.imgur.com/Ye5mA8L.png)

Como você deve imaginar, é possível também fazer isso em C. Basta mudar os endereços das variáveis do tipo ponteiro de função que estão na struct usada como contexto. Para ficar o mais próximo possível do "modo C++" de fazer polimorfirmo, podemos escrever _hardcoded_ a tal _vtable_ para os diferentes tipos de "classe":

```cpp
#include <stdio.h>

struct MinhaVTable;

struct MinhaClasse
{
	const MinhaVTable* VTable;
	int MinhaPropriedade;
};

struct MinhaVTable
{
	void (*MeuMetodo)(MinhaClasse*);
	void (*MeuOutroMetodo)(MinhaClasse*);
};

void MinhaClasse_MeuMetodo(MinhaClasse* pThis)
{
    pThis->VTable->MeuOutroMetodo(pThis);
}

void MinhaClasse_MeuOutroMetodo(MinhaClasse* pThis)
{
    pThis->MinhaPropriedade = 42;
}

void MinhaClasse_MeuOutroMetodoVersao75(MinhaClasse* pThis)
{
    pThis->MinhaPropriedade = 75;
}

static const MinhaVTable g_minhaVTableOriginal = { MinhaClasse_MeuMetodo, MinhaClasse_MeuOutroMetodo };

static const MinhaVTable g_minhaVTableVersao75 = { MinhaClasse_MeuMetodo, MinhaClasse_MeuOutroMetodoVersao75 };

int main()
{
	MinhaClasse obj = { &g_minhaVTableOriginal };
	MinhaClasse obj2 = { &g_minhaVTableVersao75 };

	obj.VTable->MeuMetodo(&obj);
	obj2.VTable->MeuMetodo(&obj2);

	printf("MinhaPropriedade (obj) = %d\n", obj.MinhaPropriedade);
	printf("MinhaPropriedade (obj2) = %d\n", obj2.MinhaPropriedade);
}
```

![](http://i.imgur.com/tRAtU9d.png)

A versão C ainda tem a vantagem de não precisar de uma vtable const (embora seja adequado em situações normais de temperatura e pressão). Os "métodos" poderiam mudar caso algum estado mudasse, alguma exceção fosse disparada, mantendo o mesmo contexto, mas um comportamento (vtable) diferente. Quem utiliza muito essa estratégia é o _kernel_ do Windows, que mexe com estruturas que contém não apenas listas ligadas genéricas, mas funções de _callback_ que não apenas o código da Microsoft precisa chamar, mas os próprios _drivers_ de terceiros que se preocupam com bom comportamento e _guidelines_ que tornam o SO rodando perfeitamente.

![](http://i.imgur.com/k20fqVJ.gif)

O importante deste artigo é demonstrar como conceitos aparentemente complicados ou escondidos de uma linguagem como C++ podem ser compreendidos completamente utilizando apenas linguagem de alto nível no bom e velho C. Essa estratégia de descer camadas de abstração, como verá, funciona para linguagens de mais alto nível, como C# ou Java, pois ambas são implementadas em linguagens como C++. No fundo, engenharia de software é um universo multi-camadas transitando pela última camada que conhecemos -- a física. Pelo menos a última camada que ainda conhecemos.