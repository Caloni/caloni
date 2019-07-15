---
date: "2007-12-05"
title: Interação entre controles no C++ Builder
categories: [ "code" ]
---
[![C++ Builder Control](http://i.imgur.com/DI06ffN.png)](/images/cppbuilder-controls.png)Como próxima lição da nossa jornada Borland, vamos aprender a fazer os controles de um _form_ interagirem entre si com a força do pensamento.

Para essa proeza precisaremos de:

    
    Dois <strong>TButtons</strong>
    Um <strong>TEdit</strong>
    Um <strong>TListBox</strong>

Bom, sabemos já como colocar esses caras no _form_ principal. Apenas espalhe-os de maneira que eles não fiquem uns em cima dos outros (essa técnica de espalhamento chama-se _design_).

Agora no evento _default_ do Button1 (duplo-clique nele) colocaremos o seguinte código:

```cpp
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if( !Edit1->Text.IsEmpty() )
	{
		ListBox1->AddItem(Edit1->Text, 0);
		Edit1->Text = "";
	}
} 

```

Percebeu? Não? Então rode e note o que acontece quando você aperta o botão.

Agora iremos fazer algo mais interessante ainda com o segundo botão. Coloque no evento default o seguinte código:

```cpp
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if( !Edit1->Text.IsEmpty() )
	{
		ListBox1->AddItem(Edit1->Text, 0);
		Edit1->Text = "";
	}
} 

```

#### É só isso?

Mais simples, impossível. E com um pouco de imaginação, o mais besta dos aplicativos pode se tornar uma utilidade do dia a dia. Até sua mãe vai adorar.

[![Lista de Compras](http://i.imgur.com/GRoobs1.gif)](/images/listadecompras.gif)
