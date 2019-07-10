---
date: "2008-07-04"
title: VirtualBox
categories: [ "blog" ]
---
[![virtualbox_about_screen.png](http://i.imgur.com/SmWJn1o.png)](http://en.wikipedia.org/wiki/VirtualBox)O [VirtualBox](http://www.virtualbox.org) parece ser o concorrente mais próximo atualmente da [VMWare](http://www.vmware.com). Descobrimos ele essa semana e resolvemos fazer alguns testes. O resultado foi bem animador.

Desenvolvido pela Sun Microsystems, as características do VirtualBox impressionam pelo cuidado que houve em torná-lo muito parecido com sua concorrente paga. Apenas para começar, ela suporta dispositivos USB, possui múltiplos snapshots e já suporta o modo do [VMWare Fusion](www.vmware.com/download/fusion) - chamado de _"seamless mode_" - , que estará integrado na versão 7 da VMWare.

No entanto, entre as coisas que testamos (instalado em um Windows Vista SP1 como host), o que não funcionou já não agradou tanto. A lista de prós e contras ainda confirma a liderança da VMWare, pelo menos em qualidade:

    
    Funcionalidade          VMWare             VirtualBox

    
    Snapshots               Sim                Sim. Mesma velocidade.
    USB                     Sim                Sim. Não funcionou.
    Seamless Mode           Não                Sim.
    Clipboard               Sim                Sim. Não funcionou.
    Shared Folders          Sim                Sim. Erros de acesso.
    Ferramentas Guest       Sim                Sim.
    Pause Momentâneo        Não                Sim.

Além da tabela de testes acima, é necessário notar que por mas três vezes a VM simplesmente parou de responder, sendo necessário reiniciar o programa Host.

Em suma, o VirtualBox tem tudo para arrasar em futuras versões. Se, é claro, conseguir competir em qualidade com a VMWare que, no momento, é a líder em soluções de virtualização. Talvez por isso sua solução não seja tão barata.
