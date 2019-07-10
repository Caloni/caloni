---
date: "2015-04-04"
title: Os melhores eventos são de programadores CCPP
categories: [ "blog" ]
---
![](http://i.imgur.com/vMmxP5N.jpg)

Olá! Se você veio aqui para um _flame war_, sinto desapontá-lo. Esse título foi criado apenas para chamar atenção =)

Na verdade, eu nem tenho ideia de como são os outros encontros e eventos de comunidades de outras linguagens, tecnologia ou até mesmo áreas de conhecimento. Só sei de uma coisa: quando a turminha de C se encontra em um evento que lida com otimização, padrões da linguagem, problemas insolúveis, bibliotecas ambiciosas, engenharia reversa e sistemas operacionais de micro-controladores fica difícil não se empolgar com pelo menos uma palestra.

![](http://i.imgur.com/sjKKv5Y.jpg?1)

O [encontro](http://www.ccppbrasil.org/encontros/#encontro-de-programadores-c--c-do-brasil) que aconteceu no prédio da Microsoft, auditório 2, no sábado passado, dia 28 de março de 2015, foi o décimo-primeiro encontro do grupo C/C++ Brasil, que se formou há mais ou menos dez anos atrás (sim, estamos todos ficando velhos).

Dessa vez o evento foi muito mais focado em otimização, linguagem C, Fernandos e Rodrigos. Sim, só de Rodrigos tivemos três palestrantes! E o evento foi iniciado pelo keynote de Fernando Figuera e terminado pela palestra-relâmpago não-intencional de Fernando Mercês, um colega da área de engenharia reversa -- que trabalhei por alguns anos -- e análise de PEs, ou Portable Executables (se você não sabe o que é isso, bom, [_shame on you_](https://msdn.microsoft.com/en-us/magazine/cc301805.aspx)).

![](http://i.imgur.com/iXdBhwd.jpg?1)

Particularmente minha [palestra favorita](https://github.com/rmaalmeida/stack-protection) foi a de Rodrigo Almeida e sua técnica em cima de um SO de micro-controlador para evitar falhas dos dados da troca de contexto dos processos, e que já serve de estudo contra o ataque mais novo do momento, o [Row Hammer](http://googleprojectzero.blogspot.com.br/2015/03/exploiting-dram-rowhammer-bug-to-gain.html) (cujo [Projeto Zero](http://googleprojectzero.blogspot.com.br/2015/03/exploiting-dram-rowhammer-bug-to-gain.html) da Google está estudando). Ele basicamente envolve o acesso contínuo a uma região da memória para alterar bit(s) de uma região adjacente, apenas pela interferência física.

![](http://i.imgur.com/tAM6EhI.jpg?1)

Mas as ideias inovadoras não param por aí. Temos mais uma vez Fabio Galuppo usando C++ de maneira funcional e [tratando problemas insolúveis](https://github.com/ccppbrasil/encontro11/tree/master/FabioGaluppo) de maneira mais rápida, Rodrigo Madera tentando unir a transformação de dados em torno de apenas uma biblioteca (a sua [Moneta](https://github.com/ccppbrasil/encontro11/tree/master/RodrigoMadera)) e tivemos a ilustre presença de Cleiton Santoia que com Daniel Auresco compilaram um [paper sobre reflexão em C++](http://www.google.com/url?q=http%3A%2F%2Fwww.open-std.org%2Fjtc1%2Fsc22%2Fwg21%2Fdocs%2Fpapers%2F2014%2Fn3951.pdf&sa=D&sntz=1&usg=AFQjCNHXa2PzWy0XF9fOcM7tdabFCmqXcw) que foi enviado para o comitê. A parte mais atraente, tanto do Moneta quanto da proposta ao padrão C++, é a possibilidade de realizar coisas estaticamente, ou em tempo de compilação, e ao mesmo tempo entregar mais poder à ponta que escreve o código (nós, programadores) sem onerar a ponta que usa o código (eles e também nós, usuários).

C++ está apenas começando, como parece sugerir o breve intervalo das palestras e um talk de 10 minutos sobre o __Visual Studio 2015__ de Eric Battalio, Senior Program Manager da equipe da IDE. No entanto, mesmo apenas o básico já dá pano para a manga, como pudemos conferir através do uso do Perf, GCC e Valgrind para profiling de código de maneira extremamente detalhista. Seja que nível você programe, C e C++ ainda são linguagem extremamente em voga que têm muito a oferecer.

![](http://i.imgur.com/62DJU20.jpg?1)

Especialmente quando temos um Happy Hour com pessoas mais que especiais =)
