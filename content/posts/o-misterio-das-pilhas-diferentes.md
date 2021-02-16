---
date: "2008-03-12"
title: O mistério das pilhas diferentes
tags: [ "draft", "code" ]
---
Mal comecei a leitura do meu mais novo ["mother-fucker" livro](http://advancedwindowsdebugging.com/) e já encontrei a solução para nunca mais viver o terror que vivi quando tive que testar minha engenharia reversa do artigo sobre o Houaiss. Se trata de uma simples questão que não sei por que não sigo todas as vezes religiosamente: **configure seus símbolos corretamente**.

Esse é o primeiro ponto abordado pelo autor, por se tratar de algo que, caso não seja bem feito, pode dar dores de cabeça piores do que o próprio problema que originou a sessão de _debugging_. Por isso eu repito:

**Configure Seus Símbolos Corretamente**

Vamos acompanhar alguns momentos de tortura alheia?

#### Era uma vez

Tudo aconteceu quando inesperadamente perdi metade do [artigo que estava escrevendo](http://www.caloni.com.br/conversor-de-houaiss-para-babylon-parte-1) para explicar o processo de engenharia reversa no dicionário Houaiss. Tive que refazer todos os meus testes que havia feito no _laptop_. Como a preguiça é a mãe de todas as descobertas, não estava com ele ligado no momento do "reteste" e por isso acabei usando a máquina _desktop_, mesmo.

A análise inicial consistia simplesmente em verificar as entradas e saídas da função **ReadFile**, na esperança de entender a formatação interna do dicionário. Repetindo a seqüência:

    
    windbg -pn houaiss2.exe
    0:001> bp kernel32!ReadFile "dd @$csp L6" $$ Dando uma olhada nos parâmetros
    g

    
    0012fa70  0040a7a9 00000200 <font color="#ff0000">08bbf1d0 00000200</font>
    0012fa80  0012fa88 00000000
    eax=0012fa88 ebx=00000200 ecx=00000200 edx=08bbf1d0 esi=08bbf1d0 edi=00000200
    eip=7c80180e esp=0012fa70 ebp=0012facc iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    kernel32!ReadFile:
    7c80180e 6a20            push    20h
    $$ O buffer de saída é <font color="#ff0000">08bbf1d0 </font>
    $$ O número de bytes lidos é <font color="#ff0000">200</font>
    0:000> db 08bbf1d0 L80
    08bbf1d0  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    08bbf1e0  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    08bbf1f0  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    08bbf200  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    08bbf210  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    08bbf220  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    08bbf230  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    08bbf240  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    0:000> bp /1 @$ra "db 08bbf1d0 L80"
    0:000> g
    08bbf1d0  2a 70 72 6f 67 72 61 6d-61 2d 66 6f 6e 74 65 0d  <font color="#ff0000">*programa-fonte.</font>
    08bbf1e0  0a 43 73 2e 6d 2e 0d 0a-64 7b 5c 69 20 73 58 58  <font color="#ff0000">.Cs.m...d{\i sXX</font>
    08bbf1f0  7d 0d 0a 54 69 6e 66 0d-0a 3a 70 72 6f 67 72 61  <font color="#ff0000">}..Tinf..:progra</font>
    08bbf200  6d 61 20 64 65 20 63 6f-6d 70 75 74 61 64 6f 72  <font color="#ff0000">ma de computador</font>
    08bbf210  20 65 6d 20 73 75 61 20-66 6f 72 6d 61 20 6f 72  <font color="#ff0000"> em sua forma or</font>
    08bbf220  69 67 69 6e 61 6c 2c 20-61 6e 6f 74 61 64 6f 20  <font color="#ff0000">iginal, anotado</font>
    08bbf230  70 65 6c 6f 20 70 72 6f-67 72 61 6d 61 64 6f 72  <font color="#ff0000">pelo programador</font>
    08bbf240  20 65 6d 20 75 6d 61 20-6c 69 6e 67 75 61 67 65  <font color="#ff0000"> em uma linguage</font>
    0:000> $$
    0:000> $$ Tudo legível? Mas já? Ai, meu Deus, alguém chama uma benzedeira!
    0:000> $$

Se notarmos no artigo anterior, veremos que o conteúdo do arquivo lido **não é em texto claro**, sendo necessário passar por mais algumas instruções _assembly_ para descobrir a função responsável por embaralhar o conteúdo na memória. Contudo, ao rodar esses comandos novamente, eis que a saída do ReadFile já vem toda legível, como se o dicionário não estivesse mais encriptado.

A leitura foi feita e o texto direto do arquivo veio em claro? O que está acontecendo? Quando abro pelo comando type ele aparece todo obscuro...

[![Saída dos arquivos do dicionário](http://i.imgur.com/u3IQ3aD.gif)](/images/cmd.gif)

Sim, alguma coisa não-trivial acaba de acontecer. Testei esse procedimento no _laptop_ e no _desktop_, sendo que esse problema aconteceu apenas no _desktop_. Dessa vez a curiosidade falou mais alto que a preguiça, e tive que abrir as duas máquinas e comparar os resultados.

#### Rastreando o problema do endereço de retorno diferente

Depois de um pouco de cabeçadas rastreando o _assembly_ executado, descobri que o ponto onde o _breakpoint_ havia parado não era o retorno da chamada a ReadFile. Isso eu não vou demonstrar aqui pois se trata de raciocínio de passo-a-passo no _assembly_ até descobrir a diferença. É enfadonho e sujeito a erros. Sugiro que tente um dia desses. Para mim, o resultado lógico de tudo isso é a saída que segue:

    
    0012fa70  0040a7a9 00000200 <font color="#ff0000">08bbf1d0 00000200</font>
    0012fa80  0012fa88 00000000
    eax=0012fa88 ebx=00000200 ecx=00000200 edx=08bbf1d0 esi=08bbf1d0 edi=00000200
    eip=7c80180e esp=0012fa70 ebp=0012facc iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    kernel32!ReadFile:
    7c80180e 6a20            push    20h
    0:000> ? <font color="#ff0000">poi(esp)</font>
    Evaluate expression: 4237225 = <font color="#ff0000">0040a7a9</font>
    0:000> ? <font color="#ff6600">@$ra</font>
    Evaluate expression: 4959640 = <font color="#ff6600">004bad98</font>
    0:000> ? <font color="#ff0000">poi(@$csp)</font>
    Evaluate expression: 4237225 = <font color="#ff0000">0040a7a9 </font>

Como podemos ver pelos comandos acima, o pseudo-registrador $ra não está mostrando o valor corretamente!

#### Primeiro passo lógico: o seu é o mesmo que o meu?

A primeira coisa que se faz numa hora dessas é comparar as versões dos componentes do depurador de ambos os ambientes. Para isso usamos o comando **version**.

    
    0:000> version <font color="#ff6600">$$ desktop</font>
    Windows XP Version 2600 (Service Pack 2) UP Free x86 compatible
    Product: WinNt, suite: SingleUserTS
    kernel32.dll version:
    Debug session time: Tue Feb 26 19:51:58.295 2008 (GMT-3)
    System Uptime: 0 days 1:14:07.857
    Process Uptime: 0 days 0:31:52.840
      Kernel time: 0 days 0:00:01.482
      User time: 0 days 0:00:02.723
    Live user mode: <Local>
    command line: '"C:\Tools\DbgTools\windbg.exe" -pn houaiss2.exe'  Debugger Process 0xEC4
    dbgeng:  image <font color="#ff6600">6.6.0007.5</font>, built Sat Jul 08 17:12:40 2006
            [path: C:\Tools\DbgTools\dbgeng.dll]
    dbghelp: image <font color="#ff6600">6.6.0007.5</font>, built Sat Jul 08 17:11:32 2006
            [path: C:\Tools\DbgTools\dbghelp.dll]
            DIA version: 60516
    Extension DLL search Path:
        C:\Tools\DbgTools\winext;C:\Tools\DbgTools\winext\arcade;(...)
    Extension DLL chain:
        dbghelp: image 6.6.0007.5, API 6.0.6, built Sat Jul 08 17:11:32 2006
            [path: C:\Tools\DbgTools\dbghelp.dll]
        ext: image 6.6.0007.5, API 1.0.0, built Sat Jul 08 17:10:52 2006
            [path: C:\Tools\DbgTools\winext\ext.dll]
        exts: image 6.6.0007.5, API 1.0.0, built Sat Jul 08 17:10:48 2006
            [path: C:\Tools\DbgTools\WINXP\exts.dll]
        uext: image 6.6.0007.5, API 1.0.0, built Sat Jul 08 17:11:02 2006
            [path: C:\Tools\DbgTools\winext\uext.dll]
        ntsdexts: image 6.0.5457.0, API 1.0.0, built Sat Jul 08 17:29:38 2006
            [path: C:\Tools\DbgTools\WINXP\ntsdexts.dll]

    
    0:000> version <font color="#ff6600">$$ laptop</font>
    Windows XP Version 2600 (Service Pack 2) UP Free x86 compatible
    Product: WinNt, suite: SingleUserTS Personal
    kernel32.dll version:
    Debug session time: Tue Feb 26 20:54:39.718 2008 (GMT-3)
    System Uptime: 9 days 10:26:39.289
    Process Uptime: 0 days 0:00:56.359
      Kernel time: 0 days 0:00:00.406
      User time: 0 days 0:00:01.078
    Live user mode: <Local>
    command line: '"C:\Tools\DbgTools\windbg.exe" -pn houaiss2.exe'  Debugger Process 0x864
    dbgeng:  image <font color="#ff6600">6.8.0004.0</font>, built Thu Sep 27 18:28:09 2007
            [path: C:\Tools\DbgTools\dbgeng.dll]
    dbghelp: image <font color="#ff6600">6.8.0004.0</font>, built Thu Sep 27 18:27:05 2007
            [path: C:\Tools\DbgTools\dbghelp.dll]
            DIA version: 20119
    Extension DLL search Path:
        C:\Tools\DbgTools\WINXP;C:\Tools\DbgTools\winext;C:\(...)
    Extension DLL chain:
        dbghelp: image 6.8.0004.0, API 7.0.6, built Thu Sep 27 18:27:05 2007
            [path: C:\Tools\DbgTools\dbghelp.dll]
        ext: image 6.8.0004.0, API 1.0.0, built Thu Sep 27 18:26:59 2007
            [path: C:\Tools\DbgTools\winext\ext.dll]
        exts: image 6.8.0004.0, API 1.0.0, built Thu Sep 27 18:26:28 2007
            [path: C:\Tools\DbgTools\WINXP\exts.dll]
        uext: image 6.8.0004.0, API 1.0.0, built Thu Sep 27 18:26:45 2007
            [path: C:\Tools\DbgTools\winext\uext.dll]
        ntsdexts: image 7.0.6440.1, API 1.0.0, built Thu Sep 27 18:45:23 2007
            [path: C:\Tools\DbgTools\WINXP\ntsdexts.dll]

OK. A versão instalada no _desktop_ é bem antiga. Pode ser um indício. Fiz então a atualização e comparei novamente a saída de version.

Tudo igual.

#### Segundo passo lógico: prove ou refute seu raciocínio

Decidi então usar aquela lógica cética que é desenvolvida por quem costuma depurar coisas sinistras e esotéricas por anos e anos e não duvida de mais nada, mas também acredita piamente que **tudo tem um motivo**. Se não está aparente, basta descobri-lo. E foi o que eu fiz. Gerei dois _dumps _distintos, um no _laptop_ e outro no _desktop_. Ambos estavam com os ponteiros de instrução apontados exatamente para a entrada da função ReadFile, início de todo esse problema. Copiei o _dump_ do _desktop_ para o _laptop_ e vice-versa.

[![WinDbg Nerd](http://i.imgur.com/qPcDz79.gif)](/images/windbg-nerd.gif)

Abri o _dump_ do _desktop_ no _laptop_: tudo funcionando. Abri o _dump_ do _laptop _no _desktop_: mesmo erro.

Conclusão óbvia: é algo relacionado com o WinDbg no _desktop_, uma vez que o estado da pilha que era mostrado corretamente no _laptop _em ambos os _dumps_ falhava duplamente na máquina _desktop._

#### Próxima tentativa intuitiva: verificar o _path _dos símbolos:

    
    .sympath
    Symbol search path is: <empty>

Isso com certeza não cheira bem. Ainda mais porque do outro lado do hemisfério, meu _laptop_ estava configurado com toda a rigidez que um _laptop_ de WinDbgeiro deve ter:

    
    0:000> .sympath
    Symbol search path is: SRV*C:\Symbols*http://msdl.microsoft.com/download/symbols

E aí estava uma diferença plausível. Consertados os diretórios de símbolos, tudo voltou ao normal.

#### Moral da história

Procure primeiro verificar as coisas mais simples. Depois você tenta consertar o universo. Mas, primeiro, antes de tudo, veja se o cabo de rede está conectado. Ou no nosso cado de debugueiro:

**Configure Seus Símbolos Corretamente**
