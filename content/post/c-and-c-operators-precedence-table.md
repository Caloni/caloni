---
categories: [ "code" ]
date: "2007-07-30"
tags: [ "draft",  ]
title: "C and C++ Operators Precedence Table"
---
> Wanderley, your explanation about why a program compiles in C++ and not in C seems to me logic and correct, but gave me some doubts, because I always learned that the C and C++ operator precedence are the same thing. I checked out the Appendix A in the "C ++ - How To Program" (sixth edition) and the book table is equal to the C operators precedence table and it is different from the C++ precedence table presented by you in the article. I went to the internet and found out in two websites the table and both are equal to the book table.
>
> http://en.wikipedia.org/wiki/OperatorsinCandC
>
> http://www.cppreference.com/operatorprecedence.html
> 
> From where did you get the presented C++ table?
>
> []s,
> 
> Márcio Andrey Oliveira

Dear Márcio,

You have been my most productive reader ever. Besides having found the portability fail using static variables inside ifs, now you put in check the precedence table comparison between these two languages. In fact, some things were not so clear in that post. Let's clarify everything now (or at least try) using trustworthy sources, including the Wikipedia link sent to me.

The first doubt it's about the most basic principle: what is a precedence table? Well, it is who defines, amount a set of concurrent operations in a language, which will be the evaluation order. In other words, who cames first, who cames next, etc. Through this table is possible to know all the language facts, as the fact that the multiplication operators are evaluated before the addition operators.

This way, the table can resolve 99% of the evaluation order issues in a language, but it is not perfect.

Let's see, by example, the conditional operator, most of the times known by ternary operator. Given its peculiar format, even having the precedence lower than the comma operator, the language doesn't allow a misinterpretation. If so,


will be interpreted as


and not as


that would be the logic result if we followed the precedence table, since the comma operator has lower precedence than the ternary operator. But that doesn't make any sense in the language, and that's why the first form is understood by the compiler, even contradicting the precedence table. This is corroborated by the following quote from Wikipedia:

> A precedence table, while mostly adequate, cannot resolve a few details. In particular, note that the ternary operator allows any arbitrary expression as its middle operand, despite being listed as having higher precedence than the assignment and comma operators.

That is one of the reasons why the precedence table is just a way to express the grammar rules of a language in a simple and resumed manner. It is not the grammar neither ought to be. Let's see one more quotation, this time from the Stroustrup himself, just after presented the C++ precedence table (by the way, that was the source used by me to get the table for my post):

> A few grammar rules cannot be expressed in terms of precedence (also known as binding strength) and associativity.

We can see from my example, the Wikipedia example and the Stroustrup example that the ternary operator is the main victim. Not for less. Talking about the grammar, the C ternary operator definition is different from the C++ ternary operator definition. While in C this operator is defined like this:


In C++ language it is defined like this:


This little difference can give us some (rare) situations where we can get a syntax error in C. As in a Wikipedia example , the following expression:


is interpreted by the C language as:


In the C++ language is interpreted as:


In the C language case, we have a compilation error because the code is trying to assign a value to a lvalue (remember that lvalues can't be assigned to anything).


But in C++ there's no invalid assignment, what makes a no error compilation performed.

Now, one last question, that seems to be the most relevant in this precedence issue:

Why is the Stroustrup book precedence table different from the C precedence table?  Well, I believe that, after all our analysis, the answer must be somewhat obvious: knowing that, in the ternary operator, the third operand is an assignment-expression, it is most likely the table is agree with the grammar if we put a extra weight for the assignment operators before the ternary operator. This way, if the third operand is an assignment operation (as the case above), the imaginary parentesis will be put first in the assignment operation, making the grammar definition valid (green is in C++; red is in C):


I hope this second post about the precedence table have cleared a bit more about the subject. Is not easy to understand the C language, but once you start to try, one magic door opens. Some things to remember from this experience:

  * The precedence table is not in the Standard; it is deduced from the grammar rules.
  * There are rare expressions where we can't use the precedence table (e.g. ternary operator).
  * Nobody knows so well a language to the point to understand 100% from it; after all, nobody (and nothing) is perfect.

