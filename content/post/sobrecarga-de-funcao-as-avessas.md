---
categories: [ "code" ]
date: "2012-05-20"
tags: [ "draft",  ]
title: "Sobrecarga de função às avessas"
---
> Navegando pelo Archive.org, que possibilita viajar no tempo e encontrar coisas enterradas que seria melhor deixar por lá, consegui encontrar um post que se perdeu na dobra espaço-temporal entre o old-fashioned Caloni.com.br (com direito à velha joaninha psicodélica, desenho do meu amigo t@z) e o finado CThings. No final, consegui matar a marmota, chegar a 80 milhas por hora e voltar para o presente. Enjoy it!

Alguém já se perguntou se é possível usar sobrecarga de função quando a diferença não está nos parâmetros recebidos, mas no tipo de retorno? Melhor dizendo, imagine que eu tenha o seguinte código:

    GUID guid;
    wstring guidS;
    
    CreateNewGUID(guidS); // chama void CreateNewGUID(wstring&)
    CreateNewGUID(guid); // chama void CreateNewGUID(GUID&) (o compilador sabe disso)
    // Codigo-fonte disponivel no GitHub https://github.com/Caloni/Caloni.com.br.
    

É um uso sensato de sobrecarga. Mas vamos supor que eu queira uma sintaxe mais intuitiva, com o retorno sendo atribuído à variável:

    GUID guid;
    wstring guidS;
    
    guidS = CreateNewGUID(); // chama wstring CreateNewGUID()
    guid = CreateNewGUID(); // chama GUID CreateNewGUID() (o compilador sabe disso?)
     
    

Voltando às teorias de C++, veremos que o código acima NÃO funciona. Ou, pelo menos, não deveria. Só pelo fato das duas funções serem definidas o compilador já reclama:

        error C2556: 'GUID CreateNewGUID(void)' :
        overloaded function differs only by return type from 'std::wstring CreateNewGUID(void)'

Correto. O tipo de retorno não é uma propriedade da função que exclua a ambigüidade. Apenas a assinatura pode fazer isso (que são os tipos dos parâmetros recebidos pela função).

Pois bem. Não podemos fazer isso utilizando funções ordinárias. Então o jeito é criar nosso próprio "tipo de função" que dê conta do recado:

    struct CreateNewGUID
    {
       // o que vai aqui?
    }; 
    

Pronto. Agora podemos "chamar" a nossa função criando uma nova instância e atribuindo o "retorno" a wstring ou à nossa GUID struct:

    guidS = CreateNewGUID(); // instancia um CreateNewGUID
    guid = CreateNewGUID(); // instancia um CreateNewGUID. A diferença está no "retorno" 
    

Uma vez que criamos um novo tipo, e considerando que este tipo é, portanto, diferente dos tipos wstring e GUID já existentes, devemos simplesmente converter nosso novo tipo para cada um dos tipos de retorno desejados:

    struct CreateNewGUID
    {
       operator wstring () { ... } // a conversão é a "chamada da função".
    
       operator GUID () { ... } // E como existem duas conversões... sobrecarga!
    }; 
    

E isso conclui a solução meio esquizofrênica de nossa sobrecarga às avessas:

    // instancia um CreateNewGUID e chama CreateNewGUID::operator wstring()
    guidS = CreateNewGUID();
    
    // instancia um CreateNewGUID e chama CreateNewGUID::operator GUID()
    guid = CreateNewGUID(); 
    

Eis o fonte completo:

    #include <windows.h>
    #include <objbase.h>
    
    #include <iostream>
    #include <string>
    
    using namespace std;
    
    struct CreateNewGUID
    {
       operator wstring ()
       {
          GUID guid = operator GUID();
          OLECHAR buf[40] = { };
          ::StringFromGUID2(guid, buf, sizeof(buf));
          return wstring(buf);
       }
    
       operator GUID ()
       {
          GUID guid = { };
          ::CoCreateGuid(&guid);
          return guid;
       }
    };
    
    int _tmain(int argc, _TCHAR* argv[])
    {
       wstring guidS;
       GUID guid;
    
       // instancia um CreateNewGUID e chama CreateNewGUID::operator wstring()
       guidS = CreateNewGUID();
    
       // instancia um CreateNewGUID e chama CreateNewGUID::operator GUID()
       guid = CreateNewGUID();
    
       wcout << L"Pra nao dizer que esse exemplo nao imprime nada:\n"
             << guidS << L'\n';
    
       return 0;
    } 
    

Voltando à pergunta original: penso que, com criatividade e C++, nada é impossível =)
