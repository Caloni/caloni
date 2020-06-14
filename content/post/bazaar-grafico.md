---
categories: [ "code" ]
date: "2010-02-25"
tags: [ "draft", "tools" ]
title: "Bazaar gráfico"
---
Bom, já que por enquanto os assuntos de macho estão em falta (acabei de voltar de férias), apresento-lhes o maravilhoso mundo do Bazaar para boiolas user-friendly!

Ele é leve, vem enrustido embutido na última versão e pode economizar alguns page ups/downs no prompt do DOS. Ah, sim, antes que comentem, eu não uso o Tortoise for Bazaar porque instalar shell extensions, só os muito bem feitos. (Do contrário, bem-feito para quem instalou.)

Para exibir a lista de comandos "amigáveis", digite no prompt os comandos do Bazaar filtrando-os para os que começam com "q":

    
    bzr help commands | grep ^q.*
    
    qadd                 GUI for adding files or directories. [qbzr]
    qannotate            Show the origin of each line in a file. [qbzr]
    qbranch              Create a new copy of a branch. [qbzr]
    qbrowse              Show inventory. [qbzr]
    qcat                 View the contents of a file as of a given revision. [qbzr]
    qcommit              GUI for committing revisions. [qbzr]
    qconfig              Configure Bazaar. [qbzr]
    qdiff                Show differences in working tree in a GUI window. [qbzr]
    qgetnew              Creates a new working tree (either a checkout or full branch) [qbzr]
    qgetupdates          Fetches external changes into the working tree [qbzr]
    qinfo                 [qbzr]
    qinit                Initializes a new (possibly shared) repository. [qbzr]
    qlog                 Show log of a repository, branch, file, or directory in a Qt window. [qbzr]
    qmerge               Perform a three-way merge. [qbzr]
    qpull                Turn this branch into a mirror of another branch. [qbzr]
    qpush                Update a mirror of this branch. [qbzr]
    qrevert              Revert changes files. [qbzr]
    qtag                 Edit tags. [qbzr]

Os que eu mais uso no dia-a-dia são:

Diversão garantida. Por meio destes simples comandos podemos ver o histórico de commits e navegar pela árvore de pastas e arquivos com a anotação do último commit para cada elemento. Só para ter uma ideia de quanto uso isso, transformei-os em opções do Explorer.

Além da utilidade básica, de quebra, o qbrowse pode te levar para um qlog filtrado, e o qlog pode te levar a um diff gráfico, que é o próximo comando que eu iria mostrar.

Coisa linda de Deus. Existem dois modos de exibição, mas o padrão já é show de bola, mostrando as mudanças em todos os arquivos de um commit de uma só vez ou do arquivo/pasta especificado pelo comando. É lógico que é possível especificar qualquer faixa de commits que você quiser ver.

Uma desvantagem desse comando é que ele oculta o resto das linhas do fonte e não mostra de jeito nenhum (pelo menos não descobri ainda como fazer isso). Sendo assim, para uma análise mais detalhada das diferenças no código-fonte sempre use um editor externo que consiga comparar arquivos inteiros (eu uso o WinMerge). Você pode colocar esse comando na forma de um diff personalizado, com o uso do qconfig.

