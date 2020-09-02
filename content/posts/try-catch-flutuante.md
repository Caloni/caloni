---
date: "2008-04-03"
tags: [ "code", "draft",  ]
title: "Try-catch flutuante"
---
Esse detalhe da linguagem quem me fez descobrir foi o Yorick, que costuma comentar no blogue (na época que o blogue tinha comentários) e tive o prazer de conhecer no 4o. EPA-CCPP.

É possível, apesar de bizarro, colocar um bloco try-catch em torno da lista de inicialização de variáveis de um construtor. Essa característica da linguagem permite que possamos capturar alguma exceção lançada por algum construtor de algum membro da classe. A construção em código ficaria no estilo abaixo:


Apesar dessa capacidade, não conseguimos parar o lançamento da exceção. Após seu lançamento, caímos no bloco catch abaixo do corpo do construtor e a exceção é lançada novamente, como se houvesse uma intrução throw no final do catch.

O exemplo abaixo demonstra um código de uma classe que captura a exceção durante a inicialização dos membros. Na seguida o catch da função main é executada, provando que a exceção de fato não é "salva" no primeiro bloco.


Testei esse código nos seguintes compiladores:

  * Visual Studio 6. Falhou, demonstrando desconhecer a sintaxe.

  * Borland C++ Builder 5. Falhou, demonstrando desconhecer a sintaxe.

  * Borland Developer Studio 4. Falhou, com o mesmo erro.

  * Visual Studio 2003. Comportamento esperado.

  * Visual Studio 2005. Comportamento esperado.

  * Visual Studio 2008. Comportamento esperado.

  * G++ (no Cygwin). Comportamento esperado.

A saída esperada é a seguinte:

