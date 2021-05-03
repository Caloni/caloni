---
categories:
- code
date: '2014-09-03'
tags:
- draft
title: Shareando Ponteiros
---

Apesar de já ter palestrado algumas vezes sobre Boost e STL, acho que eu nunca escrevi muito sobre esses assuntos no blogue. Acho que o tamanho dessas bibliotecas assusta um pouco. Mas temos que começar de algum lugar, certo? E já que é pra começar, eu gostaria muito de saber de você, programador miserável, que passou poucas e boas nesses 10 anos de padrão 98 brincando com templates quando eles ainda estavam em beta: se fosse para melhorar um aspecto da sua vida de código, qual seria? Qual é aquela coisa que te atormenta como insetos vidrados no seu monitor noite adentro?

Que tal alocação de memória e ponteiros? Vamos matar dois coelhos com um template só?

## A triste realidade do código legado

"Ah, mas tem que usar alguma biblioteca bizarra com milhões de dependências e que vai quebrar todo o fonte aqui da empresa. Sem contar que vai ter que passar de novo pelos unit tests, vai dar erro de compilação, a LIB XPTO não funciona sem dar três pulinhos virado para a cafeteira e..."

Cada caso é um caso, existe o melhor dos mundos e o pior. Mas (quase) todos têm solução. Mesmo que tudo que você tenha disponível seja um bartante e um clipe, podemos tentar alguma mágica/gambiarra/adaptação técnica. Vamos ver os casos mais comuns:

## Aqui no trampo não tem frescura: posso usar C++11 (acho que até 14, 17, 34...), Visual Studio mais novo, Windows 9

Um cenário perfeito para começar. A única coisa que você precisa fazer em seus novos projetos e refatorações é incluir um único cabeçalho:

```cpp
#include <memory>

```

E pronto! Se abriu um mundo mágico onde as alocações serão compartilhadas entre funções sem se perder quem deleta o quê. Não precisa nem checar se o ponteiro é nulo, basta alocar direto e jogar para dentro do nosso mais novo smart pointer da STL:

```cpp
#include <memory>
#include <string>
#include <iostream>

struct Person
{
    Person() { std::cout << "Person created\n"; }
    ~Person() { std::cout << "Person destroyed\n"; }
    std::string name;
    std::string surname;
    int age;
    std::string phone;
};

typedef std::shared_ptr<Person> PersonRef;

PersonRef CreatePerson()
{
    return PersonRef(new Person);
}

void GetName(PersonRef person)
{
    person->name = "Carl";
}

void GetSurName(PersonRef person)
{
    person->surname = "Sagan";
}

void GetAge(PersonRef person)
{
    person->age = 79;
}

void GetPhone(PersonRef person)
{
    person->phone = "+01 042 4242-4242";
}

void PrintPerson(PersonRef person)
{
    std::cout << "Name: " << person->name << " " << person->surname
        << "\nAge: " << person->age
        << "\nPhone: " << person->phone
        << std::endl;
}

void CreateAndPrintPerson()
{
    PersonRef person = CreatePerson();
    GetName(person);
    GetSurName(person);
    GetAge(person);
    GetPhone(person);
    PrintPerson(person);
}

int main()
{
    CreateAndPrintPerson();
}

```

E pronto: você nunca mais vai precisar se preocupar com quem deleta o ponteiro, nem quantas cópias desse ponteiro andam por aí. O shared_ptr da STL, assim como a versão que já tem faz um tempo no boost, mantém um contador de referência para cada cópia do objeto que mantém o mesmo ponteiro "dentro de si". Só quando esse contador chegar a zero, ou seja, não há mais ninguém referenciando essa região da memória, o ponteiro é deletado.

O std::shared_ptr funciona desde o SP1 do Visual Studio 2010. Sem Service Pack ou em versões mais antigas pode haver disponível no namespace tr1, resquício de quando esse novo padrão ainda estava em definição.

## Aqui no trampo vivemos na era pré-jurássica, onde pessoas mais velhas torcem o nariz quando veem um tal de template.

Vou imaginar que você usa o Visual Studio 2003, um dos primeiros da safra ".NET", que, mais uma vez, NÃO TEM QUALQUER RELAÇÃO COM C++ .NET.

