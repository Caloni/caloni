---
date: "2008-08-11"
title: Guia para iniciantes no DriverEntry
categories: [ "blog" ]
---
!driverentry-com-br.PNG](/images/driverentry-com-br.PNG)A mensagem anterior deixou bem claro que tenho um roteiro de leituras bem _hardcore_ a fazer nos próximos 20 anos. Pretendo, enquanto isso, programar alguma coisinha rodando em ring0, porque nem só de teoria vive o programador-escovador-de-bits. Pensando nisso, esse fim-de-semana comecei a me aventurar nos ótimos exemplos e explicações do [DriverEntry.com.br, nossa referência _kernel mode_ tupiniquim.

A exemplo do que Dmitry fez com os livros de _drivers_, acredito que a mesma coisa pode ser feita com os blogues. A maneira de esmiuçá-los vai depender, principalmente, da quantidade de material a ser estudado e das práticas necessárias para que o conhecimento entre na cabeça de uma vez por todas.

No momento, minha prática se resume a isso:

	
  * Debug or not debug. Aqui resolvi dar uma olhada de perto nas macros e funções usadas para _tracing_ no DDK, e descobri que, assim como a runtime do C, podemos ter mensagens formatadas no estilo do printf e vprintf, o que economiza uma porção de código repetitivo. Dessa forma pude usar minha estratégia de ter a macro LOG usada para mandar linhas de depuração na saída padrão. Ainda tenho que estudar, contudo, o uso da variável va_list em kernel.

	
  * ExAllocatePool (WithoutTag)](http://www.driverentry.com.br/blog/2006/08/exallocatepoolwithouttag_30.html). Precisei fazer alguns testes no Dependency Walker e anexar o fonte que faz a vez do [GetProcAddress para drivers.

	
  * Getting Started](http://www.driverentry.com.br/blog/2006/09/getting-started.html). Esse foi o artigo mais interessante de todos, pois foi a base de todo o código que ando repetindo em meus exercícios. Além desse, é vital o [uso do Visual Studio das funções do DDK são alienígenas para mim, assim como os seus 497 parâmetros cada.

	
  * Driver plus plus](http://www.driverentry.com.br/blog/2006/10/driver-plus-plus.html). Tive que perder algum tempo codificando uma segunda versão do Useless e baixando o [framework da Hollis para testar as peculiaridades do C++ em kernel mode. Não que eu vá usar alguma coisa avançada nesse estágio, mas preciso conhecer algumas limitações e alguns macetes que farão uma grande diferença no futuro, quando as linhas de código ultrapassarem 10.000.

	
  * Pulei alguns tópicos que pretendo explorar quando estiver mais à vontade com alguns conceitos básicos, como a explicação de como obter o processo dono de uma IRP](http://www.driverentry.com.br/blog/2007/02/de-quem-essa-irp-process-id.html), a explicação do que é uma IRP](http://www.driverentry.com.br/blog/2007/02/legal-mas-o-que-uma-irp.html) (apesar de eu ter baixado e brincado com o [monitor da OSR e a aparentemente simples explanação sobre [como funcionam as listas ligadas do DDK. Tudo isso virá com o tempo, e algumas coisas estarão sempre martelando na cabeça. É só dar tempo ao tempo e codificar.

	
  * Nós queremos exemplosaprender a depurar dos dois lados da moeda.

Próximos passos?

Pelo que eu vi, no geral, acredito que aos poucos irei voltar para os tópicos que pulei, além de olhar em outros artigos que chamaram minha atenção:

	
  * Como criar um driver de boot

	
  * Usando o DSF para interagir com dispositivos USB de mentirinha

	
  * A continuação emocionante de nosso driver que recebe reads e writes

	
  * Usar o que existe de bom e melhor para garantir a qualidade de um driver

	
  * Mais alguns detalhes que começam a fazer sentido em nosso KernelEcho

	
  * Criando e usando IOCTLs. Essa vai ser ótima!

	
  * A necessidade inevitável de](http://www.driverentry.com.br/blog/2008/06/utilizando-o-registry-parte-1.html) [mexer com o registro do sistema

Tudo isso aliado aos exemplos e à teoria latente do Windows 2000 Device Driver Book (minha primeira leitura) irá dar um upgrade forçado aos meus neurônios. Espero sobreviver para contar o final da história.

O resultado dos meus exercícios atuais, com alguns poucos comentários, pode ser baixado aqui.
