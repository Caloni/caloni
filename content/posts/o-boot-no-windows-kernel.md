---
date: "2009-12-04"
tags: [ "code", "draft",  ]
title: "O boot no Windows: Kernel"
---
Finalmente chegamos em um pouco onde podemos usar o WinDbg.

Podemos espetar o depurador e fazê-lo parar assim que conectado. Se estiver rodando antes do próprio sistema operacional, teremos um sistema sem processos e sem threads, pois ele irá parar assim que o executivo puder enviar o sinal de início pela porta serial, após carregar na memória os módulos básicos.



Todos os módulos carregados antes dessa fase são os drivers que tiveram seu Start definido em zero no registro. Todos os programadores que desenvolvem esses drivers gostariam de um dia poder usar o WinDbg. Mas não podem. Quem inicia a comunicação serial com o depurador é o kernel, que só recebe o controle do ntldr depois que os drivers básicos foram carregados.

Brincadeira. É claro que esses programadores usam o WinDbg, usam até demais. Mas só a partir desse ponto. Se algum problema evitar que o sistema chegue nessa fase, o desenvolvedor terá que usar métodos alternativos de depuração, como teste de mesa (risos incontroláveis).

De qualquer forma, estamos aí. Agora podemos depurar a criação de qualquer thread, qualquer processo, o carregamento de qualquer módulo, e a chamada a qualquer função do kernel.

Para depurar a criação de qualquer thread: coloque um breakpoint na função PsCreateSystemThread.


Para depurar a criação de qualquer processo: coloque um breakpoint na função PspCreateProcess, logo no começo. Será possível capturar a criação do processo System, o processo onde roda a primeira thread do kernel, que inicializa o resto dos componentes.


E não é lindo ver que, após a chamada ao Process Manager o processo REALMENTE foi criado e está na lista de processos?


É nesse momento que percebemos que um processo, uma thread, um qualquer-coisa dentro do kernel não é nada mais nada menos que um item em uma lista. Quase tudo no kernel será um item numa lista com um monte de ponteiros referenciando outras estruturas. É isso que mantém a lógica e a coerência no sistema inteiro. Tudo isso é basicamente software, construído como castelos no ar.

O próximo processo a ser criado, logo após carregar todos os drivers, é o nosso amigo SMSS, o Gerenciador de Sessão, o primeiro pedacinho do iceberg que desponta no oceano. É ele que irá iniciar toda a "parte user-mode do kernel".

Nota: Apesar de parecer contraditório, algumas partes do kernel são de fato implementadas em user mode. Os motivos podem variar, mas geralmente são maior segurança (código que não precisa rodar em um ring privilegiado) e desempenho (código que não precisa de muita prioridade).


Como podemos ver, isso é muito divertido e muito extenso. Poderíamos ir para qualquer lado da evolução do boot. Talvez em artigos futuros daremos uma olhada no processo de logon de um usuário, o que nos obrigaria a ter uma leve noção de como o Windows autentica e autoriza as pessoas. ou talvez daremos uma passadinha no sistema de escalonamento de threads do kernel, um assunto pra lá de complicado e esotérico.

Nota: Eu pessoalmente recomendo acompanhar o processo de boot descrito por Russinovich e depurar passo-a-passo um boot de verdade. Serão horas e mais horas de puro conhecimento empírico catalogado em seu cérebro-depurador.

Então até lá. Com licença que eu preciso ver a criação do System mais uma vez.

