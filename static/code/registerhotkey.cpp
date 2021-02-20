/** @brief Puts the mouse cursor in a pre-defined place.
@author Wanderley Caloni (wanderley@caloni.com.br)
@date 07-2007
*/
#include <windows.h>
#include <tchar.h>

// Useful stuff.
//
#define SIZEOF_ARRAY(a) ( sizeof(a) / sizeof(a[0]) )

// Constant values.
//
#define HIDECURSOR_ENABLE 0x0000 ///< Restore the cursor position.
#define HIDECURSOR_DISABLE 0x0001 ///< 'Hide' the cursor position.
#define HIDECURSOR_QUIT 0x0002 ///< Quit the program.

/** And Bill said: 'WinMain!'
*/
int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, int)
{
	DWORD ret = ERROR_SUCCESS;

	// First we try to register all three hot keys.
	if( RegisterHotKey(NULL, HIDECURSOR_DISABLE, MOD_WIN, VK_DELETE) )
	{
		if( RegisterHotKey(NULL, HIDECURSOR_ENABLE, MOD_WIN, VK_INSERT) )
		{
			if( RegisterHotKey(NULL, HIDECURSOR_QUIT, MOD_WIN, VK_END) )
			{
				// Set the configuration path.
				TCHAR configPath[MAX_PATH];

				if( GetCurrentDirectory(SIZEOF_ARRAY(configPath), configPath) )
					lstrcat(configPath, _T("\\HideCursor.ini"));
				else
					lstrcpy(configPath, _T(".\\HideCursor.ini"));

				
				// Position to move the cursor when pressed the disable hot key.
				const POINT disabledPos = 
				{
					GetPrivateProfileInt(_T("HideCursor"), _T("DisableX"), 
						300, configPath),
					GetPrivateProfileInt(_T("HideCursor"), _T("DisableY"), 
						0, configPath)
				};

				
				// Where we move back the cursor when pressed the enable hot key.
				POINT enabledPos = disabledPos;
				GetCursorPos(&enabledPos);

				
				// While everything is allright, handle the hot keys.
				MSG msg = { };
				bool quit = false;
				
				while( ! quit && GetMessage(&msg, NULL, 0, 0) )
				{
					// Hey, it's a hot key!
					if( msg.message == WM_HOTKEY )
					{
						switch( msg.wParam )
						{
						// Moves the cursor to the pre-defined place.
						case HIDECURSOR_DISABLE:
							{
								POINT currPos = disabledPos;
								GetCursorPos(&currPos);

								// If the enabled and disabled positions are different
								// update the enable position and defines a new pos.
								if( currPos.x != disabledPos.x 
									|| currPos.y != disabledPos.y )
								{
									enabledPos = currPos;
									SetCursorPos(disabledPos.x, disabledPos.y);
								}
							}
							break;

						// Restores the cursor to the last enabled place.
						case HIDECURSOR_ENABLE:
							SetCursorPos(enabledPos.x, enabledPos.y);
							break;

						// Quits the program.
						case HIDECURSOR_QUIT:
							quit = true;
							break;
						}
					}
				}
				
				UnregisterHotKey(NULL, HIDECURSOR_QUIT);
			}
			else 
				ret = GetLastError();

			UnregisterHotKey(NULL, HIDECURSOR_ENABLE);
		}
		else 
			ret = GetLastError();
		
		UnregisterHotKey(NULL, HIDECURSOR_DISABLE);
	}
	else 
		ret = GetLastError();

	return ExitProcess(ret), ret;
} 
