---
date: "2008-10-29"
tags: [ "code", "draft",  ]
title: "Como funciona o PsExec"
---
Semana passada precisei reproduzir o comportamento da ferramenta PsExec em um projeto, o que me fez sentir alguma nostalgia dos tempos em que eu fazia engenharia reversa todo dia. Este breve relato (espero) reproduz os passos que segui para descobrir o que esse programa tão útil quanto perigoso faz.

Sabe-se que o PsExec consegue executar um programa remotamente, ou seja, de uma máquina para outra, outra essa que chamaremos de máquina-alvo. O programa a ser executado geralmente deve estar disponível na própria máquina-alvo (condição ideal). Além da simples execução, para aplicativos console ele permite ainda a interação como se estivéssemos executando o programa remoto em nossa própria máquina local. Ele consegue isso redirecionando sua entrada e saída, o que o torna, como nos descreve o próprio autor, um "telnet light":


Além desse comportamento já muito útil ainda existe um bônus que se trata de especificar um executável local que será copiado remotamente para a máquina-alvo e executado. Esse é o comportamento que espero imitar:



No teste acima o myprogram.exe é somente o cmd.exe renomeado. Um teste básico =)

Já fizemos isso logo acima. Se trata apenas de observar o programa funcionando. Ao mesmo tempo em que entendemos seu modus operandi coletamos pistas sobre suas entranhas. No caso do PsExec, que faz coisas além-mar, como redirecionar os pipes de entrada/saída de um programa console, iremos checar a existência de algum serviço novo na máquina-alvo e arquivos novos que foram copiados, além de opcionalmente dar uma olhada no registro. Ferramentas da própria SysInternals como Process Explorer e Process Monitor também são úteis nessa análise inicial.

Como podemos ver, um serviço com o nome de PsExec foi criado na máquina-alvo. Se procurarmos saber o caminho do arquivo que corresponde a esse serviço, tanto pelo Process Explorer ou o Service Manager, descobriremos que se trata de um arquivo no diretório do windows chamado psexecsvc.exe.

Se o arquivo existe nessa pasta, então é óbvio que alguém o copiou. Resta saber como.

Nessa segunda fase, podemos refazer o comportamento esperado inúmeras vezes, coletando dados e pensando a partir dos dados obtidos. Para esse caso,  como quase todos que analiso, vou usar o nosso amigo WinDbg. Para isso, como tenho sempre minhas ferramentas disponíveis no ambiente onde trabalho, basta digitar "windbg" antes do comando anterior e dar uma olhada em algumas APIs-chave, como a criação/abertura de arquivos e a criação de serviços. Note que é importante fazer isso em um escopo limitado para não perdermos horas de análise. Descobrir coisas como, por exemplo, que as ações do PsExec só começam a ser executadas após a digitação da senha do usuário, pode ajudar, pois daí só começo minha análise a partir desse ponto.



Uma rápida busca no Google nos informa que o pipe querendo ser aberto pertence à lista de pipes que estão sempre disponíveis nas máquinas para responder às requisições do sistema. São importantes para a comunicação entre processos (IRP, Inter Process Communication). No entanto, quem usa esse pipe é o sistema, e ele foi chamado, como pudemos ver, pela função WNetAddConnection2W.aspx).

Se analisarmos mais a fundo a pilha de chamadas conseguiremos dar um olhada nos parâmetros passados. Para isso existe a opção de mostrar os argumentos passados para as funções ao exibir a pilha:


Ele tenta abrir uma conexão com a máquina-alvo em seu compartilhamento de IPC, que como já vimos serve para comunicação entre processos, até entre máquinas distintas. Dessa forma, descobrimos um dos pontos importantes no funcionamento do PsExec: ele usa o nome e senha fornecidos para abrir uma comunicação remota no compartilhamento IPC$.

Depois sugem várias paradas ao CreateFile, de maneira que a melhor forma de acompanhar isso é colocando um "dumpezinho" de memória na sua parada:


Muito bem! Chegamos a mais um ponto importante de nossa análise: o psexecsvc.exe é copiado através do compartilhamento ADMIN$ remotamente (diretório c:\windows). Esse compartilhamento se torna acessível, uma vez que uma conexão autenticada já foi aberta. Se listarmos as conexões existentes, veremos o compartilhamento IPC$ aberto:


Também podemos notar que, enquanto estamos parados depurando o processo psexec.exe, temos acesso ao compartilhamento admin$:

A análise desses fatos demonstra como é importante fazer as coisas, pelo menos na fase "iniciante",  bem lentamente, e entender a mudança de estado durante o processo. Nem sempre isso é possível, é verdade, ainda mais quando estamos falando de análise de kernel. Mas, quando as condições permitem, vale a pena pensar antes de fazer.

Voltando à analise: temos direitos remotos nessa máquina. Dessa forma, fica fácil criar um serviço.aspx) remotamente, que é o que faz o nosso amigo PsExec:


Pronto. Isso era tudo que precisava para conseguir reproduzir seu comportamento. Agora posso fazer isso programando ou até manualmente:


O resto do comportamento, como o redirecionamento de entrada e saída e execução do processo na conta especificada, embora muito interessante, não me interessa de imediato. Quem sabe interesse a você, e não tenhamos uma continuação dessa análise em um outro blogue de "desmontagem" por aí =)
