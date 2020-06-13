---
categories: [ "blog" ]
date: "2016-09-18"
tags: [ "draft", "tools" ]
title: "Usando GVim com projetos do Visual Studio"
---
A vida dos programadores C/C++ Windows -- e que geralmente precisam do Visual Studio -- está um abandono total. A configuração de make dos projetos sempre foi baseada no uso de makefiles, assim como no Unix, e por isso mesmo o uso da ferramenta nmake do SDK do Windows era a maneira padrão de se compilar e ver o resultado de dentro do Vim para projetos Windows. Com o advento do .NET, do Visual Studio 2003 e dos XMLs disfarçados como arquivos de projeto e solution, o uso do makefile foi paulatinamente abandonado, gerando diferentes versões de ferramentas -- todas incompatíveis -- para conseguir compilar um ou mais cpps e conseguir ver o resultado.

Por isso mesmo é um assunto pouco explorado nos fóruns do Stack Overflow como configurar decentemente o comando :make do Vim para conseguir realizar o ciclor program-compile-debug que já era feito desde a época do Amiga OS (e conhecido no manual do Vim como Quickfix). Ninguém se dá ao trabalho de usar esse modelo torto.

Houve um tempo que eu mesmo pesquisei algumas soluções, e caí no velho problema de tentar conviver com diferentes versões do Visual Studio. Deixei de lado o Vim por uns anos, e passei a usar o VsVim, um plugin que roda em várias versões do Visual Studio e utiliza o vimrc de sua instalação.

Hoje voltei a fuçar esse problema e depois de algumas horas tentando entender qual a dinâmica que deve ser seguida, cheguei a dois usos legítimos do make no Visual Studio: o modo legado, através do devenv, e o modo comportado, que usa a ferramenta MsBuild para encontrar o projeto e a solution que devem ser compilados.

A não ser que você coloque o path das ferramentas direto nos comandos (algo que não recomendo pois as coisas no Vim começam a ficar estranhas com paths com espaços, algo abundante no Windows) é preferível que você escolha qual devenv e qual msbuild deseja utilizar e definir isso na variável de sistema path. No meu exemplo estou usando o msbuild para qualquer Visual Studio acima do 2010 (como o 2015), pois já está padronizado, e como tenho projetos no VS2003 para manter, escolhi deixar o devenv.com com ele.

    set path=%path%;C:\Program Files (x86)\MSBuild\14.0\Bin
    set path=%path%;c:\Program Files (x86)\Microsoft Visual Studio .NET 2003\Common7\IDE

Note que essa configuração, para ficar persistente, precisa ser definida através do Painel de Controle ou Propriedades do Sistema. Google for it.

Depois de configurado, qualquer projeto deve ser compilável em 2003 pela linha de comando (através do devenv.com):

    C:\Projects\samples\FixCMake>devenv.com FixCMake.sln /build Debug
    
    Microsoft (R) Development Environment  Version 7.10.3077.
    Copyright (C) Microsoft Corp 1984-2001. All rights reserved.
    ------ Build started: Project: FixCMake, Configuration: Debug Win32 ------
    
    Compiling...
    FixCMake.cpp
    Linking...
    
    Build log was saved at "file://c:\Projects\samples\FixCMake\Debug\BuildLog.htm"
    FixCMake - 0 error(s), 0 warning(s)
    
    ---------------------- Done ----------------------
    
        Build: 1 succeeded, 0 failed, 0 skipped
    
    C:\Projects\samples\FixCMake>

