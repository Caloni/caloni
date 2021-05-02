---
date: "2008-06-18"
categories: [ "code" ]
title: "Alinhamento de Memória Portável"
---
Como vimos durante o seminário CCPP, o alinhamento de memória pode ser problemático durante momentos críticos, como migração de plataforma (16 para 32 bits) e de ambiente (compilador novo). A forma como a memória é alinhada influi diretamente em algoritmos de criptografia ou de rede, para citar dois exemplos bem comuns, fazendo com que o que funcionava antes não funcione mais sem mexer uma única linha de código. Eu já vi isso. E isso não é bom.

A raiz do problema é que, dependendo do alinhamento usado pelo compilador, o sizeof de uma variável pode mudar de valor, mesmo que o tamanho útil não mude. Por exemplo, vamos supor que temos uma dada estrutura que iremos encriptar:

    struct S
    {
        /* 4 bytes */
        int size;

        /* 31 bytes */
        char name[31];
    };

    /* 4 + 31 = 35 bytes */

Se usarmos a construção "sizeof(struct S)", podemos obter o valor 35 caso o alinhamento seja feito em 1 byte, ou podemos obter o valor 40 se o alinhamento estiver configurado em 8 bytes. E é aí que começa o problema.

Já pensando nesse problema, os projetistas de vários compiladores suportam uma extensão não-padrão que permite definir, para um dado conjunto de estruturas e variáveis, o alinhamento que deve ser seguido. Isso de cara já resolve o problema, se sua solução usar apenas compiladores que suportem essa idéia. No Visual C++ essa idéia é traduzida pela diretiva pragma, que é definida no padrão C (6.8.6) e C++ (16.6). Seu uso não torna um programa não-padrão. No entanto, o que vai depois da diretiva é dependente da implementação e não é garantido que irá funcionar.

Usando essas diretivas ao compilador nossa estrutura sempre terá 40 bytes ocupados na memória, pois o alinhamento foi forçado em 8 bytes. Existem aqueles compiladores que não suportam essa idéia da mesma forma, ou não suportam de jeito nenhum. Para esses casos, alguns desvios de comportamento são necessários. A grande pergunta é se isso é possível de ser feito de forma 100% padrão. E, pelo que eu pude constatar, é possível, sim:

    #include <stdio.h>
    
    union Align
    {
      struct S
      {
        char buf[13];
        int x;
      }
      t;
    
      unsigned char align[
        sizeof(struct S) % 8 
        ?
        (sizeof(struct S) / 8 + 1) * 8
        :
        (sizeof(struct S))
      ];
    };

O código acima usa o conceito de união de estruturas (union) para fazer valer um alinhamento na marra (no caso, 8). Uma estrutura, como todos sabem, amontoa os seus membros um após o outro na memória. Dessa forma podemos tratar um bloco de memória com um leiaute que definimos com outros tipos. Em uma união, os membros não são amontoados um após o outro. Todos eles começam no mesmo ponto da memória. Eles se sobrescrevem. O tamanho da união sempre é o tamanho do seu maior membro, e não a soma de todos. É um tanto difícil de descrever esse leiaute, mas imagine que você tenha apenas uma posição na memória e queira chamá-la de vários nomes e tamanhos diferentes. Essa é a união.

Como deve ser fácil de imaginar, uma união não tem tanto uso quanto uma estrutura, mas ainda assim faz parte da linguagem. Ela possibilita enxergar a mesma região de memória sob vários ângulos. Podemos descobrir a organização de um inteiro na memória, por exemplo, byte a byte. Dependendo se a plataforma onde o programa acima é compilado, esse leiaute pode mudar. O motivo é que cada plataforma e compilador terá sua maneira de traduzir o código C na memória.

Agora que sabemos o que são uniões fica fácil entender o esquema da solução portável. A union acima simplesmente usa a segunda estrutura como uma auxiliar de alinhamento. Com ela do tamanho múltiplo do alinhamento desejado forçamos a união inteira a ter esse alinhamento, independente do tamanho da estrutura útil, a que iremos usar para armazenar os dados. Todo o resto é usado para alinhar na memória.

Tudo que temos que saber para fazer o alinhamento é o tamanho normal de nosso tipo útil (struct S). A partir desse valor deduzimos o próximo número que seja múltiplo de 8, através da seguinte construção:

    sizeof(struct S) % 8 
    ?
    (sizeof(struct S) / 8 + 1) * 8
    :
    (sizeof(struct S))

Ou seja, se S já for múltiplo de 8 é o próprio valor. Se não for, então dividimos por 8 e multiplicamos pelo mesmo valor adicionado de um, o que nos retorna o próximo múltiplo.

É lógico que, como se trata de uma construção onde temos completo domínio dos tipos e valores envolvidos, transformar isso em um template é "pedaço de torta".

    template<typename T, int A>
    union UAlign
    {
      T t;
    
      unsigned char align[
        sizeof(T) % A
        ?
        (sizeof(T) / A + 1) * A
        :
        (sizeof(T))
      ];
    };

E essa é a melhor parte de descobrir um padrão em um tipo: o template nasce quase que naturalmente. A beleza da linguagem floresce.
