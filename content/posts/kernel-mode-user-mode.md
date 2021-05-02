---
date: "2008-05-13"
link: "https://youtu.be/j1f7DQkFI5A"
title: "Kernel Mode >> User Mode, ou Como Fazer Debug de User Mode pelo Kernel Mode usando WinDbg"
tags: [ "code" ]
---
Existem algumas situações onde um depurador WYSIWYG é artigo de luxo.

Imagine o seguinte: temos um serviço que inicia automagicamente antes do login do Windows, e possivelmente antes mesmo do ambiente gráfico. Esse serviço tem algum problema que impede que ele funcione sob as circunstâncias de inicialização do sistema. O que fazer?  Atachar o WinDbg no processo?

Mas que mané WinDbg? Que mané atachar? Nessa hora nós temos bem menos do que nossos sentidos são capazes de enxergar.

Nessas horas o único que pode nos ajudar é o kernel debugger.

Os depuradores do pacote Debugging Tools (especialmente o ntsd e o cdb) suportam o funcionamento em modo proxy, ou seja, eles apenas redirecionam a saída e os comandos entre as duas pontas da depuração (o depurador e o depurado). Isso é comumente usado em [depuração remota] e [depuração de kernel], quando o sistema inteiro está congelado. O objetivo aqui é conseguir os dois: depurar remotamente um processo em um sistema que está travado.

Para isso podemos nos utilizar do parâmetro -d, que manda o depurador redirecionar toda saída e controle para o depurador de kernel. Para que isso funcione o depurador já deve estar atachado no sistema-alvo. A coisa funciona mais ou menos assim:

![WinDbg User Kernel Debug](/img/windbg-user-kernel.png)

Com essa configuração temos a vantagem de ter o sistema congelado só pra nós, ao mesmo tempo que conseguimos depurar nosso processo fujão, passo-a-passo.

A única desvantagem é não ter uma GUI tão poderosa quando o "WinDbg fonte colorido, tooltips, etc". Pra quem não liga pra essas frescuras, é possível depurar processos de maneira produtiva utilizando esse cenário.

Para ativar qualquer programa que irá rodar nesse modo, basta usar o aplicativo gflags:

    gflags /p /enable servico.exe /debug "c:\path\ntsd.exe -d"

Para entender o fluxo de navegação pelo mundo kernel-user misturados é preciso dar uma lida bem profunda na ajuda do Debugging Tools para entender como as coisas estão funcionando nessa configuração milagrosa que estamos usando. Procure por "Controlling the User-Mode Debugger from the Kernel Debugger". Também é possível ouvir falar parcamente sobre isso no livro Advanced Windows Debugging na parte "Redirecting a User Mode Debugger Through a Kernel". A vantagem é que vem de brinde uma bela figura para pendurar em um quadro no escritório (embora eu possa jurar que já vi essa figura na ajuda do WinDbg):

![windbg-user-kernel2.png](/img/windbg-user-kernel2.png)

Como podemos notar, o controlador de tudo é o kernel debugger. Assim que o depurador de processo entra em ação, ele se comunica com o depurador de kernel que entra no modo user mode prompt, pedindo entrada para ser redirecionada ao depurador de processo. Existem alguns caminhos para sair de um estado e entrar em outro, como o comando .breakin e o .sleep.

É necessário recomentar: estamos nos comunicando com um depurador e o seu processo depurado em um sistema totalmente travado. Isso quer dizer que o acesso a coisas como código-fonte e símbolos é extremamente limitado, porém não impossível. Apenas mantenha-os localmente na máquina-vítima, pois uma comunicação pela rede não irá funcionar.

A depuração com a linha atual no código-fonte demarcando onde estamos também não é possível, uma vez que o WinDbg da ponta de cá apenas faz o papel de garoto de recados para o "depurador de verdade" do outro lado (no nosso exemplo, o ntsd). Isso quer dizer que a forma mais "fácil" de ir passo-a-passo é usar o comando p (step) ou t (trace), além de habilitar o uso de fonte em 100%.

    input> .srcpath c:\maquina-vitima\src
    input> l+* $$ habilita uso de código-fonte no ntsd
    ...
    0:000> p
    >  15: int main() $$ número da linha seguido do fonte
    >  16: {
    0:000> bp myFunction
    0:000> g
    0:000>

Um tipo de problema que só pode ser depurado dessa maneira enfatiza a importância do uso de unit tests, além de um controle de qualidade mais aguçado antes de liberar uma versão para o cliente.

[depuração remota]: /windbg-a-distancia
[depuração de kernel]: http://www.driverentry.com.br
