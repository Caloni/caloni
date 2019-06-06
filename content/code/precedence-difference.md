---
date: "2007-07-10"
title: Precedence difference
categories: [ "code" ]
---
Once upon a time my old friend [Kabloc](http://www.kabloc.com.br) wrote this little and "harmless" function in order to print the multiplication table:

```cpp
#include <stdio.h>

int main()
{
	int f1,f2,s=0;
	   for(f1=1;(f1==11&&s!=5)?s=5,f1=0,putchar(10):(f1<=10)?f1=f1:f1=12,f1<=11;f1++)
			for(f2=1+s;f2<=5+s;f2++)printf("%dx%d=%d%c",f2,f1,f1*f2,(f2==5+s)?10:9);
	return 0;
} 

```

Despite the fact the result is a strong candidate to "[The International Obfuscated C Code Contest](http://www.ioccc.org)", the linux guys told him the code was not successful on GCC, and somewhere inside those four lines there was a non-standard piece of code.

Asked to solve the problem, given my congenital inclination to [random subjects involving C++](http://www.caloni.com.br/disassembling-the-array-operator), I decided to fix the things up in my old-n-good **Visual Studio 2003**. Nonetheless, it compiles C source code as well. We just need to rename the file from **.cpp** to **.c**. It was doing this that I found the following compiler error:

**_error C2106: '=' : left operand must be l-value_**

That happens in the line 6, the first **for** line. In other words, a C source that compiles as C++ but gives us a lack of l-value error since compiled as pure C.

Thinking about the problem rather intuitively than rationally I imagined that could be some little difference in the precedence table. Keeping that in mind, wrested the standard papers for both languages and took a look at the precedence tables:

<table width="80%" cellspacing="1" border="1" >
<tbody >
<tr >

<td colspan="2" align="center" >**c**
</td>

<td colspan="2" align="center" >**c++**
</td>
</tr>
<tr >

<td >**Operators**
</td>

<td align="center" >**Associativity **
</td>

<td align="center" >**Operators**
</td>

<td align="center" >**Associativity**
</td>
</tr>
<tr >

<td >() [] -> .
</td>

<td >left to right
</td>

<td >() [] -> . etc
</td>

<td >left to right
</td>
</tr>
<tr >

<td >! ~ ++ -- etc
</td>

<td >right to left
</td>

<td >! ~ ++ -- etc
</td>

<td >right to left
</td>
</tr>
<tr >

<td >* / % 
</td>

<td >left to right
</td>

<td >* / %
</td>

<td >left to right
</td>
</tr>
<tr >

<td >+ - 
</td>

<td >left to right
</td>

<td >+ -
</td>

<td >left to right
</td>
</tr>
<tr >

<td ><< >>
</td>

<td >left to right
</td>

<td ><< >>
</td>

<td >left to right
</td>
</tr>
<tr >

<td >< <= > >= 
</td>

<td >left to right
</td>

<td >< <= > >=
</td>

<td >left to right
</td>
</tr>
<tr >

<td >== != 
</td>

<td >left to right
</td>

<td >== !=
</td>

<td >left to right
</td>
</tr>
<tr >

<td >&
</td>

<td >left to right
</td>

<td >&
</td>

<td >left to right
</td>
</tr>
<tr >

<td >^ 
</td>

<td >left to right
</td>

<td >^ 
</td>

<td >left to right
</td>
</tr>
<tr >

<td >| 
</td>

<td >left to right
</td>

<td >| 
</td>

<td >left to right
</td>
</tr>
<tr >

<td >&&
</td>

<td >left to right
</td>

<td >&&
</td>

<td >left to right
</td>
</tr>
<tr >

<td >|| 
</td>

<td >left to right
</td>

<td >|| 
</td>

<td >left to right
</td>
</tr>
<tr >

<td >?: 
</td>

<td >right to left
</td>

<td >= += -= *= /= %= etc
</td>

<td >right to left
</td>
</tr>
<tr >

<td >= += -= *= /= %= etc
</td>

<td >right to left
</td>

<td >?:
</td>

<td >left to right
</td>
</tr>
<tr >

<td >, 
</td>

<td >left to right
</td>

<td >,
</td>

<td >left to right
</td>
</tr>
</tbody>
</table>

_Note: Reduced C++ table; C ANSI standard from 1989._

Besides some now less important details, we can notice at the end of the table a inversion between the ternary operator and the attribution operator and, more importantly, the inversion of the evaluation order. In C, the ternary operator is evaluated from right to left, whilst in C++ from left to right, like the rest. This is going to shows us that, in line 6, the same expression has two **different interpretations** in each language.

In order to understand bit by bit the problem, let's disassemble the second part of that **for**:

```cpp
    ( f1 == 11 && s != 5 ) ? s = 5, f1 = 0, putchar(10) : ( f1 <= 10 ) ? f1 = f1 : f1 = 12, f1 <= 11; 
```

We have two ternary operators nestled. In accordance with C++ standard, the ternary operators have **less precedence** than the attribution operators and are evaluated **from left to right**. In other words, in first place all the atributions inside the expression are made **before** any ternary operator. After that, the first ternary operator is executed, followed by the second:

```cpp
    ( ( f1 == 11 && s != 5 ) ? (s = 5), (f1 = 0), putchar(10) : ( f1 <= 10 ) ) ? (f1 = f1) : (f1 = 12), f1 <= 11; 
```

The parts in red are the first ones to run, followed by the green ones and, finally, by the blue ones. This color priority is completely arbitrary. Of course, the colors you see in your text editor doesn't have anything to do with this explanation.

Now let't take a look in C. In this language, different from C++, the ternary operators have **more precedence** than the attribution operators, and are executed **from right to left**. That means the first and last ternary operators are executed, ignoring the right attribution, and after that the first ternary operator is executed. Only after these two events the right attribution is evaluated:

```cpp
    ( ( f1 == 11 && s != 5 ) ? s = 5, f1 = 0, putchar(10) : ( ( f1 <= 10 ) ? f1 = f1 : f1 ) ) = 12, f1 <= 11;
```

All this make us to see the attribution to 12 will be done on the **first ternary operator result**, which possible values could be from the **putchar return** or **f1**. Remember about the **comma operator** purpose outside function calls: chain expressions, execute them and return the value from the **rightmost** expression:

```cpp
    s = 5, f1 = 0, putchar(10) // makes s equals 5, f1 equals 0 and returns the putchar call value.
    f1 = f1 : f1 // in both cases the returned value is the f1 variable
```

Well, the f1 variable is an integer. And putchar return as well. This is not going to break any type rule. However, breaks the **attribution gold rule**: "put an lvalue in the right side of an attribution".

```cpp
    f1 = 12; // right; nothing to say
    putchar(10) = 12; // woops! what's that? putchar doesn't return variable but a constant value
```

This finishes the long explanation about why that little insignificant error at the beginning of this article happened only in the C language. This is a perfect example of the little differences between these two languages. Perhaps do you use parenthesis like a crazy, and are not going to find this kind of problems inside your source code. Perhaps not.
