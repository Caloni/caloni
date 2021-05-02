---
date: "2020-06-07"
categories: [ "code" ]
title: "Awk"
---
Meu amigo sugeriu que aprender awk poderia ser útil de várias maneiras. Uma delas para organizar finanças pessoais. Dei uma lida em alguns tutoriais, sendo que o melhor custo benefício foi o [Awk in 20 Minutes], de Fred Hebert (ele é o mesmo autor de um livro sobre erlang). Gostei. É sobre tratamento de texto como sed, mas em uma versão estendida e criada na época com a mesma sintaxe de C.

    # comment
    Pattern1 { ACTIONS; }
    
    # comment
    Pattern2 { ACTIONS; }
    
    # comment
    Pattern3 { ACTIONS; }
    
    # comment
    Pattern4 { ACTIONS; }

Por ela ser uma ferramenta antiga usa conceitos antigos, como field e record. Ela foi criada para formatar texto em formato de planilha, ou banco de dados. Um field, ou campo, é uma coluna na planilha, e um record, ou registro, é uma linha dessa planilha. Imagine que você pode usar awk para manipular e extrair dados de qualquer texto que contenha esse padrão, sendo que os detalhes como o separador de campos e registros, por padrão espaço e nova-linha, podem ser alterados no começo do programa.

    # can be modified by the user
    BEGIN {

      # Field
      # Separator
      FS = ",";

      # Record
      # Separator (lines)
      RS = "\n";

      # Output
      # Field
      # Separator
      OFS = " ";

      # Output
      # Record
      # Separator
      # (aka lines)
      ORS = "\n";
    }
    # can't be modified by the user
    {
      # Number of Fields
      # in the current Record
      NF

      # Number of Records
      # seen so far
      NR

      # Script Arguments
      ARGV / ARGC
    }

Como toda linguagem usada como ferramenta do dia-a-dia existem os comandos mais úteis:

    # prints $0 
    # (just print will do it)
    { print $0; }  

    # ends the program
    { exit; }      

    # skips to the 
    # next line of input
    { next; }      

    # variable assignment
    { a=$1; b=$0 } 

    # array assignment
    { c[$1] = $2 } 

Existem tópicos mais avançados como funções, seja embutidas ou criadas pelo usuário (inclusive em C), e versões mais novas como nawk e gawk. Assim como existe o vim e existem plugins, sendo que passo muito bem sem usar plugins no meu vim. Acho difícil que um dia precise estender awk, exceto por curiosidade e para aguçar minha criatividade. E como o próprio guia GNU da ferramenta sugere, se seu programa awk atingir algumas centenas de linhas é melhor você refazer em outra linguagem. Python, por exemplo (brincadeira).

    { if (BOOLEAN) { ACTION }
      else if (BOOLEAN) { ACTION }
      else { ACTION }
    }
    { for (i=1; i<x; i++) { ACTION } }
    { for (item in c) { ACTION } }

[Awk in 20 Minutes]: https://ferd.ca/awk-in-20-minutes.html
