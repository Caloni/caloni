---
categories: [ "code" ]
date: "2011-07-26"
tags: [ "draft",  ]
title: "Depuração de emergência"
---
O programa está rodando no servidor do cliente, que é acessível por sessão remota do Windows, mas de repente ele capota. Existem aí duas possibilidades fora o debug remoto (que, nesse caso, não é possível):

	
  1. Analisar um dump gerado.

	
  2. Depurar localmente o problema.

Para a primeira opção, basta abrir o Gerenciador de Tarefas, localizar o processo e gerar o dump através do menu de contexto.

Com o dump e o Windbg em mãos, basta analisá-lo. Porém, se o seu processo é 32 bits e o servidor é 64 bits (geralmente é), o dump gerado será de 64 bits, EMBORA seja de um process 32. Ou seja, ao abri-lo, o sistema vai mostrar as threads de manipulação do SO para sistemas 32 (todos com o nosso amigo wow64cpu).







Após esse último passo, siga para o último passo desse tutorial. Ou escolha a segunda opção:

Para depurar localmente, supondo que seja um executável simples, você precisa dos seguintes itens:

	
  * Pasta do WinDbg copiado (a Debugging Tools instalada pelo SDK, ou sua pastinha particular guardada no PenDrive).

	
  * Símbolos dos binários envolvidos (em sincronia com os binários que iremos analisar).

	
  * Fontes da compilação dos binários (a versão exata seria ideal; grave o revno do controle de fonte pra facilitar).

Os fontes, no caso de uma conexão por Terminal Server, podem ser disponibilizados através do mapeamento de drives entre as máquinas. Os símbolos, no entanto, por serem usados extensivamente pelo WinDbg, é recomendável que estejam locais na máquina depurada, pois do contrário você terá que tomar uma quantidade excessiva de cafés para executar meia-dúzia de instruções.

Supondo que temos tudo isso, só precisamos executar alguns passos básicos para o setup:



Por último, execute o seguinte comando na tela de comandos do WinDbg:


E boa sorte =)
