---
date: "2008-09-19"
title: Reúna seus comandos mais usados no WinDbg com .cmdtree
categories: [ "blog" ]
---
. Logo depois meus outros colegas do fã-clube do WinDbg [Volker von Einem e [Dmitry Vostokov comentaram sobre a imensa utilidade desse comando.

E não é pra menos. É de longe o melhor comando não-documentado do ano. Tão bom que sou obrigado a comentar em português sobre ele, apesar dos três artigos já citados.

#### Comandos repetitivos

E eu estava justamente falando sobre essa mania dos programadores:

    
    windbg ANSI Command Tree 1.0
    title {"Meus Comandos Comuns"}
    body
    {"Comandos Comuns"}
     {"Subsecao"}
      {"Breakpoint no inicio do programa"} {"bp @$exentry"}
      {"GetLastError"} {"!gle"}

O resultado:

cmdtree.png

E podemos usar essa janela no nosso WinDbg, cada vez mais bonitinho e cada vez mais WYSIWYG:

cmdtree2.png

Realmente não há segredos em seu uso. Esse artigo foi apenas um patrocínio do clube do WinDbg.

 e a [Tess</blockquote>
