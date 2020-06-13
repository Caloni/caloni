---
categories: [ "code" ]
date: "2016-01-21"
tags: [ "draft",  ]
title: "Log de chamadas API direto do WinDbg"
---
Há muito tempo atrás eu havia falado sobre como a ferramenta logger.exe, do Debugging Tools for Windows, poderia ser usada para gerar um arquivo de log com centenas de APIs detalhadas em sua chamada, como parâmetros de entrada, retorno e tempo. Bom, testando isso hoje, me veio à lembrança o artigo e também a constatação que o logger é muito instável. Tão instável que não consegui logar as APIs que desejava nas inúmeras tentativas que fiz. Isso em um Windows XP!

Felizmente, as funções do logger também estão em uma DLL estilo plugin do próprio WinDbg, que pode ser chamada facilmente e que -- surpresa! -- internamente ao depurador funciona. Melhor ainda, não é necessário criar um processo para realizar o log, mas pode ser atachado em um processo já em execução, o que facilita bastante seu uso em serviços, por exemplo.

Vamos testar aqui o log da nossa cobaia de plantão, o amigo Notepad (ou Bloco de Notas), exibindo um texto que demonstra com perfeição uma das minhas características mais bizarras: confundir expressões e frases prontas.

Nota: Lembrando que estaremos testando em Windows XP 32 bits com um WinDbg igualmente 32 bits. Inicialmente comecei a testar a versão 64, mas ela também deu xabu. Aparentemente coisas periféricas do Debugging Tools nunca são muito bem testadas.

    Cirandinha que bate bate
    Cirandinha de Sao Tome
    Quando Dona Chica virou os olhos
    Acumulhou milhas maritimas

O texto ainda não foi salvo em nenhum arquivo. Iremos salvá-lo, mas antes, vamos executar o WinDbg e ver como o Notepad realiza essa operação.

    windbg -pn notepad.exe

A extensão/plugin que me referia é o Logexts.dll. Você pode instalar o log de API em um momento, habilitá-lo em outro, e até desabilitá-lo depois. Ou seja, é um processo ótimo para realizar inspeção pontual de chamadas API. Caso, claro, ele não exploda em um desses momentos.

    (9c4.f04): Break instruction exception - code 80000003 (first chance)
    eax=7ffd9000 ebx=00000001 ecx=00000002 edx=00000003 esi=00000004 edi=00000005
    eip=7c90120e esp=003bffcc ebp=003bfff4 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=0038  gs=0000             efl=00000246
    *** ERROR: Symbol file could not be found.  Defaulted to export symbols for 
    C:\WINDOWS\system32\ntdll.dll - 
    ntdll!DbgBreakPoint:
    7c90120e cc              int     3
    0:001> !logexts.logi 
    
    Windows API Logging Extensions  v3.01
    Parsing the manifest files...
    Location: C:\Temp\DbgTools(x86)\winext\manifest\main.h
       Parsing file "main.h" ...
       Parsing file "winerror.h" ...
       Parsing file "kernel32.h" ...
       ...
       Parsing file "dsound.h" ...
    Parsing completed.
    Logexts injected. Output: "C:\Documents and Settings..."
    0:001> g
    ModLoad: 50000000 50056000   C:\Temp\DbgTools(x86)\winext\logexts.dll
    Parsing the manifest files...
    Location: C:\Temp\DbgTools(x86)\winext\manifest\main.h
       Parsing file "main.h" ...
       Parsing file "winerror.h" ...
       Parsing file "kernel32.h" ...
       ...
       Parsing file "dsound.h" ...
    Parsing completed.
    (9c4.664): Break instruction exception - code 80000003 (first chance)
    eax=7ffd9000 ebx=00000001 ecx=00000002 edx=00000003 esi=00000004 edi=00000005
    eip=7c90120e esp=003bffcc ebp=003bfff4 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=0038  gs=0000             efl=00000246
    ntdll!DbgBreakPoint:
    7c90120e cc              int     3
    0:001> !logexts.loge
    Logging already initialized. Output "C:\Documents and Settings\..."
    Logging enabled.
    0:001> g
    ModLoad: 77b40000 77b62000   C:\WINDOWS\system32\appHelp.dll
    ModLoad: 76fd0000 7704f000   C:\WINDOWS\system32\CLBCATQ.DLL
    ...
    (9c4.41c): Break instruction exception - code 80000003 (first chance)
    eax=7ffd9000 ebx=00000001 ecx=00000002 edx=00000003 esi=00000004 edi=00000005
    eip=7c90120e esp=00f1ffcc ebp=00f1fff4 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=0038  gs=0000             efl=00000246
    ntdll!DbgBreakPoint:
    7c90120e cc              int     3
    0:004> !logexts.logd
    Logging disabled.
    0:004> .detach
    Detached

Depois de gerarmos o que precisamos, podemos desatachar do processo e analisar o resultado: um arquivo LGV. Para abrir esse arquivo existe uma outra ferramenta chamada logviewer. Para evitar procurar em dezenas de milhares de chamadas, há uma opção de filtrar com apenas o que queremos (no caso, CreateFile e WriteFile).

Depois de filtrado, podemos abrir a linha que nos interessa para ver como o programa utilizou a API (quais parâmetros, o retorno, etc). Nesse caso, por exemplo, houve uma falha antes na abertura do mesmo arquivo, mas isso porque houve uma tentativa de abrir um arquivo que já existe (abertura com direito de apenas leitura). Essa chamada foi feita pela DLL do diálogo comum de abertura/salvamento de arquivo do Windows (comdlg32.dll), e não pelo notepad.exe.

Como já havia dito no artigo original sobre o logview, você pode criar seu próprio header com as definições das funções de um módulo e o WinDbg graciosamente irá gerar um log de chamadas, incluindo medidas de performance. Esses dados abertos pelo logviewer podem ser exportados também para modo texto. E temos mais uma maneira de perfcounter chulé para eventualidades.
