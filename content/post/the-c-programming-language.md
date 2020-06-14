---
categories: [ "code" ]
date: "2007-10-12"
tags: [ "draft", "books" ]
title: "A Linguagem de Programação C"
---
O clássico de Ritchie e Kernighan, criadores da linguagem C, não foi meu primeiro livro de programação. E nem deveria ser. Não o recomendo para iniciantes, pois é necessário possuir algun conhecimento e prática para realmente aproveitar os conceitos desse livro.

Então, o que ler antes disso? Existem tantos livros bons para iniciantes (e tantos livros péssimos). Eu comecei com C Completo e Total, de Herbert Schildt. Não me arrependi. O autor vai descrevendo C para quem já tentou fazer algumas coisas, já programou outras e está afim de tirar as principais dúvidas sobre essa linguagem que tantos abominam por ser difícil, e tantos idolatram por ser poderosa. As práticas do livro já são um bom início para quem quer pensar, entender e programar.

Depois de Schildt, passei a ler os livros da Viviane, os famosíssimos módulos do Treinamento em Linguagem C. São ótimos para a prática e para reafirmar os conceitos lidos no primeiro livro. Para uma linguagem tão importante, uma segunda opinião é sempre bem-vinda.

Então chegou a hora. Passei algumas das minhas melhores horas na biblioteca lendo como os próprios criadores da linguagem a ensinam, e como o padrão ANSI é definido (em termos bem simplificados, condição perfeita para entender a lógica do compilador). Com o livro é possível perceber claramente que a linguagem é tão simples quanto poderosa, lembrando (quem diria!) o mais abominado ainda assembly.

Vamos aos capítulos.

O começo é quase sempre o mesmo. Os autores explicam um programa simples na linguagem, fazem alguns testes e explicam linha a linha o que cada coisa significa. O importante aqui é esquecer que existe um sistema operacional rodando por baixo de nosso programa e entender que a linguagem foi desenhada para independer disso. É tão genérica a ponto de independer dela mesma. Explico: enquanto a maioria das linguagens considera sua biblioteca parte integrante da mesma, a linguagem C faz questão de separar as coisas, reafirmando sempre que uma coisa é o preprocessamento, outra é a compilação, outra é a linkedição e nenhuma delas precisa de uma biblioteca, apesar de uma ter sido definida no padrão (baseada no uso comum da linguagem em diversos ambientes).

Se você nunca teve contato com C ou deseja ter uma aproximação mais simplificada e quer entender como as coisas mais simples funcionam na linguagem, este capítulo é imperdível.

Essa é a hora ideal para separar dois conceitos que muitas vezes ficam grudados na mente dos precoces programadores para o resto de suas vidas: uma coisa é um tipo e outra coisa é uma expressão. Uma expressão possui um tipo, que define seu comportamento de acordo com o operador usado. Tudo é explicado muito bem com exemplos bem escritos e que são realmente úteis, como strlen, atoi, strcat (presentes na biblioteca padrão) e até um contador de bits.

Se quiser entender o que cada fragmento de lógica na linguagem significa por completo (e não apenas uma expressão jogada na correria da programação do dia-a-dia) esse capítulo irá explicar. Depois de entendê-lo, nunca mais vai achar bizarro aqueles problemas de precedência que permeiam código pouco sensato.

Apenas após ter explicado os conceitos que regem qualquer linha de código operacional em C os autores se dedicam a explanar as diversas formas de controlar o fluxo do seu programa. Nessa hora a linguagem se desdobra, se torna mágica, simples, flexível e poderosa.

Não basta apenas possuir lógica de programação. Para escrever bons programas é necessário saber como construir os blocos funcionais que irão traduzir seus comandos para o computador. É nesse ponto que é fundamental o domínio de qualquer construção em C, seja um simples if ou uma combinação maluca de switches, whiles e breaks.

