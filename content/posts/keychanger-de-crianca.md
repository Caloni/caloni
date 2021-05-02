---
date: "2008-01-24"
title: "Keychanger de criança"
categories: [ "code" ]
---
Às vezes na vida a vontade de fazer alguma coisa besta acaba sendo mais forte do que o senso de ridículo. Então, resolvi ressuscitar o quase apodrecido [RusKey], um programa que fiz para trocar letras digitadas no teclado. A idéia é muito simples: o sujeito digita 'i' e sai um 'c', digita um 'f' e sai um 'u', e assim por diante. Se estiver programando e for criar um if, por exemplo, no lugar da palavra if vai aparecer... bom, não é exatamente um if que vai aparecer na tela =).

Mas se analisarmos dessa maneira pode parecer até coisa de "ráquer", o que certamente não é. Na verdade, se trata de um programa didático que visa ensinar a digitação em leiautes de teclados diferentes do normal em idiomas latinos. Pelo menos essa foi a intenção original. 

Na época eu estava às voltas com o leiaute do famoso teclado russo (percebeu a origem do nome do programa?). Eu havia estudado cirílico e estava na hora de pôr em prática no computador. Mas, como quase nunca treinava, quando tentava procurar uma palavra no Babylon ou arriscar uma expressão nas conversas com minha amiga de Moscou me perdia completamente para encontrar as letras. A necessidade é a mãe da invenção e foi aí que começou o desenvolvimento.

Um alfabeto é uma das muitas maneiras de representar as palavras de uma língua por escrito. Uma palavra escrita é um conjunto de letras que representa os sons que usamos para falar essa palavra. Cada som usado é chamado de fonema.

Assim sendo, embora o alfabeto russo seja diferente do alfabeto latino muitos fonemas são compartilhados. Isso quer dizer que podemos pegar algumas letras do cirílico e traduzir diretamente para algumas letras do nosso alfabeto, e outras letras não. Exemplos de letras que podemos fazer isso:

    Б == B
    В == V
    Г == G
    Д == D
    ...

Porém, após a tradução de uma letra no teclado, a posição dela geralmente não é a mesma posição do nosso teclado. Daí temos uma letra de nosso alfabeto em outro lugar. Se for feita uma tradução aproximada entre os dois alfabetos, nossas letras em um teclado russo ficariam dispostas assim:

![Russian Keyboard](/img/russian-keyboard.png)

Bem diferente do QWERT ASDFG que estamos acostumados, não?

Ao digitar usando esse pseudo-leiaute o treino do leiaute do teclado russo estaria sendo feito mesmo escrevendo com o alfabeto latino. Legal, não? Poderia programar com as letras todas trocadas, porque a saída final é a mesma. Basta treinar os dedos para acertarem as mesmas letras nos novos lugares. Assim, quando precisasse escrever no alfabeto cirílico saberia melhor onde cada letra fica.

A idéia é simples, e o código também não é nada complexo. Só preciso de um EXE e uma DLL. No EXE chamo uma função exportada pela DLL que por sua vez instala um hook de mensagens:

    g_hHook = SetWindowsHookEx(WH_GETMESSAGE, HookProc, GetModuleHandle(MODULE_NAME), 0);

Nas chamadas da função de callback da DLL, manipulo a mensagem WM_CHAR, que corresponde à digitação de caracteres, para trocar os caracteres originais do teclado pelos caracteres que deveriam existir no recém-inventado formato latino-russo, totalmente fora dos padrões e normas de segurança existentes:

    switch( pMsg->message )
    {
    	case WM_CHAR:
    	{
    		LPTSTR ptzChar =
    		_tcschr(g_tzRussAlphabet, (TCHAR) pMsg->wParam);
    
    		if( ptzChar )
    		{
    			size_t offset = ptzChar - g_tzRussAlphabet;
    			pMsg->wParam = (WPARAM) g_tzPortAlphabet[offset];
    		}
    	}
    } 

Simples assim. E temos um keylogger que troca caracteres! É impressionante como as coisas mais simples podem se transformar nos momentos mais divertidos de um programador em um feriado.

[RusKey]: http://www.codeproject.com/KB/winsdk/ruskey.aspx
