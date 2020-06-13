---
categories: [ "code" ]
date: "2019-09-16"
tags: [ "draft",  ]
title: "Vcpkg: Boost para Windows XP"
---
Quem programa em C++ no Brasil geralmente precisa estar preparado para manter velharias. Boa parte do parque de máquinas das empresas usam Windows, e não estou falando de Windows 10, mas muitas vezes XP. Apesar da Microsoft ter largado uma das melhores versões do seu SO para trás, milhares de máquinas ainda rodam esse bichinho, e muitos programadores precisam manter e desenvolver em nome da compatibilidade.

Porém, o desenvolvimento de libs C++ foram aos poucos largando o suporte ao XP (em C isso não existe muito, pois é mais fácil ser portável em C), pois muitos mecanismos de SOs modernos surgiram depois, como um mutex light ou mutex apenas de read. E como eles olham para o mercado global, o Brasil acaba ficando para trás.

E isso inclui a Boost, o famoso conjunto de bibliotecas usado pelos engenheiros que gostam de complicar seu código. O suporte oficial a XP da Boost acabou na 1.60, mas é possível compilar, se você quiser, versões mais novas, como a 1.68, que usaremos neste artigo. Com ela é possível gerar uma versão compatível com Windows XP usando o builder da Boost e alguns parâmetros mágicos, como toolset e define.

    >b2.exe address-model=32 architecture=x86 link=static toolset=msvc-14.0_xp define=BOOST_USE_WINAPI_VERSION=0x0501 --stagedir=".\stage_x86_xp"

O parâmetro toolset usa no caso a versão compatível para XP do conjunto de compilação do Visual Studio 2015, e o define BOOSTUSEWINAPIVERSION é colocado para suportar pelo menos Windows XP. Já o stagedir seria apenas para separar a compilação padrão para a que suporta XP e é opcional para manter duas compilações distintas. Importante lembrar que, apesar da Microsoft ter extinto o suporte a XP, até o Visual Studio mais novo possui um toolset, compilador e libs para Windows, que suporte o sistema operacional.

Esses mesmos parâmetros usados no build da Boost podem ser usados dentro do vcpkg, o compilador de pacotes multiplataforma da Microsoft. Como esperado, as libs do vcpkg compilam usando tudo do último em sua máquina: Boost, Visual Studio e o suporte ao último Windows (no caso do pacote da Boost, não, se usa o Windows Vista em diante). Mas você pode e deve modificar os ports padrões sempre que necessário. Este artigo explica como fazer partindo do zero sem receita de bolo. Vamos escanear o problema e resolvê-lo. Para isso vamos usar um exemplo bem simples da Boost.Log, que possui dependências mais novas que o Windows XP.

O status inicial e inocente de um projeto que deseja rodar para XP em Visual Studio 2015 (nosso caso de uso, poderia ser o VS mais novo) é criar um projeto que usa Boost.Log pelo wizard, instalar, se ainda não estiver instalado, o Boost.Log no vcpkg, e acabou. Só que não. Eis o código:

    // using Boost.Log
    #include <boost/log/trivial.hpp>
    
    typedef ::boost::log::sources::severity_logger< ::boost::log::trivial::severity_level > severity_logger;
    
    int main()
    {
    	severity_logger lg;
    	BOOST_LOG_SEV(lg, ::boost::log::trivial::severity_level::error) << "test";
    	return 0;
    }

Agora eis as configurações:

    >cat ConsoleApplication1.vcxproj
    
    #Platform Toolset: Visual Studio 2015 (v140)
    <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
      <ConfigurationType>Application</ConfigurationType>
      <UseDebugLibraries>true</UseDebugLibraries>
      <PlatformToolset>v140</PlatformToolset>
      <CharacterSet>Unicode</CharacterSet>
    </PropertyGroup>
    
    #C/C++, Code Generation, Runtime Library: Multi-threaded Debug (/MTd)
    <ClCompile>
      <PrecompiledHeader>Use</PrecompiledHeader>
      <WarningLevel>Level3</WarningLevel>
      <Optimization>Disabled</Optimization>
      <PreprocessorDefinitions>WIN32;_DEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <SDLCheck>true</SDLCheck>
      <RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>
    </ClCompile>
    
    >vcpkg install boost-log:x86-windows-static
    >vcpkg integrate install
    
    #Compiling from Visual Studio IDE
    1>------ Build started: Project: ConsoleApplication1, Configuration: Debug Win32 ------
    1>  ConsoleApplication1.cpp
    1>  ConsoleApplication1.vcxproj -> C:\...\Debug\ConsoleApplication1.exe
    1>  ConsoleApplication1.vcxproj -> C:\...\Debug\ConsoleApplication1.pdb (Full PDB)
    ========== Build: 1 succeeded, 0 failed, 0 up-to-date, 0 skipped ==========
    
    #Running ConsoleApplication1.exe from Windows XP
    C:\Temp>ConsoleApplication1.exe
    
    #MessageBox
    C:\Temp\ConsoleApplication1.exe não é um aplicativo Win32 válido.

