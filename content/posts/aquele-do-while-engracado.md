---
date: "2008-05-15"
tags: [ "code", "draft",  ]
title: "Aquele do-while engraçado"
---
Nesses últimos dias andei conversando com um amigo que está estudando sistemas operacionais na faculdade. Melhor ainda, vendo o código real de um sistema operacional em funcionamento. A conseqüência é que, além de aprender um bocado de como as coisas funcionam de verdade debaixo dos panos, acaba-se aprendendo alguns truquezinhos básicos e tradicionais da linguagem C.

Por exemplo, é um hábito conhecido o uso de construções do-while quando existe a necessidade de definir uma macro que possui mais de um comando em vez de usar a igualmente conhecida { construção de múltiplos comandos entre chaves }.

O que talvez não seja tão conhecido é o porquê das coisas serem assim.

Vamos imaginar uma macro de logue que é habilitada em compilações debug, mas é mantida em silêncio em compilações release:


Nada de mais, e parece até funcionar. Porém, como veremos nas próximas linhas, esse é realmente um exemplo de código "buguento", já que uma chamada dentro de uma construção if-else simplesmente não funciona.



Por que isso? Para responder a essa questão nós precisamos olhar um pouco mais de perto no resultado do preprocessador da linguagem, que apenas troca nossa macro pelo pedaço de código que ela representa:


Dessa forma, podemos ver o porquê. Quando chamamos a macro, geralmente usamos a sintaxe de chamada de função, colocando um sinal de ponto-e-vírgula logo após a chamada. Essa é a maneira correta de se chamar uma função, mas no caso de uma macro, dessa macro, é um desastre, porque ela cria dois comandos em vez de um só (um ponto-e-vírgula vazio, apesar de não fazer nada, é um comando válido). Então, isso é o que o compilador faz:


; /* uma instrução nova! ok, sem else desa vez */


Pense sobre o comando vazio como se ele fosse um comando real, o que é a maneira mais fácil de entender o erro de compilação que recebemos ao compilar o código abaixo:


printf("here we go");


Por essa razão, a maneira tradicional de escapar desse erro comum é usar uma construção válida que peça de fato um ponto-e-vírgula no final. Felizmente nós, programadores C/C++, temos essa construção, e ela é... muito bem, o do-while!


;


Assim nós podemos reescrever nossa macro de logue da maneira certa (e todas as 549.797 macros já escritas em nossa vida de programador). E, apesar de ser uma construção um tanto bizarra, ela funciona melhor do que nossa tentativa inicial:


Ao usar um do-while (com uma expressão que retorna falso dentro do teste, de maneira que o código seja executado apenas uma vez) a construção if-else consegue funcionar perfeitamente:


