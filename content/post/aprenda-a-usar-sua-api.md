---
categories: [ "code" ]
date: "2008-07-22"
tags: [ "draft",  ]
title: "Aprenda a usar sua API"
---
É conhecido que uma das desvantagens de se programar diretamente em Win32 API é a dificuldade de se entender os parâmetros e o retorno das funções. Concordo em parte. Constituída de boa documentação, parte da culpa dos programas mal-feitos reside na preguiça do programador em olhar a documentação por completo.

A Win32 API está longe de ser perfeita, mas pelo menos está razoavelmente documentada, e é na leitura atenta da documentação que iremos encontrar as respostas que precisamos para que o programa funcione.

Vejamos alguns exemplos.

O código abaixo parece bem razoável:


No entanto, está errado.

É fato que a maioria das funções que retornam handles retornam NULL para indicar o erro na tentativa de obter o recurso. Ao comparar o retorno com NULL, o programador geralmente faz uma chamada a GetLastError.aspx) para saber o que aconteceu. No entanto, uma das funções mais usadas, a CreateFile, não retorna NULL, mas INVALIDHANDLEVALUE.

Sendo assim, o código acima deveria ser:


Taí uma função que muitos erraram. Erraram tanto que eles fizeram uma nova versão menos complicada. Como está escrito no MSDN.aspx):

"The GetVersionEx function was developed because many existing applications err when examining the packed DWORD value returned by GetVersion, transposing the major and minor version numbers."

O motivo de tantos erro pode ter sido o fato que o valor retornado é uma estrutura de bits dentro de um DWORD, coisa que nem todos programadores C sabem lidar muito bem, e o fato de ser uma função muito utilizada por todos (pegar a versão do sistema operacional).

Eis a tabela de campos do retorno de GetVersion:


Mesmo que não seja tão difícil, pode ser ambíguo. Por exemplo, como saber se o Windows é 95, 98 ou ME?

O código abaixo, muito usado por todos que suportam ainda o Windows mais velhinhos, verifica se estamos rodando em plataforma NT ou 9x.


Nem sempre o handle que obtemos é fechado com CloseHandle. As funções abaixo retornam handles que devem ser desalocados com as funções à direita:


Sempre tem. Algumas dicas úteis para o dia-a-dia de um programador Win32 API são:

  * Leia a documentação

  * Se atente aos valores de retorno em caso de sucesso e erro

  * Leia sempre a seção remarks pelo menos uma vez; ela explica como desalocar recursos

  * Releia a documentação

Às vezes uma singela chamada de uma função de autenticação pode nos fazer preencher uma estrutura de 20 membros, sendo que seis deles são obtidos com mais sete chamadas de funções, todas com direito a desalocar recursos no final. O importante é sempre manter a calma, o espírito de aprendizado e aventura. Afinal, quem mandou não fazer software de telinha?
