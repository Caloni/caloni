---
date: "2007-09-24"
title: "Why is my DLL locked?"
tags: [ "code", "english" ]
---
The Windows code responsible to call DllMain for each loaded and unloaded DLLs uses an exclusive access object, the so-called mutex, to synchronize its calls. The result is that inside a process just one DllMain can be called at a given moment. This object-mutex is called "loader lock" into the Microsoft documentation.

![Loader Lock explained](/img/loader_lock.gif)

I wrote a [silly code] that represents quite well what I've seen in lots of production code. For many times I was unable to realize what was going on (whether because I didn't know about the loader lock or the code readability was too bad). The code say by itself: calling CreateThread inside DllMain must lock your execution forever.

A simple victim of all this can be an executable using a poorly written DLL, just like the code above:

    int main()
    {
      printf("load dll");
    	HMODULE lockDll = LoadLibrary(_T("dll_lock.dll"));
    
    	if( lockDll )
    	{
    		Sleep(2000);
        printf("free dll");
    		FreeLibrary(lockDll), lockDll  = NULL;
        printf("done");
    	}
    }

It is important to remember that a DllMain dependant code is a very, very bad thing. Nevertheless, there are some particular cases the only place to run our code is inside DllMain. In these cases, when detected, try to run a side by side communication with your locked thread using an event object (or equivalent) before it really returns. Using this craft the thread can warn the waiting thread that the important thing to be done is done, and the waiting thread can go to sleep and stop waiting forever locked threads.

Entre os clássicos e inestimáveis artigos de Matt Pietrek no Microsoft Journal há na [edição de setembro de 1999] um bem curto a respeito da inicialização de DLLs. Essa é a leitura mais sucinta, didátia e esclarecedora sobre a questão.

[silly code]: /code/dll_lock.cpp
[edição de setembro de 1999]: http://bytepointer.com/resources/pietrek_debug_init_routines.htm
