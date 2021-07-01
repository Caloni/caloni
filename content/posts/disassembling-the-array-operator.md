---
categories:
- code
- english
- blog
date: '2007-06-22'
tags:
- ccpp
- home
title: Disassembling the array operator
---

Arrays are fascinating in C language because they are so simple and so powerful at the same time. When we start to really understand them and realize all its power we are very close to understand another awesome feature of the language: pointers.

When I was reading the K&R book (again) I was enjoying the language specification details in the Appendix A. It was specially odd the description as an array must be accessed:

> A postfix expression followed by an expression in square brackets is a postfix expression. One of the expressions shall have the type "pointer to T" and the other shall have enumeration or integral type. The result is an lvalue of type "T". (...) The expression E1 [ E2 ] is identical (by definition) to *( (E1) + (E2) ).

Notice that the rules don't specify the order of expressions to access the array. In other words, it doesn't matter for the language if we use a pointer before the integer or an integer before the pointer.

    #include <iostream>
    #include <cassert>
    
    int main()
    {
    	char q[] = "Show me your Code, "
        "and I'll tell you who you are.";
    	int i = 13;
    	
    	std::cout 
        << "And the language is: " 
        << q [ i ] 
        << std::endl;
    	
    	assert( q[i] == i[q] );
    	assert( q[13] == 13[q] );
    	assert( *(q + i) == "That's C!"[7] );
    	
    	return 13[q] - "CThings"[0];
    } 

The q[i] bellow shows that we can use both orders and the code will compile successfully.

    std::cout 
      << "And the language is: " 
      << i [ q ] 
      << std::endl;

This code doesn't show how obscure we can be. If we use a constant integer replacing the i, by example, the code starts to be an [IOCCC] participant:

    std::cout 
      << "And the language is: " 
      << 13 [ q ] 
      << std::endl;

Is this a valid code yet, right? The expression types are following the rule. It is easy to see if we always think about using the "universal match" *( (E1) + (E2) ). Even bizarre things like this are easy to realize:

    std::cout 
      << 8["Is this Code right?"] 
      << std::endl;

Obs.: this kind of "obscure rule" hardly will pass in a code review since it is a useless feature. Be wise and don't use it in production code. This is just an amusing detail in the language specification scope. It can help in analysis, never in programming.

[IOCCC]: http://www.ioccc.org/