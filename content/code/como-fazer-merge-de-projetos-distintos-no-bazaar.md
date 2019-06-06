---
date: "2008-06-16"
title: Como fazer merge de projetos distintos no Bazaar
categories: [ "code" ]
---
O problema foi o seguinte: Nós iniciamos o controle de fonte pelo [Bazaar](http://bazaar-vcs.org/) na parte Linux do projeto, já que ela não iria funcionar pelo [Source Safe](http://www.caloni.com.br/blog/guia-basico-de-controle-de-codigo-source-safe), mesmo. Dessa forma apenas um braço do projeto estava no controle de fonte e o resto não.

No segundo momento da evolução decidimos começar a migrar os projetos para o Bazaar, inclusive a parte daquele projeto que compila no Windows. Maravilha. Ambos sendo controlados é uma beleza, não é mesmo?

Até que veio o dia de juntar.

O processo de _merge _de um controle de fonte supõe que os _branches _começaram em algum **ponto em comum**; do contrário não há como o controlador saber as coisas que mudaram em paralelo. Pois é achando a modificação **ancestral**, pai de ambos os _branches_, que ele irá medir a dificuldade de juntar as versões novamente. Se não existe ancestral, não existe análise. Como exemplificado na figura:

[![branches-sem-ancestral.gif](http://i.imgur.com/HfJy8hP.gif)](/images/branches-sem-ancestral.gif)

#### Se baseando no rebase

Acontece que existe um _plugin _esperto que consegue migrar revisões (_commits_) entre _branches _sem qualquer parentesco. Não me pergunte como ele faz isso. Mas ele faz. E foi assim que resolvemos o problema dos _branches _órfãos.

Para instalar o _plugin _do **rebase**, basta [baixá-lo e](http://bazaar-vcs.org/Rebase) copiar sua pasta extraída com um nome válido no Python (rebase, por exemplo). A partir daí os comandos do _plugin _estão disponíveis no _prompt _do Bazaar, assim como a instalação de qualquer _plugin _que cria novos comandos.

    
    >bzr help commands
    add             Add specified files or directories.
    annotate        Show the origin of each line in a file.
    bind            Convert the current branch into a checkout of the supplied branch.
    branch          Create a new copy of a branch.
    ...
    push            Update a mirror of this branch.
    <font color="#ff0000">rebase          Re-base a branch. [rebase]
    rebase-abort    Abort an interrupted rebase [rebase]
    rebase-continue Continue an interrupted rebase after resolving conflicts [rebase]
    rebase-todo     Print list of revisions that still need to be replayed as part of the  [rebase]
    </font>reconcile       Reconcile bzr metadata in a branch.
    reconfigure     Reconfigure the type of a bzr directory.
    register-branch Register a branch with launchpad.net. [launchpad]
    remerge         Redo a merge.
    remove          Remove files or directories.
    remove-tree     Remove the working tree from a given branch/checkout.
    renames         Show list of renamed files.
    <font color="#ff0000">replay          Replay commits from another branch on top of this one. [rebase]
    </font>resolve         Mark a conflict as resolved.
    revert          Revert files to a previous revision.
    ...
    whoami          Show or set bzr user id.

#### Fica de olho no replay!

O comando que usamos foi o **replay**, que não é comando principal do _plugin, _mas que resolve esse problema de maneira quase satisfatória. Como era tudo o que tínhamos, valeu a pena.

O processo que usei foi de usar esse comando n vezes para buscar revisões de um branch e colocar no outro. Um grande problema com ele é que ao encontrar merges no branch origem ele se perde e o usuário tem que fazer as modificações "na mão". Deu um pouco de trabalho, mas conseguimos migrar nossos _commits _mais importantes e deixar o projeto inteiro, Linux+Windows, em um _branch _só.

    
    C:\Tests>bzr init linux
    
    C:\Tests>cd linux
    
    C:\Tests\linux>copy con lnx
    linux
    ^Z
            1 arquivo(s) copiado(s).
    
    C:\Tests\linux>bzr add
    added lnx
    
    C:\Tests\linux>bzr commit -m "Linux 1"
    Committing to: C:/Tests/linux/
    added lnx
    Committed revision 1.
    
    C:\Tests\linux>copy con lnx2
    linux2
    ^Z
            1 arquivo(s) copiado(s).
    
    C:\Tests\linux>bzr add
    added lnx2
    
    C:\Tests\linux>bzr commit -m "Linux 2"
    Committing to: C:/Tests/linux/
    added lnx2
    Committed revision 2.
    
    C:\Tests\linux>cd ..
    
    C:\Tests>bzr init windows
    
    C:\Tests>cd windows
    
    C:\Tests\windows>copy con win1
    windows
    ^Z
            1 arquivo(s) copiado(s).
    
    C:\Tests\windows>bzr add
    added win1
    
    C:\Tests\windows>bzr commit -m "Windows 1"
    Committing to: C:/Tests/windows/
    added win1
    Committed revision 1.
    
    C:\Tests\windows>copy con win2
    windows2
    ^Z
            1 arquivo(s) copiado(s).
    C:\Tests\windows>bzr add
    added win2
    
    C:\Tests\windows>bzr commit -m "Windows 2"
    Committing to: C:/Tests/windows/
    added win2
    Committed revision 2.
    
    C:\Tests\linux>cd ..
    
    C:\Tests>cd linux
    
    C:\Tests\linux>bzr replay ..\windows -r1..2
    All changes applied successfully.
    Committing to: C:/Tests/linux/
    added win1
    Committed revision 3.
    All changes applied successfully.
    Committing to: C:/Tests/linux/
    added win2
    Committed revision 4.

    
    C:\Tests\linux>bzr log
    ------------------------------------------------------------
    revno: 4
    committer: Wanderley Caloni <wanderley@caloni.com.br>
    branch nick: windows
    timestamp: Mon 2008-06-16 07:17:10 -0300
    message:
      Windows 2
    ------------------------------------------------------------
    revno: 3
    committer: Wanderley Caloni <wanderley@caloni.com.br>
    branch nick: windows
    timestamp: Mon 2008-06-16 07:16:52 -0300
    message:
      Windows 1
    ------------------------------------------------------------
    revno: 2
    committer: Wanderley Caloni <wanderley@caloni.com.br>
    branch nick: linux
    timestamp: Mon 2008-06-16 07:16:24 -0300
    message:
      Linux 2
    ------------------------------------------------------------
    revno: 1
    committer: Wanderley Caloni <wanderley@caloni.com.br>
    branch nick: linux
    timestamp: Mon 2008-06-16 07:16:01 -0300
    message:
      Linux 1
    
    C:\Tests\linux>ls
    lnx  lnx2  win1  win2
    
    C:\Tests\linux>

![branches-com-replay.gif](http://i.imgur.com/3X8DCfS.gif)
