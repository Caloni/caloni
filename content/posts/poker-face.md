---
categories:
- code
date: '2014-05-06'
tags:
title: Poker Face
---

O segundo round da segunda fase do Code Jam passou nesse sábado. Disléxico que sou, consegui fazer apenas 8 pontos ¿ como todo mundo ¿ no teste small do problema B, que envolvia apenas dois loops aninhados (a versão large fica para outro post). Na verdade, estou aqui para expressar minha gratidão ao campeonato por ter aprendido mais uma bela lição vendo o código do primeiro colocado do primeiro round, vulgo [Kaizero](https://code.google.com/codejam/contest/2984486/scoreboard?c=2984486#vf=1), um coreano que deu uma solução simples, rápida e prática para um problema de probabilidade tão error-prone que até os juízes do Google deram uma lambuja de alguns testes errados (sem contar que houve apenas a categoria small), e me fez pensar em quantas vezes pensamos em demasiado tentando encontrar a solução perfeita para algo que simplesmente... não precisa.

Basta um hack e [commit](http://pcottle.github.io/learnGitBranching/?NODEMO&defaultTab=remote&command=levels).

## É a incerteza, idiota!

![Poker Jam](http://i.imgur.com/LmkKDXm.jpg)

O problema reza que existem dois algoritmos para embaralhar uma sequência numérica (de 0 a N): o bom e o ruim. Ambos traçam um loop do iníco ao fim pegando aleatoriamente um elemento da lista e trocando de lugar com o elemento que está sendo varrido no momento.

![ProperShuffle](http://i.imgur.com/UTQPIST.jpg)

A diferença entre o bom e o ruim é que o bom pega aleatoriamente apenas os elementos DEPOIS do elemento que está sendo varrido, enquanto o algoritmo ruim pega qualquer um dos elementos SEMPRE. Isso aparentemente e intuitivamente não parece interferir na aleatoriedade do embaralhamento, mas se levarmos ao extremo de embaralhar repetidas vezes somando a lista resultante percebemos uma tendência gritante do algoritmo ruim em manter o ordenamento inicial, ou pelo menos na média sempre tender para números menores no início e números maiores no fim, como pode ser visto nesse teste que fiz, gerado pelo Excel:

![Gráfico dos Algoritmos de Embaralhamento](http://i.imgur.com/OL0hpLv.jpg)

O que eu tentei fazer durante meu fim-de-semana retrasado e o feriado foi encontrar um detector de aleatoriedade (aliás, encontrei um bem interessante chamado [ent](http://www.fourmilab.ch/random/)), tanto "na mão" quanto pesquisando. O que eu não imaginava foi que o teste que eu tinha feito no início usando uma simples planilha Excel era a solução óbvia (naquelas de é óbvio só depois que você vê). E foi essa a solução adotada por Kaizero.

```
/** @author Kaizero
@desc Versão comentada (em português) e desofuscada do código do 
Code Jam 2014, 1A, problema 3 (Proper Shuffle)
por Wanderley Caloni (wanderley@caloni.com.br).
*/
#pragma warning(disable:4996) // warning, pra que te quero...
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<time.h>

using namespace std;

// as variáveis monossilábicas...
int w[1001], C[1001][1001], O[1001];

// Note que uma delas (C) é uma tabela gigantesca:

// 1     2    3     4   ...  1001
// 2
// 3
// ...
// 1001

// tabela verdade?
bool v[1001];

struct A
{	
	int ord, R;

	bool operator <(const A &p)const
	{
		return R < p.R;
	}
}
p[1000];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int i, TC, T, n, j;

	srand((unsigned)time(NULL)); // mexendo o saco de bingo...

	// a parte mais demorada: construir um contador gigante estilo 
	// Excel com 3 milhões de iterações
	for (i = 0; i < 3000000; i++)
	{
		// 1. Preenchemos o array sequencial.
		for (j = 0; j < 1000; j++)
		{
			w[j] = j;
		}

		// 2. Realizamos o algorimo ruim.
		for (j = 0; j < 1000; j++)
		{
			swap(w[j], w[rand() % 1000]);
		}

		// 3. Pesamos o resultado do algoritmo ruim.
		for (j = 0; j < 1000; j++)
		{
			C[j][w[j]]++;
		}
	}

	// agora a parte "fácil"...

	// ler número de casos de teste (sempre 120)
	scanf("%d", &TC);
	for (T = 1; T <= TC; T++) // iterar por cada linha
	{
		scanf("%d", &n);
		p[T].ord = T; // guardando sua posição

		// lendo os números de todos os casos
		for (i = 0; i < n; i++)
		{
			scanf("%d", &O[i]);
			p[T].R += C[i][O[i]]; // mas gravando o peso de cada posição (cálculo de 3M)
		}
	}

	// ordenando pelo peso de cada posição
	sort(p + 1, p + TC + 1);
	for (i = 1; i <= 60; i++)
		v[p[i].ord] = true; // metade tem que ser bom (a melhor metade)

	for (i = 1; i <= TC; i++)
	{
		printf("Case #%d: ", i);
		if (v[i])printf("GOOD\n");
		else printf("BAD\n");
	}
}

```

O que ele basicamente faz é acumular os resultados de três milhões de embaralhamentos feitos pelo algoritmo ruim e inferir através dos resultados que metade é bom e metade é ruim. O ruim fica do lado desbalanceado da sequência.

![Tabelona](http://i.imgur.com/oe3heEP.jpg)

Tão óbvio, tão simples, tão elegante.
