---
categories: [ "code" ]
date: "2018-07-15"
link: "https://github.com/Caloni/sep_to_kindle"
tags: [ "draft", "tools", "philosophy" ]
title: "Stanford Encyclopedia of Philosophy Para Kindle"
---
A enciclopédia mais completa e de maior respeito da internet não é um enciclopédia geral, mas uma de filosofia. Está hospedada na Universidade de Stanford e possui revisão por pares e toda a autoridade de ser escrita por especialistas nos verbetes em questão. O único problema (até agora) era não ser possível baixá-la para degustar no Kindle. Até agora.

Para realizar esta operação será necessário usar as seguintes ferramentas:

 - wget
 - sed
 - sort
 - Calibre

O projeto de conversão (disponível aqui) foi feito pensando em usuários do Windows, mas pode ser adaptado facilmente para qualquer ambiente. Se trata de um conjunto de arquivos batch (script) que realiza vários comandos, a saber:

Este batch baixa todo o conteúdo do site da Stanford em um único diretório. O processo pode demorar mais ou menos, dependendo da sua banda, mas aqui em casa (50MB) demorou cerca de meia-hora pra mais.


Este batch chama dois outros batch, call calibreremovehead.bat e call calibreremovebottom.bat, que limpam das entradas os cabeçalhos e finais em comum que são repetitivos e desnecessários para gerar um ebook, como links úteis de navegação. Como as entradas do site já possuem marcadores, isso facilitou o trabalho.



Esta batch gera os índices das entradas baseado em seus títulos, e os nomes dos arquivos serão usados para links no TOC do Calibre.


Algumas entradas possuem o marcador em, que deve ser retirado antes de ordenar os títulos.


Se não ordenarmos por título o único índice de nosso livro será inútil.


Ao final do processo com o wget percebi que algumas entradas foram baixadas mais de uma vez. Várias delas. Por isso eliminei as duplicatas usando um programa Windows chamado doublekiller.exe, mas basta você usar qualquer ferramenta que encontra os .html da mesma pasta que possuem o mesmo hash e eliminar as duplicadas. Isso deve ser feito nesse passo antes de:

Essa parte do processo precisa converter as entradas no formato Título Link para entradas HTML com a tag a, no formato que o Calibre espera:


Por fim, antes de usar o Calibre é necessário juntar os arquivos de template em um arquivo final de TOC, o calibre.html. Ao final desse processo passaremos ao Calibre em si.


Para realizar este passo basta arrastar ou abrir o arquivo html central que foi criado, e a partir dele iniciar a conversão. Note que após arrastar já será criado um zip com todos os HTMLs relacionados.

Após abrir pelo Calibre ele insere na biblioteca e é só converter para MOBI (Kindle) ou EPUB (outros leitores) ou qualquer outro formato desejado. A nota final aqui é que como se trata de um arquivo gigantesco (50 MB em HTML zipado, 80 MB em MOBI) é melhor baixar a versão 64 bits do Calibre e ter muita memória RAM. Voilà!

E por hoje é só. Se tudo der certo você poderá copiar e colar dentro do seu leitor todas as entradas de uma enciclopédia indispensável para quem está estudando filosofia. Enjoy.
