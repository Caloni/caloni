---
date: "2009-04-07"
tags: [ "code", "learning", "kernel", ]
title: "A fila das threads"
---
Em um ambiente multithreading diversas threads disputam "a tapas" a atenção do processador (CPU). Certo? Podemos dizer que, em um ambiente com muito processamento a realizar, de certa forma é isso que acontece. São threads e mais threads rodando um pedacinho de código cada vez que passam pelo processador.

Um ambiente complexo como um sistema operacional executando dezenas (às vezes centenas) de programas é repleto de pequenos detalhes que podem fazer o iniciante logo desanimar quando tentar depurar um programa com mais de uma thread. De fato, eu já percebi que muitos não vão saber nem como começar a pensar sobre o problema.

Uma forma de visualizar o cenário multithread começa na fila das threads. Elas estão indo em direção ao guichê das CPUs onde vão conseguir tempo de processamento para rodar seu código. Depois que elas esgotam seu tempo elas se dirigem para o final da fila esperando por mais tempo para executar mais código.

Para simplificar este cenário vamos imaginar duas threads iniciando com o mesmo código. Esse código incrementa um contador global até ele chegar a dez, quando a função retorna e as threads terminam.

    int count = 0;

    increment() {
      while( count < 10 ) {
        count++;
        print(tid, count);
      }
    }

    main() {
      thread t1(increment);
      thread t2(increment);
    }

O tid no pseudo-código acima é sinônimo para Thread ID, o identificador único de uma thread, que costuma ser um número. Para simplificar vamos dar ao id os apelidos de t1 e t2. Esta é uma possível saída do código acima, dependendo de quantos processadores e cores possui a máquina:

    t1 1
    t1 2
    t1 3
    t1 4
    t1 5
    t1 6
    t1 7
    t1 8
    t1 9
    t1 10

Pelo jeito a primeira thread não deu chance para a outra executar. Isso acontece por causa do pequeno espaço de tempo que é necessário para realizar a tarefa de incrementar uma variável. É tão pequena a tarefa que nem foi suficiente para a primeira thread ficar sem tempo e a CPU mandar ela para o fim da fila. Por isso a segunda thread nunca chegou a incrementar o contador.

Quando uma thread quer realizar algum processamento, ela precisa entrar na fila das threads ativas, que aguardam pela CPU que irá atendê-las. Nessa fila ela pega uma senha e aguarda a sua vez. Só que cada vez que uma thread é atendida ela ganha um tempo limitado de atendimento, que na arquitetura do sistema operacional é chamado de quantum ou time slice. Se o quantum de uma thread estoura, ou a thread não tem mais nada pra fazer, ela sai do guichê de atendimento e volta a ficar inativa, ou volta para o final da fila, aguardando por mais processamento.

Uma thread pode opcionalmente ir para o final da fila por conta própria. Para isso, basta que ela chame uma função do sistema operacional pedindo para dormir. Por isso geralmente essa função é chamada de sleep na API do sistema operacional. Nessa função costuma haver um parâmetro de quanto tempo a thread deseja dormir. Se for maior que zero ela vai para a fila de threads dormindo até passar esse tempo, para depois se dirigir à fila de threads ativas, aguardar para ser processada. Se o tempo passado for exatamente zero ela vai direto para essa última fila, mas ficará sem executar do mesmo jeito, pois esta é a fila de quem está aguardando pela sua próxima fatia de tempo de processamento.

Se chamarmos a função para dormir no código da thread antes de voltar a incrementar o contador é possível que a segunda thread tenha chance de executar.

    increment() {
      while( count < 10 ) {
        count++;
        print(tid, count);
        sleep();
      }
    }

Agora cada thread, depois de incrementar uma vez o contador, volta para o final da fila. Dessa forma vemos uma thread de cada vez incrementando o mesmo contador.

    t1 1
    t2 2
    t1 2
    t2 3
    t1 4
    t2 4
    t2 6
    t2 7
    t1 5
    t1 8
    t2 8
    t2 9
    t2 10

