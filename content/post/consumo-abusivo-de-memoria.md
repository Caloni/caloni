---
date: "2012-05-19"
title: Consumo abusivo de memória
categories: [ "code" ]
---
Era um belo dia em um ambiente de processamento fictício de filas fictícias e threads fictícias. Eis um belo código com filas, threads e processamentos feitos em stop-motion:

```cpp
#include <windows.h> // critical section, create thread...
#include <list> // nossa lista interna
#include <time.h> // randomização

struct Queue // uma fila (duh)
{
    size_t bufferSize; // cada item é um buffer de tamanho fixo
    DWORD wait; // antes de processar, aguardemos esse tempo fixo
    CRITICAL_SECTION cs; // stl é thread-safe, pero no mucho
    std::list<char*> items; // os itens!
};

DWORD WINAPI InsertItems(LPVOID pvQueue) // insere, insere, insere....
{
    Queue& queue = *(Queue*) pvQueue;
    for( int i = 0; i < 10 * 1000; ++i ) // 10k itens!
    {
        char* buffer = new char[queue.bufferSize];
        memset(buffer, (int) (i % ('Z' - 'A')) + 'A', queue.bufferSize); // teoricamente de A a Z
        buffer[queue.bufferSize - 1] = 0; // string C pra facilitar nossa depuração
        EnterCriticalSection(&queue.cs); // deixa eu entrar!
        queue.items.push_back(buffer);
        LeaveCriticalSection(&queue.cs); // deixa eu sair!
        Sleep(10); // dá uma dormidinha (sempre menor dormidinhas do processamento)
    }
    return ERROR_SUCCESS; // "tá tudo certo!" (by Starcraft 2)
}

DWORD WINAPI ProcessItems(LPVOID pvQueue) // processa, processa, processa...
{
    Queue& queue = *(Queue*) pvQueue;
    DWORD wait = 2;
    Sleep(10000); // como um advogado oportunista, aguardamos por alguém pra processar
    while( ! queue.items.empty() ) // agora vai até esvaziar o recinto
    {
        EnterCriticalSection(&queue.cs); // deixa eu entrar!
        char* buffer = queue.items.front();
        queue.items.pop_front();
        LeaveCriticalSection(&queue.cs); // deixa eu sair!
        delete [] buffer;
        Sleep(queue.wait); // aguarda por... por quanto mesmo?
    }
    return ERROR_SUCCESS; // "tá tudo certo!" (by Starcraft 2)
}

int main(int argc, char* argv[]) // No princípio havia a pilha, quando Deus disse: 'int main!'
{
    static const size_t QUEUES_SIZE = 20; // número de filas sendo processadas
    static const size_t QUEUE_ITEM_SIZE = 0x1000; // 1KB é o chunk alocado por item
    static const DWORD WAIT_TIMES[] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1000 }; // alguém vai esperar demais

    Queue queues[QUEUES_SIZE]; // as filas
    HANDLE queueThreads[QUEUES_SIZE * 2]; // as threads que processam as filas

    srand((unsigned int)time(0)); // randomizemos tudo

    for( size_t i = 0; i < QUEUES_SIZE; ++i )
    {
        queues[i].bufferSize = QUEUE_ITEM_SIZE + i; // para diferenciarmos as filas
        queues[i].wait = WAIT_TIMES[ rand() % (sizeof(WAIT_TIMES) / sizeof(DWORD)) ]; // vamos esperar por... por quanto mesmo?
        InitializeCriticalSection(&queues[i].cs); // deu crash em algumas situações em release (stl deveria ser thread-safe...)
        queueThreads[i] = CreateThread(NULL, 0, InsertItems, &queues[i], 0, NULL); // criamos thread de inserção
        queueThreads[QUEUES_SIZE + i] = CreateThread(NULL, 0, ProcessItems, &queues[i], 0, NULL); // criamos thread de processamento
    }

    WaitForMultipleObjects(QUEUES_SIZE * 2, queueThreads, TRUE, INFINITE); // espera a 'gaguera'
    return 0; // "tá tudo certo!" (by Starcraft 2)
}
 

```

