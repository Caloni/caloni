---
date: "2010-06-04"
title: Const e Volatile
categories: [ "draft", "code" ]
---
Padrão C (ISO/IEC 9899:1990)
    
    6.5.3 type-qualifier
     const
     volatile

    
    Padrão C++ (ISO/IEC 14882:1998)
    
    cv-qualifier
     const
     volatile

#### Qualificadores de tipo

Chamamos de qualificador de tipo as palavrinhas mágicas **const **e **volatile**. Na prática elas definem como uma determinada variável será usada e se comportará durante a vida do programa.

#### Const

Uma variável const não pode ser alterada pelo programa durante sua execução, apenas durante sua inicialização:

    
    const float pi = 3.14; // até onde sabemos, pi não irá mudar neste Universo

No exemplo acima, o valor de pi não pode mais ser alterado. Só que repare que ele foi, em determinado momento, alterado com um valor constante: na sua inicialização. Isso quer dizer que:

    
  * pi é uma variável no programa representada por um local na memória **endereçável **pelo programa

    
  * pi não é um define do pré-processador que irá virar uma constante literal (3.14, por exemplo)

    
    // eu posso endereçar uma constante,
    // desde que qualifique corretamente meu ponteiro
    const float* ppi = & pi;

![const-memory.png](http://i.imgur.com/V6eR9ln.png)

Teoricamente a região da memória que contiver uma variável const pode ser qualificada pelo sistema operacional como somente-leitura, mas isso não é uma obrigação. É obrigação do compilador avisar sobre tentativas de alteração da variável no meio do programa, mas nem sempre é possível enxergar que a memória não é alterável. Dessa forma, resultados imprevisíveis podem ocorrer.

![const-gpf.png](http://i.imgur.com/d51bAIH.png)

#### Uso prático

Eu costumo usar variáveis const no lugar de defines. Além de ganhar na tipagem as constantes não precisam ser necessariamente globais, nem acessíveis por outros módulos. Um outro uso muito comum é criar variáveis locais que você sabe que não devem ser alteráveis por ninguém, como o tamanho de matrizes primitivas.

```cpp
namespace Math
{
	const float Pi = 3.14;
}

//...

int func1(int x)
{
	float calc = x * Math::Pi;
	return calc;
}

//...

int func2(int y)
{
	const size_t PathSize = MAX_PATH * 2;
	//...
	char path[PathSize];
	//...
}
 

```

#### Volatile

O significado do volatile teoricamente muda de implementação para implementação, mas na prática é uma forma de definir uma variável que está sendo acessada por outros programas/threads/entidades espíritas que podem alterar o seu valor sem seu programa notar quando.

![Se concentre! Não é esse tipo de volatile!](http://i.imgur.com/carbzjo.jpg)

O exemplo clássico da API Win32 é o [InterlockedIncrement](http://msdn.microsoft.com/en-us/library/ms683614%28VS.85%29.aspx), que realiza operações atômicas em valores inteiros. Para fazer isso é necessário usar um recurso interno disponível pelo processador que irá modificar a memória sem intrusão de outras threads/processadores.

![interlocked-increment.png](http://i.imgur.com/3mqVrqA.png)

#### Uso prático

Variáveis volatile geralmente interagem de alguma forma com o sistema em que rodam, e são representadas por ponteiros para memória retornada por esse sistema ou documentada como sendo de uso específico.

#### Const e Volatile

É possível que exista uma variável que não pode ser modificada pelo seu programa, mas é modificada pelo sistema, de forma que ela é uma mutante!

    
    /// endereça o relógio do sistema, atualizado a cada 1/100 milissegundos
    const volatile int* g_systemClock = (const volatile int*) 0x7689B9D4;

[![mutante.jpg](http://i.imgur.com/4zUSxmJ.jpg) ](http://fotos-videos-incriveis.blogspot.com/2009/04/tubarao-mutante.html)

A definição de *g_systemClock é de uma memória que não pode ser alterada; só que ela é, pelo sistema. Então a variável também é volatile. No entanto, independente de ser const ou volatile, o tipo nunca será **alterado**, apenas **qualificado**. São duas coisas diferentes na linguagem.
