---
date: "2010-08-08"
title: Não é minha culpa
categories: [ "blog" ]
---
Recebi a dica de meu [amigo kernel-mode](http://www.driverentry.com.br) sobre o aplicativo [NotMyFault](http://download.sysinternals.com/Files/Notmyfault.zip), escrito como ferramenta do livro [Windows Internals](http://technet.microsoft.com/en-us/sysinternals/bb963901.aspx) e que basicamente gera telas azuis para análise.

Como os problemas gerados pela ferramenta são todos de kernel, resolvi escrever meu próprio conjunto de bugs para o pessoal da userland. E como nada na vida se cria, tudo se copia, tenho o orgulho de apresentar a vocês o **NotMyFaultEither**!

![notmyfaulteither.png](http://i.imgur.com/9k3goIZ.png) ![notmyfaulteither-crash.png](http://i.imgur.com/Y1GUCUN.png)

Seu uso é bem simples. Escolha o problema, aperte a teclar "Fazer Bug" e pronto!

O resultado pode variar dependendo do sistema operacional e da arquitetura (há versões 32 e 64 bits, ambas UNICODE). Um Access Violation no Windows Seven 64 bits, por exemplo, o processo pára de reponder.

Após a análise do SO ele exibe uma tela onde é possível achar onde está o despejo de memória que podemos usar.

![notmyfaulteither-crash-dump-automatic.png](http://i.imgur.com/g2E7tcD.png)   ![notmyfaulteither-crash-dump-task-manager.png](http://i.imgur.com/nTwkVVx.png)

Esse é um minidump (mdmp), que possui a pilha da thread faltosa e informações de ambiente. Podemos gerar um dump completo através do Gerenciador de Tarefas.

No caso do Windows XP, podemos executar processo semelhante para gerar o dump através do aplicativo [ProcDump](http://technet.microsoft.com/en-us/sysinternals/dd996900.aspx), muito útil para preparar o material da [minha palestra do próximo fim de semana](http://www.temporealeventos.com.br/?area=95&tipo=1&id=3360).

#### Sorteio do livro Windows Internals, Quarta Edição

![meuwindowsinternals.jpg](http://i.imgur.com/pHlVP93.jpg)E por falar em palestra, criei um [pacote-surpresa](/images/crash-dump-analysis-dumps.7z) de alguns minidumps para análise. Se alguém tiver a curiosidade de já ir mexendo, ou de mexer na hora da apresentação, fique à vontade. Quem montar uma lista relacionando cada dump com o tipo de problema encontrado (não precisa estar completa) irá concorrer, no dia da palestra, à quarta edição do livro Windows Internals, de Mark Russinovich. É minha cópia pessoal, mas está bem novinho, visto que a original pesa pra caramba e consulto sempre o e-book.

Estarei usando estes mesmos minidumps na palestra, junto dos dumps completos. Mas é claro que eu não iria deixar um despejo de memória completo pra vocês. Iria tornar as coisas muito fáceis ;)

Portanto, junte suas grandes dúvidas para o grande dia e nos vemos lá.
