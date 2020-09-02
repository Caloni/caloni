---
date: "2007-12-31"
tags: [ "code", "draft",  ]
title: "Gambi do dia: swap com apenas duas variáveis"
---
Este artigo é uma reedição de meu blogue antigo, guardado para ser republicado durante minhas miniférias. Esteja à vontade para sugerir outros temas obscuros sobre a linguagem C ou C++ de sua preferência. Boa leitura!

Essa interessantíssima questão veio do meu amigo Kabloc: como trocar o valor entre duas variáveis do tipo int sem utilizar uma variável intermediária? O algoritmo ordinário para um swap entre tipos inteiros é:



Uma das soluções que eu conheço é utilizar o operador de ou exclusivo, o conhecido XOR. Esse operador binário tem a não pouco bizarra habilidade de armazenar dois padrões de bits dentro de um mesmo espaço de armazenamento. Se você tiver um dos dois padrões, conseguirá o segundo. Relembremos sua tabela verdade:


Ou seja, imagine que temos o valor 1 e o valor 0. Armazenando os dois juntos com XOR obtemos 1, já que:


Mais tarde, se quisermos obter o primeiro padrão, usamos o segundo:


Para obter o segundo padrão é só utilizar o primeiro obtido:


Calcule a mesma operação com as quatro combinações possíveis e verá que podemos sempre reaver os dados partindo de um dos padrões. Como o cálculo independe do número de bits, já que operadores bit a bit operam um bit de cada vez, podemos usar a mesma técnica para juntar dois inteiros, duas strings, dois "qualquer coisa armazenada numa seqüência de zeros e uns":



Essa técnica é uma das mais básicas - se não for a mais - de criptografia simétrica. O primeiro padrão faz o papel de texto aberto, o segundo banca a senha e o terceiro será o texto encriptado. Para "desencriptar" o texto é necessária a senha (e se você souber qual o texto original, saberá a senha).

Mas, voltando ao nosso problema original, podemos trocar duas variáveis inteiras usando a técnica do XOR. Em claro:



Bom, preciso dizer que isso é uma gambi das grossas? Preciso dizer que NÃO uso isso no meu dia a dia, até porque swap é uma função já consagrada da STL? Não? Então sem Postscript dessa vez. E sem bois-cornetas =).
