---
date: "2008-09-19"
title: Reúna seus comandos mais usados no WinDbg com .cmdtree
categories: [ "blog" ]
---
Tudo começou com o [artigo de Roberto Farah](http://blogs.msdn.com/debuggingtoolbox/archive/2008/09/17/special-command-execute-commands-from-a-customized-user-interface-with-cmdtree.aspx) sobre o comando "escondido" do WinDbg [.cmdtree](http://www.microsoft.com/whdc/devtools/debugging/whatsnew.mspx). Logo depois meus outros colegas do fã-clube do WinDbg [Volker von Einem](http://voneinem-windbg.blogspot.com/2008/09/amazing-helper-cmdtree.html) e [Dmitry Vostokov](http://www.dumpanalysis.org/blog/index.php/2008/09/18/cmdtreetxt-for-cda-checklist/) comentaram sobre a imensa utilidade desse comando.

E não é pra menos. É de longe o melhor comando não-documentado do ano. Tão bom que sou obrigado a comentar em português sobre ele, apesar dos três artigos já citados.

#### Comandos repetitivos

E eu estava justamente falando sobre essa [mania dos programadores](http://www.caloni.com.br/todo-programador-e-um-filosofo-em-potencial) sempre acharem soluções para tarefas repetitivas e monótonas que o computador possa fazer sozinho.O comando .**cmdtree **é uma dessas soluções, pois possibilita ao depurador profissional juntar em uma só guia o conjunto de comandos mais usados por ele no dia-a-dia, por mais bizarros e com mais parâmetros que eles sejam, já que é possível representá-los por um _alias_ (apelido):

    
    windbg ANSI Command Tree 1.0
    title {"Meus Comandos Comuns"}
    body
    {"Comandos Comuns"}
     {"Subsecao"}
      {"Breakpoint no inicio do programa"} {"bp @$exentry"}
      {"GetLastError"} {"!gle"}

O resultado:

![cmdtree.png](http://i.imgur.com/3Dg69vQ.png)

E podemos usar essa janela no nosso WinDbg, cada vez mais bonitinho e cada vez mais [WYSIWYG](http://pt.wikipedia.org/wiki/Wysiwyg):

[![cmdtree2.png](http://i.imgur.com/rT1WBgt.png)](/images/cmdtree2.png)

Realmente não há segredos em seu uso. Esse artigo foi apenas um patrocínio do clube do WinDbg.

<blockquote>PS: Interessantemente o suficiente, durante minha navegação em busca das referências encontrei mais dois artigos de duas figurinhas carimbadas no mundo de _debugging_: [John Robbins](http://www.wintellect.com/CS/blogs/jrobbins/archive/2008/09/17/windbg-cmdtree-file-that-eases-some-sos-pain.aspx) e a [Tess](http://blogs.msdn.com/tess/archive/2008/09/18/making-it-easier-to-debug-net-dumps-in-windbg-using-cmdtree.aspx). Pois é, se o mundo de informática já é pequeno, imagine o mundo de WinDbg =)</blockquote>
