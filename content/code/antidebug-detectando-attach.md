---
date: "2007-09-10"
title: 'Antidebug: detectando attach'
categories: [ "code" ]
---
Hoje foi um belo dia para engenharia reversa e análise de proteções. Dois ótimos programas vieram ao meu conhecimento: um [monitor de chamadas de API](http://www.kakeeware.com/) e um [monitor de chamadas de COM](http://www.blunck.info/comtrace.html) (complementando o primeiro, que não monitora funções depois que [CoCreateInstance](http://msdn2.microsoft.com/en-us/library/ms686615.aspx) foi chamado). Além de que no sítio do primeiro programa - de algum entusiasta do bom e velho Assembly Win32, diga-se de passagem - encontrei o código-fonte para mais uma técnica _antidebugging_, o que nos leva de volta para a já consagrada série de [técnicas antidepuração](http://www.caloni.com.br/blog/?s=antidebug%3A).

#### Atachar que é bom, nada

O objetivo dessa proteção é detectar se, após o executável ter sido iniciado, algum depurador metido a besta tentou _atachar_-se no processo criado, ou seja, tentou iniciar o processo de depuração após o aplicativo já ter iniciada a execução. Isso é possível - de certa forma trivial - na maioria dos depuradores (se não todos), como o Visual Studio e o WinDbg. Diferente da [técnica de ocupar a DebugPort](http://www.caloni.com.br/antidebug-ocupando-a-debugport), que impede a ação de _attach_, a proteção nesse caso não protege diretamente; apenas permite que o processo saiba do suposto ataque antes de entregar o controle ao processo depurador.

O código que eu encontrei nada mais faz do que se aproveitar de uma peculiaridade do processo de _attach_: ao disparar o evento, a função **ntdll!DbgUiRemoteBreakin** é chamada. Ora, se é chamada, é lá que devemos estar, certo? E isso, como vemos abaixo, é relativamente fácil:

```cpp
#include <windows.h>
#include <iostream>
#include <assert.h>

using namespace std;

/** This function is triggered when a debugger try to attach into our process.
*/
void AntiAttachAbort()
{
	// this is a test application, remember?
	MessageBox(NULL, "Espertinho, hein?", "AntiAttachDetector", MB_OK | MB_ICONERROR);

	// this is the end
	TerminateProcess(GetCurrentProcess(), -1);
}

/** This function installs  a trigger that is activated when a debugger try to attach.
@see AntiAttachAbort.
*/
void InstallAntiAttach()
{
	PVOID attachBreak = GetProcAddress(
		GetModuleHandle("ntdll"), // this dll is ALWAYS loaded
		"DbgUiRemoteBreakin"); // this function is ALWAYS called on the attach event

	assert(attachBreak); // attachBreak NEVER can be null

	// opcodes to run a jump to the function AntiAttachAbort
	BYTE jmpToAntiAttachAbort[] =
	{ 0xB8, 0xCC, 0xCC, 0xCC, 0xCC,   // mov eax, 0xCCCCCCCC
	0xFF, 0xE0 };                     // jmp eax

	// we change 0xCCCCCCCC using a more useful address
	*reinterpret_cast<PVOID*>(&jmpToAntiAttachAbort[1]) = AntiAttachAbort;

	DWORD oldProtect = 0;

	if( VirtualProtect(attachBreak, sizeof(jmpToAntiAttachAbort), 
		PAGE_EXECUTE_READWRITE, &oldProtect) )
	{
		// if we can change the code page protection we put a jump to our code
		CopyMemory(attachBreak, 
			jmpToAntiAttachAbort, sizeof(jmpToAntiAttachAbort));

		// restore old protection
		VirtualProtect(attachBreak, sizeof(jmpToAntiAttachAbort), 
			oldProtect, &oldProtect);
	}
}

/** In the beginning, God said: 'int main!'
*/
int main()
{
	InstallAntiAttach();
	cout << "Try to attach, if you can...";
	cin.get();
} 

```

Para compilar o [código acima](/images/antiattach.cpp), basta chamar o compilador seguido do ligador. Obs.: precisamos da user32.lib para chamar a função API MessageBox:

    
    cl /c antiattach.cpp
    link antiattach.obj user32.lib

    
    antiattach.exe
    Try to attach, if you can...

Após o programa ter sido executado, qualquer tentativa de _attach_ irá exibir nossa mensagem de detecção, seguida pelo capotamento do programa.

    
    windbg -pn antiattach.exe

    
    <a href="http://i.imgur.com/mdRqvjp.png" title="Detecção de attach"><img src="http://www.caloni.com.br/blog/wp-content/uploads/antiattach.png" alt="Detecção de attach"></img></a>

#### Idiossincrasias do código

Sim, eu sei. Às vezes temos que apelar pra "ignorância" e fazer códigos obscuros como esse:

```cpp
// opcodes to run a jump to the function AntiAttachAbort
BYTE jmpToAntiAttachAbort[] =
{ 0xB8, 0xCC, 0xCC, 0xCC, 0xCC,   // mov eax, 0xCCCCCCCC
0xFF, 0xE0 };                     // jmp eax

// we change 0xCCCCCCCC using a more useful address
*reinterpret_cast<PVOID*>(&jmpToAntiAttachAbort[1]) = AntiAttachAbort; 

```

Existem inúmeras maneiras de fazer a mesma coisa. O exemplo acima é o que é chamado comumente nas rodinhas de _crackers_ de [_shellcode_](http://shellcode.org/Shellcode/), que é um nome bonitinho para "_array_ de bytes que na verdade é um _assembly_ de um código que faz coisas interessantes". _Shellcode for short_ =).

Maneiras alternativas de fazer isso são:

    
  1. Declarar uma função _naked_ no Visual Studio, criar uma função vazia logo após e fazer continha de mais e menos para chegar ao tamanho que deve ser copiado.

    
  2. Criar uma estrutura cujos membros são _opcodes_ disfarçados. Dessa forma é possível no construtor dessa estrutura preencher os valores corretamente e usá-la como uma "função móvel".

Ambas possuem prós e contras. Os contras estão relacionados com a dependência do ambiente. Na primeira alternativa é necessário configurar o projeto para desabilitar o "Edit and Continue", enquanto no segundo é necessário alinhar a estrutura em 1 byte.

Seja qual for a solução escolhida, ao menos temos a vantagem do impacto no sistema de nosso aplicativo ser praticamente nulo, pois isolamos em duas funções - AntiAttachAbort e InstallAntiAttach - um _hook_ de uma API local (do próprio processo) que supostamente nunca deveria ser chamada em um binário de produção. Além do mais, existem maneiras mais a la C++ de fazer coisas como "_live assembly_". Mas isso já é matéria para futuros e excitantes artigos =D.
