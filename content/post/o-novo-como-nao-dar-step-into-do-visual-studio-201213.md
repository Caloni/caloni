---
categories: [ "code" ]
date: "2014-08-01"
tags: [ "draft",  ]
title: "O novo 'como não dar step into' do Visual Studio 2012/13"
---
Toda vez que instalo um Visual Studio novo e começo a depurar sempre surge a necessidade de fazê-lo calar a boca nos step intos da STL, Boost, ATL e coisas que sei que não vai dar pau. (Obviamente, quando dá pau, preciso ir no disassembly e cutucar a STL para ela me entregar qual o problema com o meu contêiner.)

Nas edições antigas da IDE (até o 2010) existia uma configuração no registro para isso. Desde o Visual Studio 2012 isso mudou, e agora existe um arquivo em %programfiles(x86)%\Microsoft Visual Studio 11(ou12).0\Common7\Packages\Debugger\Visualizers chamado default.natstepfilter (gostei do detalhe do "nat": "nat thou step into, little bestard!"). Ele é um XML que já vem preenchido com algumas opções interessante:

    <?xml version="1.0" encoding="utf-8"?>
    <StepFilter xmlns="http://schemas.microsoft.com/vstudio/debugger/natstepfilter/2010">
      <Function><Name>__security_check_cookie</Name><Action>NoStepInto</Action></Function>
      <Function><Name>__abi_winrt_.*</Name><Action>NoStepInto</Action></Function>
      <Function><Name>_ObjectStublessClient.*</Name><Action>NoStepInto</Action></Function>
      <Function><Name>_Invoke@12</Name><Action>NoStepInto</Action></Function>
      <Function><Name>_RTC_Check(Esp|StackVars)</Name><Action>NoStepInto</Action></Function>
      <Function><Name>_chkstk</Name><Action>NoStepInto</Action></Function>
      <Function><Name>ATL::CComPtrBase.*::operator&amp;</Name><Action>NoStepInto</Action></Function>
      <Function><Name>ATL::CComPtrBase.*::operator-&gt;</Name><Action>NoStepInto</Action></Function>
      <Function><Name>ATL::CHeapPtrBase.*::operator&amp;</Name><Action>NoStepInto</Action></Function>
      <Function><Name>ATL::CHeapPtrBase.*::operator-&gt;</Name><Action>NoStepInto</Action></Function>
      <Function><Name>ATL::CComBSTR::operator&amp;</Name><Action>NoStepInto</Action></Function>
      <Function><Name>std::forward&lt;.*</Name><Action>NoStepInto</Action></Function>
      <Function><Name>std::move&lt;.*</Name><Action>NoStepInto</Action></Function>
      <Function><Name>Platform::EventSource::Invoke.*</Name><Action>NoStepInto</Action></Function>
      <Function><Name>std::.*</Name><Action>NoStepInto</Action></Function>
      <Function><Name>boost::.*</Name><Action>NoStepInto</Action></Function>
    </StepFilter>
    

Podemos simplesmente adicionar mais duas opções para o parzinho STL/Boost:

    <?xml version="1.0" encoding="utf-8"?>
    <StepFilter xmlns="http://schemas.microsoft.com/vstudio/debugger/natstepfilter/2010">
    
      <Function><Name>std::.*</Name><Action>NoStepInto</Action></Function>
      <Function><Name>boost::.*</Name><Action>NoStepInto</Action></Function>
    
    </StepFilter>
    

A boa nova, pelo menos para o Visual Studio 2013, é que agora é possível, se quisermos, entrar nas funções que serão ignoradas:

Eu não sei qual vai ser a próxima novidade do step into, mas para mim, já está bem ótimo.

(Fonte da informação: Andy Pennell's Blog).

