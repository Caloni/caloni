---
categories: [ "code" ]
date: "2010-08-03"
tags: [ "draft",  ]
title: "Como achar o código-fonte sem símbolos"
---
Continuo escovando bits. Dessa vez de forma mais nervosa. Se trata de um serviço que trava durante seu stop. Um colega muito esperto do suporte gerou um dump para mim, tornando as coisas mais fáceis. O problema era que não havia símbolos nem código-fonte que batessem exatamente com aquela compilação de 2004. Solução? Analisar as pilhas das threads restantes.

É sabido que esse serviço responde requisições de milhares de máquinas em um período curto de tempo, então por isso a primeira coisa que me atentei foi verificar quantas threads haviam:


São muitas.

Analisar essa quantidade absurda de threads seria um saco. Além de inútil. Foi por isso deus inventou a função !uniqstack, que encontra automagicamente quais threads estão com a pilha duplicada.



Muitas threads duplicadas. Isso quer dizer que podemos nos focar na pilha de uma delas. Basta pegar uma.








Através das funções de RPC e OLE32 podemos concluir que se trata de uma chamada direta para uma interface COM. Bom, existem centenas de métodos e dezenas de interfaces nesse serviço, tornando mais fácil tentar desmontar a chamada inicial que o rpcrt4 faz ao nosso módulo.



Nossa função é obtida em ebp+8. Podemos obter esse endereço pelo campo ChildEBP da função em questão.


Note como a função compara algo com zero. Caso não seja zero ela continua. Caso contrário ela vai para um ponto que chama uma função interna e move um código de erro para um ponteiro recebido como parâmetro, o que é muito normal, se lembrarmos que as funções COM de um programa em C devem retornar o código da chamada no retorno (SOK) e o código de erro em um lResult da vida.


O código retornado é 2Fh, e agora temos uma boa pista para encontrar a localização no fonte. A primeira coisa é encontrar o define responsável por esse erro, o que exige um pouco de familiaridade com o sistema, pois não se trata aqui de um código Windows.


Ótimo. 2F, para os leigos (leigos? o que vocês estão fazendo aqui?), é 47 em decimal, exatamente nosso código listado acima. Com esse define podemos agora procurar no código-fonte e analisar todas as funções que retornam esse código em seu início. Para nossa sorte, existe apenas uma.


Para confirmar que não estamos sonhando, podemos dar uma olhada no parâmetro passado para a função Log antes do código retornar. A memória deverá conter uma string idêntica a do código-fonte.


E, agora sim, encontramos o culpado!

Mais para a frente em minha análise consegui encontrar o objeto pelo qual todas as threads esperavam. Não tive tanta sorte, pois se tratava de um mutex, e mutexes não conseguem ser rastreados tão facilmente em user mode. Mas isso não vem ao caso. O que tentei descrever aqui foi mais ou menos o processo que você deverá seguir caso tenha que analisar um binário compilado em outras vidas. Espero que você tenha tanta sorte quanto eu.
