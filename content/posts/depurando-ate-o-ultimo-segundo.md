---
categories:
- code
date: '2009-03-31'
tags:
title: Depurando até o último segundo
---

Como depurar um programa que dá pau logo no final do desligamento de uma máquina?

No cenário em que isso se passa não existem usuários logados no momento, o que significa a impossibilidade de rodar qualquer programa em uma sessão prévia e mantê-lo no ar após o logoff. A não ser que se trate de um serviço.

O nosso programa é justamente um serviço, e por isso ele continua rodando até o final, ou bem perto dele. A primeira ideia que vem à mente é instalar o Msvcmon - depurador remoto do Visual Studio - como um serviço, como aliás já foi demonstrado neste blogue.

Essa é uma boa ideia, de fato. Contudo, não podemos esquecer que a ordem de descarregamento dos serviços pode não favorecer o nosso depurador remoto e ele ir embora antes que consigamos "atachar" nosso VC no programa faltoso. Além do mais, a própria rede, que é disponibilizada com a ajuda de serviços, pode não estar no ar, mesmo que o Msvcmon esteja.

Tudo bem, vamos dizer que você é um expert em configuração de dependências de serviços e conseguiu fazer com que a rede, o Msvcmon e o programa faltoso sejam os últimos serviços - com exceção dos drivers - a serem descarregados. Bravo!

Contudo, isso não vai adiantar de muita coisa se for necessário parar a execução por um breve momento e analisar a pilha por, digamos,  cinco segundos. Esse é o tempo que o sistema - que continua rodando - precisa para desligar a máquina.

Agora o problema é outro: não há tempo para análise durante a depuração, pois o sistema continua rodando. Nesse caso, teremos que ser mais radicais e parar o próprio sistema para que possamos depurar calmamente o problema. Isso implica em termos que utilizar um depurador de kernel (WinDbg), pois só ele tem poderes de congelar o sistema inteiro.

Mas, ainda assim, precisamos de um depurador de user para fazer análises mais profundas ou, pelo menos, mais simples, com a ajuda de símbolos e tudo mais. Nesse caso é necessário usar um depurador de user que redireciona o controle para o depurador de kernel. A transição user mode >> kernel mode pode ser feita com apenas algumas configurações antes do reboot.

E, após toda essa bagunça, podemos depurar, no conforto de uma VM, o bendito programa matador.
