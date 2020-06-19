---
categories: [ "code" ]
date: "2019-07-27"
tags: [ "draft",  ]
title: "tiodb"
---
Antigamente ele era conhecido apenas como tio, mas seu nome foi trocado para a nova modinha dos hubs com o sufixo db: são os chamados nosql. De qualquer forma, o tio, ou The Information Overlord (pesquise na web para ver se acha essa referência), começou com um núcleo e uma ideia muito simples que continuam até hoje, e que ainda é difícil de achar por aí: um servidor que mantém em memória contêineres STL disponíveis via socket em um protocolo simples. Este artigo irá explicar como baixar os fontes do servidor, compilar e acessar esses contêineres via telnet, o que possibilita a integração com virtualmente qualquer coisa que se comunique via socket.

Para executar as ações descritas abaixo você irá precisar de Visual Studio [1], Vcpkg [2] e CMake [3]. Os fontes do projeto oficial se encontram no GitHub [4]. A partir dele clone o repo localmente e entre pelo terminal na pasta server/tio.


A partir dessa pasta você irá construir o tiodb.exe, que é o único executável que você precisa compilar do projeto. Nele há um CMakeLists.txt e você irá precisa de algumas libs do boost compiladas. Então, por que não compilar todas elas? Se você não tiver o vcpkg, baixe-o do repositório do GitHub e compile seguindo as instruções do README. Tendo ele compilado basta mandar instalar os pacotes boost para x86.


Isso pode demorar. Hora do café.

Após o boost x86 instalado e sabendo que seu CMake está disponível no path, crie uma pasta para seu build, mova para ela pelo terminal e execute o seguinte comando:


Em seguida poderão haver problemas relacionados com o padrão C++ que eliminou a classe autoptr, por exemplo (mudar para uniqueptr) ou no Boost, que possui a dependência do módulo datetime não-especificado (esses problemas logo devem se resolver no repo oficial, mas no momento você pode obter essas mudanças no meu repo [5]).

Após configurado o ambiente via CMake em um mundo ideal tudo deve estar funcionando. Basta agora compilar o projeto em si.


O comando acima pode ser executado se você estiver com o ambiente do Visual Studio configurado em seu terminal. Outra opção, IDE friendly, é abrir o tiodb.sln e compilar pelo Visual Studio. De qualquer forma, se tudo der certo (novamente: em um mundo ideal) você deverá ter um executável em Debug\tiodb.exe. Basta executá-lo e ele irá abrir a porta 2605 em sua máquina e ficar escutando requisições.


Com o tio rodando você pode partir para o telnet, usando a ferramenta telnet disponível no SO ou alguma outra ferramenta de terceiro como Putty (no Windows). Vamos criar uma lista direto de lá e já demonstrar alguns comandos do protocolo texto.


Há comandos para criar contêineres, inserir itens, obter itens, etc. Para ser sincero, não imaginava que fosse tão complexo. Faz anos que mexo indiretamente com o tio e faz muito tempo que não abro um telnet. Fui olhar o código-fonte, mas a interpretação não é óbvia. Fui olhar a documentação, mas ainda assim não é muito clara [6] (nem fácil de achar).

Bom, essas foram as aventuras iniciais. A partir daí podemos explorar mais.

 - [1] https://visualstudio.microsoft.com/
 - [2] https://github.com/microsoft/vcpkg
 - [3] https://cmake.org/
 - [4] https://github.com/tiodb/tiodb
 - [5] https://github.com/Caloni/tiodb
 - [6] https://code.google.com/archive/p/tio/wikis/Protocol.wiki
