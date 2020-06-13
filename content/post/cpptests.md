---
categories: [ "blog" ]
date: "2017-07-25"
tags: [ "draft", "tools" ]
title: "CppTests"
---
Iniciei um novo projeto no GitHub que tem por objetivo ser minha prancheta de trabalhos para minha palestra no próximo encontro ccpp. Há uma infinitude de coisinhas novas na linguagem C++, fora as adições à biblioteca STL, mas que devem passar despercebidas da maioria dos programadores, que está mais é querendo terminar seus próprio projetos. Enquanto alguns conceitos, sintaxes e métodos não se solidificam, vale a pena dar uma espiada no futuro?

Depende.

Dei uma olhada nas últimas modificações adicionadas no Visual Studio 2017 (versão 15.3 preview 1, mas o último lançado é o preview 5), e há muitos elementos IMHO supérfluos, mas que tendem a ser integrados aos poucos (I hope).

A lista que achei interessante (com seu projeto):

 - binary_literals_test. Perfumaria muito bem-vinda de uma linguagem feita para trabalhar também baixo nível.
 - constexpr_test. Um teste que alguém fez na nossa lista ccpp do Telegram e que possui uma particularidade interessante (mais abaixo).
 - for_range_generic_test. Ainda em teste, mas me parece a forma definitiva de iterar entre elementos em C++; completamente genérico.
 - generic_lambdas_test. E por falar em genérico, este lambda tem muito a ver com programação funcional.
 - has_include_test. Uma maneira elegante (apesar do nome feio) de ir migrando projetos/libs aos poucos.
 - initializer_list. Só demonstrando o que já é velho (mas que ainda não comentei no blogue).
 - nodiscard_test. Essa é uma das features mais curiosas para escrita de código robusta.
 - sfinae_test. O SFINAE é um dos pilares do C++, e ele vem melhorando cada vez mais.
 - static_assert_test. O que estava faltando que no Boost é macaco velho.
 - user_defined_literals_test. Mais uma perfumaria; essa é bonitinha; para uso acadêmico.
 - variable_templates_test. Mais algo já velho, que demonstro aqui com minha superlib de log.

A otimização no if através do uso da palavra-chave constexpr possibilita a criação de diferentes instâncias da chamada que não contém o if, mas um dos dois branches dependendo do tipo ser integral ou não.

    void f(const T& value)
    {
      if constexpr(is_integral<T>())
        cout << "Integer\n";
      else
        cout << "Non Integer\n";
    }

Para que a compilação dessa opção funcione no Visual Studio 2017 15.3 é necessário inserir o parâmetro /std:c++latest nas opções do projeto em C/C++, Command Line, Additional Options.

Todos (ou a maioria) deles ainda está em teste. Acabei de baixar o preview 5, conforma um dos membros da ML dos MVPs C++ me informou que saiu quentinha do forno. Em breve novidades.
