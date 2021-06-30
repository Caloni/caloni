---
categories:
- blog
date: '2008-08-13'
tags: null
title: Quando o navegador não quer largar um arquivo
---

De vez em quando gosto muito de um vídeo que estou assistindo. Gosto tanto que faço questão de guardar para assistir mais vezes depois. O problema é que o meu Firefox ou, para ser mais técnico, o plugin de vídeo que roda em cima do meu navegador, não permite isso. Ele simplesmente cria um arquivo temporário para exibir o vídeo e logo depois o apaga, utilizando uma técnica muito útil da função CreateFile, que bloqueia o acesso do arquivo temporário e apaga-o logo após o uso:

    HANDLE WINAPI CreateFile(
      __in      LPCTSTR lpFileName,
      __in      DWORD dwDesiredAccess,
      __in      DWORD dwShareMode,
      __in_opt  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      __in      DWORD dwCreationDisposition,
      __in      DWORD dwFlagsAndAttributes,
      __in_opt  HANDLE hTemplateFile
    );

#### dwShareMode

    Value                        Meaning
    0                            Disables subsequent open operations on a file or device
    0x00000000                   to request any type of access to that file or device.

#### dwFlagsAndAttributes

    Value                        Meaning
    FILE_FLAG_DELETE_ON_CLOSE    The file is to be deleted immediately after all of its
                                 handles are closed, which includes the specified handle
                                 and any other open or duplicated handles.

Muito bem. Isso quer dizer que é possível abrir um arquivo que mais ninguém pode abrir (nem para copiar para outro arquivo), e ao mesmo tempo garante que quando ele for fechado será apagado. Isso parece uma ótima proteção de cópia não-autorizada para a maioria das pessoas.

Infelizmente, tudo isso roda sob limites muito restritos: um navegador, rodando em user mode, usando APIs bem definidas e facilmente depuráveis.

#### De volta ao WinDbg

Antes de iniciar a reprodução do vídeo, e conseqüentemente a criação do arquivo temporário, podemos atachar uma instância do nosso depurador do coração e colocar um breakpoint onde interessa:

    windbg -pn firefox.exe

    Microsoft (R) Windows Debugger Version 6.8.0004.0 X86
    Copyright (c) Microsoft Corporation. All rights reserved.
    
    *** wait with pending attach
    Symbol search path is: SRV*C:\Symbols*http://msdl.microsoft.com/download/symbols;K:\Docs\Projects
    Executable search path is:
    ModLoad: 00400000 00b64000   L:\FirefoxPortable\App\firefox\firefox.exe
    ModLoad: 7c900000 7c9b4000   C:\WINDOWS\system32\ntdll.dll
    ModLoad: 7c800000 7c8ff000   C:\WINDOWS\system32\kernel32.dll
    ...
    ModLoad: 77a00000 77a55000   C:\WINDOWS\System32\cscui.dll
    ModLoad: 765d0000 765ed000   C:\WINDOWS\System32\CSCDLL.dll
    (b58.ba8): Break instruction exception - code 80000003 (first chance)
    eax=7ffdb000 ebx=00000001 ecx=00000002 edx=00000003 esi=00000004 edi=00000005
    eip=7c901230 esp=021bffcc ebp=021bfff4 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=0038  gs=0000             efl=00000246
    ntdll!DbgBreakPoint:
    7c901230 cc              int     3
    0:017> bp kernel32!CreateFileA
    0:017> bp kernel32!CreateFileW
    0:017> g
    Breakpoint 2 hit
    eax=00000001 ebx=00000000 ecx=05432c10 edx=0000003e esi=0532ea00 edi=00000000
    eip=7c831f31 esp=0317fdc4 ebp=0317fde8 iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    kernel32!CreateFileW:
    7c810760 8bff            mov     edi,edi

Nesse momento podemos dar uma boa olhada nos parâmetros 4 e 6 da função para ver se trata-se realmente da proteção prevista (na verdade, prevista, nada; esse é um artigo baseado em uma experiência passada; vamos imaginar, contudo, que estamos descobrindo essas coisas como na primeira vez).

    0:000> dd esp
    0012f30c  300afc06 03f91920 c0000000 00000000
    0012f31c  00000000 00000002 14000000 00000000

Como podemos ver, o modo de compartilhamento do arquivo é nenhum. Entre os flags definidos no sexto parâmetro, está o de apagar o arquivo ao fechar o handle, como pude constatar no header do SDK.

Nesse caso, a solução mais óbvia e simples foi deixar esse bit desabilitado, não importando se o modo de compartilhamento está desativado. Tudo que temos que fazer é assistir o vídeo mais uma vez e fechar a aba do navegador. O arquivo será fechado, o compartilhamento aberto, e o arquivo, não apagado.

    0:012> bp kernel32!CreateFileW "ed @esp+4*6 poi(@esp+4*6) & 0xfbffffff"
    breakpoint 1 redefined
    0:012> bp kernel32!CreateFileA "ed @esp+4*6 poi(@esp+4*6) & 0xfbffffff"
    breakpoint 0 redefined
    0:012> g

E agora posso voltar a armazenar meus vídeos favoritos.