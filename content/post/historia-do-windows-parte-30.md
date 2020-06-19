---
categories: [ "code" ]
date: "2007-08-03"
tags: [ "draft",  ]
title: "História do Windows - parte 3.0"
---
Em 22 de maio de 1990 a versão 3.0 do Windows foi lançada. Foi melhorado o gerenciador de programas e o sistema de ícones, além de um novo gerenciador de arquivos e suporte a 16 cores. Entre as mudanças internas podemos citar a velocidade e a confiabilidade. Como a partir dessa versão apareceram muitos desenvolvedores que passaram a suportar a plataforma, o número de programas disponíveis aumentou, o que conseqüentemente fez com que as vendas alavancassem. Três milhões de cópias foram vendidas apenas no primeiro ano, e assim o Windows se tornou padrão nos computadores domésticos. Quando a versão 3.1 foi lançada, em 6 de abril de 1992, mais três milhões de cópias foram vendidos em apenas dois meses.

As fontes TrueType foram adicionadas, junto de novas capacidades multimídia. Outro grande avanço foi na área de comunicação entre aplicativos com a implementação da tecnologia OLE (Object Linking and Embedding), que permitiu documentos de diferentes fabricantes serem intercambiados.

Em novembro de 1993 foi lançada a primeira versão que integrou o Windows e a rede de trabalho, o Windows for Workgroups 3.1. O suporte a compartilhamento de arquivos e impressoras apareceu a partir daí. Duas aplicações novas também surgiram: Microsoft Mail, cliente de mail para uso em redes, e Schedule+, uma agenda de trabalho.

E, finalmente, agora já é hora de conversarmos sobre...

Programar interfaces naquela época não era bem o "clicar e arrastar" de hoje em dia. Eram necessários profundos conhecimentos sobre como o sistema operacional se relacionava com o seu programa e vice-versa. Hoje em dia é possível ainda programar como antigamente, já que toda a estrutura continua a mesma. Porém, é algo extremamente contraprodutivo de se fazer com as IDEs modernas que existem e suas barras de controles pré-fabricados e código automático. Faremos da forma mais rústica para entender como as coisas funcionam por baixo dos panos, o que por si só será extremamente produtivo para o nosso conhecimento.

Antes de ser criada uma janela, é necessário registrar uma classe de janela no sistema, cuja relação com uma janela é mais ou menos a mesma entre classe e objeto no paradigma de orientação a objetos. Você primeiro define uma classe para sua janela e posteriormente pode criar inúmeras janelas a partir da mesma classe.


Quando você define uma classe e a registra está dizendo para o sistema qual será sua função de janela, i. e., qual será a função responsável por receber as mensagens das janelas criadas.


Uma mensagem é um evento que ocorre relativo à sua janela ou o que está acontecendo ao redor dela no mundo Windows. Por exemplo, as janelas recebem eventos a respeito dos cliques do usuário, redesenho da janela, etc. Quem envia essas mensagens é o próprio Windows, e ele espera uma resposta da sua função de janela. Agora a parte esquisita: quem envia essas mensagens para o Windows é o seu próprio aplicativo!

O aplicativo fica aguardando por eventos em um loop conhecido como loop de mensagens. A função do loop basicamente é chamar a função GetMessage e redirecionar as mensagens obtidas para as respectivas funções de janela.


E aqui está o código completo:


Esse exemplo é bem velho, mas compila e funciona até hoje, depois de passados 17 anos:


O Windows 3.x tinha uma particularidade nefasta: qualquer aplicativo poderia travar o sistema como um todo. Se lembrarmos que o Windows antigamente era multitarefa e não-preemptivo, podemos deduzir que enquanto é executada a função de janela de um aplicativo o sistema aguarda por esse aplicativo indefinidamente. Se o aplicativo trava, ele nunca retorna. Se ele nunca retorna, o sistema fica eternamente esperando pelo retorno da função de janela. Alguns travamentos conseguiam ser resolvidos por interrupção, mas a maioria não. No próximo capítulo da série veremos como os sistemas de 32 bits resolveram esse pequeno problema.

O que o resto do código do Petzold faz? Dê uma olhada na documentação do MSDN. Ela ainda está disponível, já que todos os aplicativos precisam utilizar essas funções, seja diretamente ou através de imensos frameworks de interface com o usuário. E existem pessoas que precisam suportar código-fonte legado.

Já que agora você sabe o que são funções de janela, mensagens e afins, por que não ver tudo isso funcionando? O Microsoft Visual Studio possui uma ferramenta muito útil para isso chamada Spy++ (spyxx.exe). Existem também aplicativos equivalentes (com fonte). Outra ferramenta muito útil, principalmente na hora de desenvolver janelas com controles comuns do Windows, é o Control Spy.

  - Site de Charles Petzold
  - Outros artigos sobre a história do windows

