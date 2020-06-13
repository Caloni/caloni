---
categories: [ "blog" ]
date: "2008-01-14"
tags: [ "draft", "tools" ]
title: "Temas no WinDbg"
---
Desde a versão 6.4.7.2 que o WinDbg fornece uma subpasta chamada Themes, onde lá estão diversos workspaces configurados. Existe até um passo-a-passo de como organizar esses temas e escolher o seu favorito. Segue algumas dicas de como transformar corretamente sua área de trabalho para depuração (e mantê-la).

O WinDbg salva suas configurações no registro. Para apagar os valores previamente gravados, rode o seguinte comando:

    
    reg delete HKCU\Software\Microsoft\WinDbg

Você pode gravar um tema, rodar o WinDbg (sem parâmetros), ver se gosta do que viu, e tentar novamente. Quando estiver satisfeito com a aparência, fique com ela e comece o próximo passo.

Nas depurações do dia-a-dia algumas configurações devem estar sempre muito bem configuradas, para que torne seus momentos de desespero porque nada está funcionando mais agradáveis. Por isso, assim que escolher seu tema preferido trate de configurar os seguintes itens:

	
  * Diretórios de símbolos. Você pode começar com .symfix, que vai montar uma string padrão, e adicionar mais diretórios com .sympath+.

	
  * Diretórios de código-fonte. Coloque a raiz dos seus projetos principais. Com o tempo, se você mexe muito nos seus diretórios, é necessário fazer uma manutenção desse valor.

	
  * Diretórios de executáveis. Basicamente é o mesmo do diretório de símbolos.

Depois de configurar tudo isso, ajuste as janelas na melhor maneira e proporção que achar mais agradável. Esse será o último passo, pois depois você irá fechar o WinDbg e salvar o workspace, que a partir daí será o padrão sempre que abrir o depurador.



Como esses passos deram algum trabalho, trate de salvar as configurações, caso tenha que usá-las em outras máquinas ou restaurá-las caso algo de ruim aconteça com seu SO (como quando você depura seus drivers na mesma máquina em que desenvolve, por exemplo).

    
    reg save HKCU\Software\Microsoft\WinDbg c:\Tools\DbgTools\Themes\MyTheme.reg

Leia a documentação do WinDbg sobre temas (dentro de Themes, Themes.doc). Foi de lá que eu fiz a tradução e adaptação dos passos mais importantes. E esqueça do Visual Studio =)
