---
categories: [ "code" ]
date: "2009-04-07"
tags: [ "learning", "kernel", ]
title: "A fila das threads"
---
Em um ambiente multithreading, diversas threads disputam "a tapas" a atenção do processador (CPU). Certo? Podemos dizer que, em um ambiente com muito processamento a realizar, de certa forma é isso que acontece. São threads e mais threads rodando um pedacinho de código cada vez que passam pelo processador.

Um ambiente complexo como esse é repleto de pequenos detalhes que podem fazer o iniciante logo desanimar quando tentar depurar um programa com mais de uma thread. De fato, eu já percebi que muitos não vão saber nem como começar a mastigar o problema.

Por isso inventei algumas analogias que considero no mínimo interessantes a respeito do assunto. Sem analogias, não sei como falaria sobre essas coisas de forma amena e "explicável" para iniciantes.

A primeira "parábola" conta a história da fila das threads em direção ao guichê das CPUs. Tudo começa com três threads, todas iniciando na mesma função. O objetivo de todas elas é incrementar um contador até que seu valor chegue a 10. Todas param quando esse objetivo é alcançado.

    #include <windows.h>
    #include <stdio.h>
    
    #define MAX_GLOBAL_COUNTER 10
    
    int g_globalCounter = 0;
    
    DWORD WINAPI IncrementGlobalCounter(PVOID)
    {
    	DWORD tid = GetCurrentThreadId();
        Sleep(10); // give some time 
                   // to other threads start
    
    	while( g_globalCounter < MAX_GLOBAL_COUNTER )
    	{
    		int temp = g_globalCounter;
    		temp = temp + 1;
    		g_globalCounter = temp;
            char buffer[100];
    		sprintf(buffer, 
                "thread %d incremented counter to %d", 
                tid, temp);
            puts(buffer);
    	}
    	return 0;
    }
    
    int main()
    {
    	HANDLE threads[3];
    	DWORD tids[3];
    
    	for( int i = 0; i < 3; ++i )
    	{
    		threads[i] = CreateThread(NULL, 0, 
                IncrementGlobalCounter, 0, 0, &tids[i]);
    		printf("Thread %i: %d\n", i, tids[i]);
    	}
    
    	WaitForMultipleObjects(3, threads, 
            TRUE, INFINITE);
    }

Esta é a saída:

    Thread 0: 13800
    Thread 1: 14488
    Thread 2: 380
    thread 13800 incremented counter to 1
    thread 13800 incremented counter to 4
    thread 13800 incremented counter to 5
    thread 13800 incremented counter to 6
    thread 13800 incremented counter to 7
    thread 13800 incremented counter to 8
    thread 13800 incremented counter to 9
    thread 13800 incremented counter to 10
    thread 380 incremented counter to 3
    thread 14488 incremented counter to 2

Pelo jeito a primeira thread não deu chance para as outras. Isso acontece por causa do pequeno espaço de tempo que é necessário para realizar a tarefa de incrementar uma variável. Tempo esse tão pequeno que nem foi suficiente para a primeira thread dar lugar para as outras duas threads e ir para o final da fila.

Quando uma thread quer realizar algum processamento ela precisa entrar na fila das threads ativas, que aguardam pela CPU que irá atendê-las. Nessa fila ela pega uma senha e aguarda a sua vez. Só que cada um que é atendido pela CPU tem um tempo máximo de atendimento, que nós chamamos de quantum, ou time slice. Se o tempo máximo estoura, ou a thread não tem mais nada pra fazer, ela sai do guichê de atendimento e volta a ficar inativa, ou volta para o final da fila, aguardando por mais processamento.

Uma thread pode opcionalmente ir para o final da fila por conta própria. Para isso, basta que ela chame a função Sleep da API passando qualquer valor em milissegundos; até mesmo zero. Se passar um valor diferente de zero, ela irá para outra fila de espera, a fila das inativas, até o tempo determinado estourar. Depois ela volta para a fila das threads ativas. Se passar zero, ela vai direto para a fila das ativas, aguardando pela sua próxima fatia de tempo de processamento.

    // ...
    sprintf(buffer, 
        "thread %d incremented counter to %d", 
        tid, temp);
    puts(buffer);
    Sleep(10); // go to the end of the row
    // ...

