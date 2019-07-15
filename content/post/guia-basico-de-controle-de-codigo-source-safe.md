---
date: "2007-09-12"
title: Guia básico de controle de código (Source Safe)
categories: [ "code" ]
---
O primeiro passo para se passar no [Teste do Joel](http://brazil.joelonsoftware.com/Articles/TheJoelTest.html) é possuir algum tipo de controle de código. E ele está mais do que certo. Não existe nada mais frustrante do que não ter exatamente o código-fonte da versão que está rodando no cliente ou não saber o que mudou desde que a versão foi entregue. Esse tipo de coisa pode acabar com uma empresa ou fazer com que ela fique muito mal vista no mercado.

Porém, independente do mercado, existe um bom motivo para o desenvolvedor possuir algum tipo de controle de código: **controle**. Se você ou sua equipe não conseguem corrigir todos os bugs, pelo menos saberão o que já foi feito. Se você achou um bug que não existia antes da versão 10, o histórico das mudanças entre a versão estável 9 e a versão não-tão-estável 10 vai te dar uma pista muito boa de onde o problema pode ter sido gerado. Visto dessa forma, não importa muito o tamanho da equipe ou da organização. O importante de um bom código é que suas mudanças estejam sempre registradas, visíveis e disponíveis a qualquer um.

#### Tipos de controle de código

Um controle de código para uma pessoa só não precisa ser nada muito sofisticado, sendo que um amontoado de ZIPs pode dar conta do recado. Porém, a partir do momento em que o número de desenvolvedores aumenta para dois ou mais, aí o controle baseado em ZIPs começa a ruir, e é necessário usar uma ferramenta mais apropriada. Existem algumas opções, que vai do gosto e necessidades de cada um:

	
  * [Visual Source Safe](http://msdn.microsoft.com/ssafe/) ou **VSS**: não é gratuito nem robusto o suficiente para agüentar toneladas de código-fonte, mas vem junto do Visual Studio e pode ser apropriado para empresas de porte pequeno ou médio (e empresas de um programador só).

	
  * [Concurrent Version System](http://www.nongnu.org/cvs/) ou **CVS**: é um sistema fonte aberto, gratuito e robusto. Suficiente para agüentar toneladas de código-fonte e equipes de vários andares. Atualmente está sendo substituído gradualmente pelo

	
  * [Subversion](http://subversion.tigris.org/) ou **SVN**: é um substituto moderno do antigo CVS; igualmente gratuito e poderoso, está rapidamente se tornando a opção predominante.

Vou explicar aqui os principais passos para começar a utilizar um controle de código usando como exemplo o Source Safe versão 2005 que, apesar de não ser gratuito, é muito usado em empresas que programam para Windows e já utilizam o Visual Studio há muito tempo.

#### Primeiro passo: crie uma base de dados

Antes de qualquer coisa é necessário criar uma base de dados onde estarão os fontes. Para isso a primeira execução do programa irá exibir um assistente que irá guiá-lo pelos poucos e simples passos para a criação de uma nova base.

[![VSS criando base](http://i.imgur.com/OFRTnSq.png)](/images/vss-create.png)

O processo é bem simples, baseado em _Next, Next_, até que você chega em momento de decisão, onde deve escolher qual dos dois métodos de controle de fonte irá utilizar:

[![Controle de fonte](http://i.imgur.com/hWNkxvs.png)](/images/vss-control.png)

	
  * **Lock-Modify-Unlock Model**. O modelo clássico do Source Safe, permite que apenas um programador altere um fonte de cada vez. Se você é novo nesse negócio de controle de fonte, recomendo essa opção, que é a mais indolor. Em equipes pequenas costuma funcionar. E esse é o modelo que iremos utilizar aqui.

	
  * **Copy-Modify-Merge Model**. Esse novo modelo segue o princípio do CVS e do Subversion. Nele todos podem alterar ao mesmo tempo qualquer código-fonte. Porém, na hora de subir as modificações de volta para a base é necessário um passo intermediário conhecido como _merge._ É onde são resolvidos conflitos, caso algum desenvolvedor tenha feito modificações no mesmo local que você. Geralmente é escolhida uma ou mais pessoas para gerenciar essa parte do processo. Esse modelo tem funcionado bastante em projetos de fonte aberto e de empresas grandes.

#### Segundo passo: compartilhe a base

Agora que a base está criada, o próximo passo é torná-la disponível a todos. A maneira mais fácil de fazer isso é criando um compartilhamento na rede (de preferência oculto) e divulgando às pessoas interessadas. É claro que você, como bom administrador, irá ter que criar os usuários que irão acessar a base.

Após esse processo de integração, os usuários podem começar a usar o Source Safe através da primeira opção do início do assistente (Database Selection).

#### Terceiro passo: defina seu diretório de trabalho

Antes de começar a mexer nos fontes, o Source Safe pede que você defina um diretório raiz onde começa a ramificação de pastas dos seus fontes. Isso pode ser feito pela opção File, Set Working Folder (Ctrl + D). A partir daí, cada pasta é chamada de projeto (_project_) no Source Safe. Para criar novos projetos/pastas, use a opção "File, Create Project". Para adicionar novos arquivos, "File, Add Files". Cada usuário pode definir seu próprio diretório de trabalho por máquina, mas geralmente é uma boa idéia mantê-los todos utilizando a mesma pasta.

[![Working folder](http://i.imgur.com/HIjMA3x.png)](/images/vss-working-folder.png)

#### Quarto passo: check-IN, check-OUT

Após adicionar os arquivos do projeto, é possível fazer modificações usando a opção _check-out_. O _check-out_ quer dizer que os fontes **saem (OUT)** da base e são copiados com direito de escrita para seu disco local. Após feitas as modificações, usa-se a opção _check-in_ para subir as modificações para o banco. O _check-in_ quer dizer que as modificações feitas no disco local **entram (IN)** na base. Cada operação feita com esses dois passos é armazenada no histórico do Source Safe, e podem ser utilizadas para voltar versões antigas, comparar versões antigas novas, etc.

[![Check-out](http://i.imgur.com/TSk1c4K.png)](/images/vss-check-out.png)

[![Check-in](http://i.imgur.com/OpCfsOA.png)](/images/vss-check-in.png)

#### Quinto passo: crie seus labels

Quando todos os fontes que subirem constituirem uma **alteração madura**, compilável, testada pelo desenvolvedor e pronta para ser repassada para os testadores, deve-se criar um rótulo, ou _label_, para que futuramente essa versão possa ser facilmente identificada entre os milhões de modificações de fonte que sua equipe irá fazer ao longo do tempo. Se essa versão se tornar uma "entregável", pode-se utilizar o rótulo para obter exatamente a versão entregue a qualquer momento, independente de quantas modificações terem sido feitas depois. Essa marcação de fontes pode ser muito útil na ocorrência de incêndios, e todos sabemos que eles ocorrem com mais freqüência do que gostaríamos. Por isso é importante estar preparado.

[![Label](http://i.imgur.com/fuMv3RC.png)](/images/vss-label.png)

[![History](http://i.imgur.com/h7YOAOS.png)](/images/vss-history.png)

#### Sexto passo: valorize seu controle de fonte!

Se você chegou até aqui, quer dizer que está realmente interessado em controlar seus fontes. Parabéns! O controle de fontes vem com algumas vantagens. Vamos supor que já exista uma versão estável no Source Safe e você precisa fazer alguma correção/teste como prova de conceito. Esse tipo de fonte normalmente seria descartável, mas agora que você possui uma ferramenta de controle de fonte funcionando, isso não é necessário.

Se é necessário desenvolver uma prova de conceito, pode-se optar por criar uma ramificação do fonte, ou _branch_. Essa opção cria um novo projeto no Source Safe com fontes existentes, mantém o histórico de modificações, mas gera uma nova linha de vida do fonte. Qualquer modificação feita em um _branch_ fica nesse _branch_, seja o principal ou secundário. É possível também no futuro juntar dois _branchs_.

Agora, se a modificação é um simples teste durante a depuração, pode ser feito o _check-out_ para modificações temporárias. Se mais tarde for decidido que as modificações não serão efetuadas na base, basta executar a opção _undo check-out_, que volta o fonte da base para o disco local e mantém a versão intacta. Use essa opção com cuidado, pois quaisquer modificações no disco local serão perdidas.

#### Sétimo e último passo (ufa!): automatize o processo de build

Agora que os fontes estão vivendo tranqüilamente no controle de fontes, é possível executar _builds_ automatizados de tempos em tempos. Isso garante a estabilidade do seu projeto, pois junto dos _builds_ é possível fazer testes, tanto da compilação em si quanto depois de compilado.

O Source Safe possui uma ferramenta em linha de comando que faz as mesmas operações que a versão gráfica, além de possuir uma série de interfaces COM que podem ser usadas para interagir com o controle de fontes através de _scripts_. Além de outras ferramentas de automação de _builds_ que podem ser integradas, como o [NAnt](http://nant.sourceforge.net/) e o [CruiseControl](http://cruisecontrol.sourceforge.net/).

O resumo da ópera é: cuide bem dos seus fontes. Muito trabalho, tempo e dinheiro são despendidos com desenvolvimento. Não cuidar do resultado de tudo isso é como botar fogo no estoque de uma fábrica.
