---
date: "2007-10-30"
title: "Brincando com o WinDbg (alterando mensagem de erro no Bloco de Notas / Notepad)"
tags: [ "code", "draft" ]
---
No [primeiro artigo sobre o WinDbg] usamos o aplicativo Logger para verificar as funções APIs que são chamadas por um determinado programa. Agora iremos dar um passo adiante e depurar de fato um aplicativo qualquer, com o detalhe que não teremos o código-fonte.

Existem duas maneiras de depurar um programa localmente usando o WinDbg: iniciá-lo pelo próprio WinDbg ou conectar o depurador (attach) em um programa já em execução. Podemos especificar o que faremos direto na linha de comando ou pela sua interface. Pela linha de comando podemos usar os comandos windbg notepad.exe, windbg -pn notepad.exe e windbg -p pid. Pela interface são os conhecidos itens do menu File: Open Executable e Attach to a Process.

Para variar, iremos depurar o Bloco de Notas, o maravilhoso editor de textos da Microsoft e plataforma de testes para serviços, GINAs e drivers. Para começar, poderemos usar quaisquer das opções anteriores, o que nos levará para uma saída poluída como a seguinte:
    
    Microsoft (R) Windows Debugger  Version 6.7.0005.1
    Copyright (c) Microsoft Corporation. All rights reserved.
    
    CommandLine: notepad.exe
    Symbol search path is: SRV*C:Symbols*http://msdl.microsoft.com/downloads/symbols
    Executable search path is:
    ModLoad: 01000000 01014000   notepad.exe
    ModLoad: 7c900000 7c9b0000   ntdll.dll
    ModLoad: 7c800000 7c8f5000   C:\WINDOWS\system32\kernel32.dll
    ModLoad: 763b0000 763f9000   C:\WINDOWS\system32\comdlg32.dll
    ModLoad: 77f60000 77fd6000   C:\WINDOWS\system32\SHLWAPI.dll
    ModLoad: 77dd0000 77e6b000   C:\WINDOWS\system32\ADVAPI32.dll
    ModLoad: 77e70000 77f01000   C:\WINDOWS\system32\RPCRT4.dll
    ModLoad: 77f10000 77f57000   C:\WINDOWS\system32\GDI32.dll
    ModLoad: 7e410000 7e4a0000   C:\WINDOWS\system32\USER32.dll
    ModLoad: 77c10000 77c68000   C:\WINDOWS\system32\msvcrt.dll
    ModLoad: 773d0000 774d3000   C:WINDOWS\WinSxSx86_Microsoft.Windows.Common-Controls_Sbrubles
    ModLoad: 7c9c0000 7d1d5000   C:\WINDOWS\system32\SHELL32.dll
    ModLoad: 73000000 73026000   C:\WINDOWS\system32\WINSPOOL.DRV
    (df8.e28): Break instruction exception - code 80000003 (first chance)
    eax=001a1eb4 ebx=7ffd5000 ecx=00000000 edx=00000001 esi=001a1f48 edi=001a1eb4
    eip=7c901230 esp=0007fb20 ebp=0007fc94 iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    ntdll!DbgBreakPoint:
    7c901230 cc              int     3

Não se preocupe, nada aconteceu de errado. Essa é apenas a maneira do WinDbg de dizer "oi, estou aqui, positivo e operando". Vamos destrinchar as informações iniciais para evitar confusão:

 - Version: versão que está sendo executada do WinDbg (duh).
 - CommandLine: linha de comando que foi usada ao executar o depurador.
 - ModLoad: sempre que um módulo é carregado no processo (DLLs ou o próprio executável) o WinDbg informa os endereços inicial e final de carregamente e o nome do módulo. Para rever a lista de módulos carregados usa-se o comando lm.
 - (<pid>.<tid>): Break instruction exception - code 8000003 (first chance). Qualquer informação específica de uma thread é informada dessa maneira no WinDbg. No caso, foi a exceção de breakpoint (parada na execução) acionada no começo da depuração (e é por isso que o notepad ainda não está aparecendo).

Explicado o começo o resto é fácil. Para continuar a execução do bloco de notas basta usarmos o comando g (Go), ou pressionar F5, ou ir no menu "Debug, Go", ou ainda apertar um dos botões de fluxo do depurador listado no seu toolbar:

![Windbg debug buttons](/img/debug_windbg.png)

Nos depuradores mais comums você terá todas essas opções ao seu dispor e nos comandos mais incomuns tudo o que você terá será o prompt de comando do WinDbg e a ajuda, acionada por F1 ou pelo comando .hh <tópico>. Geralmente os comandos do WinDbg possuem milhares de parâmetros e é considerada atitude sábia olhar de vez em quando o que alguns desses parâmetros significam para que, aos poucos, aprenda-se alguns truques até a chegada da iluminação completa, onde seu espírito irá fluir livremente pela memória de todos os processos do sistema.

Por enquanto, basta apertar g seguido de ENTER.

