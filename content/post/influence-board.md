---
categories: [ "code" ]
date: "2008-03-14"
tags: [ "draft",  ]
title: "Influence Board"
---
Há muito tempo sou enxadrista não-praticante. Acho que os anos de programação me deixaram mais viciado em codar do que pensar no xeque-mate. No entanto, sempre que posso, dou uma escapulida do Visual Studio e jogo uma partida ou duas na rede, quase sempre, é claro, tomando um piau psicológico.

A falta de prática e estudos pesa muito para um enxadrista amador, já que facilmente esquecemos das combinações mortíferas que podemos aplicar e levar. É muito difícil ter em mente aquelas três dúzias de aberturas que já são batidas (e suas variantes), ou então as regrinhas de praxe de como detonar nas finais com um cavalo e um bispo.

Por isso mesmo aprendi em um livro uma técnica universal e independente de decoreba que levei pra vida toda, e tem me trazido algumas partidas no mínimo interessantes. Se trata de analisar o esquema de influências em cima do tabuleiro. Influências, nesse caso, se refere ao poder de fogo das peças amigas e inimigas. O interessante é que deixa-se de lado a análise das próprias peças! Se estuda tão somente o tabuleiro, e apesar de parecer um método difícil, ele melhora sua percepção gradativamente, e é responsável por muitas das partidas simultâneas jogadas às cegas por alguns ilustres GMIs.

Atenção: esse artigo trata sobre xadrez admitindo que o leitor saiba as regras básicas do jogo, assim como um pouco de estratégia. Se você chegou até aqui e está viajando, sugiro que pare de ler e vá jogar uma partida.

Vamos supor que a posição no tabuleiro em um dado momento seja a seguinte:

Ora, é um mate inevitável, não é? Agora imagine por um momento que você não tenha percebido isso, e precise de uma ajudinha para saber onde cada peça pode ir ou atacar no próximo lance.

Agora ficou muito mais fácil de perceber que a única saída do rei não possui nenhuma proteção, já que tanto o peão quanto o próprio rei não podem fazer muita coisa se a dama atacar a diagonal vulnerável. E ela pode fazer isso.

Essa maneira de mostrar as influências em um tabuleiro de xadrez eu apelidei de Influence Board, e criei um projeto em linha de comando para fazer as devidas considerações a respeito de uma posição determinada. Mas como ninguém hoje em dia gosta de usar o WinDbg pra jogar xadrez, transformei meu projeto em pseudo-plugin para o WinBoard, um famoso frontend de xadrez que costumo usar em minhas esporádicas partidas.

    
    C:\Projects\xboard infboard\winboard>nmake msvc.mak
    
    Microsoft (R) Program Maintenance Utility Version 8.00.50727.42
    Copyright (C) Microsoft Corporation.  All rights reserved.
    
            link /DEBUG /DEBUGTYPE:cv  /INCREMENTAL:NO /NOLOGO -subsystem:windows,5.0 WIN2000_DEBUG\winb
    oard.obj WIN2000_DEBUG\backend.obj WIN2000_DEBUG\parser.obj WIN2000_DEBUG\moves.obj WIN2000_DEBUG\li
    sts.obj  WIN2000_DEBUG\gamelist.obj WIN2000_DEBUG\pgntags.obj WIN2000_DEBUG\wedittags.obj WIN2000_DE
    BUG\wgamelist.obj WIN2000_DEBUG\zippy.obj  WIN2000_DEBUG\wsockerr.obj WIN2000_DEBUG\wclipbrd.obj WIN
    2000_DEBUG\woptions.obj WIN2000_DEBUG\infboard.obj  wsock32.lib comctl32.lib winmm.lib oldnames.lib
    kernel32.lib  advapi32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib  ws2_32.lib   WIN2000_DEBU
    G\winboard.rbj -out:WIN2000_DEBUG\winboard.exe

Após compilado, basta copiar na pasta de instalação do programa, rodá-lo e habilitar a opção "Show Influence" do menu General. Voilà! É possível até jogar às cegas com esse brinquedinho (opção Blindfold).

Bom divertimento!
