---
date: "2017-03-15"
title: "qt5.natvis"
categories: [ "blog" ]

---
A estratégia que utilizei em meu último artigo sobre Qt para expandir o tipo QString no depurador não existe mais no VS2017 RC. O arquivo autoexp.dat foi extirpado e em seu lugar foi deixado os já ativos arquivos natvis, que podem ser usados de forma global ou por usuário.

Existe um arquivo pronto circulando pela net chamado __qt5.natvis__. Alguns funcionam, outros não. As strings estão funcionando no meu depois que eu adaptei [este arquivo](https://raw.githubusercontent.com/a1ext/labeless/master/test/qt5.natvis) com as dicas do [help do qt](https://wiki.qt.io/IDE_Debug_Helpers).

Se você é admin de sua máquina, basta copiar [este arquivo](/download/qt5.natvis) em __%programfiles(x86)%, Microsoft Visual Studio, 2017, Enterprise, Common7, Packages, Debugger, Visualizers. Se for um usuário mané, em __%USERPROFILE%, Documents, Visual Studio 2017, Visualizers__.
