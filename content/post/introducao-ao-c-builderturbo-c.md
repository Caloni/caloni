---
categories: [ "code" ]
date: "2007-09-26"
tags: [ "draft",  ]
title: "Introdução ao C++ Builder...Turbo C++"
---
Após mais de um ano de tentativas, finalmente consegui instalar e iniciar com sucesso o Borland Developer Studio. Esse foi o nome pomposo dado pela Borland para a "continuação" do velho C++ Builder e seus parentes, o Delphi e o C# Builder.

Existem muitas coisas novas ainda para ver, mas não é a usabilidade. Assim como a IDE antiga, é fácil de sair mexendo e fazendo janelas, no bom estilo WYSIWYG dos produtos da Borland.

Para quem começa a desenvolver aplicativos com interface para Windows, deve saber que uma das coisas mais produtivas que já inventaram foi o Visual Basic. De fato, o VB permite que virtualmente qualquer pessoa com conhecimentos mínimos de informática torne-se um gabaritado programador de telinhas.

Porém, com o tempo você percebe que cada ferramenta tem suas vantagens e desvantagens. Uma desvantagem do VB era a falta de flexibilidade. Outra era que a linguagem usada não favorecia muito aqueles que se aventuravam chamando a Win32 API diretamente dos seus programas. Era possível, sim, mas enfadonho e nem sempre as coisas funcionavam como o esperado.

Para as pessoas que chegam nesse nível de necessidade, existem basicamente duas escolhas:

	
  1. Permanecer no mundo Microsoft e usar MFC + Win32 API, passando a programar na linguagem em que foi feito o Windows (C/C++).

	
  2. Tentar usar o Delphi, a evolução do Turbo Pascal para Windows, da Borland, que pode ser considerado mais flexível que o VB, mas ainda assim usa uma linguagem alienígena (no sentido de que ainda não é a linguagem nativa do SO).

	
  3. Mudar de sistema operacional e esquecer esse negócio de _loop_ de mensagens (eu disse duas escolhas, certo?)

Bom, eis que surge o C++ Builder: uma ferramenta idêntica ao Delphi, contudo que oferece a linguagem C++ para que todas aquelas pessoas recém-saídas da faculdade e ansiosas por entrar no mercado de trabalho esqueçam aquele papo de Pascal e passem a usar a linguagem da indústria. Pelo jeito, era mais ou menos essa a visão da Borland quando lançaram o produto.

Desde o princípio, o C++ Builder foi lançado em revistas de informática em versões para estudantes, o que estimulava as pessoas financeiramente menos capacitadas (estudantes, como eu) a cada vez mais utilizar essa ferramenta de programação para desenvolver aplicativos Windows, já que, além de não ser pago como o Visual Basic e o Visual C++, não era nem tão limitado quando o primeiro nem tão complicado quanto o segundo. E estava sempre entre os programas completos para serem testados na revista que acabou de chegar na banca. Nossa, como era divertido programar por prazer!

O mais impressionante no Builder era que desde o começo, na versão 1, já tínhamos aquela palheta maravilhosa cheio de todos os controles que já faziam parte do Windows 95. Tudo isso por causa de uma estratégia simples e eficaz: os componentes são os mesmos do Delphi. O que o C++ Builder adicionou foi uma camada de interface para que C++ e Object Pascal conversassem. O resultado disso é espantoso: é possível programar em C++ puro, chamar APIs diretamente, e ainda usar os componentes em Delphi, além de também poder desenvolver em Delphi e mesclar ambas as linguagens em um projeto. É possível até usar herança entre componentes escritos em Delphi e C++ Builder.

> Quando entrei na Scua comecei a trabalhar profissionalmente com o C++ Builder, ao desenvolver o aplicativo de administração do software de controle de acesso. Na época não tínhamos muito tempo para perder desenvolvendo tudo em Win32 API ou usar algo mais rústico como a MFC, que é mais parecido com a finada biblioteca OWL do que com a VCL (a biblioteca visual de componentes usada pela Borland para Delphi e Builder). E não, usar Visual Basic não era uma alternativa. Como a produtividade estava em jogo, hoje tenho certeza que fizemos uma boa escolha.

Eu gostava do C++ Builder antigo: sem frescura de registrar componentes e sem necessidade de instalação. Até hoje uso a versão 1.0 para brincar de vez em quando, pois é relativamente pequena; apenas copio para uma pasta e ainda funciona muito bem.

Mas desde que o mundo gerenciado veio à tona, para instalar esse singelo produto da Borland você vai precisar de alguns pré-requisitos da Microsoft:

	
  1. Microsoft .NET Framework SDK 1.1

	
  2. Visual J# .NET Redistributable Package 1.1

	
  3. Microsoft XML 4.0 SP2 Parser and SDK

Se for necessária mais alguma instalação, não se preocupe: o Borland Turbo C++ Instalation Wizard irá te avisar no momento da instalação, que deverá ser a última a ser realizada.

Após tudo isso instalado, finalmente conseguiremos rodar nossa ferramenta RAD. Aliás, antes que eu me esqueça, RAD é uma abreviação para Rapid Application Development.

Se você nunca usou essa ferramenta, ao abrir o ambiente, irá se deparar com vários elementos que precisam ser nomeados e explicados para fazer algum sentido. Mesmo que muitas coisas sejam novas, algumas devem estar sempre gravadas em sua memória:

Sempre que você clicar em algum componente gráfico para ser editado - como uma janela, um botão, uma lista - o Object Inspector será o lugar para editá-lo. Ele está dividido em propriedades e eventos. Propriedades são as características gráficas e comportamentais do componente que está sendo editado. Eventos especificam métodos para tratar as ações recebidas de algum componente (ex: clique de um botão).

A palheta é onde estão todos os componentes que podem ser usados no momento para a edição do programa. Existe uma infinidade deles, tais como: botões, menus, caixas de seleção, listas de itens, barras de rolagem, listas de ações, imagens, rótulos, grupos de botões, e assim vai a valsa. Para usá-los, basta arrastar para uma janela e editar suas propriedades.

Onde estão todos os meus arquivos? O Gerenciador de Projetos está aí para ajudá-lo. Todas as units (unidades de código) e forms (janelas) que você criar no projeto estará visível para fácil acesso. É muito importante saber organizar um projeto, pois conforme se avança, ele tende a se tornar maior e mais complexo. Junto do Gerenciador de Projetos existe o seu ajudante, o Structure. Na visão de design,  o Structure irá mostrar os controles inseridos nas janelas; na visão de unit, o Structure irá mostrar os includes, macros, classes e funções do código-fonte exibido no momento.

Considerando que o Bloco de Notas é minha vítima preferida para testes (e a vítima preferida de outros, também), nada melhor que nosso projeto seja um Bloco de Notas simplificado, que leia, exiba e salve arquivo-texto. Para esse projeto iremos utilizar apenas 5 componentes e cerca de 10 linhas de código:

	
  * 2 botões (abrir e salvar arquivo),

	
  * 1 _memo_ (para exibir o arquivo aberto),

	
  * 2 caixas de diálogo comum (abrir e salvar arquivo).

