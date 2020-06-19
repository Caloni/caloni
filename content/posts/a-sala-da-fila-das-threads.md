---
categories: [ "code" ]
date: "2009-04-17"
tags: [ "draft",  ]
title: "A sala da fila das threads"
---
Quando falei sobre a fila das threads, e como cada thread espera pacientemente em uma fila até chegar sua vez de ser atendida no guichê das CPUs, também vimos como é fácil fazer caquinhas em um programa que roda paralelamente duas threads ou mais.

Também falei que iríamos resolver esse problema, afinal de contas, temos que salvar todos aqueles programas que usam dezenas de threads trabalhando ao mesmo tempo para contar números de um até dez.

A boa notícia é que o salvamento é mais simples do que parece: coloque todas as suas threads em uma sala trancada e deixe apenas uma chave. As threads terão que brigar para sair da sala e, depois que a vencedora sair, as outras terão que ficar esperando ela voltar.

Confuso? Se estiver, ainda bem. Isso quer dizer que estamos novamente em um daqueles artigos com "pseudo-parábolas", a maneira mais ilustrada de explicar as coisas.

Os SOs modernos possuem inúmeras maneiras de controlar e monitorar o acesso a recursos do sistema. Neste breve artigo irei falar apenas de um: o critical section, ou, em tradução livre, "seção crítica". O "seção" desse nome diz respeito a uma seção do programa, ou seja, um pedaço de código mesmo. Um pedaço de código crítico.

Resumidamente, um critical section é um recurso que apenas uma thread por vez pode obter. Para que outra thread tenha acesso ao mesmo critical section, a primeira thread que o obteve deve soltá-lo. Enquanto ela não solta, as outras threads ficam paradas, esperando pela chave, na sala trancada.

Do ponto de vista do programador, o critical secton é apenas uma estrutura que é usada na chamada de quatro funções básicas: para inicializar o recurso, para entrar na seção crítica.aspx), para sair da seção crítica.aspx) e para liberar o recurso.aspx) (quando aquele critical section não mais será usado).

Falando assim, parece simples. Bom, na verdade é simples, mesmo. Tudo que você precisa para corrigir o programa do artigo anterior é criar um critical section e fazer com que as threads obtenham-no antes de mexer com o contador compartilhado.


Para finalizar, algo para pensar: se uma thread só consegue um critical section depois que outra thread soltá-lo, o que acontece se essa outra thread estiver esperando por outro critical section que uma thread que aguarda estiver segurando?

Acabamos de ilustrar um procedimento muito simples para cagar completamente no código e gerar um travamento que pode demorar de horas a semanas para ser detectado e resolvido. É o conhecido deadlock. Se você não entendeu ainda, imagine que, para voltar à sala das threads, a primeira thread que saiu precisa de duas chaves; só que ela só pegou a primeira, e a segunda está dentro da sala. Para pegar a segunda chave, ela precisa entrar na sala, só que a sala está trancada pelas duas chaves!

Deadlocks são sempre indesejáveis, e é por isso que existem diversas técnicas para tentar evitá-los. A mais conhecida é sempre obter os critical sections na mesma ordem. Dessa forma a obtenção de recursos é hierarquizada, o que impede que dois CSs estejam no mesmo nível de obtenção, evitando que duas threads distintas os obtenham.

Espero que tenha ficado claro nossa breve explanação de como podemos controlar programas multithreading. Espero, pois a próxima tarefa é entender outros conceitos mais abstratos e virtuais, como funções virtuais e classes abstratas.
