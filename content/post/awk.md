---
categories: [ "code" ]
date: "2020-06-07"
tags: [ "tools" ]
title: "Awk"
---
Meu amigo sugeriu que aprender awk poderia ser útil de várias maneiras. Uma delas para organizar finanças pessoais. Dei uma lida em alguns tutoriais, sendo que o melhor custo benefício foi o Awk in 20 Minutes, de Fred Hebert (ele é o mesmo autor de um livro sobre erlang). Gostei. É sobre tratamento de texto como sed, mas em uma versão estendida e criada na época com a mesma sintaxe de C.


Por ela ser uma ferramenta antiga usa conceitos antigos, como field e record. Ela foi criada para formatar texto em formato de planilha, ou banco de dados. Um field, ou campo, é uma coluna na planilha, e um record, ou registro, é uma linha dessa planilha. Imagine que você pode usar awk para manipular e extrair dados de qualquer texto que contenha esse padrão, sendo que os detalhes como o separador de campos e registros, por padrão espaço e nova-linha, podem ser alterados no começo do programa.


Como toda linguagem usada como ferramenta do dia-a-dia existem os comandos mais úteis:


Existem tópicos mais avançados como funções, seja embutidas ou criadas pelo usuário (inclusive em C), e versões mais novas como nawk e gawk. Assim como existe o vim e existem plugins, sendo que passo muito bem sem usar plugins no meu vim. Acho difícil que um dia precise estender awk, exceto por curiosidade e para aguçar minha criatividade. E como o próprio guia GNU da ferramenta sugere, se seu programa awk atingir algumas centenas de linhas é melhor você refazer em outra linguagem. Python, por exemplo (brincadeira).