A tempo: após executar g mais um monte daquelas mensagens cheias de caracteres irão aparecer. Não se preocupe. Elas realmente não são importantes no momento, mas é importante saber o básico, que é "o WinDbg está avisando você de tudo o que ocorre". No momento certo saberemos usar as informações na tela quando houver necessidade.

Vamos fazer algo não tão esperto para ver como o bloco de notas reage. Tente abrir um arquivo com um nome inexistente:

![Notepad File Not Found](/img/notepad_file_not_found.png)

Como podemos ver o Bloco de Notas exibe uma mensagem de erro indicando que o arquivo cujo nome você digitou não existe, pede para você verificar a [orografia] e tudo o mais. O importante aqui não é que você não sabe digitar nomes de arquivos, mas sim qual a função que o notepad usa para exibir sua mensagem de erro. Na versão original deste post esta função era a MessageBox, e eu seguia explicando o protótipo da função e seus argumentos. Hoje, 2021-03-07, no Windows 10, descubro que o MessageBox não é mais usado, dando lugar ao ShellMessageBoxW. Como eu descobri isso? Bom, eu segui os mesmos passos do post original e coloquei um breakpoint em MessageBox e executei novamente a abertura de um arquivo inválido e... o breakpoint não disparou. Nesse caso eu dei uma olhada na pilha de chamada de todas as threads para encontrar alguma thread que chamou funções de janela. Para isso você pode usar o comando ~*kvn (para todas as threads exiba a pilha de chamadas no modo verbose).

