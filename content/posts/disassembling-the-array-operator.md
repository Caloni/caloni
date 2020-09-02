---
date: "2007-06-22"
tags: [ "code", "draft",  ]
title: "Disassembling the array operator"
---
Arrays are fascinating in C language because they are so simple and so powerful at the same time. When we start to really understand them and realize all its power we are very close to understand another awesome feature of the language: pointers.

When I was reading the K&R book (again) I was enjoying the language specification details in the Appendix A. It was specially odd the description as an array must be accessed:

A postfix expression followed by an expression in square brackets is a postfix expression. One of the expressions shall have the type "pointer to T" and the other shall have enumeration or integral type. The result is an lvalue of type "T". (...) The expression E1 [ E2 ] is identical (by definition) to *( (E1) + (E2) ).

Notice that the rules don't specify the order of expressions to access the array. In other words, it doesn't matter for the language if we use a pointer before the integer or an integer before the pointer.


The quote[index] bellow shows that we can use both orders and the code will compile successfully.


This code doesn't show how obscure we can be. If we use a constant integer replacing the index, by example, the code starts to be an IOCCC participant:


Is this a valid code yet, right? The expression types are following the rule. It is easy to see if we always think about using the "universal match" *( (E1) + (E2) ). Even bizarre things like this are easy to realize:


Obs.: this kind of "obscure rule" hardly will pass in a code review since it is a useless feature. Be wise and don't use it in production code. This is just an amusing detail in the language specification scope. It can help in analysis, never in programming.
