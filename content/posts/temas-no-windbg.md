---
date: "2008-01-14"
title: Temas no WinDbg
tags: [ "draft", "blog" ]
---
[![WinDbg Workspace (Visual Studio like)](http://i.imgur.com/X3IFGZb.thumbnail.png)](http://i.imgur.com/ivqb6MO.png)Desde a versão [6.4.7.2](http://www.microsoft.com/whdc/devtools/debugging/whatsnew.mspx) que o WinDbg fornece uma subpasta chamada **Themes**, onde lá estão diversos _workspaces_ configurados. Existe até um passo-a-passo de como organizar esses temas e escolher o seu favorito. Segue algumas dicas de como transformar corretamente sua área de trabalho para depuração (e mantê-la).

#### Primeira coisa: limpe todos seus dados

O WinDbg salva suas configurações no registro. Para apagar os valores previamente gravados, rode o seguinte comando:

    
    reg delete HKCU\Software\Microsoft\WinDbg

#### Segunda coisa: execute o tema que mais gostar

Você pode gravar um tema, rodar o WinDbg (sem parâmetros), ver se gosta do que viu, e tentar novamente. Quando estiver satisfeito com a aparência, fique com ela e comece o próximo passo.

#### Configurando o que importa

Nas depurações do dia-a-dia algumas configurações devem estar sempre muito bem configuradas, para que torne seus momentos de desespero porque nada está funcionando mais agradáveis. Por isso, assim que escolher seu tema preferido trate de configurar os seguintes itens:

	
  * Diretórios de símbolos. Você pode começar com **.symfix**, que vai montar uma string padrão, e adicionar mais diretórios com **.sympath+**.

	
  * Diretórios de código-fonte. Coloque a raiz dos seus projetos principais. Com o tempo, se você mexe muito nos seus diretórios, é necessário fazer uma manutenção desse valor.

	
  * Diretórios de executáveis. Basicamente é o mesmo do diretório de símbolos.

#### Ajuste fino

Depois de configurar tudo isso, ajuste as janelas na melhor maneira e proporção que achar mais agradável. Esse será o último passo, pois depois você irá fechar o WinDbg e salvar o _workspace_, que a partir daí será o padrão sempre que abrir o depurador.

<blockquote>

> 
> #### Configure corretamente onde seu código-fonte vai abrir
> 
_Para que os arquivos fonte caiam no lugar que você escolheu, durante a configuração, abra um código-fonte e coloque no lugar que gostaria de ver todos os fontes listados, junto com um placeholder (um arquivo C usado como localizador, existem 5 dentro da pasta themes). Após isso, feche o código-fonte, mas mantenha o placeholder. Depois é só fechar o WinDbg salvando as configurações. Tudo deve funcionar como previsto (ou você esqueceu alguma coisa)._</blockquote>

Como esses passos deram algum trabalho, trate de salvar as configurações, caso tenha que usá-las em outras máquinas ou restaurá-las caso algo de ruim aconteça com seu SO (como quando você depura seus drivers na mesma máquina em que desenvolve, por exemplo).

    
    reg save HKCU\Software\Microsoft\WinDbg c:\Tools\DbgTools\Themes\MyTheme.reg

#### Para um guia completo

Leia a documentação do WinDbg sobre temas (dentro de Themes, Themes.doc). Foi de lá que eu fiz a tradução e adaptação dos passos mais importantes. E esqueça do Visual Studio =)
