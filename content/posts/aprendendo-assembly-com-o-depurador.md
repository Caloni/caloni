---
date: "2008-04-11"
tags: [ "code", "draft",  ]
title: "Aprendendo assembly com o depurador"
---
Além de servir para corrigir alguns bugs escabrosos, o nosso bom e fiel amigo depurador também possui uma utilidade inusitada: ensinar assembly! A pessoa interessada em aprender alguns conceitos básicos da arquitetura do 8086 pode se exercitar na frente de um depurador 16 ou 32 bits sem ter medo de ser feliz.

Vamos ver alguns exemplos?

Para quem está começando, recomendo usar um depurador simples, 16 bits e que existe em todo e qualquer Windows: o debug. Já usado para depurar a MBR no Caloni.com.br, poderá agora ser usado para ensinar alguns princípios da plataforma de uma maneira indolor. Basta iniciá-lo na linha de comando:


Os comandos mais úteis são o r (ver ou alterar registradores), o t/p (executar passo-a-passo), o d (exibir memória), o u (desmontar assembly) e o a (montar assembly). Ah, não se esquecendo do ? (ajuda).

Outro ensinamento bem interessante diz respeito à pilha. Aprendemos sempre que a pilha cresce de cima pra baixo, ou seja, de endereços superiores para valores mais baixos. Também vimos que os registradores responsáveis por controlar a memória da pilha são o sp (stack pointer) e o ss (stack segment). Pois bem. Vamos fazer alguns testes para ver isso acontecer.


Como vemos, ao empilhar coisas na pilha, o valor do registrador sp diminui. E ao fazermos um dump do valor de sp conseguimos ver os valores empilhados anteriormente. Isso é muito útil na hora de depurarmos chamadas de funções. Por exemplo, no velho teste do Windbg x Bloco de notas:



Aposto que você sabe em qual dos três botões eu cliquei =)

Depurar é um processo que exige dedicação (experiência) tanto ou mais do que o próprio desenvolvimento. Por isso, fazer um esforço para descobrir algum problema em algum software pode ser vantajoso no futuro, pois você terá mais capacidade de entender o que está acontecendo à sua volta.

Básico a intermediário:

	
  * Guia básico para programadores de primeiro breakpoint

	
  * Brincando com o WinDbg

	
  * Encontrando as respostas do Flash Pops

Intermediário a avançado:

	
  * Hook de API no WinDbg

	
  * Hook de COM no WinDbg

	
  * Detectando hooks globais no WinDbg

	
  * Analisando dumps com WinDbg e IDA

Blogues que eu acho superinteressantes sobre debugging (do mais essencial para o mais avançado):

	
  * Debugging Toolbox

	
  * Mark's Blog

	
  * Advanced Windows Debugging

	
  * Crash Dump Analysis

