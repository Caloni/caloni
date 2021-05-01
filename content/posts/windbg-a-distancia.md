---
date: "2008-03-26"
title: "WinDbg a distância"
tags: [ "blog" ]
---
Acho que o que mais me impressionou até hoje a respeito do WinDbg é a sua capacidade de depuração remota. Não há nada como depurar problemas sentado confortavelmente na sua cadeira de programador em frente à sua mesa de programador.

Já é fato consumado que os maiores problemas da humanidade ocorrem sempre no cliente, com uma relação de dificuldade diretamente proporcional ao cargo ocupado pelo usuário da máquina que está dando problemas. Se esse cliente por acaso mora em um lugar tão tão distante, nada mais justo do que conhecermos algumas técnicas de depuração remota para continuar a mantê-lo tão tão distante.

O ambiente de desenvolvimento (em teoria) não se deve confundir com o ambiente de testes, um lugar onde o desenvolvedor deveria colocar o pé somente quando fosse chamado e quando existisse um problema na versão Release. Por isso e portanto a única coisa permitida em um ambiente de testes é (deveria ser) um servidor de depuração.

O servidor de depuração nada mais é do que um processo que deixa alguma porta aberta  na máquina de testes para que o desenvolvedor consiga facilmente depurar problemas que ocorreram durantes os testes de produção. Ele pode ser facilmente configurado através da instalação do pacote Debugging Tools for Windows.

Existem alguns cenários muito comuns de depuração remota que serão abordados aqui. O resto dos cenários se baseia nos exemplos abaixo, e pode ser montado com uma simples releitura dos tópicos de ajuda do WinDbg sobre o assunto (procure por dbgsrv.exe).

No caso de VM ou máquina de teste do lado do desenvolvedor podemos supor que a máquina tem total acesso e controle do desenvolvedor. Tudo o que temos que fazer é iniciar um WinDbg na máquina-vítima e outro WinDbg na máquina-programador. O WinDbg da máquina-vítima deve ser iniciado no modo-servidor, enquanto o da máquina-programador no modo-cliente.

    windbg -server tcp:port=6666
    windbg -remote tcp:server=maquina-vitima,port=6666

A vantagem dessa técnica é que tanto o WinDbg da máquina-vítima quanto o da máquina-programador podem emitir comandos, e todos vêem os resultados. Uma possível desvantagem é que os símbolos devem estar disponíveis a partir da máquina-vítima.

Se for necessário, é possível convidar mais gente pra festa, pois o WinDbg permite se transformar em uma instância servidora pelo comando .server, que possui a mesma sintaxe da linha de comando. Para a comunicação entre todos esses depuradores ambulantes um comando muito útil é o .echo.

    windbg -server tcp:port=6667 -remote tcp:server=maquina-vitima,port=6666
    windbg -remote tcp:server=maquina-vitima,port=6666

    0:000>.server tcp:port=6667
    MAQUINA-PROGRAMADOR66\caloni (tcp 222.234.235.236:1974) connected at Mon Mar 24 11:47:55 2008
    0:000>.echo E ae, galera? Como que a gente vai consertar essa &%$*&?
    0:000>.echo Putz, sei lá. Acho que vou tomar mais café...

![Windbg Remote](/img/windbg-remote.gif)

No ambiente do cliente é muito mais hostil; é salutar e recomendável utilizar um servidor genérico que não imprima coisa alguma na tela "do outro lado". Após iniciar o depurador na máquina que está dando o problema, o programador tem virtualmente uma série de comandos úteis que podem ser executados remotamente, como iniciar novos processos, se anexar a processos já existentes, copiar novas versões de executáveis, etc.

O nome do processo do lado servidor para modo usuário é dbgsrv.exe. Para o modo kernel é kdsrv.exe. Os parâmetros de execução, felizmente, são os mesmos que os do WinDbg (e CDB, NTSD e KD), o que evita ter que decorar uma nova série de comandos.

Pode parecer besteira falar isso aqui, mas ao depurar um sistema em modo kernel é necessário, é claro, é óbvio, é lógico, ter uma segunda máquina do lado servidor conectada por cabo serial ou firewire ou USB-Debug na máquina-vítima. Ainda que o Debugging Tools permita uma série de flexibilidades, o depurador em modo kernel vai rodar direto do kernel (duh), ou seja, está limitado pela implementação do sistema operacional. Além de que, para travar o processo do kernel, você tem que parar todo o sistema, e nesse caso não existe pilha TCP/IP.

Para iniciar o servidor de depuração e deixar as portas abertas para o depurador temos apenas que iniciar o processo dbgsrv.exe:

    dbgsrv -t tcp:port=6666

Para iniciar o processo depurador, a sintaxe é quase a mesma, só que no lugar de remote especificamos premote:

    windbg -premote tcp:server=maquina-vitima,port=6666

Caso não se saiba a porta usada para iniciar o servidor, ou queira-se listar todos os servidores disponíveis em uma determinada máquina, usa-se o comando -QR.

    cdb -QR \\maquina-vitima

O exemplo acima utilizou uma conexão TCP para montar o ambiente de depuração remota, o que possibilita inclusive correção de problemas via internet. No entanto, nem sempre podemos nos dar ao luxo de abrir portas não-autorizadas, requisito mínimo para estabelecer a conexão com o depurador. Nesse caso, podemos configurar conexões pela porta serial, por pipes nomeados, por SSL. Se for realmente necessário usar a pilha TCP, mas o lado servidor possui um firewall, ainda assim é possível configurar este tipo de conexão com a opção clicon. Dessa forma, quem estabelece a conexão é o servidor, evitando que o cliente fique bloqueado de acessar o ambiente de depuração.

![Windbg Remote](/img/windbg-remote2.gif)

É importante notar que o dbgsrv.exe não é um depurador esperto, no sentido que ele não vai carregar os símbolos para você. Isso é importante na hora de definir qual estratégia utilizar, pois nem sempre os símbolos estarão disponíveis na máquina com problemas, e nem sempre estarão com o desenvolvedor.

Uma organização mais esperta dos ambientes de teste e desenvolvimento tomaria conta de outros problemas como símbolos e fontes com o uso de outras features poderosas do Debugging Tools como servidor de símbolos e servidor de fontes. Porém, a complicação envolvida na configuração desses dois me leva a crer que eles merecem um outro artigo. E é por isso que paramos por aqui.
