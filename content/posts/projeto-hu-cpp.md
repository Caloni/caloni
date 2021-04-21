---
date: "2020-03-15"
tags: [ "code" ]
title: "Projeto Hu Cpp"
---
Utilizo o Hugo como renderizador do meu saite já faz um tempo. Depois que juntei os posts do finado Cine Tênis Verde e do meu blogue técnico a soma dos textos ultrapassou a marca dos dois mil. Atualmente levo cerca de quinze segundos para renderizar todo o saite antes de publicá-lo.

Não é uma marca ruim, considerando que estamos com quase três mil textos, e embora o leiaute do saite seja muito simples, é justamente o que eu desejo para rápido carregamento e busca. Não tenho do que reclamar.

Porém, um programador C nunca fica satisfeito com uma solução Golang.

Sabe esses pensamentos que não saem da cabeça? Estava devaneando há uns dias sobre se não seria interessante renderizar meu saite usando uma solução em C ou C++ e ver qual seria o resultado. Claro que seria uma solução in house, cheia de bugs e completamente limitado. Mas quem liga? Meu único objetivo é a diversão, e não pretendo criar um produto genérico. Hugo já satisfaz até o mais exigente dos programadores (exceto o Elias), pois resolve vários problemas do interminável conflito entre conteúdo e design.

Por falar no dito cujo, me lembrei da nossa disputa no saite Os Programadores. Era uma resolução de exercício envolvendo leitura e parseamento de um arquivo json. Tive o insight de usar algo parecido com o que desenvolvi naquela vez.

O código que bolei lê um arquivo markdown e divide o header nos campos que eu utilizo e o texto em parágrafos. Esse é o começo mínimo para começar a converter os arquivos em html. Ele usa o mapeamento de arquivo em memória como no desafio do saite. Não precisaria, mas já que a diversão é fazer mais rápido que o Hugo, por que não?

Meu próximo passo é pegar esse parser e converter todos os arquivos para html, da maneira mais porca possível. Quer dizer, quase da maneira mais porca. Não estou usando Pascal.
