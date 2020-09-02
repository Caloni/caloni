---
date: "2008-03-10"
tags: [ "code", "draft",  ]
title: "Sed, Grep e afins"
---
Esse artigo é resultado de eu ter me matado para conseguir encontrar a forma correta de usar o aplicativo sed para fazer uma filtragem simples nos resultados de uma listagem de arquivos.

Primeiramente, eu gostaria de expressar minha total surpresa ao não conseguir encontrar um guia simples e confiável de uso dessas ferramentas na web. Existem três teorias: ou eu não sei usar as palavras mágicas certas no Google, ou a indexação das páginas realmente importantes sobre o assunto não funcionam com o Google, ou de fato não existe documentação fácil sobre o tema.

Como esta é uma exceção em anos de "googadas", eu fico com a terceira opção.

Existem algumas ferramentas que já salvaram minha vida uma dúzia de vezes e devo admitir que são tão poderosas e flexíveis quanto difíceis de usar:

  * Grep. Use esta se quiser fazer uma busca, qualquer busca, em um arquivo, um conjunto de arquivos ou uma enxurrada de caracteres do prompt de comando.
  * Sed. Use esta se quiser processar a entrada de um arquivo, um conjunto de arquivos ou uma enxurrada de caracteres do prompt de comando.
  * Sort. Use esta se quiser ordenar qualquer coisa da entrada padrão (inclusive arquivos, conjunto de arquivos...).

Essas ferramentas são nativas do ambiente Linux, mas podem ser instaladas no Windows através do Cygwin, do Mingw ou nativamente através das ferramentas GnuWin32.

O que eu queria era processar a saída de um programa de forma que eu tivesse a lista de todas as extensões dos arquivos. Por exemplo, para a seguinte entrada:


Eu gostaria de uma saída no seguinte formato:


Basicamente é isso.

Sabendo que processamento de entrada estaria envolvido, logo pensei em utilizar o sed para a tarefa. Justiça seja feita, depois de eu perder uma hora e meia em pesquisa eu encontrei um tutorial muito bom para quem está começando a entender melhor o funcionamento do sed, e é nele que me baseei para resolver meu problema e escrever este artigo.

Obs.: sim, eu conheço os tutoriais do Aurélio, e aprendi regex através do livro dele. Contudo, seu guia do sed não é tão bom quanto parece, e apesar de lê-lo de cabo a rabo, acabei precisando de ajuda extra.

Para filtrar o path do arquivo, e ao mesmo tempo retirar seu nome, podemos usar o seguinte comando (fora outras trilhões de variantes):


Após esse processamento, a saída é um monte de extensões vindas de um monte de arquivos:


Como podemos ver e é óbvio de imaginar, muitas extensões irão se repetir. Para eliminar as repetições e ordenar a saída da saída corretamente, usamos o comando sort:


	
  * Os caracteres .*[]^$\ dão problemas se usados sem escape no sed, pois fazem parte dos comandos para procurar expressões regulares. Use-os com o caractere de escape \.

	
  * Para concatenar comandos no sed, use sempre -e "comando". A ordem de execução dos comandos é a ordem em que eles são inseridos na linha de comando, ou seja, podemos confiar que no segundo comando o primeiro já terá sido executado e assim por diante.

	
  * Para fazer o escape das barras do caminho de um arquivo temos que usar o conjunto \/ (obs.: caminhos em formato Unix). Para evitar esse uso enfadonho podemos substituir o caractere de divisão do comando s colocando-o na frente:

	
s#/path/muito/muito/muito/longo.cpp#/outropath/muito/muito/longo.cpp#

	
  * Para agrupar expressõe, use sempre "\(" e "\)". É o contrário do uso dos caracteres especiais. Coisas de Unix.

