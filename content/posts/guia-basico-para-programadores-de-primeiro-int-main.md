---
categories: [ "code" ]
date: "2007-10-16"
tags: [ "draft",  ]
title: "Guia básico para programadores de primeiro int main"
---
> Vou aproveitar que meu amigo DQ publicou um artigo muito bom sobre como fazer programas fáceis de manter (merece ser lido!) e vou republicar um artigo do blogue antigo sobre o básico do básico para quem deseja entender como os programas funcionam. Não é nada sofisticado, apenas alguns conceitos comuns que, se você deseja ser programador, deveria procurar saber.

A primeira coisa a saber é o que é um programa. Podemos imaginá-lo como um arquivo que vai ser interpretado pelo computador. Essa interpretação chamamos de execução. Quando um programa está sendo executado também é comum dizermos que ele está rodando. Teoricamente ele pode rodar eternamente, mas o que acontece em casos normais é que ele tem um fim previsto, seja quando o usuário fechar a janela principal (evento externo) ou quando ele terminar o que tinha que fazer (lógica interna).

E do que é feito um programa? Basicamente de duas coisas: dados de entrada e instruções (ou código). Os dados podem estar no próprio programa ou serem lidos de algum outro lugar (do teclado, de outro arquivo, da internet, etc). As instruções do seu programa é o que será interpretado pelo computador. E o que ele fará? Basicamente alterar os dados de entrada. O objetivo fundamental de um programa é gerar dados de saída. Esses dados são escritos/exibidos para algum outro lugar (para a tela, para um arquivo, para a internet, etc).

Vamos analisar essas abstrações em exemplos da vida real:

| Exemplo         | Dados de entrada            | Processamento                 | Dados de saída                    |
| --------------  | --------------------------  | ----------------------------  | --------------------------------- |
| Bloco de Notas  | Digitação do usuário        | Leitura do teclado            | Texto exibido na tela             |
| MSN             | Envio de mensagem           | Conexão com a internet        | Seu amigo recebe a mensagem       |
| PaintBrush      | Movimento do mouse          | Interpretação de movimento    | Retângulo desenhado               |
| Firefox         | Clique do mouse em uma URL  | Conexão com o site            | Exibição da nova página           |
| Counter Strike  | Clique no botão de tiro     | Cálculo do projétil           | Inimigo acertado                  |
| Compilador      | Código do programador       | Interpretação das instruções  | Código de máquina (seu programa!) |

Como podemos ver, podemos abstrair esse lance de "dados de entrada + processamento = dados de saída" com qualquer tipo de programa que usarmos. Basta relacionar o que fazemos (digitar algo, arrastar o mouse, apertar um botão, etc) para obtermos a saída desejada (texto/gráfico na tela, no arquivo, na impressora, etc). O programa é o elemento que fica no meio fazendo essa "mágica".

Existem informações intermediárias que precisamos guardar em um programa em execução para que no final consigamos apresentar a saída desejada ao usuário. Essas informações intermediárias também são dados, só que o usuário não os enxerga. A elas chamamos de variáveis. Entenda uma variável como "um lugar na memória onde o programa armazena alguma informação durante o processamento".

Toda variável é apenas memória interpretada de uma maneira peculiar. Essa maneira de interpretar a memória é chamada de tipo. Cada variável possui o tipo que lhe convém. Basicamente, existem dois tipos de variáveis: número (ou inteiro) e texto (ou string).

Imagine um programa sendo executado do começo ao fim. A ordem em que um programa é executado é chamado de fluxo de execução. A tendência natural de um programa é ser executado pelo computador da sua primeira instrução até a última, sempre nessa ordem. Ou seja, linha 1, linha 2, linha 3, ...., linha n. Pronto. Acabou.

Porém, se fosse sempre assim, isso quer dizer que o programa seria executado sempre do mesmo jeito, e os dados de saída seriam sempre os mesmos, independente dos dados de entrada. Mas isso não acontece, certo? Quer dizer, se você não mirar direito e apertar o botão certo, o inimigo não vai cair no chão. Isso faz um certo sentido, não?

Seguindo esse raciocínio, podemos deduzir que um programa deve tomar decisões para saber o que fazer. E para tomar essas decisões ele usa o que recebeu como entrada, que são exatamente os dados de entrada. Nesse contexto, tomar decisão significa alterar o fluxo de execução. Ou seja, a ordem não necessariamente será sempre linha 1, linha 2, linha 3, etc, mas poderá ser, por exemplo, linha 1, linha 52, linha 237643, linha 52 de novo, linha 890, e assim por diante.


Note que existem várias perguntas que o programa precisa responder para seguir em frente. Para respondê-las, o programa pede a ajuda do computador para fazer comparações entre variáveis. E aí está o uso desses dados internos.

Bem, até aqui você já aprendeu um montão de coisas:

	
  * Programas podem ser armazenados em arquivos.

	
  * Quando executados, o computador interpreta suas instruções.

	
  * Um programa usa dados de entrada para gerar dados de saída.

	
  * Para tomar decisões, ele utiliza variáveis internas.

	
  * A ordem das instruções é chamado fluxo de execução.

	
  * A tomada de decisões altera o fluxo de execução de um programa.

Para concluir, vamos dar uma espiada nas estruturas de comparação de um programa em C e suas conseqüentes mudanças de fluxo. Note também que as comparações são feitas com variáveis internas.

If significa "se", ou seja, faz uma comparação, e retorna se a comparação é verdadeira (sim!) ou não (não!). Porém, o if apenas faz alguma coisa se o resultado for sim.

Else significa "senão", ou seja, é o complemento do if. Lembra-se que o if só faz alguma coisa se o resultado da comparação for sim? Pois bem, o else permite fazer outra coisa se o resultado for não.

While significa "enquanto", e é o nosso primeiro exemplo de laço, ou loop. Um loop faz constantemente a mesma coisa enquanto o resultado da comparação for sim. Uma vez que for não (pode ser a primeira, inclusive), ele não faz mais nada e o programa continua seu fluxo natural.

For significa "por", com o mesmo sentido que em "ele me chutou por 5 vezes seguidas". Ele pode ter muitos usos, mas o tradicional é fazer n vezes alguma coisa, sabendo que n é um número de vezes já conhecido. Nesse caso, o loop serve apenas para repetir um determinado número de vezes uma ação, sem nunca variar esse número de vezes.

Programar não tem segredo. É tudo uma questão de gostar, aprender, executar, aprender, gostar mais, aprender mais, executar mais, etc. Não exatamente nessa ordem. Tudo vai depender dos seus dados de entrada. Mas o fluxo já começou sua execução...

  * A inteligência do if - parte 1
  * A inteligência do if - parte 2
  * Arquitetura de von Neumann
  * Máquina de Turing
