---
date: "2019-05-28"
link: "https://github.com/Caloni/goto"
tags: [ "code", "draft",  ]
title: "C Resolve Tudo: goto"
---
Para quem decide usar a linguagem C para resolver tudo, a gota da água é o goto. Ele é flexível, cabe em (quase) qualquer ponto do código e tem 1001 utilidades. O goto é o bombril da engenharia de software.

O uso mais simples dessa importante construção da linguagem é pular de um ponto para outro do código em que esses pontos não estão diretamente relacionados, como geralmente ocorre, como sair de um laço, não entrar em um if ou selecionar um case do switch (lembrando que no caso do case do switch ele é no fundo um goto disfarçado).



Claro que esse uso é trivial demais para valer a pena uma troca de fluxo tão desestruturada. Há formas mais úteis de desviar o fluxo padrão. No exemplo acima bastaria colocar todo o código que se segue dentro do grupo pertencente ao if e o goto seria desnecessário.

Mas, por exemplo, imagine que precisamos nos desfazer de recursos na ordem inversa ao qual vão sendo adquiridos. Pode-se aninhar indefinidamente ifs ou usar um bloco de código de unwinding que vai fechando os recursos na ordem inversa e inicia sua chamada dependendo de onde ocorreu o erro. Código é melhor para ilustrar:



Esse estilo de liberação de recursos é muito usado em códigos de kernel e software mais básico, pois simplifica a visualização e aumenta a flexibilidade. Compare com a versão estruturada:



Aliás, esse uso do goto é a maneira de aplicar RAII em C (Resource acquisition is initialization). Implícito em linguagens como C++ e seus destrutores de objetos, em C é você que precisa fazer a faxina. E se a bagunça foi feita da direita pra esquerda a faxina deve ser feita da esquerda pra direita.

Esse uso super-aninhado do código me lembra do exemplo clássico de sair de muitos loops aninhados. Apenas por didática, vamos citá-lo:


Comentei no começo do texto que os cases do switch são labels de goto disfarçados. E são mesmo. Um dos algoritmos mais famosos de transformação de loop chamado Duff's device junta um do-while com switch e realiza uma cópia de buffer com um número de bytes variável:


O que está acontecendo no código acima: é possível inserir qualquer tipo de mudança de fluxo dentro do switch. Duff aproveitou essa particularidade da linguagem para produzir jumps que poderiam ser feitos em assembly. Dependendo do resto da divisão por oito o salto é realizado para um case diferente, que executará parte do laço até o while comparador final. A vantagem desse tipo de abordagem é que evita-se sair da programação estruturada, e muito menos precisa-se apelar para o assembly.

Esse código também seria possível de ser feito com o goto clássico, mas note que nesse caso ele fica mais verboso, pois é necessário fazer um if diferente para cada condição.


Caso você tenha estranhada a definição inicial da função, ela é como se definia os argumentos em linguagem C antes do padrão ANSI, com os nomes e logo em seguida a declaração das variáveis como se fossem locais (porque de fato elas são, embora sua inicialização seja feita antes da chamada). Como este código data dos anos 80 e como o padrão só foi finalizado em 89, percebe-se que ainda se usava o formato antigo no código.

Passemos para o próximo uso: código infinito. Esse é um uso clássico, e diferente do uso degenerado de laços em que a condição é sempre verdadeira (while(true), for(;;)) usando o goto fica bem-documentado que o objetivo é ficar eternamente nesse loop. Um laço infinito que eu me lembro é quando dá tela azul no Windows. O código-fonte do kernel era algo mais ou menos assim:


Os programadores usaram o apelo clássico do while. Sem motivo, pois goto é usado direto como RAII (já explicado acima). A maneira procedural de fazer seria assim:



Isso lembra outra utilidade do goto que você pode anotar no seu caderninho: ele pode voltar o fluxo, de baixo para cima.

Esse último exemplo é um dos programas C mais lindos do universo. Sua única instrução é o comando rotulado por infinite e referencia ele mesmo. É quase o salto incondicional do assembly, materializado na linguagem mais elegante jamais criada em nossa realidade.
