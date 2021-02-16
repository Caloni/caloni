---
css: "<style>section .title, .subtitle, .taglist { display: none; }</style>"
date: "2007-06-14"
tags: [ "blog" ]
title: "Wanderley Caloni"
---
Wanderley Caloni é um programador C/C++ especializado em backend para Windows que decidiu ter seu próprio blogue técnico a pedidos insistentes do seu amigo Rodrigo Strauss, que estava blogando já fazia alguns anos no www.1bit.com.br. Busco mantê-lo atualizado por esses longos anos de programação, depuração e transpiração com minhas peripécias do dia-a-dia. Eventualmente me tornei crítico de cinema e juntei aqui essas duas escovas de dentes, textos técnicos e cinematográficos, o que acabou tornando o saite gigante a ponto de eu precisar trocar meu static site generator para algo mais rápido como Hugo.

## Overview geral por cima

Colaborador frequente do Grupo C/C++ Brasil, eu e o Strauss nos consideramos fundadores do grupo por organizar e participar do Primeiro Encontro de Programadores e Aficionados da Linguagem C/C++ do Brasil, que ocorreu em São Paulo exatamente no dia dezessete de dezembro de dois mil e cinco, às três horas da tarde, no restaurante Outback do Shopping Eldorado. Desde então o grupo vem realizando encontros mais técnicos no decorrer dos anos, com palestras e debates. A cerveja tradicional se manteve ao final do evento.

Trabalhei por dez anos na área de Segurança da Informação, principalmente em dois sistemas. O primeiro deles, que tenho mais carinho, foi o Sistema de Controle de Acesso a Usuários e Aplicações (aka SCUA), desenvolvido totalmente no Brasil desde a época do MS-DOS. O segundo, mais contemporâneo, desenvolvido pela Open CS, protege os usuários contra ameaças bancárias virtuais, onde meu papel foi fazer análise de trojans e ataques de phishing utilizando engenharia reversa.

Depois desses dez anos migrei para a área financeira e fui trabalhar na EzMarket, uma pequena empresa iniciada pelo meu amigo Anderson Silva (mais tarde ela foi comprada pela UOL). Desenvolvi um sistema de risco que roda em uma das maiores corretoras do país (a Easynvest) e me tornei sócio desenvolvedor de uma empresa especializada nessas soluções, a Intelitrader. Em meio a isso me tornei sócio de outra empresa, a BitForge, pela qual nutro um carinho especial porque ela auxilia empresas e equipes de desenvolvimento em problemas complexos, seja em arquitetura, metodologias ou a pura escovação de bits. A metodologia da BitForge é simplesmente fazer o serviço e resolver o problema, seja ele qual for, da maneira mais indolor possível para o cliente.

No mundo acadêmico mantenho teias de aranha por muitos anos. Participei de minha primeira faculdade aos dezoito anos, no século passado, na Faculdade de Filosofia, Letras e Ciências Humanas da USP (aka FFLCH). Cursei um ano e meio antes de me descobrir perdidamente apaixonado por computação. Eventualmente me formei em Arquitetura de Redes pelo Instituto Brasileiro de Tecnologia Avançada. Finalizando a seção sobre diplomas e troféus em geral, de 2013 a 2018 fui nomeado MVP (aka Most Valued Professional) pela Microsoft, um prêmio em consideração pelas colaborações à comunidade C/C++.

Entre xadrez e andar de bicicleta, o hobby que levei mais a sério foi mesmo ser cinéfilo inveterado, e com isso escritor em formação. Tendo mantido por quase dez anos um blogue especializado no assunto, o Cine Tênis Verde, desde o finalzinho de 2014 sou colaborador de um site especializado, o CinemAqui, participando de cabines de imprensa e escrevendo críticas sobre cinema, geralmente sobre estreias de filmes fora do circuito hollywoodiano. A pandemia veio a pausar um pouco essa dinâmica, mas me considero extremamente grato pela oportunidade dada pelo Vinicius Carlos Vieira, editor do site.

## No detalhe

Caso esteja ainda curioso e tenha chegado até aqui, abaixo temos uma breve e não-exaustiva lista das coisas que eu andei fazendo na minha não tão breve vida de escovação de bits. E espero que essa lista continue crescendo.

