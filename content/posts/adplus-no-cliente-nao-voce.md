---
date: "2009-08-10"
tags: [ "code", "draft",  ]
title: "AdPlus no cliente, não você!"
---
O AdPlus é uma das poderosas ferramentas do pacote Debugging Tools for Windows. Se trata basicamente de um script que serve para realizar múltiplas fotografias no estado de um programa em execução usando para isso os depuradores do próprio pacote. Quando alguma coisa estiver errada, principalmente um crash ou travamento, ele paralisa a execução e gera um dump final com toda a história contada desde o começo.

Ele pode ser usado na situação mais comum: o programa trava/quebra em um cliente específico e/ou em um momento específico que pode acontecer em cinco segundos ou daqui a quinze horas. Como você não pode ficar monitorando o tempo todo a execução do programa (haja indexadores no PerfMon!) então você precisa de alguém que monitore por você. Como seres humanos costumam ter deficit de atenção muito facilmente você vai lá no cliente (ou pede para alguém ir) e executa o AdPlus, que dá conta do recado:


Esse notepad, viu! Sempre ele!

Bom, vamos fazer alguma brincadeira de desmontar para ver seu funcionamento. Com o notepad recém-aberto por esse comando, vamos abrir outro depurador em modo de visualização e alterar alguma chamada-chave para quebrar propositadamente:


Após isso só precisamos abrir um arquivo qualquer que não existe:

Depois desse lapso de memória o AdPlus irá gerar dois "dumpões" e um "dumpinho" para você:

O dumpinho é a exceção de first chance, que ele iria gerar de qualquer forma se houvesse uma exceção capturada pelo programa. É apenas um minidump.

Os outros dois dumpões são o momento da exceção second chance, o que quer dizer que é antes da casa cair, e o segundo é quando a casa já caiu e o processo pegou suas coisas e já tá indo embora.

A partir do second chance podemos visualizar a cagada feita pelo nosso WinDbg de passagem.




Se você não é desenvolvedor apenas empacote essa pasta com os dumps e envie para o culpado (ou quem você gostar menos).

Existem alguns outros parâmetros bem comuns e que podem ser muito úteis para outras situações:

	
  * Quando o programa já está rodando e não pode ser parado senão tudo está perdido (adplus -crash -pn processo.exe).

	
  * Quando o programa não vai capotar, mas vai travar/parar de responder (adplus -hang -sc processo.exe).

	
  * Quando existem muitos outros processos com o mesmo nome (adplus -crash -p [PID]).

Existem outros mais, mas apenas decorando esses e guardando a pasta do Debugging Tools no PenDrive já garante sucesso em 90% dos casos em que o cliente xingar o suporte.
