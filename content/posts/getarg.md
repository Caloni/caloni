---
categories:
- code
date: 2018-08-30 14:41:33-03:00
tags:
title: 'GetArg: the ultimate badass argv/argc parser'
---

Sim, eu acho que já resumi o suficiente meu parseador de argv/argc no meu [último artigo sobre o tema](/meu-novo-parseador-de-argc-argv). Sim, eu também acho que a [versão com STL](/como-parsear-argc-argv-para-um-map-stl) bonitinha (mas ordinária). A questão agora não são as dependências, mas o uso no dia-a-dia: precisa ter o argc nessa equação?

A resposta é não. Pois, como sabemos, o padrão C/C++ nos informa que o argv é um array de ponteiros de strings C que termina em nulo. Sabemos que ele termina, então o argc é apenas um helper para sabermos de antemão onde ele termina. Mas quando precisamos, por exemplo, passar o argv/argc para uma thread Windows, que aceita apenas um argumento mágico, talvez minha versão antiga não seja tão eficaz, pois isso vai exibir que eu aloque memória de um struct que contenha ambas as variáveis, etc. Por que não simplesmente utilizar apenas o argv?

![](https://i.imgur.com/asi80x3.png)

```
#include <string.h>
#include <stdio.h>

/** Interpreta argumentos da linha de comando (versão raiz truzona).

@author Wanderley Caloni <wanderley.caloni@bitforge.com.br>
@date 2018-08
*/
const char* GetArg(char* argv[], const char* arg)
{
    while( *++argv )
    {
        if( strcmp(*argv, arg) == 0 )
        {
            if( *(argv+1) )
                return *(argv+1);
            else
                return "";
        }
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    printf("Type enter to start...");
    getchar();

    if( GetArg(argv, "--debug") )
        printf("Waiting for debugger...\n");
    if( const char* command = GetArg(argv, "--command") )
        printf("Command %s received\n", command);
}
```

Nessa versão elminamos a necessidade do argc e de brinde ganhamos a possibilidade de usar um único ponteiro como start de um parseamento de argumentos.
