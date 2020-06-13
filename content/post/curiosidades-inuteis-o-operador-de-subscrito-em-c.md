---
categories: [ "code" ]
date: "2007-12-27"
tags: [ "draft",  ]
title: "Curiosidades inúteis: o operador de subscrito em C++"
---
Este artigo é uma reedição de meu blogue antigo, guardado para ser republicado durante minhas miniférias. Esteja à vontade para sugerir outros temas obscuros sobre a linguagem C ou C++ de sua preferência. Boa leitura!

Em C e C++ as regras de sintaxe são extremamente flexíveis. Essa liberdade toda se manteve no decorrer dos tempos porque se trata de uma das idéias fundamentais da linguagem C, motivo de sua criação. Me lembro certa vez que, bitolado em C Standard 89, usei uma sintaxe não lá muito usual para acessar um elemento de um array. Foi apenas um experimento de estudante, coisa que nunca vi em código algum e queria comprovar.

As regras de acesso a elementos de um array (subscrito) são definidas não em termos do array, mas em termos de um ponteiro e de um índice. "Me dê um ponteiro para T e um inteiro e te retorno um lvalue do tipo T". Essa é a idéia geral. A mesma idéia, com pequenas alterações, se manteve em C++. Eis parte do parágrafo que fala sobre isso:

> A postfix expression followed by an expression in square brackets is a postfix expression. One of the expressions shall have the type "pointer to T" and the other shall have enumeration or integral type. The result is an lvalue of type "T". (...) The expression E1 [ E2 ] is identical (by definition) to *( (E1) + (E2) ). - C++: International Standard ISO/IEC 14882 First Edition 1998-09-01

Isso traduzido em miúdos quer dizer que com duas expressões formando a construção E1 [ E2 ], sendo uma delas do tipo ponteiro para um tipo e a outra do tipo integral, o resultado é equivalente a *( (E1) + (E2) ). Como no código abaixo:

    #include <iostream>
    
    int main()
    {
    	char ditado[] = "Diga-me com que programas e eu te direi quem és.";
    	int indice = 8;
    
    	std::cout << "E a linguagem é: " << ditado[indice] << std::endl;
    } 
    

A teoria comprovada na prática: temos duas expressões no formato E1 [ E2 ] sendo uma do tipo ponteiro para char e a outra do tipo int, exatamente como a regra define. O detalhe obscuro que permaneceu durante a evolução dessas duas linguagens é que a regra de acesso a elementos não define a ordem das expressões. Assim sendo, me aproveito dessa flexibilidade e inverto os elementos do subscrito:

    
       std::cout << <span class="string">"E a linguagem é: "</span> << indice[ditado] << std::endl;

Isso também compila e tem o mesmo resultado, pois também é equivalente a *( (E1) + (E2) ). No final dá na mesma. E do jeito que está a inversão nem dá tanto susto assim, pois estamos lidando com duas variáveis. A coisa começa a ficar mais IOCCC se colocarmos em vez de uma delas uma constante:

    
       std::cout << <span class="string">"E a linguagem é: "</span> << 8[ditado] << std::endl;

Isso ainda é válido, certo? Os tipos das expressões estão de acordo com a regra. Fica simples de visualizar se sempre pensarmos no "equivalente universal" *( (E1) + (E2) ). Até coisas bizarras como essa acabam ficando simples:

    
       std::cout << 5[<span class="string">"Isso Compila?"</span>] << std::endl;

Nota do autor: esse tipo de "recurso obscuro" dificilmente passará por uma revisão de código, e com razão, dado que não é um método útil e muito menos conhecido. Sábio é saber evitar. Não acredito, porém, que o conhecimento de certos detalhes da linguagem em que se programa sejam completamente inúteis. Conhecimento nunca é demais, pois quanto mais se conhece maior é o número de ferramentas conceituais que se dispõe para resolver um certo problema. Em muitas vezes o "conhecimento inútil" de hoje se torna um guia sábio quando se precisa de bons conceitos sobre a coisa toda. No entanto, que não venha um boi-corneta me dizer que esse código fere as boas práticas de programação. Tenho dito.
