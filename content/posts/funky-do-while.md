---
date: "2008-02-13"
tags: [ "code", "draft",  ]
title: "Funky do-while"
---
It's a known habit to use do-while constructions when there's a need to define a macro that has more than one command instead of using the { simple multicommand brackets }. What was never clear is why this is so.

Let's imagine a trace macro that's enabled in debug mode, whilst kept in silence in release builds:


Nothing much, but it seems to work. But, as we going to see in the following lines, it is really a buggy piece of code, since a call inside an if-else construction simply doesn't work.



Why's that? In order to answer this question, we need to look closer into the result code from the preprocessor, just replacing the macro for its piece of code:


So, that's why. When we call a macro, generally we use the funcion-call syntax, putting a semicolon in the end. This is the right way to call a function, but in the macro case, it's a disaster, because it creates two commands instead of one (an empty semicolon, despite doing nothing, it's a valid command). So that's what the compiler does:




Think about the empty command as if it was a real command, what is the easier way to realize the compiler error:


printf("here we go");


For this reason, the tradicional way to skip this common error is to use a valid construction who asks for a semicolon in the end. Fortunately, language C has such construction, and it is... right, the do-while!


;


So we can rewrite our trace macro the right way, even being a funcky one:


Using a do-while (with a false expression inside the test to execute the block just once) the if-else construction is allowed and working properly:


