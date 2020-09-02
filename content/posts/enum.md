---
date: "2010-05-31"
tags: [ "code", "draft",  ]
title: "Enum"
---
Padrão C (ISO/IEC 9899:1990)


Uma enumeração faz duas coisas: define um novo tipo, parecido com um inteiro, e cria uma lista de constantes com nomes significativos. A definição técnica do tipo de um enum é mais complicada, mas basicamente ele é um novo int.

Como funciona: definimos uma lista com cada elemento tendo um valor inteiro, geralmente único. Todos os nomes usados na lista passam a fazer parte do espaço de nomes atual e funcionam como constantes com o seu valor definido no início.


Obs.: Os elementos que não possuem valor definido são definidos automaticamente como o valor do elemento anterior acrescidos de um. Se for o primeiro elemento, seu valor padrão é zero.


Detalhe bizarro: você sabia que, apesar da vírgula ser usada para separar valores de enumeração, ela pode também terminar uma listagem? Por algum motivo exdrúxulo (se alguém quiser explicar), um valor de enumeração foi definido de tal forma que sempre poderá existir uma vírgula terminando ele:


Geralmente usamos enumerações para definir valores únicos (tag) em um argumento de função, ou, mais moderno, como substituto daqueles antigos defines em C para mapas de bits. Nesse último caso não usamos o tipo da enumeração, pois ele pode conter apenas um valor único definido, e não um conjunto deles:


Note que usamos uma enumeração nesse último caso para termos um nome significativo para uma flag, além desse nome fazer de fato parte dos nomes do programa, e não um define que, para o compilador, não existe.

Como os tipos da enumeração passam a pertencer ao namespace atual, eles podem se misturar facilmente com todos os nomes daquele namespace. Dessa forma, é útil e bem organizado definir um prefixo para os nomes, que pode ser formado pelas iniciais do nome da enumeração, como no exemplo acima (fom = FileOpenMode).

O surgimento do enum veio como evolução de uma prática já consagrada pelo uso na linguagem C, que eram as listas de valores constantes criados através de defines com algum prefixo em comum (FILESHARE, SWSHOW, etc). Portanto, sempre que se encontrar em uma situação para criar esse tipo de lista, a enumeração é o caminho atualmente ideal.


Perguntado por um leitor sobre qual a diferença prática do último exemplo, onde temos praticamente o mesmo resultado entre usar defines e enumerações, imaginei que a mesma dúvida pode ter surgido para várias pessoas, porque é uma boa dúvida. Dá a entender que o autor deste artigo está se atentando a preciosismos da linguagem (e está mesmo!), mas à vezes as aparências enganam.

Para ilustrar melhor fiz um mais elaborado. Aqui, estamos lendo pedaços de dados que tiveram que ser alinhados com alguma "gordura".


Aviso para os programadores mais calejados, eu omiti propositalmente os parênteses obrigatórios para qualquer define que tenha cálculos matemáticos, para ilustrar que muitas vezes o que vemos antes não é o que aparece depois.
