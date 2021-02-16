---
date: "2007-11-29"
title: Desenhando em C++ Builder
tags: [ "draft", "code" ]
---
Uma das partes mais fáceis e divertidas de se mexer no C++ Builder é a que lida com gráficos. A abstração da VCL toma conta da alocação e liberação dos [objetos gráficos da GDI](http://msdn.microsoft.com/library/en-us/sysinfo/base/gdi_objects.asp) e nos fornece uma interface para desenhar linhas e figuras geométricas, mexer com _bitmaps_, usar fontes etc. Concomitantemente, temos acesso ao _handles_ "crus" da Win32 API para que possamos chamar alguma função esotérica necessária para o seu programa, o que nos garante flexibilidade suficiente.

#### Um "_Personal PaintBrush_" usando Canvas

Vamos fazer da área da janela principal uma tela onde possamos desenhar. Para isso, só precisamos fazer duas coisas em nosso programa: saber quando o _mouse_ está com algum botão pressionado e desenhar quando ele estiver sendo "arrastado".

Saber o estado dos botões é trivial, podemos capturar isso nos eventos **OnMouseDown** e **OnMouseUp** e guardar em alguma variável.

```cpp
//...
private:
	bool mouseDown; // essa variável guarda o estado do mouse...
//...

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	mouseDown = false; // ... e é importante iniciá-la
}

void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	mouseDown = false;
}

void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	Canvas->PenPos = TPoint(X, Y); // mais tarde veremos o porquê disso
	mouseDown = true;
} 

```

Saber quando o _mouse_ está sendo arrastado também é um passo trivial, uma vez que temos esse evento (OnMove) para tratar no controle da janela.

[![Builder OnMouseMove](http://i.imgur.com/biH37HA.png)](/images/builder-onmousemove.png)

Para desenhar, todo formulário e mais alguns controles gráficos possuem um objeto chamado **Canvas**, do tipo TCanvas (duh). Essa classe representa uma superfície de desenho que você pode acessar a partir de seus métodos. Isso é a abstração do conhecido _[device context](http://www.google.com/search?q=device+context+site%3Amsdn.microsoft.com)_ da GDI, tornando a programação mais fácil. O desenho de uma linha, por exemplo, é feito literalmente em uma linha de código.

```cpp
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
	int X, int Y)
{
	if( mouseDown )
	{
		Canvas->LineTo(X, Y);
	}
} 

```

O método **LineTo()** desenha uma linha do ponto onde está atualmente a caneta de desenho até a coordenada especificada. Esse é o motivo pelo qual no evento OnMouseDown alteramos a propriedade **PenPos** do Canvas para o ponto onde o usuário pressiona o botão do mouse.

_Voila_! Temos o nosso _Personal PaintBrush_, com toda a tosquisse que menos de 10 linhas de código podem fazer. OK, ele não é perfeito, admito, mas pode ser melhorado. Temos o código-fonte =).

#### O Windows não se lembra do que você desenhou

Um dos problemas nele reflete o comportamento de gráficos em janelas no Windows. Seja o que for que tenhamos desenhado sobre uma janela, seu conteúdo é perdido ao ser sobrescrito por outra janela. Isso porque a memória de vídeo da área de trabalho é compartilhada entre todas as janelas do sistema (isso muda com o advento do ["Avalon"](http://en.wikipedia.org/wiki/Windows_Presentation_Foundation)). Precisamos, então, sempre repintar o que é feito durante a execução do programa.

Se precisamos repintar, logo precisamos saber tudo o que o usuário fez até então. Uma das técnicas mais baratas no quesito memória para salvar o estado gráfico de uma janela é guardar um histórico das operações realizadas sobre sua superfície e executá-las novamente ao repintar a janela. A GDI é rápida o bastante para que o custo de processamento não seja sentido na maioria dos casos. Para o nosso _Paint_, apenas um array de coordenadas origem-destino já dá conta do recado:

```cpp
//...
private:
	bool mouseDown; // essa variavel guarda o estado do mouse
	std::vector<TRect> mouseHistory; // um TRect guarda duas posicoes XY
//...

// ...
{
	if( mouseDown )
	{
		// guardando a pincelada para reproduzi-la depois
		mouseHistory.push_back( TRect(Canvas->PenPos, TPoint(X, Y)) );
		Canvas->LineTo(X, Y);
	}
}
//... 

```

[![Amo o Builder](http://i.imgur.com/HGbLN0n.gif)](/images/amobuilder.gif)
