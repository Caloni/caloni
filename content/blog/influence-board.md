---
date: "2008-03-14"
title: Influence Board
categories: [ "blog" ]
---
[![Chess Board](http://i.imgur.com/4Zv3zxQ.png)](/images/board.png)Há muito tempo sou enxadrista não-praticante. Acho que os anos de programação me deixaram mais viciado em codar do que pensar no xeque-mate. No entanto, sempre que posso, dou uma escapulida do Visual Studio e jogo uma partida ou duas na rede, quase sempre, é claro, tomando um piau psicológico.

A falta de prática e estudos pesa muito para um enxadrista amador, já que facilmente esquecemos das combinações mortíferas que podemos aplicar e levar. É muito difícil ter em mente aquelas três dúzias de aberturas que já são batidas (e suas variantes), ou então as regrinhas de praxe de como detonar nas finais com um cavalo e um bispo.

Por isso mesmo aprendi em um [livro](http://www.traca.com.br/?mod=LV180839&origem=resultadodetalhada) uma técnica universal e independente de decoreba que levei pra vida toda, e tem me trazido algumas partidas no mínimo interessantes. Se trata de analisar o esquema de influências em cima do tabuleiro. Influências, nesse caso, se refere ao poder de fogo das peças amigas e inimigas. O interessante é que deixa-se de lado a análise das próprias peças! Se estuda tão somente o tabuleiro, e apesar de parecer um método difícil, ele melhora sua percepção gradativamente, e é responsável por muitas das partidas simultâneas jogadas às cegas por alguns ilustres GMIs.

<blockquote>_Atenção: esse artigo trata sobre xadrez admitindo que o leitor saiba as regras básicas do jogo, assim como um pouco de estratégia. Se você chegou até aqui e está viajando, sugiro que pare de ler e vá jogar uma partida._</blockquote>

#### Exemplo simples

Vamos supor que a posição no tabuleiro em um dado momento seja a seguinte:

[](http://i.imgur.com/6IfiNAY.png)

[![Winboard Mate](http://i.imgur.com/6IfiNAY.png)](/images/winboard-mate.png)

Ora, é um mate inevitável, não é? Agora imagine por um momento que você não tenha percebido isso, e precise de uma ajudinha para saber onde cada peça pode ir ou atacar no próximo lance.

[](http://i.imgur.com/GByvceA.png)

[![Winboard Mate (com influências)](http://i.imgur.com/GByvceA.png)](/images/winboard-mate-influence.png)

Agora ficou muito mais fácil de perceber que a única saída do rei não possui nenhuma proteção, já que tanto o peão quanto o próprio rei não podem fazer muita coisa se a dama atacar a diagonal vulnerável. E ela pode fazer isso.

[](http://i.imgur.com/0Nsxat3.png)

[![Winboard Mate Final](http://i.imgur.com/0Nsxat3.png)](/images/winboard-mate-final.png)

#### Influence Board

Essa maneira de mostrar as influências em um tabuleiro de xadrez eu apelidei de Influence Board, e criei um projeto em linha de comando para fazer as devidas considerações a respeito de uma posição determinada. Mas como ninguém hoje em dia gosta de usar o WinDbg pra jogar xadrez, transformei meu projeto em pseudo-_plugin_ para o [WinBoard](http://www.tim-mann.org/xboard.html), um famoso _frontend_ de xadrez que costumo usar em minhas esporádicas partidas.

#### Como usar

Basicamente a única coisa que o futuro usuário das influências deve fazer é baixar o [projeto WinBoard](http://ftp.gnu.org/gnu/winboard/winboard-4_2_7b.exe), a versão disponível [aqui](/images/xboard%20infboard.7z) (obs.: já contém o WinBoard completo) e compilar. Caso queira uma versão nova do programa terá que fazer o merge entre as duas versões, e por isso deixei disponívei também um [patch](/images/infboard.7z) que instala o "_plugin_" (obs.: a versão usada foi a 2.4.7).

    
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

[![WinBoard Options](http://i.imgur.com/G67wagx.png)](/images/winboard-options3.png)

[](http://i.imgur.com/R5SjM7r.png)

[![Winboard Blindfold e Influence](http://i.imgur.com/R5SjM7r.png)](/images/winboard-blindfold.png)

Bom divertimento!
