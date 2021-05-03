---
categories:
- blog
date: '2017-01-17'
tags:
- draft
title: Warning de nível 4
---

Você já colocou aquele seu projeto favorito em /W4? Por padrão, o Visual Studio cria seus projetos com o nível de warnings e 3, porque o nível 4 é muito, muito chato. No entanto, algumas vezes ele serve para que seu código não fique apenas correto, mas bem documentado e apresentável. Vamos tentar?

```log
1>------ Build started: Project: tioserver, Configuration: Debug x64 ------
1>  pch.cpp
1>  using Boost version 1_62
1>  tioclient.c
1>cl : Command line warning D9030: '/Gm' is incompatible with multiprocessing; ignoring /MP switch
1>  TioTcpSession.cpp
1>  TioTcpServer.cpp
1>  TioPython.cpp
1>  tio.cpp
1>  ContainerManager.cpp
1>  Command.cpp
1>  Generating Code...
1>  tioserver.vcxproj -> C:\Projects\tiodb\server\tio\..\..\bin\x64\Debug\tio.exe
1>  tioserver.vcxproj -> ..\..\bin\x64\Debug\tio.pdb (Full PDB)
========== Build: 1 succeeded, 0 failed, 0 up-to-date, 0 skipped ==========
```

OK, este foi o nível 3 do tioserver, o projeto principal do [tiodb](https://github.com/tiodb), uma ferramenta para manter contêineres assináveis na memória e acessíveis via socket. Note que já existe um warning, mas vamos ignorar por enquanto. O objetivo aqui é descobrir quais os warnings mais comuns do projeto que você vai escolher. Vejamos o meu:

![](http://i.imgur.com/XjbqVh9.png)

```log
1>------ Rebuild All started: Project: tioserver, Configuration: Debug x64 ------
1>  pch.cpp
1>  using Boost version 1_62
1>  tioclient.c
1>c:\projects\tiodb\client\c\tioclient.c(218): warning C4701: potentially uninitialized local variable 'start' used
1>cl : Command line warning D9030: '/Gm' is incompatible with multiprocessing; ignoring /MP switch
1>  TioTcpSession.cpp
1>c:\projects\tiodb\server\tio\tiotcpsession.h(299): warning C4458: declaration of 'eventName' hides class member
1>  c:\projects\tiodb\server\tio\tiotcpsession.h(295): note: see declaration of 'tio::EXTRA_EVENT::eventName'
1>c:\projects\tiodb\server\tio\logdb.h(213): warning C4456: declaration of 'i' hides previous local declaration
1>  c:\projects\tiodb\server\tio\logdb.h(200): note: see declaration of 'i'
1>c:\projects\tiodb\server\tio\tiotcpserver.h(81): warning C4456: declaration of 'handle' hides previous local declaration
1>  c:\projects\tiodb\server\tio\tiotcpserver.h(77): note: see declaration of 'handle'
1>c:\projects\tiodb\server\tio\tiotcpserver.h(413): warning C4456: declaration of 'b' hides previous local declaration
1>  c:\projects\tiodb\server\tio\tiotcpserver.h(316): note: see declaration of 'b'
1>c:\projects\tiodb\server\tio\tiotcpsession.cpp(127): warning C4457: declaration of 'key' hides function parameter
1>  c:\projects\tiodb\server\tio\tiotcpsession.cpp(114): note: see declaration of 'key'
1>  TioTcpServer.cpp
1>c:\projects\tiodb\server\tio\tiotcpsession.h(299): warning C4458: declaration of 'eventName' hides class member
1>  c:\projects\tiodb\server\tio\tiotcpsession.h(295): note: see declaration of 'tio::EXTRA_EVENT::eventName'
1>c:\projects\tiodb\server\tio\logdb.h(213): warning C4456: declaration of 'i' hides previous local declaration
1>  c:\projects\tiodb\server\tio\logdb.h(200): note: see declaration of 'i'
1>c:\projects\tiodb\server\tio\tiotcpserver.h(81): warning C4456: declaration of 'handle' hides previous local declaration
1>  c:\projects\tiodb\server\tio\tiotcpserver.h(77): note: see declaration of 'handle'
1>c:\projects\tiodb\server\tio\tiotcpserver.h(413): warning C4456: declaration of 'b' hides previous local declaration
1>  c:\projects\tiodb\server\tio\tiotcpserver.h(316): note: see declaration of 'b'
1>c:\projects\tiodb\server\tio\tiotcpserver.cpp(404): warning C4456: declaration of 'b' hides previous local declaration
1>  c:\projects\tiodb\server\tio\tiotcpserver.cpp(300): note: see declaration of 'b'
1>c:\projects\tiodb\server\tio\tiotcpserver.cpp(563): warning C4456: declaration of 'b' hides previous local declaration
1>  c:\projects\tiodb\server\tio\tiotcpserver.cpp(300): note: see declaration of 'b'
1>c:\projects\tiodb\server\tio\tiotcpserver.cpp(596): warning C4456: declaration of 'b' hides previous local declaration
1>  c:\projects\tiodb\server\tio\tiotcpserver.cpp(300): note: see declaration of 'b'
1>c:\projects\tiodb\server\tio\tiotcpserver.cpp(620): warning C4456: declaration of 'b' hides previous local declaration
1>  c:\projects\tiodb\server\tio\tiotcpserver.cpp(300): note: see declaration of 'b'
1>c:\projects\tiodb\server\tio\tiotcpserver.cpp(643): warning C4456: declaration of 'b' hides previous local declaration
1>  c:\projects\tiodb\server\tio\tiotcpserver.cpp(300): note: see declaration of 'b'
1>c:\projects\tiodb\server\tio\tiotcpserver.cpp(661): warning C4456: declaration of 'b' hides previous local declaration
1>  c:\projects\tiodb\server\tio\tiotcpserver.cpp(300): note: see declaration of 'b'
1>c:\projects\tiodb\server\tio\tiotcpserver.cpp(2451): warning C4456: declaration of 'value' hides previous local declaration
1>  c:\projects\tiodb\server\tio\tiotcpserver.cpp(2338): note: see declaration of 'value'
1>  TioPython.cpp
1>  tio.cpp
1>c:\projects\tiodb\server\tio\tiotcpsession.h(299): warning C4458: declaration of 'eventName' hides class member
1>  c:\projects\tiodb\server\tio\tiotcpsession.h(295): note: see declaration of 'tio::EXTRA_EVENT::eventName'
1>c:\projects\tiodb\server\tio\logdb.h(213): warning C4456: declaration of 'i' hides previous local declaration
1>  c:\projects\tiodb\server\tio\logdb.h(200): note: see declaration of 'i'
1>c:\projects\tiodb\server\tio\tiotcpserver.h(81): warning C4456: declaration of 'handle' hides previous local declaration
1>  c:\projects\tiodb\server\tio\tiotcpserver.h(77): note: see declaration of 'handle'
1>c:\projects\tiodb\server\tio\tiotcpserver.h(413): warning C4456: declaration of 'b' hides previous local declaration
1>  c:\projects\tiodb\server\tio\tiotcpserver.h(316): note: see declaration of 'b'
1>  ContainerManager.cpp
1>  Command.cpp
1>  Generating Code...
1>  tioserver.vcxproj -> C:\Projects\tiodb\server\tio\..\..\bin\x64\Debug\tio.exe
1>  tioserver.vcxproj -> ..\..\bin\x64\Debug\tio.pdb (Full PDB)
========== Rebuild All: 1 succeeded, 0 failed, 0 skipped ==========
```

Vamos ordenar e capturar apenas o código desses warnings para ver quantos ocorrem e quais os mais comuns:

```vim
sort
s/c:\\.*: \(warning C[0-9]\+\).*$/\1/
sort u
```

E a resposta é:

```log
warning C4456: declaration of 'identifier' hides previous local declaration
warning C4457: declaration of 'identifier' hides function parameter
warning C4458: declaration of 'identifier' hides class member
warning C4701: potentially uninitialized local variable 'name' used
```

Apenas quatro. Tão comuns que [a maioria](https://msdn.microsoft.com/en-us/library/mt694070.aspx) está até em ordem numérica e diz respeito a repetição de nomes em escopos diferentes, o que esconde os nomes do escopo anterior, mais amplo. O outro, o [C4701](https://msdn.microsoft.com/en-us/library/1wea5zwe.aspx), pode ser mais problemático, já que ele representa uma variável que potencialmente não foi inicializada, fonte comum daqueles erros de "como é que essa variável virou isso?".

Felizmente só temos em um ponto do código:

```cpp
//
// Contract: 
//		if no timeout, it will hang until all bytes are returned
//		if timeout is set, we can return less bytes than requested
//
int socket_receive(SOCKET socket, void* buffer, int len, const unsigned* timeout_in_seconds)
{
	int ret = 0;
	char* char_buffer = (char*)buffer;
	int received = 0;
	time_t start;
	int time_left;

#if _WIN32
	FD_SET recvset;
	struct timeval tv;
#endif

#ifdef _DEBUG
	memset(char_buffer, 0xFF, len);
#endif

    // se esse if não for verdadeiro, start fica com valor indefinido
	if(timeout_in_seconds)
		start = time(NULL);

	while(received < len)
	{
		if(timeout_in_seconds)
		{
            // C4701: potentially uninitialized local variable 'start' used
			time_left = *timeout_in_seconds - (int)(time(NULL) - start);
```

A correção é simples: inicialize a p\*\*\*\*\* das suas variáveis zero (ou determine qual o comportamento no caso else).

Vamos dar uma olhada em um dos outros warnings:

```cpp
    string containerName = container->GetName();
    unsigned handle = session->RegisterContainer(containerName, container);
    
    if(session->UsesBinaryProtocol())
    {
        // warning C4456: declaration of 'identifier' hides previous local declaration
        unsigned handle = session->RegisterContainer(containerName, container);
```

OK, isso é meio feio. A variável handle tinha acabado de ser criada logo antes da entrada do if. A não ser que sejam de fato variáveis distintas no código (apenas analisando a função inteira) elas poderiam ser reaproveitadas em apenas uma (até porque possuem o mesmo tipo). E se forem variáveis distintas... bem, coloque nomes distintos =)

E aqui termina mais uma sessão de "e se eu abrir mais os warnings do meu código". Espero que tenha aproveitado.