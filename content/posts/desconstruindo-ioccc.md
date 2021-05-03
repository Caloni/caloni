---
categories:
- code
date: '2008-02-11'
title: Desconstruindo IOCCC
---

Como alguns devem saber, e outros não (ou não deveriam), existe uma competição internacional para escolher quem escreve o código em C mais ofuscado. Isso mesmo. O evento se chama [The International Obfuscated C Code Contest] (IOCCC resumidamente) e costuma premiar anualmente os melhores "do ramo" com a chamada "menção desonrosa".

Acredito que a real valia de um campeonato desse porte é fazer as pessoas pensarem mais a fundo sobre as regras da linguagem. Isso faz com que erros mais obscuros que encontramos no dia-a-dia se tornem mais fáceis. Claro que ninguém deveria programar como os caras desse torneio, mas a título de aprendizagem, é uma grande aula sobre C.

Publico aqui a interpretação do primeiro programa a ganhar a tal [menção desonrosa], em 1984. Se trata do batidíssimo "Hello World", só que um pouco compactado e confuso. Vejamos o fonte original:

    int i;main(){for(;i["]<i;++i){--i;}"];read('-'-'-',i+++"hell\
    o, world!\n",'/'/'/'));}read(j,i,p){write(j/p+p,i---j,i/i);}

Aparentemente o fonte é bem confuso, apesar de podermos já ver a famosa string escondida no meio do código. Depois de aplicar uma formatação mais adequada para nossa tarefa de desfazer o feito, o resultado é bem mais legível:

    int i;
    
    main()
    {
      for( ; i["] < i; ++i ){--i;}"]; read('-' - '-', i++ + "hello, world!\n", '/' / '/') )
        ;
    }
    
    read(j, i, p)
    {
      write(j / p + p, i-- - j, i / i);
    }

Algumas construções são óbvias. Vamos então partir para as não-tão-óbvias.

    int i;

Como toda variável global inteira, é inicializada com zero. Logo, a linha acima é equivalente a "int i =0".

    main() { }
    read() { }

Aos programadores C++ desavisados de plantão, em C o valor de retorno padrão é int, e, caso não seja retornado nada, isso não constitui um erro, porém o comportamento é não-definido. Nada de mal, porém, pode ocorrer, a não ser o retorno de lixo da pilha.

    for( ; <censurado>; <censurado> )
        ;

Outra coisa óbvia, mas não tanto, é um laço for sem corpo. Ele possui apenas um ponto-e-vírgula, que identifica uma instrução nula. Não faz nada no corpo, mas pode fazer coisas interessantes no cabeçalho, ou seja, na inicialização, no teste e no incremento. Como podemos ver, a inicialização também está vazia, contendo esse laço apenas o teste e o incremento. No teste temos a seguinte comparação:

    i["] < i; ++i ){--i;}"]

Ora, sabendo que a variável "i" inicialmente tem o valor zero, o que estamos vendo aqui é a mesma coisa que

    0["] < i; ++i ){--i;}"]

E uma vez que aprendemos algumas [peculiaridades sobre o operador de subscrito] em C, sabemos que a linha acima é equivalente a essa linha abaixo:

    "] < i; ++i ){--i;}"[0]

Agora ficou mais fácil de entender. Se trocarmos a nossa string literal por uma variável (forma mais usual), temos um acesso típico a um dos caracteres de uma string:

    char* str = "] < i; ++i ){--i;}";
    str[0];

Só precisamos lembrar que a variável i é que define a posição, e por ser uma variável, pode mudar durante a execução:

    int i = 0;
    char* str = "] < i; ++i ){--i;}";
    str[i];

Pois bem. Agora sabemos que o laço irá ser testado pelo menos uma vez, o que quer dizer que a parte do incremento vai executar pelo menos uma vez. E essa parte é a seguinte:

    read('-' - '-', i++ + "hello, world!\n", '/' / '/')

Uma chamada de função. Nada mais simples. Podemos anular algumas coisas por aqui. Por exemplo, se subtraímos um número dele mesmo encontramos zero, e se dividirmos um número por ele mesmo o resultado é um:

    '-' - '-' == 0
    '/' / '/' == 1

Lembre-se de que um caractere em C é um tipo inteiro, e portanto, pode fazer parte de cálculos matemáticos. Depois dessa simplificação, temos

    read(0, i++ + "hello, world!\n", 1)

Agora você deveria estar se perguntando (se ainda não encontrou a resposta) do porquê de eu ter dividido os três sinais de + dessa forma. Existem duas opções para a divisão:

    i++ + "hello, world!\n" /* ou */
    i+ ++"hello, world"\n"  /* ?? */

A primeira forma é a resposta correta devido à regra de precedência (deferida pela gramática). Antes os operadores unários, depois os binários. Dessa forma, um "i+" não quer dizer nada, mas "i++" é um operando com um operador unário.

Voltando à expressão, imagino que a essa altura você já deva ter decifrado que i++ + "hello, world!\n" é o mesmo que:

    char* str = "hello, world"\n";
    &str[i++];

