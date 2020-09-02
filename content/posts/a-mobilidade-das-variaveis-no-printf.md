---
date: "2007-09-20"
tags: [ "code", "draft", "ccpp" ]
title: "A mobilidade das variáveis no printf"
---
O printf (e derivados) tem sérios problemas por conta de sua falta de tipagem. Não vou aqui dizer que cout é a alternativa óbvia e melhorada porque não é. Mas isso é uma discussão que eu não deveria começar aqui. E não começarei. Portanto, ignorem essa linha =).

O mais comum de todos é a passagem de tipo na string de formatação diferente da variável passada:



Isso costuma ser mais comum quando existem centenas de milhares de parâmetros na chamada, o que confunde o programador (e o leitor de certos blogues especializados em confundir):



O segundo que me lembro que costuma dar muitos problemas é a passagem de tipo inteiro de tamanho diferente:



É mais sutil, também costuma confundir no meio de vários parâmetros, e pode ser detectado utilizando a técnica de transformar tudo em assembly, pois com isso temos dica de tipagem ao empilhar os argumentos na saída do arquivo asm.


É claro que hoje em dia existem compiladores muito espertos, que detectam na hora o que você está digitando e a cagada que isso vai dar depois de compilado. Mas, assumindo que você não tem toda essa tecnologia ao seu dispor, ou está mesmo interessado em entender como as coisas funcionam, e não apenas seguir o manual do seu ambiente de desenvolvimento preferido, essa é uma maneira interessante de analisar o que ocorre com o seu código. Agora, a pergunta que não quer calar: por que isso acontece?

Conforme o printf interpreta a string de formatação, ele vai "comendo" (no bom sentido) os argumentos passados na pilha. Se a string informa que existe um int de 32 bits, mas na verdade existe um de 64, ele vai comer apenas 32 bits da pilha, deixando os próximos 32 para o desastre iminente. Como os próximos 32 bits de nosso int64 estão zerados, faz sentido o printf imprimir (null) no lugar da string, pois este é o comportamento padrão da função quando o ponteiro é nulo. Agora, se tivéssemos um int realmente grande - vulgo "intão" - daí as coisas seriam diferentes:


