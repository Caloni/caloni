---
categories: [ "code" ]
date: "2007-07-10"
tags: [ "draft",  ]
title: "Precedence difference"
---
Once upon a time my old friend Kabloc wrote this little and "harmless" function in order to print the multiplication table:


Despite the fact the result is a strong candidate to "The International Obfuscated C Code Contest", the linux guys told him the code was not successful on GCC, and somewhere inside those four lines there was a non-standard piece of code.

Asked to solve the problem, given my congenital inclination to random subjects involving C++, I decided to fix the things up in my old-n-good Visual Studio 2003. Nonetheless, it compiles C source code as well. We just need to rename the file from .cpp to .c. It was doing this that I found the following compiler error:


That happens in the line 6, the first for line. In other words, a C source that compiles as C++ but gives us a lack of l-value error since compiled as pure C.

Thinking about the problem rather intuitively than rationally I imagined that could be some little difference in the precedence table. Keeping that in mind, wrested the standard papers for both languages and took a look at the precedence tables.

| Precedence | Operator | Description | Associativity |
| ---------- | -------- | ----------- | ------------- |
| 1 | ++ -- | Suffix/postfix increment and decrement | Left-to-right |
| () | Function call |
| [] | Array subscripting |
| . | Structure and union member access |
| -> | Structure and union member access through pointer |
| (type){list} | Compound literal(C99) |
| 2 | ++ -- | Prefix increment and decrement[note 1] | Right-to-left |
| + - | Unary plus and minus |
| ! ~ | Logical NOT and bitwise NOT |
| (type) | Cast |
| * | Indirection (dereference) |
| & | Address-of |
| sizeof | Size-of[note 2] |
| _Alignof | Alignment requirement(C11) |
| 3 | * / % | Multiplication, division, and remainder | Left-to-right |
| 4 | + - | Addition and subtraction |
| 5 | << >> | Bitwise left shift and right shift |
| 6 | < <= | For relational operators < and ≤ respectively |
| > >= | For relational operators > and ≥ respectively |
| 7 | == != | For relational = and ≠ respectively |
| 8 | & | Bitwise AND |
| 9 | ^ | Bitwise XOR (exclusive or) |
| 10 | | | Bitwise OR (inclusive or) |
| 11 | && | Logical AND |
| 12 | || | Logical OR |
| 13 | ?: | Ternary conditional[note 3] | Right-to-Left |
| 14[note 4] | = | Simple assignment |
| += -= | Assignment by sum and difference |
| *= /= %= | Assignment by product, quotient, and remainder |
| <<= >>= | Assignment by bitwise left shift and right shift |
| &= ^= |= | Assignment by bitwise AND, XOR, and OR |
| 15 | , | Comma | Left-to-right |

Besides some now less important details, we can notice at the end of the table a inversion between the ternary operator and the attribution operator and, more importantly, the inversion of the evaluation order. In C, the ternary operator is evaluated from right to left, whilst in C++ from left to right, like the rest. This is going to shows us that, in line 6, the same expression has two different interpretations in each language.

In order to understand bit by bit the problem, let's disassemble the second part of that for:


We have two ternary operators nestled. In accordance with C++ standard, the ternary operators have less precedence than the attribution operators and are evaluated from left to right. In other words, in first place all the atributions inside the expression are made before any ternary operator. After that, the first ternary operator is executed, followed by the second:


The parts in red are the first ones to run, followed by the green ones and, finally, by the blue ones. This color priority is completely arbitrary. Of course, the colors you see in your text editor doesn't have anything to do with this explanation.

Now let't take a look in C. In this language, different from C++, the ternary operators have more precedence than the attribution operators, and are executed from right to left. That means the first and last ternary operators are executed, ignoring the right attribution, and after that the first ternary operator is executed. Only after these two events the right attribution is evaluated:


All this make us to see the attribution to 12 will be done on the first ternary operator result, which possible values could be from the putchar return or f1. Remember about the comma operator purpose outside function calls: chain expressions, execute them and return the value from the rightmost expression:


Well, the f1 variable is an integer. And putchar return as well. This is not going to break any type rule. However, breaks the attribution gold rule: "put an lvalue in the right side of an attribution".


This finishes the long explanation about why that little insignificant error at the beginning of this article happened only in the C language. This is a perfect example of the little differences between these two languages. Perhaps do you use parenthesis like a crazy, and are not going to find this kind of problems inside your source code. Perhaps not.
