---
categories: [ "code" ]
date: "2014-04-08"
tags: [ "draft",  ]
title: "Lambda: o Retorno!"
---

Na última vez que foi abordado o tema "lambda na ferida" falamos brevemente sobre como C++ agora permite criar funções dentro de funções. Hoje vamos apenas falar que aquela construção bizarra que criamos fica ainda mais bizarra se precisarmos retornar alguma coisa dessa função ou usá-la mais de uma vez.

O padrão do lambda é supor que sua função embutida e enlatada não precisa retornar nada, o que torna a sintaxe mais simples: é um void AlgumaCoisa(argumentos). No entanto, para algoritmos como o findif isso não funciona, então é necessário retornar algo. E, no caso de findif, chamá-lo mais de uma vez pode ser feito facilmente criando uma variável lambda:


O tipo de retorno que colocamos através de uma flechinha é obrigatória? De fato, não. Se eu omiti-la vai funcionar do mesmo jeito porque o único ponto de saída da minha função retorna um bool.

Esses compiladores estão ficando cada vez mais espertos.
