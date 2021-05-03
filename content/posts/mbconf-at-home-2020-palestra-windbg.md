---
categories:
- code
date: '2020-04-18'
link: https://www.papobinario.com.br/v1/
title: Minha Palestra Sobre Windbg
---

A MBConf@Home2020 foi um sucesso. Parabéns aos organizadores, palestrantes e apoiadores. Eu nunca fui em um evento de tecnologia em que tudo funcionou do começo ao fim. Simplesmente fantástico o nível de qualidade da organização. Fora que trezentas pessoas ficaram em casa e participaram conosco dessa troca de conhecimento =).

Minha palestra foi a seguinte: dei uma pincelada no que é o WinDbg para os que ainda não conhecem e realizei algumas manobras pouco usuais de depuração, tentando fugir um pouco da rotina do programador e me enfiando no que seriam minhas sessões antigas de hacking ou cracking da época que analisava trojans ou depurava serviços que saíam depois que meu depurador remoto já tinha ido embora. Segue mais ou menos o roteiro e os pontos levantados.

Hoje em dia o caminho mais fácil é pelo Visual Studio Community, que instala por padrão um Windows SDK. Nessa instalação é possível modificar os itens checando o "Debugging Tools for Windows", que é o pacote que contém o ecossistema do WinDbg.

Pulei essa parte. Tempo curto e me enrolei um pouco. E não era o caso de ficar focado na rotina de programador.

Não fui eu que escrevi o MessageBox... juro. E nesse caso não ter o código-fonte é a rotina do crackudo, que vai ter que explorar no assembly o funcionamento de um programa. Depuramos um que chama MessageBox alterando a mensagem exibida (em 32 bits). Foi legal essa diferença entre Ansi e Unicode que me perdi no começo, pois serviu para exemplificar questões de API que precisam ser conhecidas.

    void chama_eu()
    {
      MessageBox(NULL,
        "Welcome to "
        "MBConf@Home2020",
        "MBConf2020", 
        0);
    }

Abordamos o boot do Windows com NT, o uso do kd.exe por baixo dos panos do WinDbg (o DarkMode) e configuramos o cabo. Cabo? Cabo virtual, sargento. Usamos a VMWare, pré-configurada após alguns pesadelos de impressora se metendo no meio do caminho. Configuramos a porta serial, que é a melhor ever. E apontamos como named pipe para o WinDbg "de fora" conectar. Ou o kd.exe. As linhas abaixo são equivalentes.

    windbg.exe -b -k com:pipe,port=\\.\pipe\com_1,resets=0
    kd.exe -b -k com:pipe,port=\\.\pipe\com_1,resets=0

Para exemplificar a depuração de um serviço bem no início (ou fim) ou o load de processos antes dele existir checamos uma flag na gflags.exe da máquina depurada para que quando o notepad.exe subisse o ntsd fosse depurá-lo e passasse o controle para o debug do sistema. E com isso fechamos o círculo sagrado da depuração holística.

Não. Para depurar a BIOS local há o caminho do debug.com (um depurador bem simples da época do Windows 95) ou o Softice DOS, embora [eu me lembre] que tive umas dores de cabeça com ele por causa dos conflitos entre interrupções e programas residentes. A depuração estática acaba ganhando nesse quesito, que é basicamente abrir o assembly, papel e caneta. E imaginação.

Já para debug de BIOS em rede. Bem... esse é um nível hackudo. Sei que a Intel tem desenvolvido chips para diagnóstico e obtenção de dados de hardware pela rede antes mesmo do SO estar ligado, mas não cheguei a pesquisar a fundo.

Sim. Como o [Mercês] me ajudou a lembrar, existe um rundll32.exe, um executável que já vem no Windows e que pode carregar a DLL para você. Daí tudo que você precisa fazer é colocar o breakpoint das funções exportadas que deseja chamar. Dá para especificar essas funções pelo rundll32.exe também: rundll32.exe project.dll,chama_eu

Recomendo sempre o [WinDbg.info] como cheat sheet e docs.microsoft.com em seus artigos "Getting Started with WinDbg (User-Mode)" e "Getting Started with WinDbg (Kernel-Mode)" (sorry, m$, vcs mudam os links demais para eu colocar aqui).

[Mercês]: https://twitter.com/mer0x36
[WinDbg.info]: http://windbg.info/
[eu me lembre]: /o-bug-mais-bizarro-que-ja-resolvi