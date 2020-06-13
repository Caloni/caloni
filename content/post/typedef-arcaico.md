---
categories: [ "code" ]
date: "2010-04-20"
tags: [ "draft",  ]
title: "Typedef arcaico"
---
A API do Windows geralmente prima pela excelência em maus exemplos. A Notação Húngara e o Typedef Arcaico são duas técnicas que, por motivos históricos, são usados a torto e a direito pelos códigos de exemplo.

Já foi escrito muita coisa sobre os prós e contras da notação húngara. Já o typedef arcaico, esse pedacinho imprestável de código, ficou esquecido, e hoje em dia traz mais dúvidas na cabeça dos principiantes em C++ do que deveria. Para tentar desobscurecer os mitos e fatos, vamos tentar explicar o que significa essa construção tão atípica, mas comum no dia-a-dia.

Vejamos um exemplo típico desse pequeno Frankenstein semântico:

    
    typedef struct _MINHASTRUCT {
       int x;
       int y;
    }
    MINHASTRUCT, *LPMINHASTRUCT;

Bom, eu nem sei por onde começar. Talvez pelo conceito de typedef.

Um typedef, basicamente, é um apelido. Você informa um tipo e define "outro tipo".

    
    typedef tipo apelido;

O tipo é tudo que fica entre o typedef e o novo nome, que deve ser um identificador válido na linguagem. Por exemplo, a empresa onde trabalho fez um typedef informal do meu nome:

    
    typedef Wanderley Caloni Wandeco;

Se, futuramente, eu sair da empresa e entrar outro "Wanderley alguma-coisa", será possível usar o apelido novamente, bastando alterar o typedef:

    
    typedef Wanderley Cardoso Wandeco;

> Bom, "outro tipo" é forma de dizer. Isso é uma descrição errônea em muitos livros. De fato, o compilador enxerga o mesmo tipo com outro nome, daí chamarmos o typedef de apelido, mesmo.

    /** @file dois_apelidos.cpp */
    #include <iostream>
    
    using namespace std;
    
    struct Struct
    {
       int x;
       int y;
    };
    
    typedef Struct Struct1;
    typedef Struct Struct2;
    
    int main()
    {
       Struct1 s1;
       Struct2 s2;
    
       cout << typeid(s1).name() << endl;
       cout << typeid(s2).name() << endl;
    }
 

    C:\Tests>cl /EHsc dois_apelidos.cpp
    ...
    /out:dois_apelidos.exe
    dois_apelidos.obj
    
    C:\Tests>dois_apelidos.exe
    
    struct Struct struct Struct

Tipos simples são fáceis de entender porque possuem seus símbolos no mesmo lugar:

    int x;
    char c;
    long p;

Já os tipos um pouco mais complicados permite alguma mudança aqui e acolá:

    int* x;
    char * y;
    long * p;

Essa liberdade da linguagem, mesmo sendo um recurso útil, pode ser bem nocivo dependendo de quem olha o código:

    
    int x, y; // dois inteiros
    int * x, y; // um ponteiro para inteiro e um inteiro
    int x, *y; // um inteiro e um ponteiro para inteiro
    int *x, y; // um ponteiro para inteiro e um inteiro

Em algumas formas da sintaxe, além de ser inevitável, gera bastante desconfiança:

    
    // Um ponteiro para função que recebe dois inteiros e não retorna nada.
    typedef void (* FP )(int, int);
    
    // Um ponteiro para função que recebe dois inteiros e não retorna nada.
    void (*)(int, int);
    
    // Um cast para ponteiro para função que recebe dois inteiros e não retorna nada.
    ( ( void (*)(int, int) ) pf )(x, y);

    #include <iostream>
    
    void func(int x, int y)
    {
       std::cout << x << '-' << y << '\n';
    }
    
    int main()
    {
       void* pf = func;
       ( ( void (*)(int, int) ) pf )(3, 14);
    }
 

Antigamente, as structs eram construções em C que definiam um agregado de tipos primitivos (ou outras structs) e que poderiam gerar variáveis desse tipo em qualquer lugar, desde que informado seu nome e que se tratasse de uma struct:

    /** @file structs.cpp */
    struct MyStruct { int x, y; };
    
    void func1()
    {
       struct MyStruct ms;
       //...
    }
    
    void func2(struct MyStruct msa)
    {
       //...
    }
    
    int main()
    {
       struct MyStruct ms;
       func2(ms);
    }

