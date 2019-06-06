---
date: "2007-11-27"
title: Carregando DLLs arbitrárias pelo WinDbg - parte 2
categories: [ "code" ]
---
Como pudemos ver no [artigo anterior](http://www.caloni.com.br/carregando-dlls-arbitrarias-pelo-windbg), o processo para carregar uma DLL pelo WinDbg é muito extenso, enfadonho e sujeito a erros. Por esse motivo, e para tornar as coisas mais divertidas, resolvi transformar tudo aquilo em um simples _script_ que pode ser executado digitando apenas uma linha.

Se trata do meu primeiro _script_ grande para o WinDbg, por isso, peço que tenham dó de mim =).

#### _Scripts_ para o WinDbg

Um _script_ no WinDbg nada mais é que uma execução em _batch_: um arquivo texto cheio de comandos que poderíamos digitar manualmente, mas que preferimos guardar para poupar nossos dedos.

Existem quatro maneiras diferentes de chamar um _script _no WinDbg, todas muito parecidas, variando apenas se são permitidos espaços antes do nome do arquivo e se os comandos são **condensados**, isto é, as quebras de linhas substituídas por ponto-e-vírgula para executar tudo em uma linha só.

	
  * **$<**nome-do-arquivo - não permite espaços e condensa comandos.

	
  * **$><**nome-do-arquivo - não permite espaços e não condensa comandos.

	
  * **$$<**nome-do-arquivo - permite espaços e condensa comandos.

	
  * **$$><**nome-do-arquivo - permite espaços e não condensa comandos.

	
  * **$$>a<**nome-do-arquivo - igual ao anterior, e ainda permite passar argumentos.

<blockquote>_Obs.: a ajuda do WinDbg descreve as diferenças dos comandos acima de forma adversa, afirmando que os comandos '<'  não condensam as linhas e os '><' o fazem, quando na realidade é o contrário. Não se deixe enganar por esse detalhe._</blockquote>

No caso do _script_ desse artigo, utilizaremos a última forma, pois precisamos de um argumento para funcionar: **o nome da DLL**. Caso você não digite esse argumento, a ajuda do _script_ será impressa:

    
    How to use:
    $$>a<path\LoadLibrary.txt mydll.dll
    $$>a<path\LoadLibrary.txt c:\\path\\mydll.dll
    $$>a<path\LoadLibrary.txt "c:\\path with space\\mydll.dll"

#### Modo de usar

Não há qualquer dificuldade. Tudo que você tem que fazer é baixar o [_script_ que carrega DLLs](/images/loadlibrary.txt) e salvá-lo em um lugar de sua preferência. Depois é só digitar o comando que carrega _scripts_, o _path_ de nosso _script_ e o nome da DLL a ser carregada em uma das três formas exibidas. Eu costumo criar uma pasta chamada "_scripts_" dentro do diretório de instalação do Debugging Tools, o que quer dizer que posso simplesmente chamar todos meus _scripts_ (ou seja, 1) dessa maneira:

    
    $$>a<scripts\LoadLibrary.txt mydll.dll

Abaixo um pequeno teste que fiz carregando a DLL do Direct Draw (ddraw.dll) na nossa vítima de plantão:

    
    <font color="#ff0000">windbg notepad.exe</font>
    Microsoft (R) Windows Debugger Version 6.8.0004.0 X86
    Copyright (c) Microsoft Corporation. All rights reserved.
    CommandLine: notepad.exe
    Symbol search path is: SRV*C:\Symbols*http://msdl.microsoft.com/downloads/symbols
    Executable search path is:
    ModLoad: 01000000 01014000   notepad.exe
    ModLoad: 7c900000 7c9b0000   ntdll.dll
    ModLoad: 7c800000 7c8f5000   C:\WINDOWS\system32\kernel32.dll
    ...
    ModLoad: 73000000 73026000   C:\WINDOWS\system32\WINSPOOL.DRV
    (8e8.214): Break instruction exception - code 80000003 (first chance)
    eax=001a1eb4 ebx=7ffdf000 ecx=00000000 edx=00000001 esi=001a1f48 edi=001a1eb4
    eip=7c901230 esp=0007fb20 ebp=0007fc94 iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    ntdll!DbgBreakPoint:
    7c901230 cc              int     3
    0:000> <font color="#ff0000">$$>a<scripts\LoadLibrary.txt ddraw.dll</font>
    <font color="#ff0000">Trying to load the following module:
    00280000  "ddraw.dll"
    </font>ModLoad: 73760000 737a9000   C:\WINDOWS\system32\<font color="#ff0000">ddraw.dll</font>
    ModLoad: 73bc0000 73bc6000   C:\WINDOWS\system32\DCIMAN32.dll
    ModLoad: 76390000 763ad000   C:\WINDOWS\system32\IMM32.DLL
    ModLoad: 629c0000 629c9000   C:\WINDOWS\system32\LPK.DLL
    ModLoad: 74d90000 74dfb000   C:\WINDOWS\system32\USP10.dll
    Freed 0 bytes starting at 00280000
    eax=001a1eb4 ebx=7ffdf000 ecx=00000000 edx=00000001 esi=001a1f48 edi=001a1eb4
    eip=7c901230 esp=0007fb20 ebp=0007fc94 iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    ntdll!DbgBreakPoint:
    7c901230 cc              int     3

