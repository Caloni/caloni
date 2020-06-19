---
categories: [ "code" ]
date: "2008-06-06"
tags: [ "draft",  ]
title: "Declaração x definição"
---
Uma diferença que eu considero crucial na linguagem C/C++ é a questão da declaração/definição (em inglês, declaration/definition). É a diferença entre esses dois conceitos que permite, por exemplo, que sejam criadas estruturas prontas para serem conectadas a listas ligadas:


Por outro lado, e mais importante ainda, é ela que permite que as funções sejam organizadas em unidades de tradução (cpps) distintas para depois se unirem durante o link, mesmo que entre elas exista uma relação de dependência indissociável:

Existem diversas formas de entender esses dois conceitos. Eu prefiro explicar pela mesma experiência que temos quando descobrimos a divisão hardware/software:

  - Hardware é o que você chuta
  - Software é o que você xinga

Exatamente. Hardware é algo paupável, que você pode até chutar se quiser. Por exemplo, a sua memória RAM! No entanto, software é algo mais abstrato, que nós, seres humanos, não temos a capacidade de dar umas boas pauladas. Portanto, nos abstemos a somente xingar o maldito que fez o programa "buggento".

Da mesma forma, uma declaração em C/C++ nos permite moldar como será alguma coisa na memória, sem no entanto ocupar nem um mísero byte no seu programa:


Por outro lado, a definição, o hardware da história, sempre ocupará alguma coisa na memória RAM, o que, de certa forma, permite que você chute uma variável (embora muitas outras também irão para o saco).


Dessa comparação só existe uma pegadinha: uma definição também é uma declaração. Por exemplo, nos exemplos acima, além de definir func, tst e x, o código também informa ao compilador que existe uma função chamada func, que existe uma variável tst do tipo Teste e uma variável x do tipo int.

Informa ao compilador? Essa é uma outra ótima maneira de pensar a respeito de declarações: elas sempre estão conversando diretamente com o compilador. Por outro lado, nunca conversam diretamente com o hardware, pois ao executar seu código compilado, as declarações não mais existem. Foi apenas um interlúdio para que o compilador conseguisse alocar memória da maneira correta.

Complicado? Talvez seja, mesmo. Mas é algo que vale a pena fixar na mente. Isso, é claro, se você quiser ser um programador C/C++ mais esperto que os outros e resolver pequenos problemas de compilação que muitos perdem horas se perdendo.

Então por que diabos a separação declaração/definição consegue definir coisas como listas ligadas, como no código acima? A resposta é um pouco ambígua, mas representa regra essencial na sintaxe da linguagem: após a definição do nome e do tipo de declaração envolvida podemos referenciá-la como declaração, ou seja, não ferindo a limitação de que não sabemos o tamanho de uma variável do tipo declarado. Dessa forma, é perfeitamente legal definirmos um ponteiro para uma estrutura que ainda não se sabe muita coisa, além de que é uma estrutura:


Dessa forma, o começo de uma definição de estrutura já declara o nome da estrutura antes de terminar a declaração do tipo inteiro. Bizarro, não? De qualquer forma, isso permite a construção clássica de lista ligada:


Se vermos pelo lado prático, de qualquer forma seria impossível definir uma variável dentro dela mesma, pois isso geraria uma recursão infinita de definições, e, como sabemos, os recurso da máquina são finitos.
