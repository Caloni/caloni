---
date: "2016-12-27"
tags: [ "code", "draft",  ]
title: "Vídeo: Usando clang no Visual Studio"
---
Com o surgimento da infraestrutura LLVM, que possibilita a união entre diferentes ferramentas que suportam diferentes plataformas para o desenvolvimento de software, e o clang, um font-end para C/C++ que roda não só em UNIXes da vida, como também no Windows, como também no Visual Studio, tem sido uma vantagem para projetos que usam as novas features do C++ moderno, muitas ainda não implementadas no compilador da Microsoft, unir o útil (Visual Studio) ao agradável (C++ modernos via clang). Este vídeo tem como objetivo demonstrar como essa união é simples e fácil de ser realizada dentro do próprio Visual Studio. De quebra, vamos descobrir alguns problemas que podem ocorrer nessa união de toolsets e como corrigir.

Este é um guia bem básico, mas atende os requisitos de quem quer começar a mexer com essas duas tecnologias (além de aficionados pelo novo C++ que está em desenvolvimento, mas não abre mão de uma IDE tão poderosa quanto o Visual Studio):

 1. Criar um novo projeto clang no Visual Studio.
 2. Utilizar o projeto com um Console Win32 padrão e toolset Visual Studio.
 3. Implementar uma feature ainda não suportada pelo Visual Studio.
 4. Utilizar essa feature no Console Win32.
 5. Corrigir e entender problemas no meio do caminho.

https://www.youtube.com/embed/dMY91ojS0tw

 - CLang
 - LLVM
 - C++ compiler support
 - Fold expression
