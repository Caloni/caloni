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
