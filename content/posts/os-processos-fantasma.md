---
date: "2008-08-20"
title: Os processos-fantasma
tags: [ "draft", "code" ]
---
Estava eu outro belo dia tentando achar um problema em um driver que controla criação de processos quando, por acaso, listo os processos na máquina pelo depurador de kernel, após ter dado alguns logons e logoffs, quando me vem a seguinte lista de processos do Windows Explorer:

    
    PROCESS <font color="#ff0000">815f0da0</font>  SessionId: 0  Cid: 0694    Peb: 7ffd8000  ParentCid: 0100
        DirBase: 0d6e9000  ObjectTable: 00000000  HandleCount:   0.
        Image: explorer.exe
    
    PROCESS 8164bda0  SessionId: 0  Cid: 03b0    Peb: 7ffdf000  ParentCid: 0100
        DirBase: 02673000  ObjectTable: 00000000  HandleCount:   0.
        Image: explorer.exe
    
    PROCESS 815f7d50  SessionId: 0  Cid: 020c    Peb: 7ffd9000  ParentCid: 0100
        DirBase: 0bc7f000  ObjectTable: 00000000  HandleCount:   0.
        Image: explorer.exe
    
    PROCESS 8164c698  SessionId: 0  Cid: <font color="#ff0000">0794    </font>Peb: 7ffde000  ParentCid: 0100
        DirBase: 0cb08000  ObjectTable: e1a40f20  HandleCount: 279.
        Image: explorer.exe

Analisando pelo Gerenciador de Tarefas, podemos detectar que o único processo de pé possui o PID (Process ID) do último elemento de nossa lista, curiosamente o único com um contador de handles diferente de zero.

![unico-explorer-no-sistema.PNG](/images/unico-explorer-no-sistema.PNG)

Lembrando que 1940 em hexadecimal é 0x794, exatamente o valor deixado em destaque na lista acima, e reproduzido abaixo:

    
    PROCESS 8164c698  SessionId: 0  Cid: <font color="#ff0000">0794    </font>Peb: 7ffde000  ParentCid: 0100
        DirBase: 0cb08000  ObjectTable: e1a40f20  HandleCount: 279.
        Image: explorer.exe

Sendo ele o único processo a rodar, a única explicação válida para as outras instâncias do explorer.exe estarem de pé seria o fato de haver algum outro processo (inclusive o sistema operacional) com um handle aberto para ele. Felizmente isso pode ser facilmente verificado pelo uso do comando !object do WinDbg, no caso abaixo com o primeiro explorer.exe da lista, utilizando-se a sua estrutura EPROCESS (em vermelho na lista acima).

    
    kd> !object 815f0da0
    Object: 815f0da0  Type: (817cce70) Process
        ObjectHeader: 815f0d88 (old version)
        HandleCount: <font color="#ff0000">2</font>  PointerCount: <font color="#ff0000">3</font>

Muito bem. Temos dois handles e dois ponteiros ainda abertos para o objeto processo-fantasma explorer.exe. O fato de haver um handle aberto indica que é muito provável que se trate de um outro processo rodando em user mode, já que normalmente as referências para objetos dentro do kernel são feitas com o uso de ponteiros.

