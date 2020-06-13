---
categories: [ "code" ]
date: "2007-09-20"
tags: [ "draft", "ccpp" ]
title: "A mobilidade das variáveis no printf"
---
O printf (e derivados) tem sérios problemas por conta de sua falta de tipagem. Não vou aqui dizer que cout é a alternativa óbvia e melhorada porque não é. Mas isso é uma discussão que eu não deveria começar aqui. E não começarei. Portanto, ignorem essa linha =).

O mais comum de todos é a passagem de tipo na string de formatação diferente da variável passada:

    // SPrintf.cpp : Guess how many
    // lines we need to create 
    // a bug in C++?
    //
     
    #include "stdafx.h"
    #include <windows.h>
    #include <stdio.h>
     
    int _tmain(int argc, 
        _TCHAR* argv[])
    {
     printf("%s", 1234);
     return 0;
    } 

    Saída:
    ======
    Cabuuuuummmmmmmmmmmmmmmmmmmmmmm...

Isso costuma ser mais comum quando existem centenas de milhares de parâmetros na chamada, o que confunde o programador (e o leitor de certos blogues especializados em confundir):

    // SPrintf.cpp : Come one, now it 
    // is not so hard to find out.
    //
     
    #include "stdafx.h"
    #include <windows.h>
    #include <stdio.h>
     
    int _tmain(int argc, _TCHAR* argv[])
    {
     printf("%s%d%s%f%s%d%f%d%s%f%s%d"
        "%f%d%s%f%s%d%f%d...", ...);
     return 0;
    } 

    Saída:
    ======
    <censurado>

O segundo que me lembro que costuma dar muitos problemas é a passagem de tipo inteiro de tamanho diferente:

    // SPrintf.cpp : Come one, now it is not so hard to find out.
    //
     
    #include "stdafx.h"
    #include <windows.h>
    #include <stdio.h>
     
    int _tmain(int argc, _TCHAR* argv[])
    {
     printf("%s%d%s%f%s%d%f%d%s%f%s"
        "%d%f%d%s%f%s%d%f%d...", ...);
     return 0;
    } 

    Saída:
    ======
    0x1234(null) // quando o printf 
    // encontra um ponteiro para 
    // string nula, ele imprime (null)

É mais sutil, também costuma confundir no meio de vários parâmetros, e pode ser detectado utilizando a técnica de transformar tudo em assembly, pois com isso temos dica de tipagem ao empilhar os argumentos na saída do arquivo asm.

    ; 13   :
    ; 14   :  printf("0x%x%s", myLoooongInt, myString);
    mov esi, esp
    mov eax, DWORD PTR _myString$[ebp]
    push eax
    mov ecx, DWORD PTR _myLoooongInt$[ebp+4]
    push ecx
    ; dois pushs da mesma variável? Est
    mov edx, DWORD PTR _myLoooongInt$[ebp]
    <censurado>...
    push edx
    push OFFSET ??_C@_06LALPIMEG@0x?$CFx?$CFs?$AA@
    call DWORD PTR __imp__printf

É claro que hoje em dia existem compiladores muito espertos, que detectam na hora o que você está digitando e a cagada que isso vai dar depois de compilado. Mas, assumindo que você não tem toda essa tecnologia ao seu dispor, ou está mesmo interessado em entender como as coisas funcionam, e não apenas seguir o manual do seu ambiente de desenvolvimento preferido, essa é uma maneira interessante de analisar o que ocorre com o seu código. Agora, a pergunta que não quer calar: por que isso acontece?

Conforme o printf interpreta a string de formatação, ele vai "comendo" (no bom sentido) os argumentos passados na pilha. Se a string informa que existe um int de 32 bits, mas na verdade existe um de 64, ele vai comer apenas 32 bits da pilha, deixando os próximos 32 para o desastre iminente. Como os próximos 32 bits de nosso int64 estão zerados, faz sentido o printf imprimir (null) no lugar da string, pois este é o comportamento padrão da função quando o ponteiro é nulo. Agora, se tivéssemos um int realmente grande - vulgo "intão" - daí as coisas seriam diferentes:

    // SPrintf.cpp : Come one, now it 
    // is not so hard to find out.
    //
     
    #include "stdafx.h"
    #include <windows.h>
    #include <stdio.h>
     
    int _tmain(int argc, _TCHAR* argv[])
    {
     printf("%s%d%s%f%s%d%f%d%s%f%s%d"
         "%f%d%s%f%s%d%f%d...", ...);
     return 0;
    } 

    Saída:
    ======
    Unhandled exception at 0x78141bcd 
    (msvcr80.dll) in SPrintf.exe:
    0xC0000005: Access violation
    reading location 0x12345678.
