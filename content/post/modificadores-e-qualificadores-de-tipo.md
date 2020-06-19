---
categories: [ "code" ]
date: "2010-05-28"
tags: [ "draft",  ]
title: "Modificadores e qualificadores de tipo"
---
@caloni poderia pensar em fazer um artigo sobre os modificadores de tipo em c? os mais complexo, acho eu: volatile, enum, union, extern, etc

Uma coisa de cada vez: existem modificadores (ou qualificadores) de tipo e especificadores de tipo. Volatile e extern se encaixam na primeira categoria, enum e union na segunda. Veremos um pouco desses dois lados da linguagem em doses paliativas.



Um modificador de tipo é opcional na definição de um tipo e deve estar sempre relacionado com a declaração de alguma variável. Ele determina, em termos gerais, qual será a função dessa variável. Ela pode ser modificada? Onde ela se encontra no programa? Como ela será modificada?

Como exemplo rápido, temos abaixo uma variável que é atualizada pelo clock do processador e uma variável que não pode ser alterada após sua primeira atribuição:



Fica meio óbvio que a primeira variável possui seu valor volátil, ou seja, muda conforme o tempo passa, e não depende do próprio código (pode mudar sem sua permissão). A segunda variável também tem um uso explícito, uma vez que o valor de pi nunca será alterado (não nesse Universo).

Os especificadores de tipo possuem cada um sua peculiaridade. Os mais peculiares, que veremos nos próximos artigos, serão as enumerações e as construções bizarras de structs e unions.



Aqui não é um compêndio teórico sobre a linguagem. Vamos falar particularmente da programação Windows, mas esteja livre para dar seus pitacos com respeito a outros sistemas operacionais e suas implementações igualmente exdrúxulas =)
