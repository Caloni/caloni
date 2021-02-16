---
date: "2008-06-24"
title: Como estou trabalhando com o Bazaar
tags: [ "draft", "blog" ]
---
Depois de alguns ajustes e muitas perguntas do meu amigo-colega desenvolvedor [Rafael](http://www.sk5.com.br/), conseguimos definir alguns usos e costumes em nosso código controlado pelo Bazaar. Este é um guia para _Dummies_ de como é possível organizar um ou mais projetos de forma a favorecer o _refactoring _e a liberdade de uso.

#### Primeiro passo: padrão de árvore

Nosso padrão de diretórios utiliza um repositório compartilhado e dentro, na mesma ramificação, os _branches._ O _branch _principal tem o mesmo nome do projeto. Isso na máquina de um desenvolvedor ficaria:

    
    c:\src\project1
                 |
                 -- project1  (branch principal)
                 |
                 -- bug-da-tela-azul (branch secundário e temporário)
                 |
                 -- nova-tela-de-login (branch secundário e temporário)

No servidor de fontes geralmente teremos apenas o _branch _principal, apesar de que o desenvolvimento em paralelo seja permitido:

    
    c:\src\project1
                 |
                 -- project1  (branch principal)
                 |
                 -- 2.4.1 (branch secundário em desenvolvimento paralelo)

#### Segundo passo: projeto-modelo

Foi criado um projeto modelo para que todos os projetos herdassem seu histórico. Para que isso? Bom, na eventualidade de partes de um projeto irem parar em outro (isso quase nunca acontece), isso pode ser feito sem perder todo o histórico do início do projeto.

Resumindo: todos os projetos novos são _branches _do projeto-modelo.

    
    bzr init-repo _template
    cd _template
    bzr init _template
    hack hack hack
    bzr commit -m "Primeira versao de nosso projeto-modelo"

Como podemos ver acima, o projeto modelo segue o mesmo padrão de repositório compartilhado. Os projetos que criarmos serão baseados nesse projeto modelo, mas em outro repositório compartilhado.

    
    bzr init-repo novo-projeto
    bzr branch _template\_template novo-projeto\novo-projeto
    cd novo-projeto\novo-projeto
    hack hack hack
    bzr commit -m "Primeira versao de nosso novo projeto"

A ramificação dos projetos estará sempre no mesmo lugar, independente da pasta raiz.

    
    c:\src\--_template
           |     |
           |     -- _template
           |
           -- novo-projeto
           |     |
           |     -- novo-projeto
           |
           -- mais-um-projeto
                 |
                 -- mais-um-projeto

#### Terceiro passo: elegendo um servidor

O controle distribuído de fontes não significa que não existe um servidor. Existe. O detalhe é que todos os desenvolvedores guardam todo o histórico do projeto com eles, igualzinho o servidor, que é apenas mais uma máquina com mais um _branch._

O repositório do servidor pode ser criado com a opção que não cria o diretório de trabalho, que é onde os programadores mexem no código-fonte. Sendo um servidor, o código-fonte não é necessário, só a base de dados:

    
    bzr init-repo --no-trees novo-projeto
    bar branch \\desenvolvedor\src\novo-projeto\novo-projeto novo-projeto\novo-projeto

#### Quarto passo: tornando disponível o servidor

O Bazzar possui um esquema de servidor embutido nele, que fica escutando em uma porta e se comunica em um protocolo otimizado. Nós gostamos desse esquema, pois protege os projetos de acidentes de usuários que podem apagar uma pasta sem querer.

Para manter o Bazaar eternamente rodando, usamos [o programa do DriverEntry](http://www.driverentry.com.br/blog/2007/02/prog2svc-servio-sem-trabalho.html) que transforma qualquer coisa no formato de um serviço [de gelo](http://en.wikipedia.org/wiki/Wonder_Twins).

    
    prog2svc -add Bazaar "c:\program files\Bazaar\bzr.exe serve --allow-writes --diretory=c:\src"

Ou não sei usar direito esse programa ou ele não permite uso de aspas no nome do aplicativo junto de argumentos. Por isso tive que editar o registro onde ele fica para colocar aspas duplas em torno do bzr.exe.

[![bazaar-prog2svc.png](http://i.imgur.com/Md7EXVK.png)](/images/bazaar-prog2svc.png)

Após isso, ainda temos que configurar o serviço para iniciar automaticamente e usar um usuário conhecido. Enquanto o computador estiver ligado, mesmo que sem sessões abertas, nenhuma tela irá aparecer, mas o Bazaar estará rodando e ativo, escutando em sua porta padrão:

[![bazaar-service.png](http://i.imgur.com/ydtBG4o.png)](/images/bazaar-service.png)

Se estiver tudo certo, ao iniciar o serviço o Bazaar passará a ficar escutando e pronto para fazer _commits _e _branches_.

[![bazaar-tcpview.png](http://i.imgur.com/FkKIdGa.png)](/images/bazaar-tcpview.png)

Agora qualquer usuário da rede consegue fazer _updates _e _commits. _Um desenvolvedor novo faria o seguinte comando:

    
    bzr init-repo projeto
    bzr branch bzr://servidor/projeto projeto\projeto

<blockquote>_Note que o usuário do Bazaar não é obrigado a criar um repositório compartilhado. Esse foi um padrão definido aqui e não necessariamente é o melhor. _</blockquote>

#### Quinto passo: ensinando as pessoas a usar

O Bazaar por ser muito flexível entra naquela categoria de "[Difícil de acertar a maneira certa de utilizar](http://www.driverentry.com.br/blog/2008/06/utilizando-o-registry-parte-2.html)". Bom, mais ou menos. Eu sinceramente não acho que exista uma maneira errada de usar o Bazaar, mas vamos ver as maneiras mais comuns, que não são exclusivas entre si.

#### Desenvolvedor _standalone_

É aquele que prefere fazer tudo localmente e só depois, bem depois, mandar seus _commits _para o servidor. Nesse caso o comando para começar a programar é **branch**.

    
    bzr branch bzr://servidor/projeto projeto\projeto

Nesse esquema o servidor e a máquina do desenvolvedor não trocam idéia se ele não quiser. Quando quiser, pode usar os comandos **push**, **pull** e **merge**. O push coloca coisas novas no servidor; o pull puxa coisas novas do servidor, e o merge é necessário quando existem conflitos entre as mudanças no fonte. Mais sobre conflitos em um futuro artigo.

#### Desenvolvedor conectado

É o cara que quer sempre atualizar todas as modificações que ele faz imediatamente colocadas no servidor. Tudo bem. É só trabalhar no modo Source Safe (ou Subversion) com o comando **checkout**:

    
    bzr checkout bzr://servidor/projeto projeto\projeto

Um checkout funciona como o _branch, _só que faz um _bind _(ligação) com o servidor. O que quer dizer que qualquer _commit _feito localmente irá parar imediatamente também no servidor, a não ser que seja usado o parâmetro --local.

    
    bzr commit -m "Eu sei que isso vai ser feito aqui e no servidor"
    bzr commit --local -m "Apenas umas mudancinhas; depois jogo no servidor"

O modo _checkout _permite usar o comando **update** para ver se existem mudanças entre a máquina local e o servidor, diferente do modo _standalone, _onde o _update _apenas compara com o _branch _local e o diretório de trabalho.

    
    bzr update

#### Desenvolvedor polivalente

Como eu havia dito, uma coisa não exclui outra. Se você está trabalhando em um _branch _e deseja se conectar ao servidor para atualizar mudanças, basta usar o comando **bind.**

    
    bzr bind bzr://servidor/projeto projeto\projeto

O _branch _começará a trabalhar como um _checkout_.

O contrário, que é fazer um _checkout _ficar desconectado é conseguido pelo comando **unbind**.

    
    bzr unbind

Todos os novos _commits _serão feitos apenas localmente.

#### Trabalhando na sua máquina

Esses esquemas de conectado e desconectado podem ser usados no modo cliente x servidor ou tudo em uma máquina só. Por exemplo, uma série de mudanças em um projeto pode ser feito em um outro _branch _desconectado:

    
    bzr branch projeto novo-branch

Os _commits _de "novo-branch" não serão replicados para o _branch _"projeto".

No entanto, se é uma série de mudanças que devem ser colocadas imediatamente no _branch _principal, pode-se usar **checkout**.

    
    bzr checkout projeto novo-branch

Existem diversas outras formas de usar o Bazaar, e isso está sob o controle do desenvolvedor. O importante para quem está migrando é saber definir alguns padrões (onde é o servidor principal, ramificação dos projetos) e o resto é só programar, exatamente como antes.

<blockquote>_Para os "SourceSafers" de plantão: o Bazaar funciona como o Subversion sem locks, ou seja, todo mundo pode alterar qualquer fonte a qualquer hora. Isso significa que para começar a trabalhar basta começar a programar. Os commits podem ser feitos a qualquer hora, resolvidos os poucos conflitos que podem ocorrer se existirem pessoas mexendo nos mesmos fontes que você. _</blockquote>
