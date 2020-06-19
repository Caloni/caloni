---
categories: [ "code" ]
date: "2017-02-04"
tags: [ "draft",  ]
title: "Um commit por feature"
---
Imagine que você vai começar a trabalhar em algo novo. Daí você baixa a última versão do branch de dev e começa a codar. Então chega um momento em que o primeiro, segundo, terceiro commits são necessários para manter a ordem em sua cabeça. "Fiz isso logo de manhã, testei algo diferente antes do almoço e de tarde fui incrementando a solução final até passar todos os testes." Tudo bonito. Mas como fica na hora de subir essa bagaça pras pessoas verem?

Vamos visualizar isso em commits. Você baixa a última versão do dev, começa a trabalhar e de duas uma:

1. Percebe que dá para resolver tudo em um commit só.
2. Percebe que o buraco é mais embaixo; vou precisar de mais tempo e mais commits.

No caso 1, a solução é simples e direta: faça as modificações, rode os testes locais e aplique o commit já no formato definido pela sua equipe (número do ticket, texto no idioma correto, detalhes nos parágrafos abaixo). Suba e mande para code review.


Se a política de pull request estiver sendo usada, faça isso em um branch à parte, mas já mande para o reviewer aprovar o branch como se fosse um commit apenas e de preferência pronto para o rebase (o que não deve ser nem um problema se for uma mudança pontual).


Quando mais de um commit é necessário é porque vai rolar a festa. Vários commits com texto e modificações temporárias podem ser feitos, e caso o trabalho vire a noite, é recomendado subir tudo para um branch temporário remoto (de preferência que já seja identificado pela equipe como o branch para determinado issue).


Agora nós criamos uma bela duma bagunça, mas em um branch apartado e que ainda não foi enviado para pull requet ou inserido no branch de dev. Agora chega a hora de arrumar a casa. Para isso, como tudo no git, há várias maneiras, mas a mais direta é um rebase interativo (-i), onde você pega os commits e empacota tudo junto.

(Obs.: se sua modificação demorou algum tempo é melhor atualizar o branch de dev para ver se há algo novo e fazer o merge com o branch de feature; o rebase daí não encontrará conflitos.)


Nesse momento o git irá abrir o editor com os commits trabalhados. Você deverá escolher quais operações fazer com cada commit. Se o objetivo é empacotar tudo, geralmente é pick no primeiro e squash em todos os outros:


Ao final da operação mais uma vez o git irá exibir o editor. Agora é hora de você escolher o texto bonitinho, formatadinho, do seu único commit que será usado no branch de dev. Em outras palavras, transformar isso:


Nisso:


Agora na hora de fazer o merge seu histórico estará redondo, sem ramificações e com o resultado final de seu hacking parecendo que foi feito bonito desde o começo (ah, vá):


Esta é uma das inúmeras formas de trabalhar com o git de maneira individual sem atrapalhar seus colegas. Basicamente você pode escolher outras estratégias de commits e branchs locais, mas através do comando rebase -i é possível sempre reorganizar a bagunça em commits comportados, e dar a impressão que esses programadores são enviados divinos que modificam o fonte e acertam de primeira.