Bem, nesse caso, "welcome... to the desert... of the double":

    
    <code>------ Build started: Project: VS2003, Configuration: Debug Win32 ------
    Compiling...
    usando-shared-ptr.cpp
    shared-ptr.cpp(15) : error C2039: 'shared_ptr' : is not a member of 'std'
    shared-ptr.cpp(15) : error C2143: syntax error : missing ';' before '<'
    shared-ptr.cpp(18) : error C2146: syntax error : missing ';' before identifier 'CreatePerson'
    shared-ptr.cpp(18) : error C2501: 'PersonRef' : missing storage-class or type specifiers
    shared-ptr.cpp(20) : error C2064: term does not evaluate to a function taking 1 arguments
    shared-ptr.cpp(20) : warning C4508: 'CreatePerson' : function should return a value; 'void' return type assumed
    shared-ptr.cpp(23) : error C2146: syntax error : missing ')' before identifier 'person'
    shared-ptr.cpp(23) : error C2182: 'GetName' : illegal use of type 'void'
    shared-ptr.cpp(23) : error C2059: syntax error : ')'
    shared-ptr.cpp(24) : error C2143: syntax error : missing ';' before '{'
    shared-ptr.cpp(24) : error C2447: '{' : missing function header (old-style formal list?)
    shared-ptr.cpp(28) : error C2146: syntax error : missing ')' before identifier 'person'
    shared-ptr.cpp(28) : error C2182: 'GetSurName' : illegal use of type 'void'
    shared-ptr.cpp(28) : error C2059: syntax error : ')'
    shared-ptr.cpp(29) : error C2143: syntax error : missing ';' before '{'
    shared-ptr.cpp(29) : error C2447: '{' : missing function header (old-style formal list?)
    shared-ptr.cpp(33) : error C2146: syntax error : missing ')' before identifier 'person'
    shared-ptr.cpp(33) : error C2182: 'GetAge' : illegal use of type 'void'
    shared-ptr.cpp(33) : error C2059: syntax error : ')'
    shared-ptr.cpp(34) : error C2143: syntax error : missing ';' before '{'
    shared-ptr.cpp(34) : error C2447: '{' : missing function header (old-style formal list?)
    shared-ptr.cpp(38) : error C2146: syntax error : missing ')' before identifier 'person'
    shared-ptr.cpp(38) : error C2182: 'GetPhone' : illegal use of type 'void'
    shared-ptr.cpp(38) : error C2059: syntax error : ')'
    shared-ptr.cpp(39) : error C2143: syntax error : missing ';' before '{'
    shared-ptr.cpp(39) : error C2447: '{' : missing function header (old-style formal list?)
    shared-ptr.cpp(43) : error C2146: syntax error : missing ')' before identifier 'person'
    shared-ptr.cpp(43) : error C2182: 'PrintPerson' : illegal use of type 'void'
    shared-ptr.cpp(43) : error C2059: syntax error : ')'
    shared-ptr.cpp(44) : error C2143: syntax error : missing ';' before '{'
    shared-ptr.cpp(44) : error C2447: '{' : missing function header (old-style formal list?)
    shared-ptr.cpp(53) : error C2146: syntax error : missing ';' before identifier 'person'
    shared-ptr.cpp(53) : error C2065: 'person' : undeclared identifier
    shared-ptr.cpp(54) : error C3861: 'person': identifier not found, even with argument-dependent lookup
    shared-ptr.cpp(55) : error C3861: 'person': identifier not found, even with argument-dependent lookup
    shared-ptr.cpp(56) : error C3861: 'person': identifier not found, even with argument-dependent lookup
    shared-ptr.cpp(57) : error C3861: 'person': identifier not found, even with argument-dependent lookup
    shared-ptr.cpp(58) : error C3861: 'person': identifier not found, even with argument-dependent lookup
    VS2003 - 37 error(s), 1 warning(s)
    </code>

Pois é, 37 erros. Depois perguntam por que as pessoas ficam com medo de programar em C++...

Porém, a correção é mais simples do que parece: baixar o [boost](http://www.boost.org/) e trocar o nome do namespace.

```cpp
#include <boost/shared_ptr.hpp>

//...

typedef boost::shared_ptr<Person> PersonRef;

//...

```

_ATENÇÃO! Nos meus testes a única versão funcionando com o VS2003 foi a 1.47. Mas já é alguma coisa_

## Aqui não tem jeito, não. O pessoal olha feio quando usamos classe e a palavra boost é proibida de ser usada no escritório.

Não existe situação difícil que não possa piorar. Porém, mesmo nesse caso ainda há algo a se fazer, já que smart pointer utilizam mecanismos existentes na linguagem C++ desde os primórdios (ou bem próximo disso). Tudo que você precisa para criar seu próprio shared_ptr é do construtor padrão, do destrutor padrão, do construtor de cópia e dos operadores de atribuição e ponteiro. E, claro, não se esqueça de usar template se for permitido. Se não for, a coisa complica, mas não se torna impossível.

```cpp
#pragma once

// Não façam isso em casa! Usem modelo de smart pointers já construídos (como o do boost).
template<typename T>
class shared_ptr
{
public:
	shared_ptr() : m_p(), m_counter()
	{
	}

	shared_ptr(T* p) 
		: m_p(p), m_counter(new int(1)) 
	{
	}

	shared_ptr(const shared_ptr& left)
		: m_p(left.m_p), m_counter(left.m_counter)
	{
		if( m_counter )
			++*m_counter;
	}

	shared_ptr& operator = (const shared_ptr& left)
	{
		if( m_p )
		{
			if( --*m_counter == 0 )
			{
				delete m_counter;
				delete m_p;
				m_counter = 0;
				m_p = 0;
			}
		}
		if( m_counter = left.m_counter )
			++*m_counter;
		m_p = left.m_p;
	}

	~shared_ptr()
	{
		if( --*m_counter == 0 )
		{
			delete m_counter;
			delete m_p;
			m_counter = 0;
			m_p = 0;
		}
	}

	T* operator -> ()
	{
		return m_p;
	}

private:
	int* m_counter;
	T* m_p;
};

```

```cpp
#include "shared_ptr.h"

//...

typedef shared_ptr<Person> PersonRef;

//...

```

E é isso. A lição de hoje é: quem quer, arruma um jeito. Quem não quer, uma desculpa.