---
date: "2007-12-07"
title: Makefiles (e Visual Studio para todos)
categories: [ "code" ]
---
O Visual Studio é um ambiente de programação incrível, mesmo. Ele possui _auto-complete_ quase instantâneo, navegação de tipos, ajuda de contexto e flexibilidade em seus projetos. Existem [pessoas que evitam usá-lo](http://www.caloni.com.br/desenvolvendo-em-linha-de-comando) porque ele ocupa mais de 150 MB de memória virtual e 20 MB de _working set_ sem abrir nenhum projeto, mas, francamente, ele acaba sendo mais produtivo que o Bloco de Notas (exceto para testes).

Devido a pedidos de amigos, resolvi dar uma pausa nos [artigos sobre o Builder](http://www.caloni.com.br/blog/search/c++%20builder) para explicar o nível que flexibilidade que podemos obter dentro da IDE do Visual Studio para compilar qualque tipo de projeto, para qualquer plataforma e sistema operacional. Temos na verdade até a liberdade para não compilar nada! De brinde veremos o básico sobre os _makefiles_, aqueles famigerados arquivos de configuração que nossos avôs usavam em seus _mainframes_.

#### Don't built it: make it!

Na verdade, o aplicativo **make**, que faz [30 anos de idade](http://en.wikipedia.org/wiki/Make_%28software%29) esse ano, foi usado e inventado originalmente nos laboratórios Bell, antro das idéias mais criativas e poderosas daquela época. Criado para ser usado nos sistemas UNIX, com o tempo o programa se espalhou para outras plataformas e ganhou espaço entre as mais diversas levas de programadores.

Sua principal função continua de pé: compilar automaticamente projetos muito grandes. Isso quer dizer que, independente da complexidade do processo de geração de binários, esse aplicativo conseguia se virar e construir todo seu projeto através de um comando mágico. Melhor ainda, ele conseguia distingüir os arquivos que mudavam e compilar apenas o que mudou.

Mesmo com todas essas vantagens, o que realmente popularizou essa ferramenta foi sua **portabilidade** e **flexibilidade**, sendo possível através dela fazer virtualmente qualquer coisa baseado em dependências.

#### Como funciona um makefile

**Makefile** é como é chamado o arquivo de configurações usado pelo **make** para realizar as operações de _build_. Sua sintaxe básica é extremamente simples, embora muito poderosa:

regra

    
    :

dependência 

    
    [

dependência 

    
    ...]

comandocomandocomando

    
       ...

Eu costumo imaginar suas partes como uma **receita de bolo**, porque é a maneira mais fácil de entender seu comportamento, e de certa forma é assim que ele funciona:

    
  * Regra - é o nome de uma "receita" e sua "especificação": os ingredientes são as dependências e o modo de preparar são seus comandos.

    
  * Dependências - como eu disse, os ingredientes necessários para preparar uma determinada receita (regra); note que um ingrediente pode ser uma outra regra e que podem existir diversos ingredientes, separados por espaço.

    
  * Comandos - os passos necessários para preparar uma receita (regra), executado (literalmente) no ambiente de execução do make.

Vamos analisar algumas receitas/regras bem simples que fazem parte do nosso dia-a-dia. Para facilitar a visualização, coloquei a regra na cor azul, as dependências em verde e os comandos em vermelho.

<blockquote>

> 
> #### Atenção com seus comandos!
> 
_Note que os comandos não estão de vermelho à toa. É muito importante prestar atenção nas operações envolvidas na configuração de um makefile, pois estar linhas serão executadas em seu ambiente de compilação. Não importa que esteja um "cl fonte.cpp" ou um "format c:"; o seu aplicativo make irá executá-lo de qualquer forma._</blockquote>

#### Apagar um arquivo no makefile

delete-file

    
    :

file.txt del file.txt

Como podemos ver, o comando para apagar um arquivo é "del file.txt", sendo file.txt o nome do arquivo. Como a existência desse arquivo é necessária para sua exclusão, ele está na lista de ingredientes da receita delete-file.

#### Renomear um arquivo no makefile

rename-file

    
    :

file.txt ren file.txt old-file.txt

A mesma lógica para apagar um arquivo: precisamos de file.txt para renomeá-lo.

#### Compilar um arquivo C no makefile

compile-file

    
    :

file.c cl file.c

Ahá! Aí está o verdadeiro objetivo da invenção do make: podemos compilar programas através dele. O exemplo acima compila apenas um arquivo, mas podemos compilar inúmeros, fazer o _link_ de todos eles, e inclusive rodar rotinas de teste. Poderíamos dividir este exemplo em passos distintos: compilação e linkedição.

generate-file: link-file

    
    link-file:

file.objlink file.obj

    
    file.obj:

file.c cl file.c

Note a lógica envolvida: o make tenta executar generate-file. Para isso ele precisa de link-file. Então ele busca link-file, que por sua vez precisa do file.obj. O file.obj precisa do file.c, e nele é executada a compilação. Feito isso, o make volta e executa link-file, efetuando a linkedição do file.obj. Terminado o link-file, a única dependência de generate-file está completa: fim da execução.

#### Makefiles para o terceiro milênio

Bom, o mundo girou, o tempo passou, e hoje temos IDEs para todos os lados cuidando de nossos CPPs como se fôssemos bebês chorões que não agüentam configurar um projeto através de um arquivo texto. A IDE cuida de tudo para você, deixando mais tempo para você fazer o que mais importa: assistir aos vídeos do [YouTube](http://www.youtube.com/watch?v=LsiT68nZNKI).

Porém, toda a flexibilidade do mundo make não foi abandonada completamente; foi apenas deixada de lado. A maioria das IDEs profissionais permite o uso de projetos baseados nos famosos makefiles, que são os tais arquivos de configuração que devemos editar na mão para dizer ao aplicativo make como compilar nosso projeto.

#### Visual Studio e os makefiles

O Visual Studio permite a criação de projeto makefile. Na verdade, ele vai além e permite que você diga o que esse projeto deve fazer para compilar seu projeto, o que nos permitirá fazer qualquer coisa usando qualquer aplicativo. Abaixo temos o passo-a-passo para criar um projeto desse tipo.

A primeira coisa a fazer é criar um projeto do tipo makefile.

[![VS New Project](http://i.imgur.com/HGXtkSu.png)](/images/vs-new-project.png)

Você vai encontrar este tipo de projeto na categoria General.

[![VS Project](http://i.imgur.com/xOSEXhS.png)](/images/vs-makefile-project.png)

Durante o _wizard_ de criação, já é possível escolher qual será o comando para compilar, recompilar e limpar o projeto.

[![VS Config](http://i.imgur.com/73YAEBg.png)](/images/vs-makefile-config.png)

Se você se esqueceu de configurar essas opções aí, não tem problema. Elas estarão sempre disponíveis através da opção de menu "Projects, Options".

[![VS Config2](http://i.imgur.com/mO5PrL0.png)](/images/vs-makefile-config2.png)

Após todas essas operações teremos um projeto que não é controlado pela IDE, mas por [você](http://desciclo.pedia.ws/wiki/Reversal_Russa). O comando que você colocar na última tela irá definir o que o Visual Studio terá que fazer para construir seu projeto. Isso quer dizer "qualquer coisa". Porém, no momento estamos interessados em rodar o aplicativo make, baseado em um makefile que iremos configurar.

#### Um makefile que faz tudo

Para mostrar todas as potencialidades de um makefile em um projeto multialgumacoisa, vamos criar um makefile que compila nosso singelo fonte em três ambientes distintos: o compilador do Visual Studio, o GCC e o compilador da Borland. Eis o singelo fonte:

```c
#include <stdio.h>

int main()
{
	printf("Hello, Make!!\n");
	return 0;
} 

```

E eis o singelo makefile:

# # Makefile de exemplo para compilarmos todos # os makefiles de todos os ambientes # # Wanderley Caloni # all

    
    :

hello-make-gcc.exe hello-make-bcc.exe hello-make-cl.exehello-make-gcc.exe

    
    :

mingw32-make -fmakefile.gcchello-make-cl.exe

    
    :

nmake /f makefile.clhello-make-bcc.exe

    
    :

make -fmakefile.bcc

Como podemos ver, temos três ingredientes para essa receita, três executáveis, cada um com seu nome distinto e seu modo de preparar distinto. Note que uso mais três makefiles, cada um com seu conteúdo específico para preparar cada um seu executável. Como não é nenhum segredo, vou mostrá-los aqui:

    
    #
    # Makefile de exemplo para compilarmos um
    # projeto no MingGW
    #
    # Wanderley Caloni
    #
    
    all: hello-make-gcc.exe
    
    hello-make-gcc.exe: hello-make.c
        gcc -o hello-make-gcc hello-make.c

    
    #
    # Makefile de exemplo para compilarmos um
    # projeto no Visual Studio
    #
    # Wanderley Caloni
    #
    
    all: hello-make-cl.exe
    
    hello-make-cl.exe: hello-make.obj
        link /OUT:hello-make-cl.exe hello-make.obj
    
    hello-make.obj:
        cl -c hello-make.c

    
    #
    # Makefile de exemplo para compilarmos um
    # projeto no Borland C++ Builder
    #
    # Wanderley Caloni
    #
    
    all: hello-make-bcc.exe
    
    hello-make-bcc.exe: hello-make-bcc.obj
        ilink32 hello-make-bcc.obj
    
    hello-make-bcc.obj:
        bcc32 -o hello-make-bcc.obj -c hello-make.c

Como podem ver, não há segredo algum. Alguns ambientes eu configurei para compilar e efetuar o _link_ diretamente. Outros eu dividi em dois passos, para demonstrar que é possível dividir uma receita em diversas parte (o recheio, a cobertura, etc).

#### E para rodar tudo isso?

A divisão é feita para mostrar de forma didática como criar makefiles para três ambientes distintos. Dessa forma, é possível chamar o makefile principal com qualquer um desses ambientes: nmake (Visual Studio), mingw32-make (GCC) ou make (Borland). A configuração no Visual Studio fica como está na figura abaixo.

[![VS Config3](http://i.imgur.com/89ob8LZ.png)](/images/vs-makefile-config3.png)

Porém, veremos como dividir essa bagunça de ambientes em um projeto bem organizado.

#### Configuration Manager

O Visual Studio organiza suas configurações inicialmente em Debug e Release. No entanto, nada impede que criemos diferentes configurações para diferentes ambientes. Tudo isso pode ser feito através do Configuration Manager (Build, Configuration Manager). No projeto de demonstração, criei uma configuração Debug e Release para cada ambiente, além do principal, que compila para todos. A lista ficou como a figura abaixo.

[![Configuration Manager](http://i.imgur.com/SKo2nyL.png)](/images/vs-makefile-configuration-manager.png)

Para configurações específicas, comandos específicos. Para configurações genéricas, comandos que compilam todos os ambientes. Os comandos específicos mandam compilar apenas o makefile de seu respectivo ambiente:

    
    nmake /f makefile.cl
    mingw32-make -fmakefile.gcc
    make -fmakefile.bcc

#### O que faltou fazer

É necessário que todas as ferramentas usadas nas três configurações estejam disponíveis no _path_ do sistema, inclusive as três ferramentas make. A nmake, do Visual Studio, já está disponível por _default_. Uma outra opção, para quem não quer poluir o sistema, é definir um arquivo _batch_ que define um _path_ do sistema temporário com tudo que o ambiente precisa, e daí chamar o make.

Eu obviamente não defini cada configuração para gerar seus arquivos em uma pasta específica, nem defini configurações diferentes para Debug e Release. Esse foi um simples exemplo de como é possível usar o Visual Studio, mesmo o gratuito Express, para qualquer projeto que vá rodar em qualquer plataforma.

E finalmente, este não é um modelo que segue todas as recomendações de como gerar o makefile perfeito. Ele está cheio de erros de redundância e praticidade. Meu objetivo foi pura e simplesmente apresentar esta característica do Visual Studio de forma didática, de forma que mais pessoas passem a utilizá-lo, independente se desejam compilar fontes para o Windows ou não.

#### Antes que eu me esqueça

O projeto com todas essas configurações, e o fonte, está disponível para _download_ [aqui](/images/makefile.7z).
