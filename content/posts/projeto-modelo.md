---
categories:
- blog
date: '2008-07-08'
tags: null
title: Projeto-modelo
---

É muito difícil construir um modelo de pastas que sirva para a maioria dos projetos que tivermos que colocar na fôrma. Ainda mais se esses projetos tiverem que futuramente fazer parte da mesma ramificação. Foi pensando em várias coisas que chegamos a uma versão beta que pode ajudar aqueles que ficam pensando durantes dias antes mesmo de colocar as mãos no código.

Antes de começar a pensar em como as pastas estarão alinhadas, é importante saber como funcionará o controle de código do seu projeto. Como eu disse sobre o Bazaar, a estrutura inicial permitirá a junção de dois projetos distintos se estes compartilharem do mesmo commit no começo de suas vidas.

Portanto, trate de iniciar a estruturação em um projeto-modelo que já contenha pelo menos um commit: o das pastas vazias já estruturadas.

    bzr init _Template
    cd _Template
    bzr mkdir Docs
    bzr mkdir Interface
    bzr ...
    bzr ci -m "Projeto-modelo. Herde desse projeto sua estrutura inicial"

Estruturação proposta:

 - Build. Essa pasta contém tudo que é necessário para compilar e testar o projeto como um todo. Idealmente a execução da batch build.bat deve executar todo o processo. Após a compilação, é de competência dos componentes na subpasta Tests fazer os testes básicos do projeto para se certificar de que tudo está funcionando como deveria.

 - Common. Aqui devem ser colocados aqueles includes que servem para vários pontos do projeto. Está exemplificado pelo arquivo de versão (Version.h), pois todos os arquivos devem referenciar uma única versão do produto. Podem existir Outras definições básicas, como nome do produto, dos arquivos, etc. É aqui que são gravadas as interfaces que permitem dependência circular entre os componentes (e.g. Interface de componentes COM).

 - Docs. Aqui deve ser colocada toda a documentação que diz respeito ao projeto. A organização interna ainda não foi definida, pois imagina-se ser possível usar diversas fontes, como doxygen, casos de uso, bugs, arquivos de projeto e UML. Foi exemplificado com o arquivo todo.txt e changes.txt, que deve ter sempre a lista de coisas a fazer e a lista de coisas já feitas, respectivamente, tendo, portanto, que ser sempre atualizados.

 - Drivers. Essa é a parte onde ficam todos os componentes que rodam em kernel mode. Por se tratar de um domínio específico e muitas vezes compartilhar código-fonte de maneira não-heterodoxa (e.g. sem uso de LIBs), faz sentido existir uma pasta que agrupe esses elementos. Dentro da pasta existem subpastas para cada driver, exemplificados em Driver1 e Driver2.

 - Install. Todas as coisas relacionadas com instalação, desinstalação e atualização do software deve vir nessa pasta. Foi reservada uma subpasta para cada item, não sendo obrigatória sua divisão. Também existe uma pasta de DLLs, onde possivelmente existam telas personalizadas e biblioteca de uso comum pelos instaladores (o desinstalador conversa com o instalador e assim por diante).

 - Interface. Todas as telas de um programa devem ser colocadas nessa pasta. Essa é uma divisão que deve ser seguida conceitualmente. Por exemplo, se existir um gerenciador de alguma coisa no produto, as telas do gerenciador e o comportamento da interface ficam nessa pasta, mas o comportamento intrínseco do sistema (regras de negócio) devem ficar em Libraries. Para exemplificar o uso, foram criadas as Interface1 e Interface2.

 - Libraries. O ponto central do projeto, deve conter o código mais importante. Imagine a pasta Libraries como a inteligência de um projeto, de onde todos os outros componentes se utilizam para que a lógica do software seja sempre a mesma. As outras partes do projeto lidam com aspectos técnicos, enquanto o Libraries contém as regras abstratas de funcionamento. Opcionalmente ela pode ser estática ou dinâmica, caso onde foi criada a subpasta DLLs. Porém, elas devem ser divididas por função em bibliotecas estáticas, como foi exemplificado em Library1 e Library2.

 - Resources. A origem de todas as imagens, sons, cursores, etc de um projeto devem residir primeiramente na pasta Resources. A divisão interna desse item fica a critério do designer responsável, pois ele pode dividir tanto por função (Install, Interface) quanto por elementos (Images, Sounds).

 - Services. Além dos drivers e das interfaces alguns projetos necessitam de processos "invisíveis" que devem fazer algo no sistema. Isso inclui serviços do Windows, GINAs, componentes COM e coisas do gênero. Devem ser colocados nessa pasta e distribuídos como no exemplo, em Service1 e Service2.

 - Tools. Além dos componentes essenciais para o funcionamento do software também existem aqueles componentes que fornecem mais poder ao usuário, ao pessoal do suporte ou ao próprio time de desenvolvimento. Essas são as ferramentas de suporte que permitem a fácil identificação de erros no programa ou a configuração mais avançada de um item que a Interface não cobre. Adicionalmente foi colocada a subpasta Develop, que deve conter ferramentas usadas estritamente durante a fase de desenvolvimento.

Todos os componentes que disponibilizarem unidades de testes devem conter uma pasta Tests dentro de si. Essa padronização permite facilmente a localização de testes internos aos componentes. Além disso, os arquivos executáveis de testes devem sempre terminar seu nome com Test, o que permite a automatização do processo de teste durante o build.

Acredito que este esboço esteja muito bom. É o modelo inicial que estou utilizando nos projetos da empresa e de casa.