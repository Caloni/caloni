---
date: "2016-08-17"
categories: [ "draft" ]
title: "Se não está funcionando direito, mexa!"
---
Uma breve história de um chuveiro: O de casa às vezes inventa de dar choque. Isso desde que me mudei (uns 2 anos e meio). Não são choques brabos, daqueles de fazer a pessoa tremer. É apenas uma quase estática ao tocar no registro para abrir ou fechar a água. No entanto, já é motivo para pessoas mais sensíveis, como minha sobrinha de oito anos, se recusar a encostar no registro. Frecura.

(Pensando bem, quando eu era criança, tinha até medo de ficar no mesmo quarto onde havia fiação desencapada, mesmo sem energia.)

De uma semana pra cá, agora o chuveiro tem "aprontado" outra: ele desliga. Do nada. Não há nada de errado com a resistência, nem com os fios, e depois descobri, nem com a energia (não tinha um testador de tensão antes). Aliás, de vez em quando, ele liga de novo. Quando fui reclamar com o zelador, minutos atrás tentando fazê-lo ligar, adivinha quem ficou com cara de bobo demonstrando como o chuveiro estava funcionando perfeitamente?

No entanto, ele me deu uma "dica": é o disjuntor. Pensei comigo mesmo: "agora os choques fazem sentido; ele desligar (e ligar) do nada faz sentido; a vida faz sentido!".

Dito e feito. No dia seguinte fui comprar um novo. Mesmo modelo, tudo certinho (aproveitei e comprei o tal testador de tensão). Quando fui retirar o velho, notei que havia um fio desencapado muito próximo de uma das entradas de energia do dito cujo.

É nessa entrada que se conecta um pino de onde vem a energia da central. Do lado deste pino havia um fio, como quem não quer nada, "passeando" bem próximo do pino. Notei também que havia outro do lado, no disjuntor do microondas.

O apartamento onde estou é novo e sou o primeiro morador. Recebi com garantia e tudo. Para mim não fazia sentido que houvesse algo de errado com as instalações elétricas, principalmente porque já habitava o local há mais de dois anos.

Mas não é que estava errado, mesmo?

Depois de algumas horas sofrendo em tentar entender a lógica por trás das conexões -- pois obviamente eu troquei o disjuntor e nada mudou -- descobri que o parafuso que faz o aperto do pino de energia no disjuntor original estava meio frouxo, e às vezes ele não empurrava a barra usada para fixar o pino, ficando o pino frouxo. Imediatamente (tipo duas horas depois, já escurecendo e eu sem energia a não ser a luz do notebook sem internet) deduzo que quando o eletricista foi fazer a instalação, ou na última manutenção feita, esse fio desencapado muito próximo do pino de tensão deve ter ficado de fora da conexão do disjuntor, mas próximo o suficiente para coseguir uma conexão eventual. Muito provavelmente este fio é o terra, e a falta dele deve ter originado os choques eventuais, além de agora, por algum desarranjo na posição capenga em que estava, ele começou a se separar do pino/disjuntor e gerar todo esse rebuliço.

Então eu finalmente tomo coragem, decido que a instalação está errada, e coloco o fio desencapado junto do pino da corrente (até porque agora o disjuntor novo não tinha esse problema do parafuso, facilitando a operação). E ligo a central (esperando uma explosão, tipo aquelas de filmes de ação).

E tudo funciona!

A essa altura do campeonato, se você ainda está lendo isso, deve estar se perguntando o que tudo isso tem a ver com desenvolvimento de software. Ora, achei que a analogia fosse clara. Quando vamos mexer em código de terceiros, há uma mania muito sadia, mas algumas vezes traiçoeira, de acreditar que tudo o que está ali está obviamente funcionando, já que usuários estão usando e provavelmente a equipe original passou pelos perrengues necessários para colocar tudo nos eixos.

Certo? Certo?

Na maioria dos casos, certo. Porém, todo software tem bugs. E quando mexemos em código dos outros, em toda nossa humildade, nunca esperamos que haja um problema grave no comportamento principal do programa (ex: o Excel não fazer um cálculo direito). Talvez pela falsa impressão que o simples passar do tempo já valida qualquer possível bug escondido (se esquecendo da história do BSD e seu bug de 25 anos). Ledo engano. É aí que o bug fica difícil de ser corrigido, pois não há mais programadores desconfiadinhos do lado do código, e a nova leva sabe que ele está rodando faz tempo, então mais respeito...

A mensagem é clara. Antes de tirar qualquer conclusão precipitada a respeito da suposta qualidade do código que irá mexer (mesmo que esse software rode em milhões de máquinas por milhões de anos), faça um check-list de que tudo o que está vendo faz realmente sentido. Se não fizer, dobre sua atenção e valide suas premissas. Se ainda assim não fizer sentido, talvez seja hora de fazer alguma coisa. Do contrário, esse código corre o sério risco de ter aqueles comentários "não mexa aqui ou para de funcionar", e ninguém mais sabe por quê.

E você corre o risco de levar choques sem saber por quê.
