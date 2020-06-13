---
categories: [ "code" ]
date: "2017-07-27"
tags: [ "draft",  ]
title: "Forma Mais Simples De Depurar Processos Antes Do Logon"
---
No post anterior sobre debug eu havia me focado mais na depuração de processos remotos no Visual Studio 2003 de maneira convencional. Aqui eu vou abordar o assunto de uma maneira menos convencional: usando o Visual Studio 2017 mais novo e depurando uma DLL (C++) que é carregada por um serviço antes do logon no Windows 7.

Em primeiro lugar, como vimos anteriormente, a ponta server do depurador é um programa que você executa com alguns parâmetros e ele fica escutando em uma porta. Simples assim. Para que isso funcione antes do logon é necessário instalar esse programa como um serviço. Tanto no caso de depuradores mais antigos (msvCmon) quando nos mais novos (msvSmon) há sempre um executável com alguns parâmetros passados via linha de comando.

O depurador do Visual Studio mais novo fica em sua pasta de instalação Program Files, etc, Microsoft Visual Studio, 2017, Enterprise, Common7, IDE, Remote Debugger ou derivados. Dentro dessa pasta há subpastas para cada arquitetura, x64 ou x86. É essa pasta que deve ser copiada para a máquina que será depurada. Se você estiver depurando um processo 32 bits, use o x86; do contrário, vá de x64.

No caso do msvsmon, se executado com /? (padrão entre programas Windows) ele abre um pequeno help com a ajuda necessária para executar os parâmetros corretos. No caso o comando maroto é o seguinte:

    msvsmon.exe /timeout 999999 /anyuser /silent /noauth

E para transformar em um serviço podemos usar o NSSM, já visto em outros artigos.

    nssm.exe install Msvsmon msvsmon.exe /timeout 999999 /anyuser /silent /noauth

Isso cria um serviço de start automático que irá iniciar o debugger na ponta server quietinho, sem janelas, só escutando e esperando o Visual Studio atachar.

Para este exemplo vamos usar um programa console que será convertido, assim como o msvsmon, em serviço, e uma DLL que ele carrega, chamando dois métodos; um de start, outro de stop. Nosso objetivo aqui é começar a depurar a DLL logo em seu início, na chamada do start.

    #include <iostream>
    #include <windows.h>
    
    int main()
    {
        if( HMODULE dll = LoadLibraryA("DLL") )
        {
            void (*start)(), (*stop)();
            *((FARPROC*)&start) = GetProcAddress(dll, "DLL_Start");
            *((FARPROC*)&stop) = GetProcAddress(dll, "DLL_Stop");
            if( start )
                start();
            std::cout << "Type <enter> to exit\n";
            std::cin.get();
            if( stop )
                stop();
            FreeLibrary(dll);
        }
        else std::cout << "DLL not found\n";
    }

As funções de start e stop não fazem nada, apenas imprimem um passou-por-aqui:

    #include "DLL.h"
    #include <iostream>
    
    void DLL_Start()
    {
        std::cout << "DLL started\n";
    }
    
    void DLL_Stop()
    {
        std::cout << "DLL stopped\n";
    }

Todo o projeto está no GitHub para baixar e compilar você mesmo.

Depois de copiar Service.exe e DLL.dll para a máquina-alvo (e não se esquecer de instalar as dependências) instalar da mesma forma com que foi instalado o msvsmon:

    nssm.exe install Service service.exe

Agora ache o IP da máquina-alvo e vá em Debug, Attach to Process (Ctrl+Alt+P) no Visual Studio, modo remoto e digite o IP.

    cmd /k ipconfig | find "192"

Lembre-se de iniciar o serviço.

Após esse teste podemos modificar a DLL para aguardar por um depurador:

    #include <windows.h>
    
    void DLL_Start()
    {
        while( ! IsDebuggerPresent() )
            Sleep(1000);
        std::cout << "DLL started\n";
    }

Depois que houver o attach você irá continuar a execução. Portanto, coloque um breakpoint logo depois. E depois que isso funcionar já é possível iniciar sua depuração antes da tela de login. Os serviços executarão, e sua DLL estará aguardando um debugger ser atachado. Se houver necessidade é possível deixar esse modo de espera configurável, por timeout, etc.
