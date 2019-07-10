---
date: "2012-01-11"
title: RValue é o novo LValue
categories: [ "blog" ]
---
[![](http://i.imgur.com/N5uv6gS.jpg)](/images/The-C-Programming-Language.jpg)

As grandes discussões filosóficas que participei durante meu estudo da linguagem C, e mais tarde de C++, muitas vezes convergiam para o significado místico daquela figura que nós da gramática da linguagem conhecemos como lvalue, ou l-value, ou left-value. Enfim, a definição de uma expressão que representa um lugar na memória e, portanto, pode ocupar o lado esquerdo de uma atribuição/cópia/passagem de argumentos qualquer. Porém, os "grandes" embates daquela época hoje parecem brincadeira de criança, como a diferença sutil entre ++x e x++ ou convergência de tipos em templates.

Agora o buraco é mais embaixo. Agora temos referências r-value.

Agora o mundo mudou.

Foi necessário que mudasse. C++, conhecido internacionalmente como a vanguarda das linguagens, mesmo mantendo sua fama de alta performance, precisava voltar às suas origens performáticas de qualquer forma. O Criador da linguagem e seus seguidores estavam cientes: cópia de strings é uma coisa muito, muito má. Imperfect forwarding (direcionamento imperfeito?) é algo ainda pior, pois é mais sutil.

Todos concordam, então, que a mudança é necessária. Nem todos concordam, contudo, com o preço a ser pago. As coisas começam a ficar cada vez mais difíceis de entender, e agora, com r-values vindo à superfície, o universo de criaturas bizarras volta a mostrar as caras.

Desde o começo de meus estudos em C++ tenho admirado a linguagem com um certo distanciamento. Enquanto a linguagem C continua sendo o supra-sumo das linguagens de médio-nível, C++ continua sendo uma abominação cujos detalhes muitos preferem esquecer. Mas esquecer tem se tornado cada vez mais difícil frente às <del>gambiarras</del> adaptações técnicas que a linguagem vem sofrendo.

No caso de Rvalues, se antes existia uma discussão interminável sobre sua inclusão no novo padrão, agora existem discussões acerca do que tudo isso significa. Existe até um [ótimo guia](http://thbecker.net/articles/rvalue_references/section_01.html) (thanks to [pepper_chico](https://twitter.com/#!/pepper_chico)) sobre as principais mudanças de conceitos, feito para simplificar o entendimento. Mas ele mesmo é exageradamente complexo para o programador médio. É de forçar a barra, mesmo. É pedir demais.

#### Conversemos

No próximo dia 28, sábado, nos reuniremos em mais um [evento C++ organizado ](https://msevents.microsoft.com/CUI/EventDetail.aspx?EventID=1032503387&Culture=pt-BR)<del>[pela Microsoft](https://msevents.microsoft.com/CUI/EventDetail.aspx?EventID=1032503387&Culture=pt-BR)</del> [pelo Grupo C/C++ Brasil](https://msevents.microsoft.com/CUI/EventDetail.aspx?EventID=1032503387&Culture=pt-BR) e pelos agora dois MVPs do Brasil, o veterano Fabio Galuppo e o novato Rodrigo Strauss (meu amigo, mas acima de tudo muito bem-vindo ao cargo). Estou na lista de palestrantes e conversarei com vocês sobre as otimizações que o famigerado RValue deve trazer à mesa. Espero conseguir entender um pouco mais sobre essa criatura fantástica até lá.

Se o Cebolinha for um programador C++, deve estar se debatendo nesse momento.

#### Linques úteis

	
  * [C++ Rvalue References Explained](http://thbecker.net/articles/rvalue_references/section_01.html)

	
  * [A Brief Introduction to Rvalue References](http://www.artima.com/cppsource/rvalue.html)

	
  * [Want Speed? Pass by Value](http://cpp-next.com/archive/2009/08/want-speed-pass-by-value/)

	
  * [MSDN Community: C++ Renaissance, São Paulo - SP](https://msevents.microsoft.com/CUI/EventDetail.aspx?EventID=1032503387&Culture=pt-BR). **Faça sua incrição!**

