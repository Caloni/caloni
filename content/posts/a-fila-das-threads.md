---
categories: [ "code" ]
date: "2009-04-07"
tags: [ "draft",  ]
title: "A fila das threads"
---
Em um ambiente multithreading, diversas threads disputam "a tapas" a atenção do processador (CPU). Certo? Podemos dizer que, em um ambiente com muito processamento a realizar, de certa forma é isso que acontece. São threads e mais threads rodando um pedacinho de código cada vez que passam pelo processador.

Um ambiente complexo como esse é repleto de pequenos detalhes que podem fazer o iniciante logo desanimar quando tentar depurar um programa com mais de uma thread. De fato, eu já percebi que muitos não vão saber nem como começar a mastigar o problema.

Por isso mesmo que eu tive que inventar algumas analogias no mínimo interessantes a respeito do assunto. Sem analogias, não sei como falaria sobre essas coisas de forma amena e "explicável".

A primeira "parábola" conta a história da fila das threads em direção ao guichê das CPUs.

O exemplo abaixo cria três threads, todas iniciando na mesma função. O objetivo de todas elas é incrementar um contador até que seu valor chegue a 10. Todas param quando esse objetivo é alcançado.


Esta é a saída:


Pelo jeito, a primeira thread não deu chance para as outras. Isso acontece por causa do pequeno espaço de tempo que é necessário para realizar a tarefa de incrementar uma variável. Tempo esse tão pequeno que nem foi suficiente para a primeira thread dar lugar para as outras duas threads e ir para o final da fila.

Quando uma thread quer realizar algum processamento, ela precisa entrar na fila das threads ativas, que aguardam pela CPU que irá atendê-las. Nessa fila ela pega uma senha e aguarda a sua vez. Só que cada um que é atendido pela CPU tem um tempo máximo de atendimento, que nós chamamos de quantum, ou time slice. Se o tempo máximo estoura, ou a thread não tem mais nada pra fazer, ela sai do guichê de atendimento e volta a ficar inativa, ou volta para o final da fila, aguardando por mais processamento.

Uma thread pode opcionalmente ir para o final da fila por conta própria. Para isso, basta que ela chame a função Sleep.aspx) da API passando qualquer valor em milissegundos; até mesmo zero. Se passar um valor diferente de zero, ela irá para outra fila de espera, a fila das inativas, até o tempo determinado estourar. Depois ela volta para a fila das threads ativas. Se passar zero, ela vai direto para a fila das ativas.



Agora cada thread, depois de incrementar uma vez o contador, volta para o final da fila. Dessa forma vemos uma thread de cada vez incrementando o mesmo contador.

Peraí. O mesmo contador? Isso não pode gerar problemas de duas threads tentando incrementar o mesmo contador ao mesmo tempo?

Não vou mentir; pode sim. Para isso acontecer, basta irmos para o final da fila antes de incrementarmos, mas após pegarmos o valor atual do contador. Note que a saída muda completamente.



Esse problema ocorre pelo seguinte motivo: quando uma thread guarda o valor do contador na variável temp e volta para o final da fila, ela deixa de armazenar o contador atualizado para apenas depois que todas as outras threads passarem na sua frente. Só que as outras threads também pegam o mesmo valor do contador, pois ele ainda não foi alterado. Quando chega a hora da segunda passada no guichê das CPUs, todas as threads incrementaram o mesmo valor do contador.

O exemplo acima forçou essa situação, mas é preciso lembrar que isso pode acontecer mesmo sem o Sleep. É possível que o tempo da thread se esgote e ela pare de ser atendida  justo na hora que iria salvar a variável temp no contador global. Dessa forma, ela vai para o final da fila à força e, quando voltar a ser atendida, uma outra thread já terá incrementado o mesmo valor.

Esse problema pode ser facilmente resolvido se utilizarmos um sistema de bloqueio entre threads do mesmo processo. Uma outra história para contar da próxima vez.
