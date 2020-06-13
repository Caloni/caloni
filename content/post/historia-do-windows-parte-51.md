---
categories: [ "code" ]
date: "2007-11-19"
tags: [ "draft",  ]
title: "História do Windows - parte 5.1"
---
Chega às lojas no dia 25 de outubro de 2001 a unificação entre as plataformas de uso doméstico e corporativo do sistema. O Windows XP usa o kernel de 32 bits de seus antecessores Windows NT e Windows 2000. É vendido em duas edições: Home e Professional Edition. O design do sistema foi totalmente remodulado para suportar ao mesmo tempo a facilidade de uso do usuário doméstico e a robustez e confiabilidade dos clientes corporativos.

Do ponto de vista da arquitetura, pouca coisa mudou, e essa versão mudou internamente de 5.0 (Windows 2000) para 5.1 (Windows XP) . Ou seja, praticamente um patch de correção.

Agora, além do sistema 32 bits que todos já conheciam, é lançada a primeira versão 64 bits do Windows, o Windows XP 64-bit Edition. Na época a Intel se preparava para o fracasso de mercado que foi o Intel IA-64 e esse Windows suportava essa nova arquitetura. Na verdade, o projeto foi além das expectativas e aplicou sua primeira versão do Windows-on-Windows 64-bit (WOW64), que permitia a execução de aplicativos 32 bits (x86) em cima da nova plataforma. Isso era feito pela tradução literal do código do assembly "antigo" para o assembly novo, além de outras técnicas auxiliares.

Atualmente essa versão do Windows não é mais suportada.

Como se tornou uma prática desde os tempos do Windows NT, a versão para servidores é sempre lançada algum tempo depois da versão para estações de trabalho. Assim foi com o Windows NT Server, o Windows 2000 Server e agora com o Windows XP, rebatizado em sua versão servidores para Windows 2003 Server, cujo código é uma evolução do XP original.

Da mesma forma, com o lançamento da versão 64 para a plataforma x86, uma nova versão do Windows foi criada: a Windows XP Professional x64 Edition. Baseada no código do Windows 2003 Server SP1, essa nova versão se aproveitava da compatibilidade do x86-64 com a velha plataforma e otimizava a interação e execução dos velhos aplicativos 32, usando uma versão melhorada do WOW64, que se aproveitava da possibilidade de ficar trocando entre os modos 32 e 64 durante a execução dos aplicativos.

No decorrer da história do Windows avançamos uns bons 20 anos até agora. Muita coisa que deveria ter sido falada não foi, e muita coisa que não merecia ser mencionada, foi. Abaixo podemos vislumbrar por onde passamos, onde chegamos e para onde vamos.

Como podemos ver, não falarei mais aqui sobre a "outra ramificação" do Windows , aquela constituída por Windows 95, 98 e ME. Não falarei do processo antitruste contra a Microsoft por conta da venda do sistema operacional com o Internet Explorer e Media Player embutidos; não discursarei sobre os protestos dos consumidores quando a Microsoft cobrou pela versão de atualização do Windows 98, o Second Edition; muito menos esbravejarei sobre a raiva dos usuários pelo superaquecimento do processador por conta do Windows ME e sua duvidável interface revolucionária.

Pelo contrário. Acho que é uma boa hora para adentrar mais ainda nas entranhas da arquitetura NT e entender algumas coisas até então pouco exploradas.

Na eterna briga entre sistemas operacionais, uma categoria bem abastada (principalmente as discussões Tanenbaum x Torvalds) diz respeito aos sistemas monolíticos e aos baseados em microkernel. Basicamente os sistemas monolíticos possuem todo o seu código executando em modo privilegiado, inclusive os device drivers. Nos sistemas baseados em microkernel, no entanto, existe apenas uma fina camada de interface rodando em modo privilegiado, que serve de interação entre todos os serviços, driver e aplicativos e o hardware.

O problema em si não é a organização dos componentes do sistema operacional em torno de um ou de outro design, mas o que isso implica em termos de eficiência.

Abaixo podemos ver o esboço do que seria um sistema operacional com kernel monolítico, com todos acessando todos em modo kernel:

Ao ser projetado, o objetivo do Windows nunca foi ser um sistema operacional de microkernel, embora umas boas almas tenham clamado o contrário. No entanto, a organização monolítica acima foi feita de tal forma que uma visão lógica do sistema operacional nos diria que a tentativa original foi dividir os serviços em camadas e componentes (servidores), de forma que as camadas superiores pudessem confiar nos serviços das camadas inferiores, tal como é em uma pilha TCP/IP.

Porém, as coisas não são tão simples assim. O SO inteiro não é feito dessa forma. Foram usados diversos modelos para a organização do sistema, e é fácil perceber isso se enxergamos o todo através de várias visões.

A visão acima, o caos, é o que temos quando só pensamos em módulos acessando módulos e código arbitrário rodando em kernel mode. Contudo, abaixo, por exemplo, podemos ver o resultado lógico da divisão em camadas em um kernel monolítico. Existe organização, embora esta esteja toda em código privilegiado.

O acesso, porém, não é protegido, e eventuamente vão existir existir diversos atalhos (documentados ou não) para alcançar as coisas de maneira mais rápida, para o bem da velocidade.

Uma última e terceira visão, baseada em componentes, divide o código em gerenciadores e provedores de serviços. Conceitualmente  essa divisão permitiria a migração de todo o código não-crítico para user mode, embora não seja o que ocorre.

Essa divisão foi feita inicialmente e mantida apenas para serviços não-críticos que pudessem rodar em código não-privilegiado e a manutenção dos subsistemas: Win32, POSIX, MS-DOS. Nessa última visão conseguimos ainda visualizar um microkernel, mas é importante notar que não estamos falando aqui do conceito puro e formal que definimos no início da explicação.

O esboço final, dessa forma, ficou sendo um sistema operacional dividido em componentes, com a maioria rodando em modo privilegiado (kernel mode), cuja divisão lógica primária tende a ser em camadas. É muito importante ter essa visão da coisa conforme nos aprofundamos nos mistérios do ring0.

Para a organização dos recursos do sistema foi adotado um outro modelo, semelhante (embora não seja) ao conceito de orientação a objetos. Nesse modelo, os recursos são organizados em entidades identificáveis em sua maioria por um ponteiro opaco (kernel) ou um identificador, chamado de handle (user mode). Todos os recursos recebem o mesmo tratamento, embora se refiram a coisas extremamente diferentes, como um arquivo, uma porta de rede, um pedaço de memória, um processo e uma janela.

Essa organização foi adotada principalmente pela sua grande vantagem de minimizar mudanças, uma vez que as informações sobre os recursos são armazenadas em estruturas opacas, isto é, elas existem, porém não são acessíveis a todos. Isso permite que elas sofram mudanças internas no decorrer do tempo sem impactar para seus usuários.

	
  * Artigos sobre a história do Windows no Caloni.com.br

