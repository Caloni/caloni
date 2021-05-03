---
categories:
- code
date: '2009-04-17'
title: A sala da fila das threads
---

Quando falei sobre [a fila das threads], e como cada thread espera pacientemente em uma fila até chegar sua vez de ser atendida no guichê das CPUs, também vimos como é fácil fazer caquinhas em um programa que roda paralelamente duas threads ou mais.

Também falei que iríamos resolver esse problema, afinal de contas, temos que salvar todos aqueles programas que usam dezenas de threads trabalhando ao mesmo tempo para contar números de um até dez.

A boa notícia é que o salvamento é mais simples do que parece: coloque todas as suas threads em uma sala trancada e deixe apenas uma chave. As threads terão que brigar para sair da sala e, depois que a vencedora sair, as outras terão que ficar esperando ela voltar.

Confuso? Se estiver, ainda bem. Isso quer dizer que estamos novamente em um daqueles artigos com "pseudo-parábolas", a maneira mais ilustrada de explicar as coisas.

Os SOs modernos possuem inúmeras maneiras de controlar e monitorar o acesso a recursos do sistema. Neste breve artigo irei falar apenas de um: o critical section, ou, em tradução livre, "seção crítica". O "seção" desse nome diz respeito a uma seção do programa, ou seja, um pedaço de código mesmo. Um pedaço de código crítico.

Resumidamente, um critical section é um recurso que apenas uma thread por vez pode obter. Para que outra thread tenha acesso ao mesmo critical section, a primeira thread que o obteve deve soltá-lo. Enquanto ela não solta, as outras threads ficam paradas, esperando pela chave, na sala trancada.

Do ponto de vista do programador o critical secton é apenas uma estrutura que é usada na chamada de quatro funções básicas: para inicializar o recurso, para entrar na seção crítica, para sair da seção crítica e para liberar o recurso, quando aquele critical section não será usado mais.

Falando assim, parece simples. Bom, na verdade é simples, mesmo. Tudo que você precisa para corrigir o programa do artigo anterior é criar um critical section e fazer com que as threads obtenham-no antes de mexer com o contador compartilhado.

    #include <windows.h>
    #include <stdio.h>
    
    #define MAX_COUNTER 10
    
    int g_counter = 0;
    CRITICAL_SECTION g_cs;
    
    DWORD WINAPI Increment()
    {
      DWORD tid 
        = GetCurrentThreadId();
    
      while( g_counter < MAX_COUNTER )
      {
        // esse é o começo de nossa 
        // seção crítica
        // só uma thread entra
        // por vez por aqui
        EnterCriticalSection(&g_cs);
    
        int temp = g_counter;
        temp = temp + 1;
        Sleep(0); // indo para 
                  // o final da fila
        g_counter = temp;
    
        // esse é o fim de nossa 
        // seção crítica
        // a partir dessa chamada 
        // outra thread pode 
        // entrar pelo começo
        LeaveCriticalSection(&g_cs);
    
        printf("Counter: %d"
          "\t\tThread: %d\n", 
          temp, 
          tid);
      }
    
      return 0;
    }
    
    int main()
    {
      HANDLE threads[3];
      DWORD tids[3];
    
      // precisamos inicializar 
      // nosso recurso de 
      // seção crítica
      InitializeCriticalSection(&g_cs);
    
      for( int i = 0; i < 3; ++i )
      {
        threads[i] 
          = CreateThread(NULL, 
          0, 
          IncrementGlobalCounter, 
          0, 
          0, 
          &tids[i]);

        printf("Thread %i: %d\n", 
          i, 
          tids[i]);
      }
    
      // aguarda as threads
      WaitForMultipleObjects(3, 
        threads, 
        TRUE, 
        INFINITE);
    
      // agora precisamos liberar o 
      // recurso de seção crítica
      DeleteCriticalSection(&g_cs);
    }

Para finalizar, algo para pensar: se uma thread só consegue um critical section depois que outra thread soltá-lo, o que acontece se essa outra thread estiver esperando por outro critical section que uma thread que aguarda estiver segurando?

Acabamos de ilustrar um procedimento muito simples para cagar completamente no código e gerar um travamento que pode demorar de horas a semanas para ser detectado e resolvido. É o conhecido deadlock. Se você não entendeu ainda, imagine que, para voltar à sala das threads, a primeira thread que saiu precisa de duas chaves; só que ela só pegou a primeira, e a segunda está dentro da sala. Para pegar a segunda chave, ela precisa entrar na sala, só que a sala está trancada pelas duas chaves!

Deadlocks são sempre indesejáveis, e é por isso que existem diversas técnicas para tentar evitá-los. A mais conhecida é sempre obter os critical sections na mesma ordem. Dessa forma a obtenção de recursos é hierarquizada, o que impede que dois CSs estejam no mesmo nível de obtenção, evitando que duas threads distintas os obtenham.

Espero que tenha ficado claro nossa breve explanação de como podemos controlar programas multithreading. Espero, pois a próxima tarefa é entender outros conceitos mais abstratos e virtuais, como funções virtuais e classes abstratas.

[a fila das threads]: /a-fila-das-threads