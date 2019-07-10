---
date: "2007-10-08"
title: História do Windows - parte 5.0
categories: [ "blog" ]
---
[![Windows 2000 Logo](..http://i.imgur.com/9rFlXJ1.png)](http://en.wikipedia.org/wiki/Windows_2000)**Windows 2000**

Em novembro de 1998 (apenas para parceiros Microsoft) é lançada a versão 5.0 do Windows NT, conhecida como Windows 2000. Melhorias significativas foram feitas no acesso à internet, intranet e extranet. Aplicações de gerenciamento se integram fortemente e a grande novidade em termos de estruturação de dados é o Active Directory, uma tecnologia compatível com o conceito de _Distributed File System_, que viabiliza uma nova forma das empresas organizarem seus dados de maneira mais transparente à rede.

Vamos aproveitar que a versão NT foi melhorada para dar uma recapitulada geral de como as coisas funcionam [internamente](http://compare.buscape.com.br/categoria?id=3482&lkout=1&kw=windows+internals+russinovich&site_origem=1293522) no sistema operacional.

#### Fazendo como Jack

A ilustração abaixo divide os módulos que fazem parte do sistema operacional. É importante sempre ter essa imagem indelével em nossa mente para entender como as coisas funcionam.

[![Windows Architecture](http://i.imgur.com/SHFTZIx.png)](http://en.wikipedia.org/wiki/Image:Windows_2000_architecture.svg)

É importante notar que essa distribuição já existia desde a primeira versão do NT, sendo que apenas alguns itens foram adicionados (como o Gerenciador de _Plug & Play_ e o Gerenciador de Energia).

> _Um outro item importantíssimo que foi movido da versão 3.51 para a 4.0 é a GDI, responsável pelo gráfico. Inicialmente ela estava no modo de usuário, mas a necessidade de aumentar o desempenho do sistema fez com que ela fosse [incorporada](http://www.windowsitpro.com/Articles/ArticleID/2469/2469/pg/2/2.html?Ad=1) ao núcleo do sistema._

Agora vamos dissecar as partes interessantes.

#### Aplicações Win32 | POSIX | OS/2

As aplicações que rodam sobre o sistema operacional preferencialmente são feitas para rodar no Windows. Mas não precisa ser assim. A abstração inicial que se fez foi o uso de subsistemas que suportam um ambiente de execução. Essa foi a maneira escolhida pelos projetistas para que existisse compatibilidade com outros sistemas operacionais, como o OS/2 e Posix (um padrão de aplicativo utilizado em ambientes Unix/Linux). A mesma abstração permite que se rodem aplicativos 16 bits em cima do ambiente NT, que é todo feito em 32.

#### Subsistemas Win32 | POSIX | OS/2

Os subsistemas são serviços do sistema operacional que fornecem o ambiente de execução adequado para cada tipo de aplicação. Quando o usuário executa um arquivo, o _loader_ do Windows detecta o tipo de aplicação tentando rodar e carrega o subsistema necessário. Dessa forma a execução de aplicativos MS-DOS e Windows 3.11 se torna transparente para o usuário. No entanto, as proteções necessárias (e.g. acesso a interrupções) serão respeitadas.

#### Subsistemas de integridade

Além dos subsistemas que irão fornecer os mecanismos necessários para a execução dos aplicativos dependendo de seu formato, existem aqueles subsistemas que tomam conta de alguns detalhes cruciais para a correta execução das tarefas do sistema operacional. Entre eles o mais importante é a parte de segurança, responsável por realizar o _login_ dos usuários.

#### Serviços do executivo

Isso basicamente é o conjunto de funções que estão disponíveis no modo de usuário para realizar operações mais complexas no núcleo do sistema, como leitura/escrita em arquivo, criação de _threads_, chamada direta de um _driver_, etc. Mais basicamente ainda, se trata de um vetor de ponteiros de funções que são chamadas em _kernel mode_ quando o modo de usuário chama uma interrupção ou comando em _assembly_ específico para realizar uma chamada de sistema.

#### Gerenciador de I/O

É um componente muito usado toda hora no sistema, pois ele trata de chamadas de leitura/escrita em qualquer dispositivo, seja um arquivo, uma porta serial ou uma placa de vídeo. Como conceitualmente as requisições do sistema operacional foram organizadas como operações de entrada e saída, o _I/O Manager_ é essencial para a maioria das operações com dispositivos, sejam físicos, lógicos ou virtuais.

#### Gerenciador de memória virtual

A memória virtual é parte integrante e indispensável para o desempenho e normal funcionamento do sistema operacional. Entre suas responsabilidades estão a necessidade de dividir a memória entre os diferentes processos de acordo com o uso e protegê-la contra leituras, escritas e execuções não autorizadas.

Parte integrante do Gerenciador de Memória, embora freqüentemente visto como um módulo separado por sua lógica, o Gerenciador de Cachê (_Cache Manager_) se concentra mais em estabelecer as diretizes usadas para paginar partes da memória para o disco e tornar a carregá-las na memória principal (RAM).

#### _Process Manager, PnP Manager_ e _Power Manager_

Possuem funções mais periféricas, mas não menos importantes. O Gerenciador de Processos cria novos processos e mantém a relação entre eles. O Gerenciador de PnP (_Plug and Play_), novo no Windows 2000, de um modo geral gerencia a adição e remoção de dispositivos que são plugáveis enquanto a máquina está ligada. O Gerenciador de Energia, também novo, teve sua importância aumentada com o advindo do uso massivo de _laptops_. É ele que controla coisas como a hibernação do sistema operacional.

#### _Object Manager_

O Gerenciador de Objetos também é parte central e obrigatória do sistema operacional, pois ele gerencia todos os recursos disponíveis tanto em _kernel_ quanto em _user mode _(espelhado pelo _kernel_). No Windows, qualquer recurso é representado por um objeto, seja um arquivo, uma _thread_, um processo, um evento, uma interrupção, etc. Sendo que tudo é representado como um objeto, esse módulo foi especialmente criado para gerenciar todos os recursos de uma vez. Dessa forma tipos de controle global, como o controle de acesso, pôde ser centralizado em apenas um lugar no código, assim como o gerenciamento de _handles_, que são manipuladores de recursos que existem em modo de usuário.

#### _Microkernel_

O _microkernel_ pode ser entendido como a parte que faz coisas muito básicas em um sistema operacional. Tão básicas quanto executar as _threads_, gerenciar interrupções e abstrair pequenas diferenças entre arquiteturas.

#### _Kernel mode drivers_

Faz par com o _microkernel_, e pode ser escrito pela Microsoft ou por fabricantes de dispositivos. São eles os responsáveis por controlar o _hardware_ que está atrás do sistema, como o disco, a porta serial, a rede, a placa de vídeo, a própria CPU, etc. Muitos podem ser lógicos, como os filtros e os _drivers_ de sistema de arquivos e, acredite se quiser, costumam ser mais complexos que os que controlam diretamente o _hardware_.

#### _Hardware Abstraction Layer _(_aka_ HAL)_
_

A HAL é totalmente dependente de plataforma. Por causa disso, ela é totalmente isolada do resto do sistema operacional, tornando a portabilidade mais fácil de ser suportada. Em alguns casos a HAL é implementada como um conjunto de macros, o que quer dizer que você terá que recompilar seus drivers para mudar de plataforma (x86 para x64, por exemplo). Além disso, existe um conjunto de DLLs compiladas para cada plataforma, que é renomeada (para hal.dll) e copiada durante a instalação. Isso explica porque em algumas situações se você copia a instalação do Windows de uma máquina para outra com diferenças relevantes de arquitetura pode ser que as coisas não saiam exatamente como você esperava.

#### _Hardware_

A não ser que estejamos falando do Xbox, o _hardware_ é feito por terceiros, como a Intel, a AMD e a NVIDIA, e é onde você instala o seu sistema operacional do coração para rodar seus aplicativos do coração. O bom de um sistema operacional do coração é que você não percebe sua existência quando está rodando seu jogo do coração. Pelo menos não deveria.

#### Para saber mais

	
  * [Outros artigos sobre a história do windows](http://www.caloni.com.br/blog/search/historia%20do%20windows%20-%20parte)