Esse é um erro que geralmente acontece por dois motivos. O primeiro é quando rodamos um executável de 64 bits em um ambiente 32, mas este não é o caso. O segundo é  quando rodamos um executável que possui alguma DLL faltando ou funções específicas de alguma DLL, que é o caso. Para descobrir as dependências de um executável basta rodar o comando dumpbin de dentro de um terminal com as ferramentas do Visual Studio disponíveis.

    >"\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\vsvars32.bat"
    >dumpbin /imports ConsoleApplication1.exe
    
    Microsoft (R) COFF/PE Dumper Version 14.00.24215.1
    Copyright (C) Microsoft Corporation.  All rights reserved.
    
    
    Dump of file ConsoleApplication1.exe
    
    File Type: EXECUTABLE IMAGE
    
      Section contains the following imports:
    
        KERNEL32.dll
                    68D000 Import Address Table
                    68D280 Import Name Table
                         0 time date stamp
                         0 Index of first forwarder reference
    
                      32F HeapAlloc
                      333 HeapFree
                      2A2 GetProcessHeap
                      34C InitializeSRWLock <--------- OPS
                      48E ReleaseSRWLockExclusive
                      48F ReleaseSRWLockShared
                        0 AcquireSRWLockExclusive
                        1 AcquireSRWLockShared
                      2D6 GetSystemTimeAsFileTime
                      5B3 WakeAllConditionVariable
                      554 SleepConditionVariableSRW
                      ...

