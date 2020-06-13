---
categories: [ "code" ]
date: "2007-12-21"
tags: [ "draft",  ]
title: "Banco de dados no C++ Builder"
---

Um banco de dados é qualquer lugar onde podemos ler e escrever informação geralmente persistente. Pode ser um arquivo INI, uma estrutura binária ou uma plantação de servidores para fazer busca na internet.

O uso de banco de dados em programação é mais que essencial, pois permite que armazenemos os resultados de um processamento e utilizemos esses mesmos resultados em futuras execuções.

Visando preencher algumas lacunas na internet sobre esse tema, iremos agora nos aventurar na configuração e uso de um banco de dados no C++ Builder.

Obs. de camarada: banco de dados pode ser uma coisa bem chata. Contudo, a vida não é completa sem as partes chatas. O conhecimento dessa área é vital para a sobrevivência de muito desenvolvedores de software. Além do mais, pode se tornar bem mais interessante em algumas situações, como o estudo sobre normalização.

Quase como um prêmio de consolação por participarmos de um sorteio que sabemos que não iremos ganhar nunca, a Caixa generosamente oferece a opção de baixarmos todos os resultados da Mega Sena desde seu início. Iremos utilizar esse banco de dados para criar uma interface de visualização de resultados no C++ Builder.

Um problema inicial está no fato que o arquivo está no formato HTML, um formato mais difícil de usarmos no C++ Builder. Portanto, irei converter este formato em algo mais maleável, como um arquivo do Microsoft Access (manipulável pelo Open Office), o famoso MDB.

Para a conversão, nada mais que algumas expressões regulares e macros de edição não resolvam em 5 minutos, sem contar a opção de importação do próprio Access.

Neste tutorial vamos usar aquilo que é o configurador oficial de banco de dados no C++ Builder: o BDE. Se você ainda não observou, após a instalação do C++ Builder um novo item surgiu no Painel de Controle, o BDE Administrator. Vamos usá-lo para configurar uma base de dados baseada no nosso arquivo MDB recém-gerado .

Criado o MDB, podemos clicar no BDE Administrator do Painel de Controle. A única coisa que precisamos fazer é criar uma nova base de dados, e especificar seus poucos parâmetros, como o tipo de base (MSACCESS) e o path de onde está o arquivo MDB.

Ah, sim, claro, também é importante colocar um nome apropriado para a base de dados: MegaSena.

A partir daí, clicando no botão Apply !BDE Apply, tudo deve fluir. Como em informática tudo quer dizer nada, eu deixo por conta do leitor a resolução de quaisquer problemas que acontecerem durante a configuração.

Criado o banco e testado (experimente conectar pelo próprio BDE) podemos agora criar um novo projeto VCL e colocar alguns componentes interessantes feitos especialmente para banco de dados. São eles:

	
  * TDatabase: representa a própria base da dados, onde especificamos o nome da base de dados que vamos utilizar.

	
  * TTable: representa uma tabela de uma base de dados.

	
  * TDataSource: a origem dos dados que serão usados para popular seja lá o que quisermos popular.

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

Após todos esses componentes não-visuais terem sido inseridos no form, nada como colocar alguma coisa que o usuário veja: um TDBGrid.

    
      object DBGrid1: TDBGrid
        DataSource = DataSource1
      end

Com isso, nossa janela já exibe o conteúdo da tabela em tempo de design:

E é isso! Se chegamos até aqui, já sabemos o arroz com feijão de usar banco de dados com o C++ Builder. Mais para a frente podemos nos aventurar em tópicos um pouco mais avançados, como fazer buscas, navegar item a item e essas coisas que as pessoas costumam fazer com um MDB.

  * Borland Developer Studio: baixe a versão gratuita para desenvolver programas Win32 nativos em RAD
  * OpenOffice: uma suíte de escritório gratuita (para ler e escrever MDBs)

