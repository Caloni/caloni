---
categories: [ "code" ]
date: "2019-01-06"
tags: [ "draft",  ]
title: "Bug no Boost Asio usando função AcceptEx do Winsock"
---
Depois de um mês de correção e mais um ou dois meses preparando um compilado do que ocorreu no software que estamos mantendo, foi descoberta uma situação muito peculiar que ocorre tanto em Windows XP quanto no Windows 10, mas que no 10 tem uma correção bem-educada e no XP... bom, nem tanto.

O problema ocorreu em um uso padrão do Boost.Asio de modo assíncrono. Sem querer entrar muito em código nesse momento -- que teve como base nosso projeto de servidor de requisições mais rápido do universo, o motherforker -- se trata apenas de um listening que usa spawn de um lambda para tratar os accepts e dentro dele cria processos, redirecionando sua entrada e saída.

    // pseudocode
    void Acceptor::doAccept()
    {
        while(!isStopping())
        {
            async_accept();
            spawn(Acceptor::createProcessGetOutputAndSendBack);
        }
    }

Nas entranhas do Boost.Asio na implementação para Windows o accept utiliza a API AcceptEx, que já cria o socket cliente antes mesmo da conexão ser fechada. Se trata de uma operação de IO assíncrono como os que tem no Windows: faz tudo que é necessário fazer e é responsabilidade do programa verificar se houve IO (de maneira síncrona ou assíncrona). No caso do Asio a maneira de verificar é via checagem do handle de completion durante os momentos de idle do ioservice.

    BOOL AcceptEx(
      SOCKET       sListenSocket,
      SOCKET       sAcceptSocket, // <--- socket cliente já criado
      PVOID        lpOutputBuffer,
      DWORD        dwReceiveDataLength,
      DWORD        dwLocalAddressLength,
      DWORD        dwRemoteAddressLength,
      LPDWORD      lpdwBytesReceived,
      LPOVERLAPPED lpOverlapped
    );

Quando há uma nova conexão o método createProcessGetOutputAndSendBack lê dados do socket cliente como um comando a ser executado e utiliza a API CreateProcess passando esse comando. A saída desse processo criado é capturada via saída-padrão. Para isso é usada a flag de herança de handles e handles de arquivos (poderiam ser pipes) são usados para enviar entrada, capturar saída, etc.

    BOOL CreateProcessA(
      LPCSTR                lpApplicationName,
      LPSTR                 lpCommandLine,
      LPSECURITY_ATTRIBUTES lpProcessAttributes,
      LPSECURITY_ATTRIBUTES lpThreadAttributes,
      BOOL                  bInheritHandles, // <--- flag de herança de handles
      DWORD                 dwCreationFlags,
      LPVOID                lpEnvironment,
      LPCSTR                lpCurrentDirectory,
      LPSTARTUPINFOA        lpStartupInfo,
      LPPROCESS_INFORMATION lpProcessInformation
    );
    
    // usando flags de uso de entrada/saída padrão
    STARTUPINFO si = { sizeof(si) };
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = CreateFileA(inputTempFilePath, GENERIC_READ, 0, &sa, OPEN_EXISTING, 0, NULL);
    si.hStdOutput = CreateFileA(outputTempFilePath, GENERIC_WRITE, FILE_SHARE_READ, &sa, CREATE_ALWAYS, 0, NULL);
    si.hStdError = si.hStdOutput;

Após o término do processo a saída estará no arquivo aberto em si.hStdOutput. Basta abri-lo para leitura e enviar seu conteúdo via socket para o cliente. O trabalho dessa conexão termina por aí.

O que não estava previsto é que junto da herança dos handles vai também handles indesejados. Como o de "\Device\Afd", que é um recurso usado na comunicação do winsock. Ao usar as funções síncronas e tradicionais do winsock, que constitui em criar o socket server, dar listen e no accept o socket cliente ter sido criado, o AcceptEx exige já um socket cliente criado, o que é feito no sample da Microsoft com a função socket e no Boost.Asio com a duplicação do socket existente (que também foi criado via socket function).

    ClientSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

Esses dois sockets são herdáveis por default (implementação da função socket) e são representados pelos handles listados no Process Explorer como já visto, pelo nome "\Device\Afd". O contador de handles é aumentado a partir da criação do processo-filho e esses dois handles aparecem em ambos os processos.

