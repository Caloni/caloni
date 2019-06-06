---
date: "2009-01-30"
title: As funções-polegar
categories: [ "code" ]
---
Como já havia dito, não há nada mais prazeroso do que [ensinar a alguém](http://www.caloni.com.br/basico-do-basico-ponteiros) os velhos truques da profissão e relembrar o porquê de tantas coisas que guardamos na cabeça sobre programação. Hoje tive a oportunidade de explicar como funcionam as funções-polegar.

A função-polegar, uma categoria de função muito peculiar em várias APIs, possui um comportamento padrão de retorno de erros. Entre as diversas funções-polegar que conheço e uso, eis algumas que lembro de cor:

	
  * [read](https://www.opengroup.org/onlinepubs/000095399/functions/read.html), [write](https://www.opengroup.org/onlinepubs/000095399/functions/write.html) (C)

	
  * [connect](http://msdn.microsoft.com/en-us/library/ms737625(VS.85).aspx), [send](http://msdn.microsoft.com/en-us/library/ms740149(VS.85).aspx) (Sockets)

	
  * [ReadFile](http://msdn.microsoft.com/en-us/library/aa365467(VS.85).aspx), [WriteFile](http://msdn.microsoft.com/en-us/library/aa365747(VS.85).aspx), [CreateProcess](http://msdn.microsoft.com/en-us/library/ms682425.aspx) (Win32)

O que todas essas funções têm em comum? Bom, ignorando seu funcionamento interno ou seu objetivo, todas elas possuem um **valor de retorno** no estilo sim ou não, ou seja, deu certo ou não deu. Nessas funções o código de erro, o motivo da função não ter dado certo, não é retornado diretamente. É o que chamo de esquema do **polegar pra cima** ou **polegar pra baixo**. O retorno da função especifica o ângulo giratório do dedão:

	
  * **ssize_t** pread, **ssize_t** write. Retorno de -1 significa que deu algo errado.

	
  * **int** connect, **int** send. Se retornar SOCKET_ERROR

	
  * **BOOL** ReadFile, **BOOL** WriteFile, **BOOL** CreateProcess. TRUE sucesso, FALSE erro.

Por exemplo, chamamos a função ReadFile para ler um arquivo. Ela retorna FALSE. Isso significa que não deu certo nossa leitura. Por quê? Ora, não sabemos ainda. Apenas sabemos que o polegar está virado para baixo!

[](http://en.wikipedia.org/wiki/Thumbs_up)

[![Thumbs Down](http://i.imgur.com/bywKcxF.jpg)](http://en.wikipedia.org/wiki/Thumbs_up)

Em funções nessas condições, geralmente existe uma **segunda função (ou variável)** que retorna o último erro que ocorreu na API, ou seja, o erro que fez com que última função chamada retornasse que algo não deu certo. Nas funções de exemplo, são usados três métodos distintos, pois estamos falando de três APIs distintas:

	
  * Variável [errno](http://www.opengroup.org/onlinepubs/009695399/functions/errno.html)

	
  * Função [WSAGetLastError](http://msdn.microsoft.com/en-us/library/ms741580(VS.85).aspx)

	
  * Função [GetLastError](http://msdn.microsoft.com/en-us/library/ms679360(VS.85).aspx)

São esses métodos que realmente retornam **o porquê** da função ter dado errado. E é elas que devemos chamar, eu disse **devemos** chamar, sempre que a função der errado. Até porque, já que o polegar está virado para baixo, temos que fazer alguma coisa para que nosso programa não morra.

#### Atualização

Como bem observado pelo Fernando no comentário abaixo, nem todas as funções-polegar possuem uma função para obter a causa do erro. Vide **SysAllocString**, ou mesmo **malloc**. Nesse caso, não há muito o que determinar a não ser que não foi possível alocar o recurso pedido pelo sistema. Paciência.
