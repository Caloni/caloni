---
date: "2007-10-04"
title: Cronogramas
categories: [ "blog" ]
---
[![Dali Clock](http://i.imgur.com/r1DCuSS.jpg)](http://www.caloni.com.br/blog/cronograma/dali-clock)Nunca fui muito bom em definir cronogramas e nunca conheci alguém que fosse. Porém, ultimamente, no conforto do lar (férias), estou me saindo razoavelmente bem ao aplicar no meu dia-a-dia algumas regras que estabeleci como sendo boas pra mim. Não são regras que baixei do [sítio do Joel](http://brazil.joelonsoftware.com/Articles/PainlessSoftwareSchedules.html) nem é um _design pattern_, mas já me ajudam um bocado. Gostaria de compartilhá-las com meus pontuais leitores, que sempre entregam seus projetos em dia e nunca se esquecem de comentar uma linha de código sequer. Vocês são meu objetivo de vida e motivo de orgulho deste humilde blogue, que se esmera a cada dia que passa para ser fiel à inegável qualidade do meu público. Quando crescer quero ser igual a vocês.

Mas enquanto não sou, vamos às regras.

#### Regra # 1: cronogramas são imprevisíveis

Esse é o primeiro grande passo: admitir que acertar cronogramas é como acertar na loteria: milhões de pessoas tentam toda semana e uns poucos gatos pingados conseguem de vez em quando. E ainda assim por acaso.

O importante nessa analogia da loteria é perceber que, independente de ser difícil de acertar, isso não impede as pessoas de tentar. Veja você, elas (normalmente) não jogam 1, 2, 3, 4, 5, 6. Por quê? Porque elas tentam jogar no que acreditam ser uma combinação mais provável. E antes que um sábio chinês diga que a chance de sair a seqüência 1, 2, 3, 4, 5, 6 é tão provável quanto qualquer outra, explico que a analogia aqui é psicológica, não matemática. As pessoas **tentam acertar**, por mais irracional que isso pareça. A mesma filosofia deve ser seguida para cronogramas. Não chute valores que estão dentro da sua zona de conforto, mas tente de fato chegar o mais próximo possível da realidade.

E, quem sabe um dia, você não é sorteado.

#### Regra # 2: o tempo estimado vira tempo mínimo

Resumidamente: você fará uma tarefa em uma hora. Mas, diabos, você não sabe disso antes de fazer e coloca no cronograma três horas. Quanto tempo você vai levar agora? Três horas. Não que você não consiga em menos tempo, mas, ao "alargar" a janela de tempo para três horas, seu ritmo irá seguir essa premissa e será mais lento.

Obviamente que o inverso não é verdadeiro. Quer dizer, você não vai terminar uma tarefa de uma hora em dez minutos se colocar dez minutos na sua tabela mágica. Isso, mais uma vez, não é matemática: é psicologia.

> _A mesma analogia absurda serve para valores muito altos. Se estimar três meses para uma tarefa de uma hora, terá três meses para procurar um emprego novo, e não para terminar a tarefa._

__Atualização__: encontrei um artigo no Efetividade explicando sobre esse fenômeno, que já tinha nome e dono registrados antes de eu pensar neles: se chama [Lei de Parkinson](http://www.efetividade.net/2007/10/29/gerenciamento-de-projetos-cuidado-com-a-lei-de-parkinson/) e reza que "as tarefas se expandem para ocupar todo o tempo disponível". Vale a pena a leitura.

#### Regra # 3: tarefas pequenas são mais exatas

Sim, o velho ditado de [dividir para conquistar](http://en.wikipedia.org/wiki/Divide_and_conquer_algorithm). Afinal, é muito melhor estimar o tempo para fazer uma nova função do que estimar o tempo total para a nova versão do produto. Portanto, trate de dividir o seu elefante. O limite é a partir do momento em que se sentir confortável para prever o tempo necessário a ser gasto em uma subtarefa.

#### Regra # 4: uma tarefa estimada é uma tarefa completada

É muito simples ilustrar e entender esse conceito com código. Voltando ao caso da função, digamos que você consiga terminar a bendita função em exata uma hora. Você é bom, hein?

Porém, essa função ainda:

	
  * não foi comentada,

	
  * não foi testada,

	
  * não foi testada em _release_.

Logo, essa é uma tarefa em que você termina o mais importante em uma hora... mas não termina tudo. Deve-se sempre considerar a tarefa por completo, pois no final de quinze tarefas vai faltar comentar e testar tudo isso, o que aumentará consideravelmente a imprevisiblidade no seu cronograma.

#### Regra # 5: não inclua o ócio no cronograma

Seja honesto consigo mesmo e com seu chefe: você realmente trabalha 8 horas por dia? É lógico que não! E não é nenhuma vergonha admitir isso. Todos nós temos _emails_ para ler e responder, reuniões para presenciar e [bloques importantes](http://www.caloni.com.br/blog) para acompanhar. Portanto, ignore essa conversa fiada de 8 horas e admita: não se deve contar os dias como se eles tivessem 8 horas.

Qual o valor de um dia, então? Cada um sabe o valor que deve ser decrementado desse valor simbólico de 8 horas, mas esse valor sempre será menor. Não se iluda!

#### Caso de uso: Wanderley Caloni

A maneira com que eu administro meu tempo tenta (eu disse tenta) seguir as regras até aqui dispostas. Além dessas eu adicionei algumas regras minhas, baseadas em valores razoáveis e premissas consideravelmente lógicas. Aliás, isso me lembra uma última regra geral:

#### Regra # 6: entenda o seu ritmo

O cronograma costuma (deveria) ser considerado uma coisa pessoal. Por quê? Porque cada um tem seu tempo. O que vale mais ao executar uma tarefa geralmente é (deveria ser) qualidade, e não quantidade. Seu vizinho de baia costuma terminar as coisas na metade do tempo que você? Bom para ele. Porém, se você tenta empregar o mesmo ritmo ao seu dia-a-dia vai ter que gastar depois mais do dobro do tempo que você economizou corrigindo os erros de uma tarefa feita nas coxas. Nada é "de grátis".

Encare o trabalho assim como dormir: cada um tem o seu número de horas noturnas para descansar. Se dormir mais ou menos que o normal isso irá influenciar mais tarde, quando acordar. Alguns dormem 4, outros 12 horas. A média é 8. Mas e daí?

#### Agora, voltando às minhas regras pessoais

Primeiro eu tento usar um princípio que a maioria das pessoas conhece e a minoria acredita: se chama [princípio de Pareto](http://en.wikipedia.org/wiki/Pareto_principle). Ele diz que 20% de uma tarefa resolve 80% dos problemas. Aos poucos eu fui acreditando nele até que cheguei à conclusão que deve funcionar, porém existe um problema: definir quais são esses 20%.

Voltando novamente no caso da função, é óbvio que a parte mais importante é fazer a função. Mais uma vez, cada caso é um caso, e o importante é desenvolver esse _feeling_ do que é mais importante. Fazendo o que é mais importante o resto virá complementar a solução.

Essa ordem do que é mais importante deve servir para dividir qualquer tarefa e as tarefas de cada dia, ordenadas por importância. Dessa forma, é fácil começar o dia ou uma tarefa maior pelo que é mais importante. Isso nos leva a um segundo problema: definir o que é importante.

#### Importante x urgente

A maior dificuldade em definir o que é importante é que muitas vezes ele se confunde com o que é urgente, mesmo sendo dois conceitos bem diferentes.

Por exemplo, para mim foi urgente escrever este artigo, já que estou compromissado com a freqüência do meu blogue. O importante fica por conta do conteúdo. Por exemplo, considero ter tocado em todos os pontos que julgo importantes para esse tema, o que por si só caracterizaria o fim desse artigo. E é isso aí.

Bons cronogramas!

PS: _para começar a medir seu desempenho ao realizar tarefas tente usar [este programa](http://www.caloni.com.br/todolist)._

#### Para aprender a ser mais efetivo

	
  * [Efetividade.net](http://www.efetividade.net): produtividade pessoal, lifehacking, GTD e dicas espertas

