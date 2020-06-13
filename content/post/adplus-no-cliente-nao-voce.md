---
categories: [ "code" ]
date: "2009-08-10"
tags: [ "draft",  ]
title: "AdPlus no cliente, não você!"
---
O AdPlus é uma das poderosas ferramentas do pacote Debugging Tools for Windows. Se trata basicamente de um script que serve para realizar múltiplas fotografias no estado de um programa em execução usando para isso os depuradores do próprio pacote. Quando alguma coisa estiver errada, principalmente um crash ou travamento, ele paralisa a execução e gera um dump final com toda a história contada desde o começo.

Ele pode ser usado na situação mais comum: o programa trava/quebra em um cliente específico e/ou em um momento específico que pode acontecer em cinco segundos ou daqui a quinze horas. Como você não pode ficar monitorando o tempo todo a execução do programa (haja indexadores no PerfMon!) então você precisa de alguém que monitore por você. Como seres humanos costumam ter deficit de atenção muito facilmente você vai lá no cliente (ou pede para alguém ir) e executa o AdPlus, que dá conta do recado:

    
    AdPlus.vbs -crash -sc notepad.exe

Esse notepad, viu! Sempre ele!

Bom, vamos fazer alguma brincadeira de desmontar para ver seu funcionamento. Com o notepad recém-aberto por esse comando, vamos abrir outro depurador em modo de visualização e alterar alguma chamada-chave para quebrar propositadamente:

    
    windbg -pv -pn notepad.exe
    a user32!MessageBoxW
    jmp 0
    .detach
    q

Após isso só precisamos abrir um arquivo qualquer que não existe:

Depois desse lapso de memória o AdPlus irá gerar dois "dumpões" e um "dumpinho" para você:

O dumpinho é a exceção de first chance, que ele iria gerar de qualquer forma se houvesse uma exceção capturada pelo programa. É apenas um minidump.

Os outros dois dumpões são o momento da exceção second chance, o que quer dizer que é antes da casa cair, e o segundo é quando a casa já caiu e o processo pegou suas coisas e já tá indo embora.

A partir do second chance podemos visualizar a cagada feita pelo nosso WinDbg de passagem.

    
    windbg -z PID-0__Spawned0__2nd_chance_AccessViolation__full_0854_2009-07-28_09-03-54-723_0d34.dmp

    
    This dump file has an exception of interest stored in it.
    The stored exception information can be accessed via .ecxr.
    (d34.7b0): Access violation - code c0000005 (first/second chance not available)
    eax=0007cfb8 ebx=80004005 ecx=7e37a622 edx=0000000a esi=00000208 edi=003604e2
    eip=00000000 esp=0007cfa0 ebp=0007d9e4 iopl=0         nv up ei ng nz na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000286
    00000000 ??              ???
    k

    
    ChildEBP RetAddr
    WARNING: Frame IP not in any known module. Following frames may be wrong.
    0007cf9c 763ab8a8 0x0
    0007d9e4 763ab90c comdlg32!CDMessageBox+0x76
    0007da04 7638beee comdlg32!InvalidFileWarningNew+0x54
    0007e278 763873cf comdlg32!CFileOpenBrowser::OKButtonPressed+0x9f0
    0007e4b8 763872d7 comdlg32!CFileOpenBrowser::ProcessEdit+0x192
    0007e4f8 7638277f comdlg32!CFileOpenBrowser::OnCommandMessage+0x1d3
    0007e738 7e368734 comdlg32!OpenDlgProc+0x2f5
    0007e764 7e373ce4 user32!InternalCallWinProc+0x28

Se você não é desenvolvedor apenas empacote essa pasta com os dumps e envie para o culpado (ou quem você gostar menos).

Existem alguns outros parâmetros bem comuns e que podem ser muito úteis para outras situações:

	
  * Quando o programa já está rodando e não pode ser parado senão tudo está perdido (adplus -crash -pn processo.exe).

	
  * Quando o programa não vai capotar, mas vai travar/parar de responder (adplus -hang -sc processo.exe).

	
  * Quando existem muitos outros processos com o mesmo nome (adplus -crash -p [PID]).

Existem outros mais, mas apenas decorando esses e guardando a pasta do Debugging Tools no PenDrive já garante sucesso em 90% dos casos em que o cliente xingar o suporte.
