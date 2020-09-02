---
date: "2008-06-10"
tags: [ "code", "draft",  ]
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

Feito. A partir daí temos um repositório onde podemos realizar o comando commit sempre que quisermos marcar um snapshot em nosso código-fonte.

Se quisermos fazer uma alteração muito grande em nosso pequeno projeto seria melhor termos outro diretório onde trabalhar antes de realizar o commit na versão estável. Para isso podemos usar o comando branch, que cria uma nova pasta com todo o histórico da pasta inicial até esse ponto. Os históricos em um branch estão duplicados em ambas as pastas, e portanto são independentes. Você pode apagar a pasta original ou a secundária que terá o backup inteiro no novo branch.


Criar um novo branch totalmente duplicado pode se tornar um desperdício enorme de espaço em disco (e tempo). Para isso foi criado o conceito de Shared Repository, que basicamente é um diretório acima dos branchs que trata de organizar as revisões em apenas um só lugar, com a vantagem de otimizar o espaço. Nesse caso, antes de criar o projeto, poderíamos usar o comando init-repo na pasta mãe de nosso projeto, e depois continuar com o processo de init dentro da pasta do projeto.




Se compararmos o tamanho, veremos que o repositório compartilhado é que detém a maior parte dos arquivos, enquanto agora o ".bzr" que está na pasta do projeto possui apenas dados de controle. A mesma coisa irá acontecer com qualquer branch criado dentro da pasta de repositório compartilhado.

Mas já criamos nossos dois branches cheios de arquivos, certo? Certo. Como já fizemos isso, devemos criar uma nova pasta como repositório compartilhado e criar dois novos branches dentro dessa pasta, cópias dos dois branches gordinhos:


Isso irá recriar esses dois branches como os originais, mas com a metade do espaço em disco, pois seus históricos estarão compartilhados na pasta project1-repo.

O SubVersion é um sistema de controle centralizado. O Bazaar consegue se comportar exatamente como o SubVersion, além de permitir carregar o histórico inteiro consigo. Quem decide como usá-lo é apenas você, pois cada usuário do sistema tem a liberdade de escolher a melhor maneira.

Os comandos para usar o Bazaar à SubVersion são os mesmos do SubVersion: checkout e commit. No entanto, um checkout irá fazer com que seu commit crie a nova revisão primeiro no seu servidor (branch principal) e depois localmente. Se você não deseja criar um histórico inteiro localmente, pode criar um checkout leve (parâmetro --lightweight), que apenas contém arquivos de controle. No entanto, se o servidor de fontes não estiver disponível, você não será capaz de ações que dependam dele, como ver o histórico ou fazer commits.


Na verdade, o Bazaar vai além, e permite que um branch/checkout específico seja conectado e desconectado em qualquer repositório válido. Para isso são usados os comandos bind e unbind. Um branch conectado faz commits remotos e locais, enquanto um branch unbinded faz commits apenas locais. É possível mudar esse comportamento com o parâmetro --local, e atualizar o branch local com o comando update.

	
  * Bazaar User Guide

	
  * Bazaar User Reference

