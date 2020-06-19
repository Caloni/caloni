---
categories: [ "code" ]
date: "2016-01-27"
tags: [ "draft", "tools" ]
title: "Exportando repositórios antigos do Bazaar para Git"
---
Enquanto estudava sobre controle de fontes distribuído, experimentei e usei os projetos Mercurial e Bazaar, precursores desse modelo que funcionavam bem em Windows. Havia o Git, mas por conta da sua evolução assimétrica, o ambiente da Microsoft havia ficado para trás.

Hoje com o Git sendo praticamente o mainstream das conversões do SubVersion, e funcionando razoavelmente bem em ambientes Windows (64 ou 32), sobraram apenas os repositórios do Mercurial e do Bazaar. Na verdade, mais do Bazaar, pois eu havia migrado já do Hg pelo Bazaar possuir algo que hoje o Git emula, mas antes era um diferencial no projeto da Canonical: detecção de rename completo (com histórico e tudo). Isso para refatoração era vital, e suporte à refatoração pesada era o que eu precisava no momento.

Agora é hora de manter esse histórico vivo, mas convertido para o que todos usam.

A primeira coisa a ser feita é converter o repositório. Depois de convertido, como todas as operações estarão no universo Git, há uma de entradas no StackOverflow para nos ajudar a reunir os repositórios em um só, meu objetivo, já que o Git é mais leve e mais versátil nesse quesito.

No Windows, nas últimas versões do Bazaar o comando fast-export não estava mais funcionando. Parado desde 2012, não há previsão de correções. No entanto, para essa operação, a versão 2.4.2 atendeu bem. O comando é um pouco diferente, mas ele é rápido e rodou sem problemas em conjunto com o fast-import do Git.


É óbvio que nem tudo serão mil maravilhas. Eu, por exemplo, encontrei um problema com case-sensitive que me deu algumas dores de cabeça:


O Git gera um arquivo de report onde estão as informações do ocorrido. Uma forma de contornar esse tipo de problema é primeiro exportar para um arquivo e editá-lo (corrigindo o case, por exemplo):


Note que talvez você precise de um editor que suporte arquivos gigantescos (como o Vim) e precise se debruçar sobre merges com arquivos com mesmo nome e diferentes cases. Isso que dá manter projetos com refactoring pesado.

Por fim, faça a conversão para todos os .bzr que tiver e haverá um .git com todo o histórico desses anos usando Bazaar. O próximo passo é montar o histórico de todos eles em apenas um repositório (se assim desejar). Segue uma série de comandos que pode ajudar para usar em uma batch:


Você pode chamar um a um em cima de um repo novo:


Para conseguir ter acesso ao histórico dos arquivos movidos, basta usar a opção -all do log:


Tive alguns problemas em rastrear o histórico utilizando a estratégia de fazer merge no mesmo branch. A solução que encontrei, embora não exatamente direta, foi realizar os merges em branches apartados primeiro, mover os arquivos (de preferência, usando o git, para que ele detecte o rename), aplicar o commit e realizar o merge com o master. Há uma vantagem nessa estratégia, além do log --follow funcionar melhor: mantenha os branches originais, além do ponteiro para remote. Dessa forma, depois de alguns anos, saberá de onde veio esse merge maluco.

Depois de um tempo testando essa técnica, descobri que o Git se perde novamente e não encontra mais todos os logs, mesmo com --follow  mesmo movendo os arquivos. O meu problema está relacionado com mesmos paths dos arquivos em repositórios diferentes. Paciência.
