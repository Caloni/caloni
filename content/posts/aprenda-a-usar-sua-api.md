---
date: "2008-07-22"
title: Aprenda a usar sua API
tags: [ "draft", "blog" ]
---
É conhecido que uma das desvantagens de se programar diretamente em Win32 API é a dificuldade de se entender os parâmetros e o retorno das funções. Concordo em parte. Constituída de [boa documentação](http://msdn.microsoft.com), parte da culpa dos programas mal-feitos reside na preguiça do programador em olhar a documentação por completo.

A Win32 API está longe de ser perfeita, mas pelo menos está razoavelmente documentada, e é na leitura atenta da documentação que iremos encontrar as respostas que precisamos para que o programa funcione.

Vejamos alguns exemplos.

#### 1. CreateFile

O código abaixo parece bem razoável:

```c
#include <windows.h>

int main()
{
	HANDLE hFile = CreateFile("c:\\tests\\myfile.txt", GENERIC_READ, 
		FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if( hFile )
	{
		DWORD read = 0;
		CHAR buffer[100];

		if( ReadFile(hFile, buffer, sizeof(buffer), &read, NULL) )
		{
			WriteBuffer(buffer);
		}

		CloseHandle(hFile);
	}
}

 

```

No entanto, está errado.

É fato que a maioria das funções que retornam _handles_ retornam NULL para indicar o erro na tentativa de obter o recurso. Ao comparar o retorno com NULL, o programador geralmente faz uma chamada a [GetLastError](http://msdn.microsoft.com/en-us/library/ms679360(VS.85).aspx) para saber o que aconteceu. No entanto, uma das funções mais usadas, a CreateFile, não retorna NULL, mas INVALID_HANDLE_VALUE.

Sendo assim, o código acima deveria ser:

    
    if( hFile != INVALID_HANDLE_VALUE )

#### 2. GetVersion

Taí uma função que muitos erraram. Erraram tanto que eles fizeram uma nova versão menos complicada. Como está escrito no [MSDN](http://msdn.microsoft.com/en-us/library/ms724439(VS.85).aspx):

<blockquote>"_The GetVersionEx function was developed because many existing applications err when examining the packed DWORD value returned by GetVersion, transposing the major and minor version numbers._"</blockquote>

O motivo de tantos erro pode ter sido o fato que o valor retornado é uma estrutura de bits dentro de um DWORD, coisa que nem todos programadores C sabem lidar muito bem, e o fato de ser uma função muito utilizada por todos (pegar a versão do sistema operacional).

Eis a tabela de campos do retorno de GetVersion:

    
    Platform                                High-order bit   Next 7 bits     Low-order byte
    -------------------------------------   --------------   ------------    --------------
    Windows NT 3.51                         0                Build number    3
    Windows NT 4.0                          0                Build number    4
    Windows 2000 or Windows XP              0                Build number    5
    Windows 95, Windows 98, or Windows Me   1                Reserved        4
    Win32s with Windows 3.1                 1                Build number    3

Mesmo que não seja tão difícil, pode ser ambíguo. Por exemplo, como saber se o Windows é 95, 98 ou ME?

O código abaixo, muito usado por todos que suportam ainda o Windows mais velhinhos, verifica se estamos rodando em plataforma NT ou 9x.

```c
#include <windows.h>
#include <stdio.h>

int main()
{
	DWORD winVer = GetVersion();
	BOOL isPlatformNT = winVer >= 0x80000000 ? FALSE : TRUE;

	if( isPlatformNT )
		printf("Plataforma NT\n");
	else
		printf("Bem-vindo ao parque dos dinossauros!\n");

	return isPlatformNT ? 1 : 0;
}

 

```

![jurassicpark.PNG](/images/jurassicpark.PNG)

#### 3. CloseHandle. Mesmo??

Nem sempre o handle que obtemos é fechado com CloseHandle. As funções abaixo retornam handles que devem ser desalocados com as funções à direita:

    
    Função que obtém recurso         Função que libera recurso
    ------------------------         -------------------------
    LoadLibrary                      FreeLibrary
    RegOpenKey                       RegCloseKey
    GetDC                            ReleaseDC
    BeginPaint                       EndPaint

#### 4. Tem mais?

Sempre tem. Algumas dicas úteis para o dia-a-dia de um programador Win32 API são:

    
  * Leia a documentação

    
  * Se atente aos valores de retorno em caso de sucesso e erro

    
  * Leia sempre a seção remarks pelo menos uma vez; ela explica como desalocar recursos

    
  * Releia a documentação

Às vezes uma singela chamada de uma função de autenticação pode nos fazer preencher uma estrutura de 20 membros, sendo que seis deles são obtidos com mais sete chamadas de funções, todas com direito a desalocar recursos no final. O importante é sempre manter a calma, o espírito de aprendizado e aventura. Afinal, quem mandou não fazer software de telinha?
