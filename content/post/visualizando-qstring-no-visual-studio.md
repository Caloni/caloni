---
categories: [ "code" ]
date: "2017-02-20"
tags: [ "draft",  ]
title: "Visualizando QString no Visual Studio"
---
O Qt não é um framework que pode apenas ser usado no QtCreator. Através de um projeto bem configurado pelo CMake, por exemplo, é possível ter um projeto que pode ser compilado e depurado tanto nas ferramentas do Qt quanto no Visual Studio. No entanto, na hora de depurar algumas coisas são difíceis de fazer. Por exemplo: como olhar o conteúdo de uma QString?

O Visual Studio utiliza um mecanismo que lembra os comandos bizarros que se usa no WinDbg, mexendo com registradores e tal. Através dessa combinação é possível dizer para o depurador como interpretar determinados tipos de objetos. Ele já vem obviamente pronto para std::string, CString (ATL) e deveria vir com QString, de tão famosa que é. Mas a versão do Visual Studio 2015 não vem. O jeito então é editar diretamente o arquivo onde ficam esses padrões.


O nome do arquivo é autoexp.dat e ele fica em uma pasta no estilo Program Files, Microsoft Visual Studio, Common7, Packages, Debugger. É melhor você retirar ele dessa pasta antes de sobrescrevê-lo para não ter erro de acesso. Ao abri-lo verá que no começo há vários comentários que explicam como é o funcionamento desse padrão.


Felizmente (e também obviamente) o pessoal do Qt já fez uma entrada na wiki que explica como fazer para interpretar corretamente uma QString. Eles mesmos admitem que a coisa ficou difícil desde a última versão (Qt 5), mas ainda assim é possível. E, se tudo falhar, ainda é possível usar a janela de Watch:


Mas não foi o caso dessa vez. Tudo funcionou perfeitamente assim que incluí os valores da Wiki logo no começo da sessão Visualizer.
