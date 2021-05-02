---
date: "2007-10-02"
link: "https://youtu.be/mXDROf0rLkI"
categories: [ "code" ]
title: "Debug da BIOS com o SoftIce 16 bits"
---
Para quem acha que ainda não desceu demais o nível existe um [ótimo artigo] no Code Project de S. Z. Keller (aka ShalomZ) sobre como construir seu próprio sistema operacional. É simples, direta e empolgante a maneira com que ele explica e trata os detalhes básicos, desde quando o computador é ligado até quando o boot loader carrega e entrega o controle de execução. Eu mesmo fiz o teste com a imagem que foi disponibilizada para download e funcionou direitinho. Agora esse meu artigo se dispõe a explicar como você pode fazer para depurar o processo de load do seu primeiro sistema operacional.

Primeiro precisamos de uma ferramenta fundamental para esse tipo de depuração: o SoftIce versão 16 bits. Desconheço algum outro depurador de sistema em 16 bits, mas se você souber de algum, pode usá-lo com esse tutorial com as devidas adaptações.

Passado o desafio inicial de encontrar essa versão do SoftIce e saber usá-la, o resto é fácil:

  1. Crie uma nova VMWare, Virtual PC, VMSbrubles configurada para bootar pelo disquete.
  2. Formate dois disquetes de MS-DOS, FreeDos, Sbrubles-DOS.
  3. Copie o setor de boot disponível no artigo do CP para o disquete usando o programa disponível em um dos disquetes.
  4. Copie o SoftIce no outro disquete.
  5. Efetue o boot com o disquete do SoftIce.
  6. Execute o SoftIce (é só rodar, ele permanece residente e é ativado com Ctrl + D).
  7. Coloque um breakpoint na int 0x13 (disco) na função 2 (leitura) (faz-se assim: bpint 13 ah=2).
  8. Troque o disquete do Softice pelo disquete com o setor de boot do artigo do CP.
  9. Efetue novamente o boot na máquina em modo "quente" (usando o próprio SoftIce, comando boot).
  10. A execução deve ser paralisada exatamente no ponto onde o código da BIOS lê o setor de boot do seu disquete.
  11. Digite p ret e em seguida F10 ou T e seja feliz.

Pelo softice 16 bits conseguimos parar a execução nas interrupções da BIOS e ainda especificar qual das funções será executada, definida no registrador AH; mais detalhes sobre layout de memória do 8086 no artigo do DQ [^1].

Quando o código da BIOS é executado, ele precisa, entre outras coisas, fazer três:
	
  1. Encontrar o dispositivo padrão de boot.
  2. Ler o primeiro setor desse dispositivo para o endereço 0x7C00.
  3. Entregar a execução para o código em 0x7C00.

O item 2 é justamente o que utiliza essa interrupção para ler do disco. Eu prefiri colocar o breakpoint no item 2, mas nada impediria de você colocá-lo no item 3 e já iniciar a depuração no código do boot loader. Mas, como eu já passei por problemas encontrados no código da BIOS que impediam o sistema de entregar a execução para o setor de boot, já dei a dica de lambuja caso você também tenha a oportunidade de se divertir em um cliente depurando a BIOS de algum laptop desajustado.

![Breakpoint na int 0x13 função 2 (DL=0)](/img/bpint-boot.png)

A referência para saber quais as funções para cada interrupção na hora de depurar a BIOS pode ser encontrada em listas como a Ralf Brown's Interrupt List [^2]

A partir dessa leitura se usa o comando p ret do depurador, que é mais ou menos o step out do SoftIce 32. Ou seja, ele avança a execução até a função retornar. No caso do SoftIce 16 ele irá avançar até o próximo ret/iret. Por isso que também precisamos executar a próxima instrução (o próprio ret) para cair onde queremos. É nesse ponto que o "nosso" código começa a executar e onde conseguimos colocar breakpoints "de verdade", ou seja, escrevendo no parte do código que deve ser interrompida a chamada da interrupção de breakpoint (int 3). Lembre-se que não é isso o que é feito para parar no código da BIOS, uma vez que esta reside em memória de somente leitura (pelo menos durante a execução).

![Código do boot loader carregado no Softice](/img/myos-start.png)

[^1]: [Gerenciamento de memória 386] - Daniel Quadros
[^2]: [Ralf Brown's Interrupt List na Wikipedia]

[ótimo artigo]: https://www.codeproject.com/Articles/15843/Building-your-own-operating-system
[Gerenciamento de memória 386]: https://dqsoft.blogspot.com/2006/10/gerenciamento-de-memria-386.html
[Ralf Brown's Interrupt List na Wikipedia]: https://en.wikipedia.org/wiki/Ralf_Brown%27s_Interrupt_List
