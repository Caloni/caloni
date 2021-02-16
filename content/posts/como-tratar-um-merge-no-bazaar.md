---
date: "2008-05-09"
title: Como tratar um merge no Bazaar
tags: [ "draft", "code" ]
---
Hoje fizemos um _merge _de duas versões que entraram em conflito em nosso projeto-piloto usando **bzr**. Isso geralmente ocorre quando alguma coisa mudou no mesmo arquivo em lugares muito próximos um do outro. Veremos um exemplo de código para ter uma idéia de quão fácil é o processo:

```cpp
#include <stdio.h>

void InitFunction()
{
	printf("InitFunction");
}

void DoAnotherJob()
{
	char buf[100] = "";
	fgets(buf, sizeof(buf), stdin);
	printf("New line: %s", buf);
}

void TerminateFunction()
{
	printf("TerminateFunction");
}

int main()
{
	InitFunction();

	while( ! feof(stdin) )
	{
		DoAnotherJob();
	}

	TerminateFunction();
}

 

```

A execução do programa contém uma saída parecida com as linhas abaixo:

    
    C:\Tests\bzrpilot>bzppilot.exe
    InitFunctionuma linha
    New line: uma linha
    duas linhas
    New line: duas linhas
    tres linhas
    New line: tres linhas
    ^Z
    New line: TerminateFunction
    C:\Tests\bzrpilot>

Parece que está faltando algumas quebras de linha. Além de que sabemos que nossos arquivos de entrada poderão conter até 200 caracteres por linha, o que pode gerar um desastre em nosso buffer de 100 bytes. Buffer overflow!

Para corrigir ambos os problemas foram criados dois _branches_, seguindo as melhores práticas de uso de um controle de fonte distribuído:

    
    C:\Tests>bzr branch bzrpilot bzrpilot-linebreak
    Branched 1 revision(s).
    
    C:\Tests>bzr branch bzrpilot bzrpilot-bufferoverflow
    Branched 1 revision(s).

Feitas as correções devidas, o _branch _linebreak fica com a seguinte cara:

    
    void InitFunction()
    {

printf("InitFunction\n");

    
    }
    
    void DoAnotherJob()
    {
            char buf[100] = "";
            fgets(buf, sizeof(buf), stdin);

printf("New line: %s\n", buf);

    
    }
    
    void TerminateFunction()
    {

printf("TerminateFunction\n");

    
    }

Em vermelho podemos notar as linhas alteradas. Uma mudança diferente foi feita para o bug do _buffer overflow_, em seu _branch _correspondente:

    
    void DoAnotherJob()
    {

char buf[200] = "";

    
            fgets(buf, sizeof(buf), stdin);
            printf("New line: %s", buf);
    }

Agora só temos que juntar ambas as mudanças no _branch _principal.

#### "Mas espere aí! Não é uma boa termos números mágicos no código!"

Com toda razão, pensa o programador que está corrigindo o bug da quebra de linha, olhando sorrateiramente a função do meio, intocada, **DoAnotherJob**.

Então ele resolve fazer um pequeno fix "de brinde", desconhecendo que mais alguém andou alterando essas linhas:

#define ENOUGH_BYTES 100

    
    void InitFunction()
    {
            printf("InitFunction\n");
    }
    
    void DoAnotherJob()
    {

char buf[ENOUGH_BYTES] = "";

    
            fgets(buf, sizeof(buf), stdin);
            printf("New line: %s\n", buf);
    }

