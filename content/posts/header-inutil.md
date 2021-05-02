---
date: "2012-03-27"
title: Header Inútil
categories: [ "draft", "code" ]
---
O Visual Studio é uma ótima ferramenta para depurar rapidamente programas sendo desenvolvidos e <del>para editar vários arquivos ao mesmo tempo</del> para o resto usamos Vim. No entanto, a versão 2010 do ambiente (ainda não testei a 2011 beta) possui um pequeno deslize com sua árvore de dependências que não chega a prejudica o desenvolvedor, mas o deixa com um bug atrás da orelha.

Vamos supor que você crie seu super-projeto ZeroMQ e no meio dele acabe evoluindo uma nova forma de vida inútil e descartável, que aqui iremos chamar de HeaderInutil e seu fiel companheiro CppInutil:

[![](http://i.imgur.com/opLLPIk.png)](/images/header-inutil.png)

OK. Ele não está fazendo nada, mas e daí? Compilo meu projeto normalmente e depuro ele como se nada estivesse acontecendo.

------ Rebuild All started: Project: ZeroMasQueCoisaProj, Configuration: Debug Win32 ------
Build started 27/03/2012 11:40:32.
_PrepareForClean:
Deleting file "Debug\ZeroMasQueCoisaProj.lastbuildstate".
InitializeBuildStatus:
Creating "Debug\ZeroMasQueCoisaProj.unsuccessfulbuild" because "AlwaysCreate" was specified.
ClCompile:
stdafx.cpp
ZeroMasQueCoisaProj.cpp
CppInutil.cpp
Generating Code...
Manifest:
Deleting file "Debug\ZeroMasQueCoisaProj.exe.embed.manifest".
LinkEmbedManifest:
ZeroMasQueCoisaProj.vcxproj -> c:\...\Debug\ZeroMasQueCoisaProj.exe
FinalizeBuildStatus:
Deleting file "Debug\ZeroMasQueCoisaProj.unsuccessfulbuild".
Touching "Debug\ZeroMasQueCoisaProj.lastbuildstate".

Build succeeded.

Time Elapsed 00:00:00.73
========== Rebuild All: 1 succeeded, 0 failed, 0 skipped ==========

'ZeroMasQueCoisaProj.exe': Loaded 'C:\...\Debug\ZeroMasQueCoisaProj.exe', Symbols loaded.
'ZeroMasQueCoisaProj.exe': Loaded 'C:\Windows\SysWOW64\ntdll.dll', Cannot find or open the PDB file
'ZeroMasQueCoisaProj.exe': Loaded 'C:\Windows\SysWOW64\kernel32.dll', Cannot find or open the PDB file
'ZeroMasQueCoisaProj.exe': Loaded 'C:\Windows\SysWOW64\KernelBase.dll', Cannot find or open the PDB file
'ZeroMasQueCoisaProj.exe': Loaded 'C:\Windows\SysWOW64\msvcr100d.dll', Symbols loaded.
The program '[5212] ZeroMasQueCoisaProj.exe: Native' has exited with code 0 (0x0).

Show.

Mas o que acontece se eu precisar no momento do refactory (**que deve, sim, existir**) eu decidir remover meus arquivos inúteis?

Continuo compilando normalmente o projeto, mas na hora de depurar...

[![](http://i.imgur.com/vewufus.png)](/images/header-inutil2.png)

Mas o que ocorre? Eu acabei de compilar o projeto! E se eu compilar novamente e pressionar F5, ele continua apresentando o mesmo problema!

_OK, não estou admitindo aqui o famigerado Rebuild All. Se você mantém projetos com mais de 200 arquivos, acho que deve **repensar seus conceitos** ao usar Rebuild All para tudo nessa vida._

Acontece que existe uma árvore de dependências que o Visual Studio mantém para saber se seu projeto foi atualizado com tudo que tem mais de novo no que diz respeito ao **File System**, mas às vezes se esquece de checar o FS com o que está na solution. Por conta disso, o HeaderInutil e o CppInutil continuam dentro da árvore de dependência como zumbis.

O que pode ser feito nesse caso (além do que os personagens de The Walking Dead costumam fazer) é configurar o arquivo devenv.exe.config (presente em **%programfiles(x86)%\Microsoft Visual Studio 10.0\Common7\IDE**) e adicionar as seguintes linhas após a seção **configSections. (**Esses passos [estão descritos no blogue da equipe do VC](http://blogs.msdn.com/b/vsproject/archive/2009/07/21/enable-c-project-system-logging.aspx).)

<system.diagnostics>
<switches>
<add name="CPS" value="4" />
</switches>
</system.diagnostics>

[![](http://i.imgur.com/wutWKnk.png)](/images/header-inutil3.png)

Depois de modificar o arquivo, reinicie o Visual Studio e tente novamente apertar F5 no mesmo projeto, **mas com o [DebugView ](http://technet.microsoft.com/en-us/sysinternals/bb896647)aberto**.

[![](http://i.imgur.com/rzJ3Pvw.png)](/images/header-inutil4.png)

Como um amigo meu diria: "**AHÁ!!**". Descobrimos o culpado.

A solução? Nesse caso não tem jeito: dar um clean no projeto e build novamente para que o VS reconstrua a árvore de dependências. Porém, **agora sabemos por que precisamos do Rebuild All**. Não é RebuildAllMania.

![](http://www.google.com/uds/css/small-logo.png)
