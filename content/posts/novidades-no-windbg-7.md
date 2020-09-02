---
date: "2010-04-01"
tags: [ "code", "draft",  ]
title: "Novidades no Windbg 7"
---
Semestre que vem deve sair uma nova versão do nosso depurador favorito. Alguns atrasos e novas definições do projeto fizeram com que tivéssemos mais um ou dois releases da finada versão 6 antes da revolução que será o Depurador 2010.

Entre as mudanças mais esperadas, e entre as mais inesperadas, encontramos essa pequena lista de novidades que, com certeza, deixarão o desenvolvedor de sistemas da Microsoft muito mais feliz:

Hoje em dia é um trabalho um pouco tedioso encontrar qual dos drivers possuía a memória de endereço 0xB8915423, mas agora, juntando o interpretador de símbolos internos e o sistema de tooltips do Windbg, será possível passar o mouse sobre um endereço qualquer e ele mostrará imediatamente quem possui a memória, como ela foi alocada e qual seu conteúdo.

Isso só é possível, é claro, com os símbolos corretamente carregados. Algo não muito difícil se você seguir as recomendações de John Robbins. E é uma mão na roda na hora de dar um feedback instantâneo para o suporte técnico quando der uma tela azul.

Sim! Agora se o ddkbuild  estiver no path do WinDbg e você editar o código-fonte do seu driver durante a depuração (na próxima versão a visualização não será apenas read-only) e der um step-into, automaticamente o depurador irá perguntar se deseja recompilar o projeto. Depois de ativar o processo de build, através das conexões serial/firewire/usb-debug, a nova imagem irá parar diretamente na memória kernel da máquina target.

Algumas ressalvas são colocadas pela equipe da Microsoft, no entanto. Se existirem mudanças que dizem respeito a alocação dinâmica de memória em nonpaged-pool, o Edit and Continue não será possível naquele momento, apenas depois do reboot.

O último item, mais esotérico de todos, promete ser lançado a partir da versão 7.1:

Resumidamente, é um !analyze mais esperto com o algoritmo heurístico do Visual Basic .NET. Assim que for aberto um dump de tela azul e carregados os símbolos e o caminho dos fontes, a nova versão do !analyze irá verificar os valores do BugCheck gerado e, caso seja detectado que o problema está em seu driver, irá sugerir uma correção na sua função que estiver na pilha.







Existem um pouco de polêmica em torno dessa funcionalidade. Alguns dizem que ela vai mais atrapalhar do que ajudar os programadores de kernel com a vinda de analistas de sistemas Júnior programando filtros de file system sem a menor discrepância entre o que é um IRP assíncrono e uma ISR. Outros dizem que existirá uma versão paga do WinDbg com essa funcionalidade, nos mesmos moldes do Visual Studio 2010, que virá com a depuração reversa no Enterprise. Essas especulações só o tempo dirá se são verdade ou não. Se eu tiver que pagar mais caro por essas features, o lobby na empresa onde eu trabalho está garantido.
