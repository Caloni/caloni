---
date: "2008-02-07"
title: 'Silly regex trick: finding the project who failed inside a big VS solution'
categories: [ "code" ]
---
I know what you going to think about this one: "silly trick". That's why I just put it in the title. Anyway, that is something I use everyday, so I thought it might be useful to who cares about productivity.

Let's say you have to manage a big solution in Visual Studio made of more than 30 projects, and needs to rebuild all them. Suddenly, something goes wrong. The question is: how to discover, in a heartbeat, what project has failed?

[![Find Error in VS projects using regex](http://i.imgur.com/hDJdrX8.png)](/images/find-error-regex2.png)

Note that you need to enable "Regular Expressions" option in the Find Dialog (not shown here).

What I'm saying inside this regex is "find the first number different from zero followed by a space and the letters err". This lead us to the first project who has at least one error:

    
    ------ Build started: Project: FailedProj, Configuration: Release Win32 ------
    Compiling...
    stdafx.cpp
    Compiling...
    FailedProj.cpp
    .FailedProj.cpp(2477) : error C2039: 'Blablabla' : is not a member of 'IBlabla'
    Build log was saved at "file://c:Projects...ReleaseBuildLog.htm"
    FailedProj -

2 err

    
    or(s), 0 warning(s)

If you think "what about when a project generates more than 9 errors? the regex wouldn't be able to catch this case", well, you're right. Anyway, that's the quicker form to search for the unsuccessful project inside a big solution. A more complex yet complete regex would be:

    
    [1-9][0-9]* err

For me, the first version is enough. It is faster to type, simpler to catch and solves my problem. I hope it can solve yours =)
