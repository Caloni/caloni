---
categories:
- blog
date: '2008-09-10'
tags:
title: Retorno do PathIsDirectory
---

Estava eu outro dia programando aquele código esperto "para ontem" quando me deparei com uma situação no mínimo inusitada. Ao testar se um caminho recebido era de fato um diretório me foi retornado pela API um valor diferente de TRUE. E diferente de FALSE!

De acordo com a documentação, o retorno deveria ser TRUE caso o caminho enviado à função fosse de fato um diretório. Caso contrário, o retorno deveria ser FALSE.

Note que existem apenas dois valores possíveis para essa função. Porém, o valor retornado não é 1, o equivalente ao define TRUE, mas sim 0x10 (16 em hexadecimal). O simples exemplo abaixo deve conseguir reproduzir a situação (Windows XP Service Pack 3):

    Setting environment for using Microsoft Visual Studio 2008 x86 tools.
    
    C:\Tests>copy con IsPathDir.cpp
    #include <shlwapi.h>
    #include <windows.h>
    #include <stdio.h>
    
    #pragma comment(lib, "shlwapi.lib")
    
    int main()
    {
            BOOL isDir = PathIsDirectory("C:\\Tests"); // obs.: diretorio TEM que existir
            printf("Resultado: %d.\n", isDir);
    }^Z
            1 arquivo(s) copiado(s).
    
    C:\Tests>cl IsPathDir.cpp
    Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 15.00.21022.08 for 80x86
    Copyright (C) Microsoft Corporation.  All rights reserved.
    
    IsPathDir.cpp
    Microsoft (R) Incremental Linker Version 9.00.21022.08
    Copyright (C) Microsoft Corporation.  All rights reserved.
    
    /out:IsPathDir.exe
    IsPathDir.obj
    
    C:\Tests>IsPathDir.exe
    Resultado: 16.

Isso quer dizer apenas que o código abaixo vai funcionar,

    if( PathIsDirectory(path) ) // legal: qualquer coisa diferente de zero

o código abaixo vai funcionar

    if( ! PathIsDirectory(path) ) // legal: se der zero (FALSE), OK

e o código abaixo não vai funcionar:

    if( PathIsDirectory(path) == TRUE ) // vixi: TRUE nem sempre é o resultado

E, pior, o código abaixo também não vai funcionar!

    if( PathIsDirectory(path) != TRUE ) // aff... é bom rever os seus conceitos

Pesquisando um pouco descobri uma boa discussão sobre o tema, e inclusive que outras pessoas descobriram o interessante detalhe que para pastas normais o retorno é 0x10, mas para compartilhamentos o retorno é 0x1.

#### O bug atrás dos documentos

