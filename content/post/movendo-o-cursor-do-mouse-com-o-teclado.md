---
categories: [ "code" ]
date: "2007-07-26"
tags: [ "draft",  ]
title: "Movendo o cursor do mouse com o teclado"
---
Bom, vamos deixar de papo furado e "codar". Para essa primeira tentativa iremos desenvolver um programa que move o cursor do mouse quando pressionada uma tecla de atalho e voltar à sua posição original quando pressionada outra tecla.

Nota de desculpas: eu sei que estou sendo rabugento demais com o mouse. Já é o segundo artigo que escrevo falando como evitar o mouse e isso deve realmente irritar os fãs desse ponteirinho irritante.

Como eu já havia dito anteriormente, uso o mouse quando necessário. Quando ele não é necessário ele fica clicando inconscientemente no Windows Explorer, já que utilizo a configuração de clique único, onde as pastas e arquivos ficam selecionáveis apenas pousando o cursor sobre eles. Eu gosto dessa configuração, exceto pelo comportamento desagradável que ocorre quando mudo para a janela do Windows Explorer e meu mouse ganha vida própria, selecionando alguma pasta ou arquivo e mudando meu foco de seleção.

Portanto, o objetivo desse programa é simples e direto: mover o mouse para um canto enquanto eu uso meu teclado. Nada mais, nada menos. Para isso iremos registrar alguns atalhos globais no Windows. Para registrar atalhos globais no Windows utilizamos a função RegisterHotKey.

    BOOL RegisterHotKey(HWND hWnd, int id, UINT fsModifiers, UINT vk);

O importante aqui é saber que iremos ser avisados do pressionamento das teclas que registrarmos por meio dessa função através do loop de mensagens da thread que chamar a função.

Resumidamente, um loop de mensagens é a maneira definida pelo Windows para avisar as aplicações dos eventos que ocorrerem no sistema que são relevantes para as suas janelas. Teremos chance de observar isso mais vezes, mas por enquanto basta ter uma visão geral do fluxo de mensagens que ocorre quando digitarmos a nossa tecla de atalho:

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
    

Como você pode ver o código não tem muitos segredos. Para registrar os atalhos, usamos a função RegisterHotKey. Para manipular os eventos usamos o tal loop de mensagens e manipulamos a mensagem WMHOTKEY de acordo com a tecla pressionada. Para mover o mouse usamos a função SetCursorPos (e para armazenar a posição atual GetCursorPos). Por fim, para ler configurações de um .ini usamos a função GetPrivateProfileInt. Abaixo um exemplo desse arquivo texto:

    [HideCursor]
    DisableX=600
    DisableY=0

Nota final: você acha que os atalhos "WinKey + Del", "WinKey + Insert" e "WinKey + End" foram uma má escolha? Concordo. Fiz de propósito. Que tal customizar o programa para que as teclas sejam lidas do arquivo de configuração HideCursor.ini?
