---
date: "2019-12-11"
link: "https://github.com/bitforgebr/mptunnel"
tags: [ "code" ]
title: "Como Funciona o MPTunnel"
---
A ideia por trás de um sistema multipath de rede é fornecer mais de um caminho para o tráfego de pacotes. O objetivo pode ser diminuir a perda de pacotes por causa da instabilidade da infra, mas também fazer com que a velocidade da comunicação seja maior pela diminuição da razão da perda de pacotes, além da melhor rota acabar sendo por onde os pacotes irão chegar primeiro, em uma espécie de seleção natural da arquitetura.

O projeto MPTunnel é uma implementação em user space de UDP multipath. Assim como a contraparte em sua versão TCP, você pode estabilizar várias conexões entre o servidor local e o remoto.

[MPTCP] (MultiPath TCP) é uma boa ideia para tornar a conexão de rede mais robusta, mas apenas funciona em TCP, e em um ambiente multiplataforma não há soluções em kernel mode exceto o ECMP desenvolvido no último Linux, cujos [artigos de Jakub Sitnicki] explicam os detalhes. E foi através da minha busca por uma implementação de MPUDP que encontrei essa ferramenta feita por [greensea], um usuário do GitHub.

## Concepção

Existem dois servidores: Server A e Server B. A conexão de rede entre Server A e Server B é instável (com uma razão alta de perda de pacotes). Dessa forma, nós gostaríamos de estabilizar um túnel multipath entre Server A e Server B, esperando que a conexão entre ambos se torne mais confiável, diminuindo a razão entre perda e envio de pacotes. Com o broadcast dos pacotes por vários caminhos o resultado a longo prazo é uma comunicação cuja performance é prioridade.

    Server A
     |- mpclient
        |- bridge 1
           |- mpserver
              |- Server B
        |- bridge 2
           |- mpserver
              |- Server B
        |- bridge 3
           |- mpserver
              |- Server B

Mpclient é a parte cliente do mptunnel que roda no Server A. Você deve dizer a ele a informação dos servidores bridge. Uma vez que é iniciado, o mpclient abre uma porta local UDP para escutar e redirecionar qualquer pacote de e para os servidores bridge.

Mpserver é a parte servidora do mptunnel que roda em qualquer lugar que acessa o Server B. Você deve dizer a ele a informação desse Server. Uma vez que é iniciado, o mpserver irá redirecionar qualquer pacote para o Server B.

Os servidores bridge são simples, eles apenas redirecionam os pacotes do mpclient para mpserver, ou pacotes do mpserver para mpclient. Você pode usar as ferramentas nc ou socat para entregar um servidor bridge.

## Compilação

Para a solução ser rodável em Linux, Windows e Mac OS os fontes compilam em um ambiente POSIX mínimo, já disponível nos três SOs, sendo que para Windows este ambiente é o Cygwin. O resumo para compilar em Linux é instalar o gcc, o make, o git, as dependências, baixar o projeto e compilar. Esses passos devem funcionar em qualquer Linux e foi testado em Ubuntu.

### Windows

Para Windows o primeiro passo é baixar e instalar o cygwin com os seguintes pacotes adicionais ao padrão: gcc-core, socat, git, make, libev, libev-devel, libintl-devel. Em seguida deve-se baixar o repositório do mtunnel e de dentro de um terminal Cygwin executar o build.

## Exemplo usando udpserver e udpclient

Dentro do repositório deste post há como exemplo de um modelo cliente e servidor em UDP, udpclient.c e udpserver.c. Eles se comunicam de um lado para outro enviando mensagens de hello com um número na frente que é incrementado pelo servidor.

    udpclient      udpserver
    |                      |
    |--- 1 hello cli ----->|
    |                      |
    |<-- 2 hello srv ------|
    |                      |
    |--- 2 hello cli ----->|
    |                      |
    |<-- 3 hello srv ------|
    |                      |
    |--- 3 hello cli ----->|
    |                      |
    |<-- 4 hello srv ------|
    |                      |
    |......................|
    |                      |

