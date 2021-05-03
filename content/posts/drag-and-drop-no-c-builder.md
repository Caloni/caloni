---
categories:
- code
date: '2007-12-19'
title: Drag and drop no C++ Builder
---

O sistema de drag and drop do C++ Builder é muito fácil de usar, integrado que está com o sistema de classes e objetos do framework. Tanto para o objeto de drag quanto para o objeto de drop tudo que temos que fazer é definirmos a propriedade DragMode para dmAutomatic como mostra a figura. Isso fará com que toda a troca de mensagens seja manipulada automaticamente pela VCL.

![Troca-troca](/img/trocatroca.gif)

A parte (ridídula) do código fica por conta da manipulação do evento de drop. Para aceitar um objeto, devemos tratar o evento OnDragOver. Basta isso para que a variável Accept tenha seu valor default definido para true. Podemos, entretanto, escolher se iremos ou não tratar um possível drop de um objeto. Verificando seu tipo, por exemplo:

    void __fastcall TMain::FormDragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept)
    {
    	Accept = true;
    }
    
    void __fastcall TMain::ListBoxDragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept)
    {
    	Accept = dynamic_cast<TWinControl*>( Source ) ? true : false;
    } 

A parte mais interessante do código fica por conta da hora que o objeto é "jogado", no evento OnDragDrop. Nela recebemos o ponteiro para o Sender (como sempre), que é o target object, e um Source. Geralmente para manipular o source object é necessário antes realizar um cast para um tipo mais conhecido.

    void __fastcall TMain::ListBoxDragDrop(TObject *Sender, TObject *Source, 
    	int X, int Y)
    {
    	if( TListBox* listBox = dynamic_cast<TListBox*>(Sender) )
    	{
    		TWinControl* winCtrl = static_cast<TWinControl*>(Source);
    
    		if( listBox != winCtrl )
    		{
    			listBox->Items->Add(winCtrl->Name);
    			winCtrl->Visible = false;
    		}
    	}
    }

    void __fastcall TMain::FormDragDrop(TObject *Sender, TObject *Source,
    	int X, int Y)
    {
    	if( TForm* form = dynamic_cast<TForm*>(Sender) )
    	{
    		TControl* ctrl = 0;
    
    		if( TListBox* listBox = dynamic_cast<TListBox*>( Source ) )
    		{
    			for( int i = 0; i < listBox->Count; ++i )
    			{
    				if( listBox->Selected[i] )
    				{
    					ctrl = this->FindChildControl(listBox->Items->Strings[i]);
    					listBox->Items->Delete(i);
    					break;
    				}
    			}
    		}
    		else
    			ctrl = dynamic_cast<TControl*>(Source);
    
    		if( ctrl )
    		{
    			ctrl->Top = Y;
    			ctrl->Left = X;
    			ctrl->Visible = true;
    		}
    	}
    } 

E mais uma vez voilà! Pouquíssimas linhas de código e um movimentador e empilhador de controles. Dois detalhes merecem ser destacados:

 - O uso de dynamic_cast em cima dos ponteiros da VCL é uma maneira saudável de checar a integridade dos tipos recebidos - particularmente do Sender. O uso do primeiro parâmetro dos tratadores de eventos também torna o código menos preso à componentes específicos do formulário;
 - O método FindChildControl é deveras útil quando não temos certeza da existência de um controle. Geralmente é uma boa idéia confiar no sistema de gerenciamento de componentes da VCL. Não é à toa que existe um framework por baixo do ambiente RAD.