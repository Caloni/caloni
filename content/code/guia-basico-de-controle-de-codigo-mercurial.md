---
date: "2008-04-15"
title: Guia básico de controle de código (Mercurial)
categories: [ "code" ]
---
Houve um bom motivo para que, semana passada, eu estivesse caçando inúmeras versões de um projeto desenvolvido fora da empresa: **falta de controle de código**. Esse tipo de lapso pode consumir de horas a dias de tempo perdido, dependendo de em quantas cópias de máquinas virtuais ficou espalhado o código.

Já [escrevi a respeito](http://www.caloni.com.br/guia-basico-de-controle-de-codigo-source-safe) da importância de controlar e gerenciar o código-fonte para que a falta de um histórico exato das alterações não seja motivo de recorreções de problemas, binários no cliente sem contraparte para ajustes, além de uma série de dores de cabeça que costumam começar a ocorrer assim que nos damos conta que nosso software está uma bagunça que dói.

Na época, discursei brevemente sobre alguns exemplos de gerenciadores de fonte que utilizam **modelo centralizado**, e nos exemplos práticos usamos o famigerado **Source Safe**, velho amigo de quem já programa ou programou Windows por alguns anos. Além dele, temos os conhecidíssimos [CVS](http://www.nongnu.org/cvs/) e [Subversion](http://subversion.tigris.org/), ambos largamente utilizados no mundo todo.

No entanto, uma nova forma de controlar fontes está nascendo já há algum tempo, com relativo sucesso e crescentes esperanças: o [modelo distribuído](http://en.wikipedia.org/wiki/Distributed_revision_control). Nesse tipo de gerenciamento, a liberdade aumenta exponencialmente, permitindo coisas que no modelo antigo seriam muito difíceis de serem implementadas. Não vou me delongar explicando a teoria por trás da idéia, sabendo que, além de existir um ótimo texto explicando as vantagens em cima do modelo centralizado [disponível na web](http://ianclatworthy.files.wordpress.com/2007/10/dvcs-why-and-how3.pdf), o próprio sítio das implementações atuais explica a idéia de maneira muito convincente. E são elas:

	
  * [Git](http://git.or.cz/). Conhecido como o controlador de fontes do _kernel_ do Linux. Escrita a versão inicial por Linux Torvalds em C e módulos de Perl pendurados, hoje em dia tem como principal desvantagem a falta de suporte nos ambientes Windows, impactando negativamente em projetos portáveis. Sua principal vantagem, no entanto, é a rapidez: é o controle de fonte mais rápido do oeste.

	
  * [Mercurial](http://www.selenic.com/mercurial/wiki/) (ou _**hg**_). Sem dúvida o mais fácil de usar. Bem documentado e com comandos intuitivos para o usuário, vem ganhando mais adeptos a cada dia. Seu desempenho é comparável ao do Git, e seu sistema de arquivos é bem eficiente.

	
  * [Bazaar](http://bazaar-vcs.org/) (ou _**bzr**_). O irmão mais próximo do Mercurial, com comandos bem parecidos. Um costuma lembrar os comandos do outro, com pequenas diferenças. Seu desempenho não chega a ser comparável aos dois acima, mas sua robustez compensa, pois é o único, de acordo com testes e estudos, que suporta o controle total de operações de renomeação de arquivos e pastas. Recentemente seu projeto tem evoluído muito.

#### Distribuído x Centralizado

Nos sistemas centralizados o repositório de fontes fica em um lugar definido, de onde as pessoas pegam a última versão e sobem modificações, ou não, caso não tenham direito para isso.

Nos sistemas distribuídos, o histórico e ramificações ficam todos **locais**. Como assim locais? Bom, locais do jeito que eu estou falando quer dizer: **na própria pasta onde se está desenvolvendo**.

É lógico que pode existir uma versão de ramificações no servidor, que no caso do controle distribuído é mais um membro da rede _peer-to-peer_ de ramificações, já que cada colaborador possui seu próprio repositório local, capaz de trocar revisões entre colaboradores e subir revisões os servidores que interessarem.

Além disso, o conceito de ramificações (_branches_) e consolidação de versões (_merging_) é muito mais presente do que em sistemas como o Subversion, onde o _commit_ (ato de enviar as revisões de um código para o repositório central) ocorre de forma controlada. Da maneira distribuída, é comum criar um _branch_ para cada problema ou _feature_ sendo desenvolvida, e ir juntando tudo isso imediatamente após terminado, gerando um histórico bem mais detalhado e livre de gargalos com modificações temporárias.

Porém, a maior vantagem em termos de desenvolvimento acaba sendo a liberdade dos usuários, que podem trocar modificações de código entre si, sem existir a figura centralizadora do _branch_ oficial. Ela pode existir, mas não é mais uma condição _sine qua non_ para modificações no fonte.

#### Caso de uso: Mercurial

Comecei a usar em meus projetos pessoais o **Mercurial** por ter [ouvido falar](http://www.evilbitz.com/2007/11/04/an-approach-to-revision-control-your-documents/) dele primeiro. Achei a idéia fantástica, pois já estava à procura de um substituto para meu velho Source Safe, meio baleado das tantas inovações de controle de fonte que surgiram nos projetos de fonte aberto. Outro motivo para desistir do Source Safe foi o fato de ser uma solução comercial que custa dinheiro e não chega a ser absurdamente mais fácil de usar a ponto de valer a pena usá-lo.

O princípio de uso de uma ferramenta distribuída é muito simples: se você tiver um diretório de projeto já criado, basta, dentro dessa pasta, iniciar o repositório de fontes.

    
    > hg init

Após isso, será criada uma pasta com o nome .hg. Dentro dela é armazenado todo o histórico dos fontes. Podemos inicialmente adicionar os arquivos do projeto existente e fazer o primeiro _commit_, que irá começar a controlar os arquivos adicionados dentro dessa pasta e subpastas:

    
    > hg add
    adding Header.h
    adding Main.cpp
    adding Project.cpp
    adding Project.vcproj

    
    > hg commit -m "Primeira versao"

Se o programa não disse nada ao efetuar o _commit_, é porque está tudo certo. Agora podemos controlar as mudanças de nosso código usando o comando _status_. Para vermos o histórico usamos o comando _log_.

    
    > hg log
    changeset:   0:e9246bcf2107
    tag:         tip
    user:        Wanderley Caloni <wanderley@caloni.com.br>
    date:        Tue Apr 15 09:05:27 2008 -0300
    summary:     Primeira versao

    
    > echo bla bla bla >> Main.cpp
    
    > hg status
    M Main.cpp
    
    > hg commit -m "Alterado algumas coisas"
    
    > hg log
    changeset:   1:829b081df653
    tag:         tip
    user:        Wanderley Caloni <wanderley@caloni.com.br>
    date:        Tue Apr 15 09:06:29 2008 -0300
    summary:     Alterado algumas coisas
    
    changeset:   0:e9246bcf2107
    user:        Wanderley Caloni <wanderley@caloni.com.br>
    date:        Tue Apr 15 09:05:27 2008 -0300
    summary:     Primeira versao

Como vimos, ao alterar um arquivo controlado este é mostrado pelo comando _status_ como alterado (o M na frente do Main.cpp). Também existem controles para cópia e exclusão de arquivos.

Esse é o básico que se precisa saber para usar o Mercurial. Simples, não? O resto também é simples: fazer _branches_ e juntá-los é uma questão de costume, e está entre as boas práticas de uso. Eu recomendo fortemente a leitura do tutorial "**Entendendo o Mercurial**", disponível no sítio do projeto, até para entender o que existe por trás da idéia do controle descentralizado de fontes. Existe uma [tradução muito boa](http://www.selenic.com/mercurial/wiki/index.cgi/BrazilianPortugueseUnderstandingMercurial) feita pelo meu amigo [Márcio](http://marcioandreyoliveira.blogspot.com/).

Como usuário de Windows, posso dizer que a versão funciona muito bem, e é possível fazer coisas como, por exemplo, usar o [WinMerge](http://winmerge.org/) para juntar _branches_ ou comparar versões automaticamente, o que por si só já mata toda a necessidade que eu tinha do Source Safe.

#### Mercurial ou Bazaar?

Testei o Mercurial por cerca de três meses desde que o conheci. Esse fim-de-semana conheci mais a fundo o Bazaar, e pretendo começar a testá-lo também para ter uma visão dos dois mundos e optar por um deles. Ambos são projetos relativamente novos que prometem muito. De uma forma ou de outra, os programadores solitários agora possuem um sistema de controle de fontes sem frescura e que funciona para todos.

#### Para começar começando

	
  * [Leia o tutorial passo-a-passo do Mercurial](http://www.selenic.com/mercurial/wiki/index.cgi/BrazilianPortugueseTutorial)

	
  * [Leia o tutorial passo-a-passo do Bazaar](http://doc.bazaar-vcs.org/bzr.dev/en/mini-tutorial/index.html)

	
  * Comece a usá-los em projetos simples e pequenos

	
  * Comece a comparar seu uso ao do Subversion; identifique prós e contras

	
  * Trace um roteiro de migração e mão à massa

