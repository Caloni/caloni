---
date: "2011-05-18"
title: Sem reflection
tags: [ "draft", "code" ]
---
Em C++ não temos (ainda) a possibilidade de listarmos, por exemplo, a lista de métodos de um determinado tipo, a fim de chamá-lo pelo nome em tempo de execução. Algo assim:

```cpp
class MyClass
{
public:
        void Method1();
        void Method2();
        void Method3();
};

int main()
{
        MyClass c;
        if( auto m = typeid(c).methods.getaddresof("Method1") )
                m();
}
 

```

OK, foi apenas um exemplo tosco de como seria um reflection em C++.

Porém, existem algumas maneiras de contornar esse problema. A solução, é claro, depende de qual problema você está tentando resolver.

Vamos supor, por exemplo, que você queira cadastrar funções para serem chamadas de maneira uniforme pelo prompt de comando. Vamos chamar nossa classe tratadora de CommandPrompt.

```cpp
typedef void (Method*)(vector<string>& args);

class CommandPrompt
{
public:
        void Add(string name, Method m); // adiciona novo método
        void Interact(ostream& os, istream& is); // começa interação com usuário
};
 

```

Internamente, para armazenar as funções de acordo com o nome dado, basta criarmos um mapeamento entre esses dois tipos e fazemos a amarração necessária para o método principal de parseamento:

```cpp
typedef map<string, Method> MethodList; // uma variável desse tipo armazena todas as funções

void CommandPrompt::Interact(ostream& os, istream& is)
{
        while( is )
        {
                string func;
                vector<string> args;

                if( ParseLine(is, func, args) )
                {
                        // se a função desejada está em nossa lista,
                        // podemos chamá-la, mesmo sem conhecer qual é
                        if( Method m = m_funcs[func] )
                                m(args);
                }
        }
}
 

```

Essa solução não é exatamente um reflection, mas apenas parte do que o verdadeiro reflection possibilita. Existem outras funcionalidades, como traits, que a STL já consegue se virar razoavelmente bem, por exemplo.
