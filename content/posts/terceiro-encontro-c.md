---
categories:
- blog
date: '2008-01-22'
tags:
- ccppbr
title: Terceiro encontro C++
---

Nesse último sábado aconteceu, como previsto, o terceiro encontro de usuários/programadores C++. Foi um sucesso bem maior que o esperado, pelo menos por mim e pelas pessoas com quem conversei. A organização foi fantástica, e o patrocínio muito importante, o que deu abertura para pensamentos mais ousados sobre o futuro de C++ no Brasil. Foi gerada uma lista de resoluções para o futuro (que começa hoje), onde pretendemos, inclusive, fazer reuniões no mesmo estilo trimestralmente.

Aqui segue um breve relato sobre as palestras que ocorreram no evento.

C++ com wxWidgets, de Ivo Nascimento. Inicialmente o palestrante focou o ponto muito pertinente da visão comercial do uso de um framework multiplataforma que possa rodar nos três sistemas operacionais mais usados no Brasil: Windows, Linux e MacOS. É um fato que programadores precisam se alimentar e alimentar seus filhos, então essa questão pode ser interessante para aqueles que precisam expandir seus mercados.

Como sempre deve rolar, houve demonstração por código de como um programa wxWidgets é estruturado. Basicamente temos inúmeras macros e um ambiente controlado por eventos, da mesma maneira que MFC e outros frameworks famosos.

Para mim foi uma imensa vantagem e economia de tempo ter assistido à palestra, já que faz um tempo que eu tento dar uma olhada nessa biblioteca. Para quem também gostou da idéia, dê uma olhada nos tutoriais disponíveis no sítio do projeto.

C++0x - novas características, de Pedro Lamarão. Para quem achava que as palestras iriam ser superficiais no quesito linguagem deve ter ficado espantado com o nível de abstração, formalidade e profundidade com que foi tratado o assunto das novas características da linguagem C++ que serão aprovadas pelo novo padrão e que irão tornar a programação genérica muito mais produtiva e eficiente.

O foco do palestrante foi no mais importante: quais os problemas que as novas mudanças irão resolver, e de que modo a linguagem irá se tornar mais poderosa para suportar programação genérica, paradigma que, de acordo com o debate que houve após a apresentação, ainda é muito novo, mas que poderá se tornar futuramente uma base sólida de programas mais simples de serem mantidos e especializados.

Para quem se interessou pelo tema e pretende estudar um pouco mais sobre as novidades na linguagem, aqui vão algumas expressões-chave para pesquisa:

 - Proposed Wording for Variadic Templates
 - Proposed Wording for RValue Reference
 - Specifying C++ Concepts

Threads em C++, por Wanderley Caloni. O foco principal desse tema foi dividido entre a interface, óbvia, para suportar programas multithreading em C++, incluindo abstrações de sincronismo e variáveis de condição, e a mudança significativa no padrão para definir um modelo de memória consistente com programas multithreading, a grande vantagem dessa biblioteca ter sido votada, pois tendo as bases para o que eles estão chamando de "execução consistente", a interface é mera conseqüência.

Durante a apresentação foi mostrado um exemplo de uso das classes thread e mutex. O código foi melhorado (mas não completado). Ao final da palestra, fiquei devendo os links. Bem, aqui estão algumas expressões-chave também:

 - ISO C++ Strategic Plan for Multithreading
 - Thoughts on a Thread Library for C++
 - A Memory Model for C++: Strawman Proposal
 - Multi-threading Library for Standard C++

Para finalizar, segue o [álbum de fotos] disponibilizado pelo [Alberto Fabiano], organizador-mor do evento.

[álbum de fotos]: https://www.facebook.com/media/set/?vanity=ccppbrasil&set=a.1692292557687519
[Alberto Fabiano]: http://techberto.wordpress.com/