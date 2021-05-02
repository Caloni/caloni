---
date: "2008-02-15"
title: "Os diferentes erros na linguagem C"
categories: [ "code", "ccpp", "home" ]
---
Uma coisa que me espanta de vez em quando é o total desconhecimento por programadores mais ou menos experientes dos níveis de erros que podem ocorrer em um fonte escrito em C ou C++. Desconheço o motivo, mas desconfio que o fato de outras linguagens não terem essa divisão de processos pode causar alguma nivelação entre as linguagens e fazer pensar que o processo de compilação em C é como em qualquer outra linguagem.

Porém, para começar, só de falarmos em compilação já estamos pegando apenas um pedaço do todo, que é a geração de um programa executável em C. Tradicionalmente, dividimos esse processo em três passos:

  1. Preprocessamento
  2. Compilação
  3. Linkedição

Vamos dar uma olhada mais de perto em cada um deles e descobrir erros típicos de cada processo.

O preprocessamento é especificado pelos padrões C e C++, mas, tecnicamente, não faz parte da linguagem. Ou seja, antes que qualquer regra de sintaxe seja verificada no código-fonte, o preprocessamento já terá terminado.

Essa parte do processo lida com substituição de texto e diretivas baseadas em arquivos e símbolos. Por exemplo, a diretiva de preprocessamento mais conhecida

    #include <stdio.h>

faz com que todo o conteúdo do arquivo especificado seja incluído exatamente no ponto onde for colocada essa diretiva. Isso quer dizer que, antes sequer do código-fonte ser compilado, todo o conteúdo desse header padrão estará no corpo do arquivo C.

Para evitar que o mesmo header seja incluído inúmeras vezes dentro da mesma unidade em C, causando assim erros de redefinição, existe outra diretiva muito usada para cercar esses arquivos públicos:

    #ifndef __MEUHEADER__ // se já estiver definido, caio fora até endif
    #define __MEUHEADER__
    
    // conteúdo do header
    
    #endif // __MEUHEADER__

Esse conjunto de duas diretivas, por si só, é capaz de gerar os mais criativos e bizarros erros de compilação em C. E estamos falando de erros que ocorrem antes que sequer seja iniciado o processo de compilação propriamente dito. Obviamente que os erros serão capturados durante a compilação, mas o motivo deles terem ocorrido foi um erro decorrente do processo de preprocessamento. Por exemplo, vamos supor que um determinado fonte necessita de uma declaração de função contida em meuheader.h:

    #include "header-do-mal.h"
    #include "meuheader.h"
    
    int func()
    {
       meuheaderFunc();
    }

Porém, num daqueles acasos da natureza, o header-do-mal.h define justamente o que não poderia definir jamais (obs.: e isso pode muito bem acontecer na vida real, se usamos definições muito comuns):

    #ifndef __HEADERDOMAL__
    #define __HEADERDOMAL__
    
     // tirei header da jogada, huahuahua (risos maléficos)
    #define __MEUHEADER__
    
    #endif // __HEADERDOMAL__

Na hora do preprocessamento, o preprocessador não irá mais incluir o conteúdo dentro de header.h:

    #ifndef __MEUHEADER__ // se já estiver definido, caio fora até endif
    #define __MEUHEADER__
    
    int meuheaderFunc(); // talvez alguém precise disso
    
    #endif // __MEUHEADER__

Conseqüentemente, durante a compilação do código-fonte já preprocessado, sem a declaração da função meuheaderFunc, irá ocorrer o seguinte erro:

    error C3861: 'meuheaderFunc': identifier not found

Isso em fontes pequenos é facilmente identificável. Em fontes maiores, é preciso ter um pouco mais de cuidado.

Após o processo de preprocessamento, de todos os arquivos indicados terem sido incluídos, de todas as macros terem sido substituídas, todas as constantes colocadas literalmente no código-fonte, temos  o que é chamado unidade de compilação, que será entregue ao compilador, que, por sua vez, irá começar a análise sintática de fato, descobrindo novos erros que podem ou não (como vimos) ter a ver com a fase anterior. A figura abaixo ilustra esse processo, com algumas trocas conhecidas:

![Preprocessor](/img/preprocessor.gif)

Dica: quando o bicho estiver pegando, e tudo o que você sabe sobre linguagem C não estiver te ajudando a resolver um problema, tente gerar uma unidade de compilação em C e analisar sua saída. Às vezes o que é claro no código pode se tornar obscuro após o preprocessamento. Para fazer isso no VC++ em linha de comando, use o parâmetro /E.

