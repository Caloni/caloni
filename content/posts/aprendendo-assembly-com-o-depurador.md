---
date: "2008-04-11"
title: Aprendendo assembly com o depurador
tags: [ "draft", "code" ]
---
Além de servir para corrigir alguns [bugs escabrosos](http://www.caloni.com.br/analisando-dumps-com-windbg-e-ida), o nosso bom e fiel amigo depurador também possui uma utilidade inusitada: ensinar _assembly_! A pessoa interessada em aprender alguns conceitos básicos da arquitetura do 8086 pode se exercitar na frente de um depurador 16 ou 32 bits sem ter medo de ser feliz.

Vamos ver alguns exemplos?

#### A pilha é você quem manda

Para quem está começando, recomendo usar um depurador simples, 16 bits e que existe em todo e qualquer Windows: o **debug**. Já usado para depurar a MBR no [Caloni.com.br](http://www.caloni.com.br/depuracao-da-mbr), poderá agora ser usado para ensinar alguns princípios da plataforma de uma maneira indolor. Basta iniciá-lo na linha de comando:

    
    debug
    -

Os comandos mais úteis são o _**r**_ (ver ou alterar registradores), o _**t**_/_**p**_ (executar passo-a-passo), o _**d**_ (exibir memória), o _**u**_ (desmontar assembly) e o _**a**_ (montar assembly). Ah, não se esquecendo do _**?**_ (ajuda).

![Teste do debug 16 bits](/images/debug-testpng.PNG)

Outro ensinamento bem interessante diz respeito à pilha. Aprendemos sempre que a pilha cresce de **cima pra baixo**, ou seja, de endereços superiores para valores mais baixos. Também vimos que os registradores responsáveis por controlar a memória da pilha são o _**sp**_ (stack pointer) e o _**ss**_ (stack segment). Pois bem. Vamos fazer alguns testes para ver isso acontecer.

    
    -r
    AX=0000  BX=0000  CX=0000  DX=0000  SP=FFEE  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=0CF9  CS=0CF9  IP=0100   NV UP EI PL NZ NA PO NC
    0CF9:0100 69            DB      69
    -r ss
    SS <font color="#000000">0CF9</font>
    :<font color="#ff0000">9000</font>
    -r sp
    SP FFEE
    :<font color="#ff0000">ffff</font>
    -r
    AX=0000  BX=0000  CX=0000  DX=0000  <font color="#ff0000">SP=FFFF</font>  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  <font color="#ff0000">SS=9000</font>  CS=0CF9  IP=0100   NV UP EI PL NZ NA PO NC
    0CF9:0100 69            DB      69
    -a
    0CF9:0100 mov ax, 1234
    0CF9:0103 <font color="#ff0000">push ax</font>
    0CF9:0104 inc ax
    0CF9:0105 <font color="#ff0000">push ax</font>
    0CF9:0106 inc ax
    0CF9:0107 <font color="#ff0000">push ax</font>
    0CF9:0108
    -u
    0CF9:0100 B83412        MOV     AX,1234
    0CF9:0103 50            PUSH    AX
    0CF9:0104 40            INC     AX
    0CF9:0105 50            PUSH    AX
    0CF9:0106 40            INC     AX
    0CF9:0107 50            PUSH    AX
    0CF9:0108 6C            DB      6C
    ...
    AX=1234  BX=0000  CX=0000  DX=0000  <font color="#ff0000">SP=FFFF</font>  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=9000  CS=0CF9  IP=0103   NV UP EI PL NZ NA PO NC
    0CF9:0103 50            PUSH    AX
    -t
    
    AX=1234  BX=0000  CX=0000  DX=0000  <font color="#ff0000">SP=FFFD</font>  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=9000  CS=0CF9  IP=0104   NV UP EI PL NZ NA PO NC
    0CF9:0104 40            INC     AX
    -t
    
    AX=1235  BX=0000  CX=0000  DX=0000  <font color="#000000">SP=FFFD</font>  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=9000  CS=0CF9  IP=0105   NV UP EI PL NZ NA PE NC
    0CF9:0105 50            PUSH    AX
    -t
    
    AX=1235  BX=0000  CX=0000  DX=0000  <font color="#ff0000">SP=FFFB</font>  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=9000  CS=0CF9  IP=0106   NV UP EI PL NZ NA PE NC
    0CF9:0106 40            INC     AX
    -t
    
    AX=1236  BX=0000  CX=0000  DX=0000  SP=FFFB  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=9000  CS=0CF9  IP=0107   NV UP EI PL NZ NA PE NC
    0CF9:0107 50            PUSH    AX
    -t
    
    AX=1236  BX=0000  CX=0000  DX=0000  <font color="#ff0000">SP=FFF9</font>  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=9000  CS=0CF9  IP=0108   NV UP EI PL NZ NA PE NC
    0CF9:0108 6C            DB      6C
    -d 9000:fff9
    9000:FFF0                             <font color="#ff9900">36 12</font> <font color="#339966">35 12</font> <font color="#0000ff">34 12</font> 00            6.5.4..
    -

Como vemos, ao empilhar coisas na pilha, o valor do registrador sp diminui. E ao fazermos um _dump_ do valor de sp conseguimos ver os valores empilhados anteriormente. Isso é muito útil na hora de depurarmos chamadas de funções. Por exemplo, no velho teste do Windbg x Bloco de notas:

    
    windbg notepad

    
    0:000> bp user32!<font color="#ff0000">MessageBoxW</font>
    0:000> g
    ModLoad: 5cfd0000 5cff6000   C:\WINDOWS\system32\ShimEng.dll
    ModLoad: 596f0000 598ba000   C:\WINDOWS\AppPatch\AcGenral.DLL
    ModLoad: 76b20000 76b4e000   C:\WINDOWS\system32\WINMM.dll
    ModLoad: 774c0000 775fd000   C:\WINDOWS\system32\ole32.dll
    ...
    ModLoad: 10000000 10030000   C:\Arquivos de programas\Babylon\Babylon-Pro\CAPTLIB.DLL
    ModLoad: 74c40000 74c6c000   C:\WINDOWS\system32\OLEACC.dll
    ModLoad: 76050000 760b5000   C:\WINDOWS\system32\MSVCP60.dll
    Breakpoint 0 hit
    eax=00000001 ebx=00000000 ecx=000a7884 edx=00000000 esi=000b2850 edi=0000000a
    eip=7e3b630a esp=0007f6d8 ebp=0007f6f4 iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    USER32!<font color="#ff0000">MessageBoxW</font>:
    7e3b630a 8bff            mov     edi,edi
    0:000> dd esp L5
    0007f6d8  01001fc4 00010226 <font color="#ff0000">000b2850</font> 000a7ac2 ; ret   handle <font color="#ff0000">message</font> caption
    0007f6e8  00000033                            ; mb_ok
    0:000> du <font color="#ff0000">000b2850</font>
    000b2850  "O texto do arquivo Sem título fo"
    000b2890  "i alterado...Deseja salvar as al"
    000b28d0  "terações?"
    0:000> ezu 000b2850 "Tem certeza que deseja salvar esse artigo de merda?"
    0:000> g
    ModLoad: 75f50000 7604d000   C:\WINDOWS\system32\BROWSEUI.dll

[![WinDbg x Notepad](http://i.imgur.com/hyDEQtn.png)](/images/windbgxnotepad.png)

Aposto que você sabe em qual dos três botões eu cliquei =)

#### Outros linques para aprender a depurar seus programas (e os dos outros)

Depurar é um processo que exige dedicação (experiência) tanto ou mais do que o próprio desenvolvimento. Por isso, fazer um esforço para descobrir algum problema em algum software pode ser vantajoso no futuro, pois você terá mais capacidade de entender o que está acontecendo à sua volta.

Básico a intermediário:

	
  * [Guia básico para programadores de primeiro breakpoint](http://www.caloni.com.br/guia-basico-para-programadores-de-primeiro-breakpoint)

	
  * [Brincando com o WinDbg](http://www.caloni.com.br/brincando-com-o-windbg)

	
  * [Encontrando as respostas do Flash Pops](http://www.caloni.com.br/encontrando-as-respostas-do-flash-pops)

Intermediário a avançado:

	
  * [Hook de API no WinDbg](http://www.caloni.com.br/hook-de-api-no-windbg)

	
  * [Hook de COM no WinDbg](http://www.caloni.com.br/hook-de-com-no-windbg)

	
  * [Detectando hooks globais no WinDbg](http://www.caloni.com.br/detectando-hooks-globais-no-windbg)

	
  * [Analisando dumps com WinDbg e IDA](http://www.caloni.com.br/analisando-dumps-com-windbg-e-ida)

Blogues que eu acho superinteressantes sobre _debugging_ (do mais essencial para o mais avançado):

	
  * [Debugging Toolbox](http://blogs.msdn.com/debuggingtoolbox/default.aspx)

	
  * [Mark's Blog](http://blogs.technet.com/markrussinovich/default.aspx)

	
  * [Advanced Windows Debugging](http://blogs.msdn.com/ntdebugging)

	
  * [Crash Dump Analysis](http://www.dumpanalysis.org/blog/)

