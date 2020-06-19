---
categories: [ "code" ]
date: "2008-07-30"
tags: [ "draft",  ]
title: "Antidebugging using exceptions (part two)"
---
In the first article we saw how it's possible to spoof the debugger through exceptions and let the attacker lose some considerable time trying to unbind the program from the fake breakpoints. However, we saw also that this is a difficult solution to keep in the source code, besides its main weakness to be easily bypassed if discovered. Now it's time to put things easier to support and at the same time to guarantee tough times even if the attacker discover what is going on.

The upgrade showed here still uses the exception throwing intrinsically, but now it doesn't depends on the code division in minifunctions and minicalls. Instead, we just need to get code traces and put them inside a miraculous macro that will do everything we want. This, of course, after some "hammer work" that will be explained here.


The solution above is explained in pseudocode to make things clearer. Notice that exist some kind of invisible return, not stack based. To handle it, however, we can use the good for all C ANSI standard, using the setjmp (step one) and longjmp (step 3). To understand the implementation for theses functions running on the 8086 platform we need to get the basic vision of the function calls in a stack based environment (the C and Pascal way).

Registers are reserved variables in the processor that can be used by the assembly code. Stack frame is the function calling hierarchy, the "who called who" in a given execution state. Call and ret are assembly instructions to call and return from a function, respectively. Both change the stack frame.

Imagine you have a function, CallFunc, and another function, Func, and one calls the other. In order to analyse just the function call, and just that, let's consider Func doesn't receive any argument and doesn't return any value. The C code, would be like bellow:



Simple, huh? Being simple, the generated assembly will be simple as well. In CallFunc it should have the function call, and inside Func the return from the call. The rest of the code is related with Debug version stuff.



From the assembly above we can conclude two things: 1. The stack grows down, since its value decremented four bytes (0012FD3C minus 0012FD38 equal four) and 2. The return value from the calling is the address of the very next instruction after the call instruction, in the case 00411FA3.

Well, in the same way we can follow this simple execution, the attacker will do as well. That's why in the middle of this call we will throw an exception and, in the return, we will not do the return in the conventional way, but using another technique that, instead using the ret instruction, sets manually the esp value (stack state) and jumps to the next instruction in CallFunc.


All this assembly stuff doesn't need to be written in assembly level. It was just a way I found to illustrate the differences between the stack return and the jump return. As it was said, to the luck and well being for all, this same technique can be implemented using ANSI C functions:


That was the new trick for the trowing of exceptions. The final code is clearer, now:


At first sight, it seems a waste the if being directly in the code (remember we gonna use the same conditional structure in several parts in the code). To turn things clearer, resume the protected call and allows the protection to be disabled in debug version code, let's create a macro:


Now we allow the antidebugging selection by call, what turns things much easier than to choose the protected points inside the code.
