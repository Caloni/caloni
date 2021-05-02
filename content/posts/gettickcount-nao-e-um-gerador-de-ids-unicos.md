---
date: "2012-06-25"
title: GetTickCount não é um gerador de IDs únicos
categories: [ "draft", "blog" ]
---
Muitas vezes uma solução intuitiva não é exatamente o que esperamos que seja quando o código está rodando. Gerar IDs únicos, por exemplo. Se você analisar por 5 minutos pode chegar à conclusão que um simples GetTickCount, que tem resolução de clock boa e que se repete apenas depois de 50 dias pode ser um ótimo facilitador para gerar IDs exclusivos durante o dia.

[![](http://i.imgur.com/buOxKgQ.jpg)](/images/TimeTravel.jpg)

Porém, nada como código para provar que estamos errados:

```cpp
#include <windows.h>
#include <iostream>
#include <list>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

list<DWORD> g_ticks;
list<LONG> g_increments;

DWORD WINAPI Ticks(PVOID)
{
    for( int i = 1; i <= 100; ++i )
    {
        DWORD tick = GetTickCount();
        g_ticks.push_back(tick);
        Sleep(rand() % 20);
    }
    return 0;
}

DWORD WINAPI Increment(PVOID)
{
    static LONG st_prevIncrement = 0;

    for( int i = 1; i <= 100; ++i )
    {
        LONG increment = InterlockedIncrement(&st_prevIncrement);
        g_increments.push_back(increment);
        Sleep(rand() % 20);
    }
    return 0;
}

int main()
{
    const size_t threadsCount = 20;
    HANDLE threads[threadsCount];

    srand((unsigned int) time(0));

    for( size_t i = 0; i < threadsCount / 2; ++i )
        threads[i] = CreateThread(NULL, 0, Ticks, NULL, 0, NULL);
    for( size_t i = threadsCount / 2; i < threadsCount; ++i )
        threads[i] = CreateThread(NULL, 0, Increment, NULL, 0, NULL);

    WaitForMultipleObjects(threadsCount, threads, TRUE, INFINITE);

    for( auto it = g_ticks.begin(); it != g_ticks.end(); ++it )
    {
        DWORD tick = *it;
        size_t tickOccurrence = count(g_ticks.begin(), g_ticks.end(), tick);

        if( tickOccurrence > 1 )
        {
            cout << "Ocorrencia de tick duplicado!\n";
            break;
        }
    }

    for( auto it = g_increments.begin(); it != g_increments.end(); ++it )
    {
        DWORD tick = *it;
        size_t incrementOccurrence = count(g_increments.begin(), g_increments.end(), tick);

        if( incrementOccurrence > 1 )
        {
            cout << "Ocorrencia de incremento duplicado!\n";
            break;
        }
    }
}

 

```

O motivo do GetTickCount retornar números iguais remete tanto ao fato que o espaço de tempo entre uma execução e outra pode ser muito pequeno quanto ao fato de várias threads podem ser executadas efetivamente ao mesmo tempo em ambientes de dois ou mais cores.

Já o motivo do InterlockedIncrement funcionar sempre é porque aqui estamos usando uma solução de incremento atômico, ou seja, usamos a mesma base contadora e incrementamos ela em uma operação que não pode ocorrer ao mesmo tempo com outra thread.

O que aprendemos aqui? Que por mais que seja intuitiva uma solução, nunca podemos nos basear nas nossas falhas cabeças. Um computador está aí não apenas para ser mais rápido, mas para ser assertivo em nossas elucubrações. Nesse sentido, é o nosso companheiro vulcaniano.
