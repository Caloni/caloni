---
date: "2008-09-19"
title: Reúna seus comandos mais usados no WinDbg com .cmdtree
categories: [ "blog" ]
---
Tudo começou com o artigo de Roberto Farah](http://blogs.msdn.com/debuggingtoolbox/archive/2008/09/17/special-command-execute-commands-from-a-customized-user-interface-with-cmdtree.aspx) sobre o comando "escondido" do WinDbg .cmdtree](http://www.microsoft.com/whdc/devtools/debugging/whatsnew.mspx). Logo depois meus outros colegas do fã-clube do WinDbg [Volker von Einem e [Dmitry Vostokov comentaram sobre a imensa utilidade desse comando.

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

!cmdtree.png

E podemos usar essa janela no nosso WinDbg, cada vez mais bonitinho e cada vez mais WYSIWYG:

!cmdtree2.png

Realmente não há segredos em seu uso. Esse artigo foi apenas um patrocínio do clube do WinDbg.

<blockquote>PS: Interessantemente o suficiente, durante minha navegação em busca das referências encontrei mais dois artigos de duas figurinhas carimbadas no mundo de _debugging_: John Robbins](http://www.wintellect.com/CS/blogs/jrobbins/archive/2008/09/17/windbg-cmdtree-file-that-eases-some-sos-pain.aspx) e a [Tess</blockquote>
