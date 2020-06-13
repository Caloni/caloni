---
categories: [ "code" ]
date: "2007-11-23"
tags: [ "draft",  ]
title: "Carregando DLLs arbitrárias pelo WinDbg"
---
Durante meus testes para a correção de um bug me deparei com a necessidade de carregar uma DLL desenvolvida por mim no processo depurado. O detalhe é que o processo depurado é de terceiros e não possuo o fonte. Portanto, as opções para mim mais simples são:

	
  * Usar o projeto RmThread para injetar a DLL (nesse caso iniciando o processo através dele).
  * Fazer um módulo _wrapper_ para uma DLL qualquer e ser carregado de brinde.
  * Usar o WinDbg e brincar um pouco.

Por um motivo desconhecido a terceira opção me pareceu mais interessante =).

A seqüência mais simples para carregar uma DLL através do WinDbg é chamar kernel32!LoadLibrary através de um código digitado na hora, o que podemos chamar de live assembly (algo como "assembly ao vivo"). Porém, essa simples seqüência contém um pouco mais que uma dúzia de passos.

Primeiro devemos parar a execução, voltar para um ponto seguro do código e armazenar o local seguro em um registrador temporário (o WinDbg tem 20 deles, $t0 até $t19).

    <Ctrl + Break> $$ pára a execução em um ponto qualquer
    gu $$ volta para função chamadora para evitar perda do estado dos registradores
    r$t0 = @$ip $$ armazena ponteiro de instrução em registrador temporário

    Diga para o WinDbg o que vem por aí
    
    Note que usamos dois pseudo-registradores ($t0, o primeiro registrador temporário do WinDbg, e $ip, o registrador que aponta para a próxima instrução que será executada), mas só um deles possue o prefixo '@'. Esse prefixo diz ao WinDbg que o que segue é um registrador. Como o comando r já é usado com registradores, é desnecessário usá-lo para $t0. Se usarmos sintaxe C++ esse prefixo é obrigatório, enquanto na sintaxe MASM não. Porém, se não usarmos esse prefixo em registradores não-comuns (como é o caso para $ip) o WinDbg primeiro tentará interpretar o texto como um número hexadecimal. Ao falhar, tentará interpretar como um símbolo. Ao falhar novamente, ele finalmente irá tratá-lo como um registrador. A diferença na velocidade faz valer a pena digitar um caractere a mais. Faça a prova!

Parada a execução em um local seguro e armazenado o IP, em seguida podemos alocar memória para entrar o código em assembly da chamada, além do seu parâmetro, no caso o path da DLL a ser carregada.

    
    .dvalloc 0x1000 $$ alocamos memória para entrar o assembly e o parâmetro da chamada
    Allocated 1000 bytes starting at 00280000
    eza 0x00280000 "C:tempMinhaDllInvasora.dll" $$ escreve no início da memória o path da DLL
    a 0x0280000+0x100 $$ agora vamos codificar em live-assembly
    00280100 push 0x00280000 $$ empilha o parâmetro (path da DLL)
    push 0x00280000
    00280105 call kernel32!LoadLibraryA $$ chama LoadLibraryA
    call kernel32!LoadLibraryA
    0028010a int 3 $$ um breakpoint para tornar as coisas mais fáceis
    int 3
    0028010b $$ um <enter> em uma linha vazia termina a edição do live-assembly
    0:000> $$ estamos de volta no prompt do WinDbg

Note que estamos usando a versão ANSI do LoadLibrary, aquela que termina com A. Sendo assim, escrevemos uma string ANSI como parâmetro usando o comando eza.

O último passo é chamar a função previamente "editada". Para isso basta mudarmos o endereço da próxima instrução para o começo de nosso código e mandar executar, pois ele irá parar automaticamente no breakpoint que definimos "na mão", o int 3 digitado. Após a execução devemos voltar o ponteiro usando nosso backup no registrador $t0.

    
    0:000> r$ip = 0x00280000+0x100
    0:000> g
    ModLoad: 10000000 10045000   C:tempMinhaDllInvasora.dll
    ModLoad: 76390000 763ad000   C:WINDOWSsystem32IMM32.DLL
    (398.d90): Break instruction exception - code 80000003 (first chance)
    eax=10000000 ebx=7ffdd000 ecx=7c801bf6 edx=000a0608 esi=001a1f48 edi=001a1eb4
    eip=0028010a esp=0007fb24 ebp=0007fc94 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    0028010a cc              int     3 $$ esse é o breakpoint que digitamos no código
    0:000> r$ip = $t0 $$ mudando o IP para o ponto original
    *** WARNING: Unable to verify checksum for C:tempMinhaDllInvasora.dll
    0:000> g
    ModLoad: 5cb70000 5cb96000   C:WINDOWSsystem32ShimEng.dll
    ModLoad: 6f880000 6fa4a000   C:WINDOWSAppPatchAcGenral.DLL
    ModLoad: 76b40000 76b6d000   C:WINDOWSsystem32WINMM.dll
    ModLoad: 774e0000 7761d000   C:WINDOWSsystem32ole32.dll
    ...

Como pudemos ver pela saída, a DLL foi carregada e agora temos a possibilidade de chamar qualquer código que lá esteja. Como fazer isso? Provavelmente usando o mesmo método aqui aplicado. Live-assembly é o que manda 8).
