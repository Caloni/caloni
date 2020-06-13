---
categories: [ "code" ]
date: "2007-11-07"
tags: [ "draft",  ]
title: "Ponteiro de método: qual this é usado?"
---
Depois de publicado o artigo anterior sobre ponteiros de métodos surgiu uma dúvida muito pertinente do autor do blogue CodeBehind, um escovador de bits disfarçado de programador .NET: qual objeto que vale na hora de chamar um método pelo ponteiro?

Isso me estimulou a desdobrar um pouco mais os mistérios por trás dos ponteiro de métodos e de membros, e descobrir os detalhes mais ocultos desse lado esotérico da linguagem.

Para entender por inteiro o que acontece quando uma chamada ou acesso utilizando ponteiros dependentes de escopo, algumas pequenas mudanças foram feitas no nosso pequeno FuzzyCall.

    #include <windows.h>
    #include <iostream>
    #include <time.h>
    
    using namespace std;
    
    // declaramos que existe uma classe com esse nome
    class FuzzyCall;
    
    // ponteiro para métodos da classe acima
    typedef void (FuzzyCall::*FP_Fuzzy)();
    
    // ponteiro para inteiros da classe acima
    typedef int FuzzyCall::*PI_Fuzzy;
    
    /** Classe que faz chamada de um método aleatório. */
    class FuzzyCall
    {
    public:
    	FuzzyCall()
    	{
    		int bingoStone = rand() % 100; // tira uma pedra do saco
    		m_bingoStone = bingoStone; // guarda a pedra que tiramos do saco
    	}
    
    	int m_bingoStone; // pedra que tiramos do saco de bingo
    
    	// retorna a pedra que tiramos do saco de bingo
    	void PrintStone()
    	{
    		cout << "this: " << hex << this << ", member: " << dec << m_bingoStone << endl;
    	}
    };
    
    /** No princípio Deus disse: 'int main!'
    */
    int main()
    {
    	srand(GetTickCount()); // chacoalha o saco de bingo
    
    	FuzzyCall fuzzyObject1;
    	FuzzyCall fuzzyObject2;
    	FuzzyCall fuzzyObject3;
    	FP_Fuzzy pMethod = &FuzzyCall::PrintStone;
    	PI_Fuzzy pMember = &FuzzyCall::m_bingoStone;
    
    	// podemos chamar o mesmo método para diversos objetos
    	(fuzzyObject1.*pMethod)();
    	(fuzzyObject2.*pMethod)();
    	(fuzzyObject3.*pMethod)();
    
    	// separador
    	cout << endl;
    	
    	// podemos chamar o mesmo método para diversos objetos
    	cout << "this: " << hex << &fuzzyObject1 << ", member: " << dec << fuzzyObject1.*pMember << endl;
    	cout << "this: " << hex << &fuzzyObject2 << ", member: " << dec << fuzzyObject2.*pMember << endl;
    	cout << "this: " << hex << &fuzzyObject3 << ", member: " << dec << fuzzyObject3.*pMember << endl;
    } 
    

O novo código chama através do mesmo ponteiro o mesmo método (duh), mas através de três objetos diferentes. Se observarmos a saída veremos que cada instância da classe guardou uma pedra diferente do saco de bingo para si (até porque, no jogo do bingo, não é possível existir mais de uma pedra com o mesmo número):

    
    this: 0012FF6C, member: 97
    this: 0012FF5C, member: 5
    this: 0012FF60, member: 44
    
    this: 0012FF6C, member: 97
    this: 0012FF5C, member: 5
    this: 0012FF60, member: 44

Cada compilador e plataforma tem a liberdade de implementar o padrão C++ da maneira que quiser, mas o conceito no final acaba ficando quase a mesma coisa. No caso de ponteiros de métodos, o ponteiro guarda realmente o endereço da função que pertence à classe. Porém, como todo método não-estático em C++, para chamá-lo é necessário possuir um this, ou seja, o ponteiro para a instância:

Em assembly (comando "cl /Fafuzzycall3.asm fuzzycall3.cpp" para gerar a listagem), teremos algo assim:

    ; Line 48
    lea    ecx, DWORD PTR
    _fuzzyObject1$
    [ebp]
    call    DWORD PTR
    _pMethod$
    [ebp]
    ; Line 49
    lea    ecx, DWORD PTR
    _fuzzyObject2$
    [ebp]
    call    DWORD PTR
    _pMethod$
    [ebp]
    ; Line 50
    lea    ecx, DWORD PTR
    _fuzzyObject3$
    [ebp]
    call    DWORD PTR
    _pMethod$
    [ebp]

Além do ponteiro de métodos, também é possível no C++ apontar para membros de um dado objeto. Para tanto, como vimos no código, basta declarar um tipo de ponteiro de membro de acordo com o tipo desejado:

    
    // ponteiro para inteiros da classe acima
    typedef int FuzzyCall::*PI_Fuzzy;

Nesse caso, a técnica de usar o próprio enderenço não funciona, já que cada objeto possui um membro próprio em um lugar de memória próprio. Porém, assim como os ponteiros de métodos, os ponteiros de membros exigem um objeto para serem acessados, o que já nos dá a dica de onde o objeto começa. Sabendo onde ele começa, fica fácil saber onde fica o membro através do seu offset, ou seja, a distância dele a partir do início da memória do objeto. Só que para isso precisamos do offset armazenado em algum lugar. E adivinha onde que ele fica armazenado?

    
    mov    eax, DWORD PTR
    _pMember
    $[ebp]
    mov ecx, DWORD PTR
    _fuzzyObject1
    $[ebp+eax]
    ...
    mov eax, DWORD PTR
    _pMember
    $[ebp]
    mov ecx, DWORD PTR
    _fuzzyObject2
    $[ebp+eax]
    ...
    mov eax, DWORD PTR
    _pMember
    $[ebp]
    mov ecx, DWORD PTR
    _fuzzyObject3
    $[ebp+eax]

Podemos acompanhar este código no WinDbg (ou alguma outra IDE mais pomposa, se preferir) e veremos que o conteúdo do eax irá refletir o offset do membro dentro da classe FuzzyCall.

    
    bp fuzzycall3!main
    g
    fuzzycall3!main+0x61:
    00401731 8b45f8          mov     eax,dword ptr [ebp-8] ss:0023:0012ff68=00000000
    0:000> reax
    eax=00000000
    ; zero é o _offset_, já que a classe possui apenas um membro: o próprio!
    0:000> p
    ...
    fuzzycall3!main+0x64:
    00401734 8b4c05fc        mov     ecx,dword ptr [ebp+eax-4] ss:0023:0012ff6c=00000061
    0:000> recx
    ecx=00000061
    ; 61 (97 em decimal) é o valor do membro para esse this ...

Como podemos ver, não é nenhuma magia negra a responsável por fazer os ponteiros de métodos e de membros funcionarem em C++. Porém, eles não são ponteiros ordinário que costumamos misturar a torto e a direito. Essa distinção na linguagem é importante para manter o código "minimamente sadio".
