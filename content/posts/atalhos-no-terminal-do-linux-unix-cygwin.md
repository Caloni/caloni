---
date: "2017-02-27"
tags: [ "code", "draft", "tools" ]
title: "Atalhos no terminal do Linux/Unix"
---
Há pouca coisa que você pode fazer para manipular a linha de comando que está digitando em um terminal do Windows. Isso faz sentido. O terminal da Microsoft é apenas um resquício do MS-DOS, que foi herdado pelas inúmeras versões do Windows para que desenvolvedores e suporte pudessem executar alguns comandos não disponíveis pelo clique de um mouse. Já no Unix a história é inversa. Durante tantas décadas sendo usado, o sistema Unix, hoje, em sua mais nova reencarnação, Linux, foi acumulando diferentes teclas de atalho para conseguirmos refazer, desfazer e fazer melhor a montagem dos comandos digitados na linha de comando. Um sistema bash padrão já deve ter implementado o mínimo que você precisa para sobreviver na linha de comando. Aparentemente esse é um conhecimento tão bem divulgado pela comunidade que ninguém se dá ao trabalho de escrever um artigo sobre isso. Eu fiz algumas pesquisas uns tempos atrás e cheguei na seguinte lista, que tem muito mais do que eu preciso, e que seria bom aprender, nem que fosse aos poucos.

 - __Ctrl + r__ - navigate previous commands
 - __Ctrl + a__ - go to the start of the command line
 - __Ctrl + e__ - go to the end of the command line
 - __Ctrl + k__ - delete from cursor to the end of the command line
 - __Ctrl + u__ - delete from cursor to the start of the command line
 - __Ctrl + w__ - delete from cursor to start of word (i.e. delete backwards one word)
 - __Ctrl + y__ - paste word or text that was cut using one of the deletion shortcuts (such as the one above) after the cursor
 - __Ctrl + xx__ - move between start of command line and current cursor position (and back again)
 - __Alt + b__ - move backward one word (or go to start of word the cursor is currently on)
 - __Alt + f__ - move forward one word (or go to end of word the cursor is currently on)
 - __Alt + d__ - delete to end of word starting at cursor (whole word if cursor is at the beginning of word)
 - __Alt + c__ - capitalize to end of word starting at cursor (whole word if cursor is at the beginning of word)
 - __Alt + u__ - make uppercase from cursor to end of word
 - __Alt + l__ - make lowercase from cursor to end of word
 - __Alt + t__ - swap current word with previous
 - __Ctrl + f__ - move forward one character
 - __Ctrl + b__ - move backward one character
 - __Ctrl + d__ - delete character under the cursor
 - __Ctrl + h__ - delete character before the cursor
 - __Ctrl + t__ - swap character under cursor with the previous one
 - __Ctrl + l__ - clean the screen (history back)
 - __Ctrl + z__ - put in background (fg restores it)
 - __Ctrl + c__ - cancel current command
 - __Ctrl + d__ - exit the current shell

