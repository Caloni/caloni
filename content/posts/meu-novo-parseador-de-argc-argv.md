---
categories:
- code
date: '2018-08-21'
tags:
- ccpp
title: Meu Novo Parseador de Argc Argv
---

Eis que me deparo com um projeto onde não posso usar STL. Ou seja, nada de map nem string. Isso quer dizer que minha função bonita e completa de parseamento de argumentos argc/argv não pode ser usado. Essa é uma má notícia. A boa notícia é que achei uma forma muito mais simples e à prova de falhas de fazer isso. Ele basicamente percorre o array argv em busca do nome do parâmetro enviado para a função. Uma vez que ele encontre ele retorna o próximo elemento. Na falta de próximo elemento ele simplesmente retorna uma string vazia que não é nulo, mas já indica que há o parâmetro na lista de argumento.

Essa função é tão simples, e tem tão poucas dependências (strcmp) que você pode usá-la em praticamente qualquer programa que use argc/argv e que use os parâmetros dos mais complexos. Ao chamar essa função se passa o argc e o argv recebido no main e o terceiro argumento é apenas o nome de um argumento válido que pode ser recebido via linha de comando. O resultado é um ponteiro (obtido no próprio argv) da próxima string ou uma string C vazia constante (não precisa de alocação) se for o último argv. E caso ele não ache o retorno é NULL. Seu uso comum é uma linha apenas, ou uma linha para cada argumento buscado. Sua complexidade é linear, mas, ei, quem está querendo performance no início do programa?

Uma última observação: dependendo do uso você pode ou não usar o retorno, e ele possui semântica booleana, pois caso o argumento não exista o retorno é NULL e por isso não cai dentro do if (pois NULL traduzido em booleano é false). Eis uma função para copiar e colar abusivamente.