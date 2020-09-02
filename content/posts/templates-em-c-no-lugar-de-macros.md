---
date: "2016-01-14"
tags: [ "code", "draft",  ]
title: "Templates em C no lugar de macros"
---
A grande vantagem dos templates é manter o tipo de seus argumentos. Infelizmente, eles não existem na linguagem C, mas podem ser usados em construções C feitas com a linguagem C++, como ocorre com quem desenvolve device drivers para Windows.

Imagine, por exemplo, a estrutura LISTENTRY.aspx), que é uma tentativa de generalizar não só o tipo de uma lista ligada, como seu posicionamento:


A lógica por trás de LISTENTRY é que esse membro pode ser inserido em qualquer lugar da estrutura que representará um elemento. Ele pode estar realmente no meio do elemento, pois isso não importa, desde que você saiba voltar para o começo da estrutura. Isso é útil quando um elemento pode fazer parte de diferentes listas.


OK, temos uma lista ligada cujo head está inicializado. Para inserir um novo item, podemos usar as rotinas InsertHeadList, AppendTailList, RemoveEntryList, PushEntryList, PopEntryList, etc. Enfim, uma infinidade de rotinas já cuidam disso para a gente.

O que não temos é como acessar o elemento. Para isso usamos um truque bem peculiar na linguagem C, já disponível também em kernel:


Basicamente a macro obtém a partir do endereço zero o offset do membro que é a entrada da lista ligada e subtrai esse ofsset do endereço do próprio campo, ganhando de brinde o tipo de sua estrutura. Usando a macro com nossa estrutura:


Note que entry é o nome, literal, do membro na estrutura, e não há maneira possível com templates de obter isso. A solução? Usar um nome padronizado. O resultado final pode ser parecido com este:


Em ação:


"Nossa, tudo isso para substituir uma macro já consagrada no WDK??" Sim, nesse post o objetivo não ficou muito útil. É apenas uma ideia de substituição possível de ser feita em macros em geral. Pode ser bem documentada, usada há 30 anos, mas ainda é uma macro. Meu conselho: se funciona bem, use. Se vai fazer algo novo, tente sempre templates.
