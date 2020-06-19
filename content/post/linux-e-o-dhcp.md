---
categories: [ "code" ]
date: "2008-04-09"
tags: [ "draft", "tools" ]
title: "Linux e o DHCP"
---
Quando procuramos no google por "linux dhcp", o que vem em resposta são diversas dicas, tutoriais, documentos oficiais e palpites sobre como configurar um servidor Linux.

Muito bem. E a outra ponta da história?

[Testes feitos em um Fedora 8, não me pergunte mais detalhes]

O primeiro linque útil encontrado foi a documentação da Red Hat. Além disso seguem alguns macetes que eu descobri no decorrer do percurso. A primeira coisa a ser configurada é o arquivo /etc/sysconfig/network. Nele devemos, em uma configuração simplista, colocar uma única linha:


Tive alguns problemas com a entrada NETWORKINGIPV6, ou algo do gênero. A comunicação com o servidor DHCP da rede simplesmente não funcionava com essa linha, deixando o computador sem IP durante o boot. Má configuração do servidor? Pode até ser. Porém, não quis entrar nesses meandros.

Por isso, se houver a linha sobre IPV6 e você tiver problemas, comente-a temporariamente.

O passo seguinte é configurar a interface de rede, que é no fim das contas a representação da sua placa. Para isso temos alguns arquivos em /etc/sysconfig/network-scripts no formato ifcfg-nome-da-interface. Se você digitar ifconfig na linha de comando terá os nomes de interface disponíveis. No meu caso, eth0.




Note que o valor BOOTPROTO é realmente BOOTPROTO, com um O no final. Tive alguns problemas de soletrar também nesse caso, o que me gerou mais alguns reboots mal-sucedidos.

Bem, o que isso faz? Basicamente, manda o Linux utilizar o protocolo DHCP, procurando na rede algum servidor que lhe dê algum IP válido. Só isso. O resto ele faz dinamicamente.

Inclusive alterar automaticamente o arquivo /etc/resolv.conf. Nele estão definidas algumas coisas como o domínio de nomes que estamos e os IPs de onde buscar a resolução de nomes.

Feito isso, como se costuma dizer, voilà! Temos um cliente DHCP funcionando contente e feliz. Eu reiniciei a máquina para tudo dar certo, mas provavelmente devem existir maneiras mais saudáveis de reiniciar a rede (talvez um ifdown seguido de ifup resolvesse).  E agora eu posso finalmente ter acesso aos pacotes de instalação que precisava.

Notas de um Linux padawan =)
