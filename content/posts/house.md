---
categories:
- blog
date: '2010-01-25'
tags:
- draft
title: House
---

Depois da analogia entre depuração e CSI, nada como fazer o mesmo com o seriado estilo House.

Quais as semelhanças com a profissão de programador-depurador?

Em primeiro lugar, a busca por pistas. Se algo está errado com o programa, vivemos criando teorias mirabolantes a respeito do porquê tal função estar retornando zero. No entanto, como não temos tanta capacidade adivinhatória assim, geralmente nossos palpites estão errados, e o fundo do poço irá nos mostrar uma outra função que nem estava ainda na história.

Mas existem alguns pontos-comuns de conhecimento que sempre desenvolvemos no decorrer da carreira:

	
  * Se a última instrução do código é zero (ou algo próximo disso), provavelmente a pilha foi corrompida por alguém que tentou zerar uma variável, e junto dela o ponto de retorno de alguma função chamadora.

	
  * Se um programa trava em um determinado momento, voltando após um período previsível de tempo (30 segundos), automaticamente sabemos que existe algum evento/mutex usado de forma errada que, dadas as circunstâncias, apresentou uma espera longa demais.

	
  * Se uma versão nova capota em um procedimento em que a versão antiga nunca capotou, podemos divagar rapidamente quais as características da nova versão que fizeram com que isso acontecesse, ainda sem olhar para o código.

Dessa forma é possível criar teorias a partir da análise mental do que o programa normal deveria estar fazendo, mas não está. É esse tipo de análise que é feita no seriado.

Porém, o lado bom: podemos testar todas nossas hipóteses. Na vida real! Se, por enquanto, matar pacientes para depois ressuscitá-los é coisa de ficção, matar sistemas e reiniciá-los não é. E, dependendo do problema, podemos sempre replicá-lo em "outro paciente".

Talvez isso faça a profissão tão realizadora e viciante: para resolver um problema, geralmente temos todas as cartas na mão, e se não temos, fazemos ter. Afinal de contas, somos nós que iremos ressuscitar o sistema perdido.

	
  * A Ciência Médica de House