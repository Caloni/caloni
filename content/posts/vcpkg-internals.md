---
categories: [ "code" ]
date: "2018-09-12"
tags: [ "draft",  ]
title: "Vcpkg Internals: como o gerenciador de pacotes da M$ funciona por dentro (e como fazer seu próprio pacote!)"
---
Depois de entender mais ou menos como funciona o vcpkg é hora de realmente entrar no código e entender qual a grande sacada dessa ferramenta da Microsoft.

Uma das formas mais divertidas de entender o funcionamento de um fonte é compilar e sair depurando. E foi o que eu fiz. Através dos step ins e step outs foi possível ter as primeiras impressões de em qual pé está o projeto, além de pegar boas ideias para meu próprio código.

Por exemplo, no começo do programa encontrei uma saída simples e eficaz de como tratar entrada e saída (ou só saída) de dentro de um terminal:


Com tudo UTF-8 a vida fica mais fácil.

Outro ponto interessante é que o fonte é muito C++ moderno, com direito a inclusive usar headers ainda experimentais, como o filesystem (C++ 17). Ele usa também um conjunto de paths sobre onde estão as coisas (instalação, pacotes, etc). Há muito código no vcpkg que são módulos independentes que soam como retrabalho de coisas comuns, como parseamento de argumentos, mas o objetivo do projeto é ser independente de tudo. Do contrário ele não seria um bom gerenciador de pacotes.

O arquivo vcpkg\installed\vcpkg\status contém em formato texto simples o status de todos os pacotes instalados (se foi instalado com sucesso ou não, etc). A pasta vcpkg\ports contém todos os pacotes, instalados ou não. O início de tudo é o executável na pasta-raiz após compilado, vcpkg.exe, feito em C++ e que realiza todas as bruxarias para montar a hierarquia de pastas e arquivos em texto. Tudo é tão simples e baseado em arquivos de texto que vejo que a M$ finalmente se rendeu ao jeito unix de fazer as coisas (mais conhecido como o jeito certo).

No gerenciador de pacotes há um conceito chamado de triplet, que não é uma novidade; é uma forma de especificar um conjunto de elementos do ambiente para cross compiling utilizando um simples nome.


O vcpkg já vem com alguns triplets de fábrica, mas você pode criar os seus próprios na pasta triplets, alterando várias variáveis de controle de compilação:

 - VCPKG_TARGET_ARCHITECTURE. A arquitetura alvo (x86, x64, arm, arm64).
 - VCPKG_CRT_LINKAGE. A linkagem do CRT (que é mais conhecida pelo pessoal do Zwindows; valores: dynamic, static).
 - VCPKG_LIBRARY_LINKAGE. O mesmo do CRT, mas para libs (as bibliotecas podem ignorar se elas não suportam isso).
 - VCPKG_CMAKE_SYSTEM_NAME. A plataforma alvo, que pode ser vazio (o Windows desktop padrão), WindowsStore, Darwin (Mac OSX) ou Linux.
 - VCPKG_PLATFORM_TOOLSET. O toolset do Visual Studio (mais uma coisa do Zwindows); v141, v140 são valores válidos (vazio também).
 - VCPKG_VISUAL_STUDIO_PATH. Onde está a instalação do Visual Studio (é, o vcpkg tem uma certa tendência pro Zwindows).
 - VCPKG_CHAINLOAD_TOOLCHAIN_FILE. Esse não é do Zwindows, mas do CMake; a possibilidade de escolher outro toolchain (diferente de scripts/toolchains) para o CMake.

Há diversas flags de compilação que podem ser especificadas direto no triplet:

 - VCPKG_CXX_FLAGS_DEBUG
 - VCPKG_CXX_FLAGS_RELEASE
 - VCPKG_C_FLAGS
 - VCPKG_C_FLAGS_DEBUG
 - VCPKG_C_FLAGS_RELEASE

