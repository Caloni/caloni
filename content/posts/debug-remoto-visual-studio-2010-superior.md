---
date: "2019-03-06"
tags: [ "code", "draft",  ]
title: "Debug Remoto no Visual Studio 2010 ou Superior"
---
Já escrevi sobre debug remoto no finado C++ Builder, sobre como usar o msvcmon.exe no VS 2003 e o msvsmon.exe no 2010+. Sobre como depurar um serviço quando a máquina está para desligar, e até sobre depurar através de um servidor de símbolos. Está na hora de tornar a depuração mais simples para programadores de serviços Win32.

Resumo dos comandos:


Hoje em dia, às vésperas do Visual Studio 2019, espero que todo mundo use pelo menos o Visual Studio 2010 porque a partir dessa versão tornou-se muito fácil depurar remotamente, pois um pacote feito para isso já é instalado junto do Visual Studo. É uma pasta que basta copiar e colar na máquina-alvo. Para encontrá-la basta digitar "Remote Debugger" dentro do Program Files.

Copie essa pasta para a máquina onde estará os processos que deseja depurar e escolha sua arquitetura (x86, x64, i64), pois cada uma possui uma sub-pasta com os mesmos arquivos. Executa uma vez o msvsmon.exe dentro de uma delas e ele irá configurar para você o firewall do Windows. Feito isso e configurando através da janela que aparece o resto dos parâmetros basta atachar o processo ou iniciá-lo remotamente pela configuração do seu projeto no Visual Studio.

Mas este artigo não é sobre isso, é um pouco mais fundo: depurar serviços. Eles rodam na conta de sistema e muitas vezes é preciso depurá-los antes ou depois do logon na máquina. Às vezes é um teste sob as condições de sistema, o que é igualmente importante. Seja como for a maneira de fazer isso com o msvsmon.exe é transformá-lo também em um serviço. Para isso usaremos o NSSM: o Non-Sucking Service Manager. Copie ele para a mesma máquina e o executa com o comando install nome-do-serviço. Os campos principais são os mais importantes.

Mas este artigo não é sobre isso, é um pouco mais fundo: depurar serviços. Eles rodam na conta de sistema e muitas vezes é preciso depurá-los antes ou depois do logon na máquina. Às vezes é um teste sob as condições de sistema, o que é igualmente importante. Seja como for a maneira de fazer isso com o msvsmon.exe é transformá-lo também em um serviço. Para isso usaremos o NSSM: o Non-Sucking Service Manager. Copie ele para a mesma máquina e o executa com o comando install nome-do-serviço. Os campos principais são os mais importantes.

Se você digitar msvsmon.exe /h ou algo do gênero irá encontrar os parâmetros que precisa.

OBS: Eu costumo executar sem segurança alguma, pois minhas máquinas de teste são VMs locais e o perigo de vulnerabilidade não é menor do que minha própria máquina real.
