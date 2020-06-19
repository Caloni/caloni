---
categories: [ "code" ]
date: "2008-03-20"
tags: [ "draft",  ]
title: "Como rodar qualquer coisa como serviço"
---
A maior vantagem de se rodar um aplicativo como serviço, interativo ou não, é permitir que ele seja iniciado antes que seja feito um logon na máquina. Um exemplo que acontece comigo é a necessidade de depurar a GINA. Para isso, preciso que o depurador remoto do Visual Studio seja iniciado antes do logon. A solução mais fácil e rápida é rodar o Msvcmon, a parte servidora da depuração, como um serviço.

Hoje eu descobri um atalho bem interessante para isso.

Um artigo do Alex Ionescu falava sobre esse aplicativo linha de comando usado para criar, iniciar e apagar serviços. Mesmo não sendo o foco do artigo, achei muito útil a informação, pois não conhecia esse utilitário. Logo começaram a borbulhar idéias na minha mente:

"E se eu usasse esse carinha para iniciar o notepad?"

Bem, o Bloco de Notas é a vítima padrão de testes. Logo, a linha a seguir provaria que é possível rodá-lo na conta de sistema:


Porém, como todo serviço, é esperado que ele se comunique com o Gerenciador de Serviços do Windows. Como o Bloco de Notas mal imagina que agora ele é um motta-fucka service, expira o timeout de inicialização e o SCM mata o processo.


Como diria meu amigo Thiago, "não bom".

Porém porém, o SCM não mata os processos filhos do processo-serviço. Bug? Feature? Gambi? Seja o que for, pode ser usado para iniciar o nosso querido msvcmon:


Agora, quando iniciarmos o serviço Msvcmon, o processo cmd.exe será criado, que por sua vez irá rodar o msvcmon.exe que queríamos, e ficará esperando inocentemente pela sua "funesta morte" pelo SCM.

