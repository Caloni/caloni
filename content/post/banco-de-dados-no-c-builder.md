---
date: "2007-12-21"
title: Banco de dados no C++ Builder
categories: [ "code" ]
---
[![CPPB Database](http://i.imgur.com/m4lKMDv.png)](/images/cppb-database.png)

Um banco de dados é qualquer lugar onde podemos ler e escrever informação geralmente persistente. Pode ser um arquivo INI, uma estrutura binária ou uma [plantação de servidores](http://www.google.com) para fazer busca na internet.

O uso de banco de dados em programação é mais que essencial, pois permite que armazenemos os resultados de um processamento e utilizemos esses mesmos resultados em futuras execuções.

Visando preencher algumas lacunas na internet sobre esse tema, iremos agora nos aventurar na configuração e uso de um banco de dados no C++ Builder.

<blockquote>_Obs. de camarada: banco de dados pode ser uma coisa bem chata. Contudo, a vida não é completa sem as partes chatas. O conhecimento dessa área é vital para a sobrevivência de muito desenvolvedores de software. Além do mais, pode se tornar bem mais interessante em algumas situações, como o estudo sobre normalização._</blockquote>

#### Todos os resultados da Mega Sena

Quase como um prêmio de consolação por participarmos de um sorteio que sabemos que não iremos ganhar nunca, a Caixa generosamente oferece a opção de baixarmos todos os resultados da [Mega Sena](http://www.caixa.gov.br/loterias/loterias/megasena/download.asp) desde seu início. Iremos utilizar esse **banco de dados** para criar uma interface de visualização de resultados no C++ Builder.

[![Mega Sena Download](http://i.imgur.com/UAwCSiC.png)](http://www.caixa.gov.br/loterias/loterias/megasena/download.asp)

Um problema inicial está no fato que o arquivo está no formato HTML, um formato mais difícil de usarmos no C++ Builder. Portanto, irei converter este formato em algo mais maleável, como um arquivo do Microsoft Access (manipulável pelo [Open Office](http://www.openoffice.org/)), o famoso **MDB**.

Para a conversão, nada mais que algumas [expressões regulares](http://guia-er.sourceforge.net/) e [macros de edição](http://notepad-plus.sourceforge.net/uk/site.htm) não resolvam em 5 minutos, sem contar a opção de importação do próprio Access. Para evitar perder estes 5 minutos, deixei disponível o banco de dados gerado através do [_download_](/images/megasena.7z) junto com o projeto que criaremos para demonstrar a visualização.

#### Borland Database Engine

Neste tutorial vamos usar aquilo que é o configurador oficial de banco de dados no C++ Builder: o **BDE**. Se você ainda não observou, após a instalação do C++ Builder um novo item surgiu no Painel de Controle, o **BDE Administrator**. Vamos usá-lo para configurar uma base de dados baseada no nosso arquivo MDB recém-gerado .

Criado o MDB, podemos clicar no BDE Administrator do Painel de Controle. A única coisa que precisamos fazer é criar uma nova base de dados, e especificar seus poucos parâmetros, como o tipo de base (MSACCESS) e o _path_ de onde está o arquivo MDB.

[![BDE Config](http://i.imgur.com/CGK70TT.png)](/images/bde-config.png)

Ah, sim, claro, também é importante colocar um nome apropriado para a base de dados: MegaSena.

A partir daí, clicando no botão _Apply_ ![BDE Apply](http://i.imgur.com/V7nz629.png), tudo deve fluir. Como em informática tudo quer dizer nada, eu deixo por conta do leitor a resolução de quaisquer problemas que acontecerem durante a configuração.

#### Agora o Borland Studio

Criado o banco e testado (experimente conectar pelo próprio BDE) podemos agora criar um novo projeto VCL e colocar alguns componentes interessantes feitos especialmente para banco de dados. São eles:

	
  * **TDatabase**: representa a própria base da dados, onde especificamos o nome da base de dados que vamos utilizar.

	
  * **TTable**: representa uma tabela de uma base de dados.

	
  * **TDataSource**: a origem dos dados que serão usados para popular seja lá o que quisermos popular.

Abaixo segue a configuração de cada um deles, ou seja, as propriedades que você deve mudar para que tudo funcione.

    
      object Database1: TDatabase
        AliasName = 'MegaSena'
        Connected = True
        DatabaseName = 'MegaSena'
        LoginPrompt = False
      end
      object Table1: TTable
        Active = True
        DatabaseName = 'MegaSena'
        TableName = 'Resultados'
      end
      object DataSource1: TDataSource
        DataSet = Table1
      end

Após todos esses componentes não-visuais terem sido inseridos no _form_, nada como colocar alguma coisa que o usuário veja: um **TDBGrid**.

    
      object DBGrid1: TDBGrid
        DataSource = DataSource1
      end

Com isso, nossa janela já exibe o conteúdo da tabela em tempo de _design_:

[![DB Grid](http://i.imgur.com/gQZWVxo.png)](/images/cppb-dbgrid.png)

E é isso! Se chegamos até aqui, já sabemos o arroz com feijão de usar banco de dados com o C++ Builder. Mais para a frente podemos nos aventurar em tópicos um pouco mais avançados, como fazer buscas, navegar item a item e essas coisas que as pessoas costumam fazer com um MDB.

#### Links úteis

	
  * [Borland Developer Studio](http://www.codegear.com/downloads): baixe a versão gratuita para desenvolver programas Win32 nativos em RAD

	
  * [OpenOffice](http://www.openoffice.org/): uma suíte de escritório gratuita (para ler e escrever MDBs)

	
  * [MegaSena](/images/megasena.7z): o nosso projeto de banco de dados em C++ Builder

