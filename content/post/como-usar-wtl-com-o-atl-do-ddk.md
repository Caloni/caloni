---
date: "2008-10-15"
title: Como usar WTL com o ATL do DDK
categories: [ "blog" ]
---
[![wdkandatl.png](http://i.imgur.com/OoiV6X7.png)](/images/wdkandatl.png)Eu simplemente não entendo a organização dos cabeçalhos e fontes dos SDKs da Microsoft. Houve uma vez em que o [ATL](http://www.1bit.com.br/content.1bit/weblog/sopa_de_letrinhas_ATL) era distribuído junto com o SDK, e dessa forma conseguíamos usar o [WTL](http://www.1bit.com.br/content.1bit/weblog/sopa_de_letrinhas_wtl) sem ônus. Porém, um belo dia, isso é retirado do pacote, para tristeza dos que já haviam convertido a biblioteca de janelas para fonte aberto.

No entanto, num belo dia, qual não foi minha surpresa ao notar [umas pastinhas](http://i.imgur.com/OoiV6X7.png) chamadas atl21, atl30 e atl71 dentro da distribuição do WDK (o finado DDK, renomeado sabe-se-lá-por-quê)? Pelo visto, tem alguém arrastando coisa errada pra onde não devia nos instaladores de Seattle. Esses estagiários!

O fato é que eles fizeram isso, e agora é possível ter o WTL mais novo compilado com o WDK. E nem é tão difícil assim.

A primeira coisa a fazer é obter o tal doWDK. Para variar um pouco, agora existe um [processo de registro](http://www.microsoft.com/whdc/DevTools/WDK/WDKpkg.mspx) antes de obter acesso ao _download_, mais ou menos nos termos da Borland para baixar o [Builder](http://cc.codegear.com/free/turbo) / [Turbo](http://cc.codegear.com/free/turbo) / [Developer Studio](http://cc.codegear.com/free/turbo).

<blockquote>Aliás, para os que baixaram esses produtos gratuitos da Borland versão C++ e não funcionou em algumas máquinas, como foi o meu caso, está disponível para baixar uma versão mais nova; dessa vez não vi nenhum problema na compilação e depuração. Ainda.</blockquote>

Após instalado, em qualquer lugar da sua escolha, configure no seu [Visual Studio Express](http://www.microsoft.com/Express/) o caminho de onde se encontra a pasta atl71 (ou a 30, ou a 21). Aproveite também para colocar a pasta do WTL e o diretório de LIBs:

![Configurando o diretório de cabeçalhos no Visual Studio.](http://i.imgur.com/TJyNrlE.png)

![Configurando o diretório de biblioteca no Visual Studio.](http://i.imgur.com/VLryS9L.png)

Isso vai fazer com que pelo menos os exemplos que vêem com o WTL compilem.

No entanto, você verá o seguinte erro durante a compilação dos recursos:

    
    ------ Build started: Project: MTPad, Configuration: Debug Win32 ------
    Compiling resources...
    Microsoft (R) Windows (R) Resource Compiler Version 6.0.5724.0
    Copyright (C) Microsoft Corporation.  All rights reserved.
    Linking...
    CVTRES : fatal error CVT1100: <font color="#ff0000">duplicate resource</font>.  type:MANIFEST, name:1, language:0x0409
    LINK : fatal error LNK1123: failure during conversion to COFF: file invalid or corrupt
    Build log was saved at "file://c:\Lng\WTL\Samples\MTPad\Debug\BuildLog.htm"
    MTPad - 2 error(s), 0 warning(s)
    ========== Build: 0 succeeded, 1 failed, 0 up-to-date, 0 skipped ==========

Para resolver esse problema, remova a inclusão do arquivo de manifesto no arquivo RC:

    
    2 TEXTINCLUDE DISCARDABLE
    BEGIN
        "#include ""atlres.h""\r\n"
        "\0"
    END
    
    <font color="#ff0000">3 TEXTINCLUDE DISCARDABLE
    BEGIN
        "CREATEPROCESS_MANIFEST_RESOURCE_ID RT_MANIFEST ""res\\\\MTPad.exe.manifest""\r\n"
        "\0"
    END</font>
    
    #endif    // APSTUDIO_INVOKED
    
    ...
    
    #ifndef APSTUDIO_INVOKED
    /////////////////////////////////////////////////////////////////////////////
    //
    // Generated from the TEXTINCLUDE 3 resource.
    //
    <font color="#ff0000">CREATEPROCESS_MANIFEST_RESOURCE_ID RT_MANIFEST "res\\MTPad.exe.manifest"</font>
    
    /////////////////////////////////////////////////////////////////////////////
    #endif    // not APSTUDIO_INVOKED

Depois dessa alteração, deve ainda existir o seguinte erro de linquedição:

    
    ------ Build started: Project: MTPad, Configuration: Debug Win32 ------
    Compiling resources...
    Microsoft (R) Windows (R) Resource Compiler Version 6.0.5724.0
    Copyright (C) Microsoft Corporation.  All rights reserved.
    Linking...
    <font color="#ff0000">mtpad.obj : error LNK2019: unresolved external symbol
       "void * __stdcall ATL::__AllocStdCallThunk(void)" (bla bla bla)
    mtpad.obj : error LNK2019: unresolved external symbol
       "void __stdcall ATL::__FreeStdCallThunk(void *)" (bla bla bla)
    </font>.\Debug/MTPad.exe : fatal error LNK1120: 2 unresolved externals
    Build log was saved at "file://c:\Lng\WTL\Samples\MTPad\Debug\BuildLog.htm"
    MTPad - 3 error(s), 0 warning(s)
    ========== Build: 0 succeeded, 1 failed, 0 up-to-date, 0 skipped ==========

Esse problema ocorre porque as funções de alocação e desalocação de memória da ATL estão em outra LIB que os exemplos da WTL desconhecem. Para resolver, basta incluir essa nova dependência:

    
    #pragma comment(lib, "<strong>atlthunk.lib</strong>")

E pronto! Agora temos todo o poder das 500 milhões de classes da ATL aliadas à ilimitada flexibilidade das classes de janelas da WTL.

#### Para aprender a usar WTL

	
  * [Explicando a sopa de letrinhas da programação C/C++ para Windows: WTL](http://www.1bit.com.br/content.1bit/weblog/sopa_de_letrinhas_wtl)

	
  * [WTL for MFC Programmers](http://www.codeproject.com/KB/wtl/wtl4mfc1.aspx)

