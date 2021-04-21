---
date: "2020-07-05"
link: "https://www.scm.keele.ac.uk/staff/stan/2016/05/16/closing-sockets-without-killing-processes/"
tags: [ "code", "english" ]
title: "Close Remote Socket"
---
I got used to close sockets in Windows using TCP View, but I haven't learned yet how to do this in Linux. Some Google and now I know. It is kinda simple in terminal mode, as any task a programmer needs to do in your system.

You just need to find the process using netstat, find the socket descriptor using lsof, debug the process with gdb, close the socket using call command, close the debugger. You done. How simple is that, right?
