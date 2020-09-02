---
date: "2015-04-04"
tags: [ "blog", "draft", "ccppbr" ]
title: "Os melhores eventos são de programadores CCPP"
---
Olá! Se você veio aqui para um flame war, sinto desapontá-lo. Esse título foi criado apenas para chamar atenção =)

Na verdade, eu nem tenho ideia de como são os outros encontros e eventos de comunidades de outras linguagens, tecnologia ou até mesmo áreas de conhecimento. Só sei de uma coisa: quando a turminha de C se encontra em um evento que lida com otimização, padrões da linguagem, problemas insolúveis, bibliotecas ambiciosas, engenharia reversa e sistemas operacionais de micro-controladores fica difícil não se empolgar com pelo menos uma palestra.

O encontro que aconteceu no prédio da Microsoft, auditório 2, no sábado passado, dia 28 de março de 2015, foi o décimo-primeiro encontro do grupo C/C++ Brasil, que se formou há mais ou menos dez anos atrás (sim, estamos todos ficando velhos).

Dessa vez o evento foi muito mais focado em otimização, linguagem C, Fernandos e Rodrigos. Sim, só de Rodrigos tivemos três palestrantes! E o evento foi iniciado pelo keynote de Fernando Figuera e terminado pela palestra-relâmpago não-intencional de Fernando Mercês, um colega da área de engenharia reversa -- que trabalhei por alguns anos -- e análise de PEs, ou Portable Executables (se você não sabe o que é isso, bom, shame on you).

Particularmente minha palestra favorita foi a de Rodrigo Almeida e sua técnica em cima de um SO de micro-controlador para evitar falhas dos dados da troca de contexto dos processos, e que já serve de estudo contra o ataque mais novo do momento, o Row Hammer (cujo Projeto Zero da Google está estudando). Ele basicamente envolve o acesso contínuo a uma região da memória para alterar bit(s) de uma região adjacente, apenas pela interferência física.

Mas as ideias inovadoras não param por aí. Temos mais uma vez Fabio Galuppo usando C++ de maneira funcional e tratando problemas insolúveis de maneira mais rápida, Rodrigo Madera tentando unir a transformação de dados em torno de apenas uma biblioteca (a sua Moneta) e tivemos a ilustre presença de Cleiton Santoia que com Daniel Auresco compilaram um paper sobre reflexão em C++ que foi enviado para o comitê. A parte mais atraente, tanto do Moneta quanto da proposta ao padrão C++, é a possibilidade de realizar coisas estaticamente, ou em tempo de compilação, e ao mesmo tempo entregar mais poder à ponta que escreve o código (nós, programadores) sem onerar a ponta que usa o código (eles e também nós, usuários).

C++ está apenas começando, como parece sugerir o breve intervalo das palestras e um talk de 10 minutos sobre o Visual Studio 2015 de Eric Battalio, Senior Program Manager da equipe da IDE. No entanto, mesmo apenas o básico já dá pano para a manga, como pudemos conferir através do uso do Perf, GCC e Valgrind para profiling de código de maneira extremamente detalhista. Seja que nível você programe, C e C++ ainda são linguagem extremamente em voga que têm muito a oferecer.

Especialmente quando temos um Happy Hour com pessoas mais que especiais =)