Desenvolvi uma solução de cópia de arquivos entre máquinas famigeradamente conhecida como "CopyFile que não copia" usando tecnologia COM e expansão de macros. Foi meu primeiro sistema a ser lançado em produção e me orgulho bastante dele ter sido concebido ainda por um programador de nível Júnior que mal sabia compilar uma DLL.

Mantive um sistema de inventário de hardware que utiliza as tecnologias WMI e SMBIOS, além dele ser também um inventário de software, pois coleta dados pelo registro da máquina.

Criei uma proteção da área de transferência, o Ctrl+C Ctrl+V, além do PrintScreen, através de um hook de janelas e manipulação de mensagens globais do sistema. É muito bacana para proteção de cópias fáceis dos dados de uma empresa, ainda que sempre exista a cópia difícil, pelo cérebro do funcionário, impossível (até o momento) de ser protegida.

Escrevi alertas no log de eventos do sistema usando device drivers. Sim, isso parece trivial, mas nada que você desenvolva usando Microsoft em C ou C++ acaba sendo trivial no final das contas.

Me comuniquei entre o user mode e kernel mode através de chamadas à função Windows DeviceIoControl, o que engloba praticamente toda solução desses dez anos em segurança da informação e envolve níveis diferentes de conhecimento, dependendo do protocolo definido entre esses dois mundos.

Acessei remotamente desktops usando ferramenta similar ao VNC com código-fonte modificado, onde a maior dificuldade é compilar de primeira.

Fiz do zero uma ferramenta de execução remota similar ao PsExec. Em alguns casos até melhor, pois vem com o código-fonte.

Controlei a impressão de documentos através de regular expressions usando uma biblioteca da Boost junto de um hook do shell do sistema.

Gerenciei as diretivas de acesso do sistema durante o logon e o logoff dos usuários. Para isso, mais uma vez, apelei para o registro e os hooks que a vida nos dá.

Migrei entre as bases de dados CTree e SQL usando classes OLEDB. Migrei novamente utilizando camadas de abstração DCOM. Migrei mais uma vez desenvolvendo ferramentas de conversão. Havia algum problema de gerência nesse projeto que nunca conseguiu abandonar a tecnologia antiga.

Autentiquei no Windows usando serviço DCOM e GINA customizada, ou até mesmo a Credential Provider, desenvolvida no Windows Vista para substituir as técnicas anteriores.

Sincronizei remotamente duas bases de dados CTree usando serviço DCOM (olha o projeto de bases de dados CTree aí de novo).

Compilei um CD Linux bootável com scripts bash e ferramentas de criptografia de discos. Tudo em linguagem C.

Também mexi no driver de criptografia de discos rígidos e armazenamento USB, como o uso de pen drives.

Já realizei dezenas de análises de telas azuis ou dumps de memória usando WinDbg, seja em kernel mode ou user mode.

Certa vez fiz um serviço COM de execução de aplicativos na conta de sistema que foi muito útil para vários pontos de um sistema gigante.

Customizei a MBR, ou Master Boot Record, os primeiros bytes que ligam um PC, adaptando de acordo com as características da BIOS, o código que está na placa que liga um PC.

Mantive uma biblioteca de criptografia Blowfish e SHA-1 em C++ e Assembly 16 bits, o que me rendeu uma semana de análise de um bug em modo real e [um ótimo artigo aqui no blog]. Com isso aprendi a usar um carregador de boot em Assembly 16 bits e depuração usando o simplório debug.com.

Outro sistema que deu certo trabalho foi o driver de auditoria de acesso, que usa memória compartilhada e eventos entre user mode e kernel mode. Mais sessões intermináveis de depuração no WinDbg.

Trabalhei com um sistema que fazia hook de API (mais um hook) em kernel mode para ambas as plataformas Windows, NT e 9X.

Protegi os executáveis através de autenticação em domínio configurado no resource dos arquivos, uma solução muito boa para centralizar instalações em um ambiente.

Mantive DLLs de proteção à navegação em Internet Explorer 6 e 7, e Firefox 1 e 2. Tudo usando injeção de código Assembly 32 bits.

Desenvolvi uma biblioteca de proteção de código, strings na memória e execução monitorada. Isso envolvia desde o alto nível da ferramenta até o uso de interrupções Win32.

Também desenvolvi uma biblioteca de geração de log centralizado, o que parece fácil, mas não quando você precisa controlar todos os processos do sistema através de memória mapeada e eventos globais.

