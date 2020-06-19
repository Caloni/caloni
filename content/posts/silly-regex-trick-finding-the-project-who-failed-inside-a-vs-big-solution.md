---
categories: [ "code" ]
date: "2008-02-07"
tags: [ "draft",  ]
title: "Silly regex trick: finding the project who failed inside a big VS solution"
---
I know what you going to think about this one: "silly trick". That's why I just put it in the title. Anyway, that is something I use everyday, so I thought it might be useful to who cares about productivity.

Let's say you have to manage a big solution in Visual Studio made of more than 30 projects, and needs to rebuild all them. Suddenly, something goes wrong. The question is: how to discover, in a heartbeat, what project has failed?

Note that you need to enable "Regular Expressions" option in the Find Dialog (not shown here).

What I'm saying inside this regex is "find the first number different from zero followed by a space and the letters err". This lead us to the first project who has at least one error:


If you think "what about when a project generates more than 9 errors? the regex wouldn't be able to catch this case", well, you're right. Anyway, that's the quicker form to search for the unsuccessful project inside a big solution. A more complex yet complete regex would be:


For me, the first version is enough. It is faster to type, simpler to catch and solves my problem. I hope it can solve yours =)
