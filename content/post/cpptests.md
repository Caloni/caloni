---
date: 2017-07-25T16:59:05-03:00
title: "CppTests"
categories: [ "blog" ]
---
Iniciei um novo projeto no GitHub](https://github.com/Caloni/ccpptests) que tem por objetivo ser minha prancheta de trabalhos para minha palestra no [próximo encontro ccpp. Há uma infinitude de coisinhas novas na linguagem C++, fora as adições à biblioteca STL, mas que devem passar despercebidas da maioria dos programadores, que está mais é querendo terminar seus próprio projetos. Enquanto alguns conceitos, sintaxes e métodos não se solidificam, vale a pena dar uma espiada no futuro?

Depende.

Dei uma olhada nas últimas modificações adicionadas no Visual Studio 2017.

A lista que achei interessante (com seu projeto):

 - __binary_literals_test__. Perfumaria muito bem-vinda de uma linguagem feita para trabalhar também baixo nível.
 - __constexpr_test__. Um teste que alguém fez na nossa lista ccpp do Telegram e que possui uma particularidade interessante (mais abaixo).
 - __for_range_generic_test__. Ainda em teste, mas me parece a forma definitiva de iterar entre elementos em C++; completamente genérico.
 - __generic_lambdas_test__. E por falar em genérico, este lambda tem muito a ver com programação funcional.
 - __has_include_test__. Uma maneira elegante (apesar do nome feio) de ir migrando projetos/libs aos poucos.
 - __initializer_list__. Só demonstrando o que já é velho (mas que ainda não comentei no blogue).
 - __nodiscard_test__. Essa é uma das features mais curiosas para escrita de código robusta.
 - __sfinae_test__. O SFINAE é um dos pilares do C++, e ele vem melhorando cada vez mais.
 - __static_assert_test__. O que estava faltando que no Boost é macaco velho.
 - __user_defined_literals_test__. Mais uma perfumaria; essa é bonitinha; para uso acadêmico.
 - __variable_templates_test__. Mais algo já velho, que demonstro aqui com minha superlib de log.

## constexpr para especialização em ifs

A otimização no if através do uso da palavra-chave __constexpr__ possibilita a criação de diferentes instâncias da chamada que não contém o if, mas um dos dois branches dependendo do tipo ser integral ou não.

!

Para que a compilação dessa opção funcione no Visual Studio 2017 15.3 é necessário inserir o parâmetro /std:c++latest nas opções do projeto em __C/C++, Command Line__:

!

Todos (ou a maioria) deles ainda está em teste. Acabei de baixar o preview 5, conforma um dos membros da ML dos MVPs C++ me informou que saiu quentinha do forno. Em breve novidades.