Até aí tudo bem. O problema na verdade ocorre no segundo request enviado quando o primeiro request não terminou (e.g. o primeiro request é um notepad.exe que irá demorar e o segundo request um "cmd /c dir", que executa e já volta com a saída). Nessa situação todos os sockets criados até aqui -- incluindo o cliente do primeiro request -- são herdados para o segundo processo-filho, e por questões que estão além do escopo desse estudo, mas que poderão ser verificados ao se analistar os drivers das camadas de TDI do Windows (kernel mode), o send da saída do segundo request para o socket cliente fica travado até a saída do primeiro processo-filho, onde ocorre dos handles serem fechados.

É uma situação complexa, que depende de várias variáveis, mas ela ocorre, se todas as variáveis ocorrerem ao mesmo tempo. Um resumo:

 - Criação do socket cliente com a função socket.
 - Uso do AcceptEx para aceitar conexões.
 - Criação de process-filho com flag de herança de handles habilitada.
 - Processo-filho do primeiro request ainda em execução.
 - Recebimento do segundo request e criação do segundo processo-filho.
 - Escrita no socket cliente do segundo request enquanto o primeiro request ainda não foi finalizado.
 - BUG: Cliente do segundo request não recebe sua resposta.
 - RESULTADO ESPERADO: Que o cliente do primeiro request não interferisse no segundo.
 - Detalhe: Cliente do segundo requeste recebe eventualmente sua resposta após o primeiro request terminar.

A primeira solução para evitar handles herdáveis que não são desejáveis é proposta pelo Raymond Chen em seu blog: usar as API InitializeProcThreadAttributeList e UpdateProcThreadAttribute. Com isso é possível especificar quais handles podem ser herdados pelo processo-filho, e obviamente iremos colocar na lista apenas os arquivos de entrada e saída padrão (obs: não duplicar saída-padrão com erro-padrão quando ambos são o mesmo arquivo/handle).

As API InitializeProcThreadAttributeList e UpdateProcThreadAttribute não existem no Windows XP, o que quer dizer que isso exige uma segunda solução, que eu considerei antes de achar a terceira solução que teria que ser ad hoc: criar um processo-neto, sendo que o filho não receberá os handles herdados, mas irá criar o neto herdando os arquivos de entrada e saída padrão, enviando a saída de volta por um método à parte (ex: usando o nome de um arquivo em comum).

A terceira solução encontrada durante a compilação deste artigo é usar em vez da função socket, que não dá o controle sobre herança de handle, a função WSASocketW, onde existe um argumento dwFlags em que é possível passar o valor WSAFLAGNOHANDLEINHERIT (0x80), onde o handle do socket não será criado com a flag de herdável. Dessa forma apenas o socket cliente não se torna herdável e com isso o primeiro request não trava o segundo. A vantagem dessa correção é que ela é pontual no código e é de uma API já antiga, portanto compatível com todos os Windows.

UPDATE: Na verdade a flag de não-herança do socket só passou a existir no Windows 7 com SP1, o que inviabiliza essa solução para Windows Vista e XP, como previamente foi dito.

Essas correções dizem respeito ao sample de uso do winsock como modelo server/client da própria Microsoft. Ele foi modificado em um repositório que criei para meus testes e poderá ser usado como correção de todos que tiverem o mesmo problema utilizando a API do Windows diretamente.

Já para o Boost.Asio será necessário um estudo de impacto e o envio de uma proposta de correção (ou uso de um patch em que a criação do socket cliente deve ser feita sem herança). Isso pode potencialmente quebrar o funcionamento de outros tipos de programas que dependem direta ou indiretamente da herança de todos os sockets, ou talvez o Boost.Asio tenha uma maneira educada de entregar o controle da criação de sockets dependente de implementação. Eu não sei. Este é um próximo passo da pesquisa.

UPDATE: Embora use a função WSASocketW o Boost.Asio não suporta a parametrização das flags, e sua implementação não é sobrecarregável, fazendo parte do namespace socketopt. Foi criado um issue no GitHub do projeto Boost.Asio para ver os comentários e colocações da equipe. No aguardo.
