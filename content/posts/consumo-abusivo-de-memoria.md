---
date: "2012-05-19"
tags: [ "code", "draft",  ]
title: "Consumo abusivo de memória"
---
Era um belo dia em um ambiente de processamento fictício de filas fictícias e threads fictícias. Eis um belo código com filas, threads e processamentos feitos em stop-motion:


Se olharmos de perto o processamento e a memória consumida por esse processo, veremos que no início existe um boom de ambos, mas após um momento de pico, o processamento praticamente pára, mas a memória se mantém:

Depois de pesquisar por meus tweets favoritos, fica fácil ter a receita para verificarmos isso usando nosso depurador favorito: WinDbg!

windbg -pn MemoryConsumption.exe

Achamos onde está a memória consumida. Agora precisamos de dicas do que pode estar consumindo essa memória. Vamos começar por listar os chunks alocados por tamanho de alocação:



O Top 3 é de tamanhos conhecidos pelo código, de 1024 a 1024 + QUEUESSIZE - 1. O de tamanho 1037, por exemplo, possui 0x25e5 blocos alocados. Vamos listar cada um deles:


A listagem do depurador nos dá o endereço onde o chunk foi alocado no heap e o endereço devolvido para o usuário, onde colocamos nossas tralhas. Através de ambos é possível trackear a pilha da chamada que alocou cada pedaço de memória. Isso, claro, se previamente tivermos habilitado essa informação através do GFlags.aspx):


Dessa forma temos onde cada memória foi alocada, o que nos dará uma informação valiosa, dependendo qual o tipo de problema estamos tentando resolver.


Outra informação relevante é o que está gravado na memória, que pode nos dar insights de que tipo de objeto estamos lidando:


Não é o caso, mas vamos supor que fosse um objeto/tipo conhecido. Poderíamos simplesmente "importar" o tipo diretamente do PDB que estamos para modelar a memória que encontramos em volta. Mais detalhes em outro artigo.

  * CreateThread.aspx). Cria uma nova linha de execução.

  * WaitForMultipleObjects.aspx). Pode aguardar diferentes linhas de execução terminarem.

  * std::list. Lista na STL para inserir/remover objetos na frente e atrás (ui).

  * Initialize.aspx), Enter.aspx) e LeaveCriticalSection.aspx). Uma maneira simples de criar blocos de entrada atômica (apenas uma thread entra por vez).

  * memset. Se você não sabe usar memset, provavelmente não entendeu nada desse artigo.

