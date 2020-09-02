---
date: "2019-09-03"
tags: [ "code", "draft",  ]
title: "Do Bit para o Código"
---
Olá. Esta é uma viagem para dentro do computador. Como funciona um computador? Você sabe? Pois é, nem eu. Mas vamos explorar alguns pontos onde nossa vã metafísica mal encosta na singularidade que é uma arquitetura Von Neumann.

Em primeiro lugar, um bit. O que é um bit? Um bit nada mais é que um dado que se traduz em uma informação com dois, e apenas dois, valores possíveis: ligado ou desligado. Em eletrônica um bit precisa ser extraído de nosso mundo analógico, e quando eu digo analógico eu digo físico, onde existem átomos, prótons e elétrons, mas não existem bits, ou se existem, eles são muito complicados no momento.

Por enquanto, a esmagadora maioria dos computadores utiliza a frequência de uma onda para representar um bit, e dizer se ele está ligado ou desligado. Um filtro de onda consegue detectar se a frequência está alta ou baixa, sendo que alta e baixa também é uma interpretação arbitrária. É estipulado uma determinada frequência e através dela o filtro sensibiliza para o mundo digital se no momento o fio condutor desta frequência está acima ou abaixo dessa frequência, o que para nós, humanos, irá significar se o bit está ligado ou desligado.

Note que tanto faz a maneira com que você traduz a frequência, desde que haja apenas dois valor possíveis, condição sine qua non para definir um bit. Você pode interpretar uma frequência acima do nível estabelecido como ligado ou desligado, mas a partir dessa definição a frequência oposta, abaixo desse nível, deve ser o oposto do que foi definido, para assim termos o ligado/desligado (ou desligado/ligado).






A onda (mais uma intepretação da realidade) gerada pela frequência do sinal elétrico, então, é dividida em dois espaços, delimitados pelo filtro, que funciona como um filtro de linha: apenas a partir de um certo valor da onda ele deixa passar os elétrons, que irão definir do outro lado se o bit está ligado ou desligado.

Isso não quer dizer que o bit desligado (ou ligado, depende de como você definir) não contém eletricidade correndo antes do filtro, apenas que seu valor está abaixo do estabelecido para contar como ligado (ou desligado).

A partir deste ponto podemos trabalhar com o mundo digital. Limpamos as "imperfeições" do mundo físico e transformamos elétrons esquivos em apenas dois valores possíveis: 0 e 1.

Conseguindo usar e armazenar bits, a matemática fica muito mais simples e intuitiva para seres humanos, que só precisam trabalhar com uma base numérica de 2 valores em vez de 10. As mãos dos computadores possuem apenas um dedo cada, somando dois no total.

Como a base é dois convencionamos a dar nomes para as potências de 2 para conseguirmos trabalhar com valores maiores que 0 e 1. 2 elevado a 8, por exemplo, chamamos de byte, embora não no mundo todo, isso também pode mudar de interpretação, dependendo da arquitetura. Porém, na grande maioria do mundo, um byte serão 8 bits, cada um pondendo valer 0 ou 1, e juntando todos, podemos representar os valores de 0 a 255, pois 2 elevado a 8 são 256 combinações (e devemos incluir o zero).



A partir daí não existe muita mágica, pois juntando bytes podemos ter kilobytes (1024 bytes), dos kilobytes podemos ter megabytes, assim por diante até chegarmos no seu "HD de 2 Tera", o que quer dizer 2 terabytes de informação, ou 35184372088832 bits, todos organizados para serem acessados, ou um a um ou em blocos. O que for mais conveniente para a arquitetura.

Como acessamos esses bits? Bom, informação gera informação na tecnologia da informação. Precisamos dizer, usando bits, quais bits queremos obter do seu "HD de 2 Tera". O primeiro? O segundo? O vigésimo-quinto? O de número 35184372088832?

Para conseguir acessar precisamos de acesso, e esse acesso precisa conseguir deixar eu falar qual bit/byte que eu quero, ou seja, permitir que eu consiga passar esse valor (primeiro, segundo, etc). Onde está esse bit/byte nós chamamos de endereço, e para passar o endereço de um bit/byte para um HD usamos algo chamado barramento, que é como uma rodovia pode onde passam no máximo X bits.




Porém, como vimos, dependendo do número de bits há um limite da quantidade de valores que podemos representar, e isso irá limitar o nosso acesso aos bits que queremos do "HD de 2 Tera".



