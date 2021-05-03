---
categories:
- code
- ccpp
date: '2012-05-20'
title: Sobrecarga de função às avessas
---

> Nota do autor: navegando pelo Archive.org, que possibilita viajar no tempo e encontrar coisas enterradas que seria melhor deixar por lá, consegui encontrar um post que se perdeu na dobra espaço-temporal entre o old-fashioned Caloni.com.br (com direito à velha joaninha psicodélica, desenho do meu amigo que uso até hoje no blogue) e um finado outro domínio meu, o CThings. No final, consegui [matar a marmota], chegar a [80 milhas por hora] e voltar para o presente. Enjoy!

Alguém já se perguntou se é possível usar sobrecarga de função quando a diferença não está nos parâmetros recebidos, mas no tipo de retorno? Melhor dizendo, imagine que eu tenha o seguinte código:

    void CreateNewGUID(wstring&);
    void CreateNewGUID(GUID&);

    GUID guid;
    wstring guidS;

    CreateNewGUID(guidS);
    CreateNewGUID(guid);

É um uso sensato de sobrecarga. Mas vamos supor que eu queira uma sintaxe mais intuitiva, com o retorno sendo atribuído à variável:

    wstring CreateNewGUID();
    GUID CreateNewGUID();

    GUID guid;
    wstring guidS;

    guid = CreateNewGUID();
    guidS = CreateNewGUID();

Voltando às teorias de C++ veremos que o código acima NÃO funciona. Ou, pelo menos, não deveria. Só pelo fato das duas funções serem definidas o compilador já reclama com um "error C2556: 'GUID CreateNewGUID(void)': overloaded function differs only by return type from 'std::wstring CreateNewGUID(void)'". E obviamente ele está correto. O tipo de retorno não é uma propriedade da função que exclua a ambiguidade em sua chamada. Apenas a assinatura pode fazer isso (que são os tipos dos parâmetros recebidos pela função).

Como não podemos utilizar funções ordinárias o jeito é criar nosso próprio tipo de função que dê conta do recado usando a sobrecarga do operador de conversão de tipos. O operador de conversão suporta sobrecarga porque é na conversão que o compilador decide qual função chamar.

    struct CreateNewGUID
    {
      operator wstring ();
      operator GUID ();
    }; 

    guid = CreateNewGUID();
    guidS = CreateNewGUID();

Agora com o novo tipo CreateNewGUID é possível chamá-lo como uma função, o que na prática cria uma nova instância da struct. Ao atribuir o retorno dessa instância a uma variável do tipo wstring ou GUID os operadores de conversão serão requisitados, cada um dependendo do tipo da variável a qual será atribuído o retorno.

Uma vez que criamos um novo tipo, e considerando que este tipo é, portanto, diferente dos tipos wstring e GUID já existentes, devemos simplesmente converter nosso novo tipo para cada um dos tipos de retorno desejados:

    struct CreateNewGUID
    {
      operator wstring ()
      {
        wstring ret;
        // cria guid
        return ret;
      }

      operator GUID ()
      {
        GUID ret;
        // cria guid
        return ret;
      }
    };

E isso conclui a solução meio esquizofrênica de nossa sobrecarga às avessas. E voltando à pergunta original, penso que, com criatividade e C++, nada é impossível. =)

[matar a marmota]: /feitico-do-tempo
[80 milhas por hora]: /de-volta-para-o-futuro