Na saída abaixo você pode encontrar essa chamada na primeira thread, a 2b14.30f8, no stack frame 0x0e.

    0:003> ~* kvn
    
       0  Id: 2b14.30f8 Suspend: 1 Teb: 000000b7`5be5b000 Unfrozen
     # Child-SP          RetAddr               : Args to Child                                                           : Call Site
    00 000000b7`5bdbd6f8 00007ff9`c74e078e     : 00000000`ffffffff 00007ff9`ae84cd4c 000000b7`00000000 00000000`00000001 : win32u!NtUserMsgWaitForMultipleObjectsEx+0x14
    01 000000b7`5bdbd700 00007ff9`ae85352b     : 00000211`41e83718 00007ff9`c87d0454 00000000`00000001 00000000`000000e5 : USER32!RealMsgWaitForMultipleObjectsEx+0x1e
    02 000000b7`5bdbd740 00007ff9`ae853422     : 00000000`ffffffff 00000000`00000000 00000000`008f06b6 00000000`00000410 : DUser!CoreSC::WaitMessage+0xeb
    03 000000b7`5bdbd7b0 00007ff9`c74edbe1     : 00000000`00000000 00000000`00000001 00000000`00000121 00007ff9`c74cde1b : DUser!MphWaitMessageEx+0x62
    04 000000b7`5bdbd7e0 00007ff9`c87d0454     : 00000000`00000001 00000002`00000001 00000000`0000412a 00000000`00000000 : USER32!_ClientWaitMessageExMPH+0x21
    ...
    0a 000000b7`5bdbd9e0 00007ff9`b14545e7     : 00000000`00000000 00000000`00000000 00000000`00000000 00000000`00000187 : USER32!DialogBoxIndirectParamW+0x18
    0b 000000b7`5bdbda20 00007ff9`b145456e     : 15e684dc`00000800 00000000`00000000 00000000`00000000 000000b7`5bdbdb20 : COMCTL32!SHFusionDialogBoxIndirectParam+0x57
    0c 000000b7`5bdbda60 00007ff9`c748cf3e     : 00000211`479c00a0 00000000`00000000 000000b7`5bdbdbf0 000000b7`5bdbdb20 : COMCTL32!CTaskDialog::Show+0x122
    0d 000000b7`5bdbdab0 00007ff9`c747959e     : 00000000`00000000 00000000`00220a9c 00000000`00000000 00000000`00220a9c : shlwapi!TaskDialogIndirect+0x56
    0e 000000b7`5bdbdaf0 00007ff9`c68f92cd     : 00000000`00000000 00000211`47a57dd0 00000211`41e69208 00007ff9`c74cde1b : shlwapi!ShellMessageBoxW+0x18e
    0f 000000b7`5bdbdcc0 00007ff9`c68bf17c     : 00000000`80070002 000000b7`5bdbdda9 00000000`00000000 00000000`00000000 : comdlg32!_DisplayErrorMessage+0x291
    ...
    24 000000b7`5bdbeb30 00007ff9`c68b609a     : 00000000`00000000 000000b7`00000000 00000211`00000004 000000b7`5bdbed68 : USER32!DialogBoxIndirectParamW+0x18
    25 000000b7`5bdbeb70 00007ff9`c6893084     : 00000211`41e69090 00000211`00000000 00000211`41e69098 00000003`00000003 : comdlg32!<lambda_3a7baec315efe719b0d1bc9a8eafe6df>::operator()+0xee
    26 000000b7`5bdbebc0 00007ff6`2c3987ae     : 00000000`00000000 00000000`008e07ea 00000000`00000000 000000b7`5bdbf0a8 : comdlg32!CFileOpenSave::Show+0xa34
    27 000000b7`5bdbef80 00007ff6`2c398aff     : 00000000`00000000 00000000`00001808 00000000`008e07ea 00000000`00000000 : notepad!ShowOpenSaveDialog+0xfe
    ...

Essa é uma função equivalente à antiga MessageBox, cujo protótipo é int ShellMessageBoxW(HINSTANCE hAppInst, HWND hWnd, LPCWSTR lpcText, LPCWSTR lpcTitle, UINT fuStyle, ...), ou seja, uma função que recebe cinco ou mais parâmetros: o handle da instância caso a string passada esteja em um resource, o handle da janela pai, o texto da mensagem, o título e flags de exibição. As reticências ao final do protótipo indicam que ele pode conter mais argumentos.

Sabendo que o notepad não usa mais MessageBox, vamos colocar um singelo breakpoint nessa outra função API. Para parar a execução do notepad, podemos digitar "Ctrl + Break" ou ir no menu "Debug, break" ou ainda... bem, você pegou o espírito da coisa. Na linha de comando após o break digite bp shlwapi!ShellMessageBoxW seguido de g e ENTER novamente.

Note que utilizei o prefixo shlwapi! para especificar que a função está no módulo shlwapi.dll, mas não seria necessário já que o WinDbg procura por qualquer função digitada na sua lista de funções exportadas e símbolos atuais. Contudo, fazer isso torna as coisas mais rápidas e evita perder tempo à toa.

Agora podemos efetuar a mesma operação de abrir um arquivo inexistente no bloco de notas que a execução irá parar no início da função ShellMessageBoxW da API:

    Breakpoint 0 hit
    shlwapi!ShellMessageBoxW:
    00007ff9`c7479410 4055            push    rbp
    0:000> r
    rax=00007ff9c6933000 rbx=0000000000000187 rcx=00007ff9c6880000
    rdx=0000000000220a9c rsi=0000000000000001 rdi=00000211479d6030
    rip=00007ff9c7479410 rsp=000000b75bdbd728 rbp=00000211479ba190
     r8=0000000000000187  r9=0000000000000000 r10=0000021148ed1ae0
    r11=000000b75bdbd2c8 r12=0000000000000000 r13=0000000000000000
    r14=0000000000220a9c r15=0000000000000000
    iopl=0         nv up ei pl zr na po nc
    cs=0033  ss=002b  ds=002b  es=002b  fs=0053  gs=002b             efl=00000246
    shlwapi!ShellMessageBoxW:
    00007ff9`c7479410 4055            push    rbp
    
Analisando pela convenção de chamada x64 sabemos que o terceiro parâmetro, lpcText, está em r8 e é um ID do resource. O que valida essa análise é também o primeiro parâmetro, a instância do módulo que contém os resources que serão usados para carregar a mensagem, que fica em rcx e não está zerado (ele aponta para o módulo commdlg32.dll). Dessa forma nossa tarefa se torna particularmente mais difícil, pois para encontrar a string usada na mensagem de erro seria necessário buscar no meio dos resources dessa DLL.

No entanto, vou realizar aqui brincadeira semelhante ao post original, que é alterar a mensagem de erro. Para isso precisamos alocar alguma memória para escrever uma string UNICODE e alterar o registrador r8 para o endereço dessa memória. A alocação de memória pelo WinDbg pode ser feita usando o comando .dvalloc e a edição de uma string UNICODE terminada em zero pelo comando ezu (edit zero terminated unicode string). Após isso alteramos o valor do registrador com o comando r.

    0:000> .dvalloc 10
    Allocated 1000 bytes starting at 00000211`43d60000
    0:000> ezu 00000211`43d60000 "Obrigado por utilizar o maravilhoso Bloco de Notas!"
    0:000> rr8 = 00000211`43d60000
    0:000> g
    
Note que se estivéssemos tentando exibir uma string Ansi iríamos usar o comando eza (edit zero terminated ansi string). O WinDbg possui inúmeros comandos parecidos que começam com e, cuja lista pode ser consultada pelo comando .hh e. O equivalente para leitura é o comando d (de dump).

![Notepad File Not Found Thanks](/img/notepad_wonderful_file.png)

Repare que colocamos esse breakpoint diretamente na função API, ou seja, qualquer outro ponto do notepad em que ele tiver vontade de chamar a mesma API irá ativar o mesmo breakpoint e exibir a mesma mensagem, o que pode ser um pouco importuno da parte dele. Um bom exercício pós-leitura seria tratar as condições em que a mensagem será trocada, talvez se baseando na mensagem recebida. Mas isso já é lição de casa, e paramos por aqui.

[primeiro artigo sobre o WinDbg]: /introducao-ao-debugging-tools-for-windows
[orografia]: /img/orografia.jpg
