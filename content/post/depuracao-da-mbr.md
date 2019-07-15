---
date: "2008-03-24"
title: Depuração da MBR
categories: [ "code" ]
---
Dando continuidade a um artigo beeeem antigo sobre [depuração da BIOS usando SoftIce](http://www.caloni.com.br/debug-da-bios-com-o-softice-16-bits), como já vimos, podemos igualmente depurar a MBR após a chamada da INT13. Porém, devo atentar para o fato que, em algumas VMs, e sob determinadas condições do tempo e quantidade de [ectoplasma](http://pt.wikipedia.org/wiki/Ectoplasma_%28parapsicologia%29) na atmosfera, é possível que a máquina trave após o _hot boot_ iniciado pelo depurador. Isso provavelmente tem cura usando o espaço de endereçamento alto da memória com a ajuda de aplicativos como LH e UMB.

Porém, estou aqui para contar uma nova forma de depurar essa partezinha do código que pode se tornar um tormento se você só se basear em _tracing_ na tela (ou na COM1): usando o aplicativo **debug** do DOS.

#### Debug.(exe|com)

O debug é um programa extremamente antigo, criado antes mesmo do MS-DOS pertencer à Microsoft e do Windows Vista ter sido criado. Como todo sistema operacional, é essencial que exista um programa para verificar problemas em outros programas. Essa foi a "motivação" para a criação do Debug.

Com o passar do tempo e com a evolução dos depuradores modernos, o uso do debug foi diminuindo até a chegada dos 32 bits, quando daí ele parou de vez de ser usado. Com um conjunto limitado de instruções, a versão MS é incapaz de decodificar o _assembly_ de 32 bits, mostrar os registradores extendidos e de depurar em modo protegido.

O [FreeDOS](http://www.freedos.org/) é um projeto de fonte aberto que procura criar uma réplica do sistema MS-DOS, com todos seus aplicativos (e um pouco mais). Entre eles, podemos encontrar o [Debug refeito e melhorado](http://www.freedos.org/cgi-bin/lsm.cgi?mode=lsm&lsm=base/debug.lsm). A versão com código-fonte possui suporte às instruções "novas" dos processadores 32 e suporta acesso à memória extendida, modo protegido e melhorias na "interface com o usuário" (como repetição de comandos automática, mudança no valor dos registradores em uma linha, etc). Enfim, nada mau.

É por isso que comecei a utilizá-lo e é nele que me baseio o tutorial logo abaixo.

#### Como depurar a MBR (finalmente!)

Para conseguirmos essa proeza é necessário reiniciarmos a máquina com algum sistema 16 bits, de preferência que caiba em um disquete. Junto com ele basta uma cópia do debug.com. Após reiniciarmos e aparecer o prompt de comando, podemos chamar o depurador e começar a diversão:

![Debug](http://i.imgur.com/YlSOCaO.png)

A MBR fica localizada no primeiro setor do HD ativo (_master_). A BIOS automaticamente procura esse HD e faz a leitura usando a INT13, função da própria BIOS para leitura de disquetes e derivados.

Lembre-se que nem sempre existirá um MS-DOS para usarmos a INT21, tradicionalmente reservada para este sistema operacional. Portanto, se acostume com as "limitações" das funções básicas da BIOS.

O debug.com inicialmente começa a execução em um espaço de memória baixa. Podemos escrever um _assembly_ qualquer nessa memória e começar a executar. Isso é exatamente o que iremos fazer, e a instrução escolhida será a INT13, pois iremos ler o primeiro setor do HD para a memória e começar a executá-lo. Isso é a depuração da MBR.

Para fazer isso, algumas informações são necessárias, e tudo está disponível no sítio muito simpático e agradável de [Ralf Brown](http://www.ctyme.com/rbrown.htm), o cara que enumerou todas as interrupções conhecidas, além de diversas outras coisas.

Como queremos ler um setor do disco, a função da interrupção que devemos chamar é a [AH=02](http://www.ctyme.com/intr/rb-0607.htm):

### DISK - READ SECTOR(S) INTO MEMORY

    
    AH = 02h
    AL = number of sectors to read (must be nonzero)
    CH = low eight bits of cylinder number
    CL = sector number 1-63 (bits 0-5)
    high two bits of cylinder (bits 6-7, hard disk only)
    DH = head number
    DL = drive number (bit 7 set for hard disk)
    ES:BX -> data buffer

Muito bem. Tudo que temos a fazer é preencher os registradores com os valores corretos:

    
    rax 0201 ; função e número de setores (1)
    rcx 0001 ; número do cilindro e do setor (cilindro = 0, setor = 1)
    rdx 0080 ; número da cabeça (0) e do drive (HD = 0, o bit 7 deve estar levantado)
    res 0000 ; segmento em que é executada a MBR
    rbx 7e00 ; offset em que é executada a MBR

#### Por que a MBR deve ser executada em 000:7E00?

Essa é a maneira em que as coisas são. Você certamente poderia usar outro endereço, mas estamos tentando deixar a emulação de um _boot _o mais próximo possível  de um _boot _de verdade. E, tradicionalmente, o endereço de execução da MBR é em 0000:7E00. Para recordar disso, basta lembrar que o tamanho de um setor é de 0x200 bytes, e que dessa forma a MBR vai parar bem no final do endereçamento baixo (apenas _offset_).

Essa organização é diferente do endereço inicial da BIOS, que é por padrão 0xFFFF0.

Após definir corretamente os registradores, tudo que temos que fazer é escrever uma chamada à INT13 no endereço atual e executar. O conteúdo inicial do disco será escrito no endereço de memória 0000:7E00. Após isso trocamos o IP atual para esse endereço e começamos a depurar a MBR, como se estivéssemos logo após o _boot_ da máquina.

![debug2.png](http://i.imgur.com/0H8qWQw.png)

#### Depurando a BIOS

Além da MBR, muitas vezes é preciso depurar a própria BIOS para descobrir o que está acontecendo. Nesse caso, tudo que precisamos fazer é colocar o ponteiro de próxima instrução para a região de memória 0xFFFF0, que traduzido para segmento/_offset_ fica f000:fff0 (mais explicações sobre isso talvez em um futuro artigo).

    
    -rcs f000
    -rip fff0
    -t
