---
date: "2016-01-27"
title: "Exportando repositórios antigos do Bazaar para Git"
tags: [ "draft", "blog" ]
---
Enquanto estudava sobre [controle de fontes distribuído](https://en.wikipedia.org/wiki/Distributed_version_control), experimentei e usei os projetos Mercurial e Bazaar, precursores desse modelo que funcionavam bem em Windows. Havia o Git, mas por conta da sua evolução assimétrica, o ambiente da Microsoft havia ficado para trás.

Hoje com o Git sendo praticamente o _mainstream_ das conversões do SubVersion, e funcionando razoavelmente bem em ambientes Windows (64 ou 32), sobraram apenas os repositórios do Mercurial e do Bazaar. Na verdade, mais do Bazaar, pois eu havia migrado já do Hg pelo Bazaar possuir algo que hoje o Git emula, mas antes era um diferencial no projeto da Canonical: detecção de rename completo (com histórico e tudo). Isso para refatoração era vital, e suporte à refatoração pesada era o que eu precisava no momento.

Agora é hora de manter esse histórico vivo, mas convertido para o que todos usam.

### A migração

A primeira coisa a ser feita é converter o repositório. Depois de convertido, como todas as operações estarão no universo Git, há [uma](http://stackoverflow.com/questions/1425892/how-do-you-merge-two-git-repositories) de [entradas](http://stackoverflow.com/questions/13040958/merge-two-git-repositories-without-breaking-file-history) no StackOverflow para nos ajudar a reunir os repositórios em um só, meu objetivo, já que o Git é mais leve e mais versátil nesse quesito.

No Windows, nas últimas versões do Bazaar o comando fast-export não estava mais funcionando. Parado desde 2012, não há previsão de correções. No entanto, para essa operação, a versão 2.4.2 atendeu bem. O comando é um pouco diferente, mas ele é rápido e rodou sem problemas em conjunto com o fast-import do Git.

![](http://i.imgur.com/9gzHZOz.png)

```
git init
bzr fast-export --plain . | git fast-import

12:03:59 Calculating the revisions to include ...
12:03:59 Starting export of 2681 revisions ...
12:04:05 Skipping empty dir Tools/Desenv in rev 
12:04:05 Skipping empty dir Tools/Desenv in rev
12:04:45 1000/2681 commits exported at 1308/minute
12:05:12 2000/2681 commits exported at 1642/minute
12:05:59 WARNING: not creating tag u'1.09' pointing to non-existent revision 
12:05:59 WARNING: not creating tag u'1.50' pointing to non-existent revision 
12:05:59 WARNING: not creating tag u'1.51' pointing to non-existent revision 
12:05:59 WARNING: not creating tag u'1.49' pointing to non-existent revision 
12:05:59 WARNING: not creating tag u'1.48' pointing to non-existent revision 
12:05:59 WARNING: not creating tag u'1.45' pointing to non-existent revision 
12:05:59 WARNING: not creating tag u'1.47' pointing to non-existent revision 
12:05:59 WARNING: not creating tag u'1.46' pointing to non-existent revision 
12:05:59 WARNING: not creating tag u'1.40' pointing to non-existent revision 
12:05:59 WARNING: not creating tag u'1.39' pointing to non-existent revision 
12:05:59 Exported 2681 revisions in 0:02:00
C:\PROGRAM FILES (X86)\GIT\libexec\git-core\git-fast-import.exe statistics:
---------------------------------------------------------------------
Alloc'd objects:      35000
Total objects:        33979 (      9714 duplicates                  )
      blobs  :        15604 (      6833 duplicates       7747 deltas of      15389 attempts)
      trees  :        15694 (      2881 duplicates      12881 deltas of      14635 attempts)
      commits:         2681 (         0 duplicates          0 deltas of          0 attempts)
      tags   :            0 (         0 duplicates          0 deltas of          0 attempts)
Total branches:          98 (         1 loads     )
      marks:        1048576 (      2681 unique    )
      atoms:           4549
Memory total:          3567 KiB
       pools:          2200 KiB
     objects:          1367 KiB
---------------------------------------------------------------------
pack_report: getpagesize()            =      65536
pack_report: core.packedGitWindowSize =   33554432
pack_report: core.packedGitLimit      =  268435456
pack_report: pack_used_ctr            =      22324
pack_report: pack_mmap_calls          =      10353
pack_report: pack_open_windows        =          4 /          6
pack_report: pack_mapped              =  101069594 /  163170978
---------------------------------------------------------------------
```

É óbvio que nem tudo serão mil maravilhas. Eu, por exemplo, encontrei um problema com case-sensitive que me deu algumas dores de cabeça:

```
fatal: Path Something/Resource.h not in branch
fast-import: dumping crash report to .git/fast_import_crash_676
bzr: broken pipe
```

O Git gera um arquivo de report onde estão as informações do ocorrido. Uma forma de contornar esse tipo de problema é primeiro exportar para um arquivo e editá-lo (corrigindo o case, por exemplo):

```
bzr fast-export --plain . > plain-export.txt
gvim fast-export.txt
hack hack hack
type fast-export.txt | git fast-import
```

_Note que talvez você precise de um editor que suporte arquivos gigantescos (como o Vim) e precise se debruçar sobre merges com arquivos com mesmo nome e diferentes cases. Isso que dá manter projetos com refactoring pesado._

Por fim, faça a conversão para todos os .bzr que tiver e haverá um .git com todo o histórico desses anos usando Bazaar. O próximo passo é montar o histórico de todos eles em apenas um repositório (se assim desejar). Segue uma série de comandos que pode ajudar para usar em uma batch:

```
@echo off
git remote add -f bzr ..\PathToOldConvertedRepo\%1
git merge bzr/master
git remote remove bzr
mkdir Archive\%1
echo Mova os arquivos importados
pause
git add --all
git ci -m "Archiving old Bazaar repo (%1)."
```

Você pode chamar um a um em cima de um repo novo:

```
mkdir NewRepo
cd NewRepo
git init
..\MyMergeBatch.bat OldRepoName
..\MyMergeBatch.bat OldRepoName2
..\MyMergeBatch.bat OldRepoName3
```

Para conseguir ter acesso ao histórico dos arquivos movidos, basta usar a opção -all do log:

```
git log --all -- MyRemovedPath
```

## Update

Tive alguns problemas em rastrear o histórico utilizando a estratégia de fazer merge no mesmo branch. A solução que encontrei, embora não exatamente direta, foi realizar os merges em branches apartados primeiro, mover os arquivos (de preferência, usando o git, para que ele detecte o rename), aplicar o commit e realizar o merge com o master. Há uma vantagem nessa estratégia, além do log --follow funcionar melhor: mantenha os branches originais, além do ponteiro para remote. Dessa forma, depois de alguns anos, saberá de onde veio esse merge maluco.

## Update2

Depois de um tempo testando essa técnica, descobri que o Git se perde novamente e não encontra mais todos os logs, mesmo com --follow  mesmo movendo os arquivos. O meu problema está relacionado com mesmos paths dos arquivos em repositórios diferentes. Paciência.