A macro do CMake PORT será interpretada pelo triplet. Isso é uma garantia de mudanças nos settings para portabilidade. Por exemplo:


Que compila qualquer coisa que entre no match "qt5-*" como dinâmico (DLLs), embora todo o resto possa ser estático.

A integração com o Visual Studio ocorre com o uso daqueles pedaços de configuração de projetos que são as abas de propriedades. Você mesmo pode criar abas de propriedade como arquivos separados do seu vcxproj para configurações comuns a mais projetos.

Para realizar a integração o comando é vcpkg integrate install":


Note que as coisas para quem usa CMake são automáticas e fáceis de usar. Basta acrescentar o toolchain especificado. Já para Visual Studio...

O mecanismo envolve uma pasta do msbuild:


Dentro dessa pasta é colocado um desses pedaços de configuração (propriedades) chamado vcpkg.system.props.


Essa diretiva usa a pasta definida pela variável de ambiente LOCALAPPDATA (geralmente C:\Users\<seu-usuario>\AppData\Local) para localizar um outro arquivo, o vcpkg.user.targets.


No exemplo estou usando um vcpkg disponível na pasta c:\libs (que é basicamente um clone do repositório GitHub do vcpkg). Note que ele inclui automaticamente nos projetos do Visual Studio um target dentro dele, o vcpkg\scripts\buildsystems\msbuild\vcpkg.targets. Vejamos o que tem nele:


Note como as pastas de instalação dos pacotes do triplet selecionado são incluídas na configuração de um projeto do Visual Studio. As libs ficam na subpasta installed/triplet/lib, os binários em installed/triplet/bin, os includes em installed/triplet/include e assim por diante. A ramificação dos pacotes está de acordo com o basename de cada um deles.

A mágica ocorre já na hora de dar include. E é mágica desde o autocomplete até o link. Por exemplo, digamos que vamos fazer um embedded de Python usando o exemplo do help:


O programa compila e linka. Para provar que ele usa a lib instalada (versão debug):



Se você prestou atenção ao conteúdo de msbuild\vcpkg.targets lá em cima vai ter visto que há uma condição que adiciona toda e qualquer lib como dependência adicional ao projeto compilando:


É isso que resolve o problema de saber qual o nome da lib resultante de um pacote instalado. Porém, isso não é o ideal, principalmente por dois motivos:

 1. Os nomes de configuração do projeto tem que ser Debug ou Release (maneiras de melhorar já está sendo discutido no GitHub).
 2. O usuário final não tem qualquer controle do que adicionar como dependência; simplesmente vai todos os pacotes instalados (mais uma discussão no GitHub).

Porém, no momento é assim que funciona. Para o problema #1 a solução paliativa é o próprio usuário adicionar em seu msbuild as condições de sua configuração. A sugestão da thread é boa:


Pelo menos tudo que começar com Debug (ou Release) já entraria no filtro.

UPDATE: Essa sugestão já foi adicionada à última versão do vcpkg. É feita uma normalização do nome:


Assim o que seguir é Debug ou Release =).

Um outro potencial problema dos usuários de Visual Studio para compilar e rodar projetos C++ são as dependências de binários (DLLs). É possível que um pacote seja compilado de maneira dinâmica, ou seja, com DLLs de dependência. Essas DLLs na instalação do pacote devem constar na pasta bin, mas por conta dessa pasta não fazer parte dos diretórios de sistema o depurador do Visual Studio irá carregar um executável em sua pasta de geração em que não encontrará as eventuais DLLs que ele precisa para rodar.

Para "corrigir" isso, ou melhor dizendo, contornar a experiência, também foi adicionado um comando Post Build no vcpkg.targets com um comando Power Shell que copia esses binários para a pasta de geração do projeto atual. Dessa forma o projeto pode rodar sem problemas, o usuário fica feliz e consegue terminar sua programação antes de passar para o deploy (e facilita deploys de testes, pois basta copiar a pasta de geração do executável que todas suas dependências estarão lá).


