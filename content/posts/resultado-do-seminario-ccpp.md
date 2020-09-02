---
date: "2008-06-03"
tags: [ "blog", "draft", "essays" ]
title: "Resultado do Seminário CCPP"
---
Aconteceu nesse fim-de-semana, como era previsto, o nosso primeiro Seminário CCPP Brasil, com direito a pessoas de todas as idades e origens, mas todas com algo em comum: a paixão e o interesse pelas linguagens-mestre do mundo da programação.

Começo esse artigo agradecendo a todos os que direta e indiretamente participaram para o sucesso do evento, entre eles os organizadores, o carro-chefe responsável por acordar o espírito C++ da galera no início do ano, os palestrantes e, claro, óbvio, toda a comunidade C++ que participou em corpo (vulgo hardware) e alma (vulgo software).

Termino a introdução fazendo uma minicrítica ao preço pago pelos participantes. Não que eu ache que seja muito, pelo contrário: dado o alto nível técnico das palestras, parece até mentira termos acesso a um evento com essa estrutura por tão pouco. Porém, o muito e o pouco são relativos, e ainda acredito que existam pessoas que não vão aos encontros por falta de recursos. Por isso mesmo vai um apelo para que nos futuros encontros tenhamos alguma forma de permitir às pessoas menos favorecidas de participar democraticamente dessa que é a expressão viva das linguagens C e C++ em nosso país.

Vamos às palestras!

Dicas e Truques de Portabilidade, por Wanderley Caloni

É muito difícil analisar uma palestra feita por você mesmo. É mais difícil ainda quando essa palestra é a primeira de uma batelada de argumentações de alto nível técnico que seguiram o dia. Posso dizer, no entanto, que consegui o que queria quando fui para o evento: demonstrar as dificuldades e as facilidades de tornar um código portável, independente se entre sistemas operacionais, ambientes ou compiladores.

Foi visto primeiramente o que faz da portabilidade uma coisa difícil. Detalhes como sintaxe e gramática fazem toda a diferença quando o que se almeja é um código limpo de imperfeições trazidas pelo ambiente de desenvolvimento. Também foi dada especial atenção às famigeradas extensões de compiladores, que fazem a linguagem parecer uma coisa que não é.

Por fim, foram apresentadas algumas sugestões movidas pela experiência e estudo dessas mesmas dificuldades. Para ilustrar, dois exemplos bem vivos de como um código portável deve se comportar, tanto no código-fonte quanto em sua documentação.

Programação Concorrente com C++, por Fábio Galuppo

Artigo sobre apresentação

Para quem está acostumado com os temas geralmente "gerenciados" de Fábio Galuppo com certeza deve ter se surpreendido com a descrição teórica dos inúmeros problemas que cercam a vida do programador multithreading. O palestrante partiu do mais simples, o conceito de threads, conceito que, segundo ele mesmo, pode ser explicado em 15 minutos, para algo mais sutil e que gera muitos erros escondidos: o conceito de locks (semáforos, mutexes, etc).

Os programadores em nível de sistema devem ter adorado o contexto histórico dos problemas (você sabia que o primeiro lock inventado foi o semáforo?) tanto quanto o contexto teórico (explicação sobre modelo de memória).

Um destaque especial foram os experimentos com código rodando de verdade no Visual Studio, como o exemplo que tenta criar o maior número de threads possível na arquitetura 64. Simplesmente assustador!

Se por um lado faltou tempo para explicar os usos e princípios das bibliotecas de programação paralela disponíveis e mais usadas do mercado, por outro a palestra preencheu uma lacuna importante na minha primeira palestra sobre threads em C++, demonstrando os erros mais comuns e o que não se deve fazer em programas que rodam mais de uma thread.

Mais uma vez voltando à teoria, a palestra foca mais uma vez em bons princípios de design, como o padrão de projeto monitor e a descrição dos modelos onde é justificado o uso de mais de uma thread no programa.

Programação Multiplataforma Usando STL e Boost, por Rodrigo Strauss

