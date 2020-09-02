---
date: "2008-01-30"
tags: [ "code", "draft",  ]
title: "Compartilhando variáveis com o mundo"
---
Desde que comecei a programar, para compartilhar variáveis entre processo é meio que consenso usar-se a milenar técnica do crie uma seção compartilhada no seu executável/DLL. Isso funciona desde a época em que o Windows era em preto e branco. Mas, como tudo em programação, existem mil maneiras de assar o pato. Esse artigo explica uma delas, a não-tão-milenar técnica do use memória mapeada nomeada misturada com templates.

Era comum (talvez ainda seja) fazer um código assim:


Aquele pragma do começo garante que qualquer instância do mesmo executável, mas processos distintos, irão compartilhar qualquer variável definida dentro da seção "shared". O nome na verdade não importa muito - é apenas usado para clareza - , mas o atributo do final, sim.

Algumas desvantagens dessa técnica são:

  * Não permite compartilhamento entre executáveis diferentes, salvo se tratar-se de uma DLL carregada por ambos.

  * É um compartilhamento estático, que permanece do início do primeiro processo ao fim do último.

  * Não possui proteção, ou seja, se for uma DLL, qualquer executável que a carregar tem acesso à área de memória.

Muitas vezes essa abordagem é suficiente, como em hooks globais, que precisam apenas de uma ou duas variáveis compartilhadas. Também pode ser útil como contador de instâncias, do mesmo jeito que usamos as variáveis estáticas de uma classe em C++ (vide sharedptr do boost, ou a CString do ATL, que usa o mesmo princípio).

Houve uma vez em que tive que fazer hooks direcionados a threads específicas no sistema, onde eu não sabia nem qual o processo host nem quantos hooks seriam feitos. Essa é uma situação onde fica muito difícil usar a técnica milenar.

Foi daí que eu fiz um conjunto de funções alfa-beta de compartilhamento de variáveis baseado em template e memória mapeada:


Como pode-se ver, o seu funcionamento é muito simples: uma função-template que recebe uma referência para um ponteiro de ponteiro do tipo da variável desejada, o seu nome global e retorna uma variável alocada na memória de cachê do sistema. Como contraparte existe uma função que abre essa memória baseada em seu nome e faz o cast (coversão de tipo) necessário. Ambas as chamadas devem chamar uma terceira função para liberar o recurso.

O segredo para entender mais detalhes dessa técnica é pesquisar as funções envolvidas: CreateFileMapping, OpenFileMapping, MapViewOfFile e UnmapViewOfFile. Bem, o CloseHandle também ;)

Ah, é mesmo! Fiz especialmente para o artigo:


Preciso lembrar que essa é uma versão inicial ainda, mas que pode muito bem ser melhorada. Duas idéias interessantes são: parametrizar a proteção da variável (através do SECURITYATTRIBUTES) e transformá-la em classe. Uma classe parece ser uma idéia bem popular. Afinal, tem tanta gente que só se consegue programar se o código estiver dentro de uma.

  * MSDN Library - by Microsoft

  * Code Project - by Developers

  * Google - by Google