O script executado pelo PowerShell fica em vcpkg\scripts\buildsystems\msbuild e recebe o TargetPath (o binário-alvo) como parâmetro e onde estão os binários instalados pelo vcpkg, e com base na saída da ferramenta dumpbin extrai as dependências do executável e as busca no diretório bin:


Isso é o equivalente ao uso padrão de dumpbin com grep e sed:


A cópia dos binários é feito com um teste simples de "path existe" com deploy:


Fato curioso: no script do PowerShell existem alguns hacks para alguns pacotes, incluindo Qt.

O uso do CMake permite aos usuários do vcpkg ter boas ideias apenas lendo os scripts do projeto. Se você abrir o solution vcpkg.sln dentro de toolsrc vai descobrir todos os scripts listados por lá. Há funções espertinhas como o download e extração de pacotes 7zip do Source Forge.

Essa parte fica em vcpkg/scripts/cmake. Olhe, por exemplo, como retornar a versão do Windows SDK (vcpkggetwindowssdk.cmake):


Assim como o esquema de triplets, tudo pode ser atualizado conforme o gosto do freguês, adicionando funções e configurações úteis em seu clone do repositório, e feitas atualizações com a versão oficial.

O vcpkg não é apenas um ecossistema de libs compiladas e instaladas em uma pasta para serem usadas localmente. Pode ser um caminho simples e rápido para você conseguir compilar libs conhecidas e entregar para um terceiro um zip com todos os includes, libs e dependências do seu projeto.


Para trabalhar em equipe é vital que todos falem a mesma língua. Uma das formas disso acontecer é usar um gerenciamento de pacotes que inclua todos os ambientes que a equipe usa. Como geralmente esses ambiente não são os mesmos, o uso de pacotes próprios do vcpkg é um plus da ferramenta que vem para somar em padronização de fontes e compilação.

Primeiro de tudo é interessante existir um local público de download dos fontes (caso o projeto seja opensource; se bem que é possível que o endereço seja apenas visível para usuários logados ou outro mecanismo de proteção).

Uma estrutura simples de lib que compila com CMake, por exemplo, deverá conter alguns arquivos mínimos:


Um .cpp com a implementação, um .h público para o usuário acessar, uma licença de uso (LICENSE) e um arquivo CMakeLists.txt são o suficiente para demonstar o uso. Dentro do CMakeLists.txt temos as seguintes diretivas:


A partir de um zip na internet da pasta bitforge já é possível começar a montar seu próprio pacote:


Dica: você pode também testar ou implantar isso localmente usando Python:


O arquivo portfile.cmake já possui teoricamente tudo o que precisa para falhar. Há alguns caveats que podem te dar bastante dor de cabeça no começo. Por isso mesmo eu vou economizar algum tempo para você.

Em primeiro lugar, preste atenção no diretório onde estarão os fontes. É costume do template usar o mesmo nome do zip, o que nem sempre é verdade (aqui não é, não existe versão no nome da pasta zipada):

Então em vez de:


Isso:


O erro que deve acontecer na falta dessa mudança é o seguinte:


Em segundo lugar, a cópia do header é feita tanto em release quanto em debug. A compilação via vcpkg irá te avisar que tem alguma coisa errada pois está duplicado, mas já há uma linha mágica que pode ser adicionada:


O erro que deve acontecer na falta dessa mudança é o seguinte:


E por último, é obrigatório ter um arquivo de copyright, no caso o nosso LICENSE do projeto. O portfile.cmake já tem o comando, mas está comentado:


O erro que deve acontecer na falta dessa mudança é o seguinte:


Basicamente isso é o que você precisa para começar a construir seu pacote:


O próximo passo é instalar:


E voilá! Agora o include está disponível, as funções estão disponíveis, o link está funcionando e seu pacote pode ser compartilhado com toda a empresa. Basta copiar a pasta ports/bitforge ou adicioná-la no repositório por um commit.
