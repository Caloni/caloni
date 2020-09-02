---
date: "2016-01-12"
tags: [ "code", "draft",  ]
title: "Classe, objeto, contexto, método, polimorfismo"
---
No post anterior implementamos "métodos" em C usando ponteiros de função dentro de structs que eram passadas como parâmetro. Tudo isso embutido por um compilador que gera o que chamamos de instância de uma classe, ou objeto, em C++. Isso é possível graças ao contexto que é passado para uma função (que no caso de C++ é o operador implícito this, que sempre existe dentro de um método não-estático).


Para objetos não-polimórficos, o C++ não precisa mudar essa tabela de funções que os objetos de uma classe contém. No entanto, quando há pelo menos um método virtual, surge a necessidade de se criar a famigerada vtable, ou seja, justamente uma tabela de ponteiros de função, que dependem da classe instanciada (base ou algumas das derivadas). Se uma classe derivada sobrescreve um método de alguma classe base, é o endereço desse método que irá existir na vtable. Já vimos isso há muito tempo atrás escovando os bits da vtable direto no assembly e na pilha.




Como você deve imaginar, é possível também fazer isso em C. Basta mudar os endereços das variáveis do tipo ponteiro de função que estão na struct usada como contexto. Para ficar o mais próximo possível do "modo C++" de fazer polimorfirmo, podemos escrever hardcoded a tal vtable para os diferentes tipos de "classe":




A versão C ainda tem a vantagem de não precisar de uma vtable const (embora seja adequado em situações normais de temperatura e pressão). Os "métodos" poderiam mudar caso algum estado mudasse, alguma exceção fosse disparada, mantendo o mesmo contexto, mas um comportamento (vtable) diferente. Quem utiliza muito essa estratégia é o kernel do Windows, que mexe com estruturas que contém não apenas listas ligadas genéricas, mas funções de callback que não apenas o código da Microsoft precisa chamar, mas os próprios drivers de terceiros que se preocupam com bom comportamento e guidelines que tornam o SO rodando perfeitamente.

O importante deste artigo é demonstrar como conceitos aparentemente complicados ou escondidos de uma linguagem como C++ podem ser compreendidos completamente utilizando apenas linguagem de alto nível no bom e velho C. Essa estratégia de descer camadas de abstração, como verá, funciona para linguagens de mais alto nível, como C# ou Java, pois ambas são implementadas em linguagens como C++. No fundo, engenharia de software é um universo multi-camadas transitando pela última camada que conhecemos -- a física. Pelo menos a última camada que ainda conhecemos.
