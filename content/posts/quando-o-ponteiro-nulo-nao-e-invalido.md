---
categories:
- code
date: '2008-02-29'
title: Quando o ponteiro nulo não é inválido
---

Existe coisa mais prazerosa do que admitir um erro que foi cometido na mesma semana? Existe: quando você sabia que estava certo, mas resolveu usar o senso comum por falta de provas.

Pois bem. O mesmo amigo que me recomendou que escrevesse sobre o assunto do ponteiro nulo achou um livro sobre [armadilhas em C] com um exemplo que demonstra exatamente o contrário: dependendo da plataforma, ponteiros nulos são sim válidos.

Nesse caso, se tratava de um programa que iria rodar em um microprocessador, daqueles que o [DQ] costuma programar. Pois bem. Quando o dito cujo ligava era necessário chamar uma rotina que estava localizada exatamente no endereço 0. Para fazer isso, o código era o seguinte:

    ( * (void(*)()) 0 ) ();

Nada mais simples: um cast do endereço 0 (apesar de normalmente inválido, 0 pode ser convertido para endereço) para ponteiro de função que não recebe parâmetros e não retorna nada, seguido de deferência ("o apontado de") e chamada (a dupla final de parênteses). A linha acima é o equivalente às linhas abaixo:

    typedef void (*func_t)();
    func_t func = (func_t) 0;
    func();

É bem o que o autor diz depois de jogar esta expressão: "expressions like these strike terror into the hearts of C programmers". É lógico que isso não é bem verdade para as pessoas que acompanham este blogue =)

[armadilhas em C]: http://www.literateprogramming.com/ctraps.pdf
[DQ]: http://dqsoft.blospot.com