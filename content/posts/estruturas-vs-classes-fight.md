---
date: "2014-05-20"
title: "Estruturas VS Classes: fight!"
tags: [ "draft", "code" ]
---
[![EpicRapBattleStructVcClass](http://i.imgur.com/0uar0i8.jpg)](/images/14250890913_37a06bf7a2_o.jpg)

Uma dúvida besta e importante ao mesmo tempo que muitos iniciantes em C++ possuem é saber qual a diferença entre um objeto declarado como _class_ e um objeto declarado como _struct_. A causa dessa dúvida é uma linguagem que se derivou de outra (C) que não possuía classes, e portanto criou a palavra-chave _class_ para "ficar bonito", pois, na prática, não muda muita coisa. Tomemos como exemplo o código mais simples de todos:

```cpp
struct MinhaEstrutura
{
};

class MinhaClasse
{
};

int main()
{
    MinhaEstrutura me;
    MinhaClasse mc;
}

```

Ele compila e roda sem problemas:

[![StructVsClass](http://i.imgur.com/APlOm65.jpg)](/images/14230192924_fd9c2fb490_z.jpg)

"Estruturalmente" falando, **MinhaEstrutura** e **MinhaClasse** são idênticas, pois são os detalhes de sintaxe que diferem, e diferem pouco. Abrindo o jogo, a única diferença que poderá ser sentida em usar um ou outro é que **structs possuem seus membros públicos por padrão e classes possuem seus membros privados por padrão**. Apenas isso. O resto, nada muda.

Isso pode ser visto quando adicionamos um construtor para nossos tipos de teste:

```cpp
struct MinhaEstrutura
{
    MinhaEstrutura() {}
};

class MinhaClasse
{
    MinhaClasse() {}
};

int main()
{
    MinhaEstrutura me;
    MinhaClasse mc;
}

```

[![StructVsClass-Construtor](http://i.imgur.com/vwpucpm.jpg)](/images/14230273964_89e37e2487_z.jpg)

Antes não havia problemas para **MinhaClasse** porque o construtor padrão criado para ela é público por default. Porém, explicitando no código um construtor e deixando sua privacidade ligada por padrão temos esse erro que NÃO ocorre em **MinhaEstrutura**.

Mas, então, posso criar todas minhas classes usando a palavra-chave struct?

Isso mesmo! Nada lhe obriga tecnicamente a usar class. Porém, assim como nada lhe obriga a usar uma linha para cada comando na linguagem ¿ afinal, todos poderiam estar na mesma linha separados por ponto-e-vírgula ¿ o uso da palavra _struct_ para classes no sentido de "objetos que possuem inteligência, métodos, herança, polimorfismo e outras firulas" não se enquadra nas boas práticas dos programadores C++.

Geralmente uma _struct_ é uma forma de concatenar tipos primitivos e só. Algumas liberdades além disso geralmente são permitidas, mas desencorajadas, como um construtor que inicia os membros da _struct_ com valores-default.

```cpp
#include <iostream>

struct MinhaEstrutura
{
    MinhaEstrutura()
    {
        x = 0;
        y = 2;
        c = 'C';
    }

    int x;
    int y;
    char c;
};

int main()
{
    MinhaEstrutura me;
    std::cout << "x: " << me.x << ", y: " << me.y << ", c: " << me.c << std::endl;
}

```

[![StructVsClassStructConstructor](http://i.imgur.com/rdpllNf.jpg)](/images/14207416246_60675f681a_z.jpg)

E, por que não, uma sobrecarga do operador de stream para imprimirmos diretamente os valores de **MinhaEstrutura** para a saída com apenas um comando?

```cpp
#include <iostream>

struct MinhaEstrutura
{
    MinhaEstrutura() { x = 0; y = 2; c = 'C'; }
    int x; int y; char c;
};

std::ostream& operator << (std::ostream& os, const MinhaEstrutura& me)
{
    std::cout << "x: " << me.x << ", y: " << me.y << ", c: " << me.c;
    return os;
}

int main()
{
    MinhaEstrutura me;
    std::cout << me << std::endl;
}

```

[![StructVsClassStreams](http://i.imgur.com/np4trf9.jpg)](/images/14043966560_422ae353d9_z.jpg)

Enfim, não há nenhum limite que se aplica à uma _struct_ além do bom senso. A criação da palavra _class_ não foi por falta do que fazer. Ela diz claramente que estamos definindo um objeto que contém usos mais adequados à orientação a objetos de C++ do que a programação estruturada de C, e vice-versa. É uma forma de tornar o código mais legível, mas nada do outro mundo. Sabemos, no final das contas, que o compilador trata as duas (quase) da mesma maneira.

Qual será a próxima batalha épica? Você escolhe!

https://www.youtube.com/watch?v=zn7-fVtT16k

