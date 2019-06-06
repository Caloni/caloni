---
date: "2008-08-15"
title: Duas pequenas dicas para programar no caos
categories: [ "code" ]
---
Ultimamente não tenho acertado muito bem meus cronogramas, com erros que variam de um dia a uma semana. A causa desse problema, pelo que eu tenho conseguido detectar, está em dois problemas que acredito acontecer de maneira muito freqüente em um ambiente de desenvolvimento que [ainda está no caos](http://brazil.joelonsoftware.com/Articles/TheJoelTest.html):

	
  * Mudança constante de prioridade

	
  * Falta de testes básicos no software antes de mexer

Portanto, aí vão algumas dicas empíricas para lidar com esses detalhezinhos que são "faceizinhos de serem esquecidinhos" (by [Rafael](http://www.sk5.com.br)).

#### Nunca, nunca, nunca comece nada antes de terminar o que está fazendo

Simples de dizer, não? No entanto, se o que você está fazendo é tão pequeno quanto duas horas passa a ficar um pouco mais fácil. E isso é possível se você souber [fazer direito um cronograma](http://www.caloni.com.br/cronograma), dividindo suas tarefas em tarefas menores, mais paupáveis e "pausáveis".

[![tarefasimportanteseurgentes.PNG](/images/tarefasimportanteseurgentes.PNG)](http://www.caloni.com.br/todolist)

Um exemplo real serial o de uma mudança em um projeto que envolva três componentes: uma LIB estática, um componente COM e um _driver_. No caso de ser necessário parar no meio do projeto, é importante que essas três partes estejam bem separadas em tarefas que alteram o código-fonte um a um, sendo a última tarefa a integração entre todos. É interessante notar que, se for bem estruturado o projeto, é possível fazer testes individuais por componente antes da integração de fato, o que torna as coisa bem menos dolorosas. A divisão seria algo incremental e possivelmente paralelizável:

![todolistcomponentizado.PNG](/images/todolistcomponentizado.PNG)

#### Sempre, sempre, sempre teste o básico da parte do software que irá mexer

Você tem certeza que o programa está rodando como deveria, que não existem problemas paralelos e relacionados que podem prejudicar seu desempenho cronogrametal? A última versão funciona realmente como deveria funcionar? Não? Nesse caso, esqueça sua estimativa inicial: ela foi pro espaço. Quer dizer, do ponto de vista otimista, adiada para depois de serem resolvidos os problemas atuais.

Mais uma vez, os testes individuais (chamados de _[unit tests](http://en.wikipedia.org/wiki/Unit_testing)_) são importantes para a consistência do projeto no decorrer de sua vida. Isso aliado a um processo de build automatizado que detecte erros de funcionamento e compilação pode economizar um tempo enorme na hora de fazer uma "pequena modificaçãozinha" naquele fonte escroto.

Em empresas onde a qualidade de _software_ é piada, essas duas atitudes podem salvar algumas vidas e projetos no meio do caminho, apesar de parar no meio das tarefas não ser uma das melhores práticas de um desenvolvimento sério.
