---
date: "2016-01-11"
title: "Classe, objeto, contexto, método"
categories: [ "draft", "code" ]

---
No [post anterior](/classe-objeto-contexto) falamos como a passagem de um endereço de uma struct consegue nos passar o contexto de um "objeto", seja em C (manualmente) ou em C++ (automagicamente pelo operador implícito __this__). Trocamos uma propriedade desse "objeto" em C, mas ainda não chamamos um método.

Hoje faremos isso.

Isso é relativamente simples quando se conhece ponteiros de função, existentes tanto em C quanto em C++. Ponteiros de função são tipos que contém endereço de uma função com assinatura específica (tipo de retorno e de argumentos). Através de um ponteiro de função é possível chamar uma função e passar alguns argumentos. Como o contexto nada mais é que um argumento, será só passá-lo como parâmetro.

```cpp
bool MinhaFuncao(int x, int y)
{
	return x == y;
}

int main()
{
	bool (*PMinhaFuncao)(int, int) = MinhaFuncao;
	PMinhaFuncao(2, 3);
}
```

No exemplo anterior não sabíamos como chamar um método de nosso "objeto" em C:

```cpp
struct MinhaClasse
{
    int MinhaPropriedade;
};

void MinhaClasse_MeuMetodo(MinhaClasse* pThis)
{
   pThis->MinhaPropriedade = 42;
   ///@todo Chamar pThis->MeuOutroMetodo();
}
```

Isso se torna fácil se tivermos uma nova "propriedade" na nossa struct que é um ponteiro para a função que queremos chamar.

```cpp
#include <stdio.h>

struct MinhaClasse
{
	int MinhaPropriedade;
	void (*MeuMetodo)(MinhaClasse*);
	void (*MeuOutroMetodo)(MinhaClasse*);
};

void MinhaClasse_MeuMetodo(MinhaClasse* pThis)
{
	pThis->MeuOutroMetodo(pThis);
}

void MinhaClasse_MeuOutroMetodo(MinhaClasse* pThis)
{
	pThis->MinhaPropriedade = 42;
}

int main()
{
	MinhaClasse obj;

	obj.MinhaPropriedade = 0;

	// precisamos iniciar os "métodos" em C; em C++ é automágico
	obj.MeuMetodo = MinhaClasse_MeuMetodo; 
	obj.MeuOutroMetodo = MinhaClasse_MeuOutroMetodo;

	obj.MeuMetodo(&obj);
    printf("MinhaPropriedade = %d", obj.MinhaPropriedade);
}
```

![](http://i.imgur.com/uzfJuTC.png)

![](http://i.imgur.com/JLJaAsB.png)

Parece muito trabalho para algo que é feito "automagicamente" em C++, certo? Certo. Porém, agora sabemos o que acontece por baixo dos panos em C++ e que pode ser feito em C (ainda que "na mão"). Você provavelmente nunca fará esse tipo de código em C para emular C++, mas o objetivo desse código é entender como funciona, por exemplo, a _vtable_ do C++, que permite polimorfismo.

Mas esse é assunto para outro _post_.
