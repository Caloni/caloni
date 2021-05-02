---
date: "2007-12-17"
title: "Sizeof (de novo)"
categories: [ "code" ]
---
Algumas coisas em C parecem tão simples na programação do dia-a-dia que em alguns momentos podem existir situações confusas e misteriosas. O uso obscuro do operador sizeof, por exemplo, pode dar margem a interpretações erradas a respeito do que está acontecendo por debaixo dos panos. Apesar do padrão ter sido elaborado para tentar tornar a linguagem uma coisa intuitiva e de fácil dedução, isso não acontece todas as vezes.

Vamos tomar, por exemplo, o seguinte minicódigo:

    size_t len = sizeof("A simple string");
    memcpy(buf, "A simple string", len);

A pergunta ingênua: quantos bytes são copiados para buf?

A resposta ingênua: er... o tamanho de "A simple string"?

Agora vamos supor que você é um pouco mais esperto e começa a pensar: "mas, peraí, estou passando na realidade um ponteiro para sizeof, o que quer dizer que, se meus cálculos estiverem corretos, e estivermos em uma plataforma de 32 bits, sizeof deve retornar 4, o que quer dizer que acabei de achar um bug escabroso, uhuu!".

Muito bem, o raciocínio é perfeito. Afinal de contas, "A simple string" é um ponteiro para um array de caracteres terminados em zero, certo?

Estou quase certo disso. Porém, isso quer dizer que já deixei vários bugs escabrosos há uns 4 anos atrás em trechos de código parecidos com esse. Será que eu estava errado e não me dei conta, ou sabia de algo que esqueci faz muito tempo?

Eu e meu amigo demos uma olhada no padrão da linguagem C de 89 (revisão de 90), que diz duas coisas muito importantes nesse momento: o que é um sizeof e o que é uma string constante (chamada no padrão de string literal):

> #### Sizeof (6.3.3.4)
>
> The sizeof operator yields the size (in bytes) of its operand, which may be an expression or the parenthesized name of a type. The size is determined from the type of the operand, which is not itself evaluated. The result is an integer constant.
>
> #### String literal (6.1.4)
> 
> A character string literal is a sequence of zero or more multibyte characters enclosed in double-quotes, as in "xyz". A wide string literal is the same, except prefixed by the letter L. (...) The multibyte character sequence is then used to initialize an array of static storage duration and lenght just sufficient to contain the sequence.

Em C++ (padrão ISO de 98) o texto é muito parecido, apenas abragendo também o conceito de type-id (desnecessário explicar para o contexto deste artigo):

> 
> #### Sizeof (5.3.3)
> 
> The sizeof operator yields the number of bytes in the object representation of its operand. The operand is either an expression, which is not evaluated, or a parenthesized type-id.
> 
> #### String literal (2.13.4)
> 
> A string literal is a sequence of characters (as defined in 2.13.2) surrounded by double quotes, optionally beginning with the letter L, as in "..." or L"...". (...) An ordinary string literal has type "array of n const char" and static storage duration (...).

Esses textos do padrão demonstram que o operador sizeof irá retornar o número de bytes baseado no tipo do operando, e que o tipo de uma string literal é de array de caracteres com o tamanho justo para caber a string.

Bem, todos sabemos o resultado das linhas abaixo:

    char charArray[100];
    size_t len = sizeof(charArray);

Nesse caso é simples de observar que o operador sizeof irá retornar 100, que é o número em bytes para abrigar o tipo do operando, que é de "array de 100 caracteres". Podemos, então, imaginar que a nossa idiomática expressão do início é no fundo um resumo das linhas que se seguem.

    ...
    static char aSimpleString[] = "A simple string";
    ...
    size_t len = sizeof(aSimpleString);
    memcpy(buf, aSimpleString, len);

Ou seja, o tipo de nossa string é na verdade de array estático de caracteres, como se uma variável tivesse sido definida anteriormente com o conteúdo da string, que deve estar em algum lugar da memória do programa. Visto dessa forma fica bem mais simples de entender o que acontece na versão resumida.

O mais encorajador desse problema do sizeof é que a resposta ingênua estava certa, ou seja, pelo menos dessa vez, o padrão conseguiu através de suas regras seguir a intuição do programador.
