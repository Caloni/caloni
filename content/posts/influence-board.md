---
date: "2008-03-14"
title: "Influence Board"
categories: [ "code" ]
---
Há muito tempo sou enxadrista não-praticante. Acho que os anos de programação me deixaram mais viciado em codar do que pensar no xeque-mate. No entanto, sempre que posso, dou uma escapulida do Visual Studio e jogo uma partida ou duas na rede, quase sempre, é claro, tomando um piau psicológico.

A falta de prática e estudos pesa muito para um enxadrista amador, já que facilmente esquecemos das combinações mortíferas que podemos aplicar e levar. É muito difícil ter em mente aquelas três dúzias de aberturas que já são batidas (e suas variantes), ou então as regrinhas de praxe de como detonar nas finais com um cavalo e um bispo.

Por isso mesmo aprendi em um livro chamado Xadrez sem Mestre, de J. Carvalho, uma técnica universal e independente de decoreba que levei pra vida toda, e tem me trazido algumas partidas no mínimo interessantes. Se trata de analisar o esquema de influências em cima do tabuleiro. Influências, nesse caso, se refere ao poder de fogo das peças amigas e inimigas. O interessante é que deixa-se de lado a análise das próprias peças! Se estuda tão somente o tabuleiro, e apesar de parecer um método difícil, ele melhora sua percepção gradativamente, e é responsável por muitas das partidas simultâneas jogadas às cegas por alguns ilustres GMIs.

![Chess Board](/img/influence-board.png)

> Atenção: esse artigo trata sobre xadrez admitindo que o leitor saiba as regras básicas do jogo, assim como um pouco de estratégia. Se você chegou até aqui e está viajando, sugiro que pare de ler e vá jogar uma partida.

Vamos supor que a posição no tabuleiro em um dado momento seja a seguinte:

![Winboard Mate](/img/winboard-mate.png)

Ora, é um mate inevitável, não é? Agora imagine por um momento que você não tenha percebido isso, e precise de uma ajudinha para saber onde cada peça pode ir ou atacar no próximo lance.

![Winboard Mate (com influências)](/img/winboard-mate-influence.png)

Agora ficou muito mais fácil de perceber que a única saída do rei não possui nenhuma proteção, já que tanto o peão quanto o próprio rei não podem fazer muita coisa se a dama atacar a diagonal vulnerável. E ela pode fazer isso.

![Winboard Mate Final](/img/winboard-mate-final.png)

Essa maneira de mostrar as influências em um tabuleiro de xadrez eu apelidei de Influence Board, e criei um projeto em linha de comando para fazer as devidas considerações a respeito de uma posição determinada. Mas como ninguém hoje em dia gosta de usar o WinDbg pra jogar xadrez, transformei meu projeto em pseudo-plugin para o [WinBoard], um famoso frontend de xadrez que costumo usar em minhas esporádicas partidas.

Basicamente a única coisa que o futuro usuário das influências deve fazer é baixar o projeto WinBoard; no caso a versão disponível [meu repositório do GitHub] (obs.: já contém o XBoard e o WinBoard completos) e compilar (suporta cmake). Caso queira uma versão nova do programa terá que fazer o merge entre as duas versões (a versão base usada foi a 2.4.7).

    mkdir build && cd build
    cmake -A Win32 ..
    cmake --build .

Após compilado, basta rodar o winboard.exe gerado; haverá uma nova opção "Show Influence" do menu General. Voilà! É possível até jogar às cegas com esse brinquedinho (opção Blindfold).

![WinBoard Options](/img/winboard-options3.png)

![Winboard Blindfold e Influence](/img/winboard-blindfold.png)

Bom divertimento!

[WinBoard]: http://www.tim-mann.org/xboard.html
[meu repositório do GitHub]: https://github.com/Caloni/influence_board
