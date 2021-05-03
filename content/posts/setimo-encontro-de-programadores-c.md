---
categories:
- blog
date: '2010-07-26'
tags:
- draft
title: Sétimo Encontro de Programadores C++
---

Mais um fim-de-semana no ócio e na vadiagem. Tenho que manter minhas [qualidades de bom programador](http://c2.com/cgi/wiki?LazinessImpatienceHubris) que sou: preguiçoso, impaciente e pretensioso.

Mas nem por isso deixei de terminar uma primeira versão do aplicativo que irei usar como base na minha palestra do nosso próximo [encontro C++](http://www.ccppbrasil.org/wiki/Grupo:Encontro_VII): [Crash Dump Analysis](/images/crashdumpanalysis.7z). Se alguém tiver dicas de quais os problemas mais difíceis do Universo para analisar em um dump de memória, comente a respeito e veremos o que dá pra fazer.

![crash-dump.png](http://i.imgur.com/wNd2Z1m.png)

Enquanto isso, continuo descobrindo maravilhas do WinDbg. Essa semana fiquei brincando de colocar breakpoint em user-mode, mas depurando o kernel, como fizeram [os rapazes do Ntdebugging](http://blogs.msdn.com/b/ntdebugging/archive/2010/07/20/debugging-services-startup-in-svchost-from-a-kernel-mode-debug-session.aspx). A conclusão é que ele vale para todos os aplicativos abertos. Tente com o MessageBox!

    
    !process 0 0 notepad.exe
    .reload /user
    bp user32!MessageBoxW

Mas devaneio. Talvez outra boa qualidade de um bom programador.