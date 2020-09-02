---
date: "2007-08-29"
tags: [ "code", "draft",  ]
title: "Hook de API no WinDbg"
---
Basicamente existem duas maneiras de um executável obter o endereço de uma função API do Windows: ou ele usa uma lib de interface com a DLL (o chamado "link estático") ou ele chama a função kernel32!GetProcAddress explicitamente [1].

Para conseguir saber as funções das quais um executável obtém o endereço através da primeira técnica podemos utilizar o mundialmente famoso Dependency Walker. Ele nos mostrará quais DLLs ele utiliza e quais funções por DLL ele quer o endereço. Ele também nos avisa sobre as DLLs que estão utilizando delay load, uma técnica inventada no Visual Studio para que os executáveis não dependam estaticamente de APIs muito novas que podem não existir em versões do Windows mais antigas. Com o Depends também é possível fazer hook de chamadas de API utilizando a opção profiling (F7), mas não costuma funcionar muito bem com trojans, pois eles capotam antes que alguma coisa interessante ocorra.

O importante do Dependency Walker para o WinDbg é que com um editor é possível copiar todas as funções exibidas em sua interface para um editor, usar um pouco de regular expressions e criar uma batelada de breakpoints no WinDbg:


O comando "bp" cria um breakpoint no endereço requisitado. O que está entre aspas são os comandos que você deseja executar quando o breakpoint for disparado. No caso, para todas as funções será impresso o seu nome (comando ".echo") e a execução irá continuar (comando "g"). Ao rodar o programa, as chamadas das funções são mostradas na saída do depurador:


Lindo, não? Porém ainda podem estar sendo chamadas as funções obtidas pela segunda técnica, a do GetProcAddress. Para esse caso devemos ir um pouquinho mais fundo e rodar o executável duas vezes. Na primeira, coletamos as funções que são obtidas por essa técnica através do seguinte comando:


O comando "da" exibe o conteúdo de uma string em C (caracteres ANSI e terminada em zero) na memória. A memória no caso é o "apontado do valor contido no segundo parâmetro da pilha". Complicado? Nem tanto: lembre-se que o ESP aponta sempre pro endereço de retorno da função chamadora e os parâmetros são sempre empilhados na ordem inversa da declaração em C. Logo, se o protótipo de GetProcAddress é:


O último parâmetro empilhado (ESP+4) é o hModule, e o penúltimo (ESP+8) é o lpProcName, que é o lugar onde é passado o nome da função.

Devemos lembrar de colocar esse breakpoint bem no início da execução e rodar o executável uma vez. Com isso coletamos o conjunto de nomes de funções usadas para chamar GetProcAddress:


Daí é só organizar a lista obtida em ordem alfabética, acabar com duplicidades e criar o mesmo tipo de breakpoint que foi usado para as funções estáticas (pode ser sem o nome da DLL porque, embora não recomendado, o WinDbg se vira para encontrar os símbolos). Depois de criados os comandos, rodamos novamente o executável e, logo no início, já colocamos todos os breakpoints das funções coletadas.

Essa é uma maneira rústica, porém eficaz e rápida de obter a lista de execução da API utilizada por um programa [2].

[1] Uma variação do método GetProcAddress é a técnica de delay load usado pelo Visual C++. Porém, como o Dependency Walker nos mostra também as DLLs que estão linkadas usando essa técnica se torna dispensável um tratamento ad hoc.

[2] Essa técnica nem sempre funciona com todas as chamadas API, pois o aplicativo ainda pode utilizar outras maneiras de obter o endereço de uma função e chamá-la. A solução definitiva seria escrever diretamente um assembly esperto no começo da função, o que pode gerar mais problemas que soluções. Do jeito que está, conseguimos resolver 90% dos nossos problemas com análise de chamadas API. O resto nós podemos resolver em futuros artigos.

  * http://www.kakeeware.com: sítio com monitor de chamadas de API e outras ferramentas interessantes. Detalhe notável: o cara faz tudo usando apenas _assembly_, o que torna os programas realmente pequenos e rápidos.
  * ComTrace: outro monitor de chamadas, mas de componentes COM. Intercepta todas as chamadas de métodos de um aplicativo.
