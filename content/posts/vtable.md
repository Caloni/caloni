---
date: "2011-03-01"
title: VTable
categories: [ "draft", "code" ]
---
Acho que na breve história desse blogue nunca contei a história do vtable. No máximo fizemos um [hookzinho nos métodos de um componente COM](http://www.caloni.com.br/hook-de-com-no-windbg). Mas só.

Não encontro uma analogia simples, assim, de cabeça. Então vou contar no cru, mesmo. Talvez seja até mais divertido.

A vtable foi um mecanismo criado para implementar o polimorfismo em C++ quando falamos de ponteiros para classes base cujos métodos virtuais foram sobrescritos por uma classe derivada.

A coisa fica mais simples quando explicamos que em C++ você só paga pelo que usa. Se você declarar uma classe que não tenha nenhum método virtual, os objetos dessa classe não precisarão de uma vtable. No entanto, você não conseguirá sobrescrever um método dessa classe através de uma derivada:

```cpp
#include <iostream>

class C
{
public:
        void method()
	{
		std::cout << "C::method\n";
	}
};

class D : public C
{
public:
        void method()
	{
		std::cout << "D::method\n";
	}
};

void func(C* c)
{
        c->method(); 
}

int main()
{
        D d;
        func(&d); // passa endereço de C "dentro de D"
}

 

```

    
    Saída
    =====

    
    C::method

No exemplo acima, a chamada feita em func irá chamar o método da classe C, mesmo que a classe D tenha sobrescrito esse método. O programador semi-experiente deve pensar "lógico, ela não é virtual!", e está certo, assim como qualquer pessoa que decora essas formulazinhas de vestibular.

Para criarmos polimorfismo de verdade, precisamos declarar o método em C como virtual:

    
    class C
    {
    public:
            virtual void method();
    };

Agora sim, a chamada em func irá ser para D::method.

Pergunte para o programador semi-experiente em C++ por que as coisas são assim e provavelmente ele irá falar algo sobre vtable, mesmo que não saiba exatamente como ela funciona.

A vtable é uma tabela que guarda o endereço dos métodos virtuais de uma classe. Se uma classe derivada sobrescrever um ou mais métodos de sua classe base, ela terá uma outra vtable com os endereços dos métodos "corrigidos".

[![](http://i.imgur.com/Ye5mA8L.png)](/images/vtable11.png)

Dessa forma, algo um pouco diferente ocorre na chamada c->method() quando estamos lidando com classes polimórficas: o início de um objeto dessa classe terá um ponteiro para a vtable de sua classe. Quando um método virtual é chamado, em vez do compilador gerar uma chamada estática para o endereço do método da classe cujo tipo estamos usando, ele irá redirecionar essa chamada para uma posição na vtable para onde esse objeto aponta. No caso de um objeto do tipo D, a entrada para method em sua vtable apontará não para C::method, mas para D::method, uma função com a mesma assinatura contida na classe base C e que, portanto, a sobrescreve.

Façamos um pequeno teste para comprovar o que falamos. Vamos escancarar a chamada feita a partir de uma instância de D e a partir de uma instância de C. Nada que um WinDbg não resolva de braços cruzados:

    
    int main()
    {
            D d;
            C c;
    
            func(&d);
            func(&c);
    }

    
    cl /Zi vtable3.cpp
    windbg vtable3.exe

[![vtable2.png](http://i.imgur.com/9408xv1.png)](/images/vtable2.png)
