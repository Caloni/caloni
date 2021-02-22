---
date: "2007-08-17"
title: "Junctions"
tags: [ "code" ]
---
Semana passada baixei uma nova imagem para minha máquina de desenvolvimento. Esse esquema do pessoal da engenharia instalar as coisas para você facilita muito as coisas, mas existe o risco de algo ser instalado no lugar errado, que foram os casos do DDK e do SDK do Windows. Aqui no desenvolvimento, para efeito de padronização, utilizamos a seguinte estrutura de diretórios para esses dois aplicativos:

    Library
    |- ddk
    |- legacy
    |- mssdk

Porém, por algum motivo desconhecido os instaladores da Microsoft não seguem o nosso padrão: o SDK é instalado em %programfiles%, Microsoft Platform SDK e o DDK em C:, WINDDK, 3790.1830. Para corrigir este pequeno ato relapso eu até poderia reinstalar ambos os aplicativos no local correto, gastanto algumas horas do dia, mas existe uma outra solução mais rápida e simpática chamada de junction.

Um junction é um link simbólico (symbolic link) de diretório. É praticamente um atalho, com a diferença que ele se comporta exatamente como se fosse o próprio objeto para o qual aponta: qualquer arquivo criado ou apagado usando o junction cria ou apaga um arquivo real no diretório real para o qual ele aponta. Essa característica pode ser tão útil quanto perigosa, por isso devem-se utilizar junctions com cuidado.

Para criar um junction pode-se usar uma ferramenta disponível no Windows Resource Kit chamada linkd.exe. Porém, para evitar de ter que baixar todo o pacote para usar um único arquivo, existe uma outra ferramenta desenvolvida à parte por Mark Russinovich chamada... junction. O comando para criar junctions é bem fácil e direto:

    junction c:\library\mssdk "path where is microsoft platform sdk"
    junction c:\library\ddk "path where is winddk"

E é isso aí. A partir de agora tanto as pastas originais quanto os junctions criados para elas respondem como se fossem a mesma coisa, porém com paths diferentes.

> "Neo, sooner or later, you're going to realize, just as I did, that there's a different between knowing the path... and walking the path..."

No Windows Vista os junctions também funcionam para arquivos e possuem seu próprio aplicativo nativo, o mklink.exe. Porém, ele chama os links para diretórios de junctions (em português, junções) e os links para arquivos de links mesmo. Você pode notar uma pequena gamb.. adaptação técnica ao mudarem o nome da pasta "Documents and Settings" para "Users" (ou "Usuários", na versão em português). Esse link é extremamente necessário para a compatibilidade daqueles aplicativos feitos às pressas que não se importam em perguntar para o sistema onde está a pasta de documentos do usuário, fixando o path como se ele fosse estar sempre lá.
