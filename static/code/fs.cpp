#include <iostream>
#include <windows.h>

#pragma comment(lib, "user32")

int main()
{
    if( ! SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE | CONSOLE_WINDOWED_MODE, NULL) )
    {
        // Se falhas com GLE 120 (função não suportada) usar função abaixo.
        ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    }
    system("chcp 65001");
}
