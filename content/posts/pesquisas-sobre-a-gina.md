---
categories:
- code
- draft
date: '2008-07-02'
title: Pesquisas sobre a GINA
---

Já sabemos o que é uma GINA. Afinal, todo mundo já viu uma antes. E sabemos que hoje em dia ela está morta.

No entanto, algumas pequenas mudanças foram feitas nela no Windows XP que ainda almaldiçoam o código de quem tenta reproduzir a famosa GINA da Microsoft. Nem todos chegam no final e morrem tentando.

Eu sou um deles.

Uma explicação sobre como funciona o processo de logon (local e remoto) e os componentes envolvidos está no artigo "How Interactive Logon Works" da Technet. Esse artigo irá abrir os olhos para mais detalhes que você gostaria de saber sobre nossa velha e querida amiga. Os desenhos explicativos estão ótimos!

Após essa leitura picante, podemos voltar ao feijão com arroz e começar de novo lendo a descrição de como funciona a GINA na Wikipedia, que nos remete a vários linques interessantes, entre os quais:

	
  * A explicação documentada do MSDN de como funciona a interação entre Winlogon e GINA.

	
  * Um ótimo artigo dividido em duas partes que explica como fazer sua própria customização de GINA. Foi nele que encontrei o retorno que precisava para emular a execução do Gerenciador de Tarefas baseado na digitação do Ctrl + Alt + Del. De brinde ainda vem uma GINA de exemplo para _download_.

A partir de mais algumas buscas e execuções do Process Monitor podemos encontrar os valores no registro que habilitam o Fast User Switching e a Tela de Boas Vindas do Windows XP. O valor da Tela de Boas Vindas é que habilita e desabilita a execução do Gerenciador de Tarefas baseado em Ctrl + Alt + Del. Esses itens são essenciais para os que quiserem criar uma réplica perfeita da GINA da Microsoft no Windows XP. Isso finaliza a minha busca.

Sempre tem mais. Se a máquina estiver no domínio essa opção não funciona. Porém, o WinLogon verifica se existe um valor chamado ForceFriendlyUi, que descobri graças ao Process Monitor. Aliado ao LogonType, sendo igual a 1, a Tela de Boas-Vindas é habilitada, mesmo em um ambiente com servidor de domínio.

Por último, claro, salvo se não existir o valor GinaDll dentro da chave do WinLogon. Se esse for o caso, o ForceFriendlyUi também não funciona. E é exatamente aí que uma GINA é instalada.

E eis que surge uma nova GINA.