---
date: "2010-02-08"
title: Restaurando o registro
categories: [ "draft", "blog" ]
---
Algumas ferramentas viram essenciais quando o importante é tempo. As minhas favoritas são: [Visual Studio](http://www.microsoft.com/exPress/) e [batch](http://www.microsoft.com/WINDOWS/). Com esses dois eu faço virtualmente qualquer coisa que preciso em pouquíssimo tempo. É lógico que, na ausência dessas, alternativas são bem-vindas, como [Notepad++](http://notepad-plus.sourceforge.net/uk/site.htm), [viM](http://www.vim.org/), [grep](http://gnuwin32.sourceforge.net/), [cygwin](http://www.cygwin.com/).

Ontem tive que resolver uma "situação" no cliente, e graças ao bom Deus (ele também é programador) existia um Notepad++ na bagagem que levávamos. Além, é claro, do Excel e do sistema batch do Windows.

O problema consistia basicamente em usar a saída do [RegMon](http://technet.microsoft.com/en-us/sysinternals/bb896652.aspx) para identificar e restaurar algumas modificações que danificavam a instalação do Internet Explorer. O sistema de reparo do IE não existia no cliente, pois ele estava sem Service Pack (bem-vindo ao mundo real), mas podíamos nos guiar através dele na nossa máquina virtual para saber o que faríamos. O estrago era feito durante o registro e/ou desregistro de um componente COM.

<blockquote>_Aliás, não, eu não preciso usar o onipresente e onipotente Process Monitor para resolver um detalhezinho no registro. Você talvez precise, já que a Microsoft já tirou o Reg e o File de circulação._</blockquote>

Para iniciar, filtramos os resultados do RegMon para apenas capturar escritas no registro, não importando se falharam ou deram resultado.

![Filtro no RegMon](http://i.imgur.com/Fz9QRP1.png)

A partir disso executamos o registro e desregistro do componente, além da restauração do IE6, responsável por limpar a bagunça. O processo responsável por registrar componentes é o **regsvr32** e o responsável por limpar a bagunça, **rundll32**.

![Restauração do IExplore](http://i.imgur.com/Ps7V57G.png)

Tendo a saída do RegMon exportada para formato texto, abrimos no Excel e filtramos o conteúdo pelo nome do processo. Note que existem duas instâncias de regsvr32 para usar, pois não sabemos em qual delas é danificado o registro.

![Filtro no Excel](http://i.imgur.com/iEB0YQJ.png)

Para cada um dos filtros copiamos apenas o endereço da chave alterada para dois arquivos texto: regsvr32.txt e ierestore.txt. Usaremos esse primeiro para encontrar ocorrências no segundo, provando que um modifica o que o outro consertou.

Existe um comando muito simplório em batch Windows que é o aplicativo **find**. Através dele podemos encontrar a ocorrência de uma string em um arquivo. Para transformar todas aquelas linhas do registro do arquivo regsvr32 em comandos find poderíamos elaborar algumas colunas no Excel ou usar o Notepad++ e suas macros, mais rápidas.

Para quem não conhece macros, saiba que elas são muito úteis. Às vezes até mais úteis que "regexes", pois não é necessário pensar muito na expressão a ser usada. Macros apenas repetem os movimentos do teclado que fazemos enquanto as estamos gravando. Por exemplo, eu tenho o meu monte de linhas de registro assim:

    
    HKLM\SOFTWARE\Microsoft\Cryptography\RNG
    HKLM\SOFTWARE\Microsoft\Cryptography\RNG\Seed
    HKCR\AppID\{EE62DE09-3A23-46DB-8FA2-266088F329CD}
    HKCR\AppID\{EE62DE09-3A23-46DB-8FA2-266088F329CD}\(Default)
    HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Browser Helper Objects\{C322BA70-E3E7-4737-821C-D25378A3F830}
    HKCR\CLSID\{684E2452-19E1-42CC-9C93-A83044BA1AF2}
    HKCR\CLSID\{684E2452-19E1-42CC-9C93-A83044BA1AF2}\Programmable
    ...

Quero transformar cada linha em um comando find. Iniciou a gravação da macro no início da primeira linha e digito o seguinte (em pseudo-alguma-coisa):

find, espaço, abre aspas, end, fecha aspas, espaço, ierestore.txt, linha abaixo, home

    
    find "HKLM\SOFTWARE\Microsoft\Cryptography\RNG" ierestore.txt
    HKLM\SOFTWARE\Microsoft\Cryptography\RNG\Seed
    HKCR\AppID\{EE62DE09-3A23-46DB-8FA2-266088F329CD}

Pronto. Parar macro. Terei que repetir isso dois milhões de vezes até o final do arquivo. Ora, então mando o Notepad++ repetir a minha macro até o final do arquivo e adio minha tendinite para os próximos anos.

![Filtro no Notepad++](http://i.imgur.com/XOUfV9L.png)

Só preciso agora renomear meu arquivo para .bat e executar. Posso redirecionar a saída da tela para um terceiro arquivo, de onde irei formatar minha lista de entradas no registro que foram adulteradas por ambos os programas (o registro do componente COM e a restauração do Internet Explorer).

Nesse momento podemos ir tomar café. Bem melhor do que ficar horas e horas dando localizar, copiar, colar em todas as entradas do regsvr.

[![Tomando café](http://i.imgur.com/jBRCDmf.jpg)](http://www.caloni.com.br/blog/restauranto-o-registro/tomando-cafe/)

Terminada a operação, abrimos o terceiro arquivo, retiramos as entradas insignificantes (por exemplo, o gerador de sementes de números randômicos) e os cabeçalhos do comando, algo bem fácil já que se trata do mesmo arquivo.

    
    ---------- IERESTORE.TXT
    ...

A próxima tarefa seria analisar cada entrada e ver se ela é relevante. Essa parte foi manual, mas, encontrado um padrão, listamos rapidamente o que poderia estar dando errado e criamos uma lista de entradas para exportar do registro "sadio" a fim de gerar um .REG que corrigiria sistemas danificados.

Algumas passadas no Notepad++ para eliminar linhas duplicadas e algumas passadas pelo cérebro para eliminar chaves redundantes (chave dentro de chave) e tcharam!

    
    ...
    HKCR\Interface\{3050F2E3-98B5-11CF-BB82-00AA00BDCE0B}
    HKCR\Interface\{3050F2E5-98B5-11CF-BB82-00AA00BDCE0B}
    HKCR\Interface\{3050F32D-98B5-11CF-BB82-00AA00BDCE0B}
    HKCR\Interface\{3050F357-98B5-11CF-BB82-00AA00BDCE0B}
    HKCR\Interface\{3050F35C-98B5-11CF-BB82-00AA00BDCE0B}
    HKCR\Interface\{3050F37E-98B5-11CF-BB82-00AA00BDCE0B}
    HKCR\Interface\{3050F38C-98B5-11CF-BB82-00AA00BDCE0B}
    ...

O próximo passo para nossa obra-prima é outra macro que irá reproduzir o comando reg, que pode realizar operações no registro do Windows.

    
    ...
    reg export HKCR\Interface\{3050F240-98B5-11CF-BB82-00AA00BDCE0B} 3050F240-98B5-11CF-BB82-00AA00BDCE0B.reg
    reg export HKCR\Interface\{3050F25A-98B5-11CF-BB82-00AA00BDCE0B} 3050F25A-98B5-11CF-BB82-00AA00BDCE0B.reg
    reg export HKCR\Interface\{3050F25E-98B5-11CF-BB82-00AA00BDCE0B} 3050F25E-98B5-11CF-BB82-00AA00BDCE0B.reg
    reg export HKCR\Interface\{3050F2E3-98B5-11CF-BB82-00AA00BDCE0B} 3050F2E3-98B5-11CF-BB82-00AA00BDCE0B.reg
    reg export HKCR\Interface\{3050F2E5-98B5-11CF-BB82-00AA00BDCE0B} 3050F2E5-98B5-11CF-BB82-00AA00BDCE0B.reg
    reg export HKCR\Interface\{3050F32D-98B5-11CF-BB82-00AA00BDCE0B} 3050F32D-98B5-11CF-BB82-00AA00BDCE0B.reg
    ...

E o último passo é juntar toda essa galera em um arquivo só.

    
    copy *.reg ierestore.reg

Claro, não se esqueça de retirar os cabeçalhos duplicados (Windows Registry Editor Version X.XX). E Voilà! Fácil, não? Não?! Bom, então é por isso que eu sou bem pago =)