Pronto. Um fonte politicamente correto! E que vai causar um conflito ao juntar essa galera. Vamos ver na seqüência:

    
    C:\Tests>bzr log bzrpilot-linebreak --short
        3 Wanderley Caloni  2008-05-08
          A little fix
    
        2 Wanderley Caloni  2008-05-08
          Corrected line breaks
    
        1 Wanderley Caloni  2008-05-08
          Our first version
    
    C:\Tests>bzr log bzrpilot-bufferoverflow --short
        2 Wanderley Caloni  2008-05-08
          Corrigido buffer overflow
    
        1 Wanderley Caloni  2008-05-08
          Our first version

    
    C:\Tests>bzr log bzrpilot --short
        1 Wanderley Caloni  2008-05-08
          Our first version

    
    C:\Tests>cd bzrpilot
    
    C:\Tests\bzrpilot>bzr pull ..\bzrpilot-linebreak
     M  bzppilot.cpp
    All changes applied successfully.
    Now on revision 3.
    
    C:\Tests\bzrpilot>bzr pull ..\bzrpilot-bufferoverflow

bzr: ERROR: These branches have diverged. Use the merge command to reconcile them.

Ops. Algo deu errado no segundo _pull_. O Bazaar nos diz que os _branches _estão diferentes, e que termos que usar o comando _merge _no lugar.

    
    C:\Tests\bzrpilot>bzr merge ..\bzrpilot-bufferoverflow
     M  bzppilot.cpp

Text conflict in bzppilot.cpp

    
    1 conflicts encountered.

Usamos _merge _no lugar do _pull _e ganhamos agora um conflito no arquivo bzppilot.cpp, nosso único arquivo. Vamos ver a bagunça que fizemos?

#### Como funcionam os merges no Bazaar

