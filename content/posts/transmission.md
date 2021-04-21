---
date: "2020-06-01"
tags: [ "code" ]
title: "Transmission"
---
Dia de fazer funcionar o download automágico de legendas depois que o Transmission baixou meu Netflix caseiro. O download funcionou, mas não foi dos melhores, pois o sincronismo e o encoding veio errado, e o rename de _pb para o nome do arquivo não está acontecendo rodando pelo transmission-daemon. Fora isso tá com tudo em cima.

No final do dia a correção era mais simples que imaginava: eu só precisava desabilitar duas flags: o uso de sufixo no nome do arquivo salvo e a flag que força todo arquivo a ser salvo como utf8 (os arquivos em português do Brasil são salvos no encoding do Windows, o ISO-8859-1 ou Windows 1252 para os mais íntimos).

No final do dia todos os bugs conterão uma correção trivial escondida do outro lado do muro chinês.
