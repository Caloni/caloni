---
categories: [ "code" ]
date: "2011-05-22"
tags: [ "draft",  ]
title: "Comparando strings no WinDbg"
---
O WinDbg fornece aos programadores diversos meios (muitos redundantes) de comparar valores inteiros em quaquer lugar da memória, em qualquer tamanho (8, 16, 32, 64 bits). Porém, quando precisamos comparar strings, que todos sabem ser uma sequência de bytes de tamanho arbitrário (se for em C, até o zero terminador).

Uma solução simples e rápida é comparar os 4 primeiros bytes de uma string, ou os 4 primeiros bytes que diferem de uma lista grande.

Por exemplo, imagine o seguinte código que abre todos os arquivos da pasta de sistema:


Queremos colocar um breakpoint no momento em que o arquivo shell32.dll estiver sendo aberto. Para isso, devemos nos atentar para os parâmetros passados para a função CreateFile.


Temos que nos atentar para o padrão de bits após esse path. Vamos dar uma olhada por dentro da string.





O nome do arquivo começa no offset 16+4 = 20, ou 14 em hexa. Dessa forma, podemos capturar o padrão de bits da seguinte maneira:



Para nos certificarmos que é realmente esse o padrão, e para já montarmos nosso próprio padrão para o shell32.dll, vamos alocar um pedaço de memória e verificar se a sequência de bits está correta.








Ótimo. Os padrões bateram, então podemos colocar um breakpoint condicional partindo do padrão de bits do nome do arquivo que precisamos.











