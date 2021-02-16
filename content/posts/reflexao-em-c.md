---
date: "2008-06-30"
title: Reflexão em C++
tags: [ "draft", "code" ]
---
O termo e conceito de "[_reflection_](http://en.wikipedia.org/wiki/Reflection_(computer_science))" ([reflexão](http://pt.wikipedia.org/wiki/Reflex%C3%A3o_%28programa%C3%A7%C3%A3o%29)), muito usado em linguagens modernas, é a capacidade de um programa de observar e até de alterar sua própria estrutura. Bom, isso você pode ler na Wikipédia. O interessante é o que podemos usar desse conceito na linguagem C++.

Infelizmente não muito.

O sistema de **RTTI** (_Run Time Type Identification_), a identificação de tipos em tempo de execução, seria o começo do _reflection _em C++. Foi um começo que não teve meio nem fim, mas existe na linguagem. Dessa forma podemos tirar algum proveito disso.

Um leitor pediu para que eu falasse um pouco sobre essas coisas, especificamente como se faz para obter o nome da classe de onde estamos executando um determinado método. Para esse tipo de construção podemos usar o operado **typeid**, que retorna informações básicas sobre um tipo de acordo com um tipo, instância ou expressão:

```cpp
#include <iostream>

using namespace std;

int main()
{
	cout << typeid( int ).name() << endl;

	int x;
	cout << typeid( x ).name() << endl;

	cout << typeid( 2 + 2 ).name() << endl;
}

 

```

    
    C:\Tests>cl typeid.cpp
    Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 15.00.21022.08 for 80x86
    Copyright (C) Microsoft Corporation.  All rights reserved.
    
    /out:typeid.exe
    typeid.obj
    
    C:\Tests>typeid.exe
    int

Dessa forma, podemos nos aproveitar do fato que todo método não-estático possui a variável implícita **this**, do tipo "ponteiro constante para T", onde T é o tipo da classe que contém o método sendo chamado.

```cpp
#include <iostream>

using namespace std;

class MyClass
{
	public:
		void MyMethod()
		{
			cout << typeid(*this).name() << "::MyMethod" << endl;
		}
};

int main()
{
	MyClass myc;

	myc.MyMethod();
}

 

```

    
    C:\Tests>cl typeid-class.cpp
    Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 15.00.21022.08 for 80x86
    Copyright (C) Microsoft Corporation.  All rights reserved.
    
    /out:typeid-class.exe
    typeid-class.obj
    
    C:\Tests>typeid-class.exe

class MyClass::MyMethod

Com classes não-polimórficas a coisa parece não ter muita utilidade. No entanto, essa mesma técnica pode ser aplicada em classes derivadas, uma vez que o operador typeid pode trabalhar em tempo de execução:

```cpp
#include <iostream>

using namespace std;

class MyClass
{
	public:
		virtual void MyMethod()
		{
			cout << typeid(*this).name() << "::MyMethod" << endl;
		}
};

class MyDerivatedClass1 : public MyClass { };

class MyDerivatedClass2 : public MyClass { };

int main()
{
	MyClass* myc1 = new MyDerivatedClass1;
	MyClass* myc2 = new MyDerivatedClass2;

	myc1->MyMethod();
	myc2->MyMethod();
}

 

```

    
    C:\Tests>cl typeid-class2.cpp
    Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 15.00.21022.08 for 80x86
    Copyright (C) Microsoft Corporation.  All rights reserved.
    
    /out:typeid-class2.exe
    typeid-class2.obj
    
    C:\Tests>typeid-class2.exe

class MyDerivatedClass1::MyMethod class MyDerivatedClass2::MyMethod

Apenas se lembre de ter de fato uma classe polimórfica (eu consegui isso tornando MyMethod uma função virtual). Do contrário você pode [ter problemas](http://www.caloni.com.br/typeid-e-os-perigos-do-nao-polimorfismo).
