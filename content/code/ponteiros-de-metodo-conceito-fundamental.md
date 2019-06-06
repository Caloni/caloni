---
date: "2007-11-05"
title: 'Ponteiros de método: conceito fundamental'
categories: [ "code" ]
---
[![Arrow Pointer](http://i.imgur.com/uIttDdG.jpg)](/images/arrow-pointer.jpg)Diferente de ponteiros de função (funções globais ou estáticas) - que são a grosso modo ponteiros como qualquer um - os ponteiros de método possuem uma semântica toda especial que costuma intimidar até quem está acostumado com a aritmética de ponteiros avançada. Não é pra menos: é praticamente uma definição à parte, com algumas limitações e que deixa a desejar os quase sempre criativos programadores da linguagem, que vira e mexe estão pedindo mudanças no [C++0x](http://www.artima.com/cppsource/cpp0x.html).

Três regras iniciais que devem ser consideradas para usarmos ponteiros para métodos são:

    
  * A semântica para lidar com ponteiros de método é **totalmente diferente** de ponteiros de função.

    
  * Ponteiros de método de classes distintas **nunca** se misturam.

    
  * Para chamarmos um ponteiro de método precisamos sempre de um **objeto da classe** para a qual ele aponta.

Visto isso, passemos a um exemplo simples, um chamador de métodos aleatórios, que ilustra o princípio básico de utilização:

```cpp
#include <windows.h>
#include <iostream>
#include <time.h>

using namespace std;

// declaramos que existe uma classe com esse nome
class FuzzyCall;

// ponteiro para métodos da classe acima
typedef void (FuzzyCall::*FP_Fuzzy)();

/** Classe que faz chamada de um método aleatório. */
class FuzzyCall
{
public:

	FuzzyCall()
	{
		srand(GetTickCount()); // chacoalha o saco de bingo
	}

   FP_Fuzzy GiveMeAMethod() { return m_methods[rand() % 3]; }

private:
	void MethodOne()   { cout << "One!\n"; }
	void MethodTwo()   { cout << "Two!\n"; }
	void MethodThree() { cout << "Three!\n"; }

	static FP_Fuzzy m_methods[3];
};

/** Array com os métodos que podem ser chamados aleatoriamente. */
FP_Fuzzy FuzzyCall::m_methods[3] = { &MethodOne, &MethodTwo, &MethodThree };

/** Recebe um ponteiro para um método de FuzzyCall e chama com um objeto local. */
void passThrough(FP_Fuzzy pMethod)
{
	FuzzyCall fuzzyObject; // esse é o objeto local
	( fuzzyObject.*pMethod )(); // essa é a chamada
}

/** No princípio Deus disse: 'int main!'
*/
int main()
{
	FuzzyCall fuzzyObject1;
	FP_Fuzzy pMethod;

	// pegamos um método da classe qualquer
	pMethod = fuzzyObject1.GiveMeAMethod();

	// e passamos para uma outra função
	passThrough(pMethod);
} 

```

Como podemos ver, para o _typedef_ de ponteiros de método é necessário especificar o escopo da classe. Com isso o compilador já sabe que só poderá aceitar endereços de métodos pertencentes à mesma classe com o mesmo protótipo.

Na hora de atribuir, usamos o operador de endereço e o nome do método (com escopo, se estivermos fora da classe). É importante notar que, diferente de ponteiros de função, o operador de endereço é obrigatório. Do contrário:

    
    error C4867: 'FuzzyCall::MethodOne': function call missing argument list;
    use '&FuzzyCall::MethodOne' to create a pointer to member

E, por fim, a chamada. Como é a chamada de um método, é quase intuitiva a necessidade de um objeto para chamá-la. Do contrário não teríamos um this para alterar o objeto em qualquer método não-estático, certo? Daí a necessidade do padrão C++ especificar dois operadores especialistas para esse fim, construídos a partir da combinação de operadores já existentes em C:

```cpp
FuzzyCall fuzzyObject; // esse é o objeto local
FuzzyCall* pFuzzy = &fuzzyObject; // ponteiro para esse mesmo objeto

( fuzzyObject.*pMethod )(); // [objeto] .* [ponteiro de método]
( fuzzyObject->*pMethod )(); // [ponteiro para objeto] ->* [ponteiro de método] 

```

Esses operadores obrigam o programador a sempre ter um objeto e um ponteiro. Daí não tem como errar. Infelizmente, devido à ordem de precedência, temos que colocar os parênteses em torno da expressão para chamar o método. Pelo menos fica equivalente ao que precisávamos fazer antes da padronização da linguagem C.
