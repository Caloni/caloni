---
date: "2008-06-30"
tags: [ "code", "draft",  ]
title: "Reflexão em C++"
---
O termo e conceito de "reflection)" (reflexão), muito usado em linguagens modernas, é a capacidade de um programa de observar e até de alterar sua própria estrutura. Bom, isso você pode ler na Wikipédia. O interessante é o que podemos usar desse conceito na linguagem C++.

Infelizmente não muito.

O sistema de RTTI (Run Time Type Identification), a identificação de tipos em tempo de execução, seria o começo do reflection em C++. Foi um começo que não teve meio nem fim, mas existe na linguagem. Dessa forma podemos tirar algum proveito disso.

Um leitor pediu para que eu falasse um pouco sobre essas coisas, especificamente como se faz para obter o nome da classe de onde estamos executando um determinado método. Para esse tipo de construção podemos usar o operado typeid, que retorna informações básicas sobre um tipo de acordo com um tipo, instância ou expressão:



Dessa forma, podemos nos aproveitar do fato que todo método não-estático possui a variável implícita this, do tipo "ponteiro constante para T", onde T é o tipo da classe que contém o método sendo chamado.



class MyClass::MyMethod

Com classes não-polimórficas a coisa parece não ter muita utilidade. No entanto, essa mesma técnica pode ser aplicada em classes derivadas, uma vez que o operador typeid pode trabalhar em tempo de execução:




Apenas se lembre de ter de fato uma classe polimórfica (eu consegui isso tornando MyMethod uma função virtual). Do contrário você pode ter problemas.
