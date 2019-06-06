---
date: "2007-07-16"
title: What happens inside the sizeof operator
categories: [ "code" ]
---
The question: how to get the size of a struct member without declaring it as a variable in memory? In pseudocode:

```cpp
static const size_t FIELD_SIZE_MSGID = 15;

struct FEEDER_RECORD_HEADER
{
   char MessageID[FIELD_SIZE_MSGID];
   char MessageIndex[10];
};

// error C2143: syntax error : missing ')' before '.'
char MessageIndexBuffer[sizeof(FEEDER_RECORD_HEADER.MessageIndex) + 1];

// error C2070: '': illegal sizeof operand
char MessageIndexBuffer[sizeof(FEEDER_RECORD_HEADER::MessageIndex) + 1]; 

```

In this first try (even being a nice one) we can clearly see by instinct that the construction is not supposed to work. The compiler error is not even clear. The member access operator (the point sign) needs to have as its left some variable or constant of the same type of the struct. Since the operand is the **type** itself, there is no deal.

The second test is more feasible. Even the compiler can alert us. We have accessed the right member in the right struct but in the wrong way. As we're not using a static member or, in other words, a class variable, we can't access the member by scope. We need an object. But in order to have an object we are supposed to have to create one, and this is exactly what is not allowed in our solution.

**C++ Dead Zone**

This kind of problem reminds me about a curious feature inside the **sizeof** operator: it **doesn't evaluate the expressions** used as operands. How's that? Well, as the sizeof main purpose is to provide us the memory size filled by the expression, it simply doesn't make sense to execute the expression. We just need to note that the language we're talking about defends **eficiency and clarity as main principles**. If you want to execute the expression, we do it without using sizeof operator.

So, now we know that everything put inside a sizeof is not going to be executed in fact. It works somewhat like the c++ "dead zone": is the place where - talking about executable code - nothing runs. That means we can build a object inside sizeof that nothing is going to happen, except for the expression size. Let's look the resulting assembly:

**_sz = sizeof( (new FEEDER_RECORD_HEADER)->MessageID ); // this...
mov dword ptr [sz], 0Fh ; ... is translated into this_**

Another way to do the same thing (for those who can't bear the use of operator new delete, seeing the code as a memory leak):

**sz = sizeof( ((FEEDER_RECORD_HEADER*)0)->MessageID );****_ // this...
_****_mov dword ptr [sz], 0Fh ; ... is translated into this_**

Conclusion: the operator new is called and nothing happens. We got what we wanted. That shows us one more time that the little details built inside a language layout are only very important in the exact time we need them.
