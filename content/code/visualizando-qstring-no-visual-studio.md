---
date: "2017-02-20"
title: "Visualizando QString no Visual Studio"
categories: [ "code" ]

---
O Qt não é um framework que pode apenas ser usado no QtCreator. Através de um projeto bem configurado pelo CMake, por exemplo, é possível ter um projeto que pode ser compilado e depurado tanto nas ferramentas do Qt quanto no Visual Studio. No entanto, na hora de depurar algumas coisas são difíceis de fazer. Por exemplo: como olhar o conteúdo de uma QString?

O Visual Studio utiliza um mecanismo que lembra os comandos bizarros que se usa no WinDbg, mexendo com registradores e tal. Através dessa combinação é possível dizer para o depurador como interpretar determinados tipos de objetos. Ele já vem obviamente pronto para std::string, CString (ATL) e deveria vir com QString, de tão famosa que é. Mas a versão do Visual Studio 2015 não vem. O jeito então é editar diretamente o arquivo onde ficam esses padrões.

```ini
; AutoExp.Dat - templates for automatically expanding data
```

O nome do arquivo é __autoexp.dat__ e ele fica em uma pasta no estilo Program Files, Microsoft Visual Studio, Common7, Packages, Debugger. É melhor você retirar ele dessa pasta antes de sobrescrevê-lo para não ter erro de acesso. Ao abri-lo verá que no começo há vários comentários que explicam como é o funcionamento desse padrão.

```ini
; type=[text]<member[,format]>...
;
; type		Name of the type (may be followed by <*> for template
;			types such as the ATL types listed below).
;
; text		Any text.Usually the name of the member to display,
;			or a shorthand name for the member.
;
; member	Name of a member to display.
;
; format	Watch format specifier. One of the following:
;
;	Letter	Description					Sample		   Display
;	------	--------------------------	------------   -------------
;	d,i		Signed decimal integer		0xF000F065,d   -268373915
;	u		Unsigned decimal integer	0x0065,u	   101
;	o		Unsigned octal integer		0xF065,o	   0170145
;	x,X		Hexadecimal integer			61541,X		   0X0000F065
;	l,h		long or short prefix for	00406042,hx    0x0c22
;			  d, i, u, o, x, X
;	f		Signed floating-point		3./2.,f		   1.500000
;	e		Signed scientific-notation	3./2.,e		   1.500000e+000
;	g		Shorter of e and f			3./2.,g		   1.5
;	c		Single character			0x0065,c	   'e'
;	s		Zero-terminated string		pVar,s		   "Hello world"
;	su		Unicode string				pVar,su		   "Hello world"
;
; For details of other format specifiers see Help under:
; "format specifiers/watch variable"
```

Felizmente (e também obviamente) o pessoal do Qt já fez [uma entrada na wiki](https://wiki.qt.io/IDE_Debug_Helpers) que explica como fazer para interpretar corretamente uma QString. Eles mesmos admitem que a coisa ficou difícil desde a última versão (Qt 5), mas ainda assim é possível. E, se tudo falhar, ainda é possível usar a janela de Watch:

```txt
(char*)str.d + str.d->offset,su
```

Mas não foi o caso dessa vez. Tudo funcionou perfeitamente assim que incluí os valores da Wiki logo no começo da sessão __Visualizer__.

![](http://i.imgur.com/3dnGwGK.gif)