Bom, já deu pra ver que 64 bits é suficiente para pegar muitos e muitos bits. O problema é que endereçar toda essa gente custa tempo, pois cada bit precisa ser interpretado para daí o HD conseguir chegar no bit que ele precisa para daí devolver o seu bit. Imagine que para acessar 1 bit você precisa enviar 64?

Como esse modelo é impraticável criamos uma contraparte: em vez de apenas retornar 1 bit vamos diminuir a resolução e entregar já o bloco mais próximo de bits. Você manda 32 bits, por exemplo, e eu te mando uns 16 bytes, o que dá 65536 bits pela tabelinha acima. É um ótimo negócio, pois enviar bits e bytes para lá e para cá é muito mais barato, computacionalmente falando, do que ter que fazer uma busca de 1 bit em uma imensidão de bits. Essa quantidade de bits que o computador trabalha sempre que pedimos chamamos de palavra (word), o que faz muito sentido: estamos conversando com o computador, e ele responde com palavras geralmente, não com letras. Quem diabos responde um "olá" com "b"?

Já aprendemos muita coisa. Sabemos que os elétrons de um fio condutor pode ser dividido em frequências alta e baixa da onda e que essa divisão transforma o mundo analógico/físico em mundo digital, com bits valendo apenas 0 e 1. Sabemos que 1 bit sozinho não faz muita coisa, então começamos a ajuntá-los com nomes como byte, kilobyte e "HD de 2 Tera". Sabemos que para conseguir pegar os nossos bits de volta o computador pede bits que dizem onde eles estão, o que chamamos de endereço. E como mandar 32 bits para obter apenas 1 é muito trabalho de busca à toa, sabemos que o computador nos entrega de volta uma palavra, que é um naco de 8, 16, 32 bits ou valores maiores. É assim que nos comunicamos com os computadores: com palavras (words).

Então, agora, o código abaixo não deve ser o menor mistério para nós:


O programa acima verifica se a variável argc contém o valor 2. Argc é um int, o que quer dizer que na minha arquitetura são 4 bytes, ou 32 bits. Se esses 32 bits estão configurados com 0s e 1s de tal maneira que a soma de todos totalizam o valor 2, então meu código entrará dentro do primeiro if. Se não, então o código cairá no else e enviará os caracteres "How to use..." blá blá blá para a saída padrão através da chamada da função da libc puts. Esses caracteres também são formados por bits. Cada caractere possui 8 bits. E estão configurados de tal forma que darão um valor de 0 a 255 que será interpretado de tal maneira: o nth elemento da entrada de uma tabela de caracteres. Essa tabela se chama tabela ascii, e contém os números 0 a 9, as letras de a até z (e maiúculas, A até Z), alguns sinais, etc. Essa é uma nova forma de interpretar os números que conseguimos somando os bits, e só funciona dessa forma porque a linguagem C está especificada dessa maneira.



Essas letras representam o alfabeto romano, usado por boa parte do Ocidente, mas para o computador isso é apenas um comando que depois de passar por várias camadas de interpretação, incluindo o sistema operacional (que controla bits e bytes acima do computador), irá acender determinados leds em seu monitor para que o ser humano que estiver olhando para ele irá entender que aquilo é a letra H, por exemplo. No caso de H, imagine que ele está acendendo uma série de leds da cor da letra que está vendo exatamente na posição que você está olhando, enquanto em volta está acendendo a cor do fundo onde essa letra está sendo "impressa". Se pudéssemos enxergar com um zoom, poderíamos ver cada um desses leds acesos, mas perderíamos a noção de qual letra no final está sendo desenhada. Na época de monitores de tubo e preto e branco era até possível ver os dois, mas hoje em dia o celular mais vagabundo exibe milhões e milhões de leds em sua cara.



Poderíamos continuar explicando o que é esse FILE e como ele se relaciona com o seu "HD de 2 Tera" para abrir apenas os bits que dizem respeito ao nome do arquivo, que é uma entrada em outra tabela de nomes de arquivos que ele encontra perguntando para o sistema operacional e assim lendo a posição correta dos bits que você precisa e assim por diante até que sua mente estrale e você entenda a miríade de abstrações e interpretações da realidade com que estamos lidando. Daí você veria que eu sou que nem você, dos bits e bytes, dos bauds e sockets, e que me surpreendo a cada dia em como mais e mais interpretações são possíveis de serem criadas a partir de um mundo digital inteiro construído a partir de nosso mundo físico. Bem-vindo ao meu mundo, ao nosso mundo, programador =)
