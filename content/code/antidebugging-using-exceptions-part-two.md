---
date: "2008-07-30"
title: Antidebugging using exceptions (part two)
categories: [ "code" ]
---
In the first article we saw how it's possible to spoof the debugger through exceptions and let the attacker lose some considerable time trying to unbind the program from the fake breakpoints. However, we saw also that this is a difficult solution to keep in the source code, besides its main weakness to be easily bypassed if discovered. Now it's time to put things easier to support and at the same time to guarantee tough times even if the attacker discover what is going on.

The upgrade showed here still uses the exception throwing intrinsically, but now it doesn't depends on the code division in minifunctions and minicalls. Instead, we just need to get code traces and put them inside a miraculous macro that will do everything we want. This, of course, after some "hammer work" that will be explained here.

```cpp
// Go back to place pre-defined by the restoration point.
void LongJmp(restorePoint)
{
	// Here we will generate an exception to make things difficult.
	// @todo Make a breakpoint exception and catch it.

	// 3. We return to the if without using the stack, but from the restoration point.
	GoBackToTheStartFunction(restorePoint);
}

// Here everything begins.
int Start()
{
	// Obs.: follow the agreement flow according to the numbers.

	// 1. First pass: we define a restoration point to the return of LongJmp.
	// 4. Second pass: we go back from the LongJmp function, but this time we get into the else.
	if( RestorePointDefined() == Defined )
	{
		// 2. We call the function that will return to the if.
		LongJmp( if );
	}
	else
	{
		// 5. Call the real function, our true target.
		CallTheUsefulFunction();
	}

	// 6. End of execution.
	return 0;
} 

```

The solution above is explained in pseudocode to make things clearer. Notice that exist some kind of invisible return, not stack based. To handle it, however, we can use the good for all C ANSI standard, using the setjmp (step one) and longjmp (step 3). To understand the implementation for theses functions running on the 8086 platform we need to get the basic vision of the function calls in a stack based environment (the C and Pascal way).

#### Registers, stack frame and call/ret

Registers are reserved variables in the processor that can be used by the assembly code. Stack frame is the function calling hierarchy, the "who called who" in a given execution state. Call and ret are assembly instructions to call and return from a function, respectively. Both change the stack frame.

Imagine you have a function, CallFunc, and another function, Func, and one calls the other. In order to analyse just the function call, and just that, let's consider Func doesn't receive any argument and doesn't return any value. The C code, would be like bellow:

    
    void Func()
    {
       return;
    }

    
    void CallFunc()
    {
       Func();
    }

Simple, huh? Being simple, the generated assembly will be simple as well. In CallFunc it should have the function call, and inside Func the return from the call. The rest of the code is related with Debug version stuff.

    
    Func:
    00411F73 prev_instruction ; ESP = 0012FD38 (four bytes stacked up)
    00411F74 ret ; *ESP = 00411FA3 (return address)

    
    CallFunc:
    00411F9C prev_instruction
    00411F9E call Func (411424h) ; ESP = 0012FD3C
    00411FA3 next_instruction

From the assembly above we can conclude two things: 1. The stack grows down, since its value decremented four bytes (0012FD3C minus 0012FD38 equal four) and 2. The return value from the calling is the address of the very next instruction after the call instruction, in the case 00411FA3.

Well, in the same way we can follow this simple execution, the attacker will do as well. That's why in the middle of this call we will throw an exception and, in the return, we will not do the return in the conventional way, but using another technique that, instead using the ret instruction, sets manually the esp value (stack state) and jumps to the next instruction in CallFunc.

    
    Func:
    00411F60 throw_exception
    00411F61 ...
    00411F73 catch_exception
    00411F74 mov ESP, 0012FD3C ; ESP = 0012FD3C, just like CallFunc
    00411F75 jmp 00411FA3 ; jumps to CallFunc::next_instruction

#### Back to the Middle Earth

All this assembly stuff doesn't need to be written in assembly level. It was just a way I found to illustrate the differences between the stack return and the jump return. As it was said, to the luck and well being for all, this same technique can be implemented using ANSI C functions:

```cpp
jmp_buf env; // Contains the next instruction (stack state).

void Func()
{
	// 3. Return using the "nonconventional" way
	longjmp(env, 1);
}

void CallFunc()
{
	// 1. If we're setting, returns 0.
	// 2. If we're returning, returns a value different from 0.
	if( setjmp(env) == 0 )
		Func();

	int x = 10; // 4. Next instruction.
} 

```

That was the new trick for the trowing of exceptions. The final code is clearer, now:

```cpp
/** The only purpose of this function is to generate an exception.
*/
DWORD LongJmp(jmp_buf* env)
{
	__try
	{
		__asm int 3
	}
		__except( EXCEPTION_EXECUTE_HANDLER )
	{
		longjmp(*env, 1);
	}

	return ERROR_SUCCESS;
}

/** And God said: 'int main!'
*/
int main()
{
	DWORD ret = ERROR_SUCCESS;

	while( cin )
	{
		string line;

		cout << "Type something\n";
		getline(cin, line);

		jmp_buf env;

		if( setjmp(env) == 0 )
		{
			LongJmp(&env);
		}
		else
		{
			cout << line << endl;
		}
	}

	return (int) ret;
} 

```

At first sight, it seems a waste the if being directly in the code (remember we gonna use the same conditional structure in several parts in the code). To turn things clearer, resume the protected call and allows the protection to be disabled in debug version code, let's create a macro:

```cpp
/** Use this macro instead LongJmp
*/
#define ANTIDEBUG(code)
{
	jmp_buf env;

	if( setjmp(env) == 0 )
	{
		LongJmp(&env);
	}
	else
	{
		code;
	}
}

/** And God said: 'int main!'
*/
int main()
{
	DWORD ret = ERROR_SUCCESS;

	while( cin )
	{
		string line;

		cout << "Type something\n";
		getline(cin, line);

		ANTIDEBUG(( cout << line << endl ));
	}

	return (int) ret;
} 

```

Now we allow the antidebugging selection by call, what turns things much easier than to choose the protected points inside the code.
