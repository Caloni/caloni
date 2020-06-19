---
categories: [ "code" ]
date: "2009-07-10"
tags: [ "draft",  ]
title: "Polimorfismo estático"
---
Para explicar polimorfismo, nada como ver as coisas como elas eram. Se você fosse um programador C de vinte anos atrás e criasse as seguintes funções:


Imediatamente o compilador iria acusar os seguintes erros:



Isso acontece porque em C os identificadores são únicos por escopo. Esse é o motivo por que o seguinte código também está errado:



De volta aos anos 90, isso também está errado em C++. Até por uma questão de lógica: como o compilador pode saber a qual variável estamos nos referindo se usarmos o mesmo nome para duas delas?

Só que existe um truquezinho para impedir essa ambiguidade quando falamos de funções: os parâmetros que ela recebe.



Isso permitiu que em C++ fosse criada a sobrecarga estática, que é exatamente isso: chamar a função não apenas de acordo com seu nome, mas também de acordo com sua assinatura, ou seja, o número e o tipo dos parâmetros recebidos. Chamamos de sobrecarga estática porque isso é feito apenas pelo compilador, não pesando em nada durante a execução do programa.

Entre seus usos mais comuns estão os seguintes:

  * Ter funções com o mesmo nome mas que tratam de diferentes parâmetros;




  * Versões novas da mesma função que recebem parâmetros adicionais;



  * Mesmo nome de método para setar e obter o valor de uma propriedade;



  * Bom, o que mais sua imaginação mandar =)

