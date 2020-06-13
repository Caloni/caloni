---
categories: [ "code" ]
date: "2007-09-24"
tags: [ "draft",  ]
title: "Why is my DLL locked?"
---
There is a document from Microsoft alerting about the hazards in putting your code inside a DllMain function. what is more comprehensive and easier to read than the MSDN observations. It is worth reading, even because the explanations about the loader lock and its side effects can do very good for your code health.

In short, the Windows code responsible to call DllMain for each loaded/unloaded DLLs uses an exclusive access object (the so-called "mutex") to synchronize its calls. The result is that inside a process just one DllMain can be called at a given moment. This object-mutex is called "loader lock" into the Microsoft documentation.

The code below is silly, but represents quite well what I've seen in lots of production code. For many times I was unable to realize what was going on (whether because I didn't know about the loader lock or the code readability was too bad). The comments say by themselves:

    //
    // LoaderLock.dll
    //
    #include <windows.h>
    
    HANDLE g_thrLock = NULL; // locked thread handle
    BOOL g_getOut = FALSE; // it would be useful to unlock the thread, but it's not
    
    /** The thread locker
    
    The function of this thread is to lock. It tries to call DllMain (indirectly). 
    In order to do this, it needs the loader lock. Unfortunately the main thread 
    has got it before. The obvious result: this secondary thread is going to 
    wait forever for a resource that will be never released.
    */
    DWORD WINAPI ThreadLock(PVOID)
    {
    	while( true )
    	{
    		// I'm here to hinder, not to help
    		Sleep(1000);
    		if( g_getOut ) 
    			break;
    	}
    
    	return ERROR_ACCESS_DENIED; // this does not work
    }
    
    /** The DllMain locker
    
    The function of this DllMain is to show how not to code an DllMain. It creates 
    a thread on the PROCESS_ATTACH event (bad sign). Not happy yet, it waits 
    for the thread on the PROCESS_DETACH event (bad bad sign). As this thead has 
    got the loader lock, the secondary thread will never reach the point 
    where it returns.
    */
    BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
    {
    	if( fdwReason == DLL_PROCESS_ATTACH )
    	{
    		// creates the locked thread
    		DWORD tid = 0;
    		g_thrLock = CreateThread(NULL, 0, ThreadLock, NULL, 0, &tid);
    	}
    	else if( fdwReason == DLL_PROCESS_DETACH )
    	{
    		// waits for the thread for ever and ever
    		g_getOut = TRUE;
    		WaitForSingleObject(g_thrLock, INFINITE);
    		CloseHandle(g_thrLock), g_thrLock = NULL;
    	}
    } 
    

A simple victim of all this can be an executable using a poorly written DLL, just like the code above:

    //
    // Victim.exe
    //
    #include <windows.h>
    #include <tchar.h>
    
    int main()
    {
    	HMODULE lockDll = LoadLibrary(_T("LoaderLock.dll"));
    
    	if( lockDll )
    	{
    		Sleep(5000);
    		FreeLibrary(lockDll), lockDll  = NULL;
    	}
    } 
    

In order to the see the locking code in action, copy the DLL and EXE source files and use the following commands to generate the executable files:

    
    cl /c loaderlock.cpp loaderlock-exe.cpp
    link loaderlock-exe.obj
    link /dll loaderlock.obj

It is important to remember that a DllMain dependant code is a very, very bad thing. Nevertheless, there are some particular cases the only place to run our code is inside DllMain. In these cases, when detected, try to run a side by side communication with your locked thread using an event object (or equivalent) before it really returns. Using this craft the thread can warn the waiting thread that the important thing to be done is done, and the waiting thread can go to sleep and stop waiting forever locked threads.

    
  1. NT Loader (MSJ Sep 99) - Matt Pietrek
  2. mgrier's WebLog - NT Loader team participant
