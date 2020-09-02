---
date: "2014-01-08"
tags: [ "code", "draft",  ]
title: "BovespaBacktesting"
---
Eu não sou apenas um programador: sou um especulador. Ou, para quem ficou com medo, um investidor. Ficou bonito, agora? Trocando em miúdos, isso quer dizer que muitas vezes aposto na bolsa de valores, aquela onde as pessoas ganham e perdem dinheiro loucamente. Porém, assim como faço com minha carreira de desenvolvedor, não deixo de estudar e aprimorar minhas habilidades. Tirando alguns anos de estudo com livros de finanças, economia e contabilidade, foi com base nisso que eu fiz uma série de scripts que realiza operações de backtesting nos papéis da Bovespa.

Backtesting é uma maneira dos especuladores terem uma noção de quão bom ou ruim é sua estratégia de compra e venda. É uma maneira profissional de se aproximar do mercado caótico das ações. Basicamente um backtesting simula o que o especulador faria na vida real com um histórico razoável de variação de preços das ações que pretende operar. Se esse monte de palavras novas neste blogue está te deixando com medo, recomendo dar uma passada no Senhor Mercado (lá você irá também aprender mais sobre técnicas de backtesting).

Vamos supor que minha ideia de estratégia seja comprar quando o preço de uma determinada ação estiver na metade do seu topo histórico e vender quando ele estiver no dobro do momento da compra. Uma estratégia bem tosca, mas se fizer dinheiro, quem liga para vaidade? Outra estratégia mais refinada usa médias móveis para estabelecer pontos de compra e venda dependendo da tendência do mercado. Qual das duas dá mais dinheiro? Existem duas maneiras de saber: a dolorosa e a indolor. A dolorosa seria sacar uma grana do banco e começar a operar em sua corretora favorita seguindo ambas as estratégias e ver qual te deixou mais rico e qual te levou à falência. A indolor seria baixar o histórico de preços dos papéis que está interessado em usar essas estratégias e rodar uma simulação que opere seguindo ambas as estratégias e descubra qual é a perdedora. Qual você preferiria?

OK, esse assunto já está ficando bem monótono para quem acompanha um blogue de programação. Vamos ao código!

O projeto que mantenho no GitHub possui algumas ideias que gostaria de compartilhar com todos que estão interessados em realizar um backtesting, independente de sua estratégia. A primeira delas seria de onde baixar o histórico de preços de maneira simples e barata. Eu recomendo e uso o software Grafix, que consegue baixar as informações diretamente do saite da Bovespa e realizar os ajustes necessários para montar e exibir as informações. Com base no banco de dados do Grafix é que o BovespaBacktesting (meu projeto) importa as informações que ele precisa. Ele irá importar apenas os códigos que estiverem em uma lista disponível no arquivo data/filterCodes relativo de onde o script estiver rodando. Esse arquivo é apenas texto com um código por linha.


A partir dessa importação é possível realizar queries com as variações diárias, semanais e mensais dos preços dos ativos conhecidos (a mesma lista de código). A própria lista de ativos conhecidos está disponível através de uma função, tornando a iteração simples e direta.


Com essas informações de preço é possível aplicar qualquer tipo de indicador. O BovespaBackteting possui apenas os mais usuais, mas basta implementar a lógica de tratamento em Python, o que não deve consumir nem muito tempo nem muitos neurônios, pois com o histórico disponível tudo fica mais fácil.


As funções-macro calculam trades (operações) a partir de alguns parâmetros definidos no código ou por parâmetros. As versões do BovespaBacktesting foram variando nesse sentido. Ainda não há uma maneira saudável de comparar diversas estratégias, pois o que eu tenho feito basicamente é alterar alguns parâmetros, rodar o backtesting e exportar para um CSV (função já disponível).


Já existem algumas firulas caso você esteja pensando em uma estratégia em que seja viável viver de operar, como cálculo de salário e a inclusão de variáveis que levem em conta que parte do dinheiro ganho será usado. Ainda é um código bem tosco, mas funciona e pode ser o ponto de entrada de quem deseja conhecer mais sobre o mercado de ações e como os profissionais conseguem tirar dinheiro deste grande cassino.