Peraí, o mesmo contador? Isso pode gerar problemas. Se duas threads tentarem incrementar o mesmo contador ao mesmo tempo, quem garante que elas não irão incrementar o mesmo valor? Bom, se você é bom observador já deve ter reparado que na execução acima ocorreu exatamente isso, com mais de uma thread incrementando o contador com o mesmo valor.

Para forçar isso acontecer mais rápido e de maneira mais gritante podemos fazer a thread ir para o final da fila antes de incrementarmos e após pegarmos o valor atual do contador. Note que nesses testes a saída muda completamente dependendo de quantos processadores sua máquina tem. O resultado às vezes pode ser bem bizarro do que o visto nesse artigo. [^1]

    increment() {
      while( count < 10 ) {
        int c = count;
        sleep();
        c++;
        print(tid, c);
        count = c;
      }
    }

O código acima pode gerar a seguinte saída:

    t1 1
    t2 1
    t1 2
    t2 2
    t1 3
    t2 3
    t1 4
    t2 4
    t1 5
    t2 5
    t2 6
    t1 6
    t2 7
    t1 7
    t1 8
    t2 8
    t2 9
    t1 9
    t2 10
    t1 10

Explicando mais uma vez com mais detalhes: quando uma thread guarda o valor do contador na variável local e volta para o final da fila, ela deixa de armazenar o contador atualizado para apenas **depois** que todas as outras threads passarem na sua frente. Só que as outras threads também pegam o mesmo valor do contador, pois ele ainda não foi alterado. Quando chega a hora da segunda passada no guichê das CPUs, todas as threads incrementaram o mesmo valor do contador. Se houvesse apenas um processador em uma máquina o fluxo de execução do ponto de vista do processamento único para duas threads ficaria mais ou menos o seguinte (zzz é quando uma thread dorme):

    t1 c = count (0)
    t1 zzz
    t2 c = count (0)
    t2 zzz
    t1 c++ (1)
    t2 c++ (1)
    t1 print c (1)
    t2 print c (1)
    t1 count = c (1)
    t2 count = c (1)
    t1 c = count (1)
    t1 zzz
    t2 c = count (1)
    t2 zzz
    ...

O exemplo acima forçou essa situação, mas é preciso lembrar que isso pode acontecer mesmo sem a thread dormir. É possível que o tempo da thread se esgote e ela pare de ser atendida justo na hora que iria salvar a variável c no contador global. Dessa forma, ela vai para o final da fila à força e, quando voltar a ser atendida, uma outra thread já terá lido o valor anterior para ela própria incrementar.

O que gostaríamos que acontecesse para corrigir o problema é forçar a segunda thread a esperar antes que a primeira termine todo o processo de incrementar e salvar no contador global, o que resolveria o nosso problema (o wait no exemplo abaixo é uma thread aguardando e não fazendo nada):

    t1 c = count (0)
    t1 zzz
    t2 wait
    t1 c++ (1)
    t2 wait
    t1 print c (1)
    t2 wait
    t1 count = c (1)
    t2 wait
    t1 ready
    t2 c = count (1)
    t1 wait
    t2 c++ (2)
    t1 wait
    t2 print c (2)
    t1 wait
    t2 count = c (2)
    t2 ready
    t1 c = count (2)
    t2 wait
    ...

Esse wait do fluxo, ou seja, deixar a próxima thread aguardando a que chegou primeiro incrementar, pode ser obtido se utilizarmos um mecanismo de acesso exclusivo fornecido pelo sistema operacional. Uma outra história para contar, que chamarei de "A sala da fila das threads".

[^1]: Eu mesmo em meus testes não pude usar sleep passando zero como o tempo para dormir porque meu número de processadores não permite que eu faça esse experimento, já que sempre vão existir processadores dispostos a reprocessar a thread que acabou de ir para o final de sua fila.
