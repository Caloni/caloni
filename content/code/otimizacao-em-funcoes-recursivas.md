---
date: "2008-01-18"
title: Otimização em funções recursivas
categories: [ "code" ]
---
O [livro que estou lendo](http://compare.buscape.com.br/categoria?id=3482&lkout=1&kw=Dominando+algoritmos+com+C&site_origem=1293522) fala sobre algoritmos em C. Os primeiros capítulos são praticamente uma revisão para quem já programou em C, pois tratam de coisas que programadores com mais de cinco anos de casa devem ter na memória cachê (listas, pilhas, recursão, etc). Porém, tive uma agradável surpresa de achar um truque muito sabido que não conhecia, chamado de [tail recursion](http://en.wikipedia.org/wiki/Tail_recursion). Fiz questão de testar nos dois compiladores mais conhecidos e eis o resultado.

#### Recursividade cara

Imagine uma função recursiva que calcula o [fatorial](http://pt.wikipedia.org/wiki/Fatorial) de um número. Apenas para lembrar, o fatorial de um número n é igual a n * n-1 * n-2 * n-3 até o número 1. Existem implementações iterativas (com um laço for, por exeplo) e recursivas, que no caso chamam a mesma função n vezes.

```c
int factorial(int n)
{
	if (n > 1)
		return factorial(n - 1) * n;
	else
		return 1;
}

int main()
{
	return factorial(1000);
}
 

```

Para ver o _overhead_ de uma função dessas, compilamos com a opção de debug e depuramos no CDB.

    
    cl /Zi recursive-factorial1.c

    
    cdb recursive-factorial1.exe

    
    Microsoft (R) Windows Debugger Version 6.8.0004.0 X86
    Copyright (c) Microsoft Corporation. All rights reserved.
    
    CommandLine: recursive-factorial1.exe
    Symbol search path is: SRV*C:\Symbols*\\symbolserver\OSSYMBOLS
    Executable search path is:
    ModLoad: 00400000 0041e000   recursive-factorial1.exe
    ModLoad: 7c900000 7c9b0000   ntdll.dll
    ModLoad: 7c800000 7c8f5000   C:\WINDOWS\system32\kernel32.dll
    (594.700): Break instruction exception - code 80000003 (first chance)
    eax=00241eb4 ebx=7ffdb000 ecx=00000000 edx=00000001 esi=00241f48 edi=00241eb4
    eip=7c901230 esp=0012fb20 ebp=0012fc94 iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    ntdll!DbgBreakPoint:
    7c901230 cc              int     3
    0:000> bp factorial
    *** WARNING: Unable to verify checksum for recursive-factorial1.exe
    0:000> l+*
      WARNING: Line information loading disabled
    Source options are ffffffff:
         1/t - Step/trace by source line
         2/l - List source line at prompt
         4/s - List source code at prompt
         8/o - Only show source code at prompt
    0:000> g
    Breakpoint 0 hit
    >    2: {
    0:000> p
    >    3:         if (n > 1)
    0:000>
    >    4:                 return factorial(n - 1) * n;
    0:000>
    Breakpoint 0 hit
    >    2: {
    0:000>
    >    3:         if (n > 1)
    0:000>
    >    4:                 return factorial(n - 1) * n;
    0:000>
    Breakpoint 0 hit
    >    2: {
    0:000>
    >    3:         if (n > 1)
    0:000>
    >    4:                 return factorial(n - 1) * n;
    0:000>
    Breakpoint 0 hit
    >    2: {
    0:000>
    >    3:         if (n > 1)
    0:000>
    >    4:                 return factorial(n - 1) * n;
    0:000>
    Breakpoint 0 hit
    >    2: {
    0:000>
    >    3:         if (n > 1)
    0:000>
    >    4:                 return factorial(n - 1) * n;
    0:000>
    Breakpoint 0 hit
    >    2: {
    0:000>
    >    3:         if (n > 1)
    0:000> k
    ChildEBP RetAddr
    0012ff28 00401035 recursive_factorial1!factorial+0x3
    0012ff34 00401035 recursive_factorial1!factorial+0x15
    0012ff40 00401035 recursive_factorial1!factorial+0x15
    0012ff4c 00401035 recursive_factorial1!factorial+0x15
    0012ff58 00401035 recursive_factorial1!factorial+0x15
    0012ff64 0040105d recursive_factorial1!factorial+0x15
    0012ff70 00401268 recursive_factorial1!main+0xd
    0012ffc0 7c816fd7 recursive_factorial1!__tmainCRTStartup+0x15f
    0012fff0 00000000 kernel32!BaseProcessStart+0x23
    0:000>

Ou seja, conforme chamamos a função recursivamente, a pilha tende a crescer. Agora imagine todo o _overhead_ da execução, que precisa, a cada chamada, gerar um _stack frame_.

A mesma coisa podemos notar se compilarmos o mesmo fonte no GCC e depurarmos pelo GDB. Aliás, a primeira participação especial do GDB nesse blogue =)

    
    $ gcc -g recursive-factorial1.c
    $ gdb a.exe
    GNU gdb 6.5.50.20060706-cvs (cygwin-special)
    Copyright (C) 2006 Free Software Foundation, Inc.
    GDB is free software, covered by the GNU General Public License, and you are
    welcome to change it and/or distribute copies of it under certain conditions.
    Type "show copying" to see the conditions.
    There is absolutely no warranty for GDB.  Type "show warranty" for details.
    This GDB was configured as "i686-pc-cygwin"...
    (gdb) break factorial
    Breakpoint 1 at 0x401056: file recursive-factorial1.c, line 3.
    (gdb) run
    Starting program: /cygdrive/c/temp/a.exe
    Loaded symbols for /cygdrive/c/WINDOWS/system32/ntdll.dll
    Loaded symbols for /cygdrive/c/WINDOWS/system32/kernel32.dll
    Loaded symbols for /usr/bin/cygwin1.dll
    Loaded symbols for /cygdrive/c/WINDOWS/system32/advapi32.dll
    Loaded symbols for /cygdrive/c/WINDOWS/system32/rpcrt4.dll
    Breakpoint 1, factorial (n=1000) at recursive-factorial1.c:3
    3               if (n > 1)
    (gdb) step
    4                       return factorial(n - 1) * n;
    (gdb)
    
    Breakpoint 1, factorial (n=999) at recursive-factorial1.c:3
    3               if (n > 1)
    (gdb)
    4                       return factorial(n - 1) * n;
    (gdb)
    
    Breakpoint 1, factorial (n=998) at recursive-factorial1.c:3
    3               if (n > 1)
    (gdb)
    4                       return factorial(n - 1) * n;
    (gdb)
    
    Breakpoint 1, factorial (n=997) at recursive-factorial1.c:3
    3               if (n > 1)
    (gdb)
    4                       return factorial(n - 1) * n;
    (gdb)
    
    Breakpoint 1, factorial (n=996) at recursive-factorial1.c:3
    3               if (n > 1)
    (gdb)
    4                       return factorial(n - 1) * n;
    (gdb)
    
    Breakpoint 1, factorial (n=995) at recursive-factorial1.c:3
    3               if (n > 1)
    (gdb)
    4                       return factorial(n - 1) * n;
    (gdb)
    
    Breakpoint 1, factorial (n=994) at recursive-factorial1.c:3
    3               if (n > 1)
    (gdb)
    4                       return factorial(n - 1) * n;
    (gdb)
    
    Breakpoint 1, factorial (n=993) at recursive-factorial1.c:3
    3               if (n > 1)
    (gdb)
    4                       return factorial(n - 1) * n;
    (gdb) backtrace
    #0  factorial (n=993) at recursive-factorial1.c:4
    #1  0x00401068 in factorial (n=994) at recursive-factorial1.c:4
    #2  0x00401068 in factorial (n=995) at recursive-factorial1.c:4
    #3  0x00401068 in factorial (n=996) at recursive-factorial1.c:4
    #4  0x00401068 in factorial (n=997) at recursive-factorial1.c:4
    #5  0x00401068 in factorial (n=998) at recursive-factorial1.c:4
    #6  0x00401068 in factorial (n=999) at recursive-factorial1.c:4
    #7  0x00401068 in factorial (n=1000) at recursive-factorial1.c:4
    #8  0x004010b3 in main () at recursive-factorial1.c:11
    (gdb)

#### Recursividade barata

Isso acontece porque o compilador é obrigado a montar um novo _stack frame_ para cada chamada da mesma função, já que os valores locais precisam manter-se intactos até o retorno recursivo da função. Porém, existe uma otimização chamada de _tail recursion_, que ocorre se, e somente se (de acordo com meu livro):

    
  * A chamada recursiva é a última instrução que será executada no corpo da função.

    
  * O valor de retorno da chamada não é parte de uma expressão.

Note que ser a última instrução não implica em ser a última linha da função, o importante é que seja a última linha **executada**. No nosso exemplo, isso já é fato, só que usamos o retorno em uma expressão.

    
```cpp
    return factorial(n - 1) * n;
    // o retorno da chamada recursiva 
    // é parte de uma expressão
```


Por isso é necessário desenvolver uma segunda versão do código, que utiliza dois parâmetros para que aconteça a situação de _tail recursion_.

```c
int factorial(int n, int a)
{
	if (n < 0)
		return 0;
	else if (n == 0)
		return 1;
	else if (n == 1)
		return a;
	else
		return factorial(n - 1, n * a);
}

int main()
{
	return factorial(1000, 1);
}
 

```

Nessa segunda versão, a chamada da função recursiva não mais é parte de uma expressão, e continua sendo a última instrução executada. Agora só temos que compilar com a opção de otimização certa em ambos os compiladores e testar.

Para o Visual Studio, podemos usar a flag /Og (otimização global).

    
    cl /Zi /Og recursive-factorial2.c

    
    cdb recursive-factorial2.exe

    
    ...
    bp factorial
    g
    ...
    Breakpoint 0 hit
    eax=003235f0 ebx=7c80abc1 ecx=00000001 edx=0041c560 esi=00000002 edi=00000a28
    eip=00401020 esp=0012ff68 ebp=0012ffc0 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    recursive_factorial2!factorial:
    00401020 55              push    ebp
    0:000> l+*
      WARNING: Line information loading disabled
    Source options are ffffffff:
         1/t - Step/trace by source line
         2/l - List source line at prompt
         4/s - List source code at prompt
         8/o - Only show source code at prompt
    0:000> p
    >    3:         if (n < 0)
    0:000>
    >    5:         else if (n == 0)
    0:000>
    >    7:         else if (n == 1)
    0:000>
    >   10:                 return factorial(n - 1, n * a);
    0:000>
    >    5:         else if (n == 0)
    0:000>
    >    7:         else if (n == 1)
    0:000>
    >   10:                 return factorial(n - 1, n * a);
    0:000>
    >    5:         else if (n == 0)
    0:000>
    >    7:         else if (n == 1)
    0:000>
    >   10:                 return factorial(n - 1, n * a);
    0:000>
    >    5:         else if (n == 0)
    0:000>
    >    7:         else if (n == 1)
    0:000>
    >   10:                 return factorial(n - 1, n * a);
    0:000>
    >    5:         else if (n == 0)
    0:000>
    >    7:         else if (n == 1)
    0:000>
    >   10:                 return factorial(n - 1, n * a);
    0:000>
    >    5:         else if (n == 0)
    0:000>
    >    7:         else if (n == 1)
    0:000>
    >   10:                 return factorial(n - 1, n * a);
    0:000>
    >    5:         else if (n == 0)
    0:000>
    >    7:         else if (n == 1)
    0:000>
    >   10:                 return factorial(n - 1, n * a);
    0:000>
    >    5:         else if (n == 0)
    0:000>
    >    7:         else if (n == 1)
    0:000>
    >   10:                 return factorial(n - 1, n * a);
    0:000>
    >    5:         else if (n == 0)
    0:000>
    >    7:         else if (n == 1)
    0:000>
    >   10:                 return factorial(n - 1, n * a);
    0:000>
    >    5:         else if (n == 0)
    0:000> k
    ChildEBP RetAddr
    0012ff64 0040105c recursive_factorial2!factorial+0x10
    0012ff70 00401266 recursive_factorial2!main+0xc
    0012ffc0 7c816fd7 recursive_factorial2!__tmainCRTStartup+0x15f
    0012fff0 00000000 kernel32!BaseProcessStart+0x23
    0:000>

Como podemos ver, após n chamadas, a pilha continua apenas com uma chamada a factorial.

Para o GCC, a opção é mais explítica, e funciona da mesma forma.

    
    $ gcc -g -foptimize-sibling-calls  recursive-factorial2.c

    
    $ gdb a.exe
    ...
    (gdb) break factorial
    ...
    (gdb) run
    
    ...
    Breakpoint 1, factorial (n=1000, a=0) at recursive-factorial2.c:3
    3               if (n < 0)
    
    (gdb) step
    5               else if (n == 0)
    (gdb)
    7               else if (n == 1)
    (gdb)
    10                      return factorial(n - 1, n * a);
    (gdb)
    11      }
    (gdb)
    factorial (n=1, a=6695656) at recursive-factorial2.c:10
    10                      return factorial(n - 1, n * a);
    (gdb)
    factorial (n=999, a=0) at recursive-factorial2.c:2
    2       {
    (gdb)
    
    Breakpoint 1, factorial (n=999, a=0) at recursive-factorial2.c:3
    3               if (n < 0)
    (gdb)
    5               else if (n == 0)
    (gdb)
    7               else if (n == 1)
    (gdb)
    10                      return factorial(n - 1, n * a);
    (gdb)
    11      }
    (gdb)
    factorial (n=1, a=6695656) at recursive-factorial2.c:10
    10                      return factorial(n - 1, n * a);
    (gdb)
    factorial (n=998, a=0) at recursive-factorial2.c:2
    2       {
    (gdb)
    
    Breakpoint 1, factorial (n=998, a=0) at recursive-factorial2.c:3
    3               if (n < 0)
    (gdb)
    5               else if (n == 0)
    (gdb)
    7               else if (n == 1)
    (gdb)
    10                      return factorial(n - 1, n * a);
    (gdb)
    11      }
    (gdb)
    factorial (n=1, a=6695656) at recursive-factorial2.c:10
    10                      return factorial(n - 1, n * a);
    (gdb)
    factorial (n=997, a=0) at recursive-factorial2.c:2
    2       {
    (gdb)
    
    Breakpoint 1, factorial (n=997, a=0) at recursive-factorial2.c:3
    3               if (n < 0)
    (gdb)
    5               else if (n == 0)
    (gdb)
    7               else if (n == 1)
    (gdb)
    10                      return factorial(n - 1, n * a);
    (gdb)
    11      }
    (gdb)
    factorial (n=1, a=6695656) at recursive-factorial2.c:10
    10                      return factorial(n - 1, n * a);
    (gdb)
    factorial (n=996, a=0) at recursive-factorial2.c:2
    2       {
    (gdb)
    
    Breakpoint 1, factorial (n=996, a=0) at recursive-factorial2.c:3
    3               if (n < 0)
    (gdb)
    5               else if (n == 0)
    (gdb)
    7               else if (n == 1)
    (gdb)
    10                      return factorial(n - 1, n * a);
    (gdb)
    11      }
    (gdb)
    factorial (n=1, a=6695656) at recursive-factorial2.c:10
    10                      return factorial(n - 1, n * a);
    (gdb) backtrace
    #0  factorial (n=1, a=6695656) at recursive-factorial2.c:10
    #1  0x61006198 in dll_crt0_1 () from /usr/bin/cygwin1.dll
    #2  0x61004416 in _cygtls::call2 () from /usr/bin/cygwin1.dll
    #3  0x00000000 in ?? ()
    (gdb)

Voilà!
