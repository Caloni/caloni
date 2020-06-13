---
categories: [ "code" ]
date: "2015-01-11"
tags: [ "draft",  ]
title: "Por que o Visual Studio gera executáveis mutantes"
---
> Esse é um post antigo que encontrei no meio dos meus emails de 2006, mas que contém uma boa dica para quem já entendeu o passo-a-passo da compilação, mas ainda tem sérios problemas quando os projetos ficam gigantes.

Essa é a segunda vez que encontro esse mesmo problema. Como acredito que outras almas podem estar sofrendo do mesmo mal, coloco aqui uma breve descrição de como o VC8 faz para gerar um executável que, mesmo não dependendo das DLLs de runtime, não são executados em sistemas que suportam a interpretação do ".manifest". De canja, um pequeno programa que exibe a lista dos programas instalados no sistema.

Primeiro, precisamos de um solution que contenha um projeto console e uma LIB. O projeto console deve usar a LIB para fazer alguma coisa. No exemplo abaixo, estarei listando os programas instalados no Windows (os mostrados no painel de controle através da opção "Adicionar/remover programas".

    /** library.h
    */
    #pragma once
    #include <string>
    #include <vector>
    
    typedef std::vector<std::string> InstalledSoftwareList;
    int getInstalledSoftware(InstalledSoftwareList&);
    
    /** library.cpp
    */
    #include "library.h"
    #include <windows.h> // aqui precisamos do windows para as funções de registro
    #include <tchar.h> // suporte a unicode condicional
    
    #define SW_ROOT_KEY "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"
    #define SW_DISPLAY_NAME "DisplayName"
    
    /** Retorna o número de elementos em um array. */
    template<typename T, size_t Sz>
    DWORD SizeofArray(const T(&arr)[Sz]) { return Sz; }
    
    /** Retorna lista com descrição de cada programa instalado no sistema. */
    int getInstalledSoftware(InstalledSoftwareList& installedSoftware)
    {
       HKEY swRoot = NULL;
       DWORD err = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T(SW_ROOT_KEY), 0, KEY_READ, &swRoot);
    
       if( err == ERROR_SUCCESS )
       {
          DWORD swIndex = 0;
          TCHAR swKeyName[MAX_PATH] = _T("");
    
          // para cada chave dentro da raiz de programas instalados
          while( (err = RegEnumKey(swRoot, swIndex++, swKeyName, SizeofArray(swKeyName))) 
             == ERROR_SUCCESS )
          {
             HKEY swCurrent = NULL;
             err = RegOpenKeyEx(swRoot, swKeyName, 0, KEY_READ, &swCurrent);
    
             if( err == ERROR_SUCCESS )
             {
                CHAR swDisplay[MAX_PATH] = ""; // vamos obter a string já em mb
                DWORD swDisplaySz = SizeofArray(swDisplay);
    
                if( (err = RegQueryValueExA(swCurrent, SW_DISPLAY_NAME, 0, NULL, 
                   reinterpret_cast<PBYTE>(swDisplay), &swDisplaySz)) == ERROR_SUCCESS )
                {
                   installedSoftware.push_back(swDisplay);
                }
    
                RegCloseKey(swCurrent);
             }
          }
    
          // se não tem mais itens, então não é um erro
          if( err == ERROR_NO_MORE_ITEMS )
             err = ERROR_SUCCESS;
          RegCloseKey(swRoot);
       }
       return int(err);
    }
    
    /** console.cpp
    */
    #include "../library/library.h" // include da nossa lib
    #include <algorithm>
    #include <iostream>
    
    using namespace std;
    
    int main()
    {
       int ret;
       InstalledSoftwareList swList;
    
       cout << "MSVC Mutant - v. beta\n"
          << "by Wanderley Caloni (www.caloni.com.br)\n\n";
    
       // obtém a lista de programas instalados e exibe na tela
       ret = getInstalledSoftware(swList);
    
       if( ret == 0 )
       {
          cout << "Programs installed on your system\n"
             << "=================================\n";
          copy(swList.begin(), swList.end(), ostream_iterator<string>(cout, "\n"));
    
       }
       else
          cout << "Error " << ret << " trying to list installed programs.\n";
    
       return ret;
    }

