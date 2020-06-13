---
categories: [ "code" ]
date: "2008-08-05"
tags: [ "draft",  ]
title: "Antidebugging during the process attach"
---
Today was a great day for reverse engineering and protection analysis. I've found two great programs to to these things: a API call monitor and a COM call monitor. Besides that, in the first program site - from a enthusiastic of the good for all Win32 Assembly - I've found the source code for one more antidebugging technique, what bring us back to our series of antidebugging techniques.

The purpose of this protection is to detect if some debugger tries to attach into our running process. The attach to process operation is pretty common in all known debugger, as WinDbg and Visual Studio. Different from the DebugPort protection, this solution avoids the attach action from the debuggee program. In this case the protection can make choices about what to do on the event of attach (terminate the process, send an e-mail, etc).

The code I've found does nothing more than to make use of the attach process function that's always called: the ntdll!DbgUiRemoteBreakin. Being always called, we can just to put our code there, what is relatively easy to do:

    #include <windows.h>
    #include <iostream>
    #include <assert.h>
    
    using namespace std;
    
    /** This function is triggered when a debugger try to attach into our process.
    */
    void AntiAttachAbort()
    {
    	// this is a test application, remember?
    	MessageBox(NULL, "Espertinho, hein?", "AntiAttachDetector", MB_OK | MB_ICONERROR);
    
    	// this is the end
    	TerminateProcess(GetCurrentProcess(), -1);
    }
    
    /** This function installs  a trigger that is activated when a debugger try to attach.
    @see AntiAttachAbort.
    */
    void InstallAntiAttach()
    {
    	PVOID attachBreak = GetProcAddress(
    		GetModuleHandle("ntdll"), // this dll is ALWAYS loaded
    		"DbgUiRemoteBreakin"); // this function is ALWAYS called on the attach event
    
    	assert(attachBreak); // attachBreak NEVER can be null
    
    	// opcodes to run a jump to the function AntiAttachAbort
    	BYTE jmpToAntiAttachAbort[] =
    	{ 0xB8, 0xCC, 0xCC, 0xCC, 0xCC,   // mov eax, 0xCCCCCCCC
    	0xFF, 0xE0 };                     // jmp eax
    
    	// we change 0xCCCCCCCC using a more useful address
    	*reinterpret_cast<PVOID*>(&jmpToAntiAttachAbort[1]) = AntiAttachAbort;
    
    	DWORD oldProtect = 0;
    
    	if( VirtualProtect(attachBreak, sizeof(jmpToAntiAttachAbort), 
    		PAGE_EXECUTE_READWRITE, &oldProtect) )
    	{
    		// if we can change the code page protection we put a jump to our code
    		CopyMemory(attachBreak, 
    			jmpToAntiAttachAbort, sizeof(jmpToAntiAttachAbort));
    
    		// restore old protection
    		VirtualProtect(attachBreak, sizeof(jmpToAntiAttachAbort), 
    			oldProtect, &oldProtect);
    	}
    }
    
    /** In the beginning, God said: 'int main!'
    */
    int main()
    {
    	InstallAntiAttach();
    	cout << "Try to attach, if you can...";
    	cin.get();
    } 
    

To compile the code above, just call the compiler and linker normally. Obs.: We need the user32.lib in order to call MessageBox API:

    
    cl /c antiattach.cpp
    link antiattach.obj user32.lib

    
    antiattach.exe
    Try to attach, if you can...

After the program has been running, every try to attach will show a detection message and program termination.

    
    windbg -pn antiattach.exe

    
    <a href="/images/mdRqvjp.png" title="Detecção de attach"><img src="/images/mdRqvjp.png" alt="Detecção de attach"></img></a>

Yes, I know. Sometimes we have to use "brute force codding" and make obscure codes, like this:

    // opcodes to run a jump to the function AntiAttachAbort
    BYTE jmpToAntiAttachAbort[] =
    { 0xB8, 0xCC, 0xCC, 0xCC, 0xCC,   // mov eax, 0xCCCCCCCC
    0xFF, 0xE0 };                     // jmp eax
    
    // we change 0xCCCCCCCC using a more useful address
    *reinterpret_cast<PVOID*>(&jmpToAntiAttachAbort[1]) = AntiAttachAbort; 
    

There are a lot of ways to do the same thing. The example above is what is normally called in the crackers community as a shellcode, what is a pretty name for "byte array that is really the assembly code that does interesting things". Shellcode for short =).

Alternative ways to do this are:

    
  1. To declare a naked function in Visual Studio, to create an empty function just after, do some math to calculate the size of the function to be copied into another place (aware of Edit and Continue option).

    
  2. To create a structure whose members are masked opcodes. This way, is possible in the constructor to receive the values and use it as a "mobile function".

Both have pros and cons. The cons are related with the environment dependency. In the first alternative is necessary to configure the project to disable "Edit and Continue" option, whilst in the second one is necessary to align 1 byte the structure.

Anyway, given the implementation, the main advantage is to isolate the code in only two functions - AntiAttachAbort and InstallAntiAttach - an API local hook (in the same process) that should never be called in production code. Besides, there are C++ ways to do such thing like "live assembly". But this is matter for other future and exciting articles.
