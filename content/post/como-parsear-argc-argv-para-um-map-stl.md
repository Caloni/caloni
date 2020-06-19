---
categories: [ "code" ]
date: "2018-01-26"
tags: [ "draft",  ]
title: "Como Parsear Argc Argv para um map STL"
---
Os clássicos argv/argc são úteis quando os parâmetros de um programa são conhecidos e geralmente obrigatórios (até a ordem pode ser obrigatória). Isso funciona muito bem para C. Porém, há a possibilidade de STLzar esses argumentos de forma simples, usando a lógica UNIX de fazer as coisas e transformando tudo em um map de string para string. E tudo isso cabe em uma função pequena que você pode copiar e levar com você em seu cinto de utilidades:


Com a função ParseCommandLine disponível assim que você adicionar este header (eu chamo de args.h) basta no início do seu main chamá-lo passando o argv e o argc recebidos:


O resultado é que a variável args irá conter um mapa entre parâmetros e valores. Se seu programa for chamado com, por exemplo, a seguinte linha de comando:


A variável args irá conter três elementos: "--name", "--surname" e "--enable-log". Nos dois primeiros ele irá entregar os valores respectivos "Agatha" e "Christie" se indexado (args["--name"], por exemplo). No terceiro elemento o valor é uma string vazia. Apenas a existência dele é o flag. Costumo usar isso para conseguir depurar por parâmetro:


De maneira geral argv/argc já estão divididos quando o programa começa. O que o ParseCommandLine faz é apenas entregar os parâmetros formatados da maneira usual para tratarmos rapidamente as opções passadas dinamicamente para o programa.
