---
categories:
- code
date: '2008-05-23'
tags:
- draft
title: Aprendendo rapidamente conceitos essenciais do WinDbg
---

Todo o poder e flexibilidade do pacote Debugging Tools da Microsoft pode ser ofuscado pela sua complexidade e curva de aprendizagem. Afinal de contas, usar o depurador do Visual Studio é muito fácil, quando se começa a usar, mas mesmo assim conheço muitos programadores que relutam em depurar passo-a-passo, preferindo a depuração por meio de "MessageBoxes" ou saídas na tela. Imagine, então, a dificuldade que não é para quem conseguiu às duras penas aprender a tornar um hábito a primeira passada do código novo em folha através do F10 começar a fazer coisas como configurar símbolos e digitar comandos exdrúxulos em uma tela em modo texto. Para piorar a questão, existem aqueles que defendem o uso unificado de uma ferramenta que faça tudo, como um telefone celular. Eu discordo. Quando a vantagem competitiva de uma ferramenta sobre outra é notável, nada pior que ficar preso em um ambiente legalzinho que faz o mínimo para você, mas não resolve o seu problema de deadlock.

Foi pensando nessa dificuldade que foi escrita uma apresentação nota dez por Robert Kuster que explica todas as minúcias importantes para todo programador iniciante e experiente na arte de "WinDbgear". "WinDbg. From A to Z!" é uma ferramenta tão útil quanto o próprio WinDbg, pois explica desde coisas simples que deve-se saber desde o início, como configurar símbolos, quanto assuntos mais avançados, como depuração remota. Até para quem já está no nível avançado vale a pena recapitular algumas coisas que já foram ditas no  AWD.

Mesmo tentando ser sucinto, o assunto ocupou um conjunto de 111 transparências que demoram de uma a duas horas de leitura cuidadosa, se você não fizer testes durante o trajeto. Entre as coisas que eu li e reli, segue uma lista importante para nunca ser esquecida (entre parênteses o número das transparências que considero mais importantes):

	
  * O que é são as bibliotecas de depuração do Windows e como elas podem te ajudar (6 e 9)

	
  * O que são símbolos de depuração (11, 12, 14)

	
  * Como funciona a manipulação de exceções e como depurar (18, 19, 85)

	
  * Como configurar seu depurador para funcionar globalmente (20)

	
  * Tipos de comandos no WinDbg (22)

	
  * Configurando símbolos e fontes no WinDbg (24, 25)

	
  * Interagindo com as janelas do WinDbg (33)

	
  * Informações sobre processos, pilhas e memória (29, 41, 43, 45, 66)

	
  * Informações sobre _threads_ e _locks_ (31, 55)

	
  * Comandos úteis com _strings _e memórias (66)

	
  * Avaliando expressões no WinDb: MASM e C++ (70, 71)

	
  * Usando _breakpoints _no WinDbg (básico) (81)

	
  * Usando _breakpoints _no WinDbg (complicado) (83, 84)

	
  * Depuração remota (muito útil!) (87)

	
  * Escolhendo a melhor ferramenta para o problema (fantástico!) (108)

Além da enchurrada de informações, o autor ainda explica a teoria com comandos digitados no próprio WinDbg, dando um senso bem mais prático à ferramenta. Ou seja, é útil tanto para os que aprendem por definições abstratas e lista de comandos quanto os que preferem já colocar a mão na massa e massacrar o bom e velho notepad.exe.

No final, duas dicas importantíssimas do autor para quem deseja se aventurar nesse mundo: leia a documentação do WinDbg (que também é ótima, apesar de bem mais extensa) e aprenda assembly (simplesmente essencial para resolver muitos problemas).

Se você ainda não teve tempo de se dedicar à depuração avançada em Windows e pensa que nunca terá, dedique duas horinhas divididas em períodos de 15 minutos por dia para explorar esse fantástico tutorial, que com certeza, se bem aplicado, reduzirá exponencialmente seu tempo de resolução de problemas.

Eu recomendo.

Existe uma tradução para inglês desse texto no saite do próprio Robert Kuster, que usou-o como uma espécie de introdução.