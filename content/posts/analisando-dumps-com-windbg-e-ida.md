---
date: "2008-01-10"
tags: [ "code", "draft",  ]
title: "Analisando dumps com WinDbg e IDA"
---
Apesar de ser recomendado que 100% dos componentes de um software esteja configurado corretamente para gerar símbolos na versão release, possibilitando assim a visualização do nome das funções internas através de um arquivo de dump (despejo) gerado na ocorrência de um crash, essa verdade só ocorre em 80% das vezes. Quis Murphy que dessa vez a única parte não "simbolizada" fosse a que gerou a tela azul em um Intel Quad Core que estou analisando esses dias.

Para incluir um programa novo em nosso leque de opções, vamos usar dessa vez uma ferramenta chamada IDA, um disassembler estático cujo nome é uma clara homenagem à nossa primeira programadora da história. E, é lógico, o WinDbg não poderá ficar de fora, já que ele será nosso analisador de dumps.

Tecnicamente falando, um dump nada mais é do que o conjunto de informações relevantes de um sistema em um determinado momento da execução, geralmente logo após um crash, onde tudo pára e morre. No caso do Windows, o crash é chamado de BSOD, Blue Screen Of Death, ou Tela Azul da Morte (bem macabro, não?). Do ponto de vista do usuário, é aquela simpática tela azul que aparece logo após o travamento da máquina.

Em algumas máquinas, essa tela nem mais é vista, pois o Windows XP é configurado automaticamente para exibir um simpático reboot que joga todos os seus dados não-salvos naquele momento para o limbo (ou, como diria o Thiago, para o "céu dos dados não-salvos antes de uma tela azul").

Dumps podem ser abertos por um depurador que entenda o tipo de dump gerado (Visual Studio, WinDbg, OllyDbg, IDA, sd, etc). Se estamos falando de aplicativos que travaram, o Visual Studio pode dar conta do recado. Se é realmente uma tela azul, o WinDbg é o mais indicado.

Para abrir um dump no WinDbg, tudo que temos que fazer é usar o item do menu "File, Open Crash Dump" ou digitar direto da linha de comando:


Após alguns segundos, o WinDbg irá imprimir uma saída parecida com as linhas abaixo.



Mini Kernel Dump File: Only registers and stack trace are available











Geralmente a melhor idéia agora é seguir o conselho do WinDbg e usar o comando !analyze.










Esse é o resultado de um dos minidumps recebidos.

Um minidump contém apenas a pilha de chamada que causou a tela azul, o estados dos registradores e algumas informações sobre módulos carregados no kernel.

A partir daí podemos extrair algumas informações úteis, que eu sublinhei na saída do WinDbg. Na ordem de chegada:

  1. O código do Bug Check. Esse é talvez o mais importante, pois pode resolver rapidamente o nosso problema. Procurando na ajuda do WinDbg pelo código do erro (obs: execute o link pelo explorer) conseguimos ter algumas dicas de como evitar esse erro:
"The MAXIMUMWAITOBJECTSEXCEEDED bug check has a value of 0x0000000C. This indicates that the current thread exceeded the permitted number of wait objects."
Mais sobre isso pra depois.

  2. Os dados da pilha. Pela pilha de chamadas, podemos não apenas saber se nosso driver está no meio com cara de culpado, como, através dos _offsets_, descobrir em que função ele se enfiou para dar no que deu.

  3. A última chamada do kernel antes do nosso driver pode indicar-nos que evento foi o responsável por iniciar todo o processo de cabum. Nesse caso, IopLoadDriver nos dá uma ótima dica: foi na hora de carregar o nosso driver.

Com isso em mãos, mesmo sem símbolos e nomes de funções no código, conseguiríamos achar o código responsável pelo BSOD. Porém, vamos imaginar por um momento que não foi tão fácil assim e fazer entrar em cena outra ferramenta indispensável nessas horas: o Interactive Disassembler.

No sítio do IDA podemos encontrar o download para uma versão gratuita do IDA, isso se usado com objetivos não-comerciais. Ou seja, para você que está lendo esse blogue por aprendizado, não terá nenhum problema você baixar essa versão e fazer alguns testes com seu driver favorito.

O funcionamento básico do IDA é bem básico, mesmo. Simplesmente escolhemos um executável para ele destrinchar e nos mostrar um assembly bem amigável, com todos os nomes de funções que ele puder deduzir. Como não temos os símbolos do próprio executável, as funções internas ganham "apelidos", como sub6669, loc13F35 e por aí vai. Isso não importa, já que temos nomes amigáveis de APIs para pesquisar no código-fonte e tentar encontrar as funções originais em C.

Pois bem. Como manda o figurino, o primeiro ponto do assembly que temos que procurar é o ponto em que uma função interna é chamada logo após IopLoadDriver, mydriver+0x4058. Por coincidência (ou não, já que essa é a função do IopLoadDriver), se trata da função inicial do executável, ou seja, provavelmente a função DriverEntry no código-fonte (obs: estamos analisando um driver feito para plataforma NT).

Como podemos ver pela imagem acima, o ponto de retorno é logo após uma chamada à função sub113F0, que não sabemos qual é. No entanto, sabemos que logo no início é chamada a função IoIsWdmVersionAvailable, o que já nos permite fazer uma correlação com o código-fonte original. Após a chamada à IoIsWdmVersionAvailable, a próxima e última chamada de uma função é o que procuramos. Dessa forma, podemos ir caminhando até o ponto onde o driver chama o sistema operacional:









Voilà! O caminho não foi tão longo. Chegamos rapidamente no ponto onde é chamada a função KeWaitForMultipleObject que, de acordo com o WinDbg e com a OSR, pode gerar uma tela azul se esperarmos por mais de três objetos e não especificarmos um buffer no parâmetro WaitBlockArray. Agora podemos olhar no fonte e ver por quantos objetos esperamos e tirar nossa própria conclusão do que está acontecendo:


Ora, ora. O número de processadores influencia no número de objetos que estaremos esperando na função de espera. Esse seria um bom motivo para gerar um MAXIMUMWAITOBJECTSEXCEEDED em máquinas onde existe mais de 3 processadores ativos, não? Talvez seja uma boa hora para atualizar esse código e torná-lo compatível com os novos Quad Core.

É importante, durantes os testes de desenvolvimento, sempre manter em dia uma versão debug (para o mundo kernel mode, versões checked) para que os primeiros problemas, geralmente os mais bestinhas, sejam pêgos de forma rápida e eficiente. No entanto, um bom desenvolvedor não se limita a depurar com código-fonte. Ele deve estar sempre preparado para enfrentar problemas de falta da versão certa, informação pela metade, situação não-reproduzível. Para isso que servem as ferramentas maravilhosas que podemos usar no dia-a-dia. O IDA é mais uma das que deve estar sempre no cinto de utilidades do bom "debugador".
