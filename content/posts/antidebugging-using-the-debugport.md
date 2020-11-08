---
date: "2008-08-01"
link: "/ppt/antidebugging-eu-nao-quero-que-vc-mexa-no-meu-codigo.pdf"
tags: [ "code", "draft",  ]
title: "Antidebugging using the DebugPort"
---
When a debugger starts a process to be debugged or, the article case, connects to a already created process, the communication between these processes is made through an internal resource inside Windows called LPC (Local Procedure Call). The system creates a "magic" communication port for debugging and the debugging events pass throw it.

Among these events we can tell the most frequent:

  * Activated breakpoints

  * Thrown exceptions

  * Threads creation/termination

  * DLLs load/unload

  * Process exit

In the case of connecting into a existent process, the API DebugActiveProcess is called. Since this call, if successful, the caller program is free now to call the API DebugActiveProcess looking for debugging events. The main loop for a debugger is, so, pretty simple:


The interesting detail about this communication process is that a program can be debugged actively only for ONE debugger. In other words, while there's a process A debugging process B, no one besides A can debug and break B.Using this principle, we can imagine a debugging protection based on this exclusivity, creating a protector process that connects to the protected process and "debugs" it:


The needed steps to test the code above are:

  1. Compile the code

  2. Run notepad (or another victim)

  3. Get its PID (Process ID)

  4. Run the protector process passing the notepad PID as the argument

  5. Try to attach to the notepad using a debugger (e.g. Visual C++)

After the attach process, the debug port is occupied, and the communication between the debugger and debuggee is made throug LPC. Bellow we can see a little illustration of how things work:

Basically the process stay receiving debugging events (through the LPC message queue) until the final event, the process exit. Notice that if someone try to terminate the protector process the debuggee process will be terminated, too.

The strength in this protection is that it doesn't affect the code understanding and readability. In fact the code that protects is in another process. The weakness, I would say, it is your visibility. Everyone that will try to attack the solution will se two processes being created, what gives him/her something to think about...

That's why thinking about the implementation is vital. Particularly the main point to be thought is the debugger/debuggee union. As much as better these two pieces were packed, harder to the attacker will be to separate them. An additional idea is to use the same technique in the opposite way, in other words, the debuggee process to attach into the debugger.

This time I'm not going to say that there's a easy solution. Maybe because I haven't though enough about the problem. Ideas?
