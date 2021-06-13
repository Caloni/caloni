---
categories:
- code
date: '2008-08-11'
tags:
title: Guia para iniciantes no DriverEntry
---

A mensagem anterior deixou bem claro que tenho um roteiro de leituras bem hardcore a fazer nos próximos 20 anos. Pretendo, enquanto isso, programar alguma coisinha rodando em ring0, porque nem só de teoria vive o programador-escovador-de-bits. Pensando nisso, esse fim-de-semana comecei a me aventurar nos ótimos exemplos e explicações do www.driverentry.com.br, nossa referência kernel mode tupiniquim.

A exemplo do que Dmitry fez com os livros de drivers, acredito que a mesma coisa pode ser feita com os blogues. A maneira de esmiuçá-los vai depender, principalmente, da quantidade de material a ser estudado e das práticas necessárias para que o conhecimento entre na cabeça de uma vez por todas.

No momento, minha prática se resume a isso:

 - Debug or not debug. Aqui resolvi dar uma olhada de perto nas macros e funções usadas para tracing no DDK, e descobri que, assim como a runtime do C, podemos ter mensagens formatadas no estilo do printf e vprintf, o que economiza uma porção de código repetitivo. Dessa forma pude usar minha estratégia de ter a macro LOG usada para mandar linhas de depuração na saída padrão. Ainda tenho que estudar, contudo, o uso da variável va_list em kernel.

 - ExAllocatePool (WithoutTag). Precisei fazer alguns testes no Dependency Walker e anexar o fonte que faz a vez do GetProcAddress para drivers em meu miniprojeto do Bazaar para aprendizado de programação em kernel.

 - Getting Started. Esse foi o artigo mais interessante de todos, pois foi a base de todo o código que ando repetindo em meus exercícios. Além desse, é vital o uso do Visual Studio no processo de desenvolvimento, pois muitas (quase todas) das funções do DDK são alienígenas para mim, assim como os seus 497 parâmetros cada.

 - Driver plus plus. Tive que perder algum tempo codificando uma segunda versão do Useless e baixando o framework da Hollis para testar as peculiaridades do C++ em kernel mode. Não que eu vá usar alguma coisa avançada nesse estágio, mas preciso conhecer algumas limitações e alguns macetes que farão uma grande diferença no futuro, quando as linhas de código ultrapassarem 10.000.

 - Pulei alguns tópicos que pretendo explorar quando estiver mais à vontade com alguns conceitos básicos, como a explicação de como obter o processo dono de uma IRP, a explicação do que é uma IRP (apesar de eu ter baixado e brincado com o monitor da OSR) e a aparentemente simples explanação sobre como funcionam as listas ligadas do DDK. Tudo isso virá com o tempo, e algumas coisas estarão sempre martelando na cabeça. É só dar tempo ao tempo e codificar.

 - Nós queremos exemplos. Esse foi o artigo que mais me deu trabalho, mas que mais valeu a pena. Codifiquei tudo do zero, olhando aos poucos no código do Fernando para pegar o jeito de usar funções com nomes enormes e auto-explicativas e parâmetros com os nomes a, b, c. Também dediquei um tempinho considerável com a aplicação de user mode, para (re)aprender a depurar dos dois lados da moeda.

Próximos passos?

Pelo que eu vi, no geral, acredito que aos poucos irei voltar para os tópicos que pulei, além de olhar em outros artigos que chamaram minha atenção:

 - Como criar um driver de boot
 - Usando o DSF para interagir com dispositivos USB de mentirinha
 - A continuação emocionante de nosso driver que recebe reads e writes
 - Usar o que existe de bom e melhor para garantir a qualidade de um driver
 - Mais alguns detalhes que começam a fazer sentido em nosso KernelEcho
 - Criando e usando IOCTLs. Essa vai ser ótima!
 - A necessidade inevitável de mexer com o registro do sistema

Tudo isso aliado aos exemplos e à teoria latente do Windows 2000 Device Driver Book (minha primeira leitura) irá dar um upgrade forçado aos meus neurônios. Espero sobreviver para contar o final da história.
