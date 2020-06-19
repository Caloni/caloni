---
categories: [ "code" ]
date: "2014-04-15"
tags: [ "draft", "puzzle" ]
title: "Geleia de Código"
---

Não costumo participar de campeonatos de programação por alguns motivos vagos: é perda de tempo (não ganho nada com isso), sou um péssimo programador (ou pasteleiro), dá preguiça (esse é o mais válido) e por aí vai o mimimi. Dessa forma, sempre passei ileso de eventos como o atual Google Code Jam, que pretende levar a categoria de código ofuscado para um novo patamar.

No entanto, esse ano apareceram dois motivos que me levaram a gastar cinco minutos de paciência com as historinhas bestas da equipe do Google. Primeiro o Python, que desde 2013 tem renovado em mim a sensação que programar ainda é divertido (e que o pessoal da Microsoft e do padrão C++ tinham tirado de mim há muito tempo com seus compiladores cada vez mais complexos/lentos e as IDEs que demoram o tempo do cafezinho para abrir). Segundo o que move o mundo: a concorrência. Minha digníssima esposa, levada por alguns pontos-extra na faculdade (uma iniciativa até que louvável do professor), resolveu participar da primeira fase (a classificação desta fase também dava pontos).

O fato é que depois desses cinco minutos eu simplesmente não consegui parar até o minuto final das 23 horas (horário de Brasília) de domingo, quando o tempo-limite esgotou. O aspecto mais divertido do Code Jam é que há liberdade total para a ferramenta que você pretende usar: linguagens de programação, Excel, uma calculadora ou apenas seu cérebro. Você recebe uma "missão" e um arquivo de entrada e precisa cuspir um arquivo de saída de acordo com a missão. Apenas isso. O resto fica por conta da criatividade dos codadores e gambiarreiros de plantão.

Todos os exercícios levam em consideração um arquivo de entrada que possui em sua primeira linha o número de testes que serão feitos e em seguida um número determinado de linhas e parâmetros, geralmente divididos por espaço. O primeiro problema, por exemplo, apenas considerava a suposição de cartas em pequeno truque de mágica e recebia como entrada a disposição dessas cartas junto com a escolha da fileira que o participante dizia onde estava a carta escolhida.



O segundo exercício já envolvia um jogo bem divertido em que o jogador ficava clicando em cookies como se não houvese amanhã. Esse deu um pouco mais de trabalho, mas foi mais divertido que o primeiro.


Já o terceiro... o terceiro passa. Vamos para o quarto, um dos mais instigantes, pois envolve duas regras distintas de um jogo e a otimização das melhores estratégias para ambos. Isso consumiu bem mais tempo que os outros dois iniciais, pois lembro de ter me isolado por uma hora para conseguir colocar tudo na cabeça.


Já o terceiro foi um fracasso total. Tentei de todas as maneiras resolver o impasse de descobrir qual disposição de um jogo de campo minado poderia ser resolvido em apenas um clique (parece o jogo oposto do viciado clicador de cookies), mas falhei miseravelmente. E desconfio o porquê. Primeiro entendo que meu perfeccionismo me impediu de realizar uma checagem padrão para exceções já conhecidas (quando há apenas uma linha ou coluna, quando há apenas um espaço sem minas, etc). Eu pensei: se o Google fez esse problema, ele deve ter bolado alguma solução genérica que independa de ifs. Bom, não que eu saiba. Depois de terminado o tempo dei uma olhada em algumas soluções dos competidores e não achei nenhuma solução que usasse algum algoritmo maluco e genérico (não achei nenhum indiano, contudo).

Eis a solução porca e mal-resolvida (alguns pontos do códido foram feitos depois de ver o código de outrem):


Não, eu não usei o Google para descobrir a lógica por trás do problema. Vai que os caras ficam monitorando quem fica fazendo pesquisas. E, não, tampouco usei o Bing. Não sou masoquista a esse ponto.

PS: Bom, estou na próxima fase. Veremos o que o futuro nos espera. Esse programador foi fisgado pelo campeonato de pastéis.
