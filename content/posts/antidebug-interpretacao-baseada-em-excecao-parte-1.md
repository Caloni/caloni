---
date: "2007-07-20"
link: "/ppt/antidebugging-eu-nao-quero-que-vc-mexa-no-meu-codigo.pdf"
tags: [ "code", "draft",  ]
title: "Antidebug: interpretação baseada em exceção (parte 1)"
---
Um depurador utiliza breakpoints para "paralisar" momentaneamente a execução do programa sendo depurado. Para isso ele se utiliza de uma bem conhecida instrução conhecida como int 3. Essa instrução gera uma exceção - exceção de breakpoint - que é capturada pelo sistema operacional e repassada para o código de tratamento dessa exceção. Em programas sendo depurados esse código está localizado no depurador. Em programas "livres" esse código normalmente não existe e ao acontecer essa exceção o aplicativo simplesmente "capota".

A idéia principal na proteção baseada em exceção é tomarmos conta dessas exceções durante a execução do aplicativo. Fazendo isso podemos nos aproveitar desse fato e, no código responsável por tratar a exceção, executar o código protegido. A solução discutida aqui é parecido com um interpretador de scripts. Consiste basicamente de duas threads. A primeira thread lê uma seqüência de instruções e manda a segunda thread executá-las passo a passo. Para fazer isso a segunda thread usa um conjunto de pequenas funções com blocos de código bem definidos. Em pseudocódigo isso ficaria assim:


A proteção ainda não está aí. Mas fará parte intrínseca da thread de execução. Tudo que precisamos fazer é adicionar um tratamento de exceções e fazer chover ints 3. As exceções disparadas pela int 3 são capturadas por uma segunda função que antes de retornar o controle executa a próxima instrução enfileirada:


O algoritmo da thread de execução continua o mesmo. Só que o ponto onde cada instrução é executada depende do lançamento de uma exceção. Note que essa exceção tem que ocorrer para que a chamada da próxima instrução ocorra. Isso é fundamental, pois dessa forma ninguém pode simplesmente retirar o int 3 do código para evitar o lançamento da exceção. Se fizer isso, então mais nenhuma instrução será executada.

Na prática, se alguém tentar depurar um programa desse tipo vai ter que enfrentar dezenas ou centenas de lançamento de exceções até descobrir o que está acontecendo. Claro que, como em toda a proteção de software, ela não é definitiva; tem por função dificultar o trabalho de quem tenta entender o software. Isso não vai parar aqueles que são realmente bons no que fazem.

O preço pago por essa proteção fica na visibilidade e compreensão do código-fonte comprometidos pelo uso da técnica. A programação fica baseada em uma máquina de estados e as funções ficam limitadas a algum tipo de padronização no comportamento. Quando mais granular for o pseudoscript, ou seja, quanto menores forem os blocos de código contido nas minifunções, mais difícil de entender o código será.

O exemplo abaixo recebe entrada por um prompt de comandos e mapeia a primeira palavra digitada para o índice de uma função que deve ser chamada. O resto da linha digitada é passado como parâmetro para essa função. A thread de interpretação lê a entrada do usuário e escreve em uma variável-string global, ao mesmo tempo que a thread de execução espera essa string ser preenchida para executar a ação. Foi usado o pool dessa variável para o código ficar mais simples, mas o ideal seria algum tipo de sincronismo, como eventos, por exemplo.


O ponto forte da proteção é que a pessoa precisa entender o que está acontecendo para tomar alguma atitude inteligente para solucionar o "problema". O ponto fraco é que após entendido o problema a solução torna-se fácil de visualizar. Tão fácil que eu nem pretendo citar aqui.

Futuramente veremos uma maneira de tornar as coisas mais legíveis e usáveis no dia-a-dia de um programador de software de segurança.
