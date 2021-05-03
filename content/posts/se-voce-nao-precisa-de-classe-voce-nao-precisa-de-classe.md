---
categories:
- draft
- blog
date: 2017-12-17 22:11:40-02:00
title: Se você não precisa de classe você não precisa de classe
---

Nos últimos dias me deparei com o seguinte (pseudo-)código:

```c++
int main(int argc, const char **argv)
{
    MyClass obj;
    HRESULT hr = obj.init();

    if ( SUCCEEDED(hr) )
    {
        if ( args have "cmd1" )
        {
            hr = obj.cmd1();
        }
        else if ( args have "cmd2" )
        {
            hr = obj.cmd2();
        }
        ... // você entendeu a ideia
    }
}
```

Dentro de MyClass a seguinte estrutura:

```c++
class MyClass
{
public:
    HRESULT m_result = S_OK;

    HRESULT init();
    HRESULT cmd1();
    HRESULT cmd2();
    // você pegou a ideia
};
```

Então eu me pergunto: qual a função da classe em um código desses?

Bjarne Stroustrup desde o começo, em seu livro [The C++ Programming Language](https://www.google.com.br/search?q=the+c%2B%2B+programming+language), sugere que C++ não é uma linguagem unicamente orientada a objetos, mas multi-paradigmas. Hoje, em 2017, ela é uma linguagem genérica e até funcional. Na época poderia ser usada como orientada a objetos, mas também como estruturada e imperativa comum. O goto funciona até hoje.

Então o erro no código acima é supor mecanicamente que como é C++ precisa ter classe.

![](https://i.imgur.com/OoGOCOL.jpg)

Não. O código não precisa ter uma classe. No entanto, seu código precisa ter classe. Entendeu?

Ter classe é para poucos. É para programadores que se preocupam com a relação entre funcionalidade, estilo, arquitetura e todos os inúmeros elementos que tornam um código perfeito. Para ser perfeito, um código precisa levar em conta tantos elementos que apenas um programador acordado, obsessivo, fora da matrix, conseguiria observar o que deve ser feito.

Uma pequena sugestão:

```c++
#include <map>

int main(int argc, const char **argv)
{
    MyMap cmds;

    if ( SUCCEEDED(init()) )
    {
        cmds[args]();
    }
}

HRESULT init();
HRESULT cmd1();
HRESULT cmd2();
// você pegou a ideia
```

É a melhor solução? Não. Só uma ideia para tornar o código simples de entender, enxuto para manter, com apenas o modelito básico. Tem até um map para evitar encher de ifs. Mas não precisaria se você tem meia-dúzia de funções.

E note que eu disse funções, não classe. E é possível ter classe sem classes.