---
date: "2007-12-05"
title: "Interação entre controles no C++ Builder"
tags: [ "code" ]
---
Como próxima lição da nossa jornada Borland, vamos aprender a fazer os controles de um form interagirem entre si com a força do pensamento.

Para essa proeza precisaremos de:

 - Dois TButtons
 - Um TEdit
 - Um TListBox

Bom, sabemos já como colocar esses caras no form principal. Apenas espalhe-os de maneira que eles não fiquem uns em cima dos outros (essa técnica de espalhamento chama-se design).

Agora no evento default do Button1 (duplo-clique nele) colocaremos o seguinte código:

    void __fastcall TForm1::Button1Click(TObject *Sender)
    {
    	if( !Edit1->Text.IsEmpty() )
    	{
    		ListBox1->AddItem(Edit1->Text, 0);
    		Edit1->Text = "";
    	}
    } 

Percebeu? Não? Então rode e note o que acontece quando você aperta o botão.

Agora iremos fazer algo mais interessante ainda com o segundo botão. Coloque no evento default o seguinte código:

    void __fastcall TForm1::Button1Click(TObject *Sender)
    {
    	if( !Edit1->Text.IsEmpty() )
    	{
    		ListBox1->AddItem(Edit1->Text, 0);
    		Edit1->Text = "";
    	}
    } 

Mais simples, impossível. E com um pouco de imaginação, o mais besta dos aplicativos pode se tornar uma utilidade do dia a dia. Até sua mãe vai adorar.

![Lista de Compras](/img/listadecompras.gif)