Simples e indolor.

#### Entendendo o código

Vamos agora dar uma olhada no _script_ completo e dissecar as linhas pausadamente. Dessa forma entenderemos como a função inteira funciona e como usar os comandos isoladamente para criar novos _scripts_.

    
    <font color="#339966">$$
    $$ @brief Loads a module inside the debuggee process.
    $$ @author Wanderley Caloni <wanderley@caloni.com.br>
    $$ @date 2007-11
    $$
    </font>.if( <font color="#000000">${/d:</font><font color="#0000ff">$arg1</font>} )
    {
        r <font color="#ff9900">$t2</font> = @<font color="#0000ff">$ip</font>
        .foreach /pS 5 ( addr { .dvalloc 0x1000 } ) { r<font color="#ff00ff">$t0</font> = addr }
        r <font color="#ff0000">$t1</font> = @<font color="#ff00ff">$t0</font> + 0x100
        eza @<font color="#ff00ff">$t0</font> "${<font color="#0000ff">$arg1</font>}"
        .echo Trying to load the following module:
        da @<font color="#ff00ff">$t0</font>
        <font color="#339966">$$ push </font><font color="#339966">$ip</font>
        eb @<font color="#ff0000">$t1</font> 0x68
        ed @<font color="#ff0000">$t1</font> + 0x01 @<font color="#ff6600">$t2</font>
    <font color="#339966">    $$ pushfd</font>
        eb @<font color="#ff0000">$t1</font> + 0x05 0x9c
    <font color="#339966">    $$ pushad</font>
        eb @<font color="#ff0000">$t1</font> + 0x06 0x60
    <font color="#339966">    $$ push </font><font color="#339966">$t0</font>
        eb @<font color="#ff0000">$t1</font> + 0x07 0x68
        ed @<font color="#ff0000">$t1</font> + 0x08 @<font color="#ff00ff">$t0</font>
    <font color="#339966">    $$ call LoadLibrary</font>
        eb @<font color="#ff0000">$t1</font> + 0x0c 0xe8
        ed @<font color="#ff0000">$t1</font> + 0x0d ( kernel32!LoadLibraryA - @<font color="#ff0000">$t1</font> - 0x11 )
    <font color="#339966">    $$ popad</font>
        eb @<font color="#ff0000">$t1</font> + 0x11 0x61
    <font color="#339966">    $$ popfd</font>
        eb @<font color="#ff0000">$t1</font> + 0x12 0x9d
    <font color="#339966">    $$ ret</font>
        eb @<font color="#ff0000">$t1</font> + 0x13 0xc3
        r <font color="#0000ff">$ip</font> = @<font color="#ff0000">$t1</font>
        bp /1 @<font color="#ff6600">$t2</font> ".dvfree @<font color="#ff00ff">$t0</font> 0"
        g
    }
    .else
    {
       .echo How to use:
       .echo $$>a<path\LoadLibrary.txt mydll.dll
       .echo $$>a<path\LoadLibrary.txt c:\\path\\mydll.dll
       .echo $$>a<path\LoadLibrary.txt "c:\\path with space\\mydll.dll"
    }

Como podemos ver, ele é um pouco grandinho. Por isso mesmo que ele é um _script_, já que não precisamos, sempre que formos usar este comando, ficar olhando para o fonte.

