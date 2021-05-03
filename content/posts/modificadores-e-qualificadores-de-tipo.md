---
categories:
- draft
- code
date: '2010-05-28'
title: Modificadores e qualificadores de tipo
---

<blockquote>_@caloni poderia pensar em fazer um artigo sobre os modificadores de tipo em c? os mais complexo, acho eu: volatile, enum, union, extern, etc_</blockquote>

Uma coisa de cada vez: existem **modificadores **(ou qualificadores) de tipo e **especificadores** de tipo. _Volatile_ e _extern_ se encaixam na primeira categoria, _enum_ e _union_ na segunda. Veremos um pouco desses dois lados da linguagem em doses paliativas.

#### Padrão C (ISO/IEC 9899:1990)

    
    6.5.2.2 enum-specifier
     <a href="http://www.caloni.com.br/enum">enum</a>
    
    6.5.3 type-qualifier
     <a href="http://www.caloni.com.br/const-e-volatile">const</a>
     <a href="http://www.caloni.com.br/const-e-volatile">volatile</a>
    
    6.5.2.1 struct-or-union
     struct
     union
    
    6.5.1 storage-class-specifier
     typedef
     extern
     static
     auto
     register

#### Padrão C++ (ISO/IEC 14882:1998)

    
    type-specifier
     <a href="http://www.caloni.com.br/enum">enum-specifier</a>
    
    enum-specifier
     <a href="http://www.caloni.com.br/enum">enum</a>
    
    cv-qualifier
     <a href="http://www.caloni.com.br/const-e-volatile">const</a>
     <a href="http://www.caloni.com.br/const-e-volatile">volatile</a>
    
    class-key
     class
     struct
     union
    
    storage-class-specifier
     auto
     register
     static
     extern
     mutable
    
    decl-specifier
     storage-class-specifier
     typedef

#### Modificadores de tipo

Um modificador de tipo é opcional na definição de um tipo e deve estar sempre relacionado com a declaração de alguma variável. Ele determina, em termos gerais, qual será a função dessa variável. Ela pode ser modificada? Onde ela se encontra no programa? Como ela será modificada?

Como exemplo rápido, temos abaixo uma variável que é atualizada pelo clock do processador e uma variável que não pode ser alterada após sua primeira atribuição:

    
    volatile int* clockSecs = <algum-endereço-do-sistema>;

    
    const float pi = 3.14;

Fica meio óbvio que a primeira variável possui seu valor volátil, ou seja, muda conforme o tempo passa, e não depende do próprio código (pode mudar sem sua permissão). A segunda variável também tem um uso explícito, uma vez que o valor de pi nunca será alterado (não nesse Universo).

#### Especificadores de tipo

Os especificadores de tipo possuem cada um sua peculiaridade. Os mais peculiares, que veremos nos próximos artigos, serão as enumerações e as construções bizarras de structs e unions.

    
    enum Contador { um = 1, dois, tres, };

    
    union Atoms { struct { int part1; int part2; } parts; int64 total; };

Aqui não é um compêndio teórico sobre a linguagem. Vamos falar particularmente da programação Windows, mas esteja livre para dar seus pitacos com respeito a outros sistemas operacionais e suas implementações igualmente exdrúxulas =)