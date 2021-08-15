---
categories:
- code
date: 2018-02-20 00:06:40-03:00
tags:
title: Variáveis static local Nunca São Inicializadas Se Você Não Chama Sua Função
---

Uma dúvida muito comum dos programadores iniciantes em C/C++ diz respeito às variáveis static que são declaradas dentro de um escopo, como uma função. Sabemos que se ela fosse declarada global, fora de qualquer escopo, ela seria inicializada antes do main ser chamado, como diz este trecho de alguém que pesquisou a respeito:

> "C++ Primer says. Each local static variable is initialized before the first time execution passes through the object's definition. Local statics are not destroyed when a function ends; they are destroyed when program terminates." - Someone that google it for but did not get it

Mas no caso de variáveis static declaradas dentro de uma função isso não acontece, e ela pode ser inicializada a qualquer momento. Basta alguém chamar a função onde ela foi definida.

```
#include <iostream>

int func2()
{
    std::cout << "Func2 called\n";
    return 21;
}

int func()
{
    static int st_x = func2();
    return st_x * 2;
}

int main()
{
    std::cout << "Passing by...\n";
    std::cout << "Func returns " << func() << std::endl;
    std::cout << "Exiting...\n";
}
```

```
c:\Projects\caloni\projects>cl /EHsc static_local_sample.cpp
Microsoft (R) C/C++ Optimizing Compiler Version 19.12.25827 for x86
Copyright (C) Microsoft Corporation.  All rights reserved.

static_local_sample.cpp
Microsoft (R) Incremental Linker Version 14.12.25827.0
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:static_local_sample.exe
static_local_sample.obj

c:\Projects\caloni\projects>
```

```

c:\Projects\caloni\projects>static_local_sample.exe
Passing by...
Func2 called
Func returns 42
Exiting...

c:\Projects\caloni\projects>
```

Note que mesmo trocando static int para static const int a mesma coisa acontece. Apenas conseguimos forçar a inicialização antes do main quando há alguma variável global (static ou não) que chame a função.

```
#include <iostream>

int func2()
{
    std::cout << "Func2 called\n";
    return 21;
}

int func()
{
    static int st_x = func2();
    return st_x * 2;
}

static const int g_x = func();

int main()
{
    std::cout << "Passing by...\n";
    std::cout << "Func returns " << func() << std::endl;
    std::cout << "Exiting...\n";
}
```

```
c:\Projects\caloni\projects>cl /EHsc static_local_sample.cpp
Microsoft (R) C/C++ Optimizing Compiler Version 19.12.25827 for x86
Copyright (C) Microsoft Corporation.  All rights reserved.

static_local_sample.cpp
Microsoft (R) Incremental Linker Version 14.12.25827.0
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:static_local_sample.exe
static_local_sample.obj

c:\Projects\caloni\projects>static_local_sample.exe
Func2 called
Passing by...
Func returns 42
Exiting...

c:\Projects\caloni\projects>
```

O problema disso é que é possível que duas threads chamem func() "ao mesmo tempo", gerando uma dupla inicialização caso a implementação da libc não seja thread-safe. E a menos que o padrão especifique que essa inicialização deva ser thread safe, melhor fazer as coisas direito.

Mas, a título de curiosidade, é bom saber que o Visual Studio 2017 essa parte da libc já possui um mecanismo de proteção, como o sugestivo nome _tls_index já indica:

```
c:\Projects\caloni\projects>cl /EHsc /Zi static_local_sample.cpp
Microsoft (R) C/C++ Optimizing Compiler Version 19.12.25827 for x86
Copyright (C) Microsoft Corporation.  All rights reserved.

static_local_sample.cpp
Microsoft (R) Incremental Linker Version 14.12.25827.0
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:static_local_sample.exe
/debug
static_local_sample.obj

c:\Projects\caloni\projects>windbg static_local_sample.exe
```

```
static_local_sample!func [c:\projects\caloni\projects\static_local_sample.cpp @ 10]:
   10 000fe410 55              push    ebp
   10 000fe411 8bec            mov     ebp,esp
   10 000fe413 6aff            push    0FFFFFFFFh
   10 000fe415 686c801800      push    offset static_local_sample!wcschr+0x1cc7 (0018806c)
   10 000fe41a 64a100000000    mov     eax,dword ptr fs:[00000000h]
   10 000fe420 50              push    eax
   10 000fe421 a180901a00      mov     eax,dword ptr [static_local_sample!__security_cookie (001a9080)]
   10 000fe426 33c5            xor     eax,ebp
   10 000fe428 50              push    eax
   10 000fe429 8d45f4          lea     eax,[ebp-0Ch]
   10 000fe42c 64a300000000    mov     dword ptr fs:[00000000h],eax
   11 000fe432 a11cb51a00      mov     eax,dword ptr [static_local_sample!_tls_index (001ab51c)] ((( Thread Local Storage? )))
   11 000fe437 648b0d2c000000  mov     ecx,dword ptr fs:[2Ch]
   11 000fe43e 8b1481          mov     edx,dword ptr [ecx+eax*4]
   11 000fe441 a128b01a00      mov     eax,dword ptr [static_local_sample!st_x+0x4 (001ab028)]
   11 000fe446 3b8204010000    cmp     eax,dword ptr [edx+104h]
   11 000fe44c 7e3b            jle     static_local_sample!func+0x79 (000fe489) ((( compara para ver se chama inicialização ou não )))

static_local_sample!func+0x3e [c:\projects\caloni\projects\static_local_sample.cpp @ 11]:
   11 000fe44e 6828b01a00      push    offset static_local_sample!st_x+0x4 (001ab028)
   11 000fe453 e8a736ffff      call    static_local_sample!ILT+2810(__Init_thread_header) (000f1aff)
   11 000fe458 83c404          add     esp,4
   11 000fe45b 833d28b01a00ff  cmp     dword ptr [static_local_sample!st_x+0x4 (001ab028)],0FFFFFFFFh
   11 000fe462 7525            jne     static_local_sample!func+0x79 (000fe489)

static_local_sample!func+0x54 [c:\projects\caloni\projects\static_local_sample.cpp @ 11]:
   11 000fe464 c745fc00000000  mov     dword ptr [ebp-4],0
   11 000fe46b e8bb37ffff      call    static_local_sample!ILT+3110(?func2YAHXZ) (000f1c2b) ((( note a chamada a func2 )))
   11 000fe470 a324b01a00      mov     dword ptr [static_local_sample!st_x (001ab024)],eax
   11 000fe475 c745fcffffffff  mov     dword ptr [ebp-4],0FFFFFFFFh
   11 000fe47c 6828b01a00      push    offset static_local_sample!st_x+0x4 (001ab028)
   11 000fe481 e89443ffff      call    static_local_sample!ILT+6165(__Init_thread_footer) (000f281a)
   11 000fe486 83c404          add     esp,4

static_local_sample!func+0x79 [c:\projects\caloni\projects\static_local_sample.cpp @ 12]:
   12 000fe489 a124b01a00      mov     eax,dword ptr [static_local_sample!st_x (001ab024)] ((( a partir da segunda chamada tudo começa aqui )))
   12 000fe48e d1e0            shl     eax,1
   13 000fe490 8b4df4          mov     ecx,dword ptr [ebp-0Ch]
   13 000fe493 64890d00000000  mov     dword ptr fs:[0],ecx
   13 000fe49a 59              pop     ecx
   13 000fe49b 8be5            mov     esp,ebp
   13 000fe49d 5d              pop     ebp
   13 000fe49e c3              ret
```