Observação importante: para ignorar todas as estripulias da versão Debug, todos os testes foram compilados em Release.

Primeiramente, modifico a configuração padrão dos dois projetos para não depender da DLL de runtime do VC. Isso está em Project, Properties, C/C++, Code Generation, Runtime Library. Depois executo em uma máquina virtual sem as runtimes do VC8 instaladas:

    MSVC Mutant - v. beta
    by Wanderley Caloni (www.caloni.com.br)
    
    Programs installed on your system
    =================================
    Windows XP Service Pack 2
    WebFldrs XP
    VMware Tools

Perfeito. Exatamente o que eu queria: um executável console que não dependesse de DLL nenhuma exceto as que já estão instaladas em um Windows ordinário.

Agora, vamos imaginar que esse é um daqueles projetos enormes de 5 * 10 ^ 42 de linhas (obs: dramatização) e que meu aplicativo console está linkado com cerca de 3 * 10 ^ 666 de LIBs. E uma delas (a library do exemplo) está com a configuração original, ou seja, com a dependência da DLL de runtime. E ela usa a STL. Provavelmente o aplicativo console não irá compilar, mas isso não é problema, pois estamos acostumados a colocar a msvcrt.lib na lista de LIBs ignoradas, pois em muitos outros casos (que não vale a pena discutir aqui) esse workaround é válido. E tudo volta a funcionar. Quer dizer, linkar:

O sistema no pode executar o programa especificado.

Tudo bem, meu executável não é mutante ainda. Mas agora vamos trocar a chamada da nossa função que usa STL por uma função que não usa:

    /** library.h
    */
    int doesNothing();
    
    /** library.cpp
    */
    
    /** Essa função não faz nada. Quer dizer, ela retorna 0. Mas é só isso. */
    int doesNothing()
    {
       return 0;
    }
    
    /** console.cpp
    */
    #include "../library/library.h" // include da nossa lib
    
    int main()
    {
       int ret;
    
       // não faz nada. bom, chama uma função. mas isso é quase nada.
       ret = doesNothing();
    
       return ret;
    }

    Linking
    =======
    library.lib(library.obj) : warning LNK4049: locally 
     defined symbol __invalid_parameter_noinfo imported
    
    Running
    =======
    O sistema no pode executar o programa especificado.
    
    Depends
    =======
    Error: The Side-by-Side configuration information in "blablabla\CONSOLE.EXE" 
     contains errors.
    Falha na inicialização do aplicativo devido a configuração incorreta.
    A reinstalação do aplicativo pode resolver o problema (14001).

Agora sim, a mutação fez efeito! Temos um aplicativo que não depende da DLL de runtime, mas que no meio das n LIBs que ele utiliza existe uma configurada com a dependência. Ignorando a msvcrt.lib e um warning na compilação encontramos uma mensagem de erro um tanto exdrúxula.

Até agora, a maneira que eu tenho utilizado para rastrear esse problema é não ignorar a msvcrt e ir tirando as dependências das LIBs pouco a pouco, até que ocorra o erro de símbolo duplicado. Algo assim:

    MSVCRT.lib(ti_inst.obj) : error LNK2005: "private: __thiscall 
     type_info::type_info(class type_info const &)" (??0type_info@@AAE@ABV0@@Z) 
     already defined in LIBCMT.lib(typinfo.obj)
    MSVCRT.lib(ti_inst.obj) : error LNK2005: "private: class type_info & __thiscall 
     type_info::operator=(class type_info const &)" (??4type_info@@AAEAAV0@ABV0@@Z) 
     already defined in LIBCMT.lib(typinfo.obj)
    LINK : warning LNK4098: defaultlib 'MSVCRT' conflicts with use of other libs; 
     use /NODEFAULTLIB:library
    Blablabla\console.exe : fatal error LNK1169: one or more multiply defined symbols found

Se você tiver realmente 3 * 10 ^ 666 de LIBs, boa sorte =).
