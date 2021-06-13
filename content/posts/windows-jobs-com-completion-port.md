---
categories:
- code
date: '2008-09-23'
tags:
- draft
title: Windows Jobs com Completion Port
---

Ou "Como esperar o término de todos os processos-filho criados a partir de um conjunto de processos".

Dessa vez confesso que esperava um pouco mais de documentação do MSDN, ou pelo menos um sistema de referências cruzadas eficiente. Outro dia demorei cerca de duas horas para conseguir [criar um _**job**_](http://msdn.microsoft.com/en-us/library/ms682409(VS.85).aspx), anexar o processo desejado e, a pior parte, esperar que todos os processos (o principal e seus filhos e netos) terminassem.

Além da [pouca documentação](http://msdn.microsoft.com/en-us/library/ms684161(VS.85).aspx), parece que não são muitas as pessoas que fazem isso e publicam na web, ou eu [não sei procurar direito](http://www.google.com.br/search?q=wait+all+processes+inside+job+object).

Mas, pra início de conversa, o que é um job mesmo?

#### Leve introdução sobre o conceito de jobs

Um job é um objeto "novo" no kernel do Windows 2000 em diante, e se prontifica a suprir a carência que havia anteriormente de **controle sobre o que os processos podem fazer e por quanto tempo**.

A abstração mais coerente que eu consigo tirar de um job é como **um trabalho a ser executada por um ou mais processos**. O objeto job controla a criação, o término e as exceções que ocorrem dentro dele mesmo.

[![job.gif](http://i.imgur.com/JJM9DY8.gif)](/images/job.gif)

Entre as funções mais úteis de um job estão limitar o tempo de execução do conjunto de processos, o número de handles/arquivos/outros objetos abertos, limite de memória RAM ocupada e a possibilidade de terminar todos os processos de uma só vez.

Para informações básicas de como criar um job e anexar processos recomendo o ótimo artigo de [Jeffrey Richter](http://www.microsoft.com/msj/0399/jobkernelobj/jobkernelobj.aspx).

No final desse artigo ele chega a citar o controle mais refinado dos processos através de uma [**completion port**](http://msdn.microsoft.com/en-us/library/aa365198(VS.85).aspx), que permitirá receber eventos que ocorrem dentro de um job durante sua vida útil. Apesar de citar, não há código de exemplo que faça isso.

Bom, agora há:

```cpp
#define _WIN32_WINNT 0x0500 // Jobs só existem do 2000 em diante
#include <windows.h>

/** @brief Função que cria um processo a partir de cmdLine
 * e coloca-o dentro de um job. A função aguarda o término
 * do processo e de qualquer subprocesso criado por este.
 */
DWORD CreateJobAndWait(LPSTR cmdLine)
{
   // primeiro, criamos um job sem nome
   HANDLE job = CreateJobObject(NULL, NULL);

   if( job )
   {
      STARTUPINFO si = { sizeof(si) };
      PROCESS_INFORMATION pi;

      // depois, criamos um processo suspenso (travado)
      if( CreateProcess(NULL, cmdLine, NULL, NULL, FALSE, 
         CREATE_SUSPENDED | CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi) )
      {
         // atribuímos esse processo ao nosso jobo
         AssignProcessToJobObject(job, pi.hProcess);

         // rodamos o processo
         ResumeThread(pi.hThread);

         // essa é uma completion i/o port genérica
         // (ou seja, não relacionada com nenhum arquivo
         // ou outra completion port)
         HANDLE port = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 
                 NULL, 0, 0);

         if( port )
         {
            JOBOBJECT_ASSOCIATE_COMPLETION_PORT jobPort;

            jobPort.CompletionKey = 0; // ver variável key abaixo
            jobPort.CompletionPort = port; // nossa completion port vai aqui!

            // definimos a c.p. em nosso job
            if( SetInformationJobObject(job, 
                        JobObjectAssociateCompletionPortInformation, 
                        &jobPort, sizeof(jobPort)) )
            {
               ULONG_PTR key = 0; // ver membro CompletionKey acima
               LPOVERLAPPED overlap = 0;
               DWORD tranferred = 0;

               // nosso loop de mensagens com completion port
               while( GetQueuedCompletionStatus(port, &tranferred, 
                  &key, &overlap, INFINITE) )
               {
                  // transferred especifica a mensagem
                  DWORD msg = *(LPDWORD) &tranferred;

                  // significa que não existem mais processos rodando
                  if( msg == JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO )
                     break; // saímos fora
               }
            }

            CloseHandle(port); // fecha tudo
         }

         CloseHandle(pi.hThread); // fecha tudo
         CloseHandle(pi.hProcess); // fecha tudo
      }

      CloseHandle(job); // fecha tudo
   }

   return 0;
}

int main(int argc, char* argv[])
{
   if( argc == 2 )
      CreateJobAndWait(argv[1]);
}

 

```

O exemplo acima cria um processo baseado em uma linha de comando e espera pelo término do processo criado e de todos os subprocessos criados a partir do primeiro processo. Note que mesmo que o primeiro processo termine, a Completion Port só receberá o evento que todos os processos acabaram depois que o último subprocesso terminar.

Dessa forma, ao compilarmos o código:

    
    C:\Tests\CreateJob>cl Createjob.cpp
    Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 15.00.21022.08 for 80x86
    Copyright (C) Microsoft Corporation.  All rights reserved.
    
    Createjob.cpp
    Microsoft (R) Incremental Linker Version 9.00.21022.08
    Copyright (C) Microsoft Corporation.  All rights reserved.
    
    /out:Createjob.exe
    Createjob.obj

E rodarmos mais um prompt de comando através de nosso programa (o texto em azul significa nossa nova janela de prompt):

    
    C:\Tests\CreateJob>Createjob.exe cmd        (travado)

Microsoft Windows XP [versão 5.1.2600] (C) Copyright 1985-2001 Microsoft Corp. C:\Tests\CreateJob>notepad C:\Tests\CreateJob>exit

    
    C:\Tests\CreateJob>                         (continua travado)
                                                (fechando notepad)

    
    C:\Tests\CreateJob>                         (deve destravar)

Mesmo ao fecharmos o prompt criado, o programa só será finalizado ao fecharmos o Bloco de Notas iniciado pelo segundo prompt.

Além desse evento, que era o que eu estava procurando, esse método permite obter outros eventos bem interessantes:

    
  * **JOB_OBJECT_MSG_NEW_PROCESS**. Um novo processo foi criado dentro do job.

    
  * ** JOB_OBJECT_MSG_EXIT_PROCESS**. Um processo existente dentro do job foi terminado.

    
  * **JOB_OBJECT_MSG_PROCESS_MEMORY_LIMIT**. O limite de memória de um processo já foi alcançado.

    
  * **JOB_OBJECT_MSG_END_OF_PROCESS_TIME**. O limite de tempo de processamento de um processo já foi alcançado.

Enfim, jobs não terminam por aí. Dê mais uma olhada no MSDN e veja se encontra mais alguma utilidade interessante para o nosso amigo job. Eu encontrei e fiquei feliz.