Por falar em olhar, uma primeira olhada revela a seguinte estrutura:

    
    .if( <font color="#000000">${/d:</font><font color="#0000ff">$arg1</font>} )
    {
       ...
    }
    .else
    {
       ...
    }

Qualquer semelhança com as instruções em C não é mera coincidência. Essa estrutura de fato verifica se o resultado dentro do .if é verdadeiro. No caso o _script_ verifica se o primeiro parâmetro foi passado, já que os argumentos são acessíveis através dos _alias_ (apelidos) **$arg1 - $argn**. Essa maneira de usar os argumentos passados no WinDbg ainda não foi documentada, mas encontrei essa dica em [um artigo do Roberto Farah](http://blogs.msdn.com/debuggingtoolbox/archive/2007/05/03/windbg-script-get-portable-executable-headers.aspx), um grande escritor de _scripts_ para o WinDbg.

Da mesma forma, o que não deve ser nenhuma surpresa, o WinDbg suporta comentários. Todas as linhas que contêm '$$' isoladamente são comentários, e seu conteúdo da direita é ignorado, salvo se for encontrado um ponto-e-vírgula.

A primeira coisa que fazemos para carregar a DLL é salvar o estado do registrador IP, que indica onde está a próxima instrução:

    
        r <font color="#ff9900">$t2</font> = @<font color="#0000ff">$ip</font>

Feito isso, usamos um comando não tão comum, mas que pode ser muito útil nos casos em que precisamos capturar algum dado da saída de um comando do WinDbg e usá-lo em outro comando.

#### .foreach

A estrutura do .foreach deixa o usuário especificar dois grupos de comandos: o primeiro grupo irá gerar uma saída que pode ser aproveitada no segundo grupo.

    
    .foreach /pS 5 <font color="#339966">$$pula;</font> ( <font color="#ff0000">addr</font> <font color="#339966">$$alias;</font> { .dvalloc 0x1000 <font color="#339966">$$saída;</font> } ) { r<font color="#ff00ff">$t0</font> = <font color="#ff0000">addr</font> }

A opção **"/pS 5"** diz ao comando para pular 5 posições antes de capturar o _token_ que será usado no próximo comando. Os _tokens_ são divididos por espaço. Sendo a saída de **".dvalloc 0x1000"**

    
    Allocated 1000 bytes starting at 00280000

Pulando 5 posições iremos capturar o endereço onde a memória foi alocada. E é isso mesmo que queremos!

    
    1         2    3     4        <font color="#ff0000">5</font>  6
    Allocated 1000 bytes starting at <font color="#ff0000">00280000</font>

O sinônimo do endereço (_alias_) se torna **"addr"**, apelido que usamos ao executar o segundo comando, que armazena o endereço no registrador temporário $t0:

    
    r<font color="#ff00ff">$t0</font> = addr

Após alocada a memória, gravamos o parâmetro de LoadLibrary, o _path_ da DLL a ser carregada, em seu início.

    
    eza @<font color="#ff00ff">$t0</font> "${<font color="#0000ff">$arg1</font>}"

O código _assembly _que irá chamar fica um ponto à frente, mas na mesma memória alocada.

    
    r <font color="#ff0000">$t1</font> = @<font color="#ff00ff">$t0</font> + 0x100

#### _Script assembly_

Conforme as técnicas vão cada vez ficando mais "não-usuais", mais difícil fica achar um nome para a coisa. Essa técnica de escrever o _assembly_ de um código através de escritas em hexadecimal dentro de um _script_ do WinDbg eu chamei de _"script assembly_". Se tiver um nome melhor, não se acanhe em usá-lo. E me deixe saber =).

    
        <font color="#339966">$$ push </font><font color="#339966">$ip</font>
        eb @<font color="#ff0000">$t1</font> 0x68
        ed @<font color="#ff0000">$t1</font> + 0x01 @<font color="#ff6600">$t2</font>
    <font color="#339966">    $$ pushfd</font>
        eb @<font color="#ff0000">$t1</font> + 0x05 0x9c
    <font color="#339966">    $$ pushad</font>
        eb @<font color="#ff0000">$t1</font> + 0x06 0x60
    <font color="#339966">    $$ push </font><font color="#339966">$t0</font>
        eb @<font color="#ff0000">$t1</font> + 0x07 0x68
        ed @<font color="#ff0000">$t1</font> + 0x08 @<font color="#ff00ff">$t0</font>
    <font color="#339966">    $$ call LoadLibrary</font>
        eb @<font color="#ff0000">$t1</font> + 0x0c 0xe8
        ed @<font color="#ff0000">$t1</font> + 0x0d ( kernel32!LoadLibraryA - @<font color="#ff0000">$t1</font> - 0x11 )
    <font color="#339966">    $$ popad</font>
        eb @<font color="#ff0000">$t1</font> + 0x11 0x61
    <font color="#339966">    $$ popfd</font>
        eb @<font color="#ff0000">$t1</font> + 0x12 0x9d
    <font color="#339966">    $$ ret</font>
        eb @<font color="#ff0000">$t1</font> + 0x13 0xc3

