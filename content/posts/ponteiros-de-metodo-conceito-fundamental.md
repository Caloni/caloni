---
date: "2007-11-05"
title: "Ponteiros de método: conceito fundamental"
tags: [ "code" ]
---
Diferente de ponteiros de função globais ou estáticas, que são a grosso modo ponteiros como qualquer um, os ponteiros de método possuem uma semântica toda especial que costuma intimidar até quem está acostumado com a aritmética de ponteiros avançada. Não é pra menos: é praticamente uma definição à parte, com algumas limitações e que deixa a desejar os quase sempre criativos programadores da linguagem, que vira e mexe estão pedindo mudanças no C++0x.

Três regras iniciais que devem ser consideradas para usarmos ponteiros para métodos são:

 - A semântica para lidar com ponteiros de método é totalmente diferente de ponteiros de função.
 - Ponteiros de método de classes distintas nunca se misturam.
 - Para chamarmos um ponteiro de método precisamos sempre de um objeto da classe para a qual ele aponta.

Visto isso, passemos a um [exemplo simples], um chamador de métodos aleatórios, que ilustra o princípio básico de utilização:

    #include <iostream>
    #include <time.h>
    
    class Rand;
    
    typedef void (Rand::*FP)();
    
    class Rand
    {
      public:
        Rand()
        {
          srand(time(NULL));
        }
    
        FP GiveMeFunc()
        {
          return m_funcs[rand() % 3];
        }
    
      private:
        void FuncOne()   { std::cout << "One!\n"; }
        void FuncTwo()   { std::cout << "Two!\n"; }
        void FuncThree() { std::cout << "Three!\n"; }
    
        static FP m_funcs[3];
    };
    
    FP Rand::m_funcs[3] = { &FuncOne, &FuncTwo, &FuncThree };
    
    void passThrough(FP fp)
    {
      Rand r;
      ( r.*fp )(); // <<-- this
    }
    
    /** No princípio Deus disse:
      'int main!'
     */
    int main()
    {
      Rand r;
      FP fp;
    
      fp = r.GiveMeFunc();
      passThrough(fp);
    }

Como podemos ver, para o typedef de ponteiros de método é necessário especificar o escopo da classe. Com isso o compilador já sabe que só poderá aceitar endereços de métodos pertencentes à mesma classe com o mesmo protótipo. Na hora de atribuir, usamos o operador de endereço e o nome do método (com escopo, se estivermos fora da classe). É importante notar que, diferente de ponteiros de função, o operador de endereço é obrigatório. Do contrário:
    
    error C4867: 'Rand::FuncOne': function call 
    missing argument list; use '&Rand::FuncOne' 
    to create a pointer to member

E, por fim, a chamada. Como é a chamada de um método, é quase intuitiva a necessidade de um objeto para chamá-la. Do contrário não teríamos um this para alterar o objeto em qualquer método não-estático, certo? Daí a necessidade do padrão C++ especificar dois operadores especialistas para esse fim, construídos a partir da combinação de operadores já existentes em C:

    Rand r;
    Rand* pr = &r;

    // [obj] .* [method ptr]
    ( r.*pMethod )();

    // [obj ptr] ->* [method ptr] 
    ( pr->*pMethod )();

Esses operadores obrigam o programador a sempre ter um objeto e um ponteiro. Daí não tem como errar. Infelizmente, devido à ordem de precedência, temos que colocar os parênteses em torno da expressão para chamar o método. Pelo menos fica equivalente ao que precisávamos fazer antes da padronização da linguagem C.

[exemplo simples]: /code/member_pointer.cpp
