---
categories:
- code
date: '2010-08-30'
tags:
- draft
title: Como ofuscar strings
---

Já fiz ofuscamento e embaralhamento de dados acho que umas três ou quatro vezes. Dessa vez, parti para o batidíssimo esquema de fazer o pré-processamento de um header com defines que irão virar estruturas reaproveitadas por uma função padrão que desofusca e ofusca aquela tripa de bytes em algo legível: a string original.

Vamos ver um exemplo:

    
    #define MY_STR "Essa é minha string do coração"

Conseguimos capturar os três elementos desse define (um descartável) por um simples scanf:

    
    scanf("#define %s \"%[^\"]", def, str);

A função scanf retorna o número de argumentos capturados. Então se a coisa funcionou é só comparar com 2.

Depois de capturado, imprimimos na saída (o arquivo pós-processado) uma estrutura que irá conter nosso amigo embaralhado:

    
    printf("struct ST_%s { byte key; size_t bufferSize; byte buffer[%d] }\n"
    	" %s = { %d, %d, { ";
    
    for( ; ; ) printf(Cada byte ofuscado);
    
    printtf(" } };\n");

Pronto. Agora o usuário da string precisa abri-la usando uma macro esperta que irá chamar uma função esperta para desofuscar a string e entregar o ponteiro de buffer devidamente "casteado":

    
    #include "header-pos-processado.h"
    
    #define ABRE_VAR(var, type) (type) OpenVar( (GENERIC_STRUCT) var)
    
    int main()
    {
    	char* str = ABRE_VAR(MY_STR, char*);
    }

Uma vez que a abertura se faz "inplace", ou seja, a memória da própria variável da estrutura original é alterada, pode-se fechar a variável novamente, se quiser, após o uso.

    
    FECHA_VAR(MY_STR);

A GENERIC_STRUCT do exemplo se trata apenas de um esqueleto para que todas as estruturas das 500 strings ofuscadas sejam entendidas a partir de um modelo. Sim, essa é uma solução usando linguagem C apenas, então não posso me dar ao luxo daqueles templates frescurentos.

    
    struct GENERIC_STRUCT
    {
    	byte key;
    	size_t bufferSize;
    	byte buffer[1];
    };

Como a string é ofuscada? Sei lá, use um XOR:

    
    for( size_t i = 0; i < bufferSize; ++i )
    	buffer[i] ^= key;

Dessa forma abrir ou fechar a variável pode ser feito usando a mesma função.

Alguém aí gostaria de uma explicação didática sobre o operador XOR?

<blockquote>_PS: Acho que, além das minhas palestras, meus artigos estão também parecendo um brainstorm. _</blockquote>