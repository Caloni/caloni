---
date: "2007-09-20"
tags: [ "code", "ccpp" ]
title: "A mobilidade das variáveis no printf"
---
O printf (e derivados) tem sérios problemas por conta de sua falta de tipagem. Não vou aqui dizer que cout é a alternativa óbvia e melhorada porque não é. Mas isso é uma discussão que eu não deveria começar aqui. E não começarei. Portanto, ignorem essa linha =).

O erro mais comum de todos é a passagem de tipo na string de formatação diferente da variável passada:

    void f(wchar_t* arg)
    {
     printf("%s", arg);
     return 0;
    }

Isso costuma ser mais comum quando existem centenas de milhares de parâmetros na chamada, o que confunde o programador (e o leitor de certos blogues especializados em confundir). Imagine um  printf em que a string de formatação é algo como "%s%d%s%f%s%d%f%d%s%f%s%d". Agora imagine os parâmetros passados e a necessidade dos tipos baterem um a um. É, você entendeu o drama.

O segundo erro que me lembro que costuma dar muitos problemas é a passagem de tipo inteiro de tamanho diferente:

    char ch = getc();
    printf("%d", ch);

É mais sutil, também costuma confundir no meio de vários parâmetros, e pode ser detectado utilizando a técnica de transformar tudo em assembly, pois com isso temos dica de tipagem ao empilhar os argumentos na saída do arquivo asm. É claro que hoje em dia existem compiladores muito espertos, que detectam na hora o que você está digitando e a cagada que isso vai dar depois de compilado. Mas, assumindo que você não tem toda essa tecnologia ao seu dispor, ou está mesmo interessado em entender como as coisas funcionam, e não apenas seguir o manual do seu ambiente de desenvolvimento preferido, essa é uma maneira interessante de analisar o que ocorre com o seu código. Agora, a pergunta que não quer calar: por que isso acontece?

Funções com quantidade variável de argumentos como o printf devem interpretar os argumentos que ele sabe que são passados para entender quais os outros argumentos que estão na pilha. Ele interpreta a string de formatação e vai "comendo" os argumentos passados na pilha. Se a string informa que existe um int de 32 bits, mas na verdade existe um de 64, ele vai comer apenas 32 bits da pilha, deixando os próximos 32 para o desastre iminente.

Dica: se você encontrar problemas de crash ou corrompimento de pilha e houver um printf ou derivados, como funções de logs que confiam no printf, experimente desabilitar a chamada dessas funções e ver se o problema permanece. Isso pode ser feito pelo preprocessador:

    #define printf
    #define sprintf
    #define LOG

Ao definir os nomes das funções usadas para nada não haverá a chamada da função, apesar do código compilar exatamente igual, exceto a chamada. Ou seja, se houver problemas em algum printf ele sumirá. A partir daí é só ir comentando e descomentando as partes do código até encontrar.
