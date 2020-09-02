---
date: "2014-09-03"
tags: [ "code", "draft",  ]
title: "Shareando Ponteiros"
---
Apesar de ter palestrado algumas vezes sobre Boost e STL nunca escrevi muito sobre esses assuntos aqui. O tamanho dessas bibliotecas assusta um pouco. Mas temos que começar de algum lugar.

E por isso eu gostaria de saber de você, programador miserável, que passou poucas e boas nesses dez anos de padrão 98 brincando com templates quando eles ainda estavam em beta: se fosse para melhorar um aspecto da sua vida de código C++, qual seria? Qual é aquela coisa que te atormenta como insetos vidrados no seu monitor noite adentro?

Se eu fosse você reponderia: alocação de memória e ponteiros. E portanto vamos matar dois coelhos com um template só usando smart pointers, que desalocam memória quando não precisamos mais dela e mantém os ponteiros gerenciados.

"Ah, mas tem que usar uma biblioteca bizarra com milhões de dependências e que vai quebrar todo o fonte aqui da empresa. Sem contar que vai ter que passar de novo pelos unit tests, vai dar erro de compilação, a LIB XPTO não funciona sem dar três pulinhos virado para a cafeteira e..."

Cada caso é um caso, existe o melhor dos mundos e o pior. Mas (quase) todos têm solução. Mesmo que tudo que você tenha disponível seja um barbante e um clipe, podemos tentar alguma mágica/gambiarra/adaptação técnica. Vamos ver os casos mais comuns:

Um cenário perfeito para começar. A única coisa que você precisa fazer em seus novos projetos e refatorações é incluir um único cabeçalho:

E pronto! Se abriu um mundo mágico onde as alocações serão compartilhadas entre funções sem se perder quem deleta o quê. Não precisa nem checar se o ponteiro é nulo, basta alocar direto e jogar para dentro do nosso mais novo smart pointer da STL:


E pronto: você nunca mais vai precisar se preocupar com quem deleta o ponteiro, nem quantas cópias desse ponteiro andam por aí. O sharedptr da STL, assim como a versão que já tem faz um tempo no boost, mantém um contador de referência para cada cópia do objeto que mantém o mesmo ponteiro "dentro de si". Só quando esse contador chegar a zero, ou seja, não há mais ninguém referenciando essa região da memória, o ponteiro é deletado.

O std::sharedptr funciona desde o SP1 do Visual Studio 2010. Sem Service Pack ou em versões mais antigas pode haver disponível no namespace tr1, resquício de quando esse novo padrão ainda estava em definição.

Vou imaginar que você usa o Visual Studio 2003, um dos primeiros da safra ".NET", que, mais uma vez, NÃO TEM QUALQUER RELAÇÃO COM C++ .NET.

Bem, nesse caso, "welcome... to the desert... of the double":


Pois é, 37 erros. Depois perguntam por que as pessoas ficam com medo de programar em C++...

Porém, a correção é mais simples do que parece: baixar o boost e trocar o nome do namespace.


ATENÇÃO! Nos meus testes a única versão funcionando com o VS2003 foi a 1.47. Mas já é alguma coisa

Não existe situação difícil que não possa piorar. Porém, mesmo nesse caso ainda há algo a se fazer, já que smart pointer utilizam mecanismos existentes na linguagem C++ desde os primórdios (ou bem próximo disso). Tudo que você precisa para criar seu próprio sharedptr é do construtor padrão, do destrutor padrão, do construtor de cópia e dos operadores de atribuição e ponteiro. E, claro, não se esqueça de usar template se for permitido. Se não for, a coisa complica, mas não se torna impossível.



E é isso. A lição de hoje é: quem quer, arruma um jeito. Quem não quer, uma desculpa.

