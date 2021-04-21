---
date: "2020-06-07"
tags: [ "code" ]
title: "Leak de Memória"
---
Esse fim de semana vi um programa, sem leak de memória, que só de ficar alocando e desalocando apresentava um consumo crescente no Process Explorer. Imaginando que poderia ser alguma lib externa, como o redis, fui eliminando uma por uma as variáveis do sistema, até chegar em um loop em que a única coisa feita no corpo do código era alocar e desalocar memória. E ela apenas subia.

Essa memória é alocada para um objeto acessível por uma interface. Abaixo dessa abstração reside uma mensagem do protocol buffers, ainda na versão 2. Isso quer dizer que cada new e delete construía uma nova mensagem protobuf, além da vtable da interface, e destruía em seguida. Apenas um campo int era preenchido como teste. Para monitorar melhor a memória usei um segundo campo string, pois daí posso alocar quantos bytes quiser para ele e o gráfico do Process Explorer fica dando um berro que não dá para ignorar.

Então me veio o pensamento sobre a versão debug, que não é confiável. Uma versão debug de uma lib pode decidir que é importante manter coisas na memória que o programa não pediu, mas que é importante para diagnóstico. Então compilei a versão release. O padrão de consumo se repetiu, embora em um ritmo menor porque versão release é mais performática. O consumo crescente ainda estava aí.

O jeito foi ir destroçando o código, classe por classe, até fazer o padrão de consumo crescente estabilizar. Este projeto tem uma arquitetura complexa, cheia de interfaces e classes que manipulam dados internos através delas. É complicado destrinchar e me custou o domingo inteiro. E quando finalmente encontrei o problema, não tinha nada a ver com o que eu imaginava. Se tratava da fila de linhas de log que não eram apagadas porque o servidor de log não havia sido configurado no componente, e como ele nunca conectava, a lib de log decidia manter as linhas em memória até conseguir. Pode ser um erro de arquitetura ou uma decisão de segurança. De qualquer forma, não há leak. Apenas um sintoma.

Essa sessão de debugging me deu alguns insights, entre eles um que é sempre mais frequente: nunca supor nada antes de analisar um problema. Minha estratégia de dividir para conquistar sempre foi a única que gerou resultados rápidos, ainda que às custas de não confiar em minha intuição. A longo prazo essa estratégia é vencedora, pois a intuição não utilizada sem critérios fica mais afiada conforme você acumula conhecimento. É como o cara dos [Axiomas de Zurique] (o livro) dizia, intuição é um quase-conhecimento. Saber cada vez mais irá fazer com que você consiga caminhar mais rapidamente por onde quer chegar.

[Axiomas de Zurique]: /axiomas-de-zurique
