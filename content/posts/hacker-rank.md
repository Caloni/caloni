---
date: "2019-08-08"
link: "https://gist.github.com/Caloni/31fd1105dd18374105d2eb00bce7ee3f"
tags: [ "code", "draft", "ccpp", "english" ]
title: "Some things I learned in a Hacker Rank exercise"
---
A couple of days ago I subscribed to Hacker Hank, a website specialized in provide interview exercises. The site is as a better version of Code Jam, with the possibility to Compile & Run the code, as well as running several test cases.

Talking with friends about one of them proposed a interesting puzzle called Find the Running Median. This is a good problem because it is easy to understand and tricky to implement.

My first attempt was naive, but worked for test cases where there were no duplicated numbers, a detail I overlooked in the description and happenned the very first test (lucky me it is possible to download the test cases, input and output, giving in return some of the points accumulated solving other problems).


So I started to draw in my window a new solution, based on inplace sort algorithm, using the same vector proposed skeleton by the site. The idea was to just move elements inside the vector, ordering them as calculating the median to evey new number.



I still wasn't thinking about the sort algorithm until I began to try and fail several times, but this try/error bitch always taught me how to make things faster then embryological bullshit to born from scribbed windows. It only requested a debugger to make the edit, compile, debug triple step.


I was still trying in the window, thought, until in one of these iteractions with the compiler/debugger I achieved a simples, clearer solution, using only offsets from the vector instead of iterators.


This version almost done it, except for timeout error. Hacker Hank has a timeout of 2 seconds to C++ solutions and I was exceding it. After some thought (more try/error) I thought about change the container, but before I made a simples test: instead of using erase/insert methods make the things manually as in good old C.


And it worked. Now what I learned looking the other solutions.

There are incredible tools in C++, even since 98 or 11, that are frequently overlooked, but it is important to notice that the language has a framework for processing: containers, algorithms and so on. By example, looking for other solutions I learned about the characteristics of multiset and priorityqueue (spoiler: both have a ordering predicate and are logarithmic). There are smart functions in algorithm, too, as lowerbound.

A lot of solutions simply ignored the skeleton provided by the site and began its own code from scratch, eliminating the "request" that the numbers must be stored first in a vector. Sometimes, when there as skeleton in our life, we use them as guidelines, forgetting that "there is no spoon".

I hope you learned something, too. You can see my Hacker Rank attempts in the site (nickname caloni) or my GitHub repository.
