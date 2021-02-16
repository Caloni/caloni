---
date: "2007-11-09"
title: Detectando hooks globais no WinDbg
tags: [ "draft", "code" ]
---
Nada como um comando prático para aprender rapidamente uma técnica. Nesse caso, tive que usar o comando abaixo para localizar o momento em que um executável instala um _hook_ global:

    
    bp user32!SetWindowsHookExA "j poi(esp+4*4) 'g' ; '.echo *** GLOBAL HOOK ***; g'"

Vamos analisar cada um dos subcomandos novos um a um.

#### Comandos acionados por _breakpoints_

No WinDbg é possível definir um ou mais comandos que são executados quando um _breakpoint_ é acionado. Esses comandos ficam entre aspas duplas e podem conter as mesmas coisas que digitamos na linha de comando. Alguns comandos, porém, são mais úteis que outros nesse contexto. Por exemplo, o comando ".echo". Podemos digitar .echo na linha de comando do WinDbg. O que acontece?

    
    7c901230 cc              int     3
    0:000> .echo O que acontece?
    O que acontece?

Exatamente o que o comando se dispõe a fazer: **imprimir seus argumentos na tela**. E qual a vantagem nisso? Nenhuma, se estamos na linha de comando. Mas muita se estivermos colocando um _breakpoint_ onde queremos contar o número de vezes que passamos por lá, o comando tem serventia:

    
    0:000> bp $exentry ".echo Passou pelo entry point; g"
    0:000> g
    ModLoad: 5cb70000 5cb96000   C:WINDOWSsystem32ShimEng.dll
    ModLoad: 6f880000 6fa4a000   C:WINDOWSAppPatchAcGenral.DLL
    ModLoad: 76b40000 76b6d000   C:WINDOWSsystem32WINMM.dll
    ModLoad: 774e0000 7761d000   C:WINDOWSsystem32ole32.dll
    ...
    ModLoad: 5ad70000 5ada8000   C:WINDOWSsystem32UxTheme.dll
    ModLoad: 76390000 763ad000   C:WINDOWSsystem32IMM32.DLL
    <font color="#ff0000">Passou pelo entry point</font>
    ModLoad: 74720000 7476b000   C:WINDOWSsystem32MSCTF.dll
    ModLoad: 755c0000 755ee000   C:WINDOWSsystem32msctfime.ime
    ModLoad: 10000000 10006000   C:Program FilesMouseToolMT.dll

Se essa mensagem fosse exibida mais de uma vez, poderíamos supor que é possível existir algum tipo de infecção na execução do aplicativo, como quando o código inicial carrega o original e volta a executar o mesmo ponto.

[![Código Malicioso](http://i.imgur.com/f90hl3p.gif)](/images/codigo-malicioso.gif)

O objetivo aqui é "preparar o terreno" (ficar residente) antes que o código original seja executado. Com um simples _breakpoint_ e um simples .echo conseguimos visualizar esse tipo de ataque. Outra possibilidade é que se trata daqueles executáveis "empacotados" por meio de algum encriptador de códigos como [UPX](http://www.google.com.br/search?q=UPX), que desempacota o código e reexecuta o ponto de entrada do executável.

Claro, esse é apenas um uso que podemos fazer desses comandos.

#### O comando j ou if

Aprendi o comando **j** antes do **.if**, por isso acabo usando mais o primeiro, mas ambos possuem similaridades. O formato desse comando é exatamente como um "_if-else_":

    
    j Expression Command1 ; Command2
    j Expression 'Command1' ; 'Command2'

Se **Expression** for verdadeiro, **Command1** será executado; do contrário, **Command2** será. Se você não precisa do _else_ basta usar um comando vazio ' '. A escolha é sua em usar aspas simples ou nada. Se usar aspas simples, é possível colocar mais de um comando, que foi o que eu fiz no _else_:

    
    '.echo *** GLOBAL HOOK ***; g'"

Tudo depende do uso que você fizer desde comando. Algumas peculiaridades existem com relação ao uso de aspas duplas, simples, sem aspas, com ponto-e-vírgula, etc, mas são coisas que, como diz o [Thiago](http://www.codebehind.wordpress.com), "só se aprende na dor".

#### Brincando com a pilha (de novo)

Lembram-se de nossa peregrinação pela pilha de chamadas quando fizemos um [_hook_ na função MessageBox](http://www.caloni.com.br/brincando-com-o-windbg) pelo WinDbg? Aqui é a mesma coisa, pois estou analisando um parâmetro passado na pilha (esp): o ID da _thread_ para onde vai o _hook_:

    
    HHOOK <a href="http://msdn2.microsoft.com/en-us/library/ms644990.aspx" title="SetWindowsHookEx no MSDN">SetWindowsHookEx</a>(
    	int idHook,
    	HOOKPROC lpfn,
    	HINSTANCE hMod,
    	DWORD dwThreadId <font color="#339966">// Identifier of the thread (...) to be associated</font>
    	);

Relembrando nosso passeio pela pilha, ao entrar em uma função stdcall, os primeiros 4 bytes são o endereço de retorno, os próximos o primeiro parâmetro e assim por diante. O que quer dizer que:

    
    poi ( esp + (4 * 4) )

É o apontado do quarto parâmetro (4*4) que está sendo verificado. Concluindo, se o parâmetro **dwThreadId** for igual a zero, estamos diante de um _hook_ global, e é o momento em que meu .echo vai exibir na tela "*** GLOBAL HOOK ***". Do contrário, a execução vai continuar silenciosamente.
