---
categories:
- code
date: '2008-09-19'
tags: null
title: Reúna seus comandos mais usados no WinDbg com .cmdtree
---

Tudo começou com o [artigo de Roberto Farah] sobre o comando "escondido" do WinDbg .cmdtree. Logo depois meus outros colegas do fã-clube do WinDbg [Volker von Einem] e [Dmitry Vostokov] comentaram sobre a imensa utilidade desse comando. E não é pra menos. É de longe o melhor comando não-documentado do ano. Tão bom que sou obrigado a comentar em português sobre ele, apesar dos três artigos já citados.

#### Comandos repetitivos

E eu estava justamente falando sobre essa mania dos programadores sempre acharem soluções para tarefas repetitivas e monótonas que o computador possa fazer sozinho.O comando .cmdtree é uma dessas soluções, pois possibilita ao depurador profissional juntar em uma só guia o conjunto de comandos mais usados por ele no dia-a-dia, por mais bizarros e com mais parâmetros que eles sejam, já que é possível representá-los por um alias (apelido):

    windbg ANSI Command Tree 1.0
    title {"Meus Comandos Comuns"}
    body
    {"Comandos Comuns"}
     {"Subsecao"}
      {"Breakpoint no inicio do programa"} {"bp @$exentry"}
      {"GetLastError"} {"!gle"}

O resultado:

![.cmdtree](/img/cmdtree.png)

E podemos usar essa janela no nosso WinDbg, cada vez mais bonitinho e cada vez mais [WYSIWYG](http://pt.wikipedia.org/wiki/Wysiwyg):

![.cmdtree2.png](/img/cmdtree2.png)

Realmente não há segredos em seu uso. Esse artigo foi apenas um patrocínio do clube do WinDbg.

[artigo de Roberto Farah]: https://docs.microsoft.com/en-us/archive/blogs/debuggingtoolbox/special-commandexecute-commands-from-a-customized-user-interface-with-cmdtree
[Volker von Einem]: http://voneinem-windbg.blogspot.com/2008/09/amazing-helper-cmdtree.html
[Dmitry Vostokov]: http://www.dumpanalysis.org/blog/index.php/2008/09/18/cmdtreetxt-for-cda-checklist/