Dependências de APIs relacionadas com o SRWLock dizem respeito ao Slim Read/Write Lock do Windows, implementado a partir do Windows Vista. A primeira coisa a ser descoberta pelo programador é: quem está usando essas funções? Se não está no seu próprio código, provavelmente está em uma das libs linkadas. E uma dessas libs com certeza é o Boost.Log, pelo include no código.

    vcpkg>grep -r InitializeSRWLock --include=*.hpp --include=*.cpp
    
    buildtrees/boost-log/src/ost-1.68.0-cbff90ee0b/include/boost/log/detail/light_rw_mutex.hpp:        boost::winapi::InitializeSRWLock(&m_Mutex);
    buildtrees/boost-log/src/ost-1.68.0-cbff90ee0b/src/once_block.cpp:        typedef void (BOOST_WINAPI_WINAPI_CC *InitializeSRWLock_t)(winapi_srwlock*);
    buildtrees/boost-log/src/ost-1.68.0-cbff90ee0b/src/once_block.cpp:            InitializeSRWLock_t pInitializeSRWLock,
    buildtrees/boost-log/src/ost-1.68.0-cbff90ee0b/src/once_block.cpp:            pInitializeSRWLock(&m_Mutex);
    buildtrees/boost-log/src/ost-1.68.0-cbff90ee0b/src/once_block.cpp:            once_block_impl_nt6::InitializeSRWLock_t pInitializeSRWLock =
    buildtrees/boost-log/src/ost-1.68.0-cbff90ee0b/src/once_block.cpp:                (once_block_impl_nt6::InitializeSRWLock_t)boost::winapi::get_proc_address(hKernel32, "InitializeSRWLock");
    buildtrees/boost-log/src/ost-1.68.0-cbff90ee0b/src/once_block.cpp:            if (pInitializeSRWLock)
    buildtrees/boost-log/src/ost-1.68.0-cbff90ee0b/src/once_block.cpp:                                        pInitializeSRWLock,
    buildtrees/boost-log/src/ost-1.68.0-cbff90ee0b/src/windows/light_rw_mutex.cpp://! A complement stub function for InitializeSRWLock
    buildtrees/boost-log/src/ost-1.68.0-cbff90ee0b/src/windows/light_rw_mutex.cpp:            (init_fun_t)boost::winapi::get_proc_address(hKernel32, "InitializeSRWLock");
    buildtrees/boost-winapi/src/ost-1.68.0-9d99055439/include/boost/winapi/srw_lock.hpp:InitializeSRWLock(::_RTL_SRWLOCK* SRWLock);
    buildtrees/boost-winapi/src/ost-1.68.0-9d99055439/include/boost/winapi/srw_lock.hpp:BOOST_FORCEINLINE VOID_ InitializeSRWLock(PSRWLOCK_ SRWLock)
    buildtrees/boost-winapi/src/ost-1.68.0-9d99055439/include/boost/winapi/srw_lock.hpp:    ::InitializeSRWLock(reinterpret_cast< ::_RTL_SRWLOCK* >(SRWLock));
    installed/x86-windows-static/include/boost/log/detail/light_rw_mutex.hpp:        boost::winapi::InitializeSRWLock(&m_Mutex);
    installed/x86-windows-static/include/boost/winapi/srw_lock.hpp:InitializeSRWLock(::_RTL_SRWLOCK* SRWLock);
    installed/x86-windows-static/include/boost/winapi/srw_lock.hpp:BOOST_FORCEINLINE VOID_ InitializeSRWLock(PSRWLOCK_ SRWLock)
    installed/x86-windows-static/include/boost/winapi/srw_lock.hpp:    ::InitializeSRWLock(reinterpret_cast< ::_RTL_SRWLOCK* >(SRWLock));
    packages/boost-log_x86-windows-static/include/boost/log/detail/light_rw_mutex.hpp:        boost::winapi::InitializeSRWLock(&m_Mutex);
    packages/boost-winapi_x86-windows-static/include/boost/winapi/srw_lock.hpp:InitializeSRWLock(::_RTL_SRWLOCK* SRWLock);
    packages/boost-winapi_x86-windows-static/include/boost/winapi/srw_lock.hpp:BOOST_FORCEINLINE VOID_ InitializeSRWLock(PSRWLOCK_ SRWLock)
    packages/boost-winapi_x86-windows-static/include/boost/winapi/srw_lock.hpp:    ::InitializeSRWLock(reinterpret_cast< ::_RTL_SRWLOCK* >(SRWLock));

Note as linhas onde ::InitializeSRWLock é chamado. O escopo global indica que há uma dependência estática entre essa função API e o executável se essa parte do código for compilada, o que pode ser descoberto através da IDE do Visual Studio abrindo os arquivos e verificando se a parte onde há essas chamadas fica "cinza" (há defines que impedem essa parte de compilar), ou depurando e inserindo breakpoints nessa parte, que deverá ser chamada. O dumpbin poderia ser usado de novo caso houvesse símbolos para explorar o uso dessas funções de dentro do executável, mas por padrão a compilação do Boost não gera símbolos, tornando a tarefa ingrata, pois estará tudo em assembly sem tradução para o fonte.