Para descobrirmos quem detém esse handle, existe o comando !handle, que pode exibir informações sobre todos os handles de um determinado tipo no processo atual. Como queremos procurar por todos os handles do tipo Process em todos os processos existentes, é necessário usá-lo em conjunto com o comando mais esperto [!for_each_process](http://www.dumpanalysis.org/blog/index.php/2008/05/30/who-opened-that-file/), que pode fazer coisas incríveis para o programador de user/kernel:

    
    kd> !for_each_process "!handle 0 1 @#Process Process"
    processor number 0, process 817cc830
    Searching for handles of type Process
    PROCESS 817cc830  SessionId: none  Cid: 0004    Peb: 00000000  ParentCid: 0000
        DirBase: 00039000  ObjectTable: e1000cc0  HandleCount: 286.
        Image: System
    
    Handle table at e1002000 with 286 Entries in use
    0004: Object: 817cc830  GrantedAccess: 001f0fff
    
    0298: Object: 8169a958  GrantedAccess: 001f03ff
    
    0308: Object: 8156c880  GrantedAccess: 00000438
    
    067c: Object: 816744e8  GrantedAccess: 001f03ff
    
    processor number 0, process 81589020
    Searching for handles of type Process
    PROCESS 81589020  SessionId: none  Cid: 016c    Peb: 7ffd7000  ParentCid: 0004
        DirBase: 06978000  ObjectTable: e130d688  HandleCount:  21.
        Image: smss.exe
    
    Handle table at e12a5000 with 21 Entries in use
    0038: Object: 81561128  GrantedAccess: 001f0fff
    
    003c: Object: 81561128  GrantedAccess: 00000400
    
    0050: Object: 815b2128  GrantedAccess: 001f0fff
    
    0054: Object: 81668020  GrantedAccess: 00000400
    
    processor number 0, process 81561128
    Searching for handles of type Process
    PROCESS 81561128  SessionId: 0  Cid: 0234    Peb: 7ffde000  ParentCid: 016c
        DirBase: 0742d000  ObjectTable: e13e0418  HandleCount: 342.
        Image: csrss.exe
    
    Handle table at e14f3000 with 342 Entries in use
    0014: Object: 815b2128  GrantedAccess: 001f0fff
    
    00ec: Object: 8154e880  GrantedAccess: 001f0fff
    
    0100: Object: 8156c880  GrantedAccess: 001f0fff
    
    0130: Object: 815dc798  GrantedAccess: 001f0fff
    
    processor number 0, process 815b2128
    Searching for handles of type Process
    PROCESS 815b2128  SessionId: 0  Cid: 024c    Peb: 7ffde000  ParentCid: 016c
        DirBase: 075b2000  ObjectTable: e13d5790  HandleCount: 448.
        Image: winlogon.exe
    
    Handle table at e102b000 with 448 Entries in use
    018c: Object: 8154e880  GrantedAccess: 001f0fff
    
    019c: Object: 8156c880  GrantedAccess: 001f0fff
    
    processor number 0, process 8154e880
    Searching for handles of type Process
    PROCESS 8154e880  SessionId: 0  Cid: 0290    Peb: 7ffda000  ParentCid: 024c
        DirBase: 07908000  ObjectTable: e15fea78  HandleCount: 261.
        Image: services.exe
    
    Handle table at e15cf000 with 261 Entries in use
    029c: Object: 81668020  GrantedAccess: 001f0fff
    
    0330: Object: 815dc798  GrantedAccess: 001f0fff

    
    ... continua por muuuuuuuito mais tempo

Uma simples busca pelo EPROCESS do processo-fantasma nos retorna dois processos que o estão referenciando: um svchost.exe e um outro processo com um nome muito suspeito, provavelmente feito sob encomenda para a confecção desse artigo:

    
    Handle table at e167b000 with 247 Entries in use
    processor number 0, process 8169a958
    Searching for handles of type Process
    PROCESS 8169a958  SessionId: 0  Cid: 03f4    Peb: 7ffdb000  ParentCid: 0290
        DirBase: 08437000  ObjectTable: e156bc38  HandleCount: 1302.
        Image: svchost.exe
    
    Handle table at e19fe000 with 1302 Entries in use
    0108: Object: 815b2128  GrantedAccess: 00000478
    
    0128: Object: 815b2128  GrantedAccess: 00000478
    
    012c: Object: 815b2128  GrantedAccess: 00100000
    
    015c: Object: 815b2128  GrantedAccess: 0000047a
    
    01f4: Object: 81615928  GrantedAccess: 00000478
    
    02f0: Object: 815f7d50  GrantedAccess: 00100068
    
    035c: Object: 8169a958  GrantedAccess: 001f0fff
    
    0dbc: Object: 8156c880  GrantedAccess: 00100000
    
    0f44: Object: 8169a958  GrantedAccess: 00000068
    
    <font color="#ff0000">1020: Object: 815f0da0  GrantedAccess: 00100068</font>
    
    10dc: Object: 8169a958  GrantedAccess: 00100000
    
    1118: Object: 815f42f0  GrantedAccess: 00100068

    
    ...

    
    processor number 0, process 8164c220
    Searching for handles of type Process
    PROCESS 8164c220  SessionId: 0  Cid: 044c    Peb: 7ffdf000  ParentCid: 02a4
        DirBase: 0db16000  ObjectTable: e15c66b8  HandleCount:  12.
        Image: <font color="#ff0000">ProcessLeaker.exe</font>
    
    Handle table at e103a000 with 12 Entries in use
    <font color="#ff0000">0010: Object: 815f0da0  GrantedAccess: 00100000</font>
    
    001c: Object: <font color="#ff0000">815f42f0  </font>GrantedAccess: 00100000
    
    0028: Object: <font color="#ff0000">8164bda0  </font>GrantedAccess: 00100000
    
    002c: Object: <font color="#ff0000">815f7d50  </font>GrantedAccess: 00100000
    
    0030: Object: <font color="#ff0000">8164c698  </font>GrantedAccess: 00100000

Se lembrarmos o ponteiro dos outros processos, podemos notar que ele está bloqueando todas as outras instâncias dos antigos explorer.exe, executados em outras sessões do usuário:

    
    PROCESS <font color="#ff0000">815f0da0</font>  SessionId: 0  Cid: 0694    Peb: 7ffd8000  ParentCid: 0100
        DirBase: 0d6e9000  ObjectTable: 00000000  HandleCount:   0.
        Image: explorer.exe
    
    PROCESS <font color="#ff0000">8164bda0</font>  SessionId: 0  Cid: 03b0    Peb: 7ffdf000  ParentCid: 0100
        DirBase: 02673000  ObjectTable: 00000000  HandleCount:   0.
        Image: explorer.exe
    
    PROCESS <font color="#ff0000">815f7d50</font>  SessionId: 0  Cid: 020c    Peb: 7ffd9000  ParentCid: 0100
        DirBase: 0bc7f000  ObjectTable: 00000000  HandleCount:   0.
        Image: explorer.exe
    
    PROCESS <font color="#ff0000">8164c698</font>  SessionId: 0  Cid: <font color="#000000">0794    </font>Peb: 7ffde000  ParentCid: 0100
        DirBase: 0cb08000  ObjectTable: e1a40f20  HandleCount: 279.
        Image: explorer.exe

Esse ProcessLeaker se tratava de um serviço do mesmo produto que contém de fato um leak de recurso: em um dado momento ele abre um handle para o processo explorer.exe, só que por alguns motivos obscuros ele não é fechado nunca, gerando uma lista interminável de processos-fantasma. E é lógico que ele originalmente não chama ProcessLeaker.exe =)

Essa análise mostra duas coisas: que com um pouco de conhecimento e atitude é possível encontrar bugs em outras partes do programa, mesmo quando resolvendo outros problemas e que, nem sempre o problema está onde parece estar, que seria no nosso querido driver de controle de processos do começo da história.
