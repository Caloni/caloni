---
date: "2015-01-04"
tags: [ "code", "ccpp" ]
title: "Entendendo a Compilação"
---
Fiz alguns slides a pedido dos organizadores do TDC 2014, já que a palestra que ministrei com esse tema foi para ajudar meu amigo-sócio Rodrigo Strauss que não havia preparado nenhum slide a respeito.Felizmente eu já havia explicado alguns conceitos-chave para quem programa em C/C++ e precisa -- eu disse: PRECISA -- conhecer todo o passo-a-passo que leva o seu código-fonte a gerar um executável com código de máquina pronto para rodar.

Como havia explicado anteriormente, existem três processos principais e clássicos (pode haver mais, dependendo do compilador, ambiente, etc) na formação de um código de máquina a partir de arquivos-fontes escritos em C ou C++ (ou ambos, são intercambiáveis). São eles: preprocessamento, compilação e linkedição.

O preprocessamento é um trocador de textos. No máximo há macros, em que é possível passar argumentos (no formato texto). Exemplos são include, ifdef e define.

A compilação é o núcleo da linguagem. Regras de sintaxe e gramática são validadas aqui pelo compilador. Cada compilação bem-sucedida recebe uma unidade de tradução e cospe um arquivo-objeto, que ainda não é executável, mas que já passou pela validação da linguagem.

Por fim, a linkedição junta todos os arquivos-objeto, procurando ligar os nomes das funções e variáveis referenciadas um pelo outro. Os nomes externos são importantes neste passo para que o linker encontre as lacunas que precisa para consertar os saltos e assim gerar o executável final, que pode ser um programa com uma função main ou uma biblioteca dinâmica carregada por outro programa compilado seguindo esses três passos.