Artigo sobre apresentação

Como sempre, Strauss está apaixonado pelo Boost (e a STL). Descrevendo as partes mais importantes que todo programador C++ moderno deve saber sobre essas bibliotecas, ambas modernas, a palestra focou principalmente no uso do dia-a-dia, e as vantagens produtivas que o C++ atual pode ter sobre o velho e tradicional programa em C com listas encadeadas artesanais.

Entre as coisas mais importantes citadas, que todo programador do novo século deveria saber, estão:

	
  * A total falta da necessidade de desalocarmos objetos manualmente em nossos programas, visto que o auto_ptr (STL) e shared_ptr (Boost) dão conta do recado de maneira impecável.

	
  * A total falta da necessidade de usarmos aqueles velhos _arrays _em C que quase nunca sabemos o tamanho exato para guardar nossos valores (e que continuamente colocávamos com o tamanho 100, MAX_PATH, ou UM_OUTRO_DEFINE_COMUM_EM_LINUX). A classe boost::array provê todas as funcionalidades básicas, além das avançadas, do uso de _arrays _tradicionais, sem qualquer _overhead_ adicional de um _array _em C.

	
  * A total falta de necessidade de ficar convertendo _strings _e inteiros. Com a ajuda da classe std::string e de construções geniais como lexical_cast (Boost), felizmente podemos deixar nossas velhas funções que precisavam de um _buffer_, como _itoa (embora não-padrão).

Enfim, para quem pôde ver, a palestra focou nos princípios que farão hoje em dia um programador C++ completo, profissional e que, como seus colegas de outras linguagens, se preocupa igualmente com a produtividade de seu código. Ah, sim, e não gosta nem um pouco de reinventar a roda.

Técnicas de Otimização de Código, por Rodrigo Kumpera & André Tupinambá

Aparentemente o que pensei que seria, em minha sincera opinião, um desastre (dois palestrantes falando sobre a mesma coisa) se transformou em uma combinação estupenda de teoria e prática aplicadas à arte de otimização de código. Rodrigo e André conseguiram destrinchar o tema harmoniosamente, sempre dividido entre técnicas avançadas (algumas demonstradas pela experiência dos palestrantes) e teoria disciplinar, que visa alertar o wannabe que otimizar pode ser uma coisa boa; porém, preste atenção aos que já fizeram isso têm a dizer.

Com uma didática impecável, o novato nesse tema (como eu) pôde ver as dificuldades de conseguir determinar o objetivo de todo otimizador de código que, segundo eles, deve estar sempre atento na máxima de que "toda otimização é na verdade uma troca". Ou seja, se o programador quer melhor processamento, pagará com memória, se quiser otimizar espaço na RAM, irá gastar mais com processamento e/ou disco, e assim por diante.

Foram apresentados exemplos reais de otimização, além de dicas muito importantes sobre o comportamento das compilaçõe de cada dia.  Você sabia, por exemplo, que ao declarar em escopos mais locais suas variáveis usadas apenas em pequenos trechos de código, estará dando uma poderosa dica ao compilador para que ele consiga usar os registradores no máximo de sua capacidade?

Ao final, como é de praxe, tivemos um sorteio de ótimos livros sobre programação e C++ em geral, com destaque aos livros do Herb Sutter. Rodrigo Strauss, conhecido fundador dos encontros, recebeu sua mais que merecida homenagem ao receber um de seus livros autografados. É o mais novo MVP da comunidade!

E por falar em comunidade, e agora podemos ver claramente, estamos com uma força bem maior do que no início do ano. A seqüência de ótimos eventos, além de nossos mestres do conselho Jedi de programadores C++, prova finalmente que, se depender da qualidade dos desenvolvedores, o Brasil pode sim ser uma poderosa fonte de programas de qualidade que façam coisas bem mais interessantes do que acessar um banco SQL. Nós já temos a matéria-prima.

	
  * Discussão sobre o evento na nossa lista

Imagens do evento cedidas por Fernando Roberto (valeu, Ferdinando!).
