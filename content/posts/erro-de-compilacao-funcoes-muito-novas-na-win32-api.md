---
date: "2007-08-21"
title: "Erro de compilação: funções muito novas na Win32 API"
categories: [ "code" ]
---
Quando fala-se em depuração geralmente o pensamento que vem é de um código que já foi compilado e está rodando em alguma outra máquina e gerando problemas não detectados nos testes de desenvolvedor. Mas nem sempre é assim. Depuração pode envolver problemas durante a própria compilação. Afinal de contas, se não está compilando, ou foi compilado errado, é porque já existem problemas antes mesmo da execução começar.

O fonte abaixo, por exemplo, envolve um detalhe que costuma atormentar alguns programadores, ou por falta de observação ou documentação (ou ambos).

    #include <stdio.h>
    #include <windows.h>
    
    void main(void)
    {
    	typedef enum _COMPUTER_NAME_FORMAT
    	{
    		ComputerNameNetBIOS,
    		ComputerNameDnsHostname,
    		ComputerNameDnsDomain,
    		ComputerNameDnsFullyQualified,
    		ComputerNamePhysicalNetBIOS,
    		ComputerNamePhysicalDnsHostname,
    		ComputerNamePhysicalDnsDomain,
    		ComputerNamePhysicalDnsFullyQualified,
    		ComputerNameMax
    	} COMPUTER_NAME_FORMAT;
    
    	COMPUTER_NAME_FORMAT CF = ComputerNameDnsDomain;
    
    	char szDomainName[MAX_COMPUTERNAME_LENGTH];
    
    	DWORD dwSize = sizeof(szDomainName);
    
    	//GetComputerName(szDomainName, &dwSize);
    	GetComputerNameEx(CF, szDomainName, &dwSize);
    } 

Tirando o fato que o retorno void não é mais um protótipo padrão da função main e que a definição da enumeração COMPUTER_NAME_FORMAT dentro da função main é no mínimo suspeita, podemos testar a compilação e verificar que existe exatamente um erro grave neste fonte:

    
    cl getcomputername.cpp
    getcomputername.cpp(26) : error C3861: 'GetComputerNameEx': identifier not found

A função GetComputerNameEx parece não ter sido definida, apesar de estarmos incluindo o header windows.h, que é o pedido pela documentação do MSDN.

Esse tipo de problema acontece na maioria das vezes por dois motivos:
    
  1. o header responsável não foi incluído (não é o caso, como vimos),
  2. é necessário especificar a versão mínima do sistema operacional.

De fato, se criarmos coragem e abrirmos o arquivo winbase.h, que é onde a função é definida de fato, e procurarmos pela função GetComputerNameEx encontramos a seguinte condição:

    #if (_WIN32_WINNT >= 0x0500)
    
    typedef enum _COMPUTER_NAME_FORMAT {
        ComputerNameNetBIOS,
        ComputerNameDnsHostname,
        ComputerNameDnsDomain,
        ComputerNameDnsFullyQualified,
        ComputerNamePhysicalNetBIOS,
        ComputerNamePhysicalDnsHostname,
        ComputerNamePhysicalDnsDomain,
        ComputerNamePhysicalDnsFullyQualified,
        ComputerNameMax
    } COMPUTER_NAME_FORMAT ;
    
    WINBASEAPI
    BOOL
    WINAPI
    GetComputerNameExA (
        __in    COMPUTER_NAME_FORMAT NameType,
        __out_ecount_part_opt(*nSize, *nSize + 1) LPSTR lpBuffer,
        __inout LPDWORD nSize
        );
    WINBASEAPI
    BOOL
    WINAPI
    GetComputerNameExW (
        __in    COMPUTER_NAME_FORMAT NameType,
        __out_ecount_part_opt(*nSize, *nSize + 1) LPWSTR lpBuffer,
        __inout LPDWORD nSize
        );
    #ifdef UNICODE
    #define GetComputerNameEx  GetComputerNameExW
    #else
    #define GetComputerNameEx  GetComputerNameExA
    #endif // !UNICODE
    
    //...
    
    #endif // _WIN32_WINNT

Ou seja, para que essa função seja visível a quem inclui o windows.h, é necessário antes definir que a versão mínima do Windows será a 0x0500, ou seja, Windows 2000 (vulgo Windows 5.0). Aliás, é como aparece na documentação. Um pouco de observação nesse caso seria o suficiente para resolver o caso, já que tanto abrindo o header quanto olhando no exemplo do MSDN nos levaria a crer que é necessário definir essa macro:

    #define _WIN32_WINNT 0x0500
    
    #include <windows.h>
    #include <stdio.h>
    #include <tchar.h>
    
    void _tmain(void)
    {
    	TCHAR buffer[256] = TEXT("");
    	TCHAR szDescription[8][32] = {TEXT("NetBIOS"), 
    	TEXT("DNS hostname"), 
    	TEXT("DNS domain"), 
    	TEXT("DNS fully-qualified"), 
    	TEXT("Physical NetBIOS"), 
    	TEXT("Physical DNS hostname"), 
    	TEXT("Physical DNS domain"), 
    	TEXT("Physical DNS fully-qualified")};
    	int cnf = 0;
    	DWORD dwSize = sizeof(buffer);
    
    	for( cnf = 0; cnf < ComputerNameMax; cnf++ )
    	{
    		if (!GetComputerNameEx( (COMPUTER_NAME_FORMAT)cnf, buffer, &dwSize) )
    		{
    			_tprintf(TEXT("GetComputerNameEx failed (%d)\n"),
    			GetLastError());
    			return;
    		}
    			else _tprintf(TEXT("%s: %s\n"), szDescription[cnf], buffer);
    
    		dwSize = sizeof(buffer);
    		ZeroMemory(buffer, dwSize);
    	}
    } 

Outra observação que poderia ter ajudado na hora de codificar seria dar uma olhada no que os caras escrevem na seção de advertências (remarks) da documentação:

> To compile an application that uses this function, define the _WIN32_WINNT macro as 0x0500 or later. For more information, see Using the Windows Headers.

Podemos também notar pela definição do COMPUTER_NAME_FORMAT dentro do main que o código estava no meio do caminho de cometer um sacrilégio: declarar funções e estruturas que já estão definidas nos headers da API. Portanto, se você já encontrou algum código parecido com esse, é hora de colocar em prática algumas teorias de refactoring.
