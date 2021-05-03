---
categories:
- draft
- code
date: '2021-05-01'
link: https://youtu.be/PU0O_HYMoCw
tags:
- debug
title: Como Configurar Debug de Kernel Pela Rede (Hyper-V Edition)
---

Estava pensando em transformar alguns posts antigos que estou revisando em vídeos no YouTube. Acho que o esforço para fazer isso é relativamente baixo se for sem áudio, sem edição e apenas com o que eu naturalmente faria para validar as partes técnicas, e muita gente poderia aprender algumas coisas, como, por exemplo, configurar o debug de kernel.

Foi nessas que eu comecei a gravar um vídeo para [o post] onde eu ensino a depurar um processo em user mode através do debug de kernel mode usando o WinDbg. Esse post é de mais de dez anos e na época usei VMWare e emulação de cabo serial. Hoje estou usando Hyper-V e vejo que a maneira mais fácil de configurar o debug de kernel é pelo driver de rede, usando uma ferramenta do Debugging Tools chamado kdnet.

No vídeo original comecei na inocência seguindo o tutorial da Microsoft para configurar o kdnet, mas acabei gastando quase uma hora nesse esforço, e foi em vão. Eu não consegui usar os passos descritos no tutorial para fazer o boot finalmente conectar no kd.exe.

Pesquisando sobre pessoas que tiveram o mesmo problema encontro um [post da Ophir Harpaz] no Medium dizendo que irá ensinar o porquê de cada comando na configuração desse tipo de debug. O título do post é apenas um chamariz, pois também é um passo-a-passo sem explicação nenhuma dos motivos por trás de cada comando. Porém, os passos são diferentes do da Microsoft, e esses funcionaram. Então vou gravar o vídeo, e de brinde segue o passo-a-passo:

Com uma VM de Windows 10 criada no Hyper-V, desabilite o Secure Boot pelas configurações da VM:

![](/img/hyper-v-disable-secure-boot.png)

Desligue a VM. Pelo meno do Hyper-V crie um novo adaptador pelo Virtual Switch Manager; esse deve apontar para um adaptador de sua máquina real, para host e target conseguirem se comunicar. Atribua esse novo adaptador à sua VM desligada e volte a ligá-la.

Já ligada abra um prompt de comando elevado e use os seguintes comandos do bcdedit para configurar um boot de debug. Lembre-se que o IP deve ser o IP da sua máquina host do seu adaptador de rede real (wi-fi ou cabo). Executando um ipconfig você consegue pegar ele.

    >bcdedit /copy {current} /d "KDNet port 50035"
    The entry was successfully copied to {dd896c2e-fccb-11e8-9cb7-d481d7c30c24}

    >bcdedit /default {dd896c2e-fccb-11e8-9cb7-d481d7c30c24}

    > bcdedit /set {default} debug yes
    The operation completed successfully.

    > bcdedit /dbgsettings net hostip:192.168.1.120 port:50035 newkey
    Key=g3mx1h96o5j9.tbdbyy05hfu7.10tkqaj5agj7e.xttvshlq4zsr

Verificando as configurações:

    > bcdedit /dbgsettings
    key         g3mx1h96o5j9.tbdbyy05hfu7.10tkqaj5agj7e.xttvshlq4zsr
    debugtype   NET
    hostip      192.168.1.120
    port        50035

Com tudo isso configurado é possível ir na máquina host e rodar o kd.exe:

    > kd.exe -k net:port=50035,key=g3mx1h96o5j9.tbdbyy05hfu7.10tkqaj5agj7e.xttvshlq4zsr

    Microsoft (R) Windows Debugger Version 10.0.18362.1 AMD64
    Copyright (c) Microsoft Corporation. All rights reserved.
    
    Using NET for debugging
    Opened WinSock 2.0
    Kernel Debug Target Status: [no_debuggee]; Retries: [0] times in last [7] seconds.
    Waiting to reconnect...

Ele vai ficar nessa de aguardar até a máquina target estar disponível, ou seja, bootando na configuração debug configurada para debug de kernel pela rede nesse IP. Lembre-se de que antes de tudo isso a porta usada deve estar acessível pelo firewall e host e target devem estar pelo menos se pingando. Verifique antes de tentar conectar.

Depois de algumas horas eu finalmente consegui. Agora é hora de começar a gravar o vídeo para o post antigo. Ou outro dia.

[o post]: /kernel-mode-user-mode
[post da Ophir Harpaz]: https://medium.com/@ophirharpaz/kdnet-tutorial-for-noobs-68669778bbd4