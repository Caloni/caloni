---
date: "2007-07-24"
title: "C++0x parcial no novo GCC 4.3"
tags: [ "blog" ]
---
A [nova versão do GCC] implementa em caráter de teste algumas novas características da nova versão da linguagem C++, que será lançada ainda nesta década (provavelmente em 2009). As novas funcionalidades são empolgantes e já fazem parte do imaginário dos programadores C++ já há algum tempo.

Atualmente temos duas maneiras de fazer asserções: usando a função assert (assert.h) ou utilizando a diretiva do pré-processador #error. Nenhum desses dois serve para emplates Para eles deverá ser definida a nova palavra-chave static_assert, que irá ser composta de dois parâmetros:

    static_assert( expressão-constante, literal-em-cadeia );

Podemos usá-la tanto no lugar da função assert quanto da diretiva #error. Mas seu uso mais interessante é como limite para a instanciação de emplates

    
    template<typename T>
    static_assert( sizeof(T) >= sizeof(int), "T is not big enough" )

Existem outros lugares onde esse novo comando pode ser usado. Para saber quando usá-lo, lembre-se que a verificação é feita durante a compilação, diferente do assert tradicional, que é chamada em tempo de execução.

Depois de todos esse anos o pré-processador sofrerá um upgrade. O objetivo é ser compatível com o novo padrão da linguagem C, o C99. A maior novidade fica por conta do número variável de parâmetros para macros. A linha abaixo resume tudo:
    
    #define TRACE(format, ...) printf(format, __VA_ARGS__)

Ou seja, não será mais necessário usar o truque dos "parênteses duplos" em macros de log que formatam parâmetros.

Considero a mudança dos templates com parâmetros variáveis a mais interessante. Com ela será possível usar um número variável de parâmetros em templates. Basicamente isso permite que um dado template aceite um número variável de parâmetros e esses parâmetros sejam "expandidos" em inúmeras construções dentro do escopo desse template. Nada melhor para explicar que um exemplo, como o caso da herança múltipla. Imagine um template que precisa herdar de seus parâmetros, mas não quer especificar a quantidade:

    template<typename... Bases> // quantidade definida pelo usuário
    class MyTemplate : public Bases...
    {

Outras pequenas correções também serão feitas para tornar a linguagem mais robusta:

 - Referências para lvalue.
 - Parâmetros default em funções-template.
 - Problema do fecha-templates duplo (>>).

Podemos esperar por outras grandes mudanças que irão ocorrer nesse novo padrão? Não exatamente. As principais estarão na biblioteca C++, com a inclusão de diversas classes e funções do projeto Boost. O resto são pequenas correções e melhorias de uma linguagem que, cá entre nós, já está bem poderosa e complexa.

[nova versão do GCC]: http://gcc.gnu.org/gcc-4.3/cxx0x_status.html
