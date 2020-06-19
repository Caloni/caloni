---
categories: [ "code" ]
date: "2009-03-05"
tags: [ "draft",  ]
title: "Os problemas mais cabeludos"
---
Quase todos os problemas do Universo são resolvidos depois de um belo dia de depuração, código comentado, descomentado, recomentado e umas muitas e boas doses de café. Alguns outros problemas mais cabeludos precisam de uma boa noitada na frente do computador, e mais café. E, finalmente, existem aqueles que nem tomando o estoque inteiro de café a coisa anda.

Um exemplo: um hook global do Windows que quando ativado em determinados eventos envia mensagens para uma única janela que cataloga informações sobre diversas janelas e processos no sistema. Esse procedimento é uma subfunção do programa principal, que já possui seus próprios problemas e idiossincrasias. Em momentos aparentemente aleatórios algumas funcionalidades não parecem estar de acordo com o que se espera.

Para esse tipo de situação que envolve 1. o sistema como um todo, 2. processos de terceiros e 3. comportamento obscuro por parte do resto do código, vale a pena seguir um checklist mais rigoroso, colocar seu bonezinho de CSI e partir para desmembrar o funcionamento do código problemático:

	
  1. Como o programa deveria funcionar?

	
  2. O que exatamente não funciona?

	
  3. O que pode ser? O que NÃO pode ser?

	
  4. Existe uma maneira de provar?

Cada uma dessas perguntas deve ser respondida com a maior sinceridade e disciplina, custe o que custar.

Esse deve ser o primeiro e mais importante indício do que pode estar acontecendo. Sem entender o funcionamento do programa, dificilmente conseguiremos passar para os passos seguintes. Na maioria das vezes, sem saber onde a coisa começa e termina, o problema vai ficar rindo da nossa cara até entendermos de fato que aquele if não merece estar naquela linha.

Para facilitar esse entendimento, nada como elaborar uma pequena explicação para si mesmo no estilo How Stuff Works. Não precisa exagerar e fazer uma tese a respeito e criar vídeos explicativos. Só precisa descrever o fluxo com os detalhes aparentemente importantes para a resolução do problema.

Continuando nosso exemplo:

	
  1. O programa inicia e cria uma _thread _específica.

	
  2. Essa _thread _específica cria uma janela que monitora e carrega uma DLL.

	
  3. Essa DLL é chamada pela _thread _e instala um _hook _global no sistema.

	
  4. O _hook _recebe eventos de todos os processos que possuem janelas.

	
  5. Quando eventos específicos são disparados, o processo atual envia uma mensagem para a janela que monitora.

	
  6. A janela que monitora monta uma tabela estatística dos eventos.

	
  7. De tempos em tempos, essa tabela é escrita em disco em um arquivo encriptado.

A lista acima é longa o suficiente para podermos elaborar perguntas interessantes e pequena o suficiente para podermos ter em mente o seu funcionamento como um todo, o que é vital para o sucesso das observações durante a depuração.

Note que a pergunta nos direciona para o sintoma do problema, não o problema em si, que provavelmente ainda não é conhecido. E nunca é demais lembrar que podemos estar lidando com uma série de problemas trabalhando em conjunto para nos deixar acordados por dias a fio.

Exemplos de respostas possíveis: a tabela estatística perde a lógica em determinado momento, o hook algumas vezes não funciona, aleatoriamente um dos processos "hookados" capota.

Essa pergunta deve ser respondida com uma análise das respostas das duas primeiras perguntas. Batendo os sintomas do problema com o seu funcionamento macro, uma ou mais cabeças aos poucos irão elaborando teorias a respeito de onde pode estar falhando.

Ex: talvez por algum motivo a DLL esteja sendo descarregada (que lugares podem ser estes?), alguém está desinstalando o hook (quais as partes do código que fazem isso?), alguma ferramenta de análise está atrapalhando nossos resultados (o que acontece se rodarmos sem o DebugView?).

Ao mesmo tempo que os sintomas do problema acusam que algo está errado, existem os sintomas de que alguma coisa, afinal de contas, está funcionando nessa porcaria de código. Através dos sintomas positivos é possível chegar a algumas conclusões sobre o que está funcionando bem.

Ex: o arquivo de log está sendo atualizado, a thread da janela que monitora recebe mensagens continuamente, algumas informações da tabela não estão corrompidas.

Esse é o pulo do gato, a parte que diferencia meninos e meninas de homens e mulheres. Se conseguirmos, através de código de teste e/ou observação, aos poucos provar nossas conclusões a respeito do problema e conseguir elaborar, passo a passo, uma "maquete mental" de todo o código funcional, será possível aos poucos ir descartando teorias e reforçando nossa confiança sobre o caminho que estamos trilhando.

Às vezes uma pequena mudança no código pode provar inúmeras coisas, como inocentar algumas partes e proteger-se de acusações infundadas feitas anteriormente. É uma briga contra o próprio ego, especialmente se o código foi feito por você mesmo.

Ex: Desabilitei o tratamento dos eventos e o hook continua funcionando.

O importante é nunca parar de pensar sobre o problema, evitando ao máximo agir mecanicamente e por impulso, a não ser que exista um bom motivo para isso. Às vezes apenas pensando de novo sobre o mesmo assunto comprova-se algo. É uma fase muito rica e próspera na resolução de problemas e deve ser aproveitada.

Ex: Quando estava habilitado o tratamento de eventos, o hook parava de funcionar em menos de cinco minutos. Agora, rodando os testes por três horas, o hook continua ativo.

Ex: Desabilitei um dos eventos que possui comunicação remota com o servidor. O hook continuou funcionando, apesar do resto dos eventos.

Por fim, com uma pequena dose de sorte e muitas doses de força de vontade (e café), o problema cansa de se esconder e mostra a cara.

Ex: Quando há falha na comunicação com o servidor com o erro 666 uma exceção é lançada, e quando capturada tenta gerar um logue, só que esse logue está mal formatado e causa com que a thread inteira vá para o espaço.

Essa é a hora em que todos se esquecem do esforço que custou chegar até ali e não documentam nada do que foi feito. Desse jeito perde-se todo esse tempo não apenas uma vez, mas todas as vezes que alguém diferente do time mexer com a mesma situação. Por isso deve-se, com a cuca fresca, escrever algumas dicas de como reproduzir o problema e elaborar um pequeno relatório ou algo que o valha do que foi feito, como foi feito e por que funcionou. Mais uma vez, não exagere. Deixe as apresentações sofisticadas de PowerPoint para os outros departamentos da empresa.

Como deve ter parecido, esse tipo de abordagem leva tempo e não é fácil de ser levado adiante sem disciplina e muita persistência. Por esse motivo é que só deve ser usado naqueles problemas em que já se perdeu uma imensidade de tempo e esperança, uma situação irremediável e que ainda não conseguiu vislumbrar o dia em que finalmente poderemos dedicar nossas vidas profissionais para uma outra tarefa mais interessante.
