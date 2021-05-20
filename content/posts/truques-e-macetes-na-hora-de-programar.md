---
categories:
- blog
date: '2021-05-20'
link:
tags:
- draft
title: Truques e Macetes na Hora de Programar
toc: true
---
Este artigo é para organizar meu raciocínio e pesquisa para uma passagem de conhecimento na empresa. Foi sugerido ensinar um pouco do que é possível fazer para acelerar um pouco o desenvolvimento de um programador no dia-a-dia, não só para codificar, mas para todo o resto que consome bem mais tempo.

## Como buscar por melhores resultados nas pesquisas

 - Não use o Google como Banco de Dados. O seu Cérebro é o Banco de Dados. Use o Google como um índice remissivo do seu cérebro. Use livros e artigos densos para alimentar seu Banco de Dados.

 - Nunca use a primeira resposta do Stack Overflow. Por quê? Porque ela é a mais popular.

 - Stack Overflow para pedaço de código; artigos para entender o código; livros para estender o código.

## Como otimizar o tempo programando

Como diria Caloni:

 - Para quê você vai querer fazer isso, se o tempo mais prazeroso do trabalho se passa programando?

Como diria [edw519], um dos membros mais populares do Hacker News:

 - Alguns caminhos são melhores que outros, mas qualquer caminho é melhor que nenhum.

 - Comece com a resposta, então trabalhe ao contrário.

 - É muito mais fácil julgar algo que já existe que definir algo que não existe.

 - Esteja preparado para cavar quantos níveis de detalhe precisar para entender.

 - Não ligue o computador a menos que você tenha uma tarefa específica.

 - Beleza é importante, mas entrega é mais importante.

 - Mantenha extremamente simples no começo. Complique conforme avança.

 - Codifique todos os dias.

Como diria René Descartes, um cara não muito popular nas rodinhas da Idade Média:

 - Cada problema que eu resolvo se torna uma regra que serve mais tarde para resolver outros problemas.

Para além disso, ou problemas modernos de déficit de atenção, leia livros:

 - [The ONE Thing], de Gary Keller ("There will always be just a few things that matter more than the rest, and out of those, one will matter most").

 - [Deep Work]: Rules for Focused Success in a Distracted World, de Cal Newport ("Professional activities performed in a state of distraction-free concentration that push your cognitive capabilities to their limit").

 - [Flow], The Psychology of Optimal Experience, de Mihaly Csikszentmihalyi ("engagement in an activity that is both challenging and attainable").

## Atalhos nos terminais (Linux e Windows) e como encontrar atalhos

 - Em ambos, para navegar entre diretórios mantendo o histórico: pushd, popd.

 - Para buscar por arquivos no Windows dir; para buscar por arquivos no Linux find; use the manual.

 - Como encontrar mais atalhos: Google? (Falar sobre como atalhos no Vim são customizados por cérebro.)

 - Caso de uso: como eu encontrava atalhos e janelas escondidas no Visual Studio.

 - Caso de uso 2: como eu decorava atalhos no Vim.

## Ferramentas úteis para análise

Como diria, edw519, um dos membros mais populares do Hacker News:

 - Use a ferramenta certa para o trabalho certo.

 - Quase qualquer ferramenta pode fazer o trabalho. Algumas são melhores que outras.

 - Lembre-se dos padrões que você usou antes. Você irá usá-los novamente.

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

 - Grep: buscar coisas dentros dos arquivos.

 - Sed: modificar coisas dentros dos arquivos.

 - Tail e head: ver o início e o final de um arquivo; seguir o final do arquivo conforme for sendo escrito.

 - Sort e uniq: sortear e uniqar coisas; ou ambos (sort -u).

 - Pipe: poder dos programadores de Roma; nunca subestime juntar ferramentas UNIX.

 - Regex: poder dos programadores do Olimpo; use o guia do Aurelio Jargas se nunca ouviu falar.

 - Awk: poder dos programadores de Asgard; use o guia GNU.

#### Git para ter grep, sed, tail e awk no seu Windows

 - Path do usuário e do sistema; tome o poder para você; sussurro: \Program Files\Git\usr\bin.

## Ferramentas do dia-a-dia

> A lenda conta que em uma competição para ver quem cortava a árvore mais rápido, o lenhador mais velho passou a maior parte do tempo amolando o machado, enquanto o competidor mais jovem dedicou-se em golpear a árvore com toda a sua força. Quando o jovem estava no meio do tronco o competidor mais experiente começou a cortar sua árvore.

### Git mais uma vez, e como usar de verdade (comandos esotéricos como cherry-pick)

 - Leia [o livro] pelamordedeus.

 - Encanamento: Git é um map de chave/valor em arquivo.

 - Porcelana: Git é uma lista encadeada de arquivos patch.


[edw519]: /the-best-of-edw519
[Flow]: /flow
[The ONE Thing]: /the-one-thing
[Deep Work]: /deep-work
[o livro]: https://git-scm.com/book/en/v2
