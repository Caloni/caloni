---
date: "2016-03-01"
title: "Crash no Windows Explorer"
categories: [ "code" ]
---
Quem nunca se deparou com um sistema Windows em que o Explorer travasse ou crashasse de vez em quando? O problema com esse tipo de problema (recursividade...) é que ele pode ocorrer por infinitos motivos. Tão infinitos quanto os shell extensions, aquelas DLLs irritantes que são carregadas automaticamente por todo processo explorer.exe, e que portanto podem gerar infinitas maneiras de travar seu shell.

Um que estava me incomodando já há algum tempo era um deadlock que acabava em restart do Explorer (isso é automático no Windows 10). Para verificar o que era, antes [configurei a geração de dumps automática](http://caloni.com.br/coletando-dumps-automaticamente) para que qualquer novo crash gerasse um arquivo de dump para eu analisá-lo. Só passou algumas horas para ter algo que pudesse trabalhar:

![](http://i.imgur.com/HMQUIVT.png)

Um dump pode ser analisado pelo Visual Studio (qualquer versão) ou depuradores como WinDbg (do pacote Debugging Tools for Windows). Como análise exploratório, apenas o Visual Studio é suficiente, pois ele pode exibir coisas como os módulos carregados pelo processo e a pilha de chamadas da thread faltosa.

![](http://i.imgur.com/n9CvNqG.png)

No caso do dump que eu estava analisando, verifiquei que a thread que gerou o travamento continha uma DLL da NVidia:

![](http://i.imgur.com/Sj6KKkc.png)

Essa DLL, de acordo com o AutoRuns, estava cadastrada no registro como um Context Menu Handler para o shell:

![](http://i.imgur.com/emFTzEo.png)

Depois de desativá-la e iniciar uma nova instância do Explorer foi possível verificar que a DLL não estava mais sendo carregada pelo processo.

![](http://i.imgur.com/UKhavJr.png)

E "magicamente" o travamento não aconteceu nos próximos dias =).
