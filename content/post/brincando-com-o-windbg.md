---
categories: [ "code" ]
date: "2007-10-30"
tags: [ "draft",  ]
title: "Brincando com o WinDbg"
---
No primeiro artigo sobre o WinDbg usamos o aplicativo Logger para verificar as funções APIs que são chamadas por um determinado programa. Agora iremos dar um passo adiante e depurar de fato um aplicativo qualquer, com o detalhe que não teremos o código-fonte.

Existem duas maneiras de depurar um programa localmente usando o WinDbg: iniciá-lo pelo próprio WinDbg ou conectar o depurador (attach) em um programa já em execução. Podemos especificar o que faremos direto na linha de comando ou pela sua interface.

Pela linha de comando:

    
    windbg notepad.exe
    windbg -pn notepad.exe (ou -p pid)

Pela interface:

Para variar, iremos depurar o Bloco de Notas, o maravilhoso editor de textos da Microsoft e plataforma de testes para serviços, GINAs e drivers. Para começar, poderemos usar quaisquer das opções anteriores, o que nos levará para uma saída parecida com a seguinte:

    
    Microsoft (R) Windows Debugger  Version 6.7.0005.1
    Copyright (c) Microsoft Corporation. All rights reserved.
    
    CommandLine: notepad.exe
    Symbol search path is: SRV*C:Symbols*http://msdl.microsoft.com/downloads/symbols
    Executable search path is:
    ModLoad: 01000000 01014000   notepad.exe
    ModLoad: 7c900000 7c9b0000   ntdll.dll
    ModLoad: 7c800000 7c8f5000   C:WINDOWSsystem32kernel32.dll
    ModLoad: 763b0000 763f9000   C:WINDOWSsystem32comdlg32.dll
    ModLoad: 77f60000 77fd6000   C:WINDOWSsystem32SHLWAPI.dll
    ModLoad: 77dd0000 77e6b000   C:WINDOWSsystem32ADVAPI32.dll
    ModLoad: 77e70000 77f01000   C:WINDOWSsystem32RPCRT4.dll
    ModLoad: 77f10000 77f57000   C:WINDOWSsystem32GDI32.dll
    ModLoad: 7e410000 7e4a0000   C:WINDOWSsystem32USER32.dll
    ModLoad: 77c10000 77c68000   C:WINDOWSsystem32msvcrt.dll
    ModLoad: 773d0000 774d3000   C:WINDOWSWinSxSx86_Microsoft.Windows.Common-Controls_Sbrubles
    ModLoad: 7c9c0000 7d1d5000   C:WINDOWSsystem32SHELL32.dll
    ModLoad: 73000000 73026000   C:WINDOWSsystem32WINSPOOL.DRV
    (df8.e28): Break instruction exception - code 80000003 (first chance)
    eax=001a1eb4 ebx=7ffd5000 ecx=00000000 edx=00000001 esi=001a1f48 edi=001a1eb4
    eip=7c901230 esp=0007fb20 ebp=0007fc94 iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    ntdll!DbgBreakPoint:
    7c901230 cc              int     3

Não se preocupe, nada aconteceu de errado. Essa é apenas a maneira do WinDbg de dizer "oi, estou aqui, positivo e operando".

Vamos destrinchar as informações iniciais para evitar confusão:

    
    Microsoft (R) Windows Debugger  Version 6.7.0005.1 <- versão do WinDbg
    Copyright (c) Microsoft Corporation. All rights reserved.
    
    CommandLine: notepad.exe <-- linha de comando usada
    Symbol search path is: SRV*C:Symbols*http://msdl.microsoft.com/downloads/symbols <-- onde estão os símbolos?
    Executable search path is:
    ModLoad: 01000000 01014000   notepad.exe <-- informações sobre cada módulo carregado (ModLoad)
    ModLoad: 7c900000 7c9b0000   ntdll.dll
    ModLoad: 7c800000 7c8f5000   C:WINDOWSsystem32kernel32.dll
    ...
    (df8.e28): Break instruction exception - code 80000003 (first chance) <-- exceção de breakpoint (início da depuração)
    
    eax=001a1eb4 ebx=7ffd5000 ecx=00000000 edx=00000001 esi=001a1f48 edi=001a1eb4 <-- estado dos registradores
    eip=7c901230 esp=0007fb20 ebp=0007fc94 iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    
    ntdll!DbgBreakPoint: <-- paramos aqui
    7c901230 cc              int     3

Muito bem. Agora vamos explicar resumidamente o que cada parte significa:

	
  * Version: versão que está sendo executada do WinDbg (duh).

	
  * CommandLine: linha de comando que foi usada ao executar o depurador.

	
  * ModLoad: sempre que um módulo é carregado no processo (DLLs ou o próprio executável) o WinDbg informa os endereços inicial e final de carregamente e o nome do módulo. Para rever a lista de módulos carregados usa-se o comando lm.

	
  * pid.tid: Break instruction exception - code 8000003 (first chance)_. Qualquer informação específica de uma _thread_ é informada dessa maneira no WinDbg. No caso, foi a exceção de _breakpoint_ (parada na execução) acionada no começo da depuração (e é por isso que o notepad ainda não está aparecendo).

Explicado o começo, o resto é fácil. Para continuar a execução do bloco de notas basta usarmos o comando g (Go), ou pressionar F5, ou ir no menu "Debug, Go", ou ainda apertar este botão:

Na maioria dos comandos mais comums você terá todas essas opções ao seu dispor. Na maioria dos comandos mais incomuns tudo o que você terá será o prompt de comando do WinDbg e a ajuda, acionada por F1 ou pelo comando .hh tópico. Geralmente os comandos do WinDbg possuem milhares de parâmetros, e é considerada atitude sábia olhar de vez em quando o que alguns desses parâmetros significam para que, aos poucos, aprenda-se alguns truques até a chegada da iluminação completa, onde seu espírito irá fluir livremente pela memória de todos os processos do sistema.

Por enquanto, basta apertar g e .

> A tempo: após executar g e mais um monte daquelas mensagens cheias de caracteres irão aparecer. Não se preocupe. Elas realmente não são importantes no momento, mas é importante saber o básico, que é "o WinDbg está avisando você de tudo o que ocorre". No momento certo, saberemos usar as informações na tela quando houver necessidade.

Vamos fazer algo não tão esperto para ver como o bloco de notas reage. Tente abrir um arquivo com um nome inexistente:

Como podemos ver, o Bloco de Notas exibe uma mensagem de erro indicando que o arquivo cujo nome você digitou não existe, pede para você verificar a "orografia" e tudo o mais. O importante aqui não é que você não sabe digitar nomes de arquivos, mas sim que a função que o notepad usa para exibir sua mensagem de erro é a conhecida API MessageBox, cujo protótipo é o seguinte:

    
    int WINAPI MessageBox(
    	HWND hWnd,            // handle para o propretário da janela
    	LPCTSTR lpText,       // ponteiro para string que contém o texto a ser exibido
    	LPCTSTR lpCaption,    // ponteiro para string que contém o título a ser exibido
    	UINT uType            // personaliza a janela com ícones, comportamento, etc
    	);

Algumas coisas a serem notadas nessa API:

	
  * Como (quase) toda API no Windows, a convenção de chamada é WINAPI, o que significa que quem chama empilha todos os parâmetros na pilha. Eu estou falando apenas de Windows 32 bits.
  * A função recebe 4 parâmetros e, de acordo com a convenção de chamada, podemos supor que esses parâmetros são empilhados na seguinte ordem (invertida): uType, lpCaption, lpText, hWnd, endereço-de-retorno.
  * As _strings_ para as quais os dois parâmetros do meio apontam são do tipo LPCTSTR, o que significa que, além de constantes, podem ser ANSI ou UNICODE, dependendo da versão que estamos utilizando.

> 
> #### ANSI x UNICODE
> 
O sistema operacional utiliza internamente a codificação UNICODE. Contudo, para manter compatibilidade com versões anteriores de outros SOs, como Windows 95, 98 e ME, as APIs são desenvolvidas em duplas, com versões UNICODE (final W), que repassam a chamada diretamente para o sistema operacional, e ANSI (final A), que fazem a conversão de strings para daí (normalmente) chamar sua irmã em UNICODE. 

Sabendo que tudo converge para UNICODE, vamos colocar um singelo breakpoint nessa função API. Para parar a execução do notepad, podemos digitar "Ctrl + Break" ou ir no menu "Debug, break" ou ainda... bem, você pegou o espírito da coisa.

    
    bp user32!MessageBoxW
    g

> 
> #### Faça do modo inteligente
> 
Note que utilizei o prefixo user32! para especificar que a função está no módulo user32.dll, mas não seria necessário já que o WinDbg procura por qualquer função digitada na sua lista de funções exportadas e símbolos atuais. Contudo, fazer isso torna as coisas mais rápidas e evita perder tempo à toa.

Agora podemos efetuar a mesma operação de abrir um arquivo inexistente no bloco de notas que a execução irá parar no início da função MessageBoxW da API:

    
    Breakpoint 0 hit
    eax=0007cfb8 ebx=80004005 ecx=7e41ce0b edx=00000008 esi=00000208 edi=001b0296
    eip=7e46630a esp=0007cfa0 ebp=0007d9e4 iopl=0         nv up ei ng nz na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000286
    USER32!MessageBoxW:
    7e46630a 8bff            mov     edi,edi