A última coisa que um controle de fonte quer fazer é confundir ou chatear o usuário. Por isso mesmo, a maioria dos conflitos que o Bazaar encontrar nos fontes serão resolvidos usando o algoritmo "se só um mexeu, então coloca a mudança". A tabela do [guia do usuário](http://doc.bazaar-vcs.org/bzr.dev/en/user-guide/#merging-changes) ilustra esse algoritmo em possibilidades:

    
    Ancestral   Usuário1   Usuário2    Resultado   Comentário
       x           x           x           x        não muda
       x           x           y           y        usuário 2 ganhou
       x           y           x           y        usuário 1 ganhou
       x           y           z           ?

conflito!!!

O ancestral é a última modificação em comum dos dois _branches _que estamos fazendo _merge_. Do ancestral pra frente cada um seguiu seu caminho, podendo existir quantas modificações quisermos.

Como podemos ver, o conflito só ocorre se ambos os usuário mexerem na mesma parte do código ao mesmo tempo. Eu disse **na mesma parte do código**, e não apenas no mesmo arquivo. Isso porque se a mudança for feita no mesmo arquivo, porém em locais diferentes, o conflito é resolvido automaticamente.

Em todos os conflitos de texto desse tipo, o Bazaar cria três arquivos de suporte e modifica o arquivo em conflito. Isso para cada conflito.

    
    arquivo.cpp          Resultado de até onde o Bazaar conseguiu o merge
    arquivo.cpp.BASE     Versão ancestral do arquivo
    arquivo.cpp.THIS     Nosso arquivo original antes de tentar fazer merge
    arquivo.cpp.OTHER    A versão que entrou em conflito com a nossa

Podemos fazer o _merge _da maneira que quisermos. Se vamos usar nossa versão de qualquer jeito é só sobrescrever o arquivo.cpp pelo arquivo.cpp.THIS. Se vamos fazer troca-troca de alterações, abrimos os arquivos .THIS e .OTHER e igualamos suas diferenças, copiando-as para arquivo.cpp.

Recomendo primeiramente olhar o que o Bazaar já fez. Se houver dúvidas sobre a integridade das mudanças, comparar diretamente os arquivos THIS e OTHER.

Vamos dar uma olhada na versão criada pelo Bazaar:

    
    #include <stdio.h>
    
    #define ENOUGH_BYTES 100
    
    void InitFunction()
    {
            printf("InitFunction\n");
    }
    
    void DoAnotherJob()
    {

<<<<<<< TREE

    
            char buf[ENOUGH_BYTES] = "";

=======

    
            char buf[200] = "";

>>>>>>> MERGE-SOURCE

    
            fgets(buf, sizeof(buf), stdin);
            printf("New line: %s\n", buf);
    }
    
    void TerminateFunction()
    {
            printf("TerminateFunction\n");
    }
    
    int main()
    {
            InitFunction();
    
            while( ! feof(stdin) )
            {
                    DoAnotherJob();
            }
    
            TerminateFunction();
    }

Ora, vemos que ele já fez boa parte do trabalho para nós: as quebras de linha já foram colocadas e o novo define já está lá. Tudo que temos que fazer é trocar o _define _por 200 e tirar os marcadores, que é a junção das duas mudanças feitas no mesmo local, e que só um ser humano (AFAIK) consegue juntar:

#define ENOUGH_BYTES 200

    
    void InitFunction()
    {
            printf("InitFunction\n");
    }
    
    void DoAnotherJob()
    {

char buf[ENOUGH_BYTES] = "";

    
            fgets(buf, sizeof(buf), stdin);
            printf("New line: %s\n", buf);
    }

Resolvido o problema, simplesmente esquecemos das versões .BASE, .THIS e .OTHER e falamos pro Bazaar que está tudo certo.

    
    C:\Tests\bzrpilot>bzr resolve bzppilot.cpp

O controle de fonte apaga automaticamente os arquivos THIS, BASE e OTHER, mantendo o original como a mudança aceita.

Após as correções dos conflitos, temos que fazer um _commit _que irá ser o filho dos dois _branches _que estamos juntando.

    
    C:\Tests\bzrpilot>bzr commit -m "Tudo certo"
    Committing to: C:/Tests/bzrpilot/
    modified bzppilot.cpp
    Committed revision 4.
    
    C:\Tests\bzrpilot>bzr log
    ------------------------------------------------------------
    revno: 4
    committer: Wanderley Caloni <wanderley@caloni.com.br>
    branch nick: bzrpilot
    timestamp: Thu 2008-05-08 22:09:35 -0300
    message:
      Tudo certo
        ------------------------------------------------------------
        revno:

1.1.1

    
        committer: Wanderley Caloni <wanderley@caloni.com.br>
        branch nick: bzrpilot-bufferoverflow
        timestamp: Thu 2008-05-08 21:47:33 -0300
        message:
          Corrigido buffer overflow
    ------------------------------------------------------------
    revno: 3
    committer: Wanderley Caloni <wanderley@caloni.com.br>
    branch nick: bzrpilot-linebreak
    timestamp: Thu 2008-05-08 21:49:30 -0300
    message:
      A little fix
    ------------------------------------------------------------
    revno: 2
    committer: Wanderley Caloni <wanderley@caloni.com.br>
    branch nick: bzrpilot-linebreak
    timestamp: Thu 2008-05-08 21:44:23 -0300
    message:
      Corrected line breaks
    ------------------------------------------------------------
    revno:

1

    
    committer: Wanderley Caloni <wanderley@caloni.com.br>
    branch nick: bzrpilot
    timestamp: Thu 2008-05-08 21:33:53 -0300
    message:
      Our first version

A versão do branch alternativo é 1.1.1, indicando que ele saiu da revisão número 1, é o primeiro alternativo e foi o único commit. Se houvessem mais modificações neste branch, elas seriam 1.1.2, 1.1.3 e assim por diante. Se mais alguém quisesse juntar alguma modificação da revisão 1 ela seria 1.2.1, 1.3.1, 1.4.1 e assim por diante.

<blockquote>_Um erro comum que pode acontecer é supor que o arquivo original está do jeito que deixamos e já usar o comando resolve diretamente. É preciso tomar cuidado, pois se algum conflito é detectado quer dizer que o Bazaar deixou para você alguns marcadores no fonte original, o que quer dizer que ele simplesmente não vai compilar enquanto você não resolver seus problemas._</blockquote>

Enfim, tudo que temos que lembrar durante um merge do Bazaar é ver os conflitos ainda não resolvidos direto no fonte e alterá-los de acordo com o problema. O resto é codificar.
