---
date: 2018-12-11T15:46:03-02:00
title: "A Maneira Errada de Começar um Projeto é com Visual Studio"
categories: [ "blog" ]
desc: "Como o encoding dos arquivos do template do Visual Studio cagam o próprio controle de fonte que a Microsoft recomenda."
---
Estava eu trabalhando com um sample e resolvi colocar controle de fonte para analisar as mudanças. E a mudança mais inesperada que eu vi quando digitei `git diff` foi que ele achou que meus arquivos de código-fonte estivessem em binário. Whaaat?

```
>git diff
>Binary files a/source.cpp and b/source.cpp differ
```

Essa lambança ocorreu com uma versão atual do Visual Studio 2017 após eu resolver ser preguiçoso e deixar o template dele criar o projeto para mim.

!

!

Particularmente não sou fã de deixar as IDEs criarem arquivos, porque geralmente elas estão cheias de más intenções disfarçadas de boas envolvendo alguma tecnologia proprietária. No caso da Microsoft há os precompiled headers, que sujam o projeto antes mesmo do tempo de compilação ser um problema. E agora descobri que os arquivos estão sendo gerados em UNICODE Windows.

```
>hxd source.cpp
```

!

## Correção

Se você tiver o mesmo problema e quiser corrigir segue o passo-a-passo: salve os arquivos com um encoding de gente grande (utf8, por exemplo). Fim do passo-a-passo.

!

Na prática, troque (possivelmente) disso:

!

Para isso:

!

A partir do segundo commit o git começará a entender que você atingiu a maioridade e vai comparar os arquivos como gente grande para você.

