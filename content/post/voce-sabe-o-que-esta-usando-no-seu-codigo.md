---
categories: [ "code" ]
date: "2015-07-28"
tags: [ "draft",  ]
title: "Você sabe o que está usando no seu código?"
---
Quando se mexe com C++ em múltiplos fontes logo vem aquela bagunça do versionamento e do compartilhamento de código. LIBs, DLLs, COMs (de Component Object Model, da Microsoft). É difícil a partir de um binário saber quais os fontes envolvidos em sua construção, a não ser que você os amarre através de um sistema automatizado de build onde todos os binários devem ser obrigatoriamente compilados (e suas dependências, claro).

Porém, há maneiras mais descentralizadas de se trabalhar. Alguém poderia simplesmente colocar a versão em cada CPP e atualizá-la, assim como comentários de histórico, toda vez que alguma mudança for feita:


OK, esse já é um modelo interessante, embora totalmente descartável se você já usa um sistema de build atrelado a um controle de fonte, já que você automaticamente já terá um número mágico para relacionar seus binários: o revno de seu commit (ou seus commits, no caso de mais de um repositório).

Uma versão um pouco mais... "binária", seria inserir uma string no próprio fonte com essa versão, e talvez até o nome de seu módulo/lib/etc:

static const char* LIBVERSION = "minhalib 0.0.1";

Dessa forma, por pior que seja a situação do controle de seus binários, sempre haverá a possibilidade de procurar a string lá dentro.

Ops, esqueci que nesses compiladores modernos o que você não usa não será incluído no binário final. Isso quer dizer que se quisermos que essas strings de identificação de dependências apareça no binário compilado precisamos pelo menos dar a impressão de que ele esteja sendo usado:


Agora uma variável estática do módulo deverá ser inicializada como um objeto da classe Using e irá jogar em uma variável estática dentro do construtor. Se ela será usada fica a dúvida do compilador, que deixa tudo como está. Ou seja, ganhamos nossa string no binário:


Uma solução mais genérica pode ser aplicada utilizando as famigeradas macros e...

O quê?!?!?!??! VOCÊ DISSE MACROS?!???!? TÁ MALUCO??!??!

Sim. Macros. São inofensivas se você usar direito.

E se reclamar vai ter goto.


A ideia é que qualquer pedaço de código, seja um conjunto de CPPs que você chama de LIB, ou um CPP que você compila em diferentes projetos (talvez em cópias diferentes ainda sendo usadas), ou até aquela função-chave, ou classe-chave. Na verdade, quando eu digo pedaço de código, é pedaço mesmo. Está livre para você imaginar e rotular o que quiser. Depois você consegue dar uma geral no resultado:


Com esse simples mecanismo que não gasta mais do que algumas chamadas de assembly no início da lib (antes do main) e o espaço ocupado na memória pelas strings somadas (menos de 1KB, provavelmente) você tem em suas mãos uma poderosa ferramenta de análise de como os binários estão sendo gerados pela sua equipe remota, ou por qual configuração foi usada na máquina de build para gerar aquela DLL com aquele problema antigo, ou porque algo que funcionava parou de funcionar e nada foi mexido (isso nunca acontece, não é mesmo?).

O código dessa brincadeira está no meu repositório de samples do GitHub.
