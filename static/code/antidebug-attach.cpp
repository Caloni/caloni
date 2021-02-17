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

