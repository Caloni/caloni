---
categories: [ "code" ]
date: "2019-12-11"
tags: [ "draft",  ]
title: "Como Funciona o MPTunnel"
---
A ideia por trás de um sistema multipath de rede é fornecer mais de um caminho para o tráfego de pacotes. O objetivo pode ser diminuir a perda de pacotes por causa da instabilidade da rede, mas também isso irá fazer com que o throughput da comunicação seja maior pela diminuição da razão da perda de pacotes, além da melhor rota acabar sendo por onde os pacotes irão chegar primeiro, em uma espécie de seleção natural da arquitetura.

Esta é uma implementação em user space de UDP multipath. Assim como a contraparte em sua versão TCP, você pode estabilizar várias conexões entre o servidor local e o remoto.

MPTCP (MultiPath TCP) é uma boa ideia para tornar a conexão de rede mais robusta, mas apenas funciona em TCP, e em um ambiente multiplataforma não há soluções em kernel mode exceto o ECMP desenvolvido no último Linux, cujos artigos de Jakub Sitnicki explicam os detalhes. E foi através da busca por uma implementação de MPUDP que foi escrita essa ferramenta por greensea, um usuário do GitHub.

                            .---- bridge server 1 ----.
                           /                            \
     Server A --- mpclient ------- bridge server 2 ------- mpserver --- Server B
                           \                            /
                            `---- bridge server 3 ----`

Existem dois servidores Server A e Server B. A conexão de rede entre Server A e Server B é instável (com uma razão alta de perda de pacotes). Dessa forma, nós gostaríamos de estabilizar um túnel multipath entre Server A e Server B, esperando que a conexão entre ambos se torne mais estável (diminua a razão de perda de pacotes). Com o broadcast dos pacotes por vários caminhos o resultado a longo prazo é uma comunicação cuja performance é prioridade.

mpclient é a parte cliente do mptunnel, ele pode rodar no ServerA. Você deve dizer ao mpclient a informação dos servidores bridge. Uma vez que o mpclient é iniciado, ele abre uma porta local UDP para listen e redireciona qualquer pacote de/para os servidores bridge.

mpserver é a parte servidora do mptunnel, ele pode rodar no ServerB. Você deve dizer ao mpserver a informação do Server B. Uma vez que mpserver é iniciado, ele irá redirecionar qualquer pacote de/para o Server B.

Os servidores bridge são simples, eles apenas redirecionam os pacote do mpclient para mpserver, ou pacotes do mpserver para mpclient. Você pode usar nc ou socat para entregar um servidor bridge.

Para a solução ser rodável em Linux, Windows e Mac OS os fontes compilam em um ambiente POSIX mínimo, já disponível nos três SOs, sendo que para Windows este ambiente é o Cygwin.

O resumo para compilar em Linux é instalar o gcc, o make, o git, as dependências, baixar o projeto e compilar. Esses passos devem funcionar em qualquer Linux, mas foi testado em Ubuntu.

    caloni@ubuntu:~$ sudo apt install gcc
    caloni@ubuntu:~$ sudo apt install make
    caloni@ubuntu:~$ sudo apt install git
    caloni@ubuntu:~$ sudo apt install libev-dev
    caloni@ubuntu:~$ git clone https://github.com/bitforgebr/mptunnel && cd mptunnel

O primeiro passo é baixar e instalar o cygwin com os seguintes pacotes adicionais ao padrão: 

 - gcc-core, socat, git, make, libev, libev-devel, libintl-devel.

Em seguida deve-se baixar o repositório do mtunnel e do terminal cygwin executar o build.

    caloni@VMW10PRO64TUNNEL ~
    $ git clone https://github.com/bitforgebr/mptunnel
    Cloning into 'mptunnel'...
    remote: Enumerating objects: 47, done.
    remote: Counting objects: 100% (47/47), done.
    remote: Compressing objects: 100% (29/29), done.
    
    Receiving objects: 100% (394/394), 177.50 KiB | 780.00 KiB/s, done.
    Resolving deltas: 100% (239/239), done.
    
    caloni@VMW10PRO64TUNNEL ~
    $ cd mptunnel/
    
    caloni@VMW10PRO64TUNNEL ~/mptunnel
    $ make
    gcc -MT "rbtree.o rbtree.d" -MM -g -Wall -I/usr/include/libev -O2 rbtree.c > rbtree.d
    gcc -MT "net.o net.d" -MM -g -Wall -I/usr/include/libev -O2 net.c > net.d
    gcc -MT "client.o client.d" -MM -g -Wall -I/usr/include/libev -O2 client.c > client.d
    gcc -MT "udpserver.o udpserver.d" -MM -g -Wall -I/usr/include/libev -O2 udpserver.c > udpserver.d
    gcc -MT "server.o server.d" -MM -g -Wall -I/usr/include/libev -O2 server.c > server.d
    gcc -MT "udpclient.o udpclient.d" -MM -g -Wall -I/usr/include/libev -O2 udpclient.c > udpclient.d
    gcc -MT "mptunnel.o mptunnel.d" -MM -g -Wall -I/usr/include/libev -O2 mptunnel.c > mptunnel.d
    gcc -g -Wall -I/usr/include/libev -O2   -c -o client.o client.c
    gcc -g -Wall -I/usr/include/libev -O2   -c -o net.o net.c
    gcc -g -Wall -I/usr/include/libev -O2   -c -o mptunnel.o mptunnel.c
    gcc -g -Wall -I/usr/include/libev -O2   -c -o rbtree.o rbtree.c
    gcc client.o net.o mptunnel.o rbtree.o  -o mpclient -llibintl -g  -lev -pthread -O2
    gcc server.c mptunnel.o net.o rbtree.o  -o mpserver -llibintl -g  -lev -pthread -O2
    gcc udpclient.c  -o udpclient -g  -lev -pthread -O2
    gcc udpserver.c  -o udpserver -g  -lev -pthread -O2
    ./make-locale.sh: line 3: xgettext: command not found
    ./make-locale.sh: line 12: msgmerge: command not found
    ./make-locale.sh: line 14: msgfmt: command not found

