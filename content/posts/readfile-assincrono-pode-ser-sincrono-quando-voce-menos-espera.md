---
categories:
- draft
- code
date: '2017-01-16'
title: ReadFile assíncrono pode ser síncrono quando você menos espera
---

Ano passado tive alguns problemas em um projeto que se comunicava com um dispositivo em firmware pela USB. Estávamos utilizando uma biblioteca open source do GitHub que parecia estar bem testada e mantida. Porém, não exatamente para nossos objetivos.

O problema da lib [hidapi](https://github.com/signal11/hidapi) era que a comunicação usb era feita de forma assíncrona. Isso no Windows é feito com a mesma função de I/O (ReadFile/WriteFile) só que passando um argumento opcional chamado de overlapped. Esse argumento é um ponteiro para uma estrutura que irá ser preenchida assim que o I/O for concluído. E quando é isso? Deve-se esperar pelo handle ser sinalizado (em outras palavras, dando um Sleep ou WaitForSingleObject neste handle).

O funcionamento padrão via overlapped é bem simples: faça a operação de I/O (passando a estrutura) e verifique o retorno. Ele deve ser FALSE e o retorno do próximo GetLastError deve ser ERROR_IO_PENDING. Bom, descrevendo a operação ela não parece ser tão intuitiva. Mas funciona:

```cpp
if (!ReadFile(hFile,
                 pDataBuf,
                 dwSizeOfBuffer,
                 &NumberOfBytesRead,
                 &osReadOperation )
   {
      if (GetLastError() != ERROR_IO_PENDING)
      {
         // Some other error occurred while reading the file.
         ErrorReadingFile();
         ExitProcess(0);
      }
      else
         // Operation has been queued and
         // will complete in the future.
         fOverlapped = TRUE;
   }
```

A questão que nós encontramos nesse projeto apenas aconteceu porque após a operação de I/O assíncrona a thread responsável por retornar o resultado ficava em wait eterno ou dava timeout. Ambas as situações são normais e esperadas. Ficar aguardando para sempre um device acontece quando este simplesmente não responde com nenhum dado. E dar timeout acontece quando não queremos aguardar o device para sempre (WaitForSingleObject(handle, 1000), por exemplo, daria timeout depois de 1 segundo, ou 1000 milissegundos).

O motivo da thread nunca retornar (ou dar timeout), porém, não estava em nenhuma dessas situações. Ao monitorar o tráfego usb se verificou que o device respondia em tempo hábil. O problema estava mais embaixo (ou mais em cima): a hidapi não se comportava conforme o MSDN mandava. Há uma situação não-mapeada nessa lib.

Erros ao chamar a API do Win32 são comuns exatamente porque esta é uma lib arcaica, pouco intuitiva com diferentes tipos de exceções. No caso de uma operação assíncrona com overlapped, se você ler as tantas páginas da [função ReadFile](https://msdn.microsoft.com/en-us/library/windows/desktop/aa365467(v=vs.85).aspx), por exemplo, vai acabar encontrando um adendo escondido no meio da documentação:

![](http://i.imgur.com/sJDJHii.png)

Este [adendo](https://support.microsoft.com/en-us/kb/156932) possui a informação que ninguém ainda sabia porque... porque a Microsoft é uma p\*\*\*, oras =)

> If, on the other hand, an operation is completed immediately, then &NumberOfBytesRead passed into ReadFile is valid for the number of bytes read. In this case, ignore the OVERLAPPED structure passed into ReadFile; __do not use it with GetOverlappedResult or WaitForSingleObject.__

Ou seja, em caso da função ReadFile (ou WriteFile) retornar TRUE em uma operação assíncrona/overlapped, isso quer dizer que a operação foi concluída com sucesso de forma síncrona, não sendo necessário aguardar o I/O ser concluído. Na verdade, é um pouco mais específico: o WaitForSingleObject __não deve ser chamado__. No nosso caso, ao chamá-lo, criávamos uma espera eterna, já que o I/O não seria mais sinalizado (porque deveria? a operação já foi concluída!).

Uma colinha da M$ de como deve ser feito o tratamento:

```cpp
   if (!ReadFile(hFile,
                 pDataBuf,
                 dwSizeOfBuffer,
                 &NumberOfBytesRead,
                 &osReadOperation )
   {
      if (GetLastError() != ERROR_IO_PENDING)
      {
         // Some other error occurred while reading the file.
         ErrorReadingFile();
         ExitProcess(0);
      }
      else
         // Operation has been queued and
         // will complete in the future.
         fOverlapped = TRUE;
   }
   else
      // Operation has completed immediately.
      fOverlapped = FALSE;

   if (fOverlapped)
   {
      // Wait for the operation to complete before continuing.
      // You could do some background work if you wanted to.
      if (GetOverlappedResult( hFile,
                               &osReadOperation,
                               &NumberOfBytesTransferred,
                               TRUE))
         ReadHasCompleted(NumberOfBytesTransferred);
      else
         // Operation has completed, but it failed.
         ErrorReadingFile();
   }
   else
      ReadHasCompleted(NumberOfBytesRead);
```

Após essa correção no projeto as coisas começaram a funcionar normalmente.

A BitForge fez a alteração em [um fork próprio](https://github.com/bitforgebr/hidapi/commit/132e03f37e8ab8c95ee264e1cfbeef6b2ed39a5b) da hidapi e enviou o __pull request__ para os mantenedores oficiais da hidapi, a signal11. Esta é mais uma lição de que, em se tratando de I/O, as coisas difíceis que o kernel às vezes faz lá embaixo acabam refletindo aqui em cima. Às vezes até na própria API!