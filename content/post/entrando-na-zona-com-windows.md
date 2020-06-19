---
categories: [ "code" ]
date: "2017-03-14"
tags: [ "draft", "tools" ]
title: "Entrando na zona com Windows"
---
**Update 2019-03-20: Adicionando programa para fazer tela cheia no Windows e retirados detalhes que não uso mais.**

Um artigo anterior havia dado umas dicas de como transformar o Vim em uma ferramenta para toda obra, com isso limitando as distrações quando se está em um computador, e com isso facilitando a entrada e a permanência no estado de fluidez de produtividade que conhecemos como "flow", ou estar na zona. Agora é a vez do Windows.

O Windows 10 já vem com atalhos pré-instalados assim que você loga nele. Tem browser, navegador de arquivos, notícias, e uma caralhada de coisas inúteis que ficam se mexendo na tela, chamando sua atenção, distraindo sobre o que é mais importante.

Mas é possível arrancar tudo isso e deixar na barra de tarefas pinado apenas as coisas realmente vitais para o uso do computador de trabalho, geralmente o terminal, o navegador (pesquisa, emails, etc) e o editor (não necessariamente o Vim).

O terminal do Windows, o Command Prompt, ou cmd para os íntimos, sofreu algumas mudanças ultimamente. Entre elas há a transparência, o que o tornou cool, e a tela cheia (atalho Alt+Enter), o que o tornou ideal como ferramenta de navegação para programadores (melhor do que o explorer, que virou um penduricalho de atalhos inúteis também). Você pode ativá-lo já entrando na tela cheia e com o code page de sua preferência (o meu é 65001, que é o utf8) usando esse pequeno programa:


Os comandos do git são muito verbose. Duas letras já seriam suficiente (o Windbg manipula seu programa com apenas uma...). Para otimizar a digitação no git crie uns aliases em seu HOME\.gitconfig:


Agora, através dos atalhos Win+1, 2, 3... pode-se abrir e alternar entre os aplicativos principais do seu dia-a-dia, que devem ficar "pinados" na barra de tarefas. Os meus atualmente são três: terminal (1 cmd), editor (2 vim) e browser (3 chrome). Não é necessário colocar coisas como Visual Studio, já que minha navegação é feita rapidamente pelo terminal para o projeto que irei mexer. Com isso o foco fica restrito a apenas uma coisa: o que você tem que fazer hoje? =)