Entendidos os princípios básicos de criação e execução de qualquer programa em C, chegou a hora de explicar como a linguagem suporta a organização de seu código através de funções, módulos e diretivas de preprocessamento. Note que os autores partem do princípio minimalista da linguagem e imagina o que acontece conforme seus programas vão se tornando cada vez maiores. Para isso explicam o mesmo princípio que foi utilizado ao desenhar a linguagem, que até hoje é usada para escrever dezenas de milhares de código em um único projeto, ou até milhões (como em sistemas operacionais).

No desenvolvimento de software a organização é um dos pilares que irá transformar o programador em um mestre da arquitetura de seu próprio código. Não negligencie a lógica das partes maiores do seu código, só se importando com os pequenos pedaços de blocos dentro de uma função. Antes de ser cientista, seja um desenvolvedor nato.

A dificuldade com que muitos programadores C têm com essas duas características da linguagem fizeram com que fosse dedicado um capítulo inteiro para explicar e reexplicar como os arrays (vetores) e ponteiros funcionam e qual a relação intrínseca entre eles. É também explicada a relação strings x arrays, já que em C uma string é uma cadeia de caracteres.

Se você programa em C e até hoje tem dificuldades para entender completamente esse assunto, sugiro que largue o que você está fazendo agora e leia esse capítulo até o final. Será bem mais proveitoso que ficar zanzando no meio de um monte de blogues (como este aqui).

A estrutura é uma composição complexa em C, mas permite um organização melhor dos dados, da mesma maneira com que as funções organizam melhor o código.

Aparentemente o tema estrutura é mais simples que ponteiros, e deveria ser tratado antes. Porém, fazer isso impediria abordar o tema de listas ligadas e outras estruturas que dependem do uso de ponteiros para que estruturas referenciem elas mesmas, algo extremamente recorrente no mundo da programação.

É sempre bom lembrar que o uso de estruturas foi o nascimento do C++, que prima pela elegância na organização e harmonia entre seu código e dados. A linguagem C também não fica para trás, mas é importante saber usar.

Para finalizar é abordado o tema da interface com o mundo exterior da linguagem. Desde sempre suportando a maneira mais básica, genérica e portátil de qualquer sistema operacional, o console, talvez hoje essa característica seja um tanto menosprezada pelos usuários de ambientes gráficos. Contudo, não deixa de ter seu valor ainda hoje, nem que seja para escrever programas de teste.

Os adendos são incrivelmente úteis e os utilizo ainda hoje como referência. Cá entre nós, o padrão formal da linguagem é algo chato de se ler, e muitos detalhes são perfeitamente ignoráveis para quem não está desenvolvendo um compilador. Contudo, acredito que a maioria dos bons programadores deveria se preocupar em entender como os compiladores entendem seu código, pois muitos dos erros podem ser facilmente resolvidos através do desenvolvimento de uma certa empatia com a linguagem. É por isso que considero o Apêndice A o mais útil de todos.

Por outro lado, sempre fui contra a reinvenção da roda. O que quer dizer que sempre fui a favor do pleno conhecimento da biblioteca padrão, pois ela fornece funções das mais usadas no dia-a-dia, e algumas outras que poderão ter sua serventia um dia desses. Mas para isso elas devem ser conhecidas. Isso quer dizer que uma passada de olhos no Apêndice B não faz mal a ninguém.

O Apêndice C hoje é um pequeno guia dos curiosos para as mudanças que foram infligidas na linguagem quando esta foi padronizada. Como fã incondicional de C, não pude deixar de ler e reler essa parte, já que me dedico também a conhecer os primórdios dessa linguagem. Contudo, é parte opcional para as pessoas práticas (a não ser que você esteja com problemas com código legado do século passado).

Livros vêm, livros vão, mas apenas os clássicos permanecerão. A Linguagem de Programação C é um clássico, sem sombra de dúvida, e nunca irá perder seu valor para a linguagem. A maioria dos livros usa-o como referência, assim como os livros tão amados da comunidade C++ sempre usam Stroustrup como referência. Portanto, se puder, reserve um tempo para o passado.
