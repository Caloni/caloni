---
date: "2008-07-18"
title: O conhecido unresolved external
tags: [ "draft", "code" ]
---
O [artigo anterior](http://www.caloni.com.br/o-caso-da-funcao-de-delay-load-desaparecida) mostrou que nem sempre as coisas são simples de resolver, mas que sempre existe um caminho a seguir e que, eventualmente, todos os problemas se solucionarão.

Porém, resolver um problema por si só não basta: é preciso **rapidez**. E como conseguimos rapidez para resolver problemas? Um jeito que eu, meu cérebro e o [Dmitry Vostokov](http://www.dumpanalysis.org/blog/) conhecem é **montando padrões**.

Um padrão nos ajuda a não pensar novamente em coisas que sabemos a resposta, de tantas vezes que já fizemos. Só precisamos saber o caminho para resolver determinado problema.

Mesmo assim, existem diversos caminhos a percorrer. Até mesmo para um singelo e batidíssimo "**unresolved external**".

#### Primeiro passo: você está usando a LIB correta?

O erro mais comum é usar uma LIB onde não está a função que estamos usando, ou usar uma versão diferente da mesma LIB que não contém a função, ou contém, mas com assinatura (parâmetros da função) diferentes. Isso pode ser verificado no código-fonte da LIB, se disponível, ou então pelo uso do **dumpbin**, como já vimos anteriormente.

<blockquote>Dica extra: às vezes você pensa que está usando uma LIB em um determinado caminho, mas o linker achou a LIB primeiro em outro lugar. Para se certificar que está verificando a mesma LIB que o linker achou, use o Process Monitor.</blockquote>

Às vezes, porém, não estamos usando a função diretamente e não conhecemos quem a usaria. Para isso que hoje em dia os compiladores mais espertos nos dizem em que parte do código foi referenciado a tal função:

    
    test.obj : error LNK2019: unresolved external symbol _func referenced in function _main

É sábio primeiro inspecionar a função que referencia, para depois entender porque ela não foi encontrada. Mesmo parecendo diferente, essa operação faz parte do primeiro passo, que é **identificar a origem**.

#### Segundo passo: você digitou direito?

Parece estúpido, mas às vezes é esse o caso. Essa é a segunda coisa a fazer porque não é tão comum quanto a primeira, visto que hoje em dia é rotina colocarmos as funções em um _header _e incluirmos esse cabeçalho em nosso código-fonte (em C++, praticamente obrigatório). Se houvesse discrepância entre o nome da função chamada e o nome da função existente, provavelmente teríamos um **erro de compilação** ("função não encontrada") antes do erro de _linking_.

#### Terceiro passo: tente incluir a função diretamente no seu código

Se a LIB não está cooperando, e der pouco trabalho, experimente incluir a função inteira (ou o cpp) dentro do seu projeto, para linkar diretamente. Se funcionar, então existe alguma diferença de compilação entre os dois projetos (o seu e o da LIB) para que haja uma divergência no nome procurado. Procure nas opções de projeto.

#### Quarto passo: comece de novo!

Sempre que nos deparamos com um problema que aos poucos vai consumindo o nosso tempo, tendemos a gastar mais tempo fazendo coisas inúteis que sabemos que não irá adiantar de nada. Às vezes fazer _brute force_ pode dar certo. Outras vezes, seria melhor recomeçar a pesquisa e tentar entender de fato o que está acontecendo na compilação. Em outras palavras: gastar o seu tempo **pensando** pode ser mais produtivo do que agir instintivamente.
