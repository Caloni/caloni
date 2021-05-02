---
date: "2008-04-11"
title: "Aprendendo assembly com o depurador"
categories: [ "code" ]
---
Além de servir para corrigir alguns [bugs escabrosos] o nosso bom e fiel amigo depurador também possui uma utilidade inusitada: ensinar assembly! A pessoa interessada em aprender alguns conceitos básicos da arquitetura do 8086 pode se exercitar na frente de um depurador 16 ou 32 bits sem ter medo de ser feliz.

Vamos ver alguns exemplos?

Para quem está começando, recomendo usar um depurador simples, 16 bits e que existe em todo e qualquer Windows: o debug. Já usado para depurar a MBR [aqui no bloque], poderá agora ser usado para ensinar alguns princípios da plataforma de uma maneira indolor. Basta iniciá-lo na linha de comando:

    debug
    -

Os comandos mais úteis são o r (ver ou alterar registradores), o t/p (executar passo-a-passo), o d (exibir memória), o u (desmontar assembly) e o a (montar assembly). Ah, não se esquecendo do ? (ajuda).

![Teste do debug 16 bits](/img/debug-testpng.png)

Outro ensinamento bem interessante diz respeito à pilha. Aprendemos sempre que a pilha cresce de cima pra baixo, ou seja, de endereços superiores para valores mais baixos. Também vimos que os registradores responsáveis por controlar a memória da pilha são o sp (stack pointer) e o ss (stack segment). Pois bem. Vamos fazer alguns testes para ver isso acontecer.

    -r
    AX=0000  BX=0000  CX=0000  DX=0000  SP=FFEE  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=0CF9  CS=0CF9  IP=0100   NV UP EI PL NZ NA PO NC
    0CF9:0100 69            DB      69
    -r ss
    SS 0CF9
    :9000
    -r sp
    SP FFEE
    :ffff
    -r
    AX=0000  BX=0000  CX=0000  DX=0000  SP=FFFF  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=9000  CS=0CF9  IP=0100   NV UP EI PL NZ NA PO NC
    0CF9:0100 69            DB      69
    -a
    0CF9:0100 mov ax, 1234
    0CF9:0103 push ax
    0CF9:0104 inc ax
    0CF9:0105 push ax
    0CF9:0106 inc ax
    0CF9:0107 push ax
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
    AX=1234  BX=0000  CX=0000  DX=0000  SP=FFFF  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=9000  CS=0CF9  IP=0103   NV UP EI PL NZ NA PO NC
    0CF9:0103 50            PUSH    AX
    -t
    
    AX=1234  BX=0000  CX=0000  DX=0000  SP=FFFD  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=9000  CS=0CF9  IP=0104   NV UP EI PL NZ NA PO NC
    0CF9:0104 40            INC     AX
    -t
    
    AX=1235  BX=0000  CX=0000  DX=0000  SP=FFFD  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=9000  CS=0CF9  IP=0105   NV UP EI PL NZ NA PE NC
    0CF9:0105 50            PUSH    AX
    -t
    
    AX=1235  BX=0000  CX=0000  DX=0000  SP=FFFB  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=9000  CS=0CF9  IP=0106   NV UP EI PL NZ NA PE NC
    0CF9:0106 40            INC     AX
    -t
    
    AX=1236  BX=0000  CX=0000  DX=0000  SP=FFFB  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=9000  CS=0CF9  IP=0107   NV UP EI PL NZ NA PE NC
    0CF9:0107 50            PUSH    AX
    -t
    
    AX=1236  BX=0000  CX=0000  DX=0000  SP=FFF9  BP=0000  SI=0000  DI=0000
    DS=0CF9  ES=0CF9  SS=9000  CS=0CF9  IP=0108   NV UP EI PL NZ NA PE NC
    0CF9:0108 6C            DB      6C
    -d 9000:fff9
    9000:FFF0                             36 12 35 12 34 12 00            6.5.4..
    -

Como vemos, ao empilhar coisas na pilha, o valor do registrador sp diminui. E ao fazermos um dump do valor de sp conseguimos ver os valores empilhados anteriormente. Isso é muito útil na hora de depurarmos chamadas de funções. Por exemplo, no velho teste do Windbg x Bloco de notas:

    windbg notepad

    0:000> bp user32!MessageBoxW
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
    USER32!MessageBoxW:
    7e3b630a 8bff            mov     edi,edi
    0:000> dd esp L5
    0007f6d8  01001fc4 00010226 000b2850 000a7ac2 ; ret   handle message caption
    0007f6e8  00000033                            ; mb_ok
    0:000> du 000b2850
    000b2850  "O texto do arquivo Sem título fo"
    000b2890  "i alterado...Deseja salvar as al"
    000b28d0  "terações?"
    0:000> ezu 000b2850 "Tem certeza que deseja salvar esse artigo de merda?"
    0:000> g
    ModLoad: 75f50000 7604d000   C:\WINDOWS\system32\BROWSEUI.dll

![WinDbg x Notepad](/img/windbgxnotepad.png)

Aposto que você sabe em qual dos três botões eu cliquei =)

Depurar é um processo que exige dedicação (experiência) tanto ou mais do que o próprio desenvolvimento. Por isso, fazer um esforço para descobrir algum problema em algum software pode ser vantajoso no futuro, pois você terá mais capacidade de entender o que está acontecendo à sua volta.

Básico a intermediário:

 - [Guia básico para programadores de primeiro breakpoint](/guia-basico-para-programadores-de-primeiro-breakpoint)
 - [Brincando com o WinDbg](/brincando-com-o-windbg)
 - [Encontrando as respostas do Flash Pops](/encontrando-as-respostas-do-flash-pops)

Intermediário a avançado:

 - [Hook de API no WinDbg](/hook-de-api-no-windbg)
 - [Hook de COM no WinDbg](/hook-de-com-no-windbg)
 - [Detectando hooks globais no WinDbg](/detectando-hooks-globais-no-windbg)
 - [Analisando dumps com WinDbg e IDA](/analisando-dumps-com-windbg-e-ida)

Blogues que eu acho superinteressantes sobre debugging (do mais essencial para o mais avançado):

 - [Advanced Windows Debugging](http://blogs.msdn.com/ntdebugging)
 - [Crash Dump Analysis](http://www.dumpanalysis.org/blog/)

[bugs escabrosos]: /analisando-dumps-com-windbg-e-ida
[aqui no bloque]: /depuracao-da-mbr
