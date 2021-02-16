---
date: "2007-06-22"
title: Disassembling the array operator
tags: [ "draft", "code" ]
---
Arrays are fascinating in C language because they are so simple and so powerful at the same time. When we start to really understand them and realize all its power we are very close to understand another awesome feature of the language: **pointers**.

When I was reading the [K&R](http://www.amazon.com/C-Programming-Language-2nd/dp/0131103628) book (again) I was enjoying the language specification details in the **Appendix A**. It was specially odd the description as an array must be accessed:

<blockquote>_A postfix expression followed by an expression in square brackets is a postfix expression. One of the expressions shall have the type "pointer to T" and the other shall have enumeration or integral type. The result is an lvalue of type "T". (...) The expression E1 [ E2 ] is identical (by definition) to *( (E1) + (E2) )._</blockquote>

Notice that the rules don't specify the order of expressions to access the array. In other words, it doesn't matter for the language if we use a **pointer before the integer or an integer before the pointer**.

```cpp
#include <iostream>
#include <cassert>

int main()
{
	char quote[] = "Show me your Code, and I'll tell you who you are.";
	int index = 13;
	
	std::cout << "And the language is: " << quote [ index ] << std::endl;
	
	assert( quote[index] == index[quote] );
	assert( quote[13] == 13[quote] );
	assert( *(quote + index) == "That's C!"[7] );
	
	return 13[quote] - "CThings"[0];
} 

```

The quote[index] bellow shows that we can use both orders and the code will compile successfully ([try it](/images/2007/06/disassembling-array.cpp)!).

_**std::cout << "And the language is: " << index [ quote ] << std::endl;**_

This code doesn't show how obscure we can be. If we use a **constant integer** replacing the index, by example, the code starts to be an [IOCCC](http://www.ioccc.org/) participant:

_**std::cout << "And the language is: " << 13 [ quote ] << std::endl;**_

Is this a valid code yet, right? The expression types are following the rule. It is easy to see if we always think about using the "universal match" ***( (E1) + (E2) )**. Even bizarre things like this are easy to realize:

_**std::cout << 8["Is this Code right?"] << std::endl;**_

_Obs.: this kind of "obscure rule" hardly will pass in a code review since it is a **useless feature**. Be wise and **don't use it in production code**. This is just an amusing detail in the language specification scope. It can help in analysis, never in programming._
