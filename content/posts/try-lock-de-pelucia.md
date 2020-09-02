---
date: "2020-04-07"
tags: [ "code", "draft", "fun" ]
title: "Meu Try Lock de Pelúcia"
---
Alguns implementam mutex pero no mucho, que é aquele mutex que não faz nada porque ele sabe que só tem uma thread rodando no processo. É uma solução elegante para abstrair o uso de lock em um processo que pode ou não rodar multithread.

Já isso me lembra o try lock de pelúcia de um driver de uma empresa que trabalhei certa vez. Como havia situações onde o lock não era nunca liberado, e a thread estava rodando em um nível de interrupção que não poderia mais voltar, ou ela agendava uma execução menos prioritária ou obtia o lock. Mas baixar a prioridade não era uma opção para o programador MacGyver. Então o código acabou ficando mais ou menos assim:


Ninguém mandou mexer com o dadinho.
