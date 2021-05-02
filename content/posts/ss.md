---
date: "2014-06-03"
title: SS
categories: [ "draft", "code" ]
---
Uma das coisas mais cretinas e difíceis para os iniciantes em C++ é conseguir formatar strings de maneira fácil, rápida e indolor. Infelizmente, a biblioteca de printf da linguagem C está fechada para reforma, pois ela é extremamente error-prone e não-intuitiva. Porém, se a printf é não-intuitiva, o que dizer < < daqueles << sinais << de << flechinhas apontando para cout? Bem melhor, não?

```cpp
#include <iostream>

int main()
{
    int x = 0x00000001;
    int y = 4;
    int z = x << y; // isso desloca 4 bits para a "esquerda"
    std::cout << z // WHAT??
        << "\nestranho..." << std::endl; // WHAT^^2!?!?!?!??!?!
}

```

[![ShiftEstranho](http://i.imgur.com/tnVztzy.png)](/images/14330337121_409bbee4f7_o.png)

A resposta é, pra variar, depende. Se você combinar com seu cérebro que o operador de shift que você aprendeu em C para cout não tem a mesma semântica, OK. No fundo eu acredito que os criadores dessa sobrecarga de operador pensaram sinceramente que hoje em dia quase ninguém conhece os operadores de shift binário, então tudo bem reaproveitá-lo de uma maneira mais miguxa.

Porém, isso depende da maneira com que você usa streams C++. Vai haver momentos de sua vida que você vai se questionar por que tiraram todo o controle, a elegância e simplicidade de um bom printf, quando os [homens eram homens](http://www.caloni.com.br/programadores-de-verdade-nao-usam-java) e sabiam configurar jumpers para instalar a nova placa EISA.

```cpp
#include <iostream>
#include <stdlib.h>

int main()
{
    int x = 0x00AB3451;
    printf("int x = 0x%08X;\n", x); // nao eh tao legivel, mas da conta do recado
    std::cout << "int x = 0x" << std::hex << x << ";" << std::endl; // pois eh, parece que melhoramos mesmo com streams...
}

```

[![Formatação Difícil do Cout](http://i.imgur.com/7hFREwa.png)](/images/14353868563_a2588b266c_o.png)

## A coisa mais fácil do jeito mais difícil

A questão dos streams fica mais complicada quando precisamos realizar atividades corriqueiras no código, como retornar uma string formatada, ou até mesmo transformar um inteiro em string.

```cpp
#include <iostream>
#include <string>
#include <sstream> // digam oi para nosso novo amiguinho!

std::string FuncaoCorriqueira(int x, int y)
{
    std::ostringstream ss; // credo, que tipo eh esse?
    ss << (x + y);
    return ss.str();
}

int main()
{
    std::cout << FuncaoCorriqueira(20, 42);
}

```

Já pensou termos que criar uma função dessas sempre que quisermos converter números em string? Ou pior, ter que fazer o que fizemos dentro dessa função: declarar um ostringstream (um cout com buffer interno de string), usá-lo como cout e obter seu buffer interno através do método str. Tudo isso para converter um número para string.

Quando uma tarefa muito comum exige mais de dois passos para ser realizada é de bom tom criarmos algum código reutilizável, certo? Um código que trará de uma vez por todas a solução final!

## SS

```cpp
#include <sstream>

struct ss
{
    template<typename T>
    ss& operator << (const T& t)
    {
        _ss << t; 
        return *this;
    }
    
    operator std::string ()
    { 
        return _ss.str();
    }

    std::ostringstream _ss;
};

```

O código acima serve bem ao nosso propósito de formatar strings em uma linha como um cout, mas retornar uma string no lugar. Ele é simples, ele é direto, ele tem defeitos que não vem ao caso (como não suportar endl), mas pode ser usado de maneira... simples e direta!

```cpp
#include "ss.h"
#include <iostream>

int main()
{
    for( int i = 0; i < 5; ++i )
    {
        std::string s = ss() << "Teste numero " << i;
        std::cout << s << std::endl;
    }
}

```

OK, o código de exemplo foi idiota, mas você pegou a ideia. Tudo que precisamos fazer para reutilizar essa pequena classe é definí-la (ss() resolve) e usá-la. Seu conversor de string retorna o buffer interno de ostringstream para nós como num passe de mágica.

_Obs.: Com certeza deve existir uma centena de bibliotecas que implementam algo do gênero, só que melhor. Essa é a típica fica isolante para continuar trabalhando._