Já mexi com os BHOs, ou Browser Helper Objects, e ActiveX, para Internet Explorer 6 e 7. Para o Mozilla e Firefox usei um plugin XPI.

Já fiz muito gerenciamento de projetos usando Source Safe, Subversion, Mercurial, Bazaar e scripts batch. Atualmente meu maior conhecimento em controle de fonte é usando git na linha de comando.

Já fiz debug de kernel em plataformas NT usando SoftIce e WinDbg. Isso em NT, mas como em 9X não existem essas coisas a solução foi uma mistura entre SoftIce e um depurador obscuro, que quase ninguém deve saber que existe, chamado WDeb98. Rodei esse cara dentro de uma máquina virtual emulada em conjunto com a interpretação das instruções em Assembly.

Como citado na introdução, fiz engenharia reversa de trojans feitos em C++, Visual Basic e Delphi usando WinDbg e IDA, e posso dizer com propriedade que os mais difíceis de entender são os feitos em VB.

Fiz certa vez uma ferramenta de diagnóstico muito simpática que lista arquivos, serviços, drivers, registro, partições, processos, tudo de uma máquina Windows.

Monitorei a execução de jobs em Windows 2000 ou superior para controle de instalação e atualização de produtos.

E por falar em monitoração, também registrei a frequência de uso de aplicações usando hook de janelas, de maneira invasiva e não-invasiva. O que não travasse estava bom.

Como pet project fiz a reversa do dicionário Houaiss e importei para o formato de outro dicionário eletrônico, o Babylon.

Controlei o sistema de build quando não havia muitas soluções open source por aí com Cruise Control .NET, e mantive um servidor de símbolos, talvez um dos únicos na época fora da Microsoft, usando Debugging Tools for Windows.

Documentei projetos através de Doxygen e uma solução wiki chamada Trac. Mantive os sistemas de documentação no ar e ativos enquanto estava no projeto, embora depois essas coisas se perdem e ninguém mais sabe como fazer as coisas.

Outro projeto que lembro com carinho, quando atingi a marca de dez mil linhas de código, foram as interfaces de gerenciamento para desktop que desenvolvi usando C++ Builder 5 e 6 e bibliotecas Visual C++. O principal deles, conhecido como Manager, roda até hoje, em um mundo onde tudo está no browser. Já mexi com interfaces de análise também, feitas em Visual C++ com os frameworks MFC, ATL e WTL.

Fiz análise de e-mails usando expressões regulares, dessa vez com a biblioteca da ATL, que é muito curiosa e enxuta, além de bugada. Nessa época também me especializei em análise de logs e edição global de projetos utilizando regular expressions. É impressionante o quanto você consegue economizar de tempo analisando logs e projetos gigantes se conhecer regular expressions.

Como citado na introdução, desenvolvi um sistema de risco para o mercado financeiro, corretoras da bolsa de valores. Hoje roda em uma das maiores corretoras do país, e contém o conjunto mais rebuscado de regras que alguém da área de risco poderia querer, desenvolvido com a ajuda de um especialista na área. Este é outro projeto que me dá orgulho, principalmente pelo sistema que detecta travas de opções.

Escrevi muitos artigos em português no meu blogue técnico, e mais alguns em inglês, aqui e [pelo Code Project], que por muitos anos era a comunidade mais ativa de projetos Microsoft.

Desenvolvi uma API de comunicação com dispositivos HID USB, o que permite navegar pela árvore de dispositivos hoje em dia que estão conectados pelo protocolo. Isso envolve pen drives, celulares, câmeras, qualquer coisa que tenha uma entrada ou saída USB.

Já programei para interfaces mobile do finado Windows Phone e para o Android. Para um usei Visual Studio e para o outro Android Studio. É impressionante como ainda são pesadas essas interfaces de desenvolvimento para mobile.

Venho mantendo as soluções de baixo nível da Intelitrader, principalmente as que envolvem market data, pois o fluxo de dados nesses sistemas é absurdamente alto em tempos de crise. Ou seja, atualmente, todo o tempo.

> "Não basta saber: temos que aplicar. Não basta querer: temos que fazer." Goethe

[um ótimo artigo aqui no blog]: /o-bug-mais-bizarro-que-ja-resolvi
[pelo Code Project]: https://www.codeproject.com/Articles/caloni
