---
date: "2008-02-05"
tags: [ "code", "draft",  ]
title: "Process Monitor e o monopólio malcriado"
---

Essa é uma regra básica, mas não é fácil de cumpri-la.  Só quem já tentou fazer isso sabe do que estou falando. Inúmeros programas mal-escritos vão tentar, de uma hora pra outra, acessar áreas do sistema de arquivos e registro que não possuem acesso, pois agora estão rodando em uma conta mais restrita. E não são programas de administração ou manutenção do sistema. Estou falando de programas de escritório e jogos. Aqui vai um singelo exemplo que tive que lidar esse fim-de-semana.

Primeiramente, quero deixar bem claro que jogamos Monopoly por mais ou menos dois meses sem ter qualquer tipo de problema, em três computadores diferentes. Até que resolvemos usar uma conta mais restrita. Foi o bastante para o programinha inocente começar a chiar.

Mau garoto. Bons tempos em que quando um jogo travava o máximo que tínhamos que fazer era apertar um botão.

Para encontrar problemas desse tipo, sempre uso o Process Monitor, que tem virado minha ferramenta básica para muitas coisas. Para os que não conhecem, o Process Monitor é uma ferramenta de auditoria de operações no sistema operacional, ou seja, tudo que alguém ler e escrever em arquivos e no registro será logado.

Sua função é mostrar tudo, absolutamente tudo que o sistema está fazendo em um determinado espaço no tempo. Isso pode ser ruim por um lado, já que será bem difícil encontrar alguma informação útil no meio de tanto lixo que pode ser gerado em um log de poucos momentos. Para ter uma idéia do que eu estou falando, tente abrir o Procmon sem qualquer filtro e deixá-lo rodando por 30 segundos sem fazer nada. No meu sistema, isso deu aproximadamente 20 000 linhas de eventos de log. Nada mau para um sistema ocioso.

É por isso que ele vem "de fábrica" já com uma série de filtros, que evitam lotar o log de eventos com informação sempre gerada pelo sistema, mas quase sempre inútil. Além dos filtros-padrão, podemos inserir nossos próprios filtros. É isso que faremos aqui para pegar o monopólio malcriado (sem trocadilhos).

Como podemos ver, iremos mostrar em nosso log todos os eventos cujo nome do processo seja monopolyclassic.exe (o nosso amigo faltoso) e iremos excluir do log qualquer evento cujo resultado tenha sido sucesso (se deu certo, provavelmente não é um erro).

Executamos novamente o jogo, dessa vez com o Process Monitor capturando todos seus movimentos.

Agora, uma pequena ressalva: eu estou cansado de ver isso, mas para quem nunca viu, pode não ser tão óbvio. Como eu disse no início do artigo, programas mal-escritos costumam tentar acessar áreas do sistema que não são acessíveis para usuários comuns. Isso quer dizer que, se o problema que está acontecendo com o jogo tem a ver com essa peculiaridade, a primeira coisa a procurar é por erros de acesso negado.

A primeira busca retorna uma chave no registro referente às propriedades de joystick. Como não estou usando joysticks, podemos ignorar este erro por enquanto e passar adiante.


O próximo erro diz respeito a uma tentativa de acesso ao arquivo Monopoly.log localizado no diretório de instalação do jogo, o que já é mais sugestivo. Podemos fazer um pequeno teste alterando o acesso desse arquivo.


Como podemos ver, o que é muito natural, um arquivo dentro da pasta de instalação de programas permite acesso de somente leitura para usuários comuns a seus arquivos, inclusive o Monopoly.log. Para fazer o teste, podemos simplesmente adicionar controle total a apenas esse arquivo, e rodar novamente o jogo.



Ora essa, estou conseguindo rodar o jogo! Isso quer dizer que nosso único problema, o acesso a esse arquivo, foi resolvido. Sabendo que um arquivo de log provavelmente não será executado por nenhuma conta privilegiada, podemos deixá-lo com acesso irrestrito para todos.

Para ter certeza que isso resolveu o problema, uma segunda auditoria de execução executada pelo Process Monitor pode nos revelar mais detalhes.


Moral da história: se algum dia você vier a escrever um programa inocente, deixe que pessoas inocentes consigam utilizá-lo.
