---
date: "2007-09-14"
tags: [ "code", "draft",  ]
title: "Aquisição de recurso é inicialização"
---
O título desse artigo é uma técnica presente no paradigma da programação em C++, razão pela qual não temos o operador finally. A idéia por trás dessa técnica é conseguirmos usar recursos representados por objetos locais de maneira que ao final da função esses objetos sejam destruídos e, junto com eles, os recursos que foram alocados. Podemos chamar de recursos aquele arquivo que necessita ser aberto para escrita, o bitmap que é exibido na tela, o ponteiro de uma interface COM, etc. O nosso exemplo é sobre arquivos:


Ignorei tratamento de erros e a dor de cabeça que é a discussão sobre inicializações dentro do construtor, matéria para um outro artigo. Fora os detalhes, o que temos é: 1. uma classe que se preocupa em alocar os recursos que necessita e no seu fim desalocá-los, 2. uma função que usa um objeto dessa classe, alegremente apenas preocupada em usar e abusar do objeto. A demonstração da técnica reside no fato que a função não se preocupa em desalocar os recursos alocados pelo objeto config. Algo óbvio, desejável e esperado.

Para vislumbrarmos melhor a utilidade dessa técnica convém lidarmos com as famigeradas exceções. A possibilidade de nossa função ou alguma função chamada por essa lançar uma exceção enquanto nosso objeto está ainda construído - e com o recurso alocado - faz com que seja vital a classe do objeto ter sido bem construída a ponto de prever essa situação e liberar os recursos no destrutor. Daí o uso da técnica se torna necessário.

Por outro lado, ao usarmos objetos, devemos ter plena confiança nas suas capacidades de gerenciar os recursos que foram por eles alocados. Só assim se tem liberdade o suficiente para nos concentrarmos no código da função e solenemente ignorarmos a implementação da classe que estamos utilizando. Afinal, temos que considerar que muitas vezes o código-fonte não está disponível. Veja a mesma função com uma chance de desvio incondicional (o lançamento de uma exceção):


Nesse exemplo tudo funciona, certo? Até se a exceção for lançada, o recurso será desalocado, pois o objeto é destruído. Isso ilustra como várias técnicas de C++ podem conviver harmoniosamente. Mais que isso, se ajudam mutuamente. O que seria das exceções se não existissem os construtores e destrutores? Da mesma forma, os recursos são alocados e desalocados baseado na premissa de construção e destruição de objetos. Por sua vez, essa premissa vale em qualquer situação, existindo ou não exceções.

Agora, e se a exceção de BlowUpFunction é lançada e a classe File não está preparada para fechar o arquivo no destrutor? Esse é o caso da versão 2 de nossa classe File, logo abaixo. Apesar de ser a segunda versão ela foi piorada (acontece nas melhores famílias e classes):


Nesse caso o código de UseFile2 acaba deixando um recurso alocado por conta de uma exceção que ocorreu em uma função secundária chamada lá pelas tantas em um momento delicado demais para ocorrerem exceções. Note que o destrutor de File2 é chamado assim como o de File, só que este não libera os recursos do objeto. Ele não usa a técnica RAII (Resource Acquisition Is Initialization, ou o título do artigo em inglês).

Nesse tipo de classe o convívio com exceções gera um dilema: onde está o erro? Como consertá-lo? Se o problema é encontrado numa hora apertada e temos cinco minutos para revolver isso, capturar a exceção causada por BlowUpFunction é uma boa idéia. Só que nem sempre as soluções de cinco minutos são as mais maduras. Podemos não saber muito bem o que fazer com esse tipo de exceção, por exemplo. Isso geraria um tratamento de erro ou redundante - se tratarmos ali mesmo o Scatadush, já tratado em um escopo mais externo - ou fragmentado - se apenas desalocarmos o recurso de File2 e relançarmos a exceção. Eu nem diria fragmentado, pois estamos tratando um erro inventado, se considerarmos que é função dos objetos desalocarem os recursos que foram por eles mesmos alocados.

A opção que dura mais de cinco minutos pode evitar futuras dores de cabeça: arregaçar as mangas e refazer a classe File2 observando o princípio de RAII. Possivelmente algo na interface deverá ser alterado, o que causará a alteração de mais códigos-fonte que utilizam essa classe. Alterar mais códigos-fonte significa testar novamente mais partes do software, algumas nem de perto relacionadas com o problema em si. Ou seja, não é cômodo, mas é íntegro. Sabendo que futuras funções que usarem essa classe já estarão corretas, mesmo que uma exceção seja lançada e não seja capturada, é um dado significativo: representa produtividade futura.

A decisão sobre qual solução é a melhor está muito além do escopo desse artigo, pois obviamente cada caso é um caso. Mas não custa nada pensar um pouco sobre C++ quando se estiver programando. E "aquisição de recurso é inicialização" faz parte do modo de pensar dessa linguagem.