Agora cada thread, depois de incrementar uma vez o contador, volta para o final da fila. Dessa forma vemos uma thread de cada vez incrementando o mesmo contador.

    Thread 0: 4136
    Thread 1: 13988
    Thread 2: 10044
    thread 4136 incremented counter to 1
    thread 10044 incremented counter to 2
    thread 13988 incremented counter to 2
    thread 13988 incremented counter to 3
    thread 4136 incremented counter to 4
    thread 10044 incremented counter to 4
    thread 13988 incremented counter to 6
    thread 10044 incremented counter to 7
    thread 4136 incremented counter to 5
    thread 4136 incremented counter to 8
    thread 13988 incremented counter to 8
    thread 10044 incremented counter to 9
    thread 10044 incremented counter to 10

Peraí. O mesmo contador? Isso não pode gerar problemas de duas threads tentando incrementar o mesmo contador ao mesmo tempo? Bom, se você é bom observador já deve ter reparado que a execução acima deu xabu.

Para forçar isso acontecer mais rápido e de maneira mais gritante, basta irmos para o final da fila antes de incrementarmos, mas __após__ pegarmos o valor atual do contador. Note que a saída muda completamente. Dependendo de quantos processadores sua máquina tem o resultado pode ser bem bizarro. Note que eu mesmo não uso `Sleep(0)` porque meu número de cores não permite que eu faça esse experimento, já que sempre vão existir cores dispostos a reprocessar a thread que acabou de ir para o final de sua fila.

    // ...
    int temp = g_globalCounter;
    temp = temp + 1;
    Sleep(10); // go to the end of the row
                // BEFORE counting the counter
    g_globalCounter = temp;
    // ...

Isso, sim, deve dar um resultado bem bizarro:

    Thread 0: 1448
    Thread 1: 14476
    Thread 2: 16892
    thread 16892 incremented counter to 1
    thread 1448 incremented counter to 1
    thread 14476 incremented counter to 1
    thread 16892 incremented counter to 2
    thread 1448 incremented counter to 2
    thread 14476 incremented counter to 2
    thread 14476 incremented counter to 3
    thread 16892 incremented counter to 3
    thread 1448 incremented counter to 3
    thread 16892 incremented counter to 4
    thread 14476 incremented counter to 4
    thread 1448 incremented counter to 4
    thread 14476 incremented counter to 5
    thread 16892 incremented counter to 5
    thread 1448 incremented counter to 5
    thread 1448 incremented counter to 6
    thread 16892 incremented counter to 6
    thread 14476 incremented counter to 6
    thread 1448 incremented counter to 7
    thread 16892 incremented counter to 7
    thread 14476 incremented counter to 7
    thread 16892 incremented counter to 8
    thread 1448 incremented counter to 8
    thread 14476 incremented counter to 8
    thread 1448 incremented counter to 9
    thread 16892 incremented counter to 9
    thread 14476 incremented counter to 9
    thread 1448 incremented counter to 10
    thread 14476 incremented counter to 10
    thread 16892 incremented counter to 10

Esse problema ocorre pelo seguinte motivo: quando uma thread guarda o valor do contador na variável temp e volta para o final da fila, ela deixa de armazenar o contador atualizado para apenas depois que todas as outras threads passarem na sua frente. Só que as outras threads também pegam o mesmo valor do contador, pois ele ainda não foi alterado. Quando chega a hora da segunda passada no guichê das CPUs, todas as threads incrementaram o mesmo valor do contador.

O exemplo acima forçou essa situação, mas é preciso lembrar que isso pode acontecer mesmo sem o `Sleep`. É possível que o tempo da thread se esgote e ela pare de ser atendida justo na hora que iria salvar a variável temp no contador global. Dessa forma, ela vai para o final da fila à força e, quando voltar a ser atendida, uma outra thread já terá incrementado o mesmo valor, ou pego o valor antigo para ela própria incrementar.

Esse problema pode ser facilmente resolvido se utilizarmos um sistema de bloqueio entre threads do mesmo processo. Uma outra história para contar da próxima vez.
