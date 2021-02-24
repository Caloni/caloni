#include <windows.h>
#include <tchar.h>
#include <stdio.h>

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

