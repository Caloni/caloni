---
categories: [ "code" ]
date: "2017-07-28"
tags: [ "draft",  ]
title: "Migrando Imagens Para Imgur"
---
Depois de migrar meus blogues para o Hugo decidi deixar o repositório mais magro migrando as imagens para um serviço de imagens. O imgur me pareceu uma solução simples com uma interface rápida (e uma API Python). Para realizar essa tarefa você vai precisar das ferramentas de sempre: grep, sed, python, vim. E lá vamos nós.

Meu primeiro passo foi realmente limpar a pasta de imagens, eliminando as que não estavam sendo usadas. A pasta de imagens ficou se acumulando por anos, e muitas imagens foram sendo carregadas através dos Wordpress da vida e plugins que deram resize nas imagens, gerando várias cópias no processo. Tudo inútil e dispendioso.


O principal problema de subir tudo para o imgur é que os nomes dos arquivos irão mudar e perder a referências usadas no texto. Para conseguir renomear os arquivos dentro dos artigos é necessário conectar no serviço do imgur e através dele obter o nome original do arquivo, disponível na propriedade name:


Executando este script será possível gerar um log no formato nome-original-do-arquivo => id-da-imagem-usado-pelo-imgur. O ID deles também é usado para link direto da imagem, de onde virá o comando sed que vai substituir nos artigos os nomes originais pelo link do imgur:


Lembrar de apagar o all.md. Ele só foi usado para gerar a saída mais simples do grep.

