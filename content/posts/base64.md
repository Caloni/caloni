---
categories: [ "code" ]
date: "2011-03-09"
tags: [ "draft",  ]
title: "Base64"
---
No meio dos meus artigos pendentes, encontrei esse, de Luiz Rocha, que fala sobre a dificuldade de entender o que seria Base64:


Não é a primeira pessoa que pede informações sobre algo específico demais para explicar (para isso existe a Wikipedia e o Google, não?). No meio da minha escrita, percebi que já havia escrito sobre os fundamentos do conhecimento por trás da criação do Base64, conhecimento esse, acredito eu, todo programador que quer sair do lugar com os próprios pés deve ter.

	
  * Básico do básico: assembly

	
  * Básico do básico: binário <-- Luiz, você está procurando por esse!

	
  * Básico do básico: tipos

	
  * Básico do básico: ponteiros

Bônus:

	
  * Como ofuscar strings

	
  * Passagem por valor e emails com anexo

	
  * Como funcionam as strings

REALMENTE para iniciantes:

	
  * Configurando seus projetos no Visual Studio

	
  * Como criar uma LIB no Visual Studio

Acredito que tudo que um programador precisa saber é o básico. O problema é que esse básico cresce a cada ano, mas, de qualquer forma, continua sendo necessário voltar às raízes de vez em quando, e se existe algo que ele nunca deve esquecer, é isso.

Até porque na programação, 90% não se cria, se copia.

Imaginemos o cenário para a criação do Base64:

Alguns meios de comunicação, notadamente envio de e-mails e a navegação web, por incrível que pareça, trabalham em um protocolo totalmente em modo texto. É até fácil de entender, pois quando essas tecnologias nasceram as limitações de velocidade e estabilidade das conexões permitiam apenas o envio de texto puro de uma ponta a outra.

Isso quer dizer que, na prática, os anexos de um e-mail e as imagens de uma página trafegam, pelo protocolo definido, em modo texto.

Como isso é possível?

A solução não é tão obscura quanto possa parecer. Se um programador médio tivesse esse problema e nenhuma solução existisse ainda, ele faria o que sempre fez para resolver problemas desse tipo: codificar a mensagem na forma permitida. Isso já é feito com o próprio texto, que é apenas uma interpretação de tabelas de caracteres.

Tudo que é necessário fazer é o contrário, mas usando a mesma lógica: montar uma tabela de caracteres válidos e traduzir para um conteúdo binário, sendo que todas as combinações possíveis devem caber nessa tabela.

A forma mais básica binária de comunicação é um byte, constituído por 8 bits, que combinados darão 2^8 entradas em nossa tabela, que precisaria de 256 caracteres diferentes. Como isso ultrapassa o limite dos protocolos que estamos lidando, que em sua maioria utilizam a tabela ascii básica, que possui 128 posições, sendo que algumas posições não possuem caracteres imprimíveis, decidiu-se usar o múltiplo anterior: 64 posições, o que nos dá a chance de codificar 6 bits de cada vez (2^6).

Esse padrão de codificação se chama Base64. Se quiser mais detalhes, basta ler a RFC, que é pequena e muito simples de se ler.

Agora, como codificar essa solução? Só entendendo o básico, é claro.
