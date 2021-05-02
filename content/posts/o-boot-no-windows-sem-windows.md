---
date: "2009-08-18"
categories: [ "code", "draft",  ]
title: "O boot no Windows: sem Windows"
---
Desde quando o usuário liga o computador até o momento em que ele vê a barra de tarefas e aqueles fundos lindos de papel de parede existem diversas coisas sendo feitas por debaixo do pano. Essa série de artigos irá explicar essas diversas coisas, ou seja, como funciona e quais as fases do boot de uma máquina que possui Windows instalado (plataforma NT).

O que esses artigos não vão fazer muito bem é explicar o lado do kernel mode funcionando, até porque temos artigos melhores explicando esse ponto de vista. Essa é uma abordagem mais "high level", apesar de "low enough". No entanto, espero que seja divertido. É esse o mais importante requisito em qualquer aprendizado, certo? Let's go!

Tudo começa no hardware, que recebe um lampejo de energia que o põe em funcionamento ("levanta-te e anda!"). Isso faz com que um pequeno pedaço de software comece a rodar. Esse pedaço inicial de código é chamado de firmware, que é um meio termo entre hardware e software.

O firmware fica gravado na placa-mãe e normalmente nós ouvimos falar dele pelo nome de BIOS, Basic Input Output System (Sistema Básico de Entrada e Saída). É nele que estão gravadas as rotinas mais básicas para fazer o hardware mais básico funcionar: CPU, memória, vídeo e teclado.

Quando o computador é ligado, o código da BIOS realiza duas operações vitais antes de continuar:

	
  1. Ver se todos os componentes de hardware estão bem;

	
  2. Ver quem é o dispositivo que inicia o sistema operacional.

Esse segundo item é o que veremos agora.

Dependendo do computador, podemos iniciá-lo por um disco rígido (HD), por um CD-ROM, por um PenDrive USB e até pela rede. Isso está subordinado ao firmware da máquina, pois é ele que comanda, até segunda ordem, todo o hardware acoplado ao sistema.

Vamos supor que um HD foi configurado para ser o inicializador do sistema operacional. Então será lido um pequeno espaço de 512 bytes, mais conhecido como setor, bem no início desse HD. Esse setor inicial possui código de inicialização (chamado de bootstrapping). Por isso, ele é colocado na memória inicial da máquina e executado. O lugar onde ele fica é fixo e conhecido por todos (lembre-se que estamos rodando em modo real!): 0x7C00.

Agora o próximo passo é com esse setor inicial do disco, que chamamos de MBR: Master Boot Record (ou Registro de Boot Mestre, em tradução livre).  Ele contém código 16 bits que não pode depender de runtime nenhuma e faz o que quiser com a memória. Também possui no seu final uma tabela de quatro entradas de partições; é nessa tabela que deve estar a partição ativa, onde está o sistema operacional.

Uma MBR padrão procura por essa partição e lê seu primeiro setor, fazendo um processo bem parecido com o que a BIOS faz inicialmente: carrega na memória o primeiro setor da partição e executa.

Vamos supor que você tenha algum Windows moderno na partição ativa. A MBR irá carregar o primeiro pedaço de código desse sistema operacional moderno, que, até então, estará rodando em modo real desprotegido como o bom e velho MS-DOS.

(Note que, mesmo que se trate de uma MBR escrita por terceiros, se ela se comportar como manda o figurino, irá carregar o primeiro setor da partição ativa descrita na tabela de partições. Isso é o que faz com que MBRs escritas pelo pessoal do Linux (e.g. Lilo) consiga fazer o boot de uma partição Microsoft.)

Agora chegamos em todos os passos iniciais realizados antes de entrar em cena o S.O.:

	
  1. O firmware da placa-mãe, conhecida como BIOS, verifica se o hardware básico está funcionando;

	
  2. Em seguida, o mesmo código procura pelo dispositivo iniciável que irá dar início ao processo de boot;

	
  3. Se for um HD, então o primeiro setor físico desse HD será carregado em memória e executado;

	
  4. Esse primeiro setor se chama MBR e contém uma tabela com até quatro entradas de partições no disco;

	
  5. O código da MBR procura pela partição ativa onde deve estar o sistema operacional;

	
  6. Assim como a BIOS, a MBR carrega na memória o primeiro setor da partição ativa e executa;

	
  7. A partir daí temos o código de um possível sistema operacional rodando.

Todos os componentes principais desse boot podem ser visualizados de uma forma bem macro na figura abaixo.

Alguns detalhes sórdidos que podem fazer alguma diferença para você, desenvolvedor de sistemas operacionais, um dia desses:

	
  * Os setores de que estamos falando (MBR, partição ativa) normalmente devem terminar com uma assinatura de dois bytes (0x55 0xAA), o que "garante" que o código contido nesse setor é válido e pode ser executado.

	
  * No caso do loader do Windows (pré-Vista), existia um arquivo no diretório-raiz da partição ativa chamado boot.ini que continha uma lista de possíveis modos de inicializar o sistema operacional, inclusive com múltiplas versões do Windows, cada um localizado em uma partição/pasta distinta (e.g., multiboot com Windows 98 e XP).

	
  * O limite de quatro partições da MBR pode ser aumentado com o uso de partições estendidas; as partições estendidas apontam para um bloco de setores no HD que inicia com um setor que contém outra tabela de partições exatamente onde fica a tabela da MBR, também com quatro entradas.

	
  * O endereçamento da localização das partições na MBR pode ser feito de duas maneiras distintas: por CHS ou por LBA. A versão CHS é bem antiga, mas ainda usada, e especifica uma localização no HD através de um posicionamento físico de três dimensões, com cilindro/trilha (C - Cylinder), cabeça (H - Head) e setor (S - Sector). Sim, isso é bem _old-fashionable_. Também existe o LBA (Logical Block Addressing), que é uma forma lógica de endereçar setores no disco, através de deslocamentos (_offsets_).

Para detectar problemas de hardware, a BIOS pode ajudar com seus beeps significativos. Isso aparentemente parece ser o fim da picada, mas não é. O DQ sabe muito bem que podemos ter problemas no hardware que exigem análises mais sofisticadas (como comprimento de onda dos sinais).

Se for detectar algum problema no sistema de boot baseado em MBR, então você tem dois caminhos:

	
  * Usar o SoftICE 16 bits e depurar o carregamento da MBR pela BIOS

	
  * Usar o Debug 16 bits do MS-DOS (ou similar) e depurar diretamente o código de boot da MBR, reproduzindo os passos anteriores da BIOS.

Se o problema for durante o carregamento do próprio sistema operacional, as mensagens de erro do loader são significativas. No entanto, pode-se usar o Debug mais uma vez e depurar essa parte, logo antes, é claro, do sistema entrar em modo protegido de 32 bits, o que daí já é outra história (que pretendo contar em breve).

	
  * Artigo sobre o boot no Linux

