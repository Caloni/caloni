---
categories: [ "code" ]
date: "2017-01-16"
tags: [ "draft",  ]
title: "ReadFile assíncrono pode ser síncrono quando você menos espera"
---
Ano passado tive alguns problemas em um projeto que se comunicava com um dispositivo em firmware pela USB. Estávamos utilizando uma biblioteca open source do GitHub que parecia estar bem testada e mantida. Porém, não exatamente para nossos objetivos.

O problema da lib hidapi era que a comunicação usb era feita de forma assíncrona. Isso no Windows é feito com a mesma função de I/O (ReadFile/WriteFile) só que passando um argumento opcional chamado de overlapped. Esse argumento é um ponteiro para uma estrutura que irá ser preenchida assim que o I/O for concluído. E quando é isso? Deve-se esperar pelo handle ser sinalizado (em outras palavras, dando um Sleep ou WaitForSingleObject neste handle).

O funcionamento padrão via overlapped é bem simples: faça a operação de I/O (passando a estrutura) e verifique o retorno. Ele deve ser FALSE e o retorno do próximo GetLastError deve ser ERRORIOPENDING. Bom, descrevendo a operação ela não parece ser tão intuitiva. Mas funciona:


A questão que nós encontramos nesse projeto apenas aconteceu porque após a operação de I/O assíncrona a thread responsável por retornar o resultado ficava em wait eterno ou dava timeout. Ambas as situações são normais e esperadas. Ficar aguardando para sempre um device acontece quando este simplesmente não responde com nenhum dado. E dar timeout acontece quando não queremos aguardar o device para sempre (WaitForSingleObject(handle, 1000), por exemplo, daria timeout depois de 1 segundo, ou 1000 milissegundos).

O motivo da thread nunca retornar (ou dar timeout), porém, não estava em nenhuma dessas situações. Ao monitorar o tráfego usb se verificou que o device respondia em tempo hábil. O problema estava mais embaixo (ou mais em cima): a hidapi não se comportava conforme o MSDN mandava. Há uma situação não-mapeada nessa lib.

Erros ao chamar a API do Win32 são comuns exatamente porque esta é uma lib arcaica, pouco intuitiva com diferentes tipos de exceções. No caso de uma operação assíncrona com overlapped, se você ler as tantas páginas da função ReadFile, por exemplo, vai acabar encontrando um adendo escondido no meio da documentação:

> Synchronization and File Position If hFile is opened with FILE_FLAG_OVERLAPPED, it is an asynchronous file handle; otherwise it is synchronous. The rules for using the OVERLAPPED structure are slightly different for each, as previously noted. Note  If a file or device is opened for asynchronous I/O, subsequent calls to functions such as ReadFile using that handle generally return immediately, but can also behave synchronously with respect to blocked execution. For more information see http://support.microsoft.com/kb/156932.

Este adendo possui a informação que ninguém ainda sabia porque... porque Microsoft.

> If, on the other hand, an operation is completed immediately, then &NumberOfBytesRead passed into ReadFile is valid for the number of bytes read. In this case, ignore the OVERLAPPED structure passed into ReadFile; do not use it with GetOverlappedResult or WaitForSingleObject.

Ou seja, em caso da função ReadFile (ou WriteFile) retornar TRUE em uma operação assíncrona/overlapped, isso quer dizer que a operação foi concluída com sucesso de forma síncrona, não sendo necessário aguardar o I/O ser concluído. Na verdade, é um pouco mais específico: o WaitForSingleObject não deve ser chamado. No nosso caso, ao chamá-lo, criávamos uma espera eterna, já que o I/O não seria mais sinalizado (porque deveria? a operação já foi concluída!).

Uma colinha da M$ de como deve ser feito o tratamento:


Após essa correção no projeto as coisas começaram a funcionar normalmente.

A BitForge fez a alteração em um fork próprio da hidapi e enviou o pull request para os mantenedores oficiais da hidapi, a signal11. Esta é mais uma lição de que, em se tratando de I/O, as coisas difíceis que o kernel às vezes faz lá embaixo acabam refletindo aqui em cima. Às vezes até na própria API!