Se você conseguir passar ileso para a fase de compilação, pode se considerar um mestre do preprocessamento.  Por experiência própria, posso afirmar que a maior parte do tempo gasto corrigindo erros de compilação, por ironia do destino, não terá origem na compilação em si, mas no preprocessamento e linkedição. Isso porque o preprocessamento confunde muito o que vimos no nosso editor preferido, e a linkedição ocorre em uma fase onde não importa mais o que está dentro das funções, mas sim o escopo de nomes, um assunto um pouco mais vago do que a linguagem C.

Na compilação você irá encontrar geralmente erros bem comportados, como conversão entre tipos, else sem if e esquecimento de pontuação ou parênteses.

    int cannotConvertError(const char* message)
    {
    	int ret = message[0];
    	return ret;
    }
    
    int ret = cannotConvertError(3);
    
    error C2664: 'cannotConvertError' : cannot convert parameter 1 from 'int' to 'const char *'

    if( test() )
    	something;
    	something-else;
    else
    	else-something;

    error C2181: illegal else without matching if

    while( (x < z) && func(x, func2(y) != 2 )
    {
    	something;
    }

    error C2143: syntax error : missing ')' before '{'

Claro, não estamos falando de erros relacionados a templates, que são um pesadelo à parte.

Dica: nunca subestime o poder de informação do compilador e da sua documentação. Se o erro tem um código (geralmente tem), procure a documentação sobre o código de erro específico, para ter uma idéia de por que esse erro costuma ocorrer, exemplos de código com esse erro e possíveis soluções. Ficar batendo a cabeça não vai ajudar em nada, e com o tempo, você irá ficar sabendo rapidamente o que aconteceu.

Chegando na linkedição, onde a esperança reside, tudo pode vir por água abaixo. Isso porque você já espera confiante que tudo dê certo, quando, na verdade, um erro bem colocado pode fazer você desistir pra sempre desse negócio de programar em C.

As características mais desejadas para corrigir erros nessa fase são:

  1. Total conhecimento da fase do preprocessamento
  2. Total conhecimento da fase da compilação
  3. Total conhecimento de níveis de escopo e assinatura de funções

Os dois primeiros itens são uma maldição previsível que deve-se carregar para todo o sempre. Se você não consegue entender o que aconteceu nas duas primeiras fases, dificilmente irá conseguir seguir adiante com essa empreitada. O terceiro item significa que deve-se levar em conta as bibliotecas que estamos usando, headers externos (com dependências externas), conflitos entre nomes, etc.

Alguns erros mais encontrados aqui são as funções não encontradas por falta da LIB certa ou por LIBs desatualizadas que não se encaixam mais com o projeto, fruto de muitas dores de cabeça de manutenção de código. Essa é a parte em que mais vale a pena saber organizar e definir uma interface clara entre os componentes de um projeto.

Do ponto de vista técnico, é a fase onde o linker junta todos os arquivos-objeto especificados, encontra as funções, métodos e classes necessárias e monta uma unidade executável, como ilustrado pela figura abaixo.

![Linker](/img/linker.gif)

Dica: uma LIB, ou biblioteca, nada mais é que uma coleção de arquivos-objeto que já foram compilados, ou seja, já passaram pelas duas primeiras fases, mas ainda não foram linkeditados. Muitas vezes é importante manter compatibilidade entre LIBs e os projetos que as usam, de forma que o processo de linkedição ocorra da maneira menos dolorosa possível.

É óbvio que, por ter passado pelas três fases de transformação de um código-fonte em um programa executável, não quer dizer que este programa está livre de erros. Os famigerados erros de lógica podem se disfarçar até o último momento da compilação e só se mostrarem quando o código estiver rodando (de preferência, no cliente).

Entre esses erros, os mais comuns costumam se aproveitar de macros, como max, que usa mais de uma vez o parâmetro, que pode ser uma chamada com uma função. A função será chamada duas vezes, mesmo que aparentemente no código a chamada seja feita uma única vez:

    #define max(a, b) ( a > b ? a : b )
    
    int z = max( func(10), 30 );

Um outro erro que já encontrei algumas vezes é quando a definição de uma classe tem um sizeof diferente do compilado em sua LIB, pela exclusão ou adição de novos membros. Isso pode (vai) fazer com que, durante a execução, a pilha seja corrompida, membros diferentes sejam acessados, entre outras traquinagens. Esses erros costumam acusar a falta de sincronismo entre os headers usados e suas reais implementações.

Enfim, na vida real, é impossível catalogar todos os erros que podem ocorrer em um fonte em C. Se isso fosse possível, ou não existiriam bugs, ou pelo menos existiria uma ferramenta para automaticamente procurar por esses erros e corrigi-los. Bom, existe o Lint.

Criei um [projeto] com alguns erros básicos, alguns demonstrados aqui, outros não, mas enfim, completamente configuráveis e divididos nessas três fases. É possível habilitar e desabilitar erros através do header cpperrors.h. Espero que gostem.

[projeto]: https://github.com/Caloni/cpperrors
