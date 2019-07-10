---
date: 2018-08-21T23:17:26-03:00
title: "Meu Novo Parseador de Argc Argv"
categories: [ "blog" ]
desc: ""
---
Eis que me deparo com um projeto onde não posso usar STL. Ou seja, nada de map nem string. Isso quer dizer que [minha função bonita e completa de parseamento de argumentos](/como-parsear-argc-argv-para-um-map-stl) argc/argv não pode ser usado. Essa é uma má notícia. A boa notícia é que achei uma forma muito mais simples e à prova de falhas de fazer isso. Quer ver?

```c++
/** Interpreta argumentos da linha de comando (versão raiz).

@author Wanderley Caloni <wanderley.caloni@bitforge.com.br>
@date 2018-08
*/
const char* GetArg(int argc, char* argv[], const char* arg)
{
    for (int i = 1; i < argc; ++i)
    {
        if( strcmp(argv[i], arg) == 0 )
        {
            if( i < argc - 1 )
                return argv[i+1];
            else
                return "";
        }
    }
    return NULL;
}
```

![](https://i.imgur.com/asi80x3.png)

Essa função é tão simples, e tem tão poucas dependências (strcmp) que você pode usá-la em praticamente qualquer programa que use argc/argv e que use os parâmetros dos mais complexos:

```
MeuPrograma.exe --debug --file c:\path\arquivo.ext --readonly 1
```

Ao chamar GetArg se passa o argc/argv recebido no main e o terceiro argumento é apenas o nome de um argumento válido que pode ser recebido via linha de comando. O resultado é um ponteiro (obtido no próprio argv) da próxima string ou uma string C vazia constante (não precisa de alocação) se for o último argv. E caso ele não ache o retorno é NULL. Seu uso comum é uma linha apenas:

```c++
if ( GetArg(argc, argv, "--debug") )
{
    printf("Waiting for debugger...\n");
    while (!IsDebuggerPresent())
        Sleep(1000);
}
```

```c++
if ( const char* configFile = GetArg(argc, argv, "--configfile") )
{
    strcpy(g_configFile, configFile, _countof(g_configFile));
}
```

Dependendo do uso você pode ou não usar o retorno, e ele possui semântica booleana, pois caso o argumento não exista o retorno é NULL e por isso não cai dentro do if (pois NULL traduzido em booleano é false).

Eis uma função para copiar e colar abusivamente.
