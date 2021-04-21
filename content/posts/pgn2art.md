---
date: "2020-06-27"
link: "https://gist.github.com/Caloni/4d5f81365a01ef9567d5d4e077403d70"
tags: [ "code" ]
title: "Pgn2art"
---
Meu sonho de consumo para acompanhar partidas de xadrez é às cegas, apenas lendo ou ouvindo o próximo lance e imaginando em minha cabeça o tabuleiro. Porém, enquanto não tenho essa habilidade, um meio-termo aceitável é ver um tabuleiro em ascii art se modificando a cada lance. É possível acompanhar uma partida dessa forma como se estivesse lendo um livro, e por isso esse formato é prático, também, pois posso jogar esse ascii art no meu Kindle.

Usando a biblioteca python-chess fiz um pequeno script que recebe o endereço de PGNs (o formato com que se grava partidas de xadrez) por URL ou path local e cospe esses tabuleiros em ascii art. Com isso pode redirecionar para um arquivo texto e enviar para o Kindle ou ler de qualquer lugar, em formato estático, a tradução da partida.

O próximo passo, antes de ler às cegas, é transformar a leitura do tabuleiro bidimensional para a leitura do formato FEN, que é o formato usado para gravar posições de um tabuleiro.
