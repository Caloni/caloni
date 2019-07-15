---
date: "2010-11-12"
title: II Seminário Portabilidade e Performance
categories: [ "blog" ]
---
Aqui estamos nós de novo. Mais uma vez a [Tempo Real Eventos](http://www.temporealeventos.com.br/?area=101-SeminarioC-e-C++-Portabilidade-e-Performance) irá organizar esse evento de final de ano. E mais uma vez, junto dos meus amigos, irei palestrar sobre um item indispensável no nécessaire de todo escovador de bits: assembly gerado pelo compilador. Vamos falar brevemente sobre o funcionamento de um código assembly 32 bits e passar para a análise dos compiladores modernos e o que eles fazem para tornar o código ainda mais rápido do que o próprio fonte em C++.

	
  * Gerando código assembly;

	
  * Guia ultra-rápido de assembly;

	
  * Recursividade sem problemas na pilha;

	
  * STL aumenta performance? (exemplos práticos);

	
  * Assembly 64 bits.

Uma outra dúvida pertinente (e discutida nos bares nerds da cidade) é se usar código STL não deixaria mais lento o resultado final, já que ele é cheio das abstrações. Por mais que autoridades competentes no funcionamento da linguagem como [Pedro Lamarão](http://software.pedro.lamarao.nom.br/) e [Thiago Adams](http://www.thradams.com/blog/) digam que as otimizações do compiladores modernos na STL/Boost são diversas vezes mais eficientes que o código artesanal de um programador, sempre fica aquela pulga atrás da orelha, pulga esta que podemos matar facilmente analisando o assembly gerado. E essa confiança extra nos dará novas chances de programar coisas legais de verdade, e não ficar ensebando um código que já está na sua velocidade máxima.

Então é isso aí. Espero que tenhamos uma manhã e uma tarde agradáveis nesse mundo da escovação de bits.

