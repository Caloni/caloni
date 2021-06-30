---
categories:
- blog
date: '2021-05-20'
link: null
tags:
- draft
title: Truques e Macetes na Hora de Programar
toc: true
---

Este artigo é para organizar meu raciocínio e pesquisa para uma passagem de conhecimento na empresa. Foi sugerido ensinar um pouco do que é possível fazer para acelerar um pouco o desenvolvimento de um programador no dia-a-dia, não só para codificar, mas para todo o resto que consome bem mais tempo.

> macete1 /ê/ substantivo masculino 1.  m.q. MACETA ('pequeno instrumento'). 2. tipo de martelo us. para esculpir em madeira ou, em trabalhos de carpintaria e marcenaria, para bater nos cabos dos formões.

Lembrando que as sugestões foram bem vagas e gerais, então essa é só uma pincelada pessoal sobre os assuntos; nada muito objetivo. As perguntas podem vir depois.

## Como buscar por melhores resultados nas pesquisas

 - Não use o Google como Banco de Dados. O seu Cérebro é o Banco de Dados. Use o Google como um índice remissivo do seu cérebro. Use livros e artigos densos para alimentar seu Banco de Dados.

 - Nunca use a primeira resposta do Stack Overflow. Por quê? Porque ela é a mais popular.

 - Stack Overflow para pedaço de código; artigos para entender o código; livros para estender o código.

## Como otimizar o tempo programando

Como diria Caloni:

 - Para quê você vai querer fazer isso, se o tempo mais prazeroso do trabalho se passa programando?

Como diria [edw519], um dos membros mais populares do Hacker News:

 - Alguns caminhos são melhores que outros, mas qualquer caminho é melhor que nenhum. Ex: fazer API HTTP com tudo GET.

 - Comece com a resposta, então trabalhe ao contrário. Ex: quero uma API HTTP, então começo chamando.

 - É muito mais fácil julgar algo que já existe que definir algo que não existe. Ex: uma API HTTP com tudo GET é feio, mas dá pra melhorar (porque já existe).

 - Esteja preparado para cavar quantos níveis de detalhe precisar para entender ("um hacker é uma pessoa que sabe exatamente o que acontece quando se pressiona um botão do teclado").

 - Não ligue o computador a menos que você tenha uma tarefa específica (para pessoas que trabalham em lugares que você não ganha pelo tempo sentado).

 - Beleza é importante, mas entrega é mais importante. Ex: a API HTTP GET tá pronta e pro usuário funcional; próxima versão a gente melhora.

 - Mantenha extremamente simples no começo. Complique conforme avança. Ex: para mexer na API HTTP GET tem um ponto de entrada cheio de ifs; agora comece a criar funções e outros pontos de entrada.

 - Codifique todos os dias (memória muscular).

Como diria René Descartes, um cara não muito popular nas rodinhas da Idade Média:

 - Cada problema que eu resolvo se torna uma regra que serve mais tarde para resolver outros problemas. Ex: se o problema é perder tempo com uma tarefa repetitiva ache uma maneira mais automática de fazer a mesma tarefa.

Para além disso, ou problemas modernos de déficit de atenção enquanto compila (galerinha do C++ e do Rust), leia livros:

 - [The ONE Thing], de Gary Keller ("There will always be just a few things that matter more than the rest, and out of those, one will matter most").

 - [Deep Work]: Rules for Focused Success in a Distracted World, de Cal Newport ("Professional activities performed in a state of distraction-free concentration that push your cognitive capabilities to their limit").

 - [Flow], The Psychology of Optimal Experience, de Mihaly Csikszentmihalyi ("engagement in an activity that is both challenging and attainable").

## Atalhos nos terminais (Linux e Windows) e como encontrar atalhos

 - Entenda a estrutura de diretórios e arquivos do seu sistema; organize (do seu jeito, mas organize).

 - Em ambos SOs, para navegar entre diretórios mantendo o histórico: pushd, popd.

 - Para buscar por arquivos no Windows dir; para buscar por arquivos no Linux find; use o manual.

 - Como encontrar mais atalhos: encontre o subconjunto que você usa. Ex: atalhos das tarefas mais comuns do seu editor favorito.

 - Caso de uso #1: como eu encontrava atalhos e janelas escondidas no Visual Studio.

 - Caso de uso #2: como eu decorava atalhos no Vim.

## Ferramentas úteis para análise

> A lenda conta que em uma competição para ver quem cortava a árvore mais rápido, o lenhador mais velho passou a maior parte do tempo amolando o machado, enquanto o competidor mais jovem dedicou-se em golpear a árvore com toda a sua força. Quando o jovem estava no meio do tronco o competidor mais experiente começou a cortar sua árvore.

Como diria, edw519, um dos membros mais populares do Hacker News:

 - Use a ferramenta certa para o trabalho certo. Ex: Vim para tudo.

 - Quase qualquer ferramenta pode fazer o trabalho. Algumas são melhores que outras. Ex: uma leiteira é multiuso.

 - Lembre-se dos padrões que você usou antes. Você irá usá-los novamente. Ex: atalho chato no Visual Studio para economizar dez digitações por uma.

### Process Explorer e como encontrar quem travou seu arquivo

 - Find, Find Handle or DLL...

 - Como saber onde está o executável de um processo.

 - Como saber a linha de comando do processo.

 - Como saber as portas de rede abertas.

 - Como saber as variáveis de ambiente do processo.

 - Como saber as strings em memória do processo.

 - Como saber as threads e stack de cada thread de um processo (com nomes de funções usando símbolos).

 - Como... bom, vocês pegaram a ideia.

### Process Monitor e como ver quem escreveu no arquivo

 - Filter, Filter...

 - Como saber a linha de comando do processo que escreveu no arquivo.

 - Como saber como foi aberto o arquivo pelo processo.

 - Como saber a duração dessa chamada de escrita em arquivo.

 - Como saber quando foi que o processo foi iniciado.

 - Como saber a pilha de chamadas da thread que escreveu no arquivos... bom, vocês pegaram a ideia.

### TCP View, WinMerge, BareTail, WinDirStat

 - Portas abertas na máquina.

 - Comparar versões diferentes de arquivos e pastas.

 - Ter um tail portátil e para múltiplos arquivos e filtro.

 - Saber quem está ocupando espaço na máquina que o cliente pediu para limpar.

### Ferramentas UNIX (desde 1970 por aí)

 - Turbinar Windows usando Git (sed, grep, ls): colocar no path do usuário ou do sistema.

 - Grep: buscar coisas dentros dos arquivos.

 - Sed: modificar coisas dentros dos arquivos.

 - Tail e head: ver o início e o final de um arquivo; seguir o final do arquivo conforme for sendo escrito.

 - Sort e uniq: sortear e uniqar coisas; ou ambos (sort -u).

 - Pipe: poder dos programadores de Roma; nunca subestime juntar ferramentas UNIX.

 - Regex: poder dos programadores do Olimpo; use o guia do Aurelio Jargas se nunca ouviu falar.

 - Awk: poder dos programadores de Asgard; use o guia GNU.

### Git

 - Leia [o livro] na segunda vez que ficar confuso usando Git fazendo a mesma coisa.

 - Encanamento: Git é um map de chave/valor em arquivo.

 - Porcelana: Git é uma lista encadeada de arquivos patch.

 - Comandos esotéricos: cherry-pick, rebase, squash, revert, sub-tree.

### Perguntas?

[edw519]: /the-best-of-edw519
[Flow]: /flow
[The ONE Thing]: /the-one-thing
[Deep Work]: /deep-work
[o livro]: https://git-scm.com/book/en/v2