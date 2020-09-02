---
date: "2015-01-11"
tags: [ "code", "draft",  ]
title: "Por que o Visual Studio gera executáveis mutantes"
---
> Esse é um post antigo que encontrei no meio dos meus emails de 2006, mas que contém uma boa dica para quem já entendeu o passo-a-passo da compilação, mas ainda tem sérios problemas quando os projetos ficam gigantes.

Essa é a segunda vez que encontro esse mesmo problema. Como acredito que outras almas podem estar sofrendo do mesmo mal, coloco aqui uma breve descrição de como o VC8 faz para gerar um executável que, mesmo não dependendo das DLLs de runtime, não são executados em sistemas que suportam a interpretação do ".manifest". De canja, um pequeno programa que exibe a lista dos programas instalados no sistema.

Primeiro, precisamos de um solution que contenha um projeto console e uma LIB. O projeto console deve usar a LIB para fazer alguma coisa. No exemplo abaixo, estarei listando os programas instalados no Windows (os mostrados no painel de controle através da opção "Adicionar/remover programas".


Observação importante: para ignorar todas as estripulias da versão Debug, todos os testes foram compilados em Release.

Primeiramente, modifico a configuração padrão dos dois projetos para não depender da DLL de runtime do VC. Isso está em Project, Properties, C/C++, Code Generation, Runtime Library. Depois executo em uma máquina virtual sem as runtimes do VC8 instaladas:


Perfeito. Exatamente o que eu queria: um executável console que não dependesse de DLL nenhuma exceto as que já estão instaladas em um Windows ordinário.

Agora, vamos imaginar que esse é um daqueles projetos enormes de 5 * 10 ^ 42 de linhas (obs: dramatização) e que meu aplicativo console está linkado com cerca de 3 * 10 ^ 666 de LIBs. E uma delas (a library do exemplo) está com a configuração original, ou seja, com a dependência da DLL de runtime. E ela usa a STL. Provavelmente o aplicativo console não irá compilar, mas isso não é problema, pois estamos acostumados a colocar a msvcrt.lib na lista de LIBs ignoradas, pois em muitos outros casos (que não vale a pena discutir aqui) esse workaround é válido. E tudo volta a funcionar. Quer dizer, linkar:

O sistema no pode executar o programa especificado.

Tudo bem, meu executável não é mutante ainda. Mas agora vamos trocar a chamada da nossa função que usa STL por uma função que não usa:



Agora sim, a mutação fez efeito! Temos um aplicativo que não depende da DLL de runtime, mas que no meio das n LIBs que ele utiliza existe uma configurada com a dependência. Ignorando a msvcrt.lib e um warning na compilação encontramos uma mensagem de erro um tanto exdrúxula.

Até agora, a maneira que eu tenho utilizado para rastrear esse problema é não ignorar a msvcrt e ir tirando as dependências das LIBs pouco a pouco, até que ocorra o erro de símbolo duplicado. Algo assim:


Se você tiver realmente 3 * 10 ^ 666 de LIBs, boa sorte =).
