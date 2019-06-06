---
date: "2008-07-10"
title: Primeiros passos no VMware Workstation
categories: [ "code" ]
---
Como uma ferramenta essencial que uso todos os dias da minha vida de programador, sou obrigado a falar neste blogue sobre a [VMware](http://www.vmware.com), ferramenta que tem me salvado algumas centenas de horas de depuração, testes e alguns cabelos brancos (a mais).

Para os que não sabem, o VMware é um _software _de virtualização que permite rodar diversos sistemas operacionais secundários (chamados de convidados, ou _guests_) em cima do sistema operacional primário (chamado de hospedeiro, ou _host_). Para isso ele utiliza uma técnica muito interessante conhecida como [virtualização](http://en.wikipedia.org/wiki/Virtualization), onde o desempenho da máquina virtual chega bem próximo da máquina nativa em que estamos rodando, ainda mais se instalados os apetrechos de otimização (vide VMware Tools) dentro dos sistemas operacionais convidados.

#### Primeiro passo: instalar (ou seria comprar?)

O VMware, diferente de [alguns](http://www.microsoft.com/windows/downloads/virtualpc/default.mspx) [outros](http://www.caloni.com.br/virtualbox) [programas de virtualização](http://www.cl.cam.ac.uk/research/srg/netos/xen/), não é gratuito. No entanto, o tempo despendido pela equipe da VMware em tornar esta a solução a de melhor qualidade (opinião pessoal de quem já mexeu com Virtual PC e pouco de VirtualBox) está bem cotado, sendo que seu preço é acessível pelo desenvolvedor médio. Pior que o preço da VMware com certeza será o dos sistemas operacionais convidados, se estes forem da Microsoft, que obriga cada instância do Windows, seja hospedeiro ou convidado, a possuir uma licença separada. Se rodar um Windows XP como hospedeiro e um Vista e 2000 como convidados vai desembolsar pelo menos o quíntuplo da licença da VMware.

No entanto, não entremos em mais detalhes financeiros. Os detalhes técnicos são mais interessantes.

#### Segundo passo: instalar (agora sim!)

![newvm.PNG](/images/newvm.PNG)

A instalação é simples e indolor, sendo constituída de cinco ou seis botões de _next_. O resto, e mais importante, é a instalação de um sistema operacional dentro de sua primeira máquina virtual. Outro assistente existe nessa fase para guiá-lo através de suas escolhas que irão configurar sua futura máquina.

<blockquote>Um pouco sobre redes

**Use bridged networking**. É criada uma conexão real através de uma ponte feita em cima de uma placa de rede da máquina real. É usado um IP diferente da máquina real e se comporta como uma outra máquina qualquer na rede.

**Use NAT**. As conexões são criadas usando o IP do sistema operacional hospedeiro. Para isto acontecer é usado o conhecido esquema de NAT, onde um único IP externo pode representar n IPs internos de uma rede (nesse caso, a rede virtual formada pelas máquinas virtuais de uma mesma máquina real).

**Use host-only networking**. O IP usado nessa conexão é diferente da máquina real, mas só é enxergada por ela e por outras VMs localizadas na mesma máquina hospedeira. Muito útil para isolar um teste de vírus, quando se precisa de uma rede mas não podemos usar a rede da empresa inteira.</blockquote>

Imagine uma VM (Virtual Machine) como uma máquina de verdade, onde podemos dar _boot_, formatar HDs (virtuais ou reais), colocar e remover dispositivos. Tendo isso em mente, fica simples entender o que funciona por dentro de sua console, ou seja, a tela onde vemos a saída da virtualização.

<blockquote>Um pouco sobre discos virtuais

Os HDs que criamos para nossas VMs são arquivos lógicos localizados em nosso HD real. A mágica em que o sistema operacional virtual acessa o disco virtual como se fosse de verdade é feita pela VMware, inclusive a doce ilusão que ele cotém 80 GB, enquanto seu arquivo-repositório ocupa meros 5 GB no disco. Nas edições novas do software, é possível mapear um HD virtual e exibi-lo na máquina real.</blockquote>

Se você dispõe do CD de instalação de um sistema operacional, por exemplo, Windows XP, basta inseri-lo no CD virtual de sua VM. Ela aceita também imagens ISO, se for o caso. Lembre-se apenas que ele terá que ser "bootável", do contrário é necessário um disquete de _boot_.

![vmdevices.PNG](/images/vmdevices.PNG)

<blockquote>Um pouco sobre BIOS</blockquote>

<blockquote>A sua VM emula todo o comportamento de uma máquina real. Ela, portanto, contém uma BIOS, feita pela VMware. Essa BIOS possui as mesmas opções interessantes de ordem de _boot _(primeiro o disquete, depois o HD, etc) e escolha de dispositivo de _boot _(tecla ESC).</blockquote>

A instalação do sistema operacional segue os mesmos passos que a instalação do sistema operacional de qualquer máquina de verdade.

[![xpinstall.PNG](/images/xpinstall.PNG)](/images/xpinstall.PNG)

<blockquote>As teclas mágicas

**Entrar o foco na VM. Digite Ctrl + G.** Todos seus movimentos de teclado e mouse só irão funcionar dentro da máquina virtual, exceto o Ctrl + Alt + Del, exclusividade do [sistema de autenticação do Windows](http://www.caloni.com.br/gina-x-credential-provider).

**Tirar o foco da VM. Digite Ctrl + Alt.** Todos seus movimentos de teclado e mouse passam a ser do SO hospedeiro.

**Ctrl + Alt + Del dentro da VM. Use Ctrl + Alt + Insert.** Ele terá o mesmo efeito que um CAD, independente em que tela estiver em sua VM.</blockquote>

Após feita a instalação, você terá um sistema operacional rodando dentro de um sistema operacional. Isso não é legal?

[![xpvm.PNG](/images/xpvm.PNG)](/images/xpvm.PNG)

<blockquote>_Snapshots_

A primeira coisa a fazer em sua VM com SO recém-instalado é criar um _snapshot_, ou seja, salvar o estado atual de sua máquina virtual. Ao fazer isso, se fizer alguma coisa dentro da VM que possa se arrepender depois, basta voltar para o estado que salvou anteriormente. A VMware permite criar quantos _snapshots _precisar (basta ter espaço em disco). Ela permite que você crie novas máquinas virtuais a partir de um estado de uma VM já criada, o que pode economizar todo o tempo de montar do zero outra VM ou copiar o disco virtual.</blockquote>

#### Dois usos muito úteis para uma VM

	
  * Abrir os seus e-mails suspeitos. Não tenha mais medo de sujar seu computador com e-mails de conteúdo duvidoso. Crie um estado seguro em sua VM através de um snapshot (fotografia de estado da máquina virtual) e execute os anexos mais absurdos. Depois basta voltar para o estado seguro.

	
  * Testes que costumam alterar o estado da máquina. Driver, [GINA](http://www.caloni.com.br/gina-x-credential-provider) ou [serviço](http://www.caloni.com.br/como-rodar-qualquer-coisa-como-servico) novo? Que tal usar uma VM para fazer os testes iniciais e parar de reformatar o Windows?

As VMs possibilitam um mundo de utilidades que o mundo ainda está descobrindo. Para nós, desenvolvedores, a maior vantagem de tudo isso é termos nossos ambientes de testes mais bizarros facilmente configurados no conforto de uma caixinha de areia.
