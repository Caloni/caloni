---
date: 2018-07-15T21:53:55-03:00
title: "Stanford Encyclopedia of Philosophy Para Kindle"
categories: [ "reading" ]
---
A enciclopédia mais completa e de maior respeito da internet não é um enciclopédia geral, mas uma de filosofia. Está hospedada na Universidade de Stanford e possui revisão por pares e toda a autoridade de ser escrita por especialistas nos verbetes em questão. O único problema (até agora) era não ser possível baixá-la para degustar no Kindle. Até agora.

Para realizar esta operação será necessário usar as seguintes ferramentas:

 - wget
 - sed
 - sort
 - Calibre

O projeto de conversão (disponível [aqui](https://github.com/Caloni/sep_to_kindle)) foi feito pensando em usuários do Windows, mas pode ser adaptado facilmente para qualquer ambiente. Se trata de um conjunto de arquivos batch (script) que realiza vários comandos, a saber:

### calibre_download.bat (baixa conteúdo do site da Stanford)

Este batch baixa todo o conteúdo do site da Stanford em um único diretório. O processo pode demorar mais ou menos, dependendo da sua banda, mas aqui em casa (50MB) demorou cerca de meia-hora pra mais.

```
wget --recursive --domains plato.stanford.edu --page-requisites --no-parent --convert-links --restrict-file-names=windows --no-directories --html-extension https://plato.stanford.edu/contents.html 
```

### calibre_clean_files.bat (limpa início e fim das entradas)

Este batch chama dois outros batch, call calibre_remove_head.bat e call calibre_remove_bottom.bat, que limpam das entradas os cabeçalhos e finais em comum que são repetitivos e desnecessários para gerar um ebook, como links úteis de navegação. Como as entradas do site já possuem marcadores, isso facilitou o trabalho.

#### calibre_remove_head.bat

```
for %%i in (index.html.*.html) do sed -n -i "/BEGIN ARTICLE HTML/,$p" %%i
```

#### calibre_remove_bottom.bat

```
for %%i in (index.html.*.html) do sed -i "/END ARTICLE HTML/,$d" %%i
```

### calibre_entries.bat (gera índice com as entradas)

Esta batch gera os índices das entradas baseado em seus títulos, e os nomes dos arquivos serão usados para links no TOC do Calibre.

```
if exist calibre_entries.txt del calibre_entries.txt
for %%i in (index.html.*.html) do calibre_title.bat %%i >> calibre_entries.txt
sed -i -e "s/<em>//" -e "s/<\/em>//" calibre_entries.txt
```

### calibre_entries_clean.bat (limpa formatação das entradas)

Algumas entradas possuem o marcador **em**, que deve ser retirado antes de ordenar os títulos.

```
sed -i -e "s/<em>//" -e "s/<\/em>//" calibre_entries.txt
```

### calibre_entries_sort.bat (ordena entradas por título)

Se não ordenarmos por título o único índice de nosso livro será inútil.

```
sort calibre_entries.txt > calibre_entries_sorted.txt
```

### Apagar duplicatas

Ao final do processo com o wget percebi que algumas entradas foram baixadas mais de uma vez. Várias delas. Por isso eliminei as duplicatas usando um programa Windows chamado [doublekiller.exe](https://www.bigbangenterprises.de/en/doublekiller/), mas basta você usar qualquer ferramenta que encontra os .html da mesma pasta que possuem o mesmo hash e eliminar as duplicadas. Isso deve ser feito nesse passo antes de:

### calibre_entries_to_template.bat (converte entradas da enciclopédia para o template do Calibre)

Essa parte do processo precisa converter as entradas no formato Título Link para entradas HTML com a tag **a**, no formato que o Calibre espera:

```
sed -e "s/\(^.*\) \(index.*$\)/        <a href=\"\2\">\1<\/a><br\/>/" calibre_entries_sorted.txt > calibre_template_entries.html
```

### calibre_merge_templates.bat (junta início, meio e fim do template do Calibre)

Por fim, antes de usar o Calibre é necessário juntar os arquivos de template em um arquivo final de TOC, o calibre.html. Ao final desse processo passaremos ao Calibre em si.

```
copy /Y calibre_template_begin.html+calibre_template_entries.html+calibre_template_end.html calibre.html
```

### Usar Calibre para abrir calibre.html

Para realizar este passo basta arrastar ou abrir o arquivo html central que foi criado, e a partir dele iniciar a conversão. Note que após arrastar já será criado um zip com todos os HTMLs relacionados.

### Converter HTML zipado em outros formatos

Após abrir pelo Calibre ele insere na biblioteca e é só converter para MOBI (Kindle) ou EPUB (outros leitores) ou qualquer outro formato desejado. A nota final aqui é que como se trata de um arquivo gigantesco (50 MB em HTML zipado, 80 MB em MOBI) é melhor baixar a versão 64 bits do Calibre e ter muita memória RAM. Voilà!

E por hoje é só. Se tudo der certo você poderá copiar e colar dentro do seu leitor todas as entradas de uma enciclopédia indispensável para quem está estudando filosofia. Enjoy.
