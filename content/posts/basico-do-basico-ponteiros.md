---
categories:
- code
date: '2008-12-06'
tags:
- draft
title: 'Básico do básico: ponteiros'
---

![Alicerces de uma casa.](http://i.imgur.com/8jW9wJy.png)Nessas últimas semanas tenho gastado meu tempo junto da mais nova pupila da [SCUA](http://www.scua.com.br), aspirante a programadora em C e Install Shield Script. Minha tarefa? Explicar tudo, desde o mais simples, como **variáveis**, até as coisas não tão triviais, como **símbolos de depuração**.

Posso afirmar que tem sido muito compensador ativar algumas partes do meu cérebro que acreditava nem mais existirem. Rever velhos conceitos, apesar de manjados, nos dá a oportunidade de lembrar que as coisas mais complexas que construímos no dia-a-dia se baseiam em um punhado de preceitos básicos que é essencial ter na cabeça. E nunca esquecê-los.

Meu amigo costuma chamar esses preceitos básicos de **fundamentais**. Isso por um bom motivo lógico e semântico: tudo que aprendemos de básico sobre qualquer área de conhecimento serve-nos de **base** para suportar as outras coisas que virão a ser entendidas na mesma área de conhecimento. Ou seja: é **a parte mais importante a ser aprendida**. Sem ela, a base, não nos é possível construir nada **sólido** e **duradouro**. Sem ela, toda a estrutura construída _a posteriori_ se rompe e vai abaixo.

Foi partindo desse princípio que me preocupei com esmero para explicar as peças mais fundamentais do conhecimento em jogo, formadoras da cabeça de um programador para sempre, seja em C como em qualquer outra linguagem. E como nada é bem explicado sem formar imagens na cabeça, aproveitei para desenhar alguns esboços no papel. O resultado desses esboços é esse artigo.

#### Ponteiro: o eterno vilão da história

Não tenho a presunção de conseguir explicar 100% para alguém iniciante o que são ponteiros em C, como usá-los e como se proteger deles. Definitivamente ponteiro não é um conceito simples, apesar de básico, e posso dizer sem vergonha que demorei cerca de seis meses no meu aprendizado em C pra entender completamente tudo relacionado com ponteiros. Demorou, quebrei a cabeça, mas depois nunca mais esqueci.

De acordo com o meu amigo [Rafael](http://www.sk5.com.br), a melhor definição que usei até hoje para explicar esse conceito envolvia um armário repleto de gavetas, todas numeradas em ordem de posição (1, 2, 3...). Cada gaveta podia guardar qualquer coisa, inclusive o número de outra gaveta em um pedaço de papel. Com isso, eu poderia guardar em uma gaveta aleatória o que eu precisava guardar e escrever o "endereço" dessa gaveta em um pedaço de papel e guardá-lo na gaveta número 1, por exemplo. Com isso poderia até esquecer a posição onde está o que eu guardei, pois bastava abrir a gaveta número 1 e ler a posição em que estava essa gaveta.

Deve ter ficado óbvio, mas se não ficou: o armário é a memória RAM, as gavetas são váriáveis e as gavetas onde guardamos pedaços de papel são ponteiros, que não deixam de ser variáveis, e apontam para outras gavetas que são... adivinha? Outras variáveis!

[![Gavetas representando posições na memória.](http://i.imgur.com/sx9fYjS.gif)](/images/pointers-drawer.gif)

[
](http://i.imgur.com/GcnMNxv.jpg)

Outros conceitos que costumo utilizar é relacionar a memória RAM com a memória do programa e contar a memória como se contam carneirinhos. Dessa forma fica fácil pelo menos entender dois conceitos fundamentais na arte dos ponteiros: memória e endereço.

#### Practice makes perfect

O segundo passo, acredito eu, é entender como a memória é dimensionada através do programa, e como o tipo molda a representação dos bits e bytes através das ligações de silício, mas isso fica pra mais tarde. Temos que programar, e é isso que vai de fato fazer a diferença no aprendizado de uma linguagem como C. Nada como uma boa mistura de teoria e prática para gerar um concreto armado que irá suportar um [Empire State](http://pt.wikipedia.org/wiki/Empire_State_Building) de conhecimento.

Por isso, segue uma lista de tarefas interessantes para exercitar o conceito de ponteiros:

	
  * Criar funções que modificam números passados como parâmetro.

	
  * Criar funções que modificam texto passado como parâmetro.

	
  * Alocar e desalocar memória dinamicamente.

Tarefas mais específicas da minha área e que uso o tempo todo:

	
  * Escrever e ler texto em arquivos.

	
  * Escrever e ler no registro do Windows.

	
  * Obter o endereço de uma função do Windows dinamicamente. E chamá-la.

    Nota: Não use as classes superiores de C++ nem referências. Estou falando de estudar ponteiros nua e cruamente. Não seja preguiçoso. Algumas coisas devem ser feitas da maneira mais "primitiva" até se entender com o que se está lidando. Lembre-se que os melhores programadores possuem os alicerces mais fortes.

#### Bônus Points: Fantoches!

Este vídeo é o mais didático do universo sobre como funcionam ponteiros em C. Veja e mostre pros seus filhos:

<div class="auto-resizable-iframe"><div><iframe frameborder="0" allowfullscreen="1" src="https://www.youtube.com/embed/mnXkiAKbUPg"></iframe></div></div>