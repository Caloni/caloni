---
date: "2010-08-08"
title: Não é minha culpa
categories: [ "blog" ]
---
 sobre o aplicativo NotMyFault, escrito como ferramenta do livro [Windows Internals e que basicamente gera telas azuis para análise.

Como os problemas gerados pela ferramenta são todos de kernel, resolvi escrever meu próprio conjunto de bugs para o pessoal da userland. E como nada na vida se cria, tudo se copia, tenho o orgulho de apresentar a vocês o **NotMyFaultEither**!

 ![notmyfaulteither-crash.png

Seu uso é bem simples. Escolha o problema, aperte a teclar "Fazer Bug" e pronto!

O resultado pode variar dependendo do sistema operacional e da arquitetura (há versões 32 e 64 bits, ambas UNICODE). Um Access Violation no Windows Seven 64 bits, por exemplo, o processo pára de reponder.

Após a análise do SO ele exibe uma tela onde é possível achar onde está o despejo de memória que podemos usar.

   ![notmyfaulteither-crash-dump-task-manager.png

Esse é um minidump (mdmp), que possui a pilha da thread faltosa e informações de ambiente. Podemos gerar um dump completo através do Gerenciador de Tarefas.

, muito útil para preparar o material da [minha palestra do próximo fim de semana.

#### Sorteio do livro Windows Internals, Quarta Edição

E por falar em palestra, criei um [pacote-surpresa irá concorrer, no dia da palestra, à quarta edição do livro Windows Internals, de Mark Russinovich. É minha cópia pessoal, mas está bem novinho, visto que a original pesa pra caramba e consulto sempre o e-book.

Estarei usando estes mesmos minidumps na palestra, junto dos dumps completos. Mas é claro que eu não iria deixar um despejo de memória completo pra vocês. Iria tornar as coisas muito fáceis ;)

Portanto, junte suas grandes dúvidas para o grande dia e nos vemos lá.