Agora eu quero conectar em meu udpserver, mas a conexão é instável e a razão de perda de pacotes é alta, gerando um throughput muito pequeno. Para aumentar o throughput, ou seja, diminuir a perda de pacote, eu posso rodar um MPUDP para o servidor e estabilizar uma "conexão" UDP através da redundância das bridges.

O udpserver está em listen na porta 6666 UDP e eu executo o mpserver no servidor da seguinte forma: "mpserver 2000 localhost 6666". Localmente executo o mpclient da seguinte forma: "mpclient 4000 client.mpclient.conf". Abaixo está o conteúdo do arquivo client.mpclient.conf:

    # mptunnel
    localhost 4001
    localhost 4002
    localhost 4003

Em cada "servidor bridge" (no exemplo está tudo local, mas não precisaria) use socat para redirecionar os pacotes: "socat udp-listen:4001 udp4:localhost:2000", "socat udp-listen:4002 udp4:localhost:2000", "socat udp-listen:4003 udp4:localhost:2000".

Os servidores bridge irão ficar em listen nas portas 4001, 4002 e 4003 e redirecionar qualquer pacote recebido para localhost:2000, e vice-versa. Agora eu faço o cliente conectar em localhost:4000 que o mpclient está em listen ele irá estabiizar uma conexão sobre o MultiPath UDP tunnel.

Dois scripts estão disponíveis para iniciar e parar a arquitetura de exemplo acima chamados respectivamente sample.start.sh e sample.stop.sh.

Para observar a performance da solução os exemplos de client e server servirão para medir a eficiência de uma comunicação onde as bridges se tornam instáveis, e para isso eles precisarão de uma rota remota entre as bridges. Este teste requer ao menos uma máquina a mais que esteja acessível na rede pelas portas a serem usadas (pode ser uma máquina virtual). Altere a execução das bridges da seguinte forma, trocando o endereço remoto pelo correto:

#### main computer
 - socat udp-listen:4001 udp4:remote_address:5001&
 - socat udp-listen:4002 udp4:remote_address:5002&
 - socat udp-listen:4003 udp4:remote_address:5003&

#### failback
 - socat udp-listen:4004 udp4:localhost:2000&

#### remote computer
 - socat udp-listen:5001 udp4:local_address:2000&
 - socat udp-listen:5002 udp4:local_address:2000&
 - socat udp-listen:5003 udp4:local_address:2000&

Isso fará com que três dos quatros bridges sejam remotos, enquanto o último estará funcionando totalmente local. Ao iniciar o mptunnel nesta configuração a comunicação entre udpclient e udpserver continuará funcionando na mesma velocidade mesmo que a comunicação na rede seja interrompida, graças ao quarto caminho totalmente local.

Outros cenários podem ser desenhados, levando em conta a velocidade de uma rede ou sua instabilidade.

## Bugs e observações

Mptunnel adiciona alguma informação de controle dentro dos pacotes, incluindo informação síncrona. O mpserver e o mpclient devem ser iniciados ao mesmo tempo. Se o mpclient ou o mpserver terminar, você terá que reiniciar ambos para restabelecer o túnel.  

Atualmente você pode especificar apenas um único host alvo. Alguém sabe se existe uma biblioteca C de proxy SOCKS5? Penso que ao tornar o mpclient como um servidor proxy SOCKS irá torná-lo mais fácil de usar.  

Mptunnel não encripta os pacotes por padrão, apesar de ter essa opção, pois isso irá diminuir o throughput. Em alguns testes o throughput atual é 3Mbps enquanto usando três túneis com criptografia, e após desabilitar a criptografia o throughput sobe para 300Mbps. Se você ainda quiser que o mptunnel encripte os pacotes, defina a variável de ambiente MPTUNNELENCRYPT=1.  

Para compilar o mptunnel, a biblioteca libev é um requisito. Para uma uma solução similar para multipath UDP em TCP dê uma olhada no projeto [mlvpn].

[MPTCP]: https://www.multipath-tcp.org/
[artigos de Jakub Sitnicki]: http://codecave.cc/multipath-routing-in-linux-part-1.html
[greensea]: https://github.com/greensea
[mlvpn]: https://github.com/zehome/MLVPN.