Ou seja, obtemos o endereço do primeiro caractere da string e incrementamos nossa variável "i" que, como sabemos, é usada no teste do laço for. Na primeira vez, testamos se o primeiro caractere de "] < i; ++i ){--i;}" é diferente de zero. Na segunda iteração, portanto, iremos testar se o segundo caractere será zero. Sabendo disso, podemos deduzir que o laço irá correr por todos os caracteres da string de teste, até encontrar o zero finalizador de string. Ao mesmo tempo, iremos enviar para a função read sempre o endereço do i'ésimo caractere da string "hello, world!\n", pois essa string também é indexada pela variável "i".

Isso quer dizer que nosso laço irá terminar exatamente no final de ambas as strings! (Note, que para comparar as strings, usamos as strings originais do programa, sem melhorar a formatação).

    "] < i ; + + i ) { - - i ; }"
     1 2 3 4 5 6 7 8 9 0 1 2 3 4
    "h e l l o ,   w o r l d ! \n"

Também devemos lembrar que o caractere de controle '\n' é representado apenas por um byte, apesar de no fonte parecer dois.

Em um passado bem longínquo, o padrão ANSI C não existia, e outras funções dominavam o ambiente UNIX. Muitas dessas funções foram adaptadas, e outras completamente copiadas para a formação do padrão. No entanto, ainda que o padrão não tenha colocado algumas funções clássicas, elas continuaram sendo usadas e suportadas. Um bom exemplo disso são as funções read e write, que, apesar de não estarem no padrão, estão no [livro de K&R], no capítulo sobre fluxos (streams) em UNIX, provando que são bem populares.

Dentro desse mundo paralelo, existem identificadores de fluxos padrões para a entrada e a saída padrão. Melhor ainda, esses identificadores são inteiros que estão especificados da seguinte maneira (tirado da [referência GNU] da linguagem C, meu grifo):

> There are also symbolic constants defined in unistd.h for the file descriptors belonging to the standard streams stdin, stdout, and stderr; see Standard Streams.
> 
> STDIN_FILENO
> This macro has value 0, which is the file descriptor for standard input.
>
> STDOUT_FILENO
> This macro has value 1, which is the file descriptor for standard output.
>
> STDERR_FILENO
> This macro has value 2, which is the file descriptor for standard error output.

Agora podemos voltar ao fonte. Vejamos como é implementada a função read, chamada dentro do laço for. Como todos sabem, se uma função já é definida em sua própria unidade, não haverá uma busca por referências externas, o que quer dizer que a implementação padrão de read não atrapalha a implementação local.

    read(j, i, p)
    {
      write(j / p + p, i-- - j, i / i);
    }

Ótimo. A função read chama a função (essa sim, padrão) write. Sabemos que tanto o primeiro quanto o último parâmetro da função será sempre constante no laço for:

    read(0, i++ + "hello, world!\n", 1)

O que quer dizer que o primeiro argumento passado para write será sempre o mesmo:

    j == 0;
    p == 1;
    j / p + p == 1;

Além da constante óbvia passada no último argumento:

    i / i = 1; /* independente de i */

Isso quer dizer que a chamada para write pode ser resumida para:

    write(1, i-- - j, 1);

O decremento da variável "i" (dentro de read) nunca é usado, uma vez que é uma variável local. E subtrair "j" é inócuo, uma vez que o valor de "j" será sempre zero. Logo, o argumento do meio é sempre o parâmetro do meio, por mais idiota que isso possa parecer =)

    write(1, i, 1);

Pronto, já temos condições de interpretar o significado dessa chamada à write. Como já vimos, o número 1 identifica a saída padrão, o que quer dizer que estamos escrevendo algo na saída padrão. Esse algo é o parâmetro "i" que, como vimos, é o endereço do i'ésimo caractere da string "hello, word!\n". O último argumento é o número de bytes a serem escritos, que será sempre um. O que quer dizer que o laço em for chamada a função read strlen("hello, world!\n") vezes passando o endereço do próximo caractere de cada vez. A função read, por sua vez, escreve este caractere na saída padrão. O resultado, como todos que compilarem o fonte e rodarem poderão comprovar, é a impressão da mensagem mais famosa do mundo da computação:

    hello, world!

E voilà =)

Abaixo um código-fonte equivalente, devidamente desencriptado:

    int i = 0;
    
    main()
    {
      char* indexString = "]<i;++i){--i;}";
      char* outputString = "hello, world!\n";
    
      for( ; indexString[i] != 0; read(&outputString[i++]) )
        ;
    }
    
    read(outStr)
    {
      write(1, outStr, 1);
    }

[The International Obfuscated C Code Contest]: http://www.ioccc.org
[menção desonrosa]: http://www.ioccc.org/1984/anonymous/anonymous.c
[peculiaridades sobre o operador de subscrito]: /curiosidades-inuteis-o-operador-de-subscrito-em-c
[livro de K&R]: /the-c-programming-language
[referência GNU]: http://www.gnu.org/software/libc/manual/html_node/Descriptors-and-Streams.html#index-STDIN_005fFILENO-1235