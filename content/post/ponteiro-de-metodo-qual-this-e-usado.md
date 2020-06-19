---
categories: [ "code" ]
date: "2007-11-07"
tags: [ "draft",  ]
title: "Ponteiro de método: qual this é usado?"
---
Depois de publicado o artigo anterior sobre ponteiros de métodos surgiu uma dúvida muito pertinente do autor do blogue CodeBehind, um escovador de bits disfarçado de programador .NET: qual objeto que vale na hora de chamar um método pelo ponteiro?

Isso me estimulou a desdobrar um pouco mais os mistérios por trás dos ponteiro de métodos e de membros, e descobrir os detalhes mais ocultos desse lado esotérico da linguagem.

Para entender por inteiro o que acontece quando uma chamada ou acesso utilizando ponteiros dependentes de escopo, algumas pequenas mudanças foram feitas no nosso pequeno FuzzyCall.


O novo código chama através do mesmo ponteiro o mesmo método (duh), mas através de três objetos diferentes. Se observarmos a saída veremos que cada instância da classe guardou uma pedra diferente do saco de bingo para si (até porque, no jogo do bingo, não é possível existir mais de uma pedra com o mesmo número):


Cada compilador e plataforma tem a liberdade de implementar o padrão C++ da maneira que quiser, mas o conceito no final acaba ficando quase a mesma coisa. No caso de ponteiros de métodos, o ponteiro guarda realmente o endereço da função que pertence à classe. Porém, como todo método não-estático em C++, para chamá-lo é necessário possuir um this, ou seja, o ponteiro para a instância:

Em assembly (comando "cl /Fafuzzycall3.asm fuzzycall3.cpp" para gerar a listagem), teremos algo assim:


Além do ponteiro de métodos, também é possível no C++ apontar para membros de um dado objeto. Para tanto, como vimos no código, basta declarar um tipo de ponteiro de membro de acordo com o tipo desejado:


Nesse caso, a técnica de usar o próprio enderenço não funciona, já que cada objeto possui um membro próprio em um lugar de memória próprio. Porém, assim como os ponteiros de métodos, os ponteiros de membros exigem um objeto para serem acessados, o que já nos dá a dica de onde o objeto começa. Sabendo onde ele começa, fica fácil saber onde fica o membro através do seu offset, ou seja, a distância dele a partir do início da memória do objeto. Só que para isso precisamos do offset armazenado em algum lugar. E adivinha onde que ele fica armazenado?


Podemos acompanhar este código no WinDbg (ou alguma outra IDE mais pomposa, se preferir) e veremos que o conteúdo do eax irá refletir o offset do membro dentro da classe FuzzyCall.


Como podemos ver, não é nenhuma magia negra a responsável por fazer os ponteiros de métodos e de membros funcionarem em C++. Porém, eles não são ponteiros ordinário que costumamos misturar a torto e a direito. Essa distinção na linguagem é importante para manter o código "minimamente sadio".
