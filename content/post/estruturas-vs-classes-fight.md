---
categories: [ "code" ]
date: "2014-05-20"
tags: [ "draft",  ]
title: "Estruturas VS Classes: fight!"
---

Uma dúvida besta e importante ao mesmo tempo que muitos iniciantes em C++ possuem é saber qual a diferença entre um objeto declarado como class e um objeto declarado como struct. A causa dessa dúvida é uma linguagem que se derivou de outra (C) que não possuía classes, e portanto criou a palavra-chave class para "ficar bonito", pois, na prática, não muda muita coisa. Tomemos como exemplo o código mais simples de todos:

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
    

Ele compila e roda sem problemas:

"Estruturalmente" falando, MinhaEstrutura e MinhaClasse são idênticas, pois são os detalhes de sintaxe que diferem, e diferem pouco. Abrindo o jogo, a única diferença que poderá ser sentida em usar um ou outro é que structs possuem seus membros públicos por padrão e classes possuem seus membros privados por padrão. Apenas isso. O resto, nada muda.

Isso pode ser visto quando adicionamos um construtor para nossos tipos de teste:

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
    

Antes não havia problemas para MinhaClasse porque o construtor padrão criado para ela é público por default. Porém, explicitando no código um construtor e deixando sua privacidade ligada por padrão temos esse erro que NÃO ocorre em MinhaEstrutura.

Mas, então, posso criar todas minhas classes usando a palavra-chave struct?

Isso mesmo! Nada lhe obriga tecnicamente a usar class. Porém, assim como nada lhe obriga a usar uma linha para cada comando na linguagem ¿ afinal, todos poderiam estar na mesma linha separados por ponto-e-vírgula ¿ o uso da palavra struct para classes no sentido de "objetos que possuem inteligência, métodos, herança, polimorfismo e outras firulas" não se enquadra nas boas práticas dos programadores C++.

Geralmente uma struct é uma forma de concatenar tipos primitivos e só. Algumas liberdades além disso geralmente são permitidas, mas desencorajadas, como um construtor que inicia os membros da struct com valores-default.

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
    

E, por que não, uma sobrecarga do operador de stream para imprimirmos diretamente os valores de MinhaEstrutura para a saída com apenas um comando?

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
    

Enfim, não há nenhum limite que se aplica à uma struct além do bom senso. A criação da palavra class não foi por falta do que fazer. Ela diz claramente que estamos definindo um objeto que contém usos mais adequados à orientação a objetos de C++ do que a programação estruturada de C, e vice-versa. É uma forma de tornar o código mais legível, mas nada do outro mundo. Sabemos, no final das contas, que o compilador trata as duas (quase) da mesma maneira.

Qual será a próxima batalha épica? Você escolhe!

https://www.youtube.com/watch?v=zn7-fVtT16k

