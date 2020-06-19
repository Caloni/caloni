---
categories: [ "code" ]
date: "2008-02-01"
tags: [ "draft",  ]
title: "Compartilhando variáveis com o mundo v2"
---
Nota de desempenho: esse artigo finaliza (finalmente) a republicação de todos os artigos do antigo blogue. Isso quer dizer que a partir de agora eu sou obrigado a trabalhar, e, se quiser manter meu ritmo atual, vou ter que fazer mais do que cinco cliques do mouse.

Como todas as coisas que fazemos e pensamos depois, descobrimos que sempre existe uma outra maneira de fazer a mesma coisa. Se é melhor ou não, pode ser uma questão de gosto, estética, objetivos de vida, etc. Com a implementação das variáveis mapeadas globais não foi diferente. Bem, é isso que se espera fazer com código experimental: experimentos. E deu no que deu: SharedVar versão 2.0 alpha Enterprise Edition.

Quando comentei no final do artigo anterior que existem pessoas que só conseguem gerar código dentro de uma classe, não estava brincando. Existem linguagens, inclusive, que suportam apenas o paradigma de orientação a objetos, e levam isso muito a sério. C++ com certeza não é uma dessas linguagens, o que quer dizer que você tem a liberdade e a responsabilidade de tomar o melhor caminho para determinado problema.

Nessa segunda solução do nosso programa alocador de variáveis globais, pra variar, vamos utilizar uma classe. E pra entrar de vez no mundo POO vamos utilizar de quebra tratamento de erro orientado a exceções. Como vamos notar, aplicadas adequadamente, essas duas características da linguagem conseguirão um código mais simples de entender, embora não se possa dizer o mesmo da implementação "under the hood".


Como podemos notar, em programação "nada se cria, tudo se reutiliza". Reutilização é boa quando podemos acrescentar características adicionais ao código sem deturpar seu objetivo original. E isso é bom.

Note que nossa classe tenta fazer as coisas logo no construtor, já que seu único objetivo é representar uma variável da memória cachê. Se ela não for bem-sucedida em sua missão, ela explode, porque não há nada que ela possa fazer para garantir a integridade do objeto sendo criado e ela não tem como saber qual o melhor tratamento de erro para o usuário da classe. Geralmente o melhor - ou pelo menos o mais adequado - é o tratamento que o usuário dá ao seu código, porque o usuário da classe é que deve saber o contexto de execução do seu código.

Bem, como o código agora está em uma classe e o erro é baseado em exceção, o código cliente muda um pouco:


Existem duas mudanças significativas: 1. a variável sozinha já representa a memória compartilhada; 2. o tratamento de erro agora é centralizado em apenas um ponto. Se pra melhor ou pior, eu não sei. Tratamento de exceções e classes são duas "modernisses" que podem ou não se encaixar em um projeto de desenvolvimento. Tudo vai depender de tudo. Por isso a melhor saída depende de como será a entrada.
