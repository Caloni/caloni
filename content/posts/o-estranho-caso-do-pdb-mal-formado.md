---
date: "2015-08-19"
tags: [ "code", "draft",  ]
title: "O Estranho Caso do PDB Mal-Aformado"
---
Era uma vez, há 13 anos atrás, um tal de Visual Studio .NET, que iria trazer a felicidade para nós, meros mortais usuários de programinhas em C com ponteiro pra lá e ponteiro pra cá. Agora a Microsoft traria para o pessoal do "baixo nível" a mais nova novidade do verão: uma IDE lenta, bugada e... bonita?

Bem, para os que estavam acostumados com o Visual C++ 6.0, nada foi mais incômodo do que esperar carregar o programa de manhã para conseguir finalmente compilar. Ajustadas as expectativas, os projetos foram aos poucos migrados para aquela nova forma de configurar EXEs, DLLs, LIBs e OCXs.

E eis que alguém, muito provavelmente eu mesmo, naquele momento de inspiração, criei a seguinte configuração para a geração dos PDBs, os símbolos para depurar programas no Windows. C/C++, Output File, Program Database File Name = "$(IntDir)/$(ProjectName).pdb".

Faz sentido, não? Afinal de contas, o PDB costuma ter o nome do projeto, e ele já está setado até em outro lugar para gerar com o mesmo nome. Nada de novo no front. Em Linker, Debugging, Generate Program Database File vemos "$(OutDir"\$(ProjectName).pdb".

Até aí tudo bem. Aliás, tudo ficou muito bem por estranhos 13 anos. Até que alguém decidiu migrar para o já não tão novo Visual Studio 2013, onde tudo correu muito bem por algumas horas... talvez 13. Até que a depuração de repente parou de funcionar.

Será o benedito? Ou o co-piloto?

Pesquisando nos fóruns da vida, antro dos desesperados, achei/lembrei de um comando muito útil no WinDbg que não apenas diz se os símbolos estão "mismatch", ou seja, os símbolos ou o PDB não está combinando com o EXE, mas também por quê.

Bom, para saber se está mismatch é aquela fórmula de bolo:

Para saber o que está errado, o famigerado !IToldYouSo

Mano, como assim?!?!? Eu acabei de compilar esse binário, eu já apaguei 15 vezes as pastas de Debug e Release, eu já rebootei mais do que o Windows me obriga a rebootar por causa das falhas de segurança.

Pois, então, desesperançado, crio um projeto novo para comparar as configurações, e voltamos 13 anos atrás, naquele fatídico dia, e entendo por que o nome do PDB temporário não é igual. Bom, na verdade não entendo, mas intuo que tenha alguma relação:

E, de fato. Solução? Copie as configurações usuais do "novo" Visual Studio comparando com o velho.

Abaixo a chamada do suporte em inglês, se alguém achar o mesmo problema em algum fórum e quiser "espalhar a palavra".

> Just got stuck in the same problem, but in a C++ source that has 13 years, where its first solution was in VS 2003. Comparing the Project Properties in C/C++, Output Files, Program Database File Name, I found out that the project was pointing to the same file path that Linker, Debugging, Generate Program Database File, when the normal situation is to generate a vc120.pdb. Comparing with a new project, the "right" value can't be $(OutDir)$(TargetName).pdb (ou ProjectName), but $(IntDir)vc$(PlatformToolsetVersion).pdb. That solved the problem. I hope solve another one's problem as well =)
Minha próxima tarefa, aparentemente, é ver como sendo sócio da BitForge e da Intelitrader, e mesmo tendo já atualizado meu perfil MVP há anos, continuo sendo funcionário da UOL Diveo/Broker =/
