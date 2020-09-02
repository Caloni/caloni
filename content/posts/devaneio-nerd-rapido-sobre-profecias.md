---
date: "2009-12-30"
tags: [ "code", "draft",  ]
title: "Devaneio nerd rápido sobre profecias"
---
Para quem já analisou os dados de uma tela azul sabe que, quando o Windows acha um culpado (vulgo driver) a data de sua compilação é exibida em um formato conhecido como DateStamp ou TimeStamp. Nesse formato o que temos é um número hexadecimal que segue o formato de tempo do Unix, que no caso é o número de segundos desde o dia primeiro de Janeiro de 1970. Isso, por curiosidade, nos dá uma margem de 140 anos antes dos número se repetirem se usarmos 32 bits nessa contagem.

O comando .formats do WinDbg nos consegue trazer desse número a hora exata em que determinado componente foi compilado. Se, por exemplo, um driver faltoso apresentou um DateStamp igual a 49EE9758, podemos concluir que ele foi compilado no dia 22 de abril de 2009, uma linda quarta-feira.


Quando fazemos algo muitas vezes seguidas temos o hábito inconsciente de observar certas idiossincrasias dos dados que sempre vem e vão. No caso dos Date Stamps, sempre me veio o fato deles iniciarem com 4 e estarem prestes a "virar o contador" para 5.

Isso aos poucos - entre uma tela azul e outra - me deixou curioso a respeito de quando seria o dia fatídico em que teríamos o DateStamp 50000000, um número cabalístico em nosso sistema decimal. E, imaginem só:


Pois é, meus amigos. O DateStamp para a virada do contador Unix se fará numa manhã de sexta. Para ser preciso, uma sexta-feira 13.

Curioso, não? Mais curioso que isso, só sabendo que o ano que isso vai ocorrer é o igualmente fatídico 2012. Felizmente antes de dezembro.
