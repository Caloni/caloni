---
date: "2007-10-08"
tags: [ "code" ]
title: "História do Windows - parte 5.0"
---
Em novembro de 1998 (apenas para parceiros Microsoft) é lançada a versão 5.0 do Windows NT, conhecida como Windows 2000. Melhorias significativas foram feitas no acesso à internet, intranet e extranet. Aplicações de gerenciamento se integram fortemente e a grande novidade em termos de estruturação de dados é o Active Directory, uma tecnologia compatível com o conceito de Distributed File System, que viabiliza uma nova forma das empresas organizarem seus dados de maneira mais transparente à rede. Assim começou a [História do Windows] para redes de gente grande.

![Windows 2000 Logo](/img/windows_2000.png)

Vamos aproveitar que a versão NT foi melhorada para dar uma recapitulada geral de como as coisas funcionam internamente no sistema operacional. Em um desenho da arquitetura veremos diferentes módulos que fazem parte do sistema operacional que dividem funções específicas e que possuem métodos específicos de comunicação interna e externa. Importante notar que a divisão entre os componentes que descreverei abaixo já existia desde a primeira versão do NT, sendo que apenas alguns itens foram adicionados, como o Gerenciador de Plug & Play e o Gerenciador de Energia. Os elementos principais do Windows, visto sob camadas de abstração, são:

 - Aplicações Win32, POSIX, OS/2;
 - Subsistemas Win32, POSIX, OS/2;
 - Subsistemas de integridade;
 - Serviços do Executivo (em inglês Executive Services);
 - Gerenciador de I/O ou I/O Manager;
 - Gerenciador de Memória Virtual ou VMM, o Virtual Memory Manager;
 - Process Manager, PnP Manager e Power Manager;
 - Object Manager;
 - Microkernel;
 - Kernel mode drivers;
 - Hardware Abstraction Layer (aka HAL);
 - Por fim, o hardware.

![Windows Architecture](/img/windows_architecture.png)

> Um outro item importantíssimo que foi movido da versão 3.51 para a 4.0 é a GDI, responsável pelos gráficos. Inicialmente ela estava no modo de usuário, mas a necessidade de aumentar o desempenho do sistema fez com que ela fosse incorporada ao núcleo do sistema.  Agora vamos dissecar as partes interessantes.

As aplicações, ou programas, que rodam sobre o sistema operacional preferencialmente são feitas para rodar no Windows, mas não precisa ser assim. A abstração inicial que se fez foi o uso de subsistemas que suportam um ambiente de execução. Essa foi a maneira escolhida pelos projetistas para que existisse compatibilidade com outros sistemas operacionais, como o OS/2 e POSIX (um padrão de aplicativo utilizado em ambientes UNIX/Linux). A mesma abstração permite que se rodem aplicativos 16 bits em cima do ambiente NT, que é todo feito em 32.

Os subsistemas de compatibilidade são serviços do sistema operacional que fornecem o ambiente de execução adequado para cada tipo de aplicação. Quando o usuário executa um arquivo, o loader do Windows detecta o tipo de aplicação tentando rodar e carrega o subsistema necessário. Dessa forma a execução de aplicativos MS-DOS e Windows 3.11 se torna transparente para o usuário. No entanto, as proteções necessárias (e.g. acesso a interrupções) serão respeitadas. Além dos subsistemas que irão fornecer os mecanismos necessários para a execução dos aplicativos dependendo de seu formato, existem aqueles subsistemas que tomam conta de alguns detalhes cruciais para a correta execução das tarefas do sistema operacional. Entre eles o mais importante é a parte de segurança, responsável por realizar o login dos usuários.

Os chamados Serviços do Executivo basicamente são o conjunto de funções que estão disponíveis no modo de usuário para realizar operações mais complexas no núcleo do sistema, como leitura/escrita em arquivo, criação de threads, chamada direta de um driver, etc. Mais basicamente ainda, se trata de um vetor de ponteiros de funções que são chamadas em kernel mode quando o modo de usuário chama uma interrupção ou comando em assembly específico para realizar uma chamada de sistema.

