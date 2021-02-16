---
date: "2009-07-10"
title: Polimorfismo estático
tags: [ "draft", "code" ]
---
Para explicar polimorfismo, nada como ver as coisas como elas eram. Se você fosse um programador C de vinte anos atrás e criasse as seguintes funções:

```c
int soma(int x, int y);
double soma(double x, double y);

int main()
{
    int zi = soma(2, 3);
    double zd = soma(2.5, 3.4);
    return 0;
}

 

```

Imediatamente o compilador iria acusar os seguintes erros:

    
    overload.c

    
    overload.c(2) : warning C4028: formal parameter 1 different from declaration
    overload.c(2) : warning C4028: formal parameter 2 different from declaration
    overload.c(2) : error C2371: 'soma' : redefinition; different basic types
            overload.c(1) : see declaration of 'soma'

Isso acontece porque em C **os identificadores são únicos por escopo**. Esse é o motivo por que o seguinte código também está errado:

```c
int main()
{
    int x = 0;
    int x = 1;
    return 0;
}

 

```

    
    overload.c
    overload.c(5) : error C2374: 'x' : redefinition; multiple initialization
            overload.c(4) : see declaration of 'x'

De volta aos anos 90, isso também está errado em C++. Até por uma questão de lógica: como o compilador pode saber a qual variável estamos nos referindo se usarmos o mesmo nome para duas delas?

Só que existe um truquezinho para impedir essa ambiguidade quando falamos de funções: os parâmetros que ela recebe.

```cpp
int soma(int x, int y);
double soma(double x, double y);

int main()
{
    int zi = soma(2, 3); // dois tipos int: chamar soma(int, int)
    double zd = soma(2.5, 3.4); // dois tipos double: só pode ser soma(double, double)
    return 0;
}

 

```

    
    C:\Tests>cl /c overload.cpp
    Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 13.10.6030 for 80x86
    Copyright (C) Microsoft Corporation 1984-2002. All rights reserved.
    
    overload.cpp
    
    C:\Tests>

Isso permitiu que em C++ fosse criada a sobrecarga estática, que é exatamente isso: chamar a função não apenas de acordo com seu nome, mas também de acordo com sua assinatura, ou seja, o número e o tipo dos parâmetros recebidos. Chamamos de sobrecarga estática porque isso é feito apenas pelo compilador, não pesando em nada durante a execução do programa.

Entre seus usos mais comuns estão os seguintes:

    
  * Ter funções com o mesmo nome mas que tratam de diferentes parâmetros;

    
    * soma(int, int);

    
    * soma(double, double);

    
    * Obs.: Isso ignora, é claro, as facilidades dos templates.

    
  * Versões novas da mesma função que recebem parâmetros adicionais;

    
    * export_data(void* buffer, int size);

    
    * export_data(void* buffer, int size, unsigned long options);

    
  * Mesmo nome de método para setar e obter o valor de uma propriedade;

    
    * Class::Property(int x); // setter

    
    * int x Class::Property() const; // getter

    
  * Bom, o que mais sua imaginação mandar =)