Para evitar toda essa digitação, os programadores usavam um pequeno truque criando um apelido para a estrutura, e usavam o apelido no lugar da struct (apesar de ambas representarem a mesma coisa).

    struct MyStruct { int x, y; };
    typedef struct MyStruct MS;

ou
    
    typedef struct MyStruct { int x, y; } MS;
    struct MyStruct ms1; // ainda prolixo
    MS ms2; // mais simples

Com a definição da linguagem C++ padrão, e mais moderna, essa antiguidade foi removida, apesar de ainda suportada. Era possível usar apenas o nome do struct como seu tipo:

    /** @file structs.cpp */
    struct MyStruct { int x, y; };
    
    void func1()
    {
       /*struct*/ MyStruct ms;
       //...
    }
    
    void func2(/*struct*/ MyStruct msa)
    {
       //...
    }
    
    int main()
    {
       /*struct*/ MyStruct ms;
       func2(ms);
    }

Porém, isso vai um pouco além de quando a Microsoft começou a fazer código para seu sistema operacional. Naquela época, o padrão ainda estava se formando e existia mais ou menos um consenso de como seria a linguagem C++ (sem muitas alterações do que de fato a linguagem C já era). De qualquer forma, a linguagem C imperava bem mais que C++. Dessa forma, já era bem formada a ideia de como declarar uma struct: a forma antiga.

    
    typedef struct _MINHASTRUCT {
       int x;
       int y;
    }
    MINHASTRUCT, *LPMINHASTRUCT;

Além do uso controverso do sublinhado para nomear entidades (que no padrão foi recomendado que se reservasse aos nomes internos da biblioteca-padrão) e do uso de MAÍUSCULASNONOME (historicamente atribuído a nomes definidos no pré-processador), o uso do typedef atracado a um struct era muito difundido. E ficou ainda mais depois que a API do Windows foi publicada com essas definições.

Ora, do mesmo jeito que é feito há vinte anos: sem typedefs. O próprio paradigma da linguagem, independente de padrões de APIs, de sistemas operacionais ou de projetos específicos já orienta o programador para entender o que o espera na leitura de um código-fonte qualquer. Qualquer pessoa que aprendeu o básico do básico sobre ponteiros e structs consegue ler o código abaixo:

    // Papai, o que que é isso?
    // Ora, filho, apenas uma definição de estrutura!
    //
    struct MinhaStruct {
       int x;
       int y;
    };
    
    // muitas linhas abaixo...
    
    void func(MinhaStruct* ms)
    {
       // asterisco significa ponteiro para MinhaStruct!
    }
    
    int main()
    {
       MinhaStruct ms;
       func(&ms);
    }

Agora, para entender a forma antiga, ou você se baseou no copy&paste dos modelos Microsoftianos, ou seja, decoreba, ou você é PhD em Linguagem C/C++ e padrões históricos de linguagens legadas. Se não é, deveria começar o curso agora.

    // Papai, o que que é isso?
    // Ora, filho, apenas uma definição de sinônimo da struct
    // _MINHASTRUCT, cujo nome não é usado, para dois nomes
    // em maiúsculas, apesar se não serem defines, com uma
    // nomenclatura de ponteiro que eu nunca vi na vida (obs: 
    // papai programa em um sistema não-Windows).
    //
    typedef struct _MINHASTRUCT {
       int x;
       int y;
    }
    MINHASTRUCT, *LPMINHASTRUCT;
    
    // muitas linhas abaixo...
    
    void func(LPMINHASTRUCT ms)
    {
       // o que diabos é um LP, mesmo?
    }
    
    int main()
    {
       MINHASTRUCT ms;
       func(&ms);
    }

Da mesma forma, o uso de uma estrutura simples de tipos mantém a lista de nomes do seu projeto limpa e clara. Compare o visualizador de classes em projetos Windows com algo mais C++ para ter uma ideia.

É claro, essa é apenas uma sugestão. Existem vantagens em sua utilização. Existe alguma vantagem no modo antigo? Existe: a Microsoft usa, e talvez mais pessoas usem. Basta a você decidir qual deve ser o melhor caminho.

De acordo com o leitor  Adriano dos Santos Fernandes, a obrigatoriedade do nome struct após seu nome continua valendo para a linguagem C padrão, assim como no compilador GCC ocorre um erro ao tentar omiti-la. Apenas na linguagem C++ essa obrigatoriedade não existe mais.

Eu não fiz meus testes, mas confio no diagnóstico de nosso amigo. A maior falha do artigo, no entanto, é usar a linguagem C como base, quando na verdade ele deveria falar sobre o uso desses typedefs em C++. Esse erro também foi corrigido no original.