Vamos exibir o estado da pilha atual (no registrador esp) no formato de double words, a palavra padrão em sistemas 32 bits:

    
    0:000> dd esp ; Dump de Double words
    0007cfa0  763db810 001b0296 0007cfb8 0007d5d0 <-- parâmetros do MessageBox (em vermelho)
    0007cfb0  00000030 00000187 00720041 00750071 <-- parâmetros do MessageBox (em vermelho)
    0007cfc0  00760069 0020006f 006e0069 00780065
    0007cfd0  00730069 00650074 0074006e 002e0065

A primeira coluna (cujo primeiro valor é 0007cfa0) exibe o endereço da pilha, sendo que o resto das colunas são os valores encontrados a partir do topo da pilha. Sabendo que a pilha cresce "ao contrário", de valores maiores de endereço para menores, os parâmetros empilhados invertidos aparecem agora na ordem do protótipo da função. Complicado? Nem tanto. Os parâmetros são empilhados na ordem inversa do protótipo em C, como tínhamos observado: uType, lpCaption, lpText, hWnd e por fim endereço-de-retorno, que é empilhado ao ser executada a instrução call.

    
    push uType               ; topo da pilha (esp) = 007cfb0, decrementado em 4 bytes (= double word)
    push lpCaption           ; esp = 007cfac (007cfb0 - 4), decrementado novamente...
    push lpText              ; esp = 007cfa8 (007cfac - 4)
    push hWnd                ; esp = 007cfa4 (007cfa8 - 4)
    call user32!MessageBoxW  ; push eip, esp = 007cfa4 - 4 = 007cfa0

Ao chegar em user32!MessageBoxW o estado da pilha reflete o protótipo, pois é o inverso do inverso (a pilha cresce "para baixo", porém os parâmetros são empilhados do último para o primeiro).

    
    0007cfa0  763db810 001b0296 0007cfb8 0007d5d0
    0007cfb0  00000030 
    
    0007cfa0   ret    hWnd  lpText lpCaption
    0007cfb0  uType

Para referenciarmos os parâmetros através do WinDbg, de forma genérica, tudo que precisamos é adicionar 4 bytes para pularmos de parâmetro em parâmetro:

    
    esp = ret
    esp + 4 = hWnd
    esp + 8 = lpText
    esp + c = lpCaption
    esp + 10 =  uType

Baseado nesse princípio básico, podemos agora exibir o conteúdo de cada parâmetro passado usando o comando d (Dump) do WinDbg, aliado ao comando poi (pointer), que deferencia um determinado endereço ("o apontado de").

    
    0:000> du poi(esp+8) <-- Dump de string Unicode do apontado (poi) do valor em esp+8 (lpText)
    0007cfb8  "Arquivo inexistente.txt.File not"
    0007cff8  " found..Please verify the correc"
    0007d038  "t file name was given."
    0:000> du poi(esp+c) <-- Dump de string Unicode do apontado (poi) do valor em esp+c (lpCaption)
    0007d5d0  "Open"

Note que se estivéssemos tentando exibir uma string Ansi iríamos usar o comando da. O WinDbg possui inúmeros comandos parecidos que começam com d, cuja lista pode ser consultada pelo comando .hh d.

Como último passo em nosso passeio, vamos especificar alguns comandos para serem executados quando o breakpoint do MessageBox for acionado. O que iremos fazer aqui é trocar a mensagem de erro e seguir em frente (um breakpoint que não pára).

Para trocar a mensagem de erro usamos o comando e (Edit), semelhante ao d.

Para continuar a execução, como já vimos, usamos o comando g (Go), e é nessas horas que apenas o comando do prompt pode nos salvar:

    
    0:004> bp user32!MessageBoxW "ezu poi(esp+8) \"Obrigado por utilizar o maravilhoso Bloco de Notas!\"; g"
    breakpoint 0 redefined

O comando bp (BreakPoint) permite que sejam especificados comandos para serem executados automaticamente sempre que o breakpoint for ativado. Por isso, ao passar em user32!MessageBoxW colocamos dois comandos (separados por ponto-e-vírgula): ezu, que Edita uma string Unicode com outra string terminada em Zero, e o comando g, que já estamos carecas de saber. O resultado é óbvio, mas divertido de ver:

Repare que colocamos esse breakpoint diretamente na função API, ou seja, qualquer outro ponto do notepad em que ele tiver vontade de chamar a mesma API irá ativar o mesmo breakpoint e exibir a mesma mensagem, o que pode ser um pouco importuno da parte dele. Um bom exercício pós-leitura seria tratar as condições em que a mensagem será trocada, talvez se baseando na mensagem recebida. Mas isso já é lição de casa, e paramos por aqui.