O problema ocorre por causa da maneira que a função determina se o caminho é um diretório ou não. Uma simples vistoria sobre a função nos revela o detalhe crucial:

    C:\Tests>cl /Zi IsPathDir.cpp
    Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 15.00.21022.08 for 80x86
    Copyright (C) Microsoft Corporation.  All rights reserved.
    
    IsPathDir.cpp
    Microsoft (R) Incremental Linker Version 9.00.21022.08
    Copyright (C) Microsoft Corporation.  All rights reserved.
    
    /out:IsPathDir.exe
    /debug
    IsPathDir.obj
    
    C:\Tests>cdb IsPathDir.exe
    
    Microsoft (R) Windows Debugger Version 6.8.0004.0 X86
    Copyright (c) Microsoft Corporation. All rights reserved.
    
    CommandLine: IsPathDir.exe
    Symbol search path is: SRV*c:\symbols*http://msdl.microsoft.com/download/symbols
    Executable search path is:
    ModLoad: 00400000 00426000   IsPathDir.exe
    ModLoad: 7c900000 7c9b4000   ntdll.dll
    ModLoad: 7c800000 7c8ff000   C:\WINDOWS\system32\kernel32.dll
    ModLoad: 77ea0000 77f16000   C:\WINDOWS\system32\SHLWAPI.dll
    ModLoad: 77f50000 77ffb000   C:\WINDOWS\system32\ADVAPI32.dll
    ModLoad: 77db0000 77e41000   C:\WINDOWS\system32\RPCRT4.dll
    ModLoad: 77e50000 77e97000   C:\WINDOWS\system32\GDI32.dll
    ModLoad: 7e360000 7e3f0000   C:\WINDOWS\system32\USER32.dll
    ModLoad: 77bf0000 77c48000   C:\WINDOWS\system32\msvcrt.dll
    (ea0.de0): Break instruction exception - code 80000003 (first chance)
    eax=00241eb4 ebx=7ffde000 ecx=00000004 edx=00000010 esi=00241f48 edi=00241eb4
    eip=7c901230 esp=0012fb20 ebp=0012fc94 iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    ntdll!DbgBreakPoint:
    7c901230 cc              int     3
    0:000> g shlwapi!PathIsDirectoryA
    ModLoad: 76360000 7637d000   C:\WINDOWS\system32\IMM32.DLL
    ModLoad: 62e80000 62e89000   C:\WINDOWS\system32\LPK.DLL
    ModLoad: 74d50000 74dbb000   C:\WINDOWS\system32\USP10.dll
    eax=009836e0 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0006f4cc edi=7c911970
    eip=77ee7538 esp=0012ff6c ebp=0012ff78 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA:
    77ee7538 8bff            mov     edi,edi
    0:000> p
    eax=009836e0 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0006f4cc edi=7c911970
    eip=77ee753a esp=0012ff6c ebp=0012ff78 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0x2:
    77ee753a 55              push    ebp
    0:000>
    eax=009836e0 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0006f4cc edi=7c911970
    eip=77ee753b esp=0012ff68 ebp=0012ff78 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0x3:
    77ee753b 8bec            mov     ebp,esp
    0:000>
    eax=009836e0 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0006f4cc edi=7c911970
    eip=77ee753d esp=0012ff68 ebp=0012ff68 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0x5:
    77ee753d 81ec0c020000    sub     esp,20Ch
    0:000>
    eax=009836e0 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0006f4cc edi=7c911970
    eip=77ee7543 esp=0012fd5c ebp=0012ff68 iopl=0         nv up ei pl nz ac pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000216
    SHLWAPI!PathIsDirectoryA+0xb:
    77ee7543 a180d2f077      mov     eax,dword ptr [SHLWAPI!__security_cookie
    0:000>
    eax=00007a43 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0006f4cc edi=7c911970
    eip=77ee7548 esp=0012fd5c ebp=0012ff68 iopl=0         nv up ei pl nz ac pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000216
    SHLWAPI!PathIsDirectoryA+0x10:
    77ee7548 56              push    esi
    0:000>
    eax=00007a43 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0006f4cc edi=7c911970
    eip=77ee7549 esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl nz ac pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000216
    SHLWAPI!PathIsDirectoryA+0x11:
    *** WARNING: Unable to verify checksum for IsPathDir.exe
    77ee7549 8b7508          mov     esi,dword ptr [ebp+8] ss:0023:0012ff70=0041dc5c
    0:000>
    eax=00007a43 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0041dc5c edi=7c911970
    eip=77ee754c esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl nz ac pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000216
    SHLWAPI!PathIsDirectoryA+0x14:
    77ee754c 85f6            test    esi,esi
    0:000>
    eax=00007a43 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0041dc5c edi=7c911970
    eip=77ee754e esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl nz na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000206
    SHLWAPI!PathIsDirectoryA+0x16:
    77ee754e 8945fc          mov     dword ptr [ebp-4],eax ss:0023:0012ff64=fffffffe
    0:000>
    eax=00007a43 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0041dc5c edi=7c911970
    eip=77ee7551 esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl nz na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000206
    SHLWAPI!PathIsDirectoryA+0x19:
    77ee7551 0f8493000000    je      SHLWAPI!PathIsDirectoryA+0xb2 (77ee75ea) [br=0]
    0:000>
    eax=00007a43 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0041dc5c edi=7c911970
    eip=77ee7557 esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl nz na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000206
    SHLWAPI!PathIsDirectoryA+0x1f:
    77ee7557 56              push    esi
    0:000>
    eax=00007a43 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0041dc5c edi=7c911970
    eip=77ee7558 esp=0012fd54 ebp=0012ff68 iopl=0         nv up ei pl nz na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000206
    SHLWAPI!PathIsDirectoryA+0x20:
    77ee7558 e85cc0fdff      call    SHLWAPI!PathIsUNCServerA (77ec35b9)
    0:000>
    eax=00000000 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0041dc5c edi=7c911970
    eip=77ee755d esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0x25:
    77ee755d 85c0            test    eax,eax
    0:000>
    eax=00000000 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0041dc5c edi=7c911970
    eip=77ee755f esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0x27:
    77ee755f 0f8585000000    jne     SHLWAPI!PathIsDirectoryA+0xb2 (77ee75ea) [br=0]
    0:000>
    eax=00000000 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0041dc5c edi=7c911970
    eip=77ee7565 esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0x2d:
    77ee7565 56              push    esi
    0:000>
    eax=00000000 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0041dc5c edi=7c911970
    eip=77ee7566 esp=0012fd54 ebp=0012ff68 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0x2e:
    77ee7566 e812feffff      call    SHLWAPI!PathIsUNCServerShareA (77ee737d)
    0:000>
    eax=00000000 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0041dc5c edi=7c911970
    eip=77ee756b esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0x33:
    77ee756b 85c0            test    eax,eax
    0:000>
    eax=00000000 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0041dc5c edi=7c911970
    eip=77ee756d esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0x35:
    77ee756d 0f8486000000    je      SHLWAPI!PathIsDirectoryA+0xc1 (77ee75f9) [br=1]
    0:000>
    eax=00000000 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0041dc5c edi=7c911970
    eip=77ee75f9 esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0xc1:
    77ee75f9 56              push    esi
    0:000>
    eax=00000000 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0041dc5c edi=7c911970
    eip=77ee75f9 esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0xc1:
    77ee75f9 56              push    esi
    0:000>
    eax=00000000 ebx=7ffde000 ecx=00000001 edx=00422828 esi=0041dc5c edi=7c911970
    eip=77ee75fa esp=0012fd54 ebp=0012ff68 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0xc2:
    77ee75fa ff15d411ea77    call    dword ptr [SHLWAPI!_imp__GetFileAttributesA (77ea11d4)]
    0:000>
    eax=00000011 ebx=7ffde000 ecx=7c91056d edx=00140608 esi=0041dc5c edi=7c911970
    eip=77ee7600 esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0xc8:
    77ee7600 83f8ff          cmp     eax,0FFFFFFFFh
    0:000>
    eax=00000011 ebx=7ffde000 ecx=7c91056d edx=00140608 esi=0041dc5c edi=7c911970
    eip=77ee7603 esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl nz ac pe cy
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000217
    SHLWAPI!PathIsDirectoryA+0xcb:
    77ee7603 74e5            je      SHLWAPI!PathIsDirectoryA+0xb2 (77ee75ea) [br=0]
    0:000>
    eax=00000011 ebx=7ffde000 ecx=7c91056d edx=00140608 esi=0041dc5c edi=7c911970
    eip=77ee7605 esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl nz ac pe cy
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000217
    SHLWAPI!PathIsDirectoryA+0xcd:
    77ee7605 83e010          and     eax,10h
    0:000>
    eax=00000010 ebx=7ffde000 ecx=7c91056d edx=00140608 esi=0041dc5c edi=7c911970
    eip=77ee7608 esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    SHLWAPI!PathIsDirectoryA+0xd0:
    77ee7608 ebe2            jmp     SHLWAPI!PathIsDirectoryA+0xb4 (77ee75ec)
    0:000>
    eax=00000010 ebx=7ffde000 ecx=7c91056d edx=00140608 esi=0041dc5c edi=7c911970
    eip=77ee75ec esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    SHLWAPI!PathIsDirectoryA+0xb4:
    77ee75ec 8b4dfc          mov     ecx,dword ptr [ebp-4] ss:0023:0012ff64=00007a43
    0:000>
    eax=00000010 ebx=7ffde000 ecx=00007a43 edx=00140608 esi=0041dc5c edi=7c911970
    eip=77ee75ef esp=0012fd58 ebp=0012ff68 iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    SHLWAPI!PathIsDirectoryA+0xb7:
    77ee75ef 5e              pop     esi
    0:000>
    eax=00000010 ebx=7ffde000 ecx=00007a43 edx=00140608 esi=0006f4cc edi=7c911970
    eip=77ee75f0 esp=0012fd5c ebp=0012ff68 iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    SHLWAPI!PathIsDirectoryA+0xb8:
    77ee75f0 e82bcafbff      call    SHLWAPI!__security_check_cookie (77ea4020)
    0:000>
    eax=00000010 ebx=7ffde000 ecx=00007a43 edx=00140608 esi=0006f4cc edi=7c911970
    eip=77ee75f5 esp=0012fd5c ebp=0012ff68 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0xbd:
    77ee75f5 c9              leave
    0:000>
    eax=00000010 ebx=7ffde000 ecx=00007a43 edx=00140608 esi=0006f4cc edi=7c911970
    eip=77ee75f6 esp=0012ff6c ebp=0012ff78 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    SHLWAPI!PathIsDirectoryA+0xbe:
    77ee75f6 c20400          ret     4
    0:000>
    eax=00000010 ebx=7ffde000 ecx=00007a43 edx=00140608 esi=0006f4cc edi=7c911970
    eip=0040101f esp=0012ff74 ebp=0012ff78 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    IsPathDir!main+0xf:
    0040101f 8945fc          mov     dword ptr [ebp-4],eax ss:0023:0012ff74=00000001
    0:000>
    eax=00000010 ebx=7ffde000 ecx=00007a43 edx=00140608 esi=0006f4cc edi=7c911970
    eip=00401022 esp=0012ff74 ebp=0012ff78 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    IsPathDir!main+0x12:
    00401022 8b45fc          mov     eax,dword ptr [ebp-4] ss:0023:0012ff74=00000010
    0:000>
    eax=00000010 ebx=7ffde000 ecx=00007a43 edx=00140608 esi=0006f4cc edi=7c911970
    eip=00401025 esp=0012ff74 ebp=0012ff78 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    IsPathDir!main+0x15:
    00401025 50              push    eax
    0:000>
    eax=00000010 ebx=7ffde000 ecx=00007a43 edx=00140608 esi=0006f4cc edi=7c911970
    eip=00401026 esp=0012ff70 ebp=0012ff78 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    IsPathDir!main+0x16:
    00401026 6868dc4100      push    offset IsPathDir!__xt_z+0x12c (0041dc68)
    0:000>
    eax=00000010 ebx=7ffde000 ecx=00007a43 edx=00140608 esi=0006f4cc edi=7c911970
    eip=0040102b esp=0012ff6c ebp=0012ff78 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    IsPathDir!main+0x1b:
    0040102b e81a000000      call    IsPathDir!printf (0040104a)
    0:000>
    Resultado: 16.
    eax=0000000f ebx=7ffde000 ecx=004010e5 edx=004228b8 esi=0006f4cc edi=7c911970
    eip=00401030 esp=0012ff6c ebp=0012ff78 iopl=0         nv up ei ng nz ac pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000296
    IsPathDir!main+0x20:
    00401030 83c408          add     esp,8
    0:000>

Ou seja, para pastas locais a função simplesmente usa a conhecidíssima GetFileAttributes, que retorna o flag 0x10 setado caso se trate de uma pasta, de acordo com a documentação: "The attributes can be one or more of the following values:"

    Return code/value              Description

    FILE_ATTRIBUTE_ARCHIVE         A file or directory that is an archive file or directory.
    32
    0x20

    FILE_ATTRIBUTE_COMPRESSED      A file or directory that is compressed.
    2048
    0x800
    ...
    
    FILE_ATTRIBUTE_DIRECTORY       The handle that identifies a directory.
    16
    0x10

Aqui termina nossa dúvida sobre o pequenino bug na documentação. E isso nos lembra também que é sempre bom comparar as coisas da melhor maneira possível. E essa melhor maneira em se tratando de ifs é supor apenas dois valores binário: ou é zero ou é não-zero.
