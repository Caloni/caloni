---
categories:
- code
date: '2008-01-30'
title: Compartilhando variáveis com o mundo
---

Desde que comecei a programar, para compartilhar variáveis entre processo é meio que consenso usar-se a milenar técnica do crie uma seção compartilhada no seu executável/DLL. Isso funciona desde a época em que [o Windows era em preto e branco]. Mas, como tudo em programação, existem mil maneiras de assar o pato. Esse artigo explica uma delas, a não-tão-milenar técnica do use memória mapeada nomeada misturada com templates.

Era comum (talvez ainda seja) fazer um código assim:

    // aqui definimos uma nova seção (note o 'shared' usado como atributo)
    #pragma section("shared", read, write, shared)
    
    // um conjunto de variáveis agrupadas para facilitar o compartilhamento
    struct EstruturaDoCoracao
    {
      int meuIntPreferido;
      char meuCharAmigo;
      double meuNumeroDePontoFlutuanteCamarada;
    };
    
    // uma instância da struct acima para podermos usar nos processo amigos
    __declspec(allocate("shared")) EstruturaDoCoracao g_coracao;
    
    int main()
    {
      g_coracao.meuCharAmigo = 'C';
      g_coracao.meuIntPreferido = 42;
      g_coracao.meuNumeroDePontoFlutuanteCamarada = 3.14159265358979323846264338;
    } 

Aquele pragma do começo garante que qualquer instância do mesmo executável, mas processos distintos, irão compartilhar qualquer variável definida dentro da seção "shared". O nome na verdade não importa muito - é apenas usado para clareza - , mas o atributo do final, sim.

Algumas desvantagens dessa técnica são:

 - Não permite compartilhamento entre executáveis diferentes, salvo se tratar-se de uma DLL carregada por ambos.
 - É um compartilhamento estático, que permanece do início do primeiro processo ao fim do último.
 - Não possui proteção, ou seja, se for uma DLL, qualquer executável que a carregar tem acesso à área de memória.

Muitas vezes essa abordagem é suficiente, como em hooks globais, que precisam apenas de uma ou duas variáveis compartilhadas. Também pode ser útil como contador de instâncias, do mesmo jeito que usamos as variáveis estáticas de uma classe em C++ (vide shared_ptr do boost, ou a CString do ATL, que usa o mesmo princípio).

Houve uma vez em que tive que fazer hooks direcionados a threads específicas no sistema, onde eu não sabia nem qual o processo host nem quantos hooks seriam feitos. Essa é uma situação onde fica muito difícil usar a técnica milenar.

Foi daí que eu fiz um conjunto de funções alfa-beta de compartilhamento de variáveis baseado em template e memória mapeada:

    #pragma once
    #include <windows.h>
    #include <tchar.h>
    
    /** Aloca uma variável em memória mapeada, permitindo a qualquer processo
    com direitos enxergá-la e alterá-la.
    */
    
    template<typename T>
    HANDLE AllocSharedVariable(T** pVar, PCTSTR varName)
    {
      DWORD varSize = sizeof(T);
      HANDLE ret = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE,
        0, varSize, varName);
    
      if( ret )
      {
        *pVar = (T*) MapViewOfFile(ret, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    
        if( ! *pVar )
        {
          DWORD err = GetLastError();
          CloseHandle(ret);
          SetLastError(err);
        }
      }
      else
        *pVar = NULL;
    
      return ret;
    }
    
    /** Abre uma variável que foi criada em memória mapeada, permitindo ao
    processo atual enxergar e alterar uma variável criada por outro processo.
    */
    template<typename T>
    HANDLE OpenSharedVariable(T** pVar, PCTSTR varName)
    {
      DWORD varSize = sizeof(T);
      HANDLE ret = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, varName);
    
      if( ret )
      {
        *pVar = (T*) MapViewOfFile(ret, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, varSize);
    
        if( ! *pVar )
        {
        DWORD err = GetLastError();
        CloseHandle(ret);
        ret = NULL;
        SetLastError(err);
        }
      }
      else
        *pVar = NULL;
    
      return ret;
    }
    
    /** Libera visualização de uma variável em memória mapeada. Quando o último processo
    liberar a última visualização, a variável é eliminada da memória.
    */
    template<typename T>
    VOID FreeSharedVariable(HANDLE varH, T* pVar)
    {
      if( pVar )
        UnmapViewOfFile(pVar);
      if( varH )
        CloseHandle(varH);
    } 

Como pode-se ver, o seu funcionamento é muito simples: uma função-template que recebe uma referência para um ponteiro de ponteiro do tipo da variável desejada, o seu nome global e retorna uma variável alocada na memória de cachê do sistema. Como contraparte existe uma função que abre essa memória baseada em seu nome e faz o cast (coversão de tipo) necessário. Ambas as chamadas devem chamar uma terceira função para liberar o recurso.

O segredo para entender mais detalhes dessa técnica é pesquisar as funções envolvidas: CreateFileMapping, OpenFileMapping, MapViewOfFile e UnmapViewOfFile. Bem, o CloseHandle também ;)

Ah, é mesmo! Fiz especialmente para o artigo:

    #define _CRT_SECURE_NO_DEPRECATE
    #include "ShareVar.h"
    #include <windows.h>
    #include <tchar.h>
    
    #include <stdio.h>
    
    #define SHARED_VAR "FraseSecreta"
    
    /** Exemplo de como usar as funções de alocação de memória compartilhada
    AllocSharedVariable, OpenSharedVariable e FreeSharedVariable.
    */
    int _tmain(int argc, PTSTR argv[])
    {
      // passou algum parâmetro: lê a variável compartilhada e exibe
    
      if( argc > 1 )
      {
        system("pause");
    
        TCHAR (*sharedVar)[100] = 0; // ponteiro para array de 100 TCHARs
        HANDLE varH = AllocSharedVariable(&sharedVar, _T(SHARED_VAR));
    
        if( varH && sharedVar )
        {
          _tprintf(_T("Frase secreta: '%s'n"), *sharedVar);
          _tprintf(_T("Pressione <enter> para retornar..."));
          getchar();
        }
      }
      else // não passou parâmetro: escreve na variável 
      // compartilhada e chama nova instância
      {
        TCHAR (*sharedVar)[100] = 0; // ponteiro para array de 100 TCHARs
        HANDLE varH = AllocSharedVariable(&sharedVar, _T(SHARED_VAR));
    
        if( varH && sharedVar )
        {
          PTSTR cmd = new TCHAR[ _tcslen(argv[0]) + 10 ];
          _tcscpy(cmd, _T("\""));
          _tcscat(cmd, argv[0]);
          _tcscat(cmd, _T("\" 2"));
    
          _tcscpy(*sharedVar, _T("Tuintuintuclaim"));
          _tsystem(cmd);
    
          delete [] cmd;
        }
      }
    
      return 0;
    } 

Preciso lembrar que essa é uma versão inicial ainda, mas que pode muito bem ser melhorada. Duas idéias interessantes são: parametrizar a proteção da variável (através do SECURITY_ATTRIBUTES) e transformá-la em classe. Uma classe parece ser uma idéia bem popular. Afinal, tem tanta gente que só se consegue programar se o código estiver dentro de uma.

[o Windows era em preto e branco]: http://dqsoft.blogspot.com/2006/10/gerenciamento-de-memria-windows-16-bits.html