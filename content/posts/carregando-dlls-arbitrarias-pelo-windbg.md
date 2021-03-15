---
date: "2007-11-23"
title: "Carregando DLLs arbitrárias pelo WinDbg"
tags: [ "code" ]
---
Durante meus testes para a correção de um bug me deparei com a necessidade de carregar uma DLL desenvolvida por mim no processo depurado. O detalhe é que o processo depurado é de terceiros e não possuo o fonte. Portanto, as opções para mim mais simples são:

 - Usar o projeto [RmThread] para injetar a DLL (nesse caso iniciando o processo através dele).
 - Fazer um módulo wrapper para uma DLL qualquer e ser carregado de brinde.
 - Usar o WinDbg e brincar um pouco.

Por um motivo desconhecido a terceira opção me pareceu mais interessante =).

A seqüência mais simples para carregar uma DLL através do WinDbg na época que escrevi este post era chamar kernel32!LoadLibrary através de um código digitado na hora, o que podemos chamar de live assembly (algo como "assembly ao vivo"). Porém, essa simples seqüência que contém um pouco mais que uma dúzia de passos hoje teria que ser feito em assembly 64 bits e é um pouco mais complicado. Para quem ainda quer se divertir dessa forma por esse caminho irei deixar as instruções para 32 bits.

Devemos parar a execução, voltar para um ponto seguro do código com o comando gu (que volta para a função chamadora e evita perda de estado dos registradores) e armazenar o local seguro em um registrador temporário (o WinDbg tem 20 deles, $t0 até $t19).
    
    gu
    r$t0 = @$ip

Note que usamos dois pseudo-registradores ($t0, o primeiro registrador temporário do WinDbg, e $ip, o registrador que aponta para a próxima instrução que será executada), mas só um deles possue o prefixo '@'. Esse prefixo diz ao WinDbg que o que segue é um registrador. Como o comando r já é usado com registradores, é desnecessário usá-lo para $t0. Se usarmos sintaxe C++ esse prefixo é obrigatório, enquanto na sintaxe MASM não. Porém, se não usarmos esse prefixo em registradores não-comuns (como é o caso para $ip) o WinDbg primeiro tentará interpretar o texto como um número hexadecimal. Ao falhar, tentará interpretar como um símbolo. Ao falhar novamente, ele finalmente irá tratá-lo como um registrador. A diferença na velocidade faz valer a pena digitar um caractere a mais. Faça a prova!

Parada a execução em um local seguro e armazenado o IP, em seguida podemos alocar memória para entrar o código em assembly da chamada, além do seu parâmetro, no caso o path da DLL a ser carregada. Para a alocação usamos o comando .dvalloc, para a escrita de uma string o comando eza (ANSI) ou ezu (UNICODE). Em seguida usamos o comando a para escrever o código assembly da chamada à função kernel32!LoadLibrary e uma interrupção 3 (breakpoint) para termos uma maneira conveniente de parada.
    
    .dvalloc 0x1000
    Allocated 1000 bytes starting at 000001d9`abd20000
    
    eza 000001d9`abd20000 "c:\\tools\\tioclient.dll"
    
    0:000> a 000001d9`abd20000+0x100
    000001d9`abd20100 call KERNEL32!LoadLibraryA
    000001d9`abd20105 int 3
    000001d9`abd20106

Note que estamos usando a versão ANSI do LoadLibrary, aquela que termina com A. Sendo assim, escrevemos uma string ANSI como parâmetro usando o comando eza.

O último passo seria chamar a função previamente "editada". Para isso basta mudarmos o endereço da próxima instrução para o começo de nosso código, definir os parâmetros nos registradores (no caso apenas um, a string em rcx) e mandar executar, pois ele irá parar automaticamente no breakpoint que definimos "na mão", o int 3 digitado. Após a execução devemos voltar o ponteiro usando nosso backup no registrador $t0.

    0:000> r$ip = 0x00280000+0x100
    0:000> g
    ModLoad: 10000000 10045000   c:\\tools\\tioclient.dll
    (398.d90): Break instruction exception - code 80000003 (first chance)
    eax=10000000 ebx=7ffdd000 ecx=7c801bf6 edx=000a0608 esi=001a1f48 edi=001a1eb4
    eip=0028010a esp=0007fb24 ebp=0007fc94 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    0028010a cc int     3
    0:000> r$ip = $t0
    *** WARNING: Unable to verify checksum for C:tempMinhaDllInvasora.dll
    0:000> g
    ModLoad: 5cb70000 5cb96000   C:\WINDOWS\system32\ShimEng.dll
    ModLoad: 6f880000 6fa4a000   C:WINDOWS\AppPatch\AcGenral.DLL
    ModLoad: 76b40000 76b6d000   C:WINDOWS\system32\WINMM.dll
    ModLoad: 774e0000 7761d000   C:WINDOWS\system32\ole32.dll
    ...

Como pudemos ver pela saída, a DLL foi carregada e agora temos a possibilidade de chamar qualquer código que lá esteja. Como fazer isso? Provavelmente usando o mesmo método aqui aplicado. Live-assembly é o que manda 8).

[RmThread]: http://www.codeproject.com/threads/RmThread.asp
