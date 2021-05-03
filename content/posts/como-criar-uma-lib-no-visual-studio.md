---
categories:
- draft
- code
date: '2008-05-29'
title: Como criar uma LIB no Visual Studio
---

Quando se está começando no ramo, alguns detalhes nunca vêm à tona para o programador novato. Ele simplesmente vai codando até se sentir satisfeito com o prazer que é proporcionado pela prática da arte dos deuses de silício.

Isso, em termos práticos, quer dizer que todo o fonte vai ser escrito no mesmo ".c", que aliás talvez nem se dê ao luxo de possuir seu próprio ".h": pra quê, se as funções são todas amigas de infância e todas se conhecem?

No começo não existe nenhum problema, mesmo. O fonte vai ser pequeno. A coisa só complica quando não dá mais pra se achar no meio de tantos _gotos_ e _ifs_ aninhados. Talvez nessa hora o programador já-não-tão-novato até tenha descoberto que é possível criar vários arquivos-fonte e reuni-los em um negócio chamado projeto, e que existem IDEs, como o Visual Studio, que organizam esses tais projetos.

A partir daí, para chegar em uma LIB, já é meio caminho andado.

#### Mas, afinal de contas, pra que eu preciso de uma LIB, mesmo?

Boa pergunta. Uma LIB, ou biblioteca, nada mais é do que um punhado de ".obj" colocados todos no mesmo arquivo, geralmente um ".lib". Esses ".obj" são o resultado da compilação de seus respectivos ".c" de origem.

[![salada2.gif](http://i.imgur.com/SiYvl1N.gif)](/images/salada2.gif)

Alguns acreditam ser esse negócio de LIB uma pura perda de tempo, pois existem trocentas configurações diferentes (e incompatíveis) e trocentas compilações diferentes para gerenciar. Outros acham que o problema está no tempo de compilação, enquanto outros defendem o uso dos ".obj" de maneira separada. Esse artigo não presume que nem um nem outro seja melhor. Apenas ensina o que você precisa saber para criar sua primeira LIB usando o Visual Studio Express.

Vamos lá?

#### Criando seu primeiro projeto de LIB

Após abrir o VS, tudo que precisamos fazer é ir em New, Project, e escolher a configuração de "Win32 Project":

[![myfirstlib.png](http://i.imgur.com/o2OVzZn.png)](/images/myfirstlib.png)

A seguir, escolhemos nas opções do assistente criar uma "Static library", e desmarcamos a opção de "Precompiled header" para evitar má sorte logo no primeiro projeto de LIB (má sorte significa horas procurando erros incríveis que você só irá fazer desaparecer se recompilar tudo com o uso do famigerado "Rebuild All"; espero que isso dê certo para você, para mim não tem funcionado).

![myfirstlib2.png](http://i.imgur.com/8q9Xv2B.png)

E pronto! Temos um projeto de LIB completo, funcional e... um tanto inútil. Mas, calma lá. Ainda não terminamos.

![myfirstlib3.png](http://i.imgur.com/HiIw4iE.png)

#### Adicionando arquivos à sua LIB

Conforme o programador consegue se livrar das maldições das mil dependências, aos poucos ele vai conseguindo novas funções genéricas e encaixáveis para colocar em sua coleção de objs.  Essa com certeza não é uma tarefa fácil, mas ei, quem disse que esse trampo de programador seria fácil?

Vamos imaginar que você é muito do sem imaginação (típico de pessoas que mantêm blogues) e criou duas funções lindíssimas que somam e multiplicam dois números:

    
    int sum(int a, int b)
    {
       return a + b;
    }
    
    int mult(int a, int b)
    {
       return a * b;
    }

Não são aquelas coisas, mas são genéricas e, até certo ponto, "úteis" para o nosso exemplo.

Agora, tudo que temos que fazer é criar dois arquivos: mymath.c e mymath.h. No mymath.c, colocamos   as funções acima exatamente como estão. No mymath.h, colocamos apenas as declarações dessas duas funções, apenas para avisar outros ".c" que existem duas funções que fazem coisas incríveis nessa nossa LIB.

    
    /* soma dois números */
    int sum(int a, int b);

    
    /* multiplica dois números */
    int mult(int a, int b);

Adicionamos esses dois arquivos ao projeto (se já não estão), e _voilà_!

    
    ------ Build started: Project: MyFirstLib, Configuration: Debug Win32 ------
    Compiling...
    mymath.c
    Creating library...
    Build log was saved at "file://c:\Projects\temp\MyFirstLib\Debug\BuildLog.htm"
    MyFirstLib - 0 error(s), 0 warning(s)
    ========== Build: 1 succeeded, 0 failed, 0 up-to-date, 0 skipped ==========

#### Usando a LIB mais maravilhosa de todos os tempos

Para usar uma LIB temos inúmeras maneiras de fazê-lo. A mais simples que eu conheço é criar um novo projeto no mesmo Solution de sua LIB. Um console, por exemplo:

![myfirstlib4.png](http://i.imgur.com/cokWnIx.png)

![myfirstlib5.png](http://i.imgur.com/Lr5Jhfd.png)

![myfirstlib6.png](http://i.imgur.com/4yLsZ3p.png)

Se você seguiu todos os passos direitinho, e eu estou assumindo que você já sabia como criar um projeto console, sua saída da compilação talvez seja mais ou menos essa:

    
    ------ Build started: Project: MyFirstCmd, Configuration: Debug Win32 ------
    Compiling...
    mycmd.c
    Linking...
    mycmd.obj : error LNK2019: unresolved external symbol _mult referenced in function _main
    mycmd.obj : error LNK2019: unresolved external symbol _sum referenced in function _main
    c:\Projects\temp\MyFirstLib\Debug\MyFirstCmd.exe : fatal error LNK1120: 2 unresolved externals
    Build log was saved at "file://c:\Projects\temp\MyFirstCmd\Debug\BuildLog.htm"
    MyFirstCmd - 3 error(s), 0 warning(s)
    ========== Build: 0 succeeded, 1 failed, 1 up-to-date, 0 skipped ==========

Dois erros! Ele não achou os símbolos _mult e _sum. Mas eles estão logo ali! E agora?

Nada a temer: tudo que temos que fazer é falar para o Solution que o projeto myfirstcmd depende do projeto myfirstlib:

![myfirstlib7.png](http://i.imgur.com/2SNMdya.png)

![myfirstlib8.png](http://i.imgur.com/I0roqBK.png)

    
    ------ Build started: Project: MyFirstCmd, Configuration: Debug Win32 ------
    Linking...
    Embedding manifest...
    Microsoft (R) Windows (R) Resource Compiler Version 6.0.5724.0
    Copyright (C) Microsoft Corporation.  All rights reserved.
    Build log was saved at "file://c:\Projects\temp\MyFirstCmd\Debug\BuildLog.htm"
    MyFirstCmd - 0 error(s), 0 warning(s)
    ========== Build: 1 succeeded, 0 failed, 1 up-to-date, 0 skipped ==========

Isso resolve o problema de organização e compilação quando temos dezenas de ".c" espalhados pelo projeto. Existem melhores alternativas, mais bem organizadas e estruturadas, inclusive lingüisticamente falando. No entanto, tudo tem sua hora, e só se deve preocupar-se com isso quando sua solução tiver algumas dezenas de ".lib". Até lá!