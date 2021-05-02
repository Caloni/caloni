---
date: "2018-07-14"
categories: [ "code", "draft",  ]
title: "Vcpkg: gerenciador de libs c++ para Linux, Mac OS... e Windows!"
---
O ambiente padronizado de bibliotecas C/C++ dos sistemas UNIX é motivo de inveja dos programadores Windows por séculos. Mas, finalmente, a Microsoft tem acordado diante da ressurreição do C++, com seus novos bug fixes e new deprecated features.

E com isso uma série de atividades têm permeada a evolução da ferramenta de desenvolvimento da Microsoft, o Visual Studio:

 - Updates frequentes
 - Projetos internos lançados como open source no GitHub
 - Compra do GitHub
 - Suporte a mais de um compilador (como clang)
 - Depuração Linux (Ubuntu) dentro do Windows
 - Ambiente Linux (Ubuntu) dentro do Windows
 - Pesado suporte ao CMake
 - Ambiente padronizado de bibliotecas para Windows, Linux e Mac OS (vcpkg)
 - Suporte à compilação de bibliotecas clássicas dos ambientes UNIX via vcpkg
 - Deploy de suas próprias bibliotecas padronizadas via vcpkg

Usar o vcpkg no Windows é tão simples que parece mágica. Ou Linux.

Para instalar você só precisa seguir o passo-a-passo do GitHub deles e usar PowerShell. O prompt PS faz tudo automático. O vcpkg é basicamente um conjunto de CMakes que fazem o serviço direito e conseguem compilar quase 1000 libs, a maioria nascidas no Linux, e integrar diretamente com projetos do VS2017.

Para provar todo o seu poder vamos usar a pior lib de todas: GTK.

O GTK não é apenas uma biblioteca, mas um conjunto de infinitas dependências. Há um tutorial gigantesco para compilar para Windows (defasado) e novos problemas surgem cada vez que alguém tenta utilizá-lo. Eu gastei mais de 40 horas para entender esses problemas compilando todas as dependências (estava em 95%) quando surgiu o vcpkg e jogou todos meus esforços no lixo (ainda bem).

Com o vcpkg tudo que é necessário fazer é rodar o comando de install com o nome da lib e toda a compilação é feita automaticamente. Depois disso, se não houver paths de include nos seus projetos do Visual Studio ele próprio irá levar em conta o path de instalação dessas libs (compilação e link). Parece mágica mesmo para quem passou décadas se matando para compilar alguma coisa que preste no Windows e que veio do Linux.

Vantagens do vcpkg:

 - Economia de tempo (de pesquisa, de compilação, de tudo)
 - Uniformidade no uso das libs
 - Flexibilidade para colocar suas próprias libs

Desvantagens do vcpkg:

 - Apenas as libs mais novas estão sendo suportadas (e não há suporte para Visual Studio mais antigo, nem SOs mais antigos como XP).
 - Usuário Linux nenhum no mundo vai querer usar (motivo: Microsoft e este já é um problema resolvido neste mundo)
 - Depende de um gerenciador proprietário (se bem que é tudo open source e não há restrições como o Java; qualquer um pode montar seu repositório).