Então, ficamos mesmo na análise do código-fonte e da compilação:

    >cat installed\x86-windows-static\include\boost\winapi\srw_lock.hpp
    
    #if BOOST_USE_WINAPI_VERSION >= BOOST_WINAPI_VERSION_WIN6
    #include <boost/winapi/basic_types.hpp>
    
    //...
    
    namespace boost {
    namespace winapi {
    
    BOOST_FORCEINLINE VOID_ InitializeSRWLock(PSRWLOCK_ SRWLock)
    {
        ::InitializeSRWLock(reinterpret_cast< ::_RTL_SRWLOCK* >(SRWLock));
    }
    
    //...
    
    #endif // #if BOOST_USE_WINAPI_VERSION >= BOOST_WINAPI_VERSION_WIN6

Se analisarmos onde BOOSTUSEWINAPIVERSION é definido descobriremos que ele é um reflexo do famigerado WIN32WINNT, que é o define que o Windows usa para determinar qual a versão mínima que o executável deve rodar. Windows Vista é 0x0600, Windows XP é 0x0501 (com SP 2 em diante 0x0502).

Isso quer dizer que devemos compilar nosso projeto indicando que pretendemos rodar em Windows XP:

    >cat ConsoleApplication1.vcxproj
    
    #Platform Toolset: Visual Studio 2015 (v140_xp)
    <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
      <PlatformToolset>v140_xp</PlatformToolset>
    </PropertyGroup>
    
    #C/C++, Preprocessor, Preprocessor Definitions
    <ClCompile>
      <PreprocessorDefinitions>_WIN32_WINNT=0x501;WIN32;_DEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
    </ClCompile>

E aí começam os problemas de linker.

    #Compiling from Visual Studio IDE
    1>------ Build started: Project: ConsoleApplication1, Configuration: Debug Win32 ------
    1>  stdafx.cpp
    1>  ConsoleApplication1.cpp
    1>ConsoleApplication1.obj : error LNK2019: unresolved external symbol "public: static void * __cdecl boost::log::v2s_mt_nt5::attribute::impl::operator new(unsigned int)" (??2impl@attribute@v2s_mt_nt5@log@boost@@SAPAXI@Z) referenced in function "public: __thiscall boost::log::v2s_mt_nt5::sources::aux::severity_level<enum boost::log::v2s_mt_nt5::trivial::severity_level>::severity_level<enum boost::log::v2s_mt_nt5::trivial::severity_level>(void)" (??0?$severity_level@W40trivial@v2s_mt_nt5@log@boost@@@aux@sources@v2s_mt_nt5@log@boost@@QAE@XZ)
    1>ConsoleApplication1.obj : error LNK2019: unresolved external symbol "public: static void __cdecl boost::log::v2s_mt_nt5::attribute::impl::operator delete(void *,unsigned int)" (??3impl@attribute@v2s_mt_nt5@log@boost@@SAXPAXI@Z) referenced in function "public: virtual void * __thiscall boost::log::v2s_mt_nt5::attributes::attribute_value_impl<enum boost::log::v2s_mt_nt5::trivial::severity_level>::`scalar deleting destructor'(unsigned int)" (??_G?$attribute_value_impl@W4severity_level@trivial@v2s_mt_nt5@log@boost@@@attributes@v2s_mt_nt5@log@boost@@UAEPAXI@Z)

Aparentemente a própria lib Boost.Log está entrando em contradição com ela mesma, pois há usos dos métodos new e delete, por exemplo, entre vários. A análise da lib compilada irá nos revelar que esses nomes realmente não existem.

    vcpkg>dir /s /b installed\*boost*log*.lib
    installed\x86-windows-static\debug\lib\boost_log-vc140-mt-gd.lib
    installed\x86-windows-static\debug\lib\boost_log_setup-vc140-mt-gd.lib
    installed\x86-windows-static\lib\boost_log-vc140-mt.lib
    installed\x86-windows-static\lib\boost_log_setup-vc140-mt.lib
    
    vcpkg>dumpbin /symbols c:\Libs\vcpkg\installed\x86-windows-static\debug\lib\boost_log-vc140-mt-gd.lib | grep v2s_mt_nt5
    
    <empty result>

Não há nenhum símbolo com esse namespace. Precisamos agora averiguar de onde ele vem.

    vcpkg>grep -r --include=*.hpp --include=*.cpp v2s_mt_nt5
    buildtrees/boost-log/src/ost-1.68.0-cbff90ee0b/include/boost/log/detail/config.hpp:#                   define BOOST_LOG_VERSION_NAMESPACE v2s_mt_nt5
    installed/x86-windows-static/include/boost/log/detail/config.hpp:#                   define BOOST_LOG_VERSION_NAMESPACE v2s_mt_nt5
    
    >cat packages/boost-log_x86-windows-static/include/boost/log/detail/config.hpp
    
    #       if defined(BOOST_LOG_NO_THREADS)
    #           define BOOST_LOG_VERSION_NAMESPACE v2s_st
    #       else
    #           if defined(BOOST_THREAD_PLATFORM_PTHREAD)
    #               define BOOST_LOG_VERSION_NAMESPACE v2s_mt_posix
    #           elif defined(BOOST_THREAD_PLATFORM_WIN32)
    #               if BOOST_USE_WINAPI_VERSION >= BOOST_WINAPI_VERSION_WIN6
    #                   define BOOST_LOG_VERSION_NAMESPACE v2s_mt_nt6
    #               else
    #                   define BOOST_LOG_VERSION_NAMESPACE v2s_mt_nt5
    #               endif
    #           else
    #               define BOOST_LOG_VERSION_NAMESPACE v2s_mt
    #           endif
    #       endif // defined(BOOST_LOG_NO_THREADS)

Então o Boost precisa ser compilado com esse define, também. Do contrário ele deve conter o namespace v2smtnt6 em sua lib. Mudando o define no nosso projeto ele irá apenas mudar a definição nos headers, mas não na lib já compilada.

    vcpkg>gvim packages/boost-log_x86-windows-static/include/boost/log/detail/config.hpp
    
    c:\Libs\vcpkg>dumpbin /symbols c:\Libs\vcpkg\installed\x86-windows-static\debug\lib\boost_log-vc140-mt-gd.lib | grep v2s_mt_nt6
    4A0 00000000 UNDEF  notype ()    External     | ?throw_@system_error@v2s_mt_nt6@log@boost@@SAXPBDI0H@Z (public: static void __cdecl boost::log::v2s_mt_nt6::system_error::throw_(char const *,unsigned int,char const *,int))
    4A1 00000000 SECT5  notype ()    External     | ??0object_name@ipc@v2s_mt_nt6@log@boost@@QAE@W4scope@01234@PBD@Z (public: __thiscall boost::log::v2s_mt_nt6::ipc::object_name::object_name(enum boost::log::v2s_mt_nt6::ipc::object_name::scope,char const *))
    4A2 00000090 SECT5  notype ()    External     | ??0object_name@ipc@v2s_mt_nt6@log@boost@@QAE@W4scope@01234@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z (public: __thiscall boost::log::v2s_mt_nt6::ipc::object_name::object_name(enum boost::log::v2s_mt_nt6::ipc::object_name::scope,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const &))
    4AF 00000000 SECTCD notype ()    External     | ??0auto_handle@aux@ipc@v2s_mt_nt6@log@bo
    ...

Mas para isso precisamos descobrir como o Boost é compilado no vcpkg. Sabemos que ele utiliza arquivos cmake dentro de cada subpasta em port, que junto de uma série de scripts já disponíveis pela ferramenta irá executar ações de compilação, instalação, etc. De dentro do Boost.Log encontramos alguns arquivos para analisar.

    c:\Libs\vcpkg>pushd ports\boost-log
    
    c:\Libs\vcpkg\ports\boost-log>ls
    CONTROL  portfile.cmake
    
    c:\Libs\vcpkg\ports\boost-log>cat CONTROL
    # Automatically generated by boost-vcpkg-helpers/generate-ports.ps1
    Source: boost-log
    Version: 1.68.0
    Build-Depends: boost-align, boost-array, boost-asio, boost-assert, boost-atomic, boost-bind, boost-build, boost-compatibility, boost-config, boost-container, boost-core, boost-date-time, boost-detail, boost-exception, boost-filesystem (!uwp), boost-function-types, boost-fusion, boost-integer, boost-interprocess, boost-intrusive, boost-io, boost-iterator, boost-lexical-cast, boost-locale (!uwp), boost-math, boost-modular-build-helper, boost-move, boost-mpl, boost-optional, boost-parameter, boost-phoenix, boost-predef, boost-preprocessor, boost-property-tree, boost-proto, boost-random, boost-range, boost-regex, boost-smart-ptr, boost-spirit, boost-static-assert, boost-system, boost-thread (!arm), boost-throw-exception, boost-type-index, boost-type-traits, boost-utility, boost-vcpkg-helpers, boost-winapi, boost-xpressive
    Description: Boost log module
    
    c:\Libs\vcpkg\ports\boost-log>cat portfile.cmake
    # Automatically generated by boost-vcpkg-helpers/generate-ports.ps1
    
    include(vcpkg_common_functions)
    
    vcpkg_from_github(
        OUT_SOURCE_PATH SOURCE_PATH
        REPO boostorg/log
        REF boost-1.68.0
        SHA512 d12f9b2d8f782e4df5df16fe6c5267c87266348f6c7c400a9c6ff0b1b7af34ee8baf3d0b4dc4aef20b0a5faf4582d5c90d3429df84d903773bef3e61df93a0d9
        HEAD_REF master
    )
    
    file(READ "${SOURCE_PATH}/build/Jamfile.v2" _contents)
    string(REPLACE "import ../../config/checks/config" "import config/checks/config" _contents "${_contents}")
    string(REPLACE " <conditional>@select-arch-specific-sources" "#<conditional>@select-arch-specific-sources" _contents "${_contents}")
    file(WRITE "${SOURCE_PATH}/build/Jamfile.v2" "${_contents}")
    file(COPY "${CURRENT_INSTALLED_DIR}/share/boost-config/checks" DESTINATION "${SOURCE_PATH}/build/config")
    
    file(READ ${SOURCE_PATH}/build/log-architecture.jam _contents)
    string(REPLACE
        "\nproject.load [ path.join [ path.make $(here:D) ] ../../config/checks/architecture ] ;"
        "\nproject.load [ path.join [ path.make $(here:D) ] config/checks/architecture ] ;"
        _contents "${_contents}")
    file(WRITE ${SOURCE_PATH}/build/log-architecture.jam "${_contents}")
    
    include(${CURRENT_INSTALLED_DIR}/share/boost-build/boost-modular-build.cmake)
    boost_modular_build(SOURCE_PATH ${SOURCE_PATH})
    include(${CURRENT_INSTALLED_DIR}/share/boost-vcpkg-helpers/boost-modular-headers.cmake)
    boost_modular_headers(SOURCE_PATH ${SOURCE_PATH})

Não há nada que indique a versão do Windows, mas há um include de boost-modular-build.cmake que parece útil.

    c:\Libs\vcpkg\ports\boost-vcpkg-helpers>pushd ..\boost-modular-build-helper
    
    c:\Libs\vcpkg\ports\boost-modular-build-helper>ls
    CMakeLists.txt  CONTROL  Jamroot.jam  boost-modular-build.cmake  nothing.bat  portfile.cmake  user-config.jam
    
    c:\Libs\vcpkg\ports\boost-modular-build-helper>cat boost-modular-build.cmake
    function(boost_modular_build)
        cmake_parse_arguments(_bm "" "SOURCE_PATH;REQUIREMENTS;BOOST_CMAKE_FRAGMENT" "OPTIONS" ${ARGN})
    
        ...
    
        file(TO_CMAKE_PATH "${_bm_DIR}/nothing.bat" NOTHING_BAT)
        set(TOOLSET_OPTIONS " <cxxflags>/EHsc <compileflags>-Zm800 <compileflags>-nologo")
        if(VCPKG_CMAKE_SYSTEM_NAME STREQUAL "WindowsStore")
            ...
            set(TOOLSET_OPTIONS "${TOOLSET_OPTIONS} <cflags>-Zl <compileflags>\"/AI\"${PLATFORM_WINMD_DIR}\"\" <linkflags>WindowsApp.lib <cxxflags>/ZW <compileflags>-DVirtualAlloc=VirtualAllocFromApp <compileflags>-D_WIN32_WINNT=0x0A00")
        else()
            set(TOOLSET_OPTIONS "${TOOLSET_OPTIONS} <compileflags>-D_WIN32_WINNT=0x0602")
        endif()
    
        if(VCPKG_PLATFORM_TOOLSET MATCHES "v141")
            list(APPEND _bm_OPTIONS toolset=msvc-14.1)
        elseif(VCPKG_PLATFORM_TOOLSET MATCHES "v140")
            list(APPEND _bm_OPTIONS toolset=msvc-14.0)
        elseif(VCPKG_PLATFORM_TOOLSET MATCHES "external")
            list(APPEND _bm_OPTIONS toolset=gcc)
        else()
            message(FATAL_ERROR "Unsupported value for VCPKG_PLATFORM_TOOLSET: '${VCPKG_PLATFORM_TOOLSET}'")
        endif()
    
        ...

Há muito mais coisa nesse cmake, incluindo definição de toolset e os define de WIN32WINNT, que está como 0x602, ou seja, acima do Windows XP. No entanto, esses flags são da compilação do Visual Studio, e não do b2.exe, o compilador do Boost. Como vimos no início do artigo, são os parâmetros para o b2.exe que precisam ser modificados. Ao analisar sua execução de dentro do próprio cmake podemos verificar que há uma variável com essas opções, o bmOPTIONS. O que faz muito sentido.

    vcpkg_execute_required_process(
        COMMAND "${B2_EXE}"
            --stagedir=${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-rel/stage
            --build-dir=${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-rel
            --user-config=${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-rel/user-config.jam
            ${_bm_OPTIONS}
            ${_bm_OPTIONS_REL}
            variant=release
            debug-symbols=on
        WORKING_DIRECTORY ${_bm_SOURCE_PATH}/build
        LOGNAME build-${TARGET_TRIPLET}-rel
    
    boost-modular-build-helper>grep _bm_OPTIONS boost-modular-build.cmake
            list(APPEND _bm_OPTIONS windows-api=store)
        list(APPEND _bm_OPTIONS
            list(APPEND _bm_OPTIONS threadapi=win32)
            list(APPEND _bm_OPTIONS threadapi=pthread)
        set(_bm_OPTIONS_DBG
        set(_bm_OPTIONS_REL
            list(APPEND _bm_OPTIONS runtime-link=shared)
            list(APPEND _bm_OPTIONS runtime-link=static)
            list(APPEND _bm_OPTIONS link=shared)
            list(APPEND _bm_OPTIONS link=static)
            list(APPEND _bm_OPTIONS address-model=64 architecture=x86)
            list(APPEND _bm_OPTIONS address-model=32 architecture=arm)
            list(APPEND _bm_OPTIONS address-model=32 architecture=x86)
            list(APPEND _bm_OPTIONS toolset=msvc-14.1)
            list(APPEND _bm_OPTIONS toolset=msvc-14.0)
            list(APPEND _bm_OPTIONS toolset=gcc)
                    ${_bm_OPTIONS}
                    ${_bm_OPTIONS_REL}
                    ${_bm_OPTIONS}
                    ${_bm_OPTIONS_DBG}

Me parece que o segredo é inserir ou modificar os argumentos dessa variável e as libs da Boost estarão automagicamente modificadas. Me parece isso hoje, horas e horas depois de analisar o build do vcpkg. Mas vou lhe economizar essas horas. Podemos realizar essa mudança pontualmente no boost-modular-build-helper, mas também devemos recompilá-lo, o que inclui suas dependências e toda a bagaça.

    vcpkg>vcpkg remove boost-modular-build-helper:x86-windows-static
    The following packages will be removed:
      * boost-algorithm:x86-windows-static
      * boost-asio:x86-windows-static
      ...
      * boost-log:x86-windows-static
      * boost-math:x86-windows-static
      ...
      * boost-xpressive:x86-windows-static
    Additional packages (*) need to be removed to complete this operation.
    If you are sure you want to remove them, run the command with the --recurse option
    
    vcpkg>vcpkg remove --recurse boost-modular-build-helper:x86-windows-static
    The following packages will be removed:
      * boost-algorithm:x86-windows-static
      * boost-asio:x86-windows-static
      ...
      * boost-lexical-cast:x86-windows-static
      * boost-locale:x86-windows-static
      * boost-log:x86-windows-static
      * boost-math:x86-windows-static
        boost-modular-build-helper:x86-windows-static
      * boost-multi-index:x86-windows-static
      ...
      * boost-unordered:x86-windows-static
      * boost-xpressive:x86-windows-static
    Additional packages (*) need to be removed to complete this operation.
    Removing package boost-log:x86-windows-static...
    Removing package boost-log:x86-windows-static... done
    Purging package boost-log:x86-windows-static...
    Purging package boost-log:x86-windows-static... done
    Removing package boost-asio:x86-windows-static...
    Removing package boost-asio:x86-windows-static... done
    Removing package boost-modular-build-helper:x86-windows-static...
    ...
    Removing package boost-modular-build-helper:x86-windows-static... done
    Purging package boost-modular-build-helper:x86-windows-static...
    Purging package boost-modular-build-helper:x86-windows-static... done
    
    
             set(TOOLSET_OPTIONS "${TOOLSET_OPTIONS} <cflags>-Zl <compileflags>\"/AI\"${PLATFORM_WINMD_DIR}\"\" <linkflags>WindowsApp.lib <cxxflags>/ZW <compileflags>-DVirtualAlloc=VirtualAllocFromApp <compileflags>-D_WIN32_WINNT=0x0A00")
         else()
    -        set(TOOLSET_OPTIONS "${TOOLSET_OPTIONS} <compileflags>-D_WIN32_WINNT=0x0602")
    +        set(TOOLSET_OPTIONS "${TOOLSET_OPTIONS} <compileflags>-D_WIN32_WINNT=0x0501 -DBOOST_USE_WINAPI_VERSION=0x0501")
    +        list(APPEND _bm_OPTIONS define=BOOST_USE_WINAPI_VERSION=0x0501)^M
         endif()
    
         if(VCPKG_PLATFORM_TOOLSET MATCHES "v141")
    -        list(APPEND _bm_OPTIONS toolset=msvc-14.1)
    +        list(APPEND _bm_OPTIONS toolset=msvc-14.1_xp)
         elseif(VCPKG_PLATFORM_TOOLSET MATCHES "v140")
    -        list(APPEND _bm_OPTIONS toolset=msvc-14.0)
    +        list(APPEND _bm_OPTIONS toolset=msvc-14.0_xp)
         elseif(VCPKG_PLATFORM_TOOLSET MATCHES "external")
             list(APPEND _bm_OPTIONS toolset=gcc)
    
    
    c:\Libs\vcpkg>vcpkg install boost-log:x86-windows-static
    The following packages will be built and installed:
      * boost-algorithm[core]:x86-windows-static
      * boost-align[core]:x86-windows-static
      * boost-any[core]:x86-windows-static
      * boost-array[core]:x86-windows-static
      ...
        boost-log[core]:x86-windows-static
      * boost-math[core]:x86-windows-static
      ... lots and lots of libs after
      * boost-winapi[core]:x86-windows-static
      * boost-xpressive[core]:x86-windows-static

Eu sei, é triste, mas mais uma caneca de café, uma partidinha de xadrez, e está pronta a recompilação. Fun fact: antigamente a compilação do Boost te dava essa dica de ir fazer café.

    #alguns (muitos) cafés depois...
    1>------ Build started: Project: ConsoleApplication1, Configuration: Debug Win32 ------
    1>  ConsoleApplication1.cpp
    1>  ConsoleApplication1.vcxproj -> C:\Users\caloni\Documents\Visual Studio 2015\Projects\ConsoleApplication1\Debug\ConsoleApplication1.exe
    1>  ConsoleApplication1.vcxproj -> C:\Users\caloni\Documents\Visual Studio 2015\Projects\ConsoleApplication1\Debug\ConsoleApplication1.pdb (Full PDB)
    ========== Build: 1 succeeded, 0 failed, 0 up-to-date, 0 skipped ==========
    
    >dumpbin /imports "C:\Users\caloni\Documents\Visual Studio 2015\Projects\ConsoleApplication1\Debug\ConsoleApplication1.exe"
    Microsoft (R) COFF/PE Dumper Version 14.00.24215.1
    Copyright (C) Microsoft Corporation.  All rights reserved.
    
    
    Dump of file C:\Users\caloni\Documents\Visual Studio 2015\Projects\ConsoleApplication1\Debug\ConsoleApplication1.exe
    
    File Type: EXECUTABLE IMAGE
    
      Section contains the following imports:
    
        KERNEL32.dll
                    693000 Import Address Table
                    693264 Import Name Table
                         0 time date stamp
                         0 Index of first forwarder reference
    
                      2CB HeapAlloc
                      2CF HeapFree
                      24A GetProcessHeap
                      279 GetSystemTimeAsFileTime
                       52 CloseHandle
                       E8 DuplicateHandle
                      459 SetEvent
                      3FE ReleaseSemaphore
                      ...
    
    #Running ConsoleApplication1.exe from Windows XP
    C:\Temp>ConsoleApplication1.exe
    [2019-09-16 15:59:44.261500] [0x00000194] [error]   test

And voilà! Não há mais dependências das APIs muito novas e conseguimos executar nosso programa em Windows XP. Mas, mais importante que isso, o que aprendemos:

 - A verificar os símbolos importados por um executável usando `dumpbin`, se certificando de que ele poderá rodar em SOs mais antigos.
 - A buscar pelo uso de funções novas pelos fontes compilados pelo vcpkg.
 - A analisar o build do vcpkg para poder modificá-lo e ser compatível com o ambiente que precisamos.
