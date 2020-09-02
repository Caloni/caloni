---
date: "2007-11-27"
tags: [ "code", "draft",  ]
title: "Carregando DLLs arbitrárias pelo WinDbg - parte 2"
---
Como pudemos ver no artigo anterior, o processo para carregar uma DLL pelo WinDbg é muito extenso, enfadonho e sujeito a erros. Por esse motivo, e para tornar as coisas mais divertidas, resolvi transformar tudo aquilo em um simples script que pode ser executado digitando apenas uma linha.

Se trata do meu primeiro script grande para o WinDbg, por isso, peço que tenham dó de mim =).

Um script no WinDbg nada mais é que uma execução em batch: um arquivo texto cheio de comandos que poderíamos digitar manualmente, mas que preferimos guardar para poupar nossos dedos.

Existem quatro maneiras diferentes de chamar um script no WinDbg, todas muito parecidas, variando apenas se são permitidos espaços antes do nome do arquivo e se os comandos são condensados, isto é, as quebras de linhas substituídas por ponto-e-vírgula para executar tudo em uma linha só.

  * $<nome-do-arquivo - não permite espaços e condensa comandos.
  * $><nome-do-arquivo - não permite espaços e não condensa comandos.
  * $$<nome-do-arquivo - permite espaços e condensa comandos.
  * $$><nome-do-arquivo - permite espaços e não condensa comandos.
  * $$>a<nome-do-arquivo - igual ao anterior, e ainda permite passar argumentos.

OBS: a ajuda do WinDbg descreve as diferenças dos comandos acima de forma adversa, afirmando que os comandos '<'  não condensam as linhas e os '><' o fazem, quando na realidade é o contrário. Não se deixe enganar por esse detalhe.

No caso do script desse artigo, utilizaremos a última forma, pois precisamos de um argumento para funcionar: o nome da DLL. Caso você não digite esse argumento, a ajuda do script será impressa:

Não há qualquer dificuldade. Tudo que você tem que fazer é baixar o script que carrega DLLs e salvá-lo em um lugar de sua preferência. Depois é só digitar o comando que carrega scripts, o path de nosso script e o nome da DLL a ser carregada em uma das três formas exibidas. Eu costumo criar uma pasta chamada "scripts" dentro do diretório de instalação do Debugging Tools, o que quer dizer que posso simplesmente chamar todos meus scripts (ou seja, 1) dessa maneira:


Abaixo um pequeno teste que fiz carregando a DLL do Direct Draw (ddraw.dll) na nossa vítima de plantão:


Simples e indolor.

Vamos agora dar uma olhada no script completo e dissecar as linhas pausadamente. Dessa forma entenderemos como a função inteira funciona e como usar os comandos isoladamente para criar novos scripts.


Como podemos ver, ele é um pouco grandinho. Por isso mesmo que ele é um script, já que não precisamos, sempre que formos usar este comando, ficar olhando para o fonte.

Por falar em olhar, uma primeira olhada revela a seguinte estrutura:


Qualquer semelhança com as instruções em C não é mera coincidência. Essa estrutura de fato verifica se o resultado dentro do .if é verdadeiro. No caso o script verifica se o primeiro parâmetro foi passado, já que os argumentos são acessíveis através dos alias (apelidos) $arg1 - $argn. Essa maneira de usar os argumentos passados no WinDbg ainda não foi documentada, mas encontrei essa dica em um artigo do Roberto Farah, um grande escritor de scripts para o WinDbg.

Da mesma forma, o que não deve ser nenhuma surpresa, o WinDbg suporta comentários. Todas as linhas que contêm '$$' isoladamente são comentários, e seu conteúdo da direita é ignorado, salvo se for encontrado um ponto-e-vírgula.

A primeira coisa que fazemos para carregar a DLL é salvar o estado do registrador IP, que indica onde está a próxima instrução:


Feito isso, usamos um comando não tão comum, mas que pode ser muito útil nos casos em que precisamos capturar algum dado da saída de um comando do WinDbg e usá-lo em outro comando.

A estrutura do .foreach deixa o usuário especificar dois grupos de comandos: o primeiro grupo irá gerar uma saída que pode ser aproveitada no segundo grupo.


A opção "/pS 5" diz ao comando para pular 5 posições antes de capturar o token que será usado no próximo comando. Os tokens são divididos por espaço. Sendo a saída de ".dvalloc 0x1000"


Pulando 5 posições iremos capturar o endereço onde a memória foi alocada. E é isso mesmo que queremos!


O sinônimo do endereço (alias) se torna "addr", apelido que usamos ao executar o segundo comando, que armazena o endereço no registrador temporário $t0:


Após alocada a memória, gravamos o parâmetro de LoadLibrary, o path da DLL a ser carregada, em seu início.


O código assembly que irá chamar fica um ponto à frente, mas na mesma memória alocada.


Conforme as técnicas vão cada vez ficando mais "não-usuais", mais difícil fica achar um nome para a coisa. Essa técnica de escrever o assembly de um código através de escritas em hexadecimal dentro de um script do WinDbg eu chamei de "script assembly". Se tiver um nome melhor, não se acanhe em usá-lo. E me deixe saber =).


Cada comentário de uma instrução em assembly é seguido pela escrita dessa instrução usando o comando e. Se trata de um código bem trivial, fora alguns detalhes que merecem mais atenção.

Os comandos acima servem para salvar e restaurar o estado dos registradores e das flags de execução. Isso permite que possamos executar o código virtualmente em qualquer posição que pararmos no código depurado, já que retornamos tudo como estava ao final da execução do LoadLibrary. É claro que isso não garante que o código estará 100% estável em todas as condições, mas já ajuda um bocado.

Uma chamada através do opcode call (código em hexa 0xe80c) é bem comum e se trata de uma chamada relativa, baseada no estado do Instruction Pointer atual mais o valor especificado. Por isso mesmo que fazemos o cálculo usando o endereço de onde será escrita a próxima instrução, que é o valor que teremos em IP quando este call for executado:


Quando o código estiver completamente escrito na memória alocada, um disassembly dele retornará algo parecido com o código abaixo:


Você pode ver com seus próprio olhos se editar o script comentando o último comando (g), executando o script e executando o disassembly do IP.


Somos um script bem comportado (na medida do possível) e por isso colocamos um breakpoint temporário no final para, quando retornarmos para o código atual, desalocarmos a memória usada para a escrita e execução das instruções.


Eu não me responsabilizo por qualquer (mau) uso do script aqui disponibilizado, assim como as eventuais perdas de código-fonte, trilhas de HD e placas de memória RAM pela sua execução. Assim sendo, bom divertimento.

O criador do DriverEntry me questionou se não seria mais fácil, em vez de escrever todos os opcodes em hexa, usar o comando a, que permite entrar o código assembly diretamente a partir de um endereço especificado. Essa realmente é uma ótima idéia, e de fato eu tentei isso no começo de meus testes. Porém, infelizmente para scripts isso não funciona bem. A partir do comando a o prompt fica esperando uma entrada do usuário, não lendo o assembly que estaria no próprio script. Pior ainda, a escrita do assembly não permite usar os registradores temporários, como $t0 ou $t1, o que nos força a escrever um código dependende de valores constantes. Por esses motivos, tive que apelar para o comando e, que é a forma mais confusa de escrever e entender assembly. Nesse tipo de edição é vital comentar bem cada linha que se escreve.
