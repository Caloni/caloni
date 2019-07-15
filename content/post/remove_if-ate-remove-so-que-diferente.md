---
date: "2014-01-21"
title: "remove_if até remove, só que diferente"
categories: [ "blog" ]
---
A surpresa de hoje foi descobrir (vejam só) que o remove_if, como todo algoritmo da STL, deve ser olhado de perto antes de usado. Nesse caso em específico porque, apesar do nome, a função NÃO remove elementos, mas os sobrescreve.

Imagine uma função que usa remove_if para remover todas as idades de potenciais lolitas:

```cpp
void RemoveIfLolita(vector<int>& ages)
{
	remove_if(ages.begin(), ages.end(), &;
}
```

Ou até sua contraparte usando um array C:

```cpp
void RemoveIfLolita(int* ages, int size)
{
	remove_if(ages, ages + size, &;
}
```

Um uso trivial pode não cuspir um resultado trivial, ou seja, os elementos não serão removidos como se espera:

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void RemoveIfLolita(int* ages, int size)
{
	remove_if(ages, ages + size, &;
}

void RemoveIfLolita(vector<int>& ages)
{
	remove_if(ages.begin(), ages.end(), &;
}

int main()
{
	vector<int> ages;

	ages.push_back(10);
	ages.push_back(21);
	ages.push_back(66);
	ages.push_back(18);
	ages.push_back(16);
	ages.push_back(15);
	ages.push_back(8);
	ages.push_back(24);
	ages.push_back(12);
	ages.push_back(20);
	ages.push_back(13);

	RemoveIfLolita(ages);
	cout << "Vector (" << ages.size() << "):\n";
	for_each(ages.begin(), ages.end(), &;

	int newAges[] = { 10, 21, 66, 18, 16, 15, 8, 24, 12, 20, 13, 13 };
	const int newAgesSz = (int) ( sizeof(newAges) / sizeof(int) );
	RemoveIfLolita(newAges, newAgesSz);
	cout << "\n\nArray (" << newAgesSz << "):\n";
	for_each(newAges, newAges + newAgesSz, [&] (int age) { cout << age << endl; } );
}

```

!RemoveIfErrado

Isso ocorre porque o comportamento do remove_if é copiar todos os elementos que retornem false (não remova) e pular elementos que retornem true (remova). No entanto, o tamanho do contêiner, e consequentemente seu ponteiro end(), permanecem o mesmo.

!RemoveIfComportamento

De acordo com o saite cplusplus.com, o algoritmo STL é previsível, simples, e por isso mesmo sujeito a otimizações do compilador:

```cpp
template <class ForwardIterator, class UnaryPredicate>
ForwardIterator remove_if (ForwardIterator first, ForwardIterator last,
	UnaryPredicate pred)
{
	ForwardIterator result = first;
	while (first!=last) {
		if (!pred(*first)) {
			*result = *first;
			++result;
		}
		++first;
	}
	return result;
}

```

Para obtermos qual seria o "novo end()", precisamos obter esse valor do retorno de remove_if. Com base nisso, podemos alterar o tamanho do contêiner ajustado:

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int RemoveIfLolita(int* ages, int size)
{
	auto newEnd = remove_if(ages, ages + size, &;
	return newEnd - ages;
}

void RemoveIfLolita(vector<int>& ages)
{
	auto newEnd = remove_if(ages.begin(), ages.end(), &;
	ages.resize(distance(ages.begin(), newEnd));
}

int main()
{
	vector<int> ages;

	ages.push_back(10);
	ages.push_back(21);
	ages.push_back(66);
	ages.push_back(18);
	ages.push_back(16);
	ages.push_back(15);
	ages.push_back(8);
	ages.push_back(24);
	ages.push_back(12);
	ages.push_back(20);
	ages.push_back(13);

	RemoveIfLolita(ages);
	cout << "Vector (" << ages.size() << "):\n";
	for_each(ages.begin(), ages.end(), &;

	int newAges[] = { 10, 21, 66, 18, 16, 15, 8, 24, 12, 20, 13, 13 };
	int newAgesSz = (int) ( sizeof(newAges) / sizeof(int) );
	newAgesSz = RemoveIfLolita(newAges, newAgesSz);
	cout << "\n\nArray (" << newAgesSz << "):\n";
	for_each(newAges, newAges + newAgesSz, [&] (int age) { cout << age << endl; } );
}

```

!RemoveIfFunciona

Esse C++... intuitivo como nunca!
