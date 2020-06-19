---
categories: [ "code" ]
date: "2019-07-10"
tags: [ "draft",  ]
title: "Como Publicar Seu Blog Em Hugo Para Ebook"
---
Eu publico meu blog inteiro de tempos em tempos para um ebook que construo formatando primeiro em html através de um tema do Hugo, o parser de blog que estou usando no momento porque ele suporta 2500 posts sem reclamar. É uma receita simples de sucesso se você precisar ter todo seu conteúdo indexado para rápida referência ou leitura cronológica.

A primeira coisa a ser feita é preparar um tema para formatar seu html. Eu já tenho um linkado no meu blogue e que precisa apenas formatar o index.html, pois todo o conteúdo e índices estarão lá. Segue um exemplo atual que uso. Ele possui índice alfabético, inclusão de um arquivo-diário que mantenho, listagem das categorias (com índices para cada uma delas) e listagem cronológica (e link para pular direto para o conteúdo).


Como eu uso Kindle eu construo a partir desse html um arquivo .mobi, mas creio ser simples de construir qualquer outro formato através desse html final. No caso do Kindle preciso de alguns arquivos para usar o kindlegen (a ferramenta da Amazon) que mantenho na pasta static do hugo, como o .ncx e o .opf (além da capa, cover.jpg). Uso uma batch muito pequena para fazer todos os passos e copiar o .mobi resultante para meu Kindle (conectado por um cabo USB e com um drive montado em K:).


Importante lembrar que a codificação do hugo (utf8) deve bater com a codificação esperada pelo gerador de ebook. Que me lembre não há muito mais segredos. Basta escrever e de vez em quando rodar o script novamente =)
