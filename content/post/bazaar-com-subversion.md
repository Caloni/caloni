---
categories: [ "code" ]
date: "2011-03-23"
tags: [ "draft", "tools" ]
title: "Bazaar com Subversion"
---
Para pessoas que ficaram viciadas em commits curtos e todo o histórico do fonte na própria máquina, foi uma surpresa descobrir que com o uso do plugin bzr-svn (já incluso no pacote de instalação), consigo ainda utilizar o Bazaar, mesmo que agora esteja trabalhando com um branch do Subversion.

Na verdade, melhor ainda: o bzr-svn baixa o SVN trunk com todo o histórico na máquina local, como se fosse um branch do próprio Bazaar, e permite a criação de branches desconectados para pequenos commits e o merge final para o servidor SVN.

E o melhor de tudo: não há segredo. Tudo que precisa fazer é instalar o Bazaar e fazer um get/co com o endereço do branch SVN que o plugin se vira sozinho para detectar que se trata do Subversion. (Se for um branch protegido, o usuário e senha serão pedidos durante o processo).

    
    C:\Projetos>bzr co http://subversion.assembla.com/svn/caloni/ caloni
    Initialising Subversion metadata cache in C:\Users\Caloni\AppData\Local\svn-cache\sbrubles.
    C:\Projetos>cd caloni
    C:\Projetos\caloni>bzr qlog
    C:\Projetos\caloni>bzr get . ..\caloni.local
    Branched 2 revision(s).
    C:\Projetos\caloni>cd ..\caloni.local
    C:\Projetos\caloni.local>vim readme.txt
    C:\Projetos\caloni.local>bzr ci -m "Commit local"
    Committing to: C:/Projetos/caloni.local/modified readme.txt
    Committed revision 3.
    C:\Projetos\caloni.local>vim readme.txt
    C:\Projetos\caloni.local>bzr ci -m "Commit local"
    Committing to: C:/Projetos/caloni.local/modified readme.txt
    Committed revision 4.
    C:\Projetos\caloni.local>vim readme.txt
    C:\Projetos\caloni.local>bzr ci -m "Commit local"
    Committing to: C:/Projetos/caloni.local/modified readme.txt
    Committed revision 5.
    C:\Projetos\caloni.local>cd ..\caloni
    C:\Projetos\caloni>bzr merge ..\caloni.local
     M  readme.txt
    All changes applied successfully.
    C:\Projetos\caloni>bzr st
    modified:  readme.txt
    pending merge tips: (use -v to see all merge revisions)  
    Wanderley Caloni 2011-03-23 Commit local
    C:\Projetos\caloni>bzr ci -m "Commit pro servidor"
    Committing to: http://subversion.assembla.com/svn/caloni
    modified readme.txtHTTP subversion.assembla.com 
    username: caloni
    <http://subversion.assembla.com:80> 
    Restricted Area caloni 
    password:
    Committed revision 3.
    C:\Projetos\caloni>bzr qlog

