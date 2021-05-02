---
date: "2007-06-20"
title: "Introdução ao Debugging Tools for Windows (usando o Logger para monitorar APIs)"
categories: [ "code" ]
---
O WinDbg é uma ferramenta obrigatória em uma das minhas mais divertidas tarefas aqui na Open: engenharia reversa de cavalos de tróia. Não tenho o código-fonte desses programas, não posso executá-los em minha própria máquina e não consigo fazer tudo que preciso usando apenas o depurador integrado do Visual Studio (como remontar o assembly do programa, por exemplo). Tudo isso faz do WinDbg a alternativa perfeita (senão uma das únicas). É um depurador que permite ser usado tanto através de janelas quanto através de comandos, o que permite um aprendizado em doses homeopáticas: comece com as janelas e aos poucos ganhe o controle total. Conseqüentemente cada dia aprendo um comando novo ou um novo uso para um comando que já conheço.

Abaixo um esboço de como o WinDbg se parece, com suas principais janelas. A de comandos é a da direita.

![Imagem ilustrativa das janelas do Windbg](/img/windbg.png)

Ele não está limitado apenas para engenharia reversa de código malévolo. Esse é o uso que eu faço dele. Meu amigo Thiago, por exemplo, resolve problemas em servidores que rodam código gerenciado com WinDbg. É a maneira ideal de depurar um problema em uma máquina onde o ambiente de desenvolvimento não está disponível nem pode ser instalado. Outro ponto relevante é que ele não depura apenas um programa em particular, mas pode ser usado para depurar um sistema inteiro. Chamado de kernel debugging, podemos usar esse modo de funcionamento para resolver os problemas que surgem logo depois de espetar algum periférico novo comprado na Santa Ifigênia.

Mas esse artigo não é apenas sobre o WinDbg. Ele não vem sozinho. É uma interface amigável para alguns depuradores linha de comando e outras ferramentas disponíveis no Debugging Tools for Windows, pacote disponível gratuitamente no sítio da Microsoft e atualizado geralmente de seis em seis meses. Nele podemos encontrar:

 - CDB: depurador que roda em user mode e é uma "linha de comando agradável" para um programador avançado.
 - NTSD: depurador que roda em user mode, da mesma forma que o CDB, mas também pode ser usado como um redirecionador de comandos para o depurador de kernel (logo abaixo). Existem algumas diferenças sutis entre esses dois depuradores (como o fato do NTSD não criar janelas quando usado como redirecionador), mas são diferenças que se aprendem no dia-a-dia.
 - KD: depurador que roda em kernel mode, pode analisar dados do sistema local ou depurar um sistema remoto conectado através de um cabo serial ou por meio de um pipe criado por uma máquina virtual. 

 Existem outros métodos mais avançados ainda para conseguir depurar uma máquina tão tão distante, por exemplo.

 - Logger: tracer de chamadas de funções da API. Pode ser usado para análise de performance ou para fazer o que eu faço com os trojans, que é dar uma olhada nas funções que eles chamam constantemente.
 - Logviewer: visualiza resultados gerados pelo Logger.

Existem ainda outras ferramentas, mas estas são as principais que costumo utilizar. Para saber como usá-las de acordo com suas necessidades recomendo a leitura de um pequeno tutorial para o WinDbg que vem junto da instalação, o kernel_debugging_tutorial.doc. Ele é apenas a introdução dos principais comandos e técnicas. Depois de ter dominado o básico, pode partir para o arquivo de ajuda, que detalha de forma completa todos os comandos, técnicas e ferramentas de todo o pacote: o debugger.chm. A maioria dos comandos que precisava encontrei usando essa ajuda ou em alguns blogs muito bons, como o Crash Dump Analysis. Porém, acredite: no WinDbg, você quase sempre vai encontrar o comando que precisa.

Para exemplificar um uso prático dessas ferramentas vamos usar o Logger para descobrir quais funções API estão sendo chamadas constantemente por um cavalo de tróia, uma coisa um tanto comum em ataques a bancos. Para tornar as coisas mais reais ainda vamos utilizar o código-fonte de um suposto cavalo de tróia usado em minhas apresentações:

    #include <windows.h>
    #include <shlwapi.h>
    
    int WINAPI WinMain(...)
    {
      CHAR wndTxt[MAX_PATH];
    
      while( true )
      {
        HWND fgWin = GetForegroundWindow();
        wndTxt[0] = 0;
    
        if( GetWindowText(...) )
        {
          if( StrStrI(wndTxt, "Fict Bank") )
          {
            MessageBox(fgWin, 
              "Hi! Like to be under attack?",
              "Free Trojan", 
              MB_OK);
            break;
          }
        }
      }
    
      ExitProcess(ERROR_SUCCESS);
    } 

Para compilar esse programa, você só precisa digitar os seguintes comandos em um console do Visual Studio:

    cl /c freetrojan.cpp
    link freetrojan.obj user32.lib shlwapi.lib

O logger.exe possui uma extensão que pode ser usada pelo WinDbg para usar os mesmos comandos a partir do depurador. Mas para tornar as coisas mais fáceis nesse primeiro contato iremos iniciar o programa através do próprio executável:

    logger freetrojan.exe

Irá aparecer uma janela onde selecionamos o conjunto de APIs que serão capturadas. Podemos manter todas as categorias selecionadas e mandar rodar usando o botão "Go". Aguarde o programa executar por um tempo para termos um pouco de dados para analisar. Em minhas análises reais eu geralmente deixo ele atacar, seja no sítio real do banco ou em uma armadilha. Depois do ataque posso confirmar qual a API que ele utilizou. Se quiser fazer isso nesse teste basta criar uma janela que contenha o texto "Fict Bank" em seu título. Após isso, podemos finalizar o processo pelo Gerenciador de Tarefas.

Mesmo após finalizá-lo ele continuará na lista de processos, como se tivesse travado. Na verdade, a parte injetada do Logger mantém o processo no ar, em um estado semi-morto (ou semi-vivo). Depois de finalizar o Logger fechando sua janela principal ambos os processos terminam e podemos ler o resultado da captura em uma pasta chamada LogExts criada por padrão no Desktop ou Área de Trabalho. Podemos dar uma olhada nos resultados através do visualizador de logs gerados, o Logviewer.

Algumas colunas do Logviewer são tão úteis que vale a pena mencioná-las:
    
 - Module: determina quem chamou a API, o próprio executável ou alguma DLL.
 - Call Duration: tempo em milissegundos que a chamada da função demorou.
 - API Function: o nome da função API que foi chamada.
 - Return Value: o retorno da chamada da função.

De quebra ele exibe todos os parâmetros das funções de acordo com o tipo, identificando inclusive quando se trata de uma enumeração ou define reservado. Essa "mágica" é feita interpretando os headers que ficam na pasta Debugging Tools for Windows, winext, manifest, tarefa executada pelo Logger no início.

O Debugging Tools é um pacote extremamente poderoso de ferramentas para programadores avançados. De maneira alguma conseguirei cobrir tudo que é possível fazer com essas ferramentas em apenas um blog e muito menos em um post. Porém, espero que essa pequena introdução seja o começo de uma série de artigos bem interessantes sobre debugging e uma série de testes realizados pelos meus leitores.
