---
date: 2019-05-17T13:53:21-03:00
title: "C Resolve Tudo: Orientação a Objetos (com Polimorfismo)"
categories: [ "code" ]
desc: "Formas de fazer com a linguagem C o que as outras linguagens fazem by design. Se quiser algum artigo sobre alguma feature de alguma linguagem ou ferramenta, comente."
---
Como programadores há um vício em nossas cabeças que é estar constantemente buscando a bala de prata, ou seja, a solução final e única para todos os nossos problemas de implementação. Com o tempo e alguma experiência descobrimos que tal coisa não existe, mas até lá nos encantamos com esse ou aquele framework, e claro, com essa ou aquela linguagem.

As linguagens que são criadas depois da revolução dos computadores pessoais querem facilitar a vida do programador médio embutindo soluções já testadas por [programadores de verdade](/programadores-de-verdade-nao-usam-java) e evitando a todo custo que o código incorra em erros comuns. Além disso, há movimentos nas comunidades e no mercado que geram tendências que influenciam essas linguagens, o que explica design patterns, orientação a objetos, programação funcional, xp, scrum, devops e qualquer outra bala de prata que vá se solidificando.

Expliquei tudo isso para chegar no tema deste artigo: você pode fazer tudo isso usando linguagem C.

Mas aí você deve estar se perguntando: "supor que uma linguagem resolve tudo não é estar defendendo também uma bala de prata?". A resposta é sim e não. Sim, é uma bala de prata se você pensar que pode fazer do zero sites e interfaces gráficas modernas em C puro. Mas a resposta também é não porque eu estou trabalhando em uma outra camada, aquela em que as soluções que ficam pra sempre são implementadas. Estou falando de pensar sempre na linguagem C quando estiver interessado no funcionamento das outras soluções.

Esse mindset propost tem como objetivo impedir que você pense que as outras soluções são mágicas porque se você consegue pensar em C ela é real. Se tem algo que a linguagem C não é esse algo é mágica. C é uma simples abstração de uma máquina virtual que se relaciona de maneira muito íntima com as implementações em assembly de várias arquiteturas. Mágica é algo que te impede de enxergar em que momento uma solução se encontra com o hardware. C nunca irá te impedir de fazer isso.

Dito isto, vamos analisar algumas balas de prata e entender como em C isso é implementado para revelar a mágica.

# Orientação a Objetos

A Orientação a Objetos se divide em algumas features. Algumas não vale a pena falar aqui, como tratar tudo como objeto. C já faz isso através de structs. Você pode montar uma struct que possua métodos, inclusive, através de ponteiros para função. E esses métodos já são sobrecarregáveis e virtuais.

```c
struct MyClass
{
    int x, y;
    void (*method)(int);
};

void method(int x)
{
}

struct MyClass NewMyClass()
{
    struct MyClass ret = { 0, 0 };
    ret.method = &method;
    return ret;
}

int main()
{
    struct MyClass obj = NewMyClass();
    obj.method(10);
}
```

A sobrecarga se torna algo trivial, bem documentada através dos nomes das funções que você está chamando. Tudo fica às claras, nada implícito, nada disse que me disse. Se eu chamo um método NewMyClass2 é óbvio que estou construindo uma segunda versão baseada na primeira, e posso inclusive comparar para ver se os métodos são originais ou sobrescritos com `obj.method == &method`, por exemplo. Além disso, é possível realizar composições de tipos onde alguns métodos são sobrescritos enquanto outros são compostos por chamadas duplas, triplas. Não há qualquer limitação ao polimorfismo exceto o que você define.

```c
struct MyClass
{
    int x, y;
    void (*method)(int);
};

void method(int x)
{
}

struct MyClass NewMyClass()
{
    struct MyClass ret = { 0, 0 };
    ret.method = &method;
    return ret;
}

void method2(int x)
{
}

struct MyClass NewMyClass2()
{
    struct MyClass ret = NewMyClass();
    ret.method = &method2;
    return ret;
}

int main()
{
    struct MyClass obj = NewMyClass2();
    obj.method(10);
}
```

Os métodos são "estáticos" por default (não há contexto), o que aliás facilita programação funcional, mas você pode buscar contexto onde te interessa, passando como parâmetro toda a "classe", seja por valor ou referência, ou passando até uma versão parcial dela. Há inúmeras maneiras de construir um objeto em C, pois ele não está restrito às regras de sintaxe da definição da linguagem, uma vez que é você que define. Além disso, como você deve ter percebido, para declarar tipos de structs é necessário o uso dessa palavra-chave, mas a linguagem C já possui um sistema de typedef para trocar convenientemente qualquer definição de tipo como um nome único.

```c
#include <stdio.h>

typedef struct SCalc
{
    int (*sum)(int, int);
    int (*mult)(struct SCalc*, int, int);

} Calc;

int calc_sum(int x, int y)
{
    return x + y;
}

int calc_mult(Calc* calc, int x, int y)
{
    int ret = 0;
    int i;
    for( i = 0; i < x; ++i )
        ret = calc->sum(ret, y);
    return ret;
}

Calc CalcNew()
{
    Calc calc;
    calc.sum = &calc_sum;
    calc.mult = &calc_mult;
    return calc;
}

int main()
{
    Calc calc = CalcNew();
    int x = 10, y = 32;
    int z = calc.sum(x, y);
    int k = calc.mult(&calc, z, y);
    printf("%d + %d = %d, %d * %d = %d\n", x, y, z, z, y, k);
}
```

```
10 + 32 = 42, 42 * 32 = 1344
```

Note que podemos ao redefinir a função de soma a de multiplicação também é alterada, mesmo não alterando seu funcionamento (mas alterando uma função que ela usa).

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct SCalc
{
    int (*sum)(int, int);
    int (*mult)(struct SCalc*, int, int);

} Calc;

int calc_sum(int x, int y)
{
    return x + y;
}

int calc_mult(Calc* calc, int x, int y)
{
    int ret = 0;
    int i;
    for( i = 0; i < x; ++i )
        ret = calc->sum(ret, y);
    return ret;
}

Calc CalcNew()
{
    Calc calc;
    calc.sum = &calc_sum;
    calc.mult = &calc_mult;
    return calc;
}


int calc_cat(int x, int y)
{
    char buf[100];
    int ret;
    sprintf(buf, "%d%d", x, y);
    ret = atoi(buf);
    return ret;
}

Calc BizarreCalcNew()
{
    Calc calc = CalcNew();
    calc.sum = &calc_cat;
    return calc;
}

int main()
{
    Calc calc = BizarreCalcNew();
    int x = 1, y = 1;
    int z = calc.sum(x, y);
    int k = calc.mult(&calc, z, y);
    printf("%d + %d = %d, %d * %d = %d\n", x, y, z, z, y, k);
}
```

```
10 + 32 = 1032, 1032 * 32 = 2147483647
```

Este é apenas um exemplo besta de polimorfismo, além de um exemplo trivial de como OO em C é infinitamente mais rico e mais complexo. Está nas mãos do programador definir até onde vai a solução proposta. E é bom saber que não existe bala de prata.