O I/O Manager é um componente muito usado toda hora no sistema, pois ele trata de chamadas de leitura/escrita em qualquer dispositivo, seja um arquivo, uma porta serial ou uma placa de vídeo. Como conceitualmente as requisições do sistema operacional foram organizadas como operações de entrada e saída, o I/O Manager é essencial para a maioria das operações com dispositivos, sejam físicos, lógicos ou virtuais.

A memória virtual é parte integrante e indispensável para o desempenho e normal funcionamento do sistema operacional. Entre suas responsabilidades estão a necessidade de dividir a memória entre os diferentes processos de acordo com o uso e protegê-la contra leituras, escritas e execuções não autorizadas. Parte integrante do Memory Manager, embora freqüentemente visto como um módulo separado por sua lógica, o Gerenciador de Cachê, em inglês Cache Manager, se concentra mais em estabelecer as diretizes usadas para paginar partes da memória para o disco e tornar a carregá-las na memória principal (RAM).

O Process Manager, PnP Manager e Power Manager possuem funções mais periféricas, mas não menos importantes. O Process Manager cria novos processos e mantém a relação entre eles. O PnP (Plug and Play) Manager, novo no Windows 2000, gerencia a adição e remoção de dispositivos que são plugáveis enquanto a máquina está ligada. O Gerenciador de Energia, também novo, teve sua importância aumentada com o advindo do uso massivo de laptops. É ele que controla coisas como a hibernação do sistema operacional, por exemplo.

O Gerenciador de Objetos, o Object Manager, também é parte central e obrigatória do sistema operacional, pois ele gerencia todos os recursos disponíveis tanto em kernel quanto em user mode (espelhado pelo kernel). No Windows, qualquer recurso é representado por um objeto, seja um arquivo, uma thread, um processo, um evento, uma interrupção, etc. Sendo que tudo é representado como um objeto, esse módulo foi especialmente criado para gerenciar todos os recursos de uma vez. Dessa forma tipos de controle global, como o controle de acesso, pôde ser centralizado em apenas um lugar no código, assim como o gerenciamento de handles, que são manipuladores de recursos que existem em modo de usuário.

O microkernel pode ser entendido como a parte que faz coisas muito básicas em um sistema operacional. Tão básicas quanto executar as threads, gerenciar interrupções e abstrair pequenas diferenças entre arquiteturas. Os drivers em kernel mode fazem par com o microkernel, e podem ser escrito pela Microsoft ou por fabricantes de dispositivos. São eles os responsáveis por controlar o hardware que está atrás do sistema, como o disco, a porta serial, a rede, a placa de vídeo, a própria CPU, etc. Muitos podem ser lógicos, como os filtros e os drivers de sistema de arquivos e, acredite se quiser, costumam ser mais complexos que os que controlam diretamente o hardware.

A HAL, Hardware Abstraction Layer, ou Camada de Abstração de Hardware, é totalmente dependente de plataforma, e justamente por causa disso ela é totalmente isolada do resto do sistema operacional, tornando a portabilidade mais fácil de ser suportada. Em alguns casos a HAL é implementada como um conjunto de macros, o que quer dizer que você terá que recompilar seus drivers para mudar de plataforma (x86 para x64, por exemplo). Além disso, existe um conjunto de DLLs compiladas para cada plataforma, que é renomeada (para hal.dll) e copiada durante a instalação. Isso explica porque em algumas situações se você copia a instalação do Windows de uma máquina para outra com diferenças relevantes de arquitetura pode ser que as coisas não saiam exatamente como você esperava.

E por fim, a não ser que estejamos falando do XBox, o hardware é feito por terceiros, como a Intel, a AMD e a NVIDIA, e é onde você instala o seu sistema operacional do coração para rodar seus aplicativos do coração. O bom de um sistema operacional do coração é que você não percebe sua existência quando está rodando seu jogo do coração. Pelo menos não deveria. O único momento que o sistema operacional do coração revela sua existência é quando as coisas dão errada e você recebe uma tela azul do coração.

[História do Windows]: /historia-do-windows
