---
categories: [ "code" ]
date: "2009-07-13"
tags: [ "draft",  ]
title: "Name mangling"
---
A sobrecarga estática possui algumas desvantagens em relação ao sistema de nomes da boa e velha linguagem C: ela não foi padronizada entre compiladores. O que isso quer dizer na prática é que funções exportadas de bibliotecas dinâmicas (DLLs) vão possuir nomes diferentes dependendo do compilador utilizado (e sua versão). Isso é o que chamamos name mangling.

Em dois projetos usando Visual C++ 2008 e Borland C++ Builder 5 (última versão que funciona direito) eu fiz uma exportação da função soma em linguagem C (o fonte é um .c). Veja o resultado:

Já usando a linguagem C++ (o fonte é um .cpp) temos outro resultado totalmente diferente para nossas duas funções soma descritas no artigo anterior:

Se quiser tentar entender essas letrinhas bizarras, recomendo baixar projetos de exemplo. Se apenas entender que você não conseguirá juntar classes VC++ e Builder usando dllexport.aspx) para tudo quanto é lado, então terminamos por aqui.
