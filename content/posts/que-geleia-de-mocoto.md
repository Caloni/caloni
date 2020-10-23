---
date: "2014-04-29"
tags: [ "code", "draft" ]
title: "Que geleia de mocotó"
---
A primeira bateria de problemas da segunda fase do Code Jam me mostrou o porquê do seu nome: meu cérebro ficou feito geleia (ha ha ha). Não consegui resolver nenhum problema a tempo, mas não culpo o C++, que passei a usar para essa fase. É burrice aliada a pressão. Duas horas e meia para entender um problema é o tipo de coisa que me deixa pensando mais no tempo do que no problema. Tenho que melhorar isso.

De qualquer forma, esse final de semana que passou foi dedicado a resolver o primeiro problema e quem sabe escrever um post a respeito. Imagino que todos tenham acesso ao enunciado e aos casos de teste, mas, por via das dúvidas, aqui vai uma descrição adaptada:

Você é um fazendeiro hi-tech com uma vaca que tem um tablet. Não especifica se esse cowblet é um iPad, mas é uma possibilidade, já que como nenhum plugue parece encaixar nas tomadas de sua fazenda, é muito provável que você seja um Applemaníaco com um monte de gadgets que precisam de conversor vindos direto do eBay.

Através do eBay também veio um engenheiro chinês cuja missão é resolver esse gato que o Sr. Fazendeiro fez em sua fazenda. Tudo que ele precisa fazer é girar gigantescos switches (ou disjuntores) que invertem a polaridade binária de cada um dos pino dos conectores das tomadas. Quando um plugue de dispositivo e uma tomada possuem a mesma configuração de bits é possível conectá-los. O objetivo final é que todos os N plugues conectem nas N tomadas depois de virados Y switches, sendo que quanto menos switches melhor (afinal, eles são gigantescos, e o chinês supõe-se que seja pequeno).

O primeiro pensamento do programador preguiçoso (go, horse, go!) manda que usemos a velha força bruta e testemos todas as combinações possíveis de disjuntores, peguemos o com menor número de bits setados (inicialmente, todos estão em 0) e zás! Porém, o caso de teste tamanho large pressupõe que o limite de pinos das tomadas pode chegar a 40, o que seria responsável por nada mais nada menos que 2^40 combinações diferentes, ou 1.099.511.627.776 para ser exato. Isso dá mais de 1 trilhão! Mesmo que nosso código seja extremamente rápido e demore apenas um milissegundo para cada combinação, serão mais de 34 anos desperdiçados, que poderiam estar melhor investidos minerando bitcoins.

Dessa forma, temos que traçar uma solução baseada nas combinações entre as tomadas e plugues, que, pelos limites da versão large dos casos de teste, podem ter a quantidade de 150, o que dá 150 * 150 = 22500 combinações de XOR.

Sim, de XOR. O XOR aqui pode ser usado para detectarmos qual a combinação de switches precisamos para que cada tomada encaixa em cada dispositivo. Esse é o nosso conjunto universo de giros de disjuntores. Com esse conjunto em mãos fica fácil saber quais combinações são possíveis de encaixar todos os dispositivos: basta contar!


Observação: note que retirei o wrapper costumeiro dos exercícios do Code Jam para não poluir demais o exemplo com código. E, na verdade, essa parte do código está compartilhada com todas as soluções (reuse!).

O que aprendi dessa pequena aventura foi: não importa o quanto um problema pareça fácil, anotar em um pedaço de papel é o caminho mais curto entre a mente e o código.

Que venha a segunda bateria de problemas!
