---
date: "2010-11-09"
tags: [ "code", "draft",  ]
title: "Patch de emergência 2"
---
No artigo anterior fizemos um patch rapidinho na memória se aproveitando de um Sleep nojento que o código nos forneceu.

E se não houvesse Sleep?

As chances de estarmos escrevendo no momento em que a função está sendo executada são tremendas, de forma que não poderíamos sobrescrevê-la sem correr o risco de um crash.

Uma solução alternativa para isso é alocar um novo pedaço de memória para a versão corrigida e trocar o endereço de chamada na função main.



Antes de trocarmos o endereço dentro do main precisamos "consertar" a função copiada. Ela está usando as funções globais rand e printf, e as chamadas usam offsets relativos. Como agora a função está em outro offset, temos que reconstruir as chamadas:


Agora a função está pronta para ser usada.


É nessa parte que trocaremos o endereço o endereço 00401005 pela memória alocada. Note que essa escrita é muito rápida e o programa lê esse endereço por muito pouco tempo se compararmos com todas as intruções que são executadas. No entanto, essa escrita não é atômica, e mesmo que as chances sejam extremamente remotas, ainda assim pode haver uma colisão no acesso à essa parte.

É salutar rezar por 10 segundos.


E voilà! A partir do momento em que digitei o call seguido de enter, a função nova já começou a operar em cima do processo ainda rodando. Se quisermos voltar a função antiga, sem problemas:


Não façam isso em casa, crianças ;)
