---
date: "2015-05-26"
title: "Depurando até o fim do mundo e de volta de novo: source server com GitHub"
categories: [ "code" ]
category: [ videos ]
---
Semana passada fiquei sabendo que o [vídeo](http://www.infoq.com/br/presentations/depurando-ate-o-fim-do-mundo#) da minha palestra "Depurando até o fim do mundo" do TDC 2014 estava disponível _online_. Resolvi assistir para ver se aprendia alguma coisa. A despeito do palestrante ser muito ruim, ele disse uma coisa interessante: com o Debugging Tools (WinDbg para os íntimos) seria possível além de indexar os símbolos (PDBs para os íntimos) usando o esquema de Symbol Server [que a própria Microsoft adota](https://support.microsoft.com/en-us/kb/311503) usar algumas ferramentas embutidas para conseguir obter o fonte através de um símbolo indexado.

E de onde viria esse fonte? Bom, _a priori_ é necessário que exista algum controle de fonte para que as versões estivessem já "indexadas" nesse controle e fossem mapeados com strings internas no PDB. Através dessas strings o WinDbg ao analisar um _crash dump_ ou até mesmo depurando um processo com o uso do PDB conseguiria baixar os fontes automagicamente desse controle de fonte, desde que ele estivesse acessível (na internet, na intranet da própria empresa, na rede, em um disco rígido externo ou na própria máquina do desenvolvedor que não quer se matar para conseguir obter a versão exatada dos fontes daquele binário).

O detalhe que o palestrante (Caloni é o nome do sujeito) citou era que já existiam scripts prontos para realizar essa tarefa para os controles de fonte mais comuns, sendo que os mais comuns são: Source Safe (?????), CVS (????????) e, claro, Subversion! (?!?!?!?!??!??!?!).

OK, pelo visto o pessoal da Microsoft mora em uma caverna ou não estão muito interessados em indexar os fontes para alguns controles de fonte que estão surgindo por aí, como Git sendo um exemplo aleatório.

Já que o tal do Caloni disse que ainda não fizeram scripts para controles mais modernos. Nenhum descentralizado ainda está na lista. Os scripts são feitos em Perl, ou seja, estão disponíveis em uma linguagem um pouco mais fácil que .BAT. Ou talvez não. De qualquer forma, não parece muito difícil de entender a dinâmica do WinDbg e simplesmente gerar o que tem que gerar dentro dos PDBs.

Pensando nisso, resolvi fazer uma primeira versão, em Python, de um script em que você passa alguns dados e ele processa seus PDBs. Depois você pode jogá-los em um Symbol Server e quando o WinDbg encontrá-lo através de um binário analisado, este irá conter o endereço no GitHub e um comando do Curl para baixá-lo, passando a exibi-lo imediatamente na tela do WinDbg. E nada mais lógico do que criar um [repositório no GitHub](https://github.com/Caloni/GitIndex) para compartilhá-lo, certo?

## Modo de Usar

O funcionamento é muito simples, mas pede muitos parâmetros (recomendo criar um batch para armazená-los). Então vejamos:

![](http://i.imgur.com/6m3En11.png)

 - dbgtools (caminho onde está o Debugging Tools for Windows)
 - pdbpath (caminho de onde devem ser pegos os PDBs, como um output da vida)
 - projname (preciso do nome do projeto com escopo do usuário para compor a URL, e.g. Caloni/GitIndex)
 - repo (esse é o caminho do repositório local, pois o remoto eu já consigo pegar com o projname)

Um detalhe importante: o revno que será usado é o HEAD do repositório local. Sim, futuramente podemos adicionar esse argumento como opcional. Porém, no momento, coisas mais urgentes devem ser feitas. Uma delas é que estou usando a visualização raw do GitHub para conseguir pegar um único arquivo-fonte, e para isso uso a ferramenta curl. Ou seja, quem é de Windows vai precisar baixar uma de suas versões e deixar no path do sistema. Quem não é de Windows... o que você está fazendo com um PDB, rapaz?

Como esse ainda é um projeto muito cru, mas gostaria de compartilhar com vocês (pois algo muito cru é melhor que nada), deixei diversos batchs de teste para ficar mais claro o funcionamento do srcsrv. Há um doc muito bom (er... ou mais ou menos) sobre o seu funcionamento na pasta srcsrv (chama-se srcsrv.doc). Usei algumas informações de lá para conseguir fazer a coisa funcionar. Se quiser me ajudar no projeto, tiver alguma dúvida, sugestão de melhoria/evolução, vamos conversar! Esse projeto será muito útil para mim no futuro, e espero que seja muito útil para outras pessoas, também.

Abaixo um vídeo do funcionamento através do WinDbg. O PDB já está indexado. No vídeo eu mostro como a pasta src (que é onde o WinDbg baixa os fontes) está vazia, e como após rodar o comando "g wmain" os símbolos são carregados e o WinDbg inicia o curl passando os parâmetros de um ponto em que ele sabe que vai precisar de um certo código-fonte. Para você realizar o mesmo com essa versão esteja ciente que você precisa do curl!

<div class="auto-resizable-iframe"><div><iframe frameborder="0" allowfullscreen="1" src="https://www.youtube.com/embed/mZewxqlFShA"></iframe></div></div>

