---
date: "2008-09-23"
tags: [ "code", "draft",  ]
title: "Windows Jobs com Completion Port"
---
Ou "Como esperar o término de todos os processos-filho criados a partir de um conjunto de processos".

Dessa vez confesso que esperava um pouco mais de documentação do MSDN, ou pelo menos um sistema de referências cruzadas eficiente. Outro dia demorei cerca de duas horas para conseguir criar um job.aspx), anexar o processo desejado e, a pior parte, esperar que todos os processos (o principal e seus filhos e netos) terminassem.

Além da pouca documentação.aspx), parece que não são muitas as pessoas que fazem isso e publicam na web, ou eu não sei procurar direito.

Mas, pra início de conversa, o que é um job mesmo?

Um job é um objeto "novo" no kernel do Windows 2000 em diante, e se prontifica a suprir a carência que havia anteriormente de controle sobre o que os processos podem fazer e por quanto tempo.

A abstração mais coerente que eu consigo tirar de um job é como um trabalho a ser executada por um ou mais processos. O objeto job controla a criação, o término e as exceções que ocorrem dentro dele mesmo.

Entre as funções mais úteis de um job estão limitar o tempo de execução do conjunto de processos, o número de handles/arquivos/outros objetos abertos, limite de memória RAM ocupada e a possibilidade de terminar todos os processos de uma só vez.

Para informações básicas de como criar um job e anexar processos recomendo o ótimo artigo de Jeffrey Richter.

No final desse artigo ele chega a citar o controle mais refinado dos processos através de uma completion port.aspx), que permitirá receber eventos que ocorrem dentro de um job durante sua vida útil. Apesar de citar, não há código de exemplo que faça isso.

Bom, agora há:


O exemplo acima cria um processo baseado em uma linha de comando e espera pelo término do processo criado e de todos os subprocessos criados a partir do primeiro processo. Note que mesmo que o primeiro processo termine, a Completion Port só receberá o evento que todos os processos acabaram depois que o último subprocesso terminar.

Dessa forma, ao compilarmos o código:


E rodarmos mais um prompt de comando através de nosso programa (o texto em azul significa nossa nova janela de prompt):


Microsoft Windows XP [versão 5.1.2600] (C) Copyright 1985-2001 Microsoft Corp. C:\Tests\CreateJob>notepad C:\Tests\CreateJob>exit



Mesmo ao fecharmos o prompt criado, o programa só será finalizado ao fecharmos o Bloco de Notas iniciado pelo segundo prompt.

Além desse evento, que era o que eu estava procurando, esse método permite obter outros eventos bem interessantes:

  * JOB_OBJECT_MSG_NEW_PROCESS. Um novo processo foi criado dentro do job.
  * JOB_OBJECT_MSG_EXIT_PROCESS. Um processo existente dentro do job foi terminado.
  * JOB_OBJECT_MSG_PROCESS_MEMORY_LIMIT. O limite de memória de um processo já foi alcançado.
  * JOB_OBJECT_MSG_END_OF_PROCESS_TIME. O limite de tempo de processamento de um processo já foi alcançado.

Enfim, jobs não terminam por aí. Dê mais uma olhada no MSDN e veja se encontra mais alguma utilidade interessante para o nosso amigo job. Eu encontrei e fiquei feliz.