Da mesma forma, projetos 2010+ devem usar o msbuild:

    C:\Projects\samples\ConsoleApplication5>msbuild
    Microsoft (R) Build Engine version 14.0.25420.1
    Copyright (C) Microsoft Corporation. All rights reserved.
    
    Building the projects in this solution one at a time. To enable parallel build, please add the "/m" switch.
    Build started 9/18/2016 6:02:19 PM.
    Project "C:\Projects\samples\ConsoleApplication5\ConsoleApplication5.sln" on node 1 (default targets).
    ValidateSolutionConfiguration:
      Building solution configuration "Debug|x64".
    The target "_ConvertPdbFiles" listed in a BeforeTargets attribute at "C:\Program Files (x86)\MSBuild\14.0\Microsoft.Common.targets\I
    The target "_CollectPdbFiles" listed in an AfterTargets attribute at "C:\Program Files (x86)\MSBuild\14.0\Microsoft.Common.targets\I
    The target "_CollectMdbFiles" listed in a BeforeTargets attribute at "C:\Program Files (x86)\MSBuild\14.0\Microsoft.Common.targets\I
    The target "_CopyMdbFiles" listed in an AfterTargets attribute at "C:\Program Files (x86)\MSBuild\14.0\Microsoft.Common.targets\Impo
    Project "C:\Projects\samples\ConsoleApplication5\ConsoleApplication5.sln" (1) is building "C:\Projects\samples\ConsoleApplication5\C
    PrepareForBuild:
      Creating directory "x64\Debug\".
      Creating directory "x64\Debug\ConsoleA.C9D4BE8C.tlog\".
    InitializeBuildStatus:
      Creating "x64\Debug\ConsoleA.C9D4BE8C.tlog\unsuccessfulbuild" because "AlwaysCreate" was specified.
    ClCompile:
      C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\x86_amd64\CL.exe /c /ZI /nologo /W3 /WX- /sdl /Od /D _DEBUG /D _CONSOLE
      140.pdb" /Gd /TP /errorReport:queue stdafx.cpp
      stdafx.cpp
      C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\x86_amd64\CL.exe /c /ZI /nologo /W3 /WX- /sdl /Od /D _DEBUG /D _CONSOLE
      140.pdb" /Gd /TP /errorReport:queue ConsoleApplication5.cpp
      ConsoleApplication5.cpp
    Link:
      C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\x86_amd64\link.exe /ERRORREPORT:QUEUE /OUT:"C:\Projects\samples\Console
      ib odbc32.lib odbccp32.lib /MANIFEST /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /manifest:embed /DEBUG /PDB:"C:\Projects\sa
      cation5.lib" /MACHINE:X64 x64\Debug\ConsoleApplication5.obj
      x64\Debug\stdafx.obj
      ConsoleApplication5.vcxproj -> C:\Projects\samples\ConsoleApplication5\x64\Debug\ConsoleApplication5.exe
      ConsoleApplication5.vcxproj -> C:\Projects\samples\ConsoleApplication5\x64\Debug\ConsoleApplication5.pdb (Full PDB)
    FinalizeBuildStatus:
      Deleting file "x64\Debug\ConsoleA.C9D4BE8C.tlog\unsuccessfulbuild".
      Touching "x64\Debug\ConsoleA.C9D4BE8C.tlog\ConsoleApplication5.lastbuildstate".
    Done Building Project "C:\Projects\samples\ConsoleApplication5\ConsoleApplication5.vcxproj" (default targets).
    
    Done Building Project "C:\Projects\samples\ConsoleApplication5\ConsoleApplication5.sln" (default targets).
    
    Build succeeded.
        0 Warning(s)
        0 Error(s)
    
    Time Elapsed 00:00:02.31
    
    C:\Projects\samples\ConsoleApplication5>

Pois é. Tirando essa facilidade, as coisas no Vim para msbuild rodam particularmente bem. Basta alterarmos o makeprg da seguinte maneira:

    :set makeprg=msbuild\ /nologo\ /v:q\ /property:GenerateFullPaths=true<CR>

As opções específicas são para gerar o path completo, as barras invertidas são por causa dessa mania do Vim de dar pau quando tem espaço em tudo.

A partir dessa configuração já é possível compilar um projeto estando em sua pasta:

Para o Visual Studio 2003 (ou qualquer um usando o devenv.com) é necessário mudar esse comando:

    :set makeprg=devenv\ %\ /build\ Debug<CR>

Sim, temos que escolher uma configuração (o msbuild já escolhe por você). E note que ele usa o arquivo atual (%) para compilar. Isso quer dizer que isso irá exigir do usuário de Vim abrir o sln ou o vcproj e executar o :make a partir daí. De qualquer forma, ele funciona também:

Note que em nenhum dos casos erros conseguirão ser capturados para irmos direto no ponto do código-fonte onde ele está. Para isso funcionar, em nosso último passo, é necessário configurar o errorformat para que ele tenha um padrão que funcione com ambas as ferramentas. Depois de testar um pouco, cheguei nesse formato:

    set errorformat=%f(%l)%m

Ele pega também os warnings, mas fazer o quê. Você não quer conviver com warnings em seu código pelo resto da vida, né? =)

E para navegar na lista é como o resultado de comandos como :vimgrep. :cnext e :cprevious vão para frente e para trás na lista, sempre pulando para o ponto no código onde está o erro.

Como deu pra perceber, para conseguir usar o msbuild e o devenv ao mesmo tempo você seria obrigado a trocar o makeprg sempre que precisasse. Para facilitar seu uso, nada como fazer um mapeamento de atalhos:

    map <F7> :set makeprg=devenv\ %\ /build\ Debug<CR>
    map <S-F7> :set makeprg=msbuild\ /nologo\ /v:q\ /property:GenerateFullPaths=true<CR>

Para alguém curioso para ver minhas configurações do Vim (quem quiser compartilhar também, fique à vontade), segue.
