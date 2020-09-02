---
date: "2011-07-26"
tags: [ "code", "draft",  ]
title: "Cuidado com variáveis temporárias"
---
Um dos problemas que a linguagem C++ possui para seus iniciantes é o de não deixar muito explícito partes do seu comportamento, principalmente as partes que lidam com ponteiros/referências e o jogo da vida dos objetos. Às  vezes a coisa fica de tal como complexa que fica até difícil explicar o porquê das coisas.

Por exemplo, vejamos o singelo caso de alguém que precisa formatar uma saída de erro e para isso escolheu um stringstream:


Quando chamamos func, ele lança uma exceção que é capturada no main que, por sua vez, formata uma stream e obtém sua string (através do método str) e através dessa string obtém o ponteiro da string em C puro (através do método cstr). Porém, a mensagem resultante na saída-padrão de erro não era o esperado:

Depurando diretamente, vemos que a stream, de fato, contém o que esperávamos. O único elemento errante é justamente o ponteiro obtido através da chamada dupla de métodos.

O porquê isso ocorre só fica óbvio quando vemos a ajuda (ou a assinatura) da função str da classe stringstream:

Ora, a função str retorna uma cópia do objeto string usado internamento pelo buffer de nossa string stream. Duas coisas ocorrem em qualquer cópia de um objeto retornada por uma função:

  * A cópia do objeto original e seu desacoplamento (óbvio).

  * A construção de um objeto baseado no original e que, após o fim da expressão onde foi chamado o método, é destruído.

Uma vez que a chamada a str termina, é entregue uma instância de uma string que contém a string original que está sendo usada pela string stream para a expressão da chamada, que geralmente vem seguida de uma cópia:


A variável buf no exemplo acima será, portanto, a terceira string usada aqui até então. Ao final da expressão, a string intermediária retornada por str é automaticamente destruída, por se trata de uma cópia temporária para obedecer a sintaxe de retorno da função.

Agora, o que acontece se, na cópia temporária, é feita uma operação para obter seu ponteiro interno usado para armazenar sua string estilo C?

Obviamente ele fica inválido após o fim da expressão!

Vamos ver em câmera lenta:

Nada como assembly fresquinho para refrescar os conceitos de C++ por baixo dos panos.

Após uma enxurrada de programadores gerenciáveis perguntarem qual seria, então, a solução ideal, segue o snipet mais explicitado:


Outro leitor sugeriu fazer toda a chamada em uma única instrução, economizando em expressividade e ainda evitando a destruição da variável temporária criada ao chamar str.


Particularmente, gosto de instruções simples que me permitam ver claramente o que está acontecendo de forma simples pelo depurador (até porque sei que o compilador irá otimizar tudo no final em versão Release, ainda mais se estiver quebrado em instruções simples). Porém, toda solução que evita o uso da variável temporária após a execução do método str é válida.
