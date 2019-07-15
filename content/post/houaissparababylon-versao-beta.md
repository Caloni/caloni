---
date: "2008-11-15"
title: HouaissParaBabylon versão beta
categories: [ "blog" ]
---
[![Tela principal do conversor Houaiss para Babylon](http://i.imgur.com/vaSJkF8.thumbnail.png)](http://i.imgur.com/p6ES79y.png)Depois de muitos fins-de-semana divididos em horas picadinhas de programação de lazer, está disponível em vosso saite a primeira versão para usuários do **conversor do dicionário Houaiss para o aplicativo Babylon**.

Foi uma longa jornada, sim, mas espero que valha a pena para quem esperou. Também espero poder receber inúmeras respostas com dúvidas, sugestões e até mesmo mais problemas que vierem a acontecer.

Segue um pequeno roteiro do funcionamento do programa, que é bem simples, aliás. Para que tudo dê certo, no entanto, é necessário que o computador onde será feita a conversão possua os três programas abaixo instalados e funcionamento corretamente:

	
  * [Dicionário Houaiss](http://www.dicionariohouaiss.com.br/comocomprar.asp). Testado na versão 2, deve ser instalado com opção de cópia dos arquivos no disco rígido.

	
  * [Babylon](http://www.babylon.com). Testado nas versões 6 e 7. Pode ser registrado ou não.

	
  * [Babylon Builder](http://www.babylon.com.br/BabylonBuilder.asp). O construtor dos dicionários Babylon. Apesar de ser possível construir dicionários personalizados para o Babylon, é necessário que se use esse aplicativo conversor. O HouaissParaBabylon o usa, e por isso precisa que ele esteja instalado corretamente.

Tudo isso verificado, basta então clicar no botão de Iniciar Conversão, sentar e esperar. A primeira fase envolve três passos:

	
  * **Desencriptação do dicionário original**. Isso é feito baseando-se em nossa [análise de engenharia reversa](http://www.caloni.com.br/conversor-de-houaiss-para-babylon-parte-1).

	
  * **Montagem do projeto de dicionário Babylon**. Para isso existe um processo de [interpretação do formato Houaiss](http://www.caloni.com.br/conversor-de-houaiss-para-babylon-parte-2), agora desencriptado, e sucessivas traduções para um projeto que o Babylon Builder irá entender.

	
  * **Construção do dicionário Babylon**. Essa parte é feita pelo Babylon Builder. Por ser o maior dicionário de português da atualidade, esse processo pode demorar bastante, e com certeza irá se tornar o maior dicionário já instalado na sua lista de dicionários do Babylon.

![Processo de conversão do dicionário Houaiss para o dicionário Babylon](http://i.imgur.com/dlTlgCc.png)

Na segunda fase, após toda essa movimentação de HD, existe apenas uma coisa a fazer: **instalar o dicionário no Babylon**.

[![Instalando dicionário Houaiss Babylon](http://i.imgur.com/71tsvab.thumbnail.png)](http://i.imgur.com/Fsw5rUt.png) Quem faz isso é o próprio Babylon, se devidamente instalado. Se tudo deu certo, o HouaissParaBabylon sai de fininho e deixa o usuário com o progresso da instalação do dicionário Houaiss-Babylon.

#### Problemas?

Se não for encontrado o dicionário Houaiss devidamente instalado no disco rígido, será exibida uma mensagem de erro pedindo que a instalação seja feita dessa maneira. Se, contudo, não for possível localizar a instalação do dicionário, será pedido ao usuário que diga onde ela se encontra, ou aponte para a pasta "Houaiss" em seu CD de instalação,** uma dica suficiente para que a operação seja bem-sucedida**.

![Seleção da pasta ¿Houaiss¿ dentro do CD de instalação.](http://i.imgur.com/aY9kCi2.png)

Outros erros comuns, como o Babylon Builder não instalado, serão obviamente avisados ao usuário. Erros mais raros terão um tratamento mais genérico. No entanto, nem por isso ele está livre de solução. Ao sair de uma conversão mal-sucedida, o usuário tem a opção de **exportar o log de operações que foram realizadas durante a malfadada operação**. Dessa forma, ele próprio conseguirá diagnosticar o problema ou, em casos mais sérios, me enviar o resultado de suas tentativas.

![Exportação de logs do conversor Houaiss para Babylon.](http://i.imgur.com/mKLYThq.png)

E é isso. Para uma versão inicial, talvez esteja razoável. Quem confirmará serão os ansiosos usuário que, espero sinceramente, consigam seus objetivos há tempos aguardados.

#### Linques

	
  * [Download do aplicativo HouaissParaBabylon do saite oficial](/images/houaissparababylon.zip)
Extensão: ZIP
Tamanho:83 KB
MD5: C1C3D2AD7A7AB5A1F711AEAB28C5F499

