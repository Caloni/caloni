---
date: 2019-03-06T21:33:15-03:00
title: "Debug Remoto no Visual Studio 2010 ou Superior"
categories: [ "draft", "code" ]
desc: "Remote Debugger disponível em qualquer instalação do Visual Studio. Use-o para depurar serviços, por exemplo."
---
Já escrevi sobre [debug remoto no finado C++ Builder](/debug-remoto-no-c-builder), sobre [como usar o msvcmon.exe no VS 2003 e o msvsmon.exe no 2010+](/debugger-remoto-do-visual-studio). Sobre [como depurar um serviço quando a máquina está para desligar](/depurando-ate-o-ultimo-segundo), e até sobre [depurar através de um servidor de símbolos](/depurando-ate-o-fim-do-mundo-e-de-volta-de-novo-source-server-com-github). Está na hora de tornar a depuração mais simples para programadores de serviços Win32.

Resumo dos comandos:

```
Busca do pacote de debug:
c:\>dir /s /b "Remote Debugger"
Executável:
C:\Tools\Remote Debugger\x64\msvsmon.exe
Argumentos:
/noauth /anyuser /timeout 99999999 /silent
Serviço:
C:\Tools\nssm.exe install Msvcmon
```

Hoje em dia, às vésperas do Visual Studio 2019, espero que todo mundo use pelo menos o Visual Studio 2010 porque a partir dessa versão tornou-se muito fácil depurar remotamente, pois um pacote feito para isso já é instalado junto do Visual Studo. É uma pasta que basta copiar e colar na máquina-alvo. Para encontrá-la basta digitar "Remote Debugger" dentro do Program Files.

![](https://i.imgur.com/bE6YxtY.png)

Copie essa pasta para a máquina onde estará os processos que deseja depurar e escolha sua arquitetura (x86, x64, i64), pois cada uma possui uma sub-pasta com os mesmos arquivos. Executa uma vez o msvsmon.exe dentro de uma delas e ele irá configurar para você o firewall do Windows. Feito isso e configurando através da janela que aparece o resto dos parâmetros basta atachar o processo ou iniciá-lo remotamente pela configuração do seu projeto no Visual Studio.

![](https://i.imgur.com/hjjz55J.png)

![](https://i.imgur.com/bA4u3NZ.png)

Mas este artigo não é sobre isso, é um pouco mais fundo: depurar serviços. Eles rodam na conta de sistema e muitas vezes é preciso depurá-los antes ou depois do logon na máquina. Às vezes é um teste sob as condições de sistema, o que é igualmente importante. Seja como for a maneira de fazer isso com o msvsmon.exe é transformá-lo também em um serviço. Para isso usaremos o [NSSM](https://nssm.cc/): o Non-Sucking Service Manager. Copie ele para a mesma máquina e o executa com o comando install <nome-do-serviço>. Os campos principais são os mais importantes.

![](https://i.imgur.com/bU6sq33.png)

Se você digitar msvsmon.exe /h ou algo do gênero irá encontrar os parâmetros que precisa:

![](https://i.imgur.com/4uyf5t7.png)

![](https://i.imgur.com/yEpsIR5.png)

Obs.: Eu costumo executar sem segurança alguma, pois minhas máquinas de teste são VMs locais e o perigo de vulnerabilidade não é menor do que minha própria máquina real.