Dentro deste repositório há como exemplo dois programas client/server em UDP, udpclient.c e udpserver.c. Eles se comunicam de um lado para outro enviando mensagens de hello com um número na frente que é incrementado pelo servidor.

    udpclient                  udpserver
        |                         |
        |--- 1 hello client ----->|
        |                         |
        |<-- 2 hello server ------|
        |                         |
        |--- 2 hello client ----->|
        |                         |
        |<-- 3 hello server ------|
        |                         |
        |--- 3 hello client ----->|
        |                         |
        |<-- 4 hello server ------|
        |                         |
        |.........................|
        |                         |

Eu quero conectar em meu udpserver, mas a conexão é instável e a razão de perda de pacotes é alta, gerando um throughput muito pequeno. Para aumentar o throughput, ou seja, diminuir a perda de pacote, eu posso rodar um MPUDP para o servidor e estabilizar uma "conexão" UDP através da redundância das bridges.

O udpserver está em listen na porta 6666 UDP e eu executo o mpserver no servidor da seguinte forma:

    mpserver 2000 localhost 6666

Localmente executo o mpclient da seguinte forma:

    mpclient 4000 client.mpclient.conf

Abaixo está o conteúdo do arquivo client.mpclient.conf 

    # mptunnel
    
    localhost 4001
    localhost 4002
    localhost 4003

Em cada "servidor bridge" (no exemplo está tudo local, mas não precisaria) use socat para redirecionar os pacotes:

    socat udp-listen:4001 udp4:localhost:2000
    socat udp-listen:4002 udp4:localhost:2000
    socat udp-listen:4003 udp4:localhost:2000

Os servidores bridge irão ficar em listen nas portas 4001, 4002 e 4003 e redirecionar qualquer pacote recebido para localhost:2000, e vice-versa.

Agora eu faço o cliente conectar em localhost:4000 que o mpclient está em listen ele irá estabiizar uma conexão sobre o MultiPath UDP tunnel.

                           .------ bridge server 1 -----.
                          /                              \
    udpclient --- mpclient ------- bridge server 2 ------- mpserver --- udpserver
                          \                              /
                           `------ bridge server 3 -----`

Dois scripts estão disponíveis para iniciar e parar a arquitetura de exemplo acima chamados respectivamente sample.start.sh e sample.stop.sh.

Para observar a performance da solução os samples udpclient/udpserver servirão para medir a eficiência de uma comunicação onde as bridges se tornam instáveis, e para isso eles precisarão de uma rota remota entre as bridges. Este teste requer ao menos uma máquina a mais que esteja acessível na rede pelas portas a serem usadas (pode ser uma máquina virtual).

Altere a execução das bridges da seguinte forma, trocando o endereço remoto pelo correto.

    # main computer
    socat udp-listen:4001 udp4:remote_address:5001&
    socat udp-listen:4002 udp4:remote_address:5002&
    socat udp-listen:4003 udp4:remote_address:5003&
    # failback
    socat udp-listen:4004 udp4:localhost:2000&
    
    # remote computer
    socat udp-listen:5001 udp4:local_address:2000&
    socat udp-listen:5002 udp4:local_address:2000&
    socat udp-listen:5003 udp4:local_address:2000&

Isso fará com que três dos quatros bridges sejam remotos, enquanto o último estará funcionando totalmente local. Ao iniciar o mptunnel nesta configuração a comunicação entre udpclient e udpserver continuará funcionando na mesma velocidade mesmo que a comunicação na rede seja interrompida, graças ao quarto caminho totalmente local.

Outros cenários podem ser desenhados levando em conta a velocidade de uma rede ou sua instabilidade.

Mptunnel adiciona alguma informação de controle dentro dos pacotes, incluindo informação síncrona. mpserver e mpclient devem ser iniciados ao mesmo tempo. Se o mpclient ou o mpserver terminar, você terá que reiniciar ambos para restabelecer o túnel.  

Atualmente você pode especificar apenas um único host alvo. Alguém sabe se existe uma biblioteca C de proxy SOCKS5? Penso que ao tornar o mpclient como um servidor proxy SOCKS irá torná-lo mais fácil de usar.  

Mptunnel não encripta os pacotes por padrão, apesar de ter essa opção, pois isso irá diminuir o throughput. Em alguns testes o throughput atual é 3Mbps enquanto usando três túneis com criptografia, e após desabilitar a criptografia o throughput sobe para 300Mbps. Se você ainda quiser que o mptunnel encripte os pacotes, defina a variável de ambiente MPTUNNELENCRYPT=1.  

Para compilar o mptunnel, essas bibliotecas são requeridas:

 - libev
 - mlvpn, uma solução similar para multipath UDP.
