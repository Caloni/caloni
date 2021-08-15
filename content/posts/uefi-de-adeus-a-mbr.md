---
categories:
- blog
date: '2017-02-09'
tags:
title: 'UEFI: dê adeus à MBR'
---

Após depurar a BIOS e a MBR, eis que surge a UEFI: os GUIDs para SOs instalados no seu HD. Quantas siglas, não é mesmo?

A BIOS (Basic Input/Output System, Sistema Básico de Entrada e Saída) é o sistema-base que se comunica com o hardware diretamente e faz a ponte entre várias interrupções e o sistema operacional (se houver um). Uma das funções iniciais da BIOS era encontrar qual a MBR (Master Boot Record, Registro do Boot Mestre) válida para entregar o controle de um pedaço de código de 512 bytes (um pouco menos) cuja função clássica era procurar em uma tabela de quatro entradas dentro dela mesma qual o SO que está ativo. A partir daí o código da MBR passava o controle para a MBR da partição ativa, que deveria conter o bootstrap do sistema operacional (naquela época bootstrap significava outra coisa).

Isso gerava várias confusões em um sistema multi-SO, algo que começou a se tornar constante depois que o Linux e o Windows de verdade (NT) veio à tona, com gerenciadores de boot no próprio SO que possibilitava que o Windows 98 conseguisse pular seu controle para um Windows NT ou 2000 e também para um Conectiva Linux. Quando as coisas davam errado era só pegar o CD de instalação de um desses e começar tudo de novo.

Ou usar o Disk Editor, a famigerada ferramenta do Norton que já salvou a vida de muitos computadores aí afora. Eu me incluo na lista de salvadores durante o tempo que fiz a manutenção de um sistema de criptografia de HD. Usar o Disk Editor era basicamente navegar pelos bytes iniciais do HD principal para encontrar qual lógica do boot estava errada. Poderia ser um erro na tabela de partições ou um modo de endereçamento que não suportava partições muito longe do início (a tabela de partições era bem limitada; abaixo ela está selecionada).

Com a UEFI (Unified Extensible Firmware Interface, Inteface de Firmware Extendido Unificado) a MBR e seus 500 bytes perdem sua vez e no lugar surge uma partição inteira, onde os SOs são organizados não por tipos de entrada, mas por GUIDs únicos (números muito grandes que em teoria não são repetidos nunca). Não há mais a chance de modificar os bytes iniciais do boot para poder realizar alguma manipulação mágica, como gerenciar os diferentes SOs. A UEFI foi feita para isso, e não apenas para SOs locais, mas qualquer tipo de extensão de firmware (o código que reside direto no hardware e manipula correntes e leds). Note como a tabela de partições em um ambiente EFI não possui entradas válidas, e o setor logo em seguida é o início de sua partição.

A UEFI diz que há suporte ao modo antigo MBR. Isso é feito mantendo o primeiro setor disponível para escrita. Uma conversão possível seria editar a tabela de partições inserindo onde está a partição de um SO e inserindo um código padrão do MBR no lugar. A mudança do tipo de boot pode ser feito na BIOS (é o modo legado), mas se for trocada ela usará a MBR para bootar, então é necessário que ela esteja funcionando.
