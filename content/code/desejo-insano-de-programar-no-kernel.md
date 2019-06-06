---
date: "2007-07-12"
title: Desejo insano de programar no kernel
categories: [ "code" ]
---
Muitas vezes meus amigos (um em particular) me perguntam por que não me interesso em programar em _kernel mode_, como se isso fosse um objetivo a ser alcançado por qualquer programador em _user mode_. Bom, não é.

Claro que sempre me empenho em entender como o sistema funciona, nos menores detalhes e sempre que posso, o que nem sempre me leva para o _kernel mode_ (entender [como a CLR funciona](http://www.amazon.com/Shared-Source-Essentials-David-Stutz/dp/059600351X/ref=pd_bbs_sr_1/002-5397975-3432020?ie=UTF8&s=books&qid=1184149958&sr=8-1), por exemplo). Posso até me considerar um ser privilegiado, já que trabalho com dois _experts_ em _kernel mode_ e .NET, respectivamente. Isso já faz algum tempo, e ambos possuem conhecimento e experiência necessários para sanar minhas dúvidas mais cruéis. Porém, uma coisa é o **conhecimento** da coisa. Outra coisa é a prática. E **a teoria**, como já dizia o Sr. Heldai, **na prática é outra**.

**Baixaria de qualquer jeito**

Existem também aqueles programadores que, entorpecidos pela idéia de que seu _software_ deve ser o mais baixo nível possível porque... bem, porque ele faz coisas muito profundas (?), ou é muito avançado (??), ou talvez até porque ele precisa ser otimizado ao máximo. Baseados nessas premissas (???), antes mesmo de conhecer o sistema operacional e pesquisar o que ele tem a oferecer que [já está disponível](http://msdn.microsoft.com) em _user mode _partem direto para a programação nua e crua, pelo simples motivo de ser legal ou na ilusão de ser a melhor maneira de se fazer as coisas sob qualquer circunstância.

Munidos de bons motivos para fazer _drivers, _o próximo passo seria então **pedir ajuda desesperadamente** (e urgentemente) em listas de discussões. Talvez esse seja o lugar menos apropriado para procurar por uma palavra amiga. Acompanhei por um tempo [uma lista de _kernel_ do Windows](http://www.osronline.com/page.cfm?name=ListServer). Apenas para efeitos de descrição, o clima e a impressão com que fiquei de lá foi que os programadores em _kernel_ não se dão muito ao trabalho de ajudar aqueles que estão perdidos no _ring0_. Então para que existe a lista? Aparentemente para aqueles que já sabem fazer o carro andar, já conhecem o motor e um pouco de mecânica dos fluidos.

Digamos que é uma cultura bem diferente do que estamos acostumados a vivenciar em _user mode. _Eles estão muito mais ocupados com problemas relacionados especificamente com o desenvolvimento de _drivers_, e não dúvidas bestas do tipo "como eu faria isso". Lá não se briga entre linguagens gerenciadas e não-gerenciadas (nem entre linguagens gerenciadas), mas entre linguagens C e C++. Lá não se ajuda a fazer aquelas "gambis" que tanto ajudam o programador na hora do sufoco, mas sim redirecionam os hereges para o desenvolvimento "politicamente correto" (siga a documentação e seja feliz).

Isso não é uma crítica destrutiva, apenas uma descrição narrativa. Nada que falo aqui é exagero ou blasfêmia. Podem perguntar para o [meu amigo de ](http://www.driverentry.com.br)_[kernel mode](http://www.driverentry.com.br)._ Aliás, use o _blog_ dele para aprender um pouco sobre o _kernel._

**Então o que é esse tal de _kernel programmer_? **

O fato é que bons programadores são bons onde quer que eles estejam (e os ruins serão ruins em qualquer lugar). E ser um desenvolvedor de qualidade exige **tempo, dedicação, paciência e estudo**. Pode ser um _designer_ usando Action Script ou um engenheiro da NASA projetando foguetes. Tanto faz. Fazer as coisas com qualidade sempre exigirá mais tempo do que gostaríamos de despender. Não é uma questão de ser mais difícil em _kernel mode_ ou mais fácil em Javascript. É saber qual dos dois será necessário usar para atingir o nível de funcionalidade e qualidade que o projeto exige. O resto é preconceito.