Cada comentário de uma instrução em _assembly_ é seguido pela escrita dessa instrução usando o comando **e**. Se trata de um código bem trivial, fora alguns detalhes que merecem mais atenção.

#### pushfd, pushad, popad, popfd

Os comandos acima servem para salvar e restaurar o estado dos registradores e das flags de execução. Isso permite que possamos executar o código virtualmente em qualquer posição que pararmos no código depurado, já que retornamos tudo como estava ao final da execução do LoadLibrary. É claro que isso não garante que o código estará 100% estável em todas as condições, mas já ajuda um bocado.

#### call

Uma chamada através do opcode **call** (código em hexa 0xe80c) é bem comum e se trata de uma **chamada relativa**, baseada no estado do _Instruction Pointer_ atual mais o valor especificado. Por isso mesmo que fazemos o cálculo usando o endereço de onde será escrita a próxima instrução, que é o valor que teremos em IP quando este **call** for executado:

    
    ( kernel32!LoadLibraryA - <font color="#ff0000">@$t1 - 0x11</font> )

Quando o código estiver completamente escrito na memória alocada, um _disassembly_ dele retornará algo parecido com o código abaixo:

    
    push    offset ntdll!DbgBreakPoint (7c901230) <font color="#339966">; empilhamos o IP atual (endereço de retorno)</font>
    pushfd <font color="#339966">; salva estado das flags atual</font>
    pushad <font color="#339966">; salva estado dos registradores atual</font>
    push    8F0000h <font color="#339966">; empilha endereço do path da dll a ser carregada</font>
    call    kernel32!LoadLibraryA (7c801d77) ; chamamos LoadLibraryA
    popad <font color="#339966">; restaura estado dos registradores</font>
    popfd <font color="#339966">; restaura estado das flags</font>
    ret <font color="#339966">; retorna para o ponto onde o depurador parou (no caso, 7c901230)</font>

Você pode ver com seus próprio olhos se editar o _script_ comentando o último comando (g), executando o _script_ e executando o _disassembly_ do IP.

    
    u @$ip

#### Limpando a bagunça

Somos um _script_ bem comportado (na medida do possível) e por isso colocamos um _breakpoint_ temporário no final para, quando retornarmos para o código atual, desalocarmos a memória usada para a escrita e execução das instruções.

    
    bp /1 @<font color="#ff6600">$t2</font> ".dvfree @<font color="#ff00ff">$t0</font> 0"

#### _Disclaimer _e outras histórias

Eu não me responsabilizo por qualquer (mau) uso do _script_ aqui disponibilizado, assim como as eventuais perdas de código-fonte, trilhas de HD e placas de memória RAM pela sua execução. Assim sendo, bom divertimento.

#### Atualização

O criador do [DriverEntry](http://www.driverentry.com.br) me questionou se não seria mais fácil, em vez de escrever todos os opcodes em hexa, usar o comando **a**, que permite entrar o código _assembly_ diretamente a partir de um endereço especificado. Essa realmente é uma ótima idéia, e de fato eu tentei isso no começo de meus testes. Porém, infelizmente para _scripts_ isso não funciona bem. A partir do comando **a** o _prompt_ fica esperando uma entrada do usuário, não lendo o _assembly_ que estaria no próprio _script_. Pior ainda, a escrita do _assembly_ não permite usar os registradores temporários, como $t0 ou $t1, o que nos força a escrever um código dependende de valores constantes. Por esses motivos, tive que apelar para o comando **e**, que é a forma mais confusa de escrever e entender _assembly. _Nesse tipo de edição é vital comentar bem cada linha que se escreve.
