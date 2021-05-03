---
categories:
- code
date: '2019-07-21'
tags:
- draft
title: SLQLocalDB
---

Hoje foi o dia de redescobrir meu velho ranço com a solução Microsoft para banco de dados. Já perdi horas, dias e semanas com problemas de conexão com algum servidor SQL Server porque a instalação possuía configurações de segurança específicas, a string de conexão não estava exatamente de acordo com a versão instalada ou uma combinação macabra desses e de mais alguns problemas.

Após degladiar novamente com problemas com o SQL Server Express 17 minha esperança para este projeto que requer este banco de dados foi uma versão mínima chamada de LocalDB [1]. Essa versão tem objetivo de servir para desenvolvedores, pois é tão mínima que apenas roda quando você usa, além de permitir isolamento por contas e compartilhamento entre contas e até remoto via named pipe. Parece bom, não?

O marketing da Microsoft sempre será melhor do que as reais soluções entregues. Depois de ver tudo isso funcionar em um banco criado com o LocalDB em pequenos e simples passos, as dores de cabeça começaram na hora de compartilhar ou de criar do zero este mesmo banco em uma conta de sistema, que é como rodam geralmente os serviços do projeto:

    C:\WINDOWS\system32>psexec -s cmd.exe
    
    PsExec v2.11 - Execute processes remotely
    Copyright (C) 2001-2014 Mark Russinovich
    Sysinternals - www.sysinternals.com
    
    Microsoft Windows [Version 10.0.17763.615]
    (c) 2018 Microsoft Corporation. All rights reserved.
    C:\WINDOWS\system32>sqllocaldb i
    MSSQLLocalDB
    
    C:\WINDOWS\system32>sqllocaldb create "test"
    LocalDB instance "test" created with version 13.1.4001.0.
    
    C:\WINDOWS\system32>sqllocaldb start "test"
    LocalDB instance "test" started.
    
    C:\WINDOWS\system32>sqlcmd -S (localdb)\test
    ...
    ... hangs forever
    ...

O fun fact até aqui é que a primeira versão que tentei, a Express 2017, sequer chegava nesse ponto, dando erros de conexão com named pipe ou timeout no login. Não estou certo de como funcionaria um login em um acesso local em um arquivo, mas essa era uma mensagem extremamente longa e potencialmente inútil. Encontrei uma outra alma sofredora na internet neste mesmo dia de hoje que recomendou fazer o rollback para o Server 2016 [2] (por isso a versão 13.1 no prompt acima), mas os erros apenas mudam de figura ou se repetem indefinidamente.

Aliás, outro fato curioso e revoltante é que a Microsoft sequer mantém a versão anterior dos seus produtos para download. A versão 2016 achei no site de alguém que se dispôs a mantê-los. Do contrário, a solução seria ~~sentar e chorar~~ olhar o código-fonte.

Rá, brincadeira. Não tem o código-fonte.

Um erro frequente e algumas vezes reportado pelas internet é o do login, mesmo. Pesquisando mais a fundo encontrei um artigo no Code Project [3] (quem diria, velhos tempos em que postava nele) de 2014 onde a pessoa explicava que depois de ler muito e testar muito ele descobriu praticamente depurando a instância do SQL Server e descobrindo que o problema estava em um crash que nunca voltava, sendo necessário dropar todas as conexões (ou o conhecido restart que várias pessoas também recomendaram).

Esse não é o meu problema. Meu problema é conseguir rodar a solução na conta de sistema, e desconfio que o modo em que o psexec executa o cmd.exe na conta de sistema pode estar relacionado, pois contas interativas em sistema são fontes clássicas de configuration mismatch (talvez falte ou sobre variáveis de ambiente, alguns handles perdidos, essas coisas).

 - [1] https://docs.microsoft.com/en-us/sql/database-engine/configure-windows/sql-server-express-localdb
 - [2] https://feedback.azure.com/forums/908035-sql-server/suggestions/36481279-sql-server-2017-express-localdb-shared-instance-co
 - [3] https://www.codeproject.com/Tips/775607/How-to-fix-LocalDB-Requested-Login-failed
