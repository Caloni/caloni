---
categories: [ "code" ]
date: "2008-02-29"
tags: [ "draft",  ]
title: "Quando o ponteiro nulo não é inválido"
---

Pois bem. O mesmo amigo que me recomendou que escrevesse sobre o assunto do ponteiro nulo achou um livro sobre armadilhas em C com um exemplo que demonstra exatamente o contrário: dependendo da plataforma, ponteiros nulos são sim válidos.

Nesse caso, se tratava de um programa que iria rodar em um microprocessador, daqueles que o DQ costuma programar. Pois bem. Quando o dito cujo ligava era necessário chamar uma rotina que estava localizada exatamente no endereço 0. Para fazer isso, o código era o seguinte:


Nada mais simples: um cast do endereço 0 (apesar de normalmente inválido, 0 pode ser convertido para endereço) para ponteiro de função que não recebe parâmetros e não retorna nada, seguido de deferência ("o apontado de") e chamada (a dupla final de parênteses).

É bem o que o autor diz depois de jogar esta expressão: "expressions like these strike terror into the hearts of C programmers". É lógico que isso não é bem verdade para as pessoas que acompanham este blogue =)
