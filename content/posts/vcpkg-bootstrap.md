---
date: "2019-11-29"
tags: [ "code", "draft",  ]
title: "Vcpkg: Bootstrap"
---
A versatilidade do vcpkg, gerenciador de pacotes multiplataforma da Microsoft, é permitir modificar tudo no projeto, desde código-fonte, pacotes instaláveis e a própria origem do repositório. Através do controle de fonte um vcpkg pode ser alimentado por diversas fontes, e por cada pacote existir em uma pasta separada permite a coexistência de várias versões e origens. Além disso, a forma de compilar os projetos e o código-base pode ser alterado exatamente da forma com que o projeto precisa.

Sabendo de tudo isso, a única coisa que você precisa em um projeto isolado é um script de bootstrap que baixe um repositório vcpkg customizado para o projeto, compile, instale os pacotes necessários e integre com o Visual Studio antes de iniciar a compilação do próprio projeto. Dessa forma é possível montar o ambiente de maneira automática e sanitizada para qualquer membro da equipe ou máquina de build.

Vejamos como seria um bootstrap.bat:


Com esse script na pasta raiz do seu projeto ele irá criar uma subpasta chamada vcpkg e após realizar as operações descritas acima integrar ao Visual Studio. Dessa forma quando for compilar o projeto os includes e libs já estarão disponíveis para que ele funcione, mesmo diretamente de uma máquina limpa.

Esse script pode ser integrado à lib principal do projeto ou o projeto da solution que primeiro deve compilar (porque todos dependem dele). Para isso existe o Pre-Build Event nas configurações de um projeto do Visual Studio. Os comandos que estiverem lá serão executados sempre antes da compilação.


O único passo não-descrito neste artigo é baixar o projeto e iniciar o build, tarefas triviais de integração.
