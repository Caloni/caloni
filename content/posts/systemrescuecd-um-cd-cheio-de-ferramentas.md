---
date: "2017-05-28"
title: "SystemRescueCD: um CD cheio de ferramentas Linux para desenvolvedores e suporte"
categories: [ "draft", "blog" ]
---
Há diversas distros Linux capazes de bootar via CD e com uma penca de ferramentas. Conheci há alguns anos uma delas: a [SystemRescueCd](http://www.system-rescue-cd.org/SystemRescueCd_Homepage): um disco de recuperação de HDs com diversas ferramentas embutidas. Dentro dele pode ser inserido outras ferramentas que achar interessante, e o mais importante, desenvolver através do próprio CD suas ferramentas.

A modificação do CD pode ser feita bootando com ele mesmo, seguinto o [tutorial da própria SystemRescueCd](http://www.system-rescue-cd.org/Sysresccd-manual-en_How_to_personalize_SystemRescueCd). No entanto, para facilitar o uso, é possível utilizá-lo em um ambiente virtualizado (criar uma VMWare que boote pelo CD, por exemplo, e depois instalar no HD virtual).

Outra opção interessante é montar outras partições partindo do próprio CD. Ao bootar com o CD da SystemRescue, após ter acesso ao terminal pela primeira vez, detecte e formate o HD Linux usando a ferramenta fdisk. Dentro da ferramenta use as opções padrão e crie uma particão Linux. Ao final, escreva com 'w', formate a partição (ex: mkfs.ext4) e a partição já deverá estar disponível no próximo boot.

```cmd
ls /dev/sd*
/dev/sda /dev/sdb
fdisk /dev/sda
mkfs.ext4 /dev/sda1
```

Para formatar uma partição Windows é possível realizar o mesmo procedimento, mas trocar o tipo de partição para Windows FAT32. Com isso a partição estará disponível para ser montada tanto na máquina virtual quanto na real.

Desligue a VM. A partir do Windows, monte o HD Windows e formate a partição criada. Ou, se a partição ainda não foi criada é só criar pelo Gerenciador de Discos do Windows.

```cmd
shutdown -h -t 0 now
```

Obs.: Apenas a VM ou a máquina real podem utilizar o HD de uma vez. Portanto, para copiar arquivos para o HD virtualizado é necessário desligar a VM antes.

## Customizando seu CD

Seguindo o tutorial do SystemRescueCD ("Step-01: Mount the working partition"), vamos montar a partição Linux na pasta /mnt/custom.

```cmd
% mkdir /mnt/custom
% mount /dev/sda1 /mnt/custom
```

Em seguida extraia os arquivos atuais do CD para a pasta custom (essa operação pode demorar alguns minutos):

```cmd
% /usr/sbin/sysresccd-custom extract
```

Após a conclusão dessa operação, os arquivos customizados poderão ser encontrados em /mnt/custom/customcd/files/bin

```cmd
ls /mnt/custom/customcd/files/bin
```

Para copiar os arquivos novos, monte a partição Windows e copie de uma pasta para outra. Já existe uma pasta em mnt chamada windows que pode ser alvo da montagem. Abaixo os comandos necessários para atualizar um possível script:

```cmd
mount /dev/sdb1 /mnt/windows
cp /mnt/windows/script.sh /mnt/custom/customcd/files/script
overwrite? y
```

Voilá! Agora que os arquivos já foram atualizados é hora de regerar um novo ISO do CD. Para isso, executar o seguinte script do RescueCD ("Step-10: Create the new ISO image"); esse comando pode demorar alguns minutos:

```cmd
/usr/sbin/sysresccd-custom isogen escolha_um_nome
```

Após a conclusão do comando o novo ISO deverá estar no diretório /mnt/custom/customcd/isofile/ com a data/hora atual. Copie este arquivo para a partição Windows para ter acesso ao ISO na máquina real:

```cmd
cp /mnt/custom/customcd/isofile/*.iso /mnt/windows
```

Desligue a máquina virtual e volte a montar o HD na máquina real. O ISO do novo CD estará disponível.
