---
categories: [ "code" ]
date: "2008-12-12"
tags: [ "draft",  ]
title: "Básico do básico: tipos"
---
Um tipo nada mais é que do que uma forma (ô) de bolo, que molda a memória como acharmos melhor moldá-la. Bom, para isso fazer sentido é necessário explicar memória, que é um conceito mais básico ainda.

A memória é qualquer lugar onde eu possa guardar alguma coisa. No artigo anterior era um punhado de gavetas. Mas poderiam muito bem ser caixas de presente. Ou um caderno. Ou até uma placa de memória RAM. O que sua criatividade quiser.

O importante no conceito de memória, computacionalmente falando, é saber que ela pode guardar qualquer tipo de informação, mas ela não sabe o que você está guardando. E eis que surge o segredo do tipo: ele conta para você, e seu programa, o que de fato está guardado na memória.

Vamos exemplificar.

Computadores trabalham muito bem com números. A própria memória só guarda valores numéricos. Porém, se é dessa forma, como conseguimos abrir o Bloco de Notas e digitar algum texto?

Para entender essa "mágica" é necessário vir à tona o conceito de representação, um tema que ainda pode dar muito pano pra manga quando estudarmos base numérica. Por enquanto, basta saber que uma representação é um faz-de-conta em que todos concordam com o que for dito. Por exemplo: Faz de conta que a letra 'A' é o número 65. Dessa forma, sempre que for visto o número 65, de agora em diante, será vista a letra 'A' no lugar.

Existem alguns faz-de-conta que são muito difundidos entre e humanidade informática. Um deles é chamado tabela ASCII (se pronuncia "ásqui"). É uma forma de todos conseguirem entender os textos de todo mundo. Abaixo podemos ver a representação de todas as letras maiúsculas na codificação ASCII:


Agora, imagine que você digitou o seguinte texto no bloco de notas:


Como esse texto é guardado na memória de um computador, se ele só entende números?

Através da nossa já conhecida tabela ASCII! Na verdade, números são armazenados na memória, mas por representarem as letras 'C', 'A', 'S' e 'A', são traduzidos de volta para o formato texto pelo Bloco de Notas, que conhece o que guardou na memória.

A técnica de representação pode guardar qualquer coisa na memória como números que serão traduzidos por algum programa que consiga abrir aqueles dados. Dessa forma podemos não só armazenar texto, como imagens, vídeos, páginas web e até mesmo os próprios programas que os abrem!

Na programação do dia-a-dia, as coisas funcionam da mesma forma. As tão faladas variáveis reservam um espaço de memória para guardar alguma coisa, mas só sabemos o que essa alguma coisa é através do tipo da variável:


Esses elementos, na memória, são um bando de número que, sem os tipos, não possuem significado algum, como podemos ver na depuração do programa abaixo:

Note que os números não estão aqui representados em decimal, onde se esperaria 35 e 42, pois a representação formal da memória geralmente está no formato hexadecimal, transformando esses números em 0x23 e 0x2a, respectivamente. Para entender essa diferença cabe estudar um pouco sobre base numérica, outro tema básico do programador sólido.

Nada é bem aprendido se não for apreendido. Algumas tarefas programáticas que podem fixar o conceito de tipo estão listadas abaixo:

	
  * Usar printf especificando tipos diversos (%d, %s, %f, %p, ...) para a mesma variável, inclusive correndo o risco de gerar algumas exceções.

	
  * Usar scanf especificando diversas variáveis para o mesmo tipo (%d, %s, %f, %p, ...), vendo o resultado da leitura da entrada do usuário na memória.

	
  * Tentar copiar o conteúdo de uma variável para outra variável de tipo diferente. Sempre analise a memória para ver o resultado.

	
  * Ordenação de extremidades): O problema Little Endian e Big Endian.

	
  * UNICODE: Por um conjunto de letras universal.

	
  * Base numérica: O que são binário e hexadecimal e como eles afetam nossa vida.

