---
categories: [ "code" ]
date: "2008-01-28"
tags: [ "draft",  ]
title: "RmThread: rode código em processo vizinho"
---
Aproveitando que utilizei a mesma técnica semana passada para desenvolver um vírus para Ethical Hacking, republico aqui este artigo que já está mofando no Code Projet, mas que espero que sirva de ajuda pra muita gente que gosta de fuçar nos internals do sistema. Boa leitura!

RmThread é um projeto que fiz baseado em uma das três idéias do artigo de Robert Kuster , "Three Ways to Inject Your Code into Another Process". No entanto, não utilizei código algum. Queria aprender sobre isso, pesquisei pela internet, e me influenciei pela técnica CreateRemoteThread & LoadLibrary. O resto foi uma mistura de "chamada de funções certas" e MSDN.

O projeto que fiz é útil para quem precisa rodar algum código em um processo vizinho, mas não quer se preocupar em desenvolver a técnica para fazer isso. Quer apenas escrever o código que vai ser executado remotamente. O projeto de demonstração, RmThread.exe, funciona exatamente como a técnica citada anteriormente. Você diz qual o processo a ser executado e a DLL a ser carregada, e ele inicia o processo e carrega a DLL em seu contexto. O resto fica por conta do código que está na DLL.

Para fazer a DLL, existe um projeto de demonstração que se utiliza de uma técnica que descobri para fazer rodar algum código a partir da execução de DllMain sem ficar escravo de suas limitações (você só pode chamar com segurança funções localizadas na kernel32.dll).

Existem três funções que poderão ser utilizadas pelo seu programa:


Eis a rotina principal simplificada demonstrando como é simples a utilização das funções:


A parte mais complicada talvez seja o que fazer quando a sua DLL é carregada. Considerando que ao ser chamada em seu ponto de entrada, o código da DLL possui algumas limitações (uma já citada; para mais, vide a ajuda de DllMain no MSDN), fiz uma "execução alternativa", criando uma thread na função DllMain:


A função da thread, por sua vez, é esperar pela finalização da thread DllMain (temos o handle dessa thread armazenado em ghThrDllMain), fazer o que tem que fazer, e retornar, liberando ao mesmo tempo o handle da DLL criado para si:


A marca TODO é aonde seu código deve ser colocado (você pode tirar o MessageBox, se quiser). Como DllMain já foi previamente executada, essa parte do código está livre para fazer o que quiser no contexto do processo vizinho.

Um detalhe interessante é que é necessária a chamada de FreeLibraryAndExitThread. Do contrário, após chamar FreeLibrary, o código a ser executado depois (um simples return) estaria em um endereço de memória inválido, já que a DLL não está mais carregada. O resultado não seria muito agradável.

Um problema chato (que você poderá encontrar) é que, se a DLL não for carregada com sucesso, não há uma maneira trivial de obter o código de erro da chamada de LoadLibrary. Uma vez que a thread inicia e termina nessa função API, o LastError se perde. Alguma idéia?

  * Endereço do artigo (e fontes) no Code Project

