---
date: "2018-12-11"
tags: [ "code" ]
title: "A Maneira Errada de Começar um Projeto é com Visual Studio"
---
Estava eu trabalhando com um sample e resolvi colocar controle de fonte para analisar as mudanças. E a mudança mais inesperada que eu vi quando digitei git diff foi que ele achou que meus arquivos de código-fonte estivessem em binário.


Essa lambança ocorreu com uma versão atual do Visual Studio 2017 após eu resolver ser preguiçoso e deixar o template dele criar o projeto para mim.

Particularmente não sou fã de deixar as IDEs criarem arquivos, porque geralmente elas estão cheias de más intenções disfarçadas de boas envolvendo alguma tecnologia proprietária. No caso da Microsoft há os precompiled headers, que sujam o projeto antes mesmo do tempo de compilação ser um problema. E agora descobri que os arquivos estão sendo gerados em UNICODE Windows.



Se você tiver o mesmo problema e quiser corrigir segue o passo-a-passo: salve os arquivos com um encoding de gente grande como utf8. Fim do passo-a-passo.

Isso pode ser obtido na janela de "Save As" do Visual Studio. Há uma flecha para baixo do lado do botão Save onde você pode abrir a opção "Save with Encoding".

Na prática, troque possivelmente de "Unicode - Codepage 1200" para "Unicode (UTF-8 without signature) - Codepage 65001".  A partir do segundo commit o git começará a entender que você atingiu a maioridade e vai comparar os arquivos como gente grande para você.

A partir do segundo commit o git começará a entender que você atingiu a maioridade e vai comparar os arquivos como gente grande para você.
