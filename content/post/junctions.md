---
date: "2007-08-17"
title: Junctions
categories: [ "blog" ]
---
Semana passada baixei uma nova imagem para minha máquina de desenvolvimento. Esse esquema do pessoal da engenharia instalar as coisas para você facilita muito as coisas, mas existe o risco de algo ser instalado no lugar errado, que foram os casos do DDK e do SDK do Windows. Aqui no desenvolvimento, para efeito de padronização, utilizamos a seguinte estrutura de diretórios para esses dois aplicativos:

[![Diretórios de bibliotecas](http://i.imgur.com/zGUkifG.png)](/images/library-directories.png)

Porém, por algum motivo desconhecido os instaladores da Microsoft não seguem o nosso padrão: o SDK é instalado em "**%programfiles%\Microsoft Platform SDK**" e o DDK em "**C:\WINDDK\3790.1830**". Para corrigir este pequeno ato relapso eu até poderia reinstalar ambos os aplicativos no local correto, gastanto algumas horas do dia, mas existe uma outra solução mais rápida e simpática chamada de _junction_.

**Atalhos simbólicos**

Um _junction_ é um _link_ simbólico ([_symbolic link_](http://msdn2.microsoft.com/en-us/library/aa365680.aspx)) de diretório. É praticamente um atalho, com a diferença que ele se comporta exatamente como se fosse o próprio objeto para o qual aponta: qualquer arquivo criado ou apagado usando o _junction_ cria ou apaga um arquivo real no diretório real para o qual ele aponta. Essa característica pode ser tão útil quanto perigosa, por isso devem-se utilizar _junctions_ com cuidado.

Para criar um _junction_ pode-se usar uma ferramenta disponível no [Windows Resource Kit](http://support.microsoft.com/?kbid=205524) chamada **linkd.exe**. Porém, para evitar de ter que baixar todo o pacote para usar um único arquivo, existe uma outra ferramenta desenvolvida à parte por Russinovich chamada [junction.exe](http://www.microsoft.com/technet/sysinternals/FileAndDisk/Junction.mspx). O comando para criar _junctions_ é bem fácil e direto:

**junction c:\library\mssdk "c:\program files\microsoft platform sdk"
junction c:\library\ddk c:\winddk**

E é isso aí. A partir de agora tanto as pastas originais quanto os _junctions_ criados para elas respondem como se fossem a mesma coisa, porém com _paths_ diferentes.

> _"Neo, sooner or later, you're going to realize, just as I did, that there's a different between knowing the path... and walking the path..."_

**_Junctions _no Windows Vista**

No Vista os _junctions _também funcionam para arquivos e possuem seu próprio aplicativo nativo, o **mklink.exe**. Porém, ele chama os _links_ para diretórios de _junctions_ (em português, junções) e os _links_ para arquivos de _links_ mesmo. Você pode notar uma pequena gamb.. adaptação técnica ao mudarem o nome da pasta "Documents and Settings" para "Users" (ou "Usuários", na versão em português).

[![Junctions no Windows Vista](http://i.imgur.com/vr7MHeY.png)](/images/documents-and-settings-vista.png)

Esse _link_ é extremamente necessário para a compatibilidade daqueles aplicativos feitos às pressas que não se importam em [perguntar para o sistema](http://msdn2.microsoft.com/en-us/library/ms647814.aspx) onde está a pasta de documentos do usuário, fixando o _path_ como se ele fosse estar sempre lá.

	
  * [Lista dos _junctions_ do Vista e explicações mais detalhadas e técnicas](http://www.svrops.com/svrops/articles/jpoints.htm).

