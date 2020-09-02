---
author: "Wanderley Caloni"
date: "2017-04-24"
tags: [ "blog", "draft", "books" ]
title: "Como publicar um livro na Amazon"
---
Estou finalizando essa semana a publicação do meu primeiro livro. Não, não é sobre programação, mas sobre Cinema. Mais de 1500 páginas sobre Cinema. Isso está acontecendo porque eu resolvi testar a possibilidade de publicar facilmente alguma coisa na Amazon baseado em um blog feito através de Jekyll (uma linguagem de marcação simples e um punhado de arquivos markdown). E, guess what? Funciona, é simples e relativamente descomplicado. Eis o caminho das pedras.

Antes de tudo, a coisa mais importante que você deve fazer é gerar conteúdo. Sem conteúdo não há livro. Eu, por exemplo, segui escrevendo sobre praticamente todo filme que eu assistia, pelo menos alguns parágrafos sobre. Ao final de quase sete anos, o resultado são páginas e páginas de texto. Esse é o seu patrimônio e uma ferramenta para praticar a escrita.

Se você usar o Git Hub Pages ou similar para publicar em seu blog poderá se aproveitar da estrutura do Jekyll, que é um builder de páginas estáticas. Basicamente cada post deve ser um arquivo markdown com um header no formato yaml. Há uns poucos templates que você pode escolher ou compilar, como o formato de cada página, e através desse template o Jekyll gera todas as páginas html. O GitHub compila automaticamente um repositório que está sendo utilizado nesse formato.

Depois que você gerar conteúdo suficiente, tudo que você precisa fazer é usar um template no Jekyll que formate o html da forma com que a ferramenta da Amazon, o KindleGen, espera. Ele recebe um html ou um opf (um formato próprio de indexação) como base e cospe um mobi, que pode ser usado para fazer upload do seu livro para publicação como ebook na Amazon. Se quiser também fazer uma versão física, eles imprimem para você. Sai mais caro, e tanto os royalties do virtual como o real são uma mixaria, mas é simples, economiza tempo e aumenta a visibilidade. Para a versão física baixe os modelos em doc deles e cole seu conteúdo. Isso já economiza formatação de margens, por exemplo.

Para a capa, você pode gerar a própria ou eles possuem um gerador de capas, também, que é razoável. Na hora de subir a capa do formato físico pode editar também o texto da contracapa e até colocar sua foto.
