---
date: "2010-10-09"
tags: [ "code", "draft",  ]
title: "Três em um"
---
Que vergonha passar tanto tempo sem postar nada. Parece que não fiz nada que valesse a pena comentar por aqui.

Na verdade, não fiz tanto, mesmo. Muitas mensagens do Outlook, gráficos UML e reuniões de alinhamento depois, sobrou um tempinho pra programar. Aprendi algumas coisas que tinha o desejo de saber há tanto tempo... Agora eu sei, quem diria, criar linques suspensos nas janelas Win32! Que novidade, não? Pois é, isso exige, de acordo com o SDK, algumas artimanhas pra fazer funcionar. Para quem está de Visual Studio 2008/2010 na mão basta seguir os passos seguintes.

Definir que estamos programando para XP ou superior:


Inserir suporte a linques na biblioteca de controles comuns:


Usar o CreateWindow com a classe certa, fazer markup html dentro do título e cuidar das mensagens de click e enter no controle:


Você que não está fazendo subclassing de janelas existe outra técnica que você pode utilizar: arrastar-e-soltar o controle do seu ToolBox. Qual é a graça?

 Outra coisa que aprendi foi como enviar mensagens ao usuário para impedir que este reinicie a máquina em momentos importantes:

A partir do Vista temos uma nova API para fazer isso. E é muito simples:


Quando ao receber a famigerada WMQUERYENDSESSION, basta retornar FALSE. O Windows faz o resto.

PS: E com uma ajudinha do Windows Internals ainda fiquei sabendo que dá pra se colocar na frente da fila para receber essa mensagem. 
