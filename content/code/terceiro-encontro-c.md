---
date: "2008-01-22"
title: Terceiro encontro C++
categories: [ "code" ]
---
Nesse último sábado aconteceu, [como previsto](http://www.caloni.com.br/cppcon-iii), o terceiro encontro de usuários/programadores C++. Foi um sucesso bem maior que o esperado, pelo menos por mim e pelas pessoas com quem conversei. A organização foi fantástica, e o [patrocínio](http://www.agit.com.br/) muito importante, o que deu abertura para pensamentos mais ousados sobre o futuro de C++ no Brasil. Foi gerada uma [lista de resoluções](http://groups.google.com/group/ccppbrasil/msg/f1e17573399e11d9) para o futuro (que começa hoje), onde pretendemos, inclusive, fazer reuniões no mesmo estilo trimestralmente.

Aqui segue um breve relato sobre as palestras que ocorreram no evento.

#### C++ com wxWidgets - Ivo Nascimento

Inicialmente o palestrante focou o ponto muito pertinente da **visão comercial** do uso de um _framework_ multiplataforma que possa rodar nos três sistemas operacionais mais usados no Brasil: Windows, Linux e MacOS. É um fato que programadores precisam se alimentar e alimentar seus filhos, então essa questão pode ser interessante para aqueles que precisam expandir seus mercados.

Como sempre deve rolar, houve demonstração por código de como um programa wxWidgets é estruturado. Basicamente temos inúmeras macros e um ambiente controlado por eventos, da mesma maneira que MFC e outros _frameworks _famosos.

Para mim foi uma imensa vantagem e economia de tempo ter assistido à palestra, já que faz um tempo que eu tento dar uma olhada nessa biblioteca. Para quem também gostou da idéia, dê uma olhada nos [tutoriais disponíveis](http://www.wxwidgets.org/docs/tutorials.htm) do sítio do projeto.

#### C++0x - novas características - Pedro Lamarão

Para quem achava que as palestras iriam ser superficiais no quesito linguagem deve ter ficado espantado com o nível de abstração, formalidade e profundidade com que foi tratado o assunto das novas características da linguagem C++ que serão aprovadas pelo novo padrão e que irão tornar a programação genérica muito mais produtiva e eficiente.

O foco do palestrante foi no mais importante: quais os problemas que as novas mudanças irão resolver, e de que modo a linguagem irá se tornar mais poderosa para suportar programação genérica, paradigma que, de acordo com o debate que houve após a apresentação, ainda é muito novo, mas que poderá se tornar futuramente uma base sólida de programas mais simples de serem mantidos e especializados.

Para quem se interessou pelo tema e pretende estudar um pouco mais sobre as novidades na linguagem, aqui vão alguns links:

	
  * [Proposed Wording for Variadic Templates](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2152.pdf)

	
  * [Proposed Wording for RValue Reference](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2118.html)

	
  * [Specifying C++ Concepts](http://www.open-std.org/jtc1/sc22/WG21/docs/papers/2005/n1886.pdf)

	
  * [O sítio do comitê dos padrões C++](http://www.open-std.org/jtc1/sc22/WG21/)

#### Threads em C++ - Wanderley Caloni

O foco principal desse tema foi dividido entre a interface, óbvia, para suportar programas _multithreading_ em C++, incluindo abstrações de sincronismo e variáveis de condição, e a mudança significativa no padrão para definir um modelo de memória consistente com programas _multithreading_, a grande vantagem dessa biblioteca ter sido votada, pois tendo as bases para o que eles estão chamando de "execução consistente", a interface é mera conseqüência.

Durante a apresentação foi mostrado um exemplo de uso das classes thread e mutex. O código foi melhorado (mas não completado), e está disponível para [download aqui](/images/stdthreads.7z), juntamente com a apresentação (em formato OpenOffice).

Ao final da palestra, fiquei devendo os links. Bem, aqui estão eles:

  * [ISO C++ Strategic Plan for Multithreading](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1815.html)
  * [Thoughts on a Thread Library for C++](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2139.html)
  * [A Memory Model for C++: Strawman Proposal](http://www.hpl.hp.com/personal/Hans_Boehm/c++mm/mm.html)
  * [Multi-threading Library for Standard C++](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2447.htm)

Para ver mais
	
  * Segue o [álbum de fotos](http://picasaweb.google.com.br/alberto.fabiano/3EncontroDoGrupoCCBrasil1ReuniOTCnica/) disponibilizado pelo [Alberto Fabiano](http://techberto.wordpress.com/), organizador-mor do evento.

