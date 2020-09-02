---
date: "2017-01-17"
tags: [ "code", "draft",  ]
title: "Warning de nível 4"
---
Você já colocou aquele seu projeto favorito em /W4? Por padrão, o Visual Studio cria seus projetos com o nível de warnings e 3, porque o nível 4 é muito, muito chato. No entanto, algumas vezes ele serve para que seu código não fique apenas correto, mas bem documentado e apresentável. Vamos tentar?


OK, este foi o nível 3 do tioserver, o projeto principal do tiodb, uma ferramenta para manter contêineres assináveis na memória e acessíveis via socket. Note que já existe um warning, mas vamos ignorar por enquanto. O objetivo aqui é descobrir quais os warnings mais comuns do projeto que você vai escolher. Vejamos o meu:


Vamos ordenar e capturar apenas o código desses warnings para ver quantos ocorrem e quais os mais comuns:


E a resposta é:


Apenas quatro. Tão comuns que a maioria está até em ordem numérica e diz respeito a repetição de nomes em escopos diferentes, o que esconde os nomes do escopo anterior, mais amplo. O outro, o C4701, pode ser mais problemático, já que ele representa uma variável que potencialmente não foi inicializada, fonte comum daqueles erros de "como é que essa variável virou isso?".

Felizmente só temos em um ponto do código:


A correção é simples: inicialize a droga das suas variáveis zero (ou determine qual o comportamento no caso else).

Vamos dar uma olhada em um dos outros warnings:


OK, isso é meio feio. A variável handle tinha acabado de ser criada logo antes da entrada do if. A não ser que sejam de fato variáveis distintas no código (apenas analisando a função inteira) elas poderiam ser reaproveitadas em apenas uma (até porque possuem o mesmo tipo). E se forem variáveis distintas... bem, coloque nomes distintos =)

E aqui termina mais uma sessão de "e se eu abrir mais os warnings do meu código". Espero que tenha aproveitado.
