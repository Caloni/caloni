---
date: "2008-04-25"
title: "Seminário CCPP Portabilidade e Performance"
categories: [ "blog" ]
---
Reserve sua cadeira. Está marcado para o último dia do mês de maio o [primeiro seminário de nosso grupo nacional de programadores e aficionados por C e C++](http://www.temporealeventos.com.br/?area=101). É bom ou não é?

O assunto gira em torno de duas preocupações constantes na vida de todo programador de linguagens de nível médio:

	
  * Quanta velocidade eu preciso nesse código?

	
  * Em quais plataformas eu conseguiria compilar e rodar meu projeto?

Para responder estas questões teremos uma bateria de palestras com temas que, dessa vez, focam o simples, puro e independente uso das linguagens C/C++:

![wanderley.gif](http://i.imgur.com/RPibM82.gif)**Dicas e Truques de Portabilidade**
Wanderley Caloni

O objetivo dessa palestra é focar nos problemas da vida real que enfrentamos no dia-a-dia para tornar um código portável ou mais maleável para um dia ser. Nesse caso existem vários assuntos a tratar, como: construções ambígüas não-padrão, isolamento de particularidades de cada sistema, identificação de problemas de portabilidade, organização do código-fonte portável, entre outros.

O nível dessa palestra será o intermediário, porque eu preciso que o público tenha o conhecimento prévio de programação C e C++. Quando você está aprendendo, uma dica ou outra sobre portabilidade pode ser interessante para não ser desvirtuado desde o início. Porém, para realmente começar a programar multiplataforma, existem desafios que devem ser transpostos por aqueles que já conseguem um nível de organização e desenvolvimento em C e C++ que não deixa dúvidas sobre a qualidade do código.

![fabio.jpg](http://i.imgur.com/BMbSRAc.jpg)

**Programação Concorrente com C++**
Fábio Galuppo

Fábio Galuppo estréia na nossa rede de palestrantes, depois de seu inspirador e excitante relato das peripécias do SD West desse ano. Ele irá falar de um tema extremamente atual, que é o uso de programação paralela, em especial usando C++. Existe uma série de coisas para entender, como os modelos a ser seguidos, o uso consciente de _threads_, a programação com bom desempenho nos novos _chips _com mútiplos núcleos de processamento e por aí vai.

Apenas para ter uma idéia da importância em se ir em uma palestra como essa, imagine que 99,9% dos produtos da Google se baseiam nesse tipo de programação, envolvendo uma plantação de algumas centenas (milhares?) de máquinas trabalhando um banco de dados gigantesco no modo cooperativo para entregar a resposta mais rápida possível do outro lado. Sentiu o drama?

![strauss.gif](http://i.imgur.com/NvLa4qf.gif)

**Programação Multiplataforma Usando STL e Boost**
Rodrigo Strauss

Voltando para o tema portabilidade, Rodrigo Strauss volta a repetir sua performance sobre Boost, dessa vez abrangendo o conjunto completo de bibliotecas que compõem essa extensão mais-que-necessária da STL para programadores produtivos e multiplataforma. Todos sabem que um código que apenas usa STL e C++ puro não consegue ir muito longe na vida real, apesar de ser 100% multiplataforma. O que muitos não sabem (inclusive eu) é como é possível turbinar o desenvolvimento portável com o uso do Boost, que é uma solução portável bem interessante.

Por exemplo, a manipulação de arquivos e diretórios não é lá o forte da STL, concentrada no conceito de streams. Com o uso do Boost, podemos ter o melhor da STL, só que turbinada. Além disso, o novo padrão de _threads _ainda está longe de chegar ao mercado, e o Boost.Threads é uma solução viável atualmente.

![kumpera.jpg](http://i.imgur.com/zZ8iled.jpg)![tupi.jpg](http://i.imgur.com/xcyNlkM.jpg)

**Técnicas de Otimização de Código**
Rodrigo Kumpera & André Tupinambá

Essa é a estréia de dois palestrantes de uma só vez! Como um bom complemento, voltamos ao tema de otimização, dessa vez em aspectos mais genéricos. Entre questões mais ou menos banais como otimização de laços e _benchmarkers_, mas que faze toda a diferença saber, teremos ainda tópicos bem avançados, como a relação de nosso código com o cachê do processador, e a tão-falada técnica de _branch prediction_, presente na maioria dos processadores atuais.

Além do aspecto genérico teremos uma pitada de matemática, como o uso de _lookup tables_ e a otimização de algoritmos baseada em operações vetoriais. Ainda como um aspecto básico, mas importante, temos o uso eficiente da memória, muitas vezes entregue ao controle do sistema operacional, que nem sempre sabe bem o que o programa está fazendo.
