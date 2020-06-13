---
categories: [ "code" ]
date: "2008-06-10"
tags: [ "draft",  ]
title: "Guia básico de repositórios no Bazaar"
---
Alguns conceitos-chave antes de trabalhar com o Bazaar são:

  * Revision (Revisão). Um snapshot dos arquivos que você está trabalhando.
  * Working Tree (Árvore de Trabalho). Um diretório contendo seus arquivos controlados por versão e subdiretórios.
  * Branch (Ramificação). Um grupo ordenado de revisões que descreve o histórico de um grupo de arquivos.
  * Repository (Repositório). Um depósito de revisões.

Agora vamos brincar um pouco com os conceitos.

O uso mais simples que existe no Bazaar é o controle de uma pasta sozinha, conhecida como uma Standalone Tree. Como toda Working Tree, ela possui um repositório relacionado, que no caso está dentro dela mesmo, na pasta oculta ".bzr".

Pra criar uma Standalone Tree, tudo que precisamos é usar o comando init de dentro da pasta a ser controlada, quando é criado um repositório local. Adicionamos arquivos para o repositório com o comando add, e finalizamos nossa primeira versão com o comando commit.
    
    C:\Tests>cd project1
    
    C:\Tests\project1>bzr init
    
    C:\Tests\project1>bzr add
    added AUTHORS
    added COPYING
    added COPYRIGHT
    added ChangeLog
    added ChangeLog.2
    added FAQ
    ...
    added winboard/extends/infboard/main.c
    added winboard/extends/infboard/msvc.mak
    added winboard/extends/infboard/support.c
    
    C:\Tests\project1>bzr commit -m "Comentario sobre a revisao"
    Committing to: C:/Tests/project1/
    added AUTHORS
    added COPYING
    added COPYRIGHT
    added ChangeLog
    added ChangeLog.2
    added FAQ
    ...
    added winboard/extends/infboard/main.c
    added winboard/extends/infboard/msvc.mak
    added winboard/extends/infboard/support.c
    Committed revision 1.
    
    C:\Tests\project1>

Feito. A partir daí temos um repositório onde podemos realizar o comando commit sempre que quisermos marcar um snapshot em nosso código-fonte.

Se quisermos fazer uma alteração muito grande em nosso pequeno projeto seria melhor termos outro diretório onde trabalhar antes de realizar o commit na versão estável. Para isso podemos usar o comando branch, que cria uma nova pasta com todo o histórico da pasta inicial até esse ponto. Os históricos em um branch estão duplicados em ambas as pastas, e portanto são independentes. Você pode apagar a pasta original ou a secundária que terá o backup inteiro no novo branch.

    
    C:\Tests\project1>cd ..
    
    C:\Tests>bzr branch project1 project1-changing
    Branched 1 revision(s).
    
    C:\Tests>cd project1-changing
    
    C:\Tests\project1-changing>

Criar um novo branch totalmente duplicado pode se tornar um desperdício enorme de espaço em disco (e tempo). Para isso foi criado o conceito de Shared Repository, que basicamente é um diretório acima dos branchs que trata de organizar as revisões em apenas um só lugar, com a vantagem de otimizar o espaço. Nesse caso, antes de criar o projeto, poderíamos usar o comando init-repo na pasta mãe de nosso projeto, e depois continuar com o processo de init dentro da pasta do projeto.

    
    C:\>bzr init-repo Tests
    
    C:\>cd Tests
    
    C:\Tests>bzr init project1

    
    C:\Tests>cd project1

    
    C:\Tests\project1>bzr add
    added AUTHORS
    added COPYING
    added COPYRIGHT
    added ChangeLog
    added ChangeLog.2
    added FAQ
    ...
    added winboard/extends/infboard/main.c
    added winboard/extends/infboard/msvc.mak
    added winboard/extends/infboard/support.c
    
    C:\Tests\project1>bzr commit -m "Comentario sobre a revisao"
    Committing to: C:/Tests/project1/
    added AUTHORS
    added COPYING
    added COPYRIGHT
    added ChangeLog
    added ChangeLog.2
    added FAQ
    ...
    added winboard/extends/infboard/main.c
    added winboard/extends/infboard/msvc.mak
    added winboard/extends/infboard/support.c
    Committed revision 1.
    
    C:\Tests\project1>

Se compararmos o tamanho, veremos que o repositório compartilhado é que detém a maior parte dos arquivos, enquanto agora o ".bzr" que está na pasta do projeto possui apenas dados de controle. A mesma coisa irá acontecer com qualquer branch criado dentro da pasta de repositório compartilhado.

Mas já criamos nossos dois branches cheios de arquivos, certo? Certo. Como já fizemos isso, devemos criar uma nova pasta como repositório compartilhado e criar dois novos branches dentro dessa pasta, cópias dos dois branches gordinhos:

    
    C:\Tests>bzr init-repo project1-repo
    
    C:\Tests>bzr branch project1 project1-repo\project1
    Branched 1 revision(s).
    
    C:\Tests>bzr branch project1-changing project1-repo\project-changing
    Branched 1 revision(s).
    
    C:\Tests>

Isso irá recriar esses dois branches como os originais, mas com a metade do espaço em disco, pois seus históricos estarão compartilhados na pasta project1-repo.

O SubVersion é um sistema de controle centralizado. O Bazaar consegue se comportar exatamente como o SubVersion, além de permitir carregar o histórico inteiro consigo. Quem decide como usá-lo é apenas você, pois cada usuário do sistema tem a liberdade de escolher a melhor maneira.

Os comandos para usar o Bazaar à SubVersion são os mesmos do SubVersion: checkout e commit. No entanto, um checkout irá fazer com que seu commit crie a nova revisão primeiro no seu servidor (branch principal) e depois localmente. Se você não deseja criar um histórico inteiro localmente, pode criar um checkout leve (parâmetro --lightweight), que apenas contém arquivos de controle. No entanto, se o servidor de fontes não estiver disponível, você não será capaz de ações que dependam dele, como ver o histórico ou fazer commits.

    
    C:\Tests\client>bzr checkout ..\server\project1
    
    C:\Tests\client>cd project1
    
    C:\Tests\client\project1>echo "New changes" >> FAQ
    
    C:\Tests\client\project1>bzr commit -m "New changes comment"
    Committing to: C:/Tests/server/project1/
    modified FAQ
    Committed revision 2.
    
    C:\Tests\client\project1>bzr log -l 1 ..\..\server\project1
    ------------------------------------------------------------
    revno: 2
    committer: Wanderley Caloni <wanderley@caloni.com.br>
    branch nick: project1
    timestamp: Sun 2008-06-08 19:52:17 -0300
    message:
      New changes comment
    
    C:\Tests\client\project1>

Na verdade, o Bazaar vai além, e permite que um branch/checkout específico seja conectado e desconectado em qualquer repositório válido. Para isso são usados os comandos bind e unbind. Um branch conectado faz commits remotos e locais, enquanto um branch unbinded faz commits apenas locais. É possível mudar esse comportamento com o parâmetro --local, e atualizar o branch local com o comando update.

	
  * Bazaar User Guide

	
  * Bazaar User Reference

