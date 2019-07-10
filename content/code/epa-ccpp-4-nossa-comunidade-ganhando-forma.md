---
date: "2008-03-29"
title: 'EPA-CCPP 4: nossa comunidade ganhando forma'
categories: [ "code" ]
---
Nesse último sábado ocorreu mais uma vez, como [todos sabem](http://www.caloni.com.br/quarto-encontro-c), o [Encontro de Programadores e Aficionados por C++](http://picasaweb.google.com/ccppmeetings/4oEncontroDeProgramadoresEAficcionadosDoGrupoCCBrasilSampa), (in)formalmente apelidado de EPA-CCPP, de acordo com [algumas conversas](http://groups.google.com/group/ccppbrasil/browse_thread/thread/10b370b5b2bd85d5/eabf850054cfc5c9?lnk=gst&q=EPA#eabf850054cfc5c9) da nossa lista de discussão.

Mais uma vez, temos que dar uma salva de palmas e agradecer de coração a todos que colaboraram direta ou indiretamente para a realização do evento, que teve uma qualidade ainda maior que o último encontro.

E por falar em qualidade, as palestras dessa vez foram ricas em informação e diversidade, pois demonstraram diferentes visões que as pessoas possuem sobre a mesma coisa, que é o uso das linguagens C e C++ na vida real sobre alguma aplicação específica.

#### TCP/IP via Boost.Asio (Rodrigo Strauss)

Infelizmente cheguei um pouco atrasado por problemas de localização (me perdi geral), mas consegui pegar a parte mais divertida da palestra do Strauss: o código.

De uma maneira bem clara e direta, o palestrante nos mostrou como usar uma biblioteca de comunicação em redes feita de modo portável e extremamente antenada com o pensamento C++/STL de fazer as coisas. Partindo de um ponto de vista prático, deu dicas importantes para os iniciantes que desejarem começar a utilizá-la e passar mais facilmente pelo caminho das pedras que é aprender novas maneiras de fazer as mesmas coisas.

Na verdade, foi além, pois ao exemplificar seu uso no código do dia-a-dia chegou a usar um projeto próprio com dezenas de CPPs e centenas (milhares?) de linhas de código utilizando 100% boost para a comunicação em rede, sendo compilável e rodável nos ambientes Windows e Linux.

#### Programação em C para microcontroladores (Daniel Quadros)

Estava particularmente interessado nessa palestra para entender alguns truques e jogos-de-cintura necessários para utilizar a linguagem C em ambientes tradicionamente limitados em memória e poder de processamento. E, posso dizer, saí satisfeito.

O panorama traçado por DQ dos inúmeros tipos de microprocessadores, suas "linhagens" e diferentes arquiteturas nos permitiram entender as dificuldades em implementar e usar um compilador C para programar em sistemas embarcados. Mais ainda, fez ver a importância de, antes de programar, entender de fato como o hardware funciona para daí pensar em fazer algo útil com ele.

Ao final, um destaque especial para os conselhos finais sobre o desenvolvimento nessa área. Um conselho em específico ficou na minha mente, pois acredito que seja de extrema importância não só para sistemas embarcados, como para todo tipo de desenvolvimento: **sempre pense em como será a depuração do sistema no projeto e em campo**. Nunca se sabe onde e como o bug poderá ocorrer. Que ele existe, todos sabemos.

#### Desenvolvimento _cross-platform_ em C++ com Qt (Basílio Miranda)

Algumas coisas que me impressionaram na palestra anterior sobre wxWidgets me impressionaram mais ainda pelas explicações do funcionamento do Qt em suas diversas plataformas suportadas. Aos poucos entendemos que desenvolver _frameworks_ de ambiente gráfico multiplataforma nem sempre é aquela coisa bonita e abstrata que imaginamos possível de fazer com as maravilhas da linguagem C++. No fundo, muitas das coisas relacionadas com o funcionamento do núcleo desses sistemas é feito com alguns "remendos" sintáticos e semânticos que só os projetistas devem realmente saber explicar o porquê.

Por outro lado, o cuidado com a documentação e com os exemplos do ambiente Qt confortaram bastante o entusiasta que deseja explorar esse outro mundo de janelas além-Microsoft. Para os que reclamam do preço abusivo da licença da versão comercial, pode ser um alívio saber que projetos desenvolvidos com a licença GPL estão isentos de taxas, mesmo que comercializados. É uma questão de testar, medir e escolher alguma das alternativas.

#### Arquitetura e desenvolvimento de _drivers _com C para Windows (Fernando Silva)

Voltando para o mundo microsoftiano, o foco da palestra do Fernando foi explicar os princípios básicos por trás do funcionamento do sistema operacional Windows desde a época que ele era um prompt do DOS. Como pudemos ver, essa é uma condição _sine qua non_ para o desenvolvimento de _drivers_ para essa plataforma, visto que são componentes que interagem diretamente com o sistema operacional, de código fechado, e muitas vezes com o _hardware_, uma caixinha de surpresas.

Entre outras coisas, vimos como funciona a divisão entre os modos usuário e _kernel_, qual a organização da memória virtual, a importância dos níveis de prioridade de _thread_ no desenvolvimento de _drivers_ e, é claro, como podemos começar a desenvolver _drivers_ desde já e gerar aquelas bonitas telas azuis.

Ao final pudemos ver que foi um tema que gerou interesse especial do grupo, pois houve várias perguntas, como por exemplo se existe uma maneira de proteger o sistema operacional dos _drivers_ (isso poderia gerar um artigo). Imagino que a palestra foi direto ao encontro do espírito do evento, que falou principalmente sobre o que cada um de nós faz com C/C++. Muito provavelmente temos uma montanha de assuntos diferentes e complementares que poderão ser cobertos nos próximos encontros.

#### Sorteios, mais eventos e agradecimentos

No final, tivemos uma série de sorteios de livros-referência em C++, convites para o seminário C++ e algumas licenças de software. Por isso é importante lembrar aos que saíram antes que poderiam ter ganhado mais conhecimento, para que da próxima vez tentem apertar apenas mais um pouco seus compromissos.

Além das palestras, tivemos o relato de [Fábio Galupo](http://fabiogaluppo.spaces.live.com) sobre o que foi o [SD West 2008](http://www.sdexpo.com/), o evento que reuniu alguns gurus do C++ para discutirem, entre outras coisas, o futuro da linguagem. Entre outras tantas coisas interessantes que ele nos trouxe, achei duas particularmente interessantes.

A primeira diz respeito à importância do bom uso de interfaces entre os programadores C++. Esse foi um tema levantado por Bjarne Stroustrup em uma de suas palestras, e é de fato algo preocupante em nossa linguagem, que não possui ainda uma organização tão produtiva quanto outros grupos de desenvolvedores.

A segunda diz respeito à necessidade de aprendermos outras linguagens. Na posição de desenvolvedores de sistemas que vão interagir com o mundo afora, é de suma importância que conheçamos nossos vizinhos mais próximos: desenvolvedores da camada acima que irão aproveitar o nosso código rápido e leve.

Após isso, ainda tive uma das mais felizes surpresas da minha vida: ganhei um exemplar do **The C++ Programming Language**, Special Edition, assinado por Bjarne Stroustrup!!! Foi um momento tão estupefato que nem sei direito o que eu fiz naquela hora, além de me levantar, agradecer mal e porcamente meus amigos da bancada (eu sei que para um presente desses não existe maneira de agradecer o suficiente), pegar meu livro e sentar novamente, ainda um pouco atordoado. Essas supresas podem matar!

Aproveito o final deste artigo para mais uma vez agradecer toda a organização do evento e, por que não, a todos da comunidade que puderam participar. Como alguém bem disse mais uma vez, a comunidade somos nós, e não um ou outro que costumam ser o porta-voz de nossos movimentos. Portanto, a todos que usam C e C++ de alguma maneira em algum momento de suas vidas, sintam-se honrados de participar do seleto grupo do EPA. Nós merecemos.
