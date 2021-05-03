---
categories:
- blog
date: '2007-10-04'
title: Cronogramas
---

Nunca fui muito bom em definir cronogramas e nunca conheci alguém que fosse. Porém, ultimamente, no conforto do lar (férias), estou me saindo razoavelmente bem ao aplicar no meu dia-a-dia algumas regras que estabeleci como sendo boas pra mim. Não são regras que baixei do sítio do Joel nem é um design pattern, mas já me ajudam um bocado. Gostaria de compartilhá-las com meus pontuais leitores, que sempre entregam seus projetos em dia e nunca se esquecem de comentar uma linha de código sequer. Vocês são meu objetivo de vida e motivo de orgulho deste humilde blogue, que se esmera a cada dia que passa para ser fiel à inegável qualidade do meu público. Quando crescer quero ser igual a vocês.

Mas enquanto não sou, vamos às regras.

O primeiro grande passo é admitir que acertar cronogramas é como acertar na loteria: milhões de pessoas tentam toda semana e uns poucos gatos pingados conseguem de vez em quando. E ainda assim por acaso. O importante nessa analogia é perceber que, independente de ser difícil de acertar, isso não impede as pessoas de tentar. Veja você, elas (normalmente) não jogam 1, 2, 3, 4, 5, 6. Por quê? Porque elas tentam jogar no que acreditam ser uma combinação mais provável. E antes que um sábio chinês diga que a chance de sair a seqüência 1, 2, 3, 4, 5, 6 é tão provável quanto qualquer outra, explico que a analogia aqui é psicológica, não matemática. As pessoas tentam acertar, por mais irracional que isso pareça. A mesma filosofia deve ser seguida para cronogramas. Não chute valores que estão dentro da sua zona de conforto, mas tente de fato chegar o mais próximo possível da realidade. E, quem sabe um dia, você não é sorteado.

A segunda regra reza que o tempo estimado vira tempo mínimo. Você fará uma tarefa em uma hora. Mas, diabos, você não sabe disso antes de fazer e coloca no cronograma três horas. Quanto tempo você vai levar agora? Três horas. Não que você não consiga em menos tempo, mas, ao "alargar" a janela de tempo para três horas, seu ritmo irá seguir essa premissa e será mais lento. Há uma explicação psicológica para isso chamada Lei de Parkinson [^1]. Obviamente que o inverso não é verdadeiro. Quer dizer, você não vai terminar uma tarefa de uma hora em dez minutos se colocar dez minutos na sua tabela mágica. Isso, mais uma vez, não é matemática: é psicologia.

> A mesma analogia absurda serve para valores muito altos. Se estimar três meses para uma tarefa de uma hora, terá três meses para procurar um emprego novo, e não para terminar a tarefa.

A terceira regra diz sobre o tamanho das tarefas: as menores são mais exatas. Este é o velho ditado de dividir para conquistar. Afinal, é muito melhor estimar o tempo para fazer uma nova função do que estimar o tempo total para a nova versão do produto. Portanto, trate de dividir o seu elefante. O limite é a partir do momento em que se sentir confortável para prever o tempo necessário a ser gasto em uma subtarefa. É muito simples ilustrar e entender esse conceito com código. Voltando ao caso da função, digamos que você consiga terminar a bendita função em exata uma hora. Você é bom, hein?

Porém, essa função ainda:
	
 - não foi comentada,
 - não foi testada,
 - não foi testada em release.

Logo, essa é uma tarefa em que você termina o mais importante em uma hora... mas não termina tudo. Deve-se sempre considerar a tarefa por completo, pois no final de quinze tarefas vai faltar comentar e testar tudo isso, o que aumentará consideravelmente a imprevisiblidade no seu cronograma.

Seja honesto consigo mesmo e com seu chefe: você realmente trabalha 8 horas por dia? É lógico que não! E não é nenhuma vergonha admitir isso. Todos nós temos emails para ler e responder, reuniões para presenciar e blogues importantes para acompanhar. Portanto, ignore essa conversa fiada de 8 horas e admita: não se deve contar os dias como se eles tivessem 8 horas. Ninguém é produtivo programando 8 horas seguidas. Essa pessoa está te enganando ou usando cocaína (que não pode ser usada todos os dias).

Qual o valor de um dia, então? Cada um sabe o valor que deve ser decrementado desse valor simbólico de 8 horas, mas esse valor sempre será menor. Não se iluda! Se precisar harmonizar seu cronograma com um relatório para entregar para o chefe você pode usar de maneira privada o seu contador pessoal, por exemplo, trabalho 4 horas no máximo programando por dia, e converter para torná-lo público, multiplicando por dois para dar as 8 horas diárias.

A maneira com que eu administro meu tempo tenta (eu disse tenta) seguir as regras até aqui dispostas. Além dessas eu adicionei algumas regras minhas, baseadas em valores razoáveis e premissas consideravelmente lógicas. Aliás, isso me lembra uma última regra geral: entenda o seu ritmo.

O cronograma costuma (deveria) ser considerado uma coisa pessoal. Por quê? Porque cada um tem seu tempo. O que vale mais ao executar uma tarefa geralmente é (deveria ser) qualidade, e não quantidade. Seu vizinho de baia costuma terminar as coisas na metade do tempo que você? Bom para ele. Porém, se você tenta empregar o mesmo ritmo ao seu dia-a-dia vai ter que gastar depois mais do dobro do tempo que você economizou corrigindo os erros de uma tarefa feita nas coxas. Nada é "de grátis".

Encare o trabalho assim como dormir: cada um tem o seu número de horas noturnas para descansar. Se dormir mais ou menos que o normal isso irá influenciar mais tarde, quando acordar. Alguns dormem 4, outros 12 horas. A média é 8. Mas e daí?

Primeiro eu tento usar um princípio que a maioria das pessoas conhece e a minoria acredita: se chama princípio de Pareto. Ele diz que 20% de uma tarefa resolve 80% dos problemas. Aos poucos eu fui acreditando nele até que cheguei à conclusão que deve funcionar, porém existe um problema: definir quais são esses 20%.

Voltando novamente no caso da função, é óbvio que a parte mais importante é fazer a função. Mais uma vez, cada caso é um caso, e o importante é desenvolver esse feeling do que é mais importante. Fazendo o que é mais importante o resto virá complementar a solução.

Essa ordem do que é mais importante deve servir para dividir qualquer tarefa e as tarefas de cada dia, ordenadas por importância. Dessa forma, é fácil começar o dia ou uma tarefa maior pelo que é mais importante. Isso nos leva a um segundo problema: definir o que é importante.

A maior dificuldade em definir o que é importante é que muitas vezes ele se confunde com o que é urgente, mesmo sendo dois conceitos bem diferentes.

Por exemplo, para mim foi urgente escrever este artigo, já que estou compromissado com a freqüência do meu blogue. O importante fica por conta do conteúdo. Por exemplo, considero ter tocado em todos os pontos que julgo importantes para esse tema, o que por si só caracterizaria o fim desse artigo. E é isso aí.

Bons cronogramas!

[^1]: "O trabalho se expande work de forma a preencher o tempo disponível para sua conclusão." - [Parkinson's Law na Wikipedia]

[Parkinson's Law na Wikipedia]: https://en.wikipedia.org/wiki/Parkinson%27s_law