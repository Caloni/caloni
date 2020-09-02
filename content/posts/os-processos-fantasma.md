---
date: "2008-08-20"
tags: [ "code", "draft",  ]
title: "Os processos-fantasma"
---
Estava eu outro belo dia tentando achar um problema em um driver que controla criação de processos quando, por acaso, listo os processos na máquina pelo depurador de kernel, após ter dado alguns logons e logoffs, quando me vem a seguinte lista de processos do Windows Explorer:


Analisando pelo Gerenciador de Tarefas, podemos detectar que o único processo de pé possui o PID (Process ID) do último elemento de nossa lista, curiosamente o único com um contador de handles diferente de zero.

Lembrando que 1940 em hexadecimal é 0x794, exatamente o valor deixado em destaque na lista acima, e reproduzido abaixo:


Sendo ele o único processo a rodar, a única explicação válida para as outras instâncias do explorer.exe estarem de pé seria o fato de haver algum outro processo (inclusive o sistema operacional) com um handle aberto para ele. Felizmente isso pode ser facilmente verificado pelo uso do comando !object do WinDbg, no caso abaixo com o primeiro explorer.exe da lista, utilizando-se a sua estrutura EPROCESS (em vermelho na lista acima).


Muito bem. Temos dois handles e dois ponteiros ainda abertos para o objeto processo-fantasma explorer.exe. O fato de haver um handle aberto indica que é muito provável que se trate de um outro processo rodando em user mode, já que normalmente as referências para objetos dentro do kernel são feitas com o uso de ponteiros.

Para descobrirmos quem detém esse handle, existe o comando !handle, que pode exibir informações sobre todos os handles de um determinado tipo no processo atual. Como queremos procurar por todos os handles do tipo Process em todos os processos existentes, é necessário usá-lo em conjunto com o comando mais esperto !foreachprocess, que pode fazer coisas incríveis para o programador de user/kernel:



Uma simples busca pelo EPROCESS do processo-fantasma nos retorna dois processos que o estão referenciando: um svchost.exe e um outro processo com um nome muito suspeito, provavelmente feito sob encomenda para a confecção desse artigo:




Se lembrarmos o ponteiro dos outros processos, podemos notar que ele está bloqueando todas as outras instâncias dos antigos explorer.exe, executados em outras sessões do usuário:


Esse ProcessLeaker se tratava de um serviço do mesmo produto que contém de fato um leak de recurso: em um dado momento ele abre um handle para o processo explorer.exe, só que por alguns motivos obscuros ele não é fechado nunca, gerando uma lista interminável de processos-fantasma. E é lógico que ele originalmente não chama ProcessLeaker.exe =)

Essa análise mostra duas coisas: que com um pouco de conhecimento e atitude é possível encontrar bugs em outras partes do programa, mesmo quando resolvendo outros problemas e que, nem sempre o problema está onde parece estar, que seria no nosso querido driver de controle de processos do começo da história.
