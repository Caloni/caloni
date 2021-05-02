---
date: "2009-07-10"
title: Static Polymorphism
categories: [ "draft", "code" ]
---
To explain the polymorphism nothing is better than see how stuff used to be. If you were a twenty old C programmer in the past and created the following functions:

```c
int soma(int x, int y);
double soma(double x, double y);

int main()
{
    int zi = soma(2, 3);
    double zd = soma(2.5, 3.4);
    return 0;
}

 

```

Immediately the compiler would blame you about the following errors:

    
    overload.c

    
    overload.c(2) : warning C4028: formal parameter 1 different from declaration
    overload.c(2) : warning C4028: formal parameter 2 different from declaration
    overload.c(2) : error C2371: 'sum' : redefinition; different basic types
            overload.c(1) : see declaration of 'sum'

This happens because in C **the identifiers are unique into the scope.** This is the reason why the following code is wrong also:

```c
int main()
{
    int x = 0;
    int x = 1;
    return 0;
}

 

```

    
    overload.c
    overload.c(5) : error C2374: 'x' : redefinition; multiple initialization
            overload.c(4) : see declaration of 'x'

Back to the 90's, this is also wrong in C++. Even for a logic issue: how the compiler can pick a variable if we're using the same name for both of them?

Even though, there's a little trick to stop the ambiguity when we talk about functions: the parameters that they receives.

```cpp
int soma(int x, int y);
double soma(double x, double y);

int main()
{
    int zi = soma(2, 3); // dois tipos int: chamar soma(int, int)
    double zd = soma(2.5, 3.4); // dois tipos double: só pode ser soma(double, double)
    return 0;
}

 

```

    
    C:Tests>cl /c overload.cpp
    Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 13.10.6030 for 80x86
    Copyright (C) Microsoft Corporation 1984-2002. All rights reserved.
    
    overload.cpp
    
    C:Tests>

This allowed in C++ the creation of static overload, that is exactly this: to call a function not just by its name, but also to match its signature, the number and the type of the received parameters. We call static because this is done just by the compiler, not creating any overhead during the execution.

Among the most common uses some are as it follows:

    
  * Functions with the same name treating different parameters;

    
    * sum(int, int);

    
    * sum(double, double);

    
    * Obs.: This ignores, of course, the templates usefulness.

    
  * New version of the same fuction with addictional parameters;

    
    * export_data(void* buffer, int size);

    
    * export_data(void* buffer, int size, unsigned long options);

    
  * Same method name to set and get the value of a class property;

    
    * Class::Property(int x); // setter

    
    * int x Class::Property() const; // getter

    
  * Well, whatever your imagination and needs demand =)

