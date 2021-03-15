---
date: "2007-12-03"
title: "Conceitos básicos na programação com C++ Builder"
tags: [ "code" ]
---
No projeto que é criado quando iniciamos a IDE três arquivos-fonte são gerados: Project1.cpp, Unit1.cpp e Unit1.h. Desses três, vamos analisar o primeiro:

    #include <vcl.h>
    
    WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
    {
    	try
    	{
    		Application->Initialize();
    		Application->CreateForm(__classid(TForm1), &Form1);
    		Application->Run();
    	}
    	//...
    
    	return 0;
    } 

Sim, existe um WinMain e ele não está escondido! Nele você pode fazer o que quiser. A IDE apenas auxilia você a gerenciar seus forms. Note que também existe a inclusão de um cabeçalho chamado vcl.h (obrigatório), o que nos leva diretamente para a base de toda a programação Delphi/Builder.

A VCL é o framework usado tanto no Builder quanto no Delphi para a programação RAD nesses ambientes. Considere como a MFC geração C++ da Borland (antes era o OWL). Todos os controles que você vê na paleta da IDE - Button, Label, CheckBox, Timer - são criados e gerenciados através da VCL. Com os mesmos nomes acrescidos do prefixo T (TButton, TCheckBox...) você tem as classes que representam em código o que você vê no ambiente RAD. Através da VCL pode-se criar novos componentes estendidos dos originais, e eles serão gerenciados pela IDE, que aliás é feita usando VCL.

Voltando ao código: o Application é um objeto visível em todo os módulos do processo e representa a aplicação em execução. Através dele você cria e destrói forms e inicia a execução da VCL. Ah, sim, é bom lembrar que todos os objetos VCL devem ser criados no heap (usando o operador new ou algum método de um objeto VCL já criado, como o CreateForm do Application). Essa e mais algumas restrições foram impostas na criação de classes VCL para que seu comportamento fosse similar/compatível com tecnologias como COM e CORBA (além das vantagens do polimorfismo e gerenciamento automático de objetos).

Olhando para o outro fonte, Unit1.h, podemos ver a definição da classe que representa o form principal:

    class TForm1 : public TForm
    {
    __published: // IDE-managed Components
    private: // User declarations
    public:  // User declarations
    	__fastcall TForm1(TComponent* Owner);
    };
    
    extern PACKAGE TForm1 *Form1; 

A classe deriva de TForm, que é uma classe da VCL que representa uma janela padrão do Windows. Como se nota, um objeto da classe é criado automaticamente, exatamente o utilizado no WinMain para a criação da janela principal.

Na classe existe um escopo estendido chamado published. Nele são colocados os membros da classe que podem ser gerenciados pela IDE. Considere como um public dinâmico. Coloque um TButton no form e note que um novo membro é criado na classe, dentro do escopo gerenciado pela IDE:

    __published: // IDE-managed Components
    TButton *Button1;

Esses membros são iniciados automaticamente pela VCL. Contudo, você ainda pode criar objetos em tempo de execução e entregar o gerenciamento de seu tempo de vida para a VCL (o que significa chamar new e nunca um delete). Para essa proeza, todos os construtores de componentes devem receber um ponteiro para o seu Owner, que será o responsável por destruir o objeto. Veja como é ridículo criar um controle novo e definir algumas propriedades:

    void __fastcall TForm1::Button1Click(TObject *Sender)
    {
    	TButton* btn2 = new TButton(this); // this é o meu form
    
    	btn2->Parent = this; // será o owner e o parent do novo botão
    	btn2->SetBounds(10, 10, 150, 25); // definindo as fronteiras dentro do form
    	btn2->Caption = "Prazer! Sou dinâmico!";
    	btn2->Visible = true;
    } 

O Parent é o component que abriga a representação visual do objeto dentro de si. Parent e Owner são dois conceitos distintos. Pra frente veremos como as janelas são gerenciadas pela VCL e pela IDE.

É claro! O Borlando C++ Builder é coisa do passado, assim como Delphi e VB como os conhecemos. A versão nova do C++ Buider chama-se Turbo C++ (até semana passada, pelo menos). Nele as coisas são iguais mas diferentes. Ou seja, os conceitos aqui apresentados ainda valem. Só estão com uma cara diferente.
