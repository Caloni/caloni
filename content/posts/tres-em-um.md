---
categories:
- code
date: '2010-10-09'
tags:
title: Três em um
---

Que vergonha passar tanto tempo sem postar nada. Parece que não fiz nada que valesse a pena comentar por aqui.

Na verdade, não fiz tanto, mesmo. Muitas mensagens do Outlook, gráficos UML e reuniões de alinhamento depois, sobrou um tempinho pra programar. Aprendi algumas coisas que tinha o desejo de saber há tanto tempo... Agora eu sei, quem diria, criar linques suspensos nas janelas Win32! Que novidade, não? Pois é, isso exige, [de acordo com o SDK](http://msdn.microsoft.com/en-us/library/bb760706%28v=VS.85%29.aspx), algumas artimanhas pra fazer funcionar. Para quem está de Visual Studio 2008/2010 na mão basta seguir os passos seguintes.

Definir que estamos programando para XP ou superior:

    #define _WIN32_WINNT 0x0600

Inserir suporte a linques na biblioteca de controles comuns:

    INITCOMMONCONTROLSEX icc = { sizeof(icc), ICC_LINK_CLASS }; 
    InitCommonControlsEx(&icc);

Usar o CreateWindow com a classe certa, fazer markup html dentro do título e cuidar das mensagens de <click> e <enter> no controle:

```
CreateWindowEx(0, WC_LINK, 
	L"<a href=\"http://www.caloni.com.br\">This site rocks!</a>", 
	WS_VISIBLE | WS_CHILD | WS_TABSTOP, ...);

//...

	case WM_NOTIFY:
		switch( ((LPNMHDR)lParam)->code )
		{
		case NM_CLICK:
		case NM_RETURN:
		{
			PNMLINK pNMLink = (PNMLINK)lParam;
			LITEM item = pNMLink->item;
			if( (((LPNMHDR)lParam)->hwndFrom == st_linkHwnd[hWndDlg]) )
			{
				// codigo util
			}
 

```

Você que não está fazendo subclassing de janelas existe outra técnica que você pode utilizar: arrastar-e-soltar o controle do seu ToolBox. Qual é a graça?

![Arrastar-e-soltar controles do Windows](http://i.imgur.com/brmIxLu.png)

 Outra coisa que aprendi foi como enviar mensagens ao usuário para impedir que este reinicie a máquina em momentos importantes:

![Bloqueio de reboot no Windows Seven](http://i.imgur.com/0OKkJKy.png)

A partir do Vista temos uma nova API para fazer isso. E é muito simples:

    BOOL WINAPI ShutdownBlockReasonCreate( 
      __in  HWND hWnd, 
      __in  LPCWSTR pwszReason 
    );   
    
    BOOL WINAPI ShutdownBlockReasonDestroy( 
      __in  HWND hWnd 
    );

Quando ao receber a famigerada WM_QUERYENDSESSION, basta retornar FALSE. O Windows faz o resto.

PS: E com uma ajudinha do Windows Internals ainda fiquei sabendo que dá pra [se colocar na frente da fila](http://msdn.microsoft.com/en-us/library/ms686227%28VS.85%29.aspx) para receber essa mensagem. 
