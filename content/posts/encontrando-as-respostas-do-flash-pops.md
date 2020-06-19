---
categories: [ "code" ]
date: "2008-01-16"
tags: [ "draft",  ]
title: "Encontrando as respostas do Flash Pops"
---
Existe uma série de jogos no sítio da UOL onde você deve acertar o nome de filmes, programas de televisão, entre outros, que vão da década de 40 até a atualidade. É divertido e viciante fazer pesquisa na internet para encontrar os resultados, ainda mais quando já se é viciado em cinema. Ficamos jogando, eu e minha namorada, por semanas a fio. Quase chegamos a preencher tudo, e por um bom tempo ficamos travados para terminar. Então começamos a apelar para o Google e o IMDB até os limites do razoável. Nesse fim de semana, por exemplo, chegamos a assistir um filme de madrugada onde tocou rapidamente um trecho de uma das músicas que faltava no jogo sobre televisão. No dia seguinte procuramos a trilha sonora do filme, ouvimos faixa a faixa e procuramos o nome da música no Google, para finalmente encontrar o resultado.

Essa foi a última resposta "honesta". Depois resolvi apelar para o WinDbg =)

A primeira coisa que pensei a respeito desse jogo foi que ele não seria tão ingênuo a ponto de colocar as respostas em texto aberto, do contrário, qual seria a graça, certo? Errado! Bom, no final das contas, um passo-a-passo bem simples me levou a encontrar a lista de respostas.

A primeira coisa a fazer é carregar o jogo na memória do navegador. Em seguida, seguindo meu raciocínio inicial, digitei a primeira resposta do jogo.

A partir daí, podemos "atachar" o WinDbg no processo do navegador e rastrear a memória do processo.


[](/images/win-pan.mp3)Então, como eu dizia, não faça isso em casa enquanto estiver digitando um artigo de seu blogue dentro do navegador. Ele vai travar!


OK. A primeira coisa é procurar pela string digitada, na esperança de achar a estrutura que escreve as respostas de acordo com a digitação. Isso pode ser feito facilmente graças ao WinDbg e ao artigo de Volker von Einem que ensina como procurar strings por toda a memória de um processo (mais tarde iremos também usar o comando-bônus do comentário de Roberto Farah).


Interessante. Dois resultados. Olhando o primeiro deles, vemos que encontramos o que queríamos sem nem  mesmo tentar quebrar alguma chave de criptografia.


O segundo, porém, não parece uma lista de respostas, mas sim a resposta que acabamos de digitar no navegador.


Para se certificar, rodamos novamente o navegador, apagamos a resposta e refazemos a busca.


De fato, a lista de respostas é tudo que encontramos.

Assim como no artigo sobre carregamento de DLLs arbitrárias,  vamos usar o muito útil comando .foreach, que caminha em uma lista de resultados de um comando para executar uma lista secundária de comandos. Apenas para relembrar, a sintaxe do foreach é a seguinte:


	
  * Variable. Um nome que usamos no OutCommands. Representa cada _token_ do resultado de InCommands.

	
  * InCommands. Um ou mais comandos que executamos para gerar uma saída na tela. Essa saída será usada em OutCommands, onde Variable é substituído por cada _token_ da saída.

	
  * OutCommands. Um ou mais comandos executados usando a saída na tela de InCommands.

Para o .foreach, um token é uma string separada por espaço(s). A saída dos comandos do WinDbg nem sempre vai gerar algo que podemos usar diretamente, como no caso da busca que fizemos inicialmente. Apenas para demonstração, vamos imprimir todos os tokens da saída de nosso comando.



Isso acontece porque ele utilizada cada palavra separada por espaços da saída da busca.


Por isso usamos a flag [1], que faz com que o comando imprima apenas o endereço onde ele encontrou a string.


Enfim, vamos ao que interessa. Para imprimir todas as strings que representam as respostas, podemos simplesmente, no OutCommands, fazer uma nova busca por string, só que dessa vez genérica, dentro de uma faixa razoável (digamos, 4KB).


Bom, vou parar o dump por aqui, já que, entre os leitores, pode haver quem queria se divertir primeiro do jeito certo =)

Vimos que o jogo é facilmente quebrável porque armazena as respostas em texto claro. Uma solução alternativa seria utilizar um hash com colisão próxima de zero. Com isso bastaria trocar as respostas possíveis por hashs possíveis e armazená-los no lugar. Quando o usuário digitasse, tudo que o programa precisaria mudar era gerar um hash a partir da resposta do usuário e comparar com o hashs das respostas válidas.

Por uma incrível coincidência, esse truquezinho eu aprendi com meu amigo Thiago há poucos dias, que está lendo Reversing. Simples, porém funcional.
