---
categories: [ "code" ]
date: "2017-02-04"
tags: [ "draft",  ]
title: "Um commit por feature"
---
Imagine que você vai começar a trabalhar em algo novo. Daí você baixa a última versão do branch de dev e começa a codar. Então chega um momento em que o primeiro, segundo, terceiro commits são necessários para manter a ordem em sua cabeça. "Fiz isso logo de manhã, testei algo diferente antes do almoço e de tarde fui incrementando a solução final até passar todos os testes." Tudo bonito. Mas como fica na hora de subir essa bagaça pras pessoas verem?

Vamos visualizar isso em commits. Você baixa a última versão do dev, começa a trabalhar e de duas uma:

1. Percebe que dá para resolver tudo em um commit só.
2. Percebe que o buraco é mais embaixo; vou precisar de mais tempo e mais commits.

No caso 1, a solução é simples e direta: faça as modificações, rode os testes locais e aplique o commit já no formato definido pela sua equipe (número do ticket, texto no idioma correto, detalhes nos parágrafos abaixo). Suba e mande para code review.

    C:\Temp\projectX>git pull
    Already up-to-date.
    
    C:\Temp\projectX>git branch
    * dev
      master
    
    C:\Temp\projectX>gvim main.cpp
    
    C:\Temp\projectX>git add main.cpp
    
    C:\Temp\projectX>git ci -m "ISS-4 Changing test function return type to int."
    [dev 7f0121b] ISS-4 Changing test function return type to int.
     1 file changed, 2 insertions(+), 1 deletion(-)
    
    C:\Temp\projectX>git status
    On branch dev
    Your branch is ahead of 'origin/dev' by 1 commit.
      (use "git push" to publish your local commits)
    nothing to commit, working tree clean
    
    C:\Temp\projectX>

Se a política de pull request estiver sendo usada, faça isso em um branch à parte, mas já mande para o reviewer aprovar o branch como se fosse um commit apenas e de preferência pronto para o rebase (o que não deve ser nem um problema se for uma mudança pontual).

    C:\Temp\projectX>gvim main.cpp
    
    C:\Temp\projectX>git co -b ISS-5-changing-test-return-value
    M       main.cpp
    Switched to a new branch 'ISS-5-changing-test-return-value'
    
    C:\Temp\projectX>git add main.cpp
    
    C:\Temp\projectX>git ci -m "ISS-5 Changing test return value"
    [ISS-5-changing-test-return-value 38df69c] ISS-5 Changing test return value
     1 file changed, 1 insertion(+), 1 deletion(-)
    
    C:\Temp\projectX>git status
    On branch ISS-5-changing-test-return-value
    nothing to commit, working tree clean
    
    C:\Temp\projectX>git push origin ISS-5-changing-test-return-value
    Counting objects: 6, done.
    Delta compression using up to 8 threads.
    Compressing objects: 100% (4/4), done.
    Writing objects: 100% (6/6), 618 bytes | 0 bytes/s, done.
    Total 6 (delta 2), reused 0 (delta 0)
    To ..\projectXRemote
     * [new branch]      ISS-5-changing-test-return-value -> ISS-5-changing-test-return-value

Quando mais de um commit é necessário é porque vai rolar a festa. Vários commits com texto e modificações temporárias podem ser feitos, e caso o trabalho vire a noite, é recomendado subir tudo para um branch temporário remoto (de preferência que já seja identificado pela equipe como o branch para determinado issue).

    C:\Temp\projectX>git branch
      ISS-5-changing-test-return-value
    * dev
      master
    
    C:\Temp\projectX>git co -b ISS-6-very-hard-hacking
    Switched to a new branch 'ISS-6-very-hard-hacking'
    
    C:\Temp\projectX>gvim main.cpp
    C:\Temp\projectX>git add main.cpp
    
    C:\Temp\projectX>git ci -m "Starting to test return 42."
    [ISS-6-very-hard-hacking e09cf24] Starting to test return 42.
     1 file changed, 1 insertion(+), 1 deletion(-)
    
    C:\Temp\projectX>gvim main.cpp
    C:\Temp\projectX>git add main.cpp
    
    C:\Temp\projectX>git ci -m "Created backup test.
    [ISS-6-very-hard-hacking 80a7f71] Created backup test.
     1 file changed, 5 insertions(+)
    
    C:\Temp\projectX>gvim main.cpp
    C:\Temp\projectX>git add main.cpp
    
    C:\Temp\projectX>git ci -m "Deleted backup function test."
    [ISS-6-very-hard-hacking 9620226] Deleted backup function test.
     1 file changed, 5 deletions(-)
    
    C:\Temp\projectX>gvim main.cpp
    C:\Temp\projectX>git add main.cpp
    
    C:\Temp\projectX>git ci -m "Screwing around."
    [ISS-6-very-hard-hacking 18d3afa] Screwing around.
     1 file changed, 2 deletions(-)
    
    C:\Temp\projectX>gvim main.cpp
    C:\Temp\projectX>git add main.cpp
    
    C:\Temp\projectX>git ci -m "Getting old version back."
    [ISS-6-very-hard-hacking f2a63d1] Getting old version back.
     1 file changed, 2 insertions(+)
    
    C:\Temp\projectX>gvim main.cpp
    C:\Temp\projectX>git add main.cpp
    
    C:\Temp\projectX>git ci -m "Small fix after unit tests."
    [ISS-6-very-hard-hacking e612339] Small fix after unit tests.
     1 file changed, 1 insertion(+), 1 deletion(-)
    
    C:\Temp\projectX>git log --oneline
    e612339 Small fix after unit tests.
    f2a63d1 Getting old version back.
    18d3afa Screwing around.
    9620226 Deleted backup function test.
    80a7f71 Created backup test.
    e09cf24 Starting to test return 42.
    7f0121b ISS-4 Changing test function return type to int.
    97222ec ISS-3 Testing something new.
    49d28aa ISS-2 Insertind comments and whatever.
    bff8edf ISS-1 First version.

Agora nós criamos uma bela duma bagunça, mas em um branch apartado e que ainda não foi enviado para pull requet ou inserido no branch de dev. Agora chega a hora de arrumar a casa. Para isso, como tudo no git, há várias maneiras, mas a mais direta é um rebase interativo (-i), onde você pega os commits e empacota tudo junto.

(Obs.: se sua modificação demorou algum tempo é melhor atualizar o branch de dev para ver se há algo novo e fazer o merge com o branch de feature; o rebase daí não encontrará conflitos.)

    C:\Temp\projectX>git merge dev
    Already up-to-date.
    
    C:\Temp\projectX>git rebase -i dev

Nesse momento o git irá abrir o editor com os commits trabalhados. Você deverá escolher quais operações fazer com cada commit. Se o objetivo é empacotar tudo, geralmente é pick no primeiro e squash em todos os outros:

    pick e09cf24 Starting to test return 42.
    squash 80a7f71 Created backup test.
    squash 9620226 Deleted backup function test.
    squash 18d3afa Screwing around.
    squash f2a63d1 Getting old version back.
    squash e612339 Small fix after unit tests.

Ao final da operação mais uma vez o git irá exibir o editor. Agora é hora de você escolher o texto bonitinho, formatadinho, do seu único commit que será usado no branch de dev. Em outras palavras, transformar isso:

    # This is a combination of 6 commits.
    # The first commit's message is:
    
    Starting to test return 42.
    
    # This is the commit message #2:
    
    Created backup test.
    
    # This is the commit message #3:
    
    Deleted backup function test.
    
    # This is the commit message #4:
    
    Screwing around.
    
    # This is the commit message #5:
    
    Getting old version back.
    
    # This is the commit message #6:
    
    Small fix after unit tests.

Nisso:

    ISS-6 A very hard hacking, tested and ready to merge.
    
    This hack involved several operations:
     - Starting to test return 42.
     - Created backup test.
     - Deleted backup function test.
     - Small fix after unit tests.

Agora na hora de fazer o merge seu histórico estará redondo, sem ramificações e com o resultado final de seu hacking parecendo que foi feito bonito desde o começo (ah, vá):

    C:\Temp\projectX>git log
    commit b4de47231f090e897053f4e9d19ea66c88d1f1fa
    Author: Wanderley Caloni <wanderley.caloni@bitforge.com.br>
    Date:   Sat Feb 4 10:59:18 2017 -0200
    
        ISS-6 A very hard hacking, tested and ready to merge.
    
        This hack involved several operations:
         - Starting to test return 42.
         - Created backup test.
         - Deleted backup function test.
         - Small fix after unit tests.
    
    commit 7f0121baac183eb1a832575781cca5d6e6a5489c
    Author: Wanderley Caloni <wanderley.caloni@bitforge.com.br>
    Date:   Sat Feb 4 10:51:54 2017 -0200
    
        ISS-4 Changing test function return type to int.
    
    commit 97222ec4578f9a4bced847266739b18f933178f3
    Author: Wanderley Caloni <wanderley.caloni@bitforge.com.br>
    Date:   Sat Feb 4 10:50:29 2017 -0200
    
        ISS-3 Testing something new.
    
    commit 49d28aa7faa02ff327ae9fac93676abad18ad0f3
    Author: Wanderley Caloni <wanderley.caloni@bitforge.com.br>
    Date:   Sat Feb 4 10:49:26 2017 -0200
    
        ISS-2 Insertind comments and whatever.
    
    commit bff8edf06e4a30480088a9a33c9b0c2ca5b6e0b3
    Author: Wanderley Caloni <wanderley.caloni@bitforge.com.br>
    Date:   Sat Feb 4 10:47:11 2017 -0200
    
        ISS-1 First version.

Esta é uma das inúmeras formas de trabalhar com o git de maneira individual sem atrapalhar seus colegas. Basicamente você pode escolher outras estratégias de commits e branchs locais, mas através do comando rebase -i é possível sempre reorganizar a bagunça em commits comportados, e dar a impressão que esses programadores são enviados divinos que modificam o fonte e acertam de primeira.
