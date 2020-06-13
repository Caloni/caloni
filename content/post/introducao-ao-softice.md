---
categories: [ "code" ]
date: "2007-07-02"
tags: [ "draft",  ]
title: "Introdução ao SoftICE"
---
O que acontece quando você precisa depurar um programa e não tem o Visual Studio instalado na máquina onde o problema está ocorrendo? Ora, para isso que existe o Remote Debugging.aspx). Eu uso direto. Você só precisa rodar um pequeno programa na máquina que vai ser depurada e abrir uma porta ou duas. O resto o Visual Studio da máquina que vai depurar faz.

Tudo bem, mas e se estamos falando de depuração em kernel mode? Bem, nesse caso o mais indicado é o nosso já conhecido WinDbg. Só precisamos de um cabo serial, firewire ou USB conectando as duas máquinas.

A vida pode ser complicada às vezes. O WinDbg em versões antigas até rodava em plataforma 9x (95/98/ME), mas agora já não roda mais. Felizmente eu mantenho uma versão das antigonas, só para garantir. Só que ele rodava apenas para depurar em user mode, o que de qualquer forma não seria útil nesse caso.

Existe uma ferramenta de depuração no DDK do Windows 98 chamada WDEB386. Sua existência está documentada no próprio DKK. Funciona similarmente ao WinDbg, ou seja, o depurador em parte roda na máquina depurada e em parte na máquina que depura, e ambas são conectadas por um cabo serial. Teoricamente essa ferramenta serviria para depurar o kernel dos sistemas 9x, mas na maioria das vezes tive problemas com ela. Não que nunca tenha funcionado. Até já consegui essa proeza uma vez depois de muito ler a documentação e resolver uma série de problemas que não estavam documentados. Se você leitor quiser tentar a sorte, vá em frente.

Para piorar as coisas, existe mais um último problema: a máquina não está ao alcance de um cabo serial. Para esse último caso talvez fosse a hora de chamar um produto não-Microsoft que dá conta do recado muito bem: o SoftICE.

O SoftICE é um depurador de kernel e user mode que é instalado na própria máquina depurarada. Ou seja, ele não precisa de uma segunda máquina só para rodar o depurador ou parte dele. Funciona no MS-DOS (versão 16 bits), plataforma 9x e NT. Criado pela Numega, mais tarde foi comprado pela Compuware, que passou a vendê-lo como um pacote para desenvolvimento de drivers, o Driver Studio. No seu time de desenvolvimento passaram nomes consagrados como Matt Pietrek e Mark Russinovich.

Essa ferramenta teve seus dias de glória quando a maioria dos crackers a utilizava para quebrar a proteção de programas e do sistema operacional. Tanto foi famosa que foram desenvolvidas diversas técnicas para detectar se o SoftICE estava ativo na máquina, mais ou menos o equivalente das diversas técnicas atuais para detectar se um programa está sendo executado dentro de uma máquina virtual.

O SoftICE deve ser instalado na máquina do desenvolvedor para gerar os símbolos dos programas e na máquina que vai ser depurada para depurar. Isso quer dizer que ele não precisa ser ativado na máquina do desenvolvedor. Só precisamos usar uma ferramenta chamada Symbol Loader, responsável por gerar símbolos e empacotar os fontes para serem usados na máquina depurada.

Na hora de instalar, você tem três opções:

	
  * _Full installation_: desenvolvimento e depuração; use se for desenvolver e depurar na mesma máquina.
  * _Host machine_: apenas desenvolvimento; não serve para depuração.
  * _Target machine_: depuração; instale essa opção na máquina de testes.

Após esse processo e a compilação do seu driver favorito podemos gerar os símbolos.

Obs. importante! Infelizmente, o Driver Studio só traduz os símbolos corretamente até a versão 6 do Visual C++, ou seja, não inclui nenhuma das versões .NET do Visual Studio (2002/2003/2005+). A Compuware se negou a oferecer suporte para os novos compiladores, talvez até prevendo que o produto iria ser descontinuado em breve.

A geração de símbolos pode ser feita de modo gráfico pelo Symbol Loader ou pela linha de comando. Vamos usar aqui a linha de comando para demonstrar como automatizar esse processo durante o processo de build:

As opções source e package são importantes para traduzir utilizando o código-fonte e empacotar esse código-fonte no arquivo gerado. Note que eu disse empacotar, o que significa que o fonte vai estar dentro do arquivo de símbolos. Portanto, se a licença do seu software é de código fechado, nunca se esqueça de apagar esse arquivo quando estiver na máquina de um cliente.

Se tudo der certo no final teremos dois arquivos a serem copiados para a máquina depurada:

Depois de copiados e o driver instalado, insira pelo Symbol Loader o arquivo NMS na lista de símbolos a serem carregados no reboot. Após configurar o depurador como lhe aprouver basta reiniciar a máquina. Feito o reboot, existe uma tecla mágica que irá nos levar para o mundo da tela preta, o ambiente padrão do SoftICE: Ctrl + D.

A interface é divida em pseudojanelas que ficam organizadas em camadas. Para exibir/esconder as janelas ou especificar o tamanho de uma delas usa-se o comando w. Aliás, basta começar a digitar um comando e o programa irá listar os comandos possíveis.

Com certeza existe um monte de coisas novas para aprender quando se troca de depurador. Mais uma vez, assim como o WinDbg, temos a opção de utilizar o sistema de janelas ou a linha de comando. Aqui vão algumas dicas importantes:

  * Para mostrar a tela do SoftICE, Ctrl + D. Digite novamente e ela some e o sistema volta a rodar.
  * Os nomes dos comandos se assemelham aos do WinDbg. Tente usá-los e sinta as diferenças.
  * A ajuda do programa é muito boa e explica direitinho todos os detalhes do ambiente. Caso algo falhe, RTFM!

Essa parece ser uma introdução muito básica ao SoftICE. E na verdade é. Teremos outras oportunidades mais pra frente de usar esse poderoso depurador, principalmente naqueles casos onde um problema só acontece no Windows 95 Release A e sem rede. Isso não é tão incomum quanto parece.
