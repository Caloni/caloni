---
date: 2018-01-26T20:53:30-02:00
title: "Como Parsear Argc Argv para um map STL"
categories: [ "code" ]
---
Os clássicos argv/argc são úteis quando os parâmetros de um programa são conhecidos e geralmente obrigatórios (até a ordem pode ser obrigatória). Isso funciona muito bem para C. Porém, há a possibilidade de STLzar esses argumentos de forma simples, usando a lógica \*nix de fazer as coisas e transformando tudo em um map de string para string. E tudo isso cabe em uma função pequena que você pode copiar e levar com você em seu cinto de utilidades:

```
/** Interpreta argumentos da linha de comando.

@author Wanderley Caloni <caloni@intelitrader.com.br>
@date 2015-06
@version 1.0.0
*/
#pragma once
#include <map>
#include <string>

typedef std::map<std::string, std::string> Args;

inline void ParseCommandLine(int argc, char* argv[], Args& args)
{
	for (int i = 1; i < argc; ++i)
	{
		std::string cmd = argv[i];
		std::string arg;
		if (i < argc - 1 && argv[i + 1][0] != '-')
		{
			arg = argv[i + 1];
			++i;
		}
		args[cmd] = arg;
	}
}
```

Com a função ParseCommandLine disponível assim que você adicionar este header (eu chamo de args.h) basta no início do seu main chamá-lo passando o argv e o argc recebidos:

```
int main(int argc, char* argv[])
{
	Args args;
	ParseCommandLine(argc, argv, args);
    // ...
```

O resultado é que a variável args irá conter um mapa entre parâmetros e valores. Se seu programa for chamado com, por exemplo, a seguinte linha de comando:

```
>program.exe --name Agatha --surname Christie --enable-log
```

A variável args irá conter três elementos: "--name", "--surname" e "--enable-log". Nos dois primeiros ele irá entregar os valores respectivos "Agatha" e "Christie" se indexado (args["--name"], por exemplo). No terceiro elemento o valor é uma string vazia. Apenas a existência dele é o flag. Costumo usar isso para conseguir depurar por parâmetro:

```
if( args.find("--debug") != args.end() )
{
    while( ! IsDebuggerPresent() )
        Sleep(1000);
}
```

De maneira geral argv/argc já estão divididos quando o programa começa. O que o ParseCommandLine faz é apenas entregar os parâmetros formatados da maneira usual para tratarmos rapidamente as opções passadas dinamicamente para o programa.
