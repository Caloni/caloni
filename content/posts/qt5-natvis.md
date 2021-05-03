---
categories:
- code
- draft
date: '2017-03-15'
title: qt5.natvis
---

A estratégia que utilizei em meu último artigo sobre Qt para expandir o tipo QString no depurador não existe mais no VS2017 RC. O arquivo autoexp.dat foi extirpado e em seu lugar foi deixado os já ativos arquivos natvis, que podem ser usados de forma global ou por usuário.

Existe um arquivo pronto circulando pela net chamado qt5.natvis. Alguns funcionam, outros não. As strings estão funcionando no meu depois que eu adaptei este arquivo com as dicas do help do qt.

Se você é admin de sua máquina, basta copiar este arquivo em %programfiles(x86)%, Microsoft Visual Studio, 2017, Enterprise, Common7, Packages, Debugger, Visualizers. Se for um usuário mané, em %USERPROFILE%, Documents, Visual Studio 2017, Visualizers.