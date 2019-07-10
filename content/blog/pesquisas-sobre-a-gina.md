---
date: "2008-07-02"
title: Pesquisas sobre a GINA
categories: [ "blog" ]
---
[![250px-xp_windows_security.png](http://i.imgur.com/eNLvM3I.thumbnail.png)](http://i.imgur.com/YprK2T7.png)Já sabemos o que é uma [GINA](http://www.caloni.com.br/gina-x-credential-provider). Afinal, todo mundo já viu uma antes. E sabemos que hoje em dia ela está morta.

No entanto, algumas pequenas mudanças foram feitas nela no Windows XP que ainda almaldiçoam o código de quem tenta reproduzir a famosa GINA da Microsoft. Nem todos chegam no final e morrem tentando.

Eu sou um deles.

#### Para os que investem em uma nova GINA

Uma explicação sobre como funciona o processo de logon (local e remoto) e os componentes envolvidos está no artigo "[How Interactive Logon Works](http://technet2.microsoft.com/windowsserver/en/library/779885d9-e5e9-4f27-9c14-5bbe77b056ba1033.mspx?mfr=true)" da Technet. Esse artigo irá abrir os olhos para mais detalhes que você gostaria de saber sobre nossa velha e querida amiga. Os desenhos explicativos estão ótimos!

Após essa leitura picante, podemos voltar ao feijão com arroz e começar de novo lendo a descrição de como funciona a [GINA na Wikipedia](http://en.wikipedia.org/wiki/Graphical_identification_and_authentication), que nos remete a vários linques interessantes, entre os quais:

	
  * A explicação documentada [do MSDN](http://msdn.microsoft.com/en-us/library/aa380543.aspx) de como funciona a interação entre Winlogon e GINA.

	
  * Um ótimo artigo dividido em [duas](http://msdn.microsoft.com/en-us/magazine/cc163803.aspx) [partes](http://msdn.microsoft.com/en-us/magazine/cc163786.aspx) que explica como fazer sua própria customização de GINA. Foi nele que encontrei o retorno que precisava para emular a execução do Gerenciador de Tarefas baseado na digitação do Ctrl + Alt + Del. De brinde ainda vem uma GINA de exemplo para _download_.

A partir de mais algumas buscas e execuções do Process Monitor podemos encontrar os valores no registro que habilitam o [Fast User Switching](http://www.pctools.com/guides/registry/detail/973/) e a [Tela de Boas Vindas](http://www.pctools.com/guides/registry/detail/972/) do Windows XP. O valor da Tela de Boas Vindas é que habilita e desabilita a execução do Gerenciador de Tarefas baseado em Ctrl + Alt + Del. Esses itens são essenciais para os que quiserem criar uma réplica perfeita da GINA da Microsoft no Windows XP. Isso finaliza a minha busca.

#### Será mesmo?

Sempre tem mais. Se a máquina estiver no domínio essa opção não funciona. Porém, o **WinLogon** verifica se existe um valor chamado **ForceFriendlyUi**, que descobri graças ao [Process Monitor](technet.microsoft.com/en-us/sysinternals/bb896645.aspx). Aliado ao **LogonType**, sendo igual a 1, a Tela de Boas-Vindas é habilitada, mesmo em um ambiente com servidor de domínio.

Por último, claro, salvo se não existir o valor **GinaDll** dentro da chave do WinLogon. Se esse for o caso, o ForceFriendlyUi também não funciona. E é exatamente aí que uma GINA é instalada.

E eis que surge uma nova GINA.
