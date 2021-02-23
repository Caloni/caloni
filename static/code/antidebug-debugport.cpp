/** @brief Antidebug protection based on DebugPort aquisition.
* @author Wanderley Caloni (wanderley@caloni.com.br)
* @date 2007-08
*/
#include <windows.h>

/* Every debugger needs a debugging loop. In this loop it catches
debugging events sent by the operating system.
*/
DWORD DebugLoop()
{
	DWORD ret = ERROR_SUCCESS;
	bool exitLoop = false;

	while( ! exitLoop )
	{
		DEBUG_EVENT debugEvt;

		WaitForDebugEvent(&debugEvt, INFINITE);

		switch( debugEvt.dwDebugEventCode )
		{
			// Process going out. We get out the loop and leave.
			case EXIT_PROCESS_DEBUG_EVENT:
			exitLoop = true;

			break;
		}

		// Necessary, since the current thread is frozen.
		ContinueDebugEvent(debugEvt.dwProcessId, debugEvt.dwThreadId, DBG_EXCEPTION_NOT_HANDLED);
	}

	return ret;
}

/* Attachs to the protected process againt debugging. Actually, we protect it
againt debugging being its debugger.
*/
DWORD AntiAttach(DWORD pid)
{
	DWORD ret = ERROR_SUCCESS;

	if( pid )
	{
		BOOL dbgActProc;

		dbgActProc = DebugActiveProcess(pid);

		if( dbgActProc )
			DebugLoop();
		else
			ret = GetLastError();
	}
	else
		ret = ERROR_INVALID_HANDLE;

	return ret;
}

/* In the beginning, God said: 'int main!'
*/
int main(int argc, char* argv[])
{
	DWORD ret = ERROR_SUCCESS;

	if( argc > 1 )
	{
		DWORD pid = atoi(argv[1]);
		ret = AntiAttach(pid);
	}

	return (int) ret;
} 

