---
categories: [ "code" ]
date: "2009-07-10"
tags: [ "draft",  ]
title: "Static Polymorphism"
---
To explain the polymorphism nothing is better than see how stuff used to be. If you were a twenty old C programmer in the past and created the following functions:


Immediately the compiler would blame you about the following errors:



This happens because in C the identifiers are unique into the scope. This is the reason why the following code is wrong also:



Back to the 90's, this is also wrong in C++. Even for a logic issue: how the compiler can pick a variable if we're using the same name for both of them?

Even though, there's a little trick to stop the ambiguity when we talk about functions: the parameters that they receives.



This allowed in C++ the creation of static overload, that is exactly this: to call a function not just by its name, but also to match its signature, the number and the type of the received parameters. We call static because this is done just by the compiler, not creating any overhead during the execution.

Among the most common uses some are as it follows:

  * Functions with the same name treating different parameters;




  * New version of the same fuction with addictional parameters;



  * Same method name to set and get the value of a class property;



  * Well, whatever your imagination and needs demand =)

