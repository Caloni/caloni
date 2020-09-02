---
date: "2008-03-12"
tags: [ "code", "draft",  ]
title: "O mistério das pilhas diferentes"
---
Mal comecei a leitura do meu mais novo "mother-fucker" livro e já encontrei a solução para nunca mais viver o terror que vivi quando tive que testar minha engenharia reversa do artigo sobre o Houaiss. Se trata de uma simples questão que não sei por que não sigo todas as vezes religiosamente: configure seus símbolos corretamente.

Esse é o primeiro ponto abordado pelo autor, por se tratar de algo que, caso não seja bem feito, pode dar dores de cabeça piores do que o próprio problema que originou a sessão de debugging. Por isso eu repito:

Vamos acompanhar alguns momentos de tortura alheia?

Tudo aconteceu quando inesperadamente perdi metade do artigo que estava escrevendo para explicar o processo de engenharia reversa no dicionário Houaiss. Tive que refazer todos os meus testes que havia feito no laptop. Como a preguiça é a mãe de todas as descobertas, não estava com ele ligado no momento do "reteste" e por isso acabei usando a máquina desktop, mesmo.

A análise inicial consistia simplesmente em verificar as entradas e saídas da função ReadFile, na esperança de entender a formatação interna do dicionário. Repetindo a seqüência:



Se notarmos no artigo anterior, veremos que o conteúdo do arquivo lido não é em texto claro, sendo necessário passar por mais algumas instruções assembly para descobrir a função responsável por embaralhar o conteúdo na memória. Contudo, ao rodar esses comandos novamente, eis que a saída do ReadFile já vem toda legível, como se o dicionário não estivesse mais encriptado.

A leitura foi feita e o texto direto do arquivo veio em claro? O que está acontecendo? Quando abro pelo comando type ele aparece todo obscuro...

Sim, alguma coisa não-trivial acaba de acontecer. Testei esse procedimento no laptop e no desktop, sendo que esse problema aconteceu apenas no desktop. Dessa vez a curiosidade falou mais alto que a preguiça, e tive que abrir as duas máquinas e comparar os resultados.

Depois de um pouco de cabeçadas rastreando o assembly executado, descobri que o ponto onde o breakpoint havia parado não era o retorno da chamada a ReadFile. Isso eu não vou demonstrar aqui pois se trata de raciocínio de passo-a-passo no assembly até descobrir a diferença. É enfadonho e sujeito a erros. Sugiro que tente um dia desses. Para mim, o resultado lógico de tudo isso é a saída que segue:


Como podemos ver pelos comandos acima, o pseudo-registrador $ra não está mostrando o valor corretamente!

A primeira coisa que se faz numa hora dessas é comparar as versões dos componentes do depurador de ambos os ambientes. Para isso usamos o comando version.



OK. A versão instalada no desktop é bem antiga. Pode ser um indício. Fiz então a atualização e comparei novamente a saída de version.

Tudo igual.

Decidi então usar aquela lógica cética que é desenvolvida por quem costuma depurar coisas sinistras e esotéricas por anos e anos e não duvida de mais nada, mas também acredita piamente que tudo tem um motivo. Se não está aparente, basta descobri-lo. E foi o que eu fiz. Gerei dois dumps distintos, um no laptop e outro no desktop. Ambos estavam com os ponteiros de instrução apontados exatamente para a entrada da função ReadFile, início de todo esse problema. Copiei o dump do desktop para o laptop e vice-versa.

Abri o dump do desktop no laptop: tudo funcionando. Abri o dump do laptop no desktop: mesmo erro.

Conclusão óbvia: é algo relacionado com o WinDbg no desktop, uma vez que o estado da pilha que era mostrado corretamente no laptop em ambos os dumps falhava duplamente na máquina desktop.


Isso com certeza não cheira bem. Ainda mais porque do outro lado do hemisfério, meu laptop estava configurado com toda a rigidez que um laptop de WinDbgeiro deve ter:


E aí estava uma diferença plausível. Consertados os diretórios de símbolos, tudo voltou ao normal.

Procure primeiro verificar as coisas mais simples. Depois você tenta consertar o universo. Mas, primeiro, antes de tudo, veja se o cabo de rede está conectado. Ou no nosso cado de debugueiro: Configure Seus Símbolos Corretamente.
