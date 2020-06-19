---
categories: [ "code" ]
date: "2017-06-13"
tags: [ "draft",  ]
title: "Debugger remoto do Visual Studio"
---
Então você está quebrando a cabeça para descobrir por que seu código não faz o que deveria fazer? Então você é desses que acha que é melhor ficar imaginando com um bloquinho de papel na mão do que colocar logo a mão na massa e ver exatamente o código passando pelo processador? Talvez você mude de ideia ao ver como é ridiculamente fácil depurar código em uma máquina remota, seja uma VM ou a máquina do cliente. Neste post vou ensinar a maneira mais antiga e a mais nova que conheço de usar o depurador do Visual Studio. Vamos usar a versão 2003 e a versão 2017 RC.

Há muito tempo atrás eu falei sobre o depurador remoto do C++ Builder, na época a ferramenta que eu mais utilizava para programar. Hoje disparado é o Visual Studio, já faz mais de uma década. Desde o VS2003 tem sido muito simples depurar remotamente. Tão simples que eu realmente esqueci que talvez algumas pessoas não saibam o quanto é útil essa ferramenta no dia-a-dia.

É possível depurar qualquer executável, tendo seu código-fonte ou não. A diferença é que sem código você terá que olhar o assembly e se for compilado como release você pode olhar o código mas ele não fará muito sentido em alguns momentos (onde estão minhas variáveis locais?). O melhor dos mundos, é claro, é depurar um executável que você tenha os símbolos, o código e esteja compilado em debug. Daí o código irá falar com você da maneira mais fácil.

É simples de achar essa opção no projeto em qualquer Visual Studio. Vá nas opções do projeto, Linker e irá encontrar em algum lugar sobre a geração do PDB. Não tenha medo de explorar as opções do projeto. Elas refletem como o XML do projeto muda (sim, é um XML). Se estiver querendo saber exatamente como ele muda, use um controle de fonte e vá experimentando.

Para depurar pelo Visual Studio 2003 há um programa chamado msvcmon.exe que deve ser copiado e executado na máquina-alvo. Ele é um executável que pode ser copiado para qualquer lugar. Junto dele devem estar duas DLLs: a natdbgdm.dll e a natdbgtlnet.dll. Se você tiver o VS2003 instalado deve achar esses arquivos em algum lugar, ou no pior dos casos no CD de instalação. Por via das dúvidas sempre há um link amigo na internet para ajudar alguém a achar o que precisa.

Copiados esses arquivos na máquina-alvo é necessário copiar também o executável. Afinal de contas, ele irá executar remotamente! O arquivo PDB, no entanto, você só precisa guardar com você. Lembre-se que toda recompilação em Debug altera de maneira significativa o PDB, então não recompile seu projeto enquanto estiver depurando. Se for fazê-lo, troque o executável na máquina-alvo.

A primeira execução de toda ferramenta, seu help, irá nos mostrar o seguinte no msvcmon:


Minhas opções favoritas são -tcpip -anyuser -timeout -1, o que libera o acesso a qualquer usuário direto por TCP/IP e o timeout da execução é infinito. All access no limits =)


Agora no Visual Studio 2003 vá em Debug, Processes (ou Ctrl+Alt+P para os íntimos) e escolha a opção de Transport como TCP/IP, digite o IP... explore sua ferramenta, poxa!

Depois de conectar remotamente por essa janela o console do msvcmon irá mostrar que usuário se logou:


Para configurar o início da depuração remota pelo próprio projeto você terá que ir nas opções de debug dele e mexer em Remote Settings. Para começar os problemas é sempre bom lembrar que projetos compilados como debug precisam das DLLs de runtime do Visual Studio que sejam debug. Mas você já sabe disso.

Depois que tudo isso estiver OK é só iniciar seus processos remotamente em modo de depuração ou atachar pela primeira janela que vimos.

Agora você deve estar se perguntando: "mas esse VS é muito velho! e os mais novos?"

Bom, desde o VS 2010 e até o VS2017 RC essa ferramenta está disponível na pasta de instalação, mudou um pouco de cara e você pode encontrar procurando por "remote". No Caso do VS mais novo que tenho em mãos aqui, o 2017 RC, existe já uma pasta pronta para copiar e colar na máquina-alvo, em Common7, IDE, Remote Debugger. Há duas pastas disponíveis: x86 e x64. Dependendo do tipo de compilação que deseja realizar (e de qual o seu executável) copie uma das duas, rode o executável da pasta e apenas configure.