Se olharmos de perto o processamento e a memória consumida por esse processo, veremos que no início existe um boom de ambos, mas após um momento de pico, o processamento praticamente pára, mas a memória se mantém:

[![](http://i.imgur.com/hoxWfdi.png)](/images/MemoryGraph.png)

Depois de pesquisar [por meus tweets favoritos](https://twitter.com/#!/caloni/status/138632431765954560), fica fácil ter a receita para verificarmos isso usando nosso depurador favorito: <del>Visual Studio</del> WinDbg!

[![](http://i.imgur.com/ZKVVT0O.png)](/images/TweetHeap.png)

windbg -pn MemoryConsumption.exe

[![](http://i.imgur.com/Bzb2XVY.png)](/images/MemorySummary.png)

Achamos onde está a memória consumida. Agora precisamos de dicas do que pode estar consumindo essa memória. Vamos começar por listar os chunks alocados por tamanho de alocação:

    
    0:004> !heap -stat -h 0
    Allocations statistics for
     heap @ 00670000
    group-by: TOTSIZE max-display: 20

    
     size #blocks total ( %) (percent of total busy bytes)
     1037 25e5 - 2667433 (33.04)
     1025 25e6 - 263da3e (32.90)
     1024 25e4 - 2639410 (32.89)
    ...

O Top 3 é de tamanhos conhecidos pelo código, de 1024 a 1024 + QUEUES_SIZE - 1. O de tamanho 1037, por exemplo, possui 0x25e5 blocos alocados. Vamos listar cada um deles:

    
    0:004> !heap -flt s 1037
     _HEAP @ 420000
     _HEAP @ 670000
     HEAP_ENTRY Size Prev Flags UserPtr UserSize - state
    <span style="color: #ff0000;"> 00558600 0221 0000 [00] 00558618 01037 - (busy)</span>         <--- vamos usar esse primeiro mais tarde
     0055fd38 0221 0221 [00] 0055fd50 01037 - (busy)
     00561f48 0221 0221 [00] 00561f60 01037 - (busy)
     00565260 0221 0221 [00] 00565278 01037 - (busy)
     0056c998 0221 0221 [00] 0056c9b0 01037 - (busy)
     0056daa0 0221 0221 [00] 0056dab8 01037 - (busy)
     0056eba8 0221 0221 [00] 0056ebc0 01037 - (busy)
     00570db8 0221 0221 [00] 00570dd0 01037 - (busy)
     00572fc8 0221 0221 [00] 00572fe0 01037 - (busy)
     005740d0 0221 0221 [00] 005740e8 01037 - (busy)
     0058abc8 0221 0221 [00] 0058abe0 01037 - (busy)
     00595618 0221 0221 [00] 00595630 01037 - (busy)
     00599a38 0221 0221 [00] 00599a50 01037 - (busy)
     0059de58 0(...)

A listagem do depurador nos dá o endereço onde o chunk foi alocado no heap e o endereço devolvido para o usuário, onde colocamos nossas tralhas. Através de ambos é possível trackear a pilha da chamada que alocou cada pedaço de memória. Isso, claro, se previamente tivermos habilitado essa informação através do [GFlags](http://msdn.microsoft.com/en-us/library/windows/hardware/ff549596(v=vs.85).aspx):

[![](http://i.imgur.com/JeqoBju.png)](/images/GFlagsMemoryStack.png)

    
    0:004> !heap -p -a <span style="color: #ff0000;">00558600</span>
     address 00558600 found in
     _HEAP @ 670000
     HEAP_ENTRY Size Prev Flags UserPtr UserSize - state
     <span style="color: #ff0000;">00558600 0221 0000 [00] 00558618 01037 - (busy)</span>
     Trace: b7a24
     7722dfa2 ntdll!RtlAllocateHeap+0x00000274
     5b628343 MSVCR100D!_heap_alloc_base+0x00000053
     5b63697c MSVCR100D!_nh_malloc_dbg+0x000002dc
     5b63671f MSVCR100D!_nh_malloc_dbg+0x0000007f
     5b6366cc MSVCR100D!_nh_malloc_dbg+0x0000002c
     5b639c5b MSVCR100D!malloc+0x0000001b
     5b627db1 MSVCR100D!operator new+0x00000011
     e84dee MemoryConsumption!operator new[]+0x0000000e
    <span style="color: #ff0000;"> e818be MemoryConsumption!InsertItems+0x0000004e</span>
     7679339a kernel32!BaseThreadInitThunk+0x0000000e
     771e9ef2 ntdll!__RtlUserThreadStart+0x00000070
     771e9ec5 ntdll!_RtlUserThreadStart+0x0000001b

Dessa forma temos onde cada memória foi alocada, o que nos dará uma informação valiosa, dependendo qual o tipo de problema estamos tentando resolver.

    
    0:004> u <span style="color: #ff0000;">e818be</span>
    MemoryConsumption!InsertItems+0x4e [c:\...\memoryconsumption.cpp @ 18]:
    00e818be 83c404 add esp,4
    00e818c1 898514ffffff mov dword ptr [ebp-0ECh],eax
    00e818c7 8b9514ffffff mov edx,dword ptr [ebp-0ECh]
    00e818cd 8955e0 mov dword ptr [ebp-20h],edx
    00e818d0 8b45f8 mov eax,dword ptr [ebp-8]
    00e818d3 8b08 mov ecx,dword ptr [eax]
    00e818d5 51 push ecx
    00e818d6 8b45ec mov eax,dword ptr [ebp-14h]

Outra informação relevante é o que está gravado na memória, que pode nos dar insights de que tipo de objeto estamos lidando:

    
    0:004> db <span style="color: #ff0000;">00558618</span>
    00558618 c0 b7 8c 0b 98 03 55 00-00 00 00 00 00 00 00 00 ......U.........
    00558628 13 10 00 00 01 00 00 00-15 94 00 00 fd fd fd fd ................
    00558638 51 51 51 51 51 51 51 51-51 51 51 51 51 51 51 51 QQQQQQQQQQQQQQQQ
    00558648 51 51 51 51 51 51 51 51-51 51 51 51 51 51 51 51 QQQQQQQQQQQQQQQQ
    00558658 51 51 51 51 51 51 51 51-51 51 51 51 51 51 51 51 QQQQQQQQQQQQQQQQ
    00558668 51 51 51 51 51 51 51 51-51 51 51 51 51 51 51 51 QQQQQQQQQQQQQQQQ
    00558678 51 51 51 51 51 51 51 51-51 51 51 51 51 51 51 51 QQQQQQQQQQQQQQQQ
    00558688 51 51 51 51 51 51 51 51-51 51 51 51 51 51 51 51 QQQQQQQQQQQQQQQQ

Não é o caso, mas vamos supor que fosse um objeto/tipo conhecido. Poderíamos simplesmente "importar" o tipo diretamente do PDB que estamos para modelar a memória que encontramos em volta. Mais detalhes [em outro artigo](http://www.caloni.com.br/importando-tipos-de-outros-projetos).

#### Funções/classes usadas nesse artigo

    
  * [CreateThread](http://msdn.microsoft.com/en-us/library/windows/desktop/ms682453(v=vs.85).aspx). Cria uma nova linha de execução.

    
  * [WaitForMultipleObjects](http://msdn.microsoft.com/en-us/library/windows/desktop/ms687025(v=vs.85).aspx). Pode aguardar diferentes linhas de execução terminarem.

    
  * [std::list](http://www.cplusplus.com/reference/stl/list/front/). Lista na STL para inserir/remover objetos na frente e atrás (ui).

    
  * [Initialize](http://msdn.microsoft.com/en-us/library/windows/desktop/ms683472(v=vs.85).aspx), [Enter](http://msdn.microsoft.com/en-us/library/windows/desktop/ms682608(v=vs.85).aspx) e [LeaveCriticalSection](http://msdn.microsoft.com/en-us/library/windows/desktop/ms684169(v=vs.85).aspx). Uma maneira simples de criar blocos de entrada atômica (apenas uma thread entra por vez).

    
  * [memset](http://www.cplusplus.com/reference/clibrary/cstring/memset/). Se você não sabe usar memset, provavelmente não entendeu nada desse artigo.

