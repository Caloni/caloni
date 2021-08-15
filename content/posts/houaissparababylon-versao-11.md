---
categories:
- blog
date: '2008-12-30'
tags:
title: HouaissParaBabylon versão 1.1
---

Saindo mais um do forno.

Essa nova versão do conversor do dicionário Houaiss para Babylon corrige o problema de não encontrar o Houaiss 1.0. O problema ocorria porque o conversor se baseava na localização do desinstalador para encontrar o dicionário. Na primeira versão do dicionário o desinstalador fica na pasta c:\Windows, onde obviamente não estava o dicionário.

Nessa nova versão, além de procurar o caminho do dicionário no registro (desinstalador) e antes de pedir para o usuário o caminho correto é tentado o caminho padrão de instalação, %programfiles%\Houaiss. Se mesmo assim o dicionário não existir continuamos perguntando para o usuário, que tem a opção de dizer onde está instalado o dicionário no disco rígido ou apontar diretamente para o CD de instalação.
