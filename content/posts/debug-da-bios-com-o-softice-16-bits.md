---
categories: [ "code" ]
date: "2007-10-02"
tags: [ "draft",  ]
title: "Debug da BIOS com o SoftIce 16 bits"
---
Para quem ainda acha que não desceu demais o nível, existe um ótimo artigo de ShalomZ, do Code Project, sobre como construir seu próprio sistema operacional. É simples, direta e empolgante a maneira com que ele explica e trata os detalhes básicos, desde quando o computador é ligado até quando o boot loader carrega e entrega o controle de execução. Eu mesmo fiz o teste com a imagem que foi disponibilizada para download e funcionou direitinho. Agora esse meu artigo se dispõe a explicar como você pode fazer para depurar o processo de load do seu primeiro sistema operacional.

Primeiro, precisamos de uma ferramenta fundamental para esse tipo de depuração: o SoftIce versão 16 bits. Desconheço algum outro depurador de sistema em 16 bits, mas se você souber de algum, pode usá-lo com esse tutorial com as devidas adaptações.

Passado o desafio inicial de encontrar essa versão do SoftIce e saber usá-la, o resto é fácil:

  1. Crie uma nova VMWare, Virtual PC, VMSbrubles configurada para bootar pelo disquete.
  2. Formate dois disquetes de MS-DOS, FreeDos, Sbrubles-DOS.
  3. Copie o setor de _boot_ disponível no artigo do CP para o disquete usando o programa disponível em um dos disquetes.
  4. Copie o SoftIce no outro disquete.
  5. Efetue o _boot_ com o disquete do SoftIce.
  6. Execute o SoftIce (é só rodar, ele permanece residente e é ativado com Ctrl + D).
  7. Coloque um _breakpoint_ na int 0x13 (disco) na função 2 (leitura) (faz-se assim: bpint 13 ah=2).
  8. Troque o disquete do Softice pelo disquete com o setor de _boot_ do artigo do CP.
  9. Efetue novamente o _boot_ na máquina em modo "quente" (usando o próprio SoftIce, comando boot).
  10. A execução deve ser paralisada exatamente no ponto onde o código da BIOS lê o setor de boot do seu disquete.
  11. Digite p ret e em seguida F10 ou T e seja feliz.

Pelo softice 16 bits conseguimos parar a execução nas interrupções da BIOS e ainda especificar qual das funções será executada, definida no registrador AH (mais detalhes sobre layout de memória do 8086 no artigo do DQ).

Quando o código da BIOS é executado, ele precisa, entre outras coisas, fazer três:

	
  1. Encontrar o dispositivo padrão de _boot._
  2. Ler o primeiro setor desse dispositivo para o endereço 0x7C00.
  3. Entregar a execução para o código em 0x7C00.

O item 2 é justamente o que utiliza essa interrupção para ler do disco. Eu prefiri colocar o breakpoint no item 2, mas nada impediria de você colocá-lo no item 3 e já iniciar a depuração no código do boot loader. Mas, como eu já passei por problemas encontrados no código da BIOS que impediam o sistema de entregar a execução para o setor de boot, já dei a dica de lambuja caso você também tenha a oportunidade de se divertir em um cliente depurando a BIOS de algum laptop desajustado.

Pela imagem acima sabemos que após o boot foi executada a interrupção 0x13, função 2 e que se trata de leitura em disquete, pois o conteúdo do registrador DL está em 0 (veja a referência das interrupções da BIOS em Ralf Brown's Interrupt List).

É mais ou menos o step out do SoftIce 32. Ou seja, ele avança a execução até a função retornar. No caso do SoftIce 16, ele irá avançar até o próximo ret/iret. Por isso que também precisamos executar a próxima instrução (o próprio ret) para cair onde queremos. É nesse ponto que o "nosso" código começa a executar e onde conseguimos colocar breakpoints "de verdade" (lembre-se que o código da BIOS está em uma memória de somente leitura, pelo menos durante a execução).

  * Building your own operating system - ShalomZ
  * Ralf Brown's Interrupt List
  * Gerenciamento de memória 386 - Daniel Quadros
