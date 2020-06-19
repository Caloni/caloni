---
categories: [ "code" ]
date: "2008-04-15"
tags: [ "draft",  ]
title: "Guia básico de controle de código (Mercurial)"
---
Houve um bom motivo para que, semana passada, eu estivesse caçando inúmeras versões de um projeto desenvolvido fora da empresa: falta de controle de código. Esse tipo de lapso pode consumir de horas a dias de tempo perdido, dependendo de em quantas cópias de máquinas virtuais ficou espalhado o código.

Já escrevi a respeito da importância de controlar e gerenciar o código-fonte para que a falta de um histórico exato das alterações não seja motivo de recorreções de problemas, binários no cliente sem contraparte para ajustes, além de uma série de dores de cabeça que costumam começar a ocorrer assim que nos damos conta que nosso software está uma bagunça que dói.

Na época, discursei brevemente sobre alguns exemplos de gerenciadores de fonte que utilizam modelo centralizado, e nos exemplos práticos usamos o famigerado Source Safe, velho amigo de quem já programa ou programou Windows por alguns anos. Além dele, temos os conhecidíssimos CVS e Subversion, ambos largamente utilizados no mundo todo.

No entanto, uma nova forma de controlar fontes está nascendo já há algum tempo, com relativo sucesso e crescentes esperanças: o modelo distribuído. Nesse tipo de gerenciamento, a liberdade aumenta exponencialmente, permitindo coisas que no modelo antigo seriam muito difíceis de serem implementadas. Não vou me delongar explicando a teoria por trás da idéia, sabendo que, além de existir um ótimo texto explicando as vantagens em cima do modelo centralizado disponível na web, o próprio sítio das implementações atuais explica a idéia de maneira muito convincente. E são elas:

  * Git. Conhecido como o controlador de fontes do _kernel_ do Linux. Escrita a versão inicial por Linux Torvalds em C e módulos de Perl pendurados, hoje em dia tem como principal desvantagem a falta de suporte nos ambientes Windows, impactando negativamente em projetos portáveis. Sua principal vantagem, no entanto, é a rapidez: é o controle de fonte mais rápido do oeste.
  * Mercurial (ou hg). Sem dúvida o mais fácil de usar. Bem documentado e com comandos intuitivos para o usuário, vem ganhando mais adeptos a cada dia. Seu desempenho é comparável ao do Git, e seu sistema de arquivos é bem eficiente.
  * Bazaar (ou bzr). O irmão mais próximo do Mercurial, com comandos bem parecidos. Um costuma lembrar os comandos do outro, com pequenas diferenças. Seu desempenho não chega a ser comparável aos dois acima, mas sua robustez compensa, pois é o único, de acordo com testes e estudos, que suporta o controle total de operações de renomeação de arquivos e pastas. Recentemente seu projeto tem evoluído muito.

Nos sistemas centralizados o repositório de fontes fica em um lugar definido, de onde as pessoas pegam a última versão e sobem modificações, ou não, caso não tenham direito para isso.

Nos sistemas distribuídos, o histórico e ramificações ficam todos locais. Como assim locais? Bom, locais do jeito que eu estou falando quer dizer: na própria pasta onde se está desenvolvendo.

É lógico que pode existir uma versão de ramificações no servidor, que no caso do controle distribuído é mais um membro da rede peer-to-peer de ramificações, já que cada colaborador possui seu próprio repositório local, capaz de trocar revisões entre colaboradores e subir revisões os servidores que interessarem.

Além disso, o conceito de ramificações (branches) e consolidação de versões (merging) é muito mais presente do que em sistemas como o Subversion, onde o commit (ato de enviar as revisões de um código para o repositório central) ocorre de forma controlada. Da maneira distribuída, é comum criar um branch para cada problema ou feature sendo desenvolvida, e ir juntando tudo isso imediatamente após terminado, gerando um histórico bem mais detalhado e livre de gargalos com modificações temporárias.

Porém, a maior vantagem em termos de desenvolvimento acaba sendo a liberdade dos usuários, que podem trocar modificações de código entre si, sem existir a figura centralizadora do branch oficial. Ela pode existir, mas não é mais uma condição sine qua non para modificações no fonte.

Comecei a usar em meus projetos pessoais o Mercurial por ter ouvido falar dele primeiro. Achei a idéia fantástica, pois já estava à procura de um substituto para meu velho Source Safe, meio baleado das tantas inovações de controle de fonte que surgiram nos projetos de fonte aberto. Outro motivo para desistir do Source Safe foi o fato de ser uma solução comercial que custa dinheiro e não chega a ser absurdamente mais fácil de usar a ponto de valer a pena usá-lo.

O princípio de uso de uma ferramenta distribuída é muito simples: se você tiver um diretório de projeto já criado, basta, dentro dessa pasta, iniciar o repositório de fontes.


Após isso, será criada uma pasta com o nome .hg. Dentro dela é armazenado todo o histórico dos fontes. Podemos inicialmente adicionar os arquivos do projeto existente e fazer o primeiro commit, que irá começar a controlar os arquivos adicionados dentro dessa pasta e subpastas:



Se o programa não disse nada ao efetuar o commit, é porque está tudo certo. Agora podemos controlar as mudanças de nosso código usando o comando status. Para vermos o histórico usamos o comando log.



Como vimos, ao alterar um arquivo controlado este é mostrado pelo comando status como alterado (o M na frente do Main.cpp). Também existem controles para cópia e exclusão de arquivos.

Esse é o básico que se precisa saber para usar o Mercurial. Simples, não? O resto também é simples: fazer branches e juntá-los é uma questão de costume, e está entre as boas práticas de uso. Eu recomendo fortemente a leitura do tutorial "Entendendo o Mercurial", disponível no sítio do projeto, até para entender o que existe por trás da idéia do controle descentralizado de fontes. Existe uma tradução muito boa feita pelo meu amigo Márcio.

Como usuário de Windows, posso dizer que a versão funciona muito bem, e é possível fazer coisas como, por exemplo, usar o WinMerge para juntar branches ou comparar versões automaticamente, o que por si só já mata toda a necessidade que eu tinha do Source Safe.

Testei o Mercurial por cerca de três meses desde que o conheci. Esse fim-de-semana conheci mais a fundo o Bazaar, e pretendo começar a testá-lo também para ter uma visão dos dois mundos e optar por um deles. Ambos são projetos relativamente novos que prometem muito. De uma forma ou de outra, os programadores solitários agora possuem um sistema de controle de fontes sem frescura e que funciona para todos.

	
  * Leia o tutorial passo-a-passo do Mercurial

	
  * Leia o tutorial passo-a-passo do Bazaar

	
  * Comece a usá-los em projetos simples e pequenos

	
  * Comece a comparar seu uso ao do Subversion; identifique prós e contras

	
  * Trace um roteiro de migração e mão à massa

