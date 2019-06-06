---
date: "2009-12-30"
title: Devaneio nerd rápido sobre profecias
categories: [ "code" ]
---
![crystallball.jpg](http://i.imgur.com/fEtiA9w.jpg)Para quem já analisou os dados de uma tela azul sabe que, quando o Windows acha um culpado (vulgo driver) a data de sua compilação é exibida em um formato conhecido como **DateStamp** ou **TimeStamp**. Nesse formato o que temos é um número hexadecimal que segue o [formato de tempo do Unix](http://en.wikipedia.org/wiki/Unix_timestamp), que no caso é o número de segundos desde o dia primeiro de Janeiro de 1970. Isso, por curiosidade, nos dá uma margem de 140 anos antes dos número se repetirem se usarmos 32 bits nessa contagem.

O comando .formats do WinDbg nos consegue trazer desse número a hora exata em que determinado componente foi compilado. Se, por exemplo, um driver faltoso apresentou um DateStamp igual a 49EE9758, podemos concluir que ele foi compilado no dia 22 de abril de 2009, uma linda quarta-feira.

    
    0:000> <font color="#0000ff">.formats 49EE9758</font>
    Evaluate expression:
      Hex:     00000000`49ee9758
      Decimal: 1240373080
      Octal:   0000000000011173513530
      Binary:  00000000 00000000 00000000 00000000 01001001 11101110 10010111 01011000
      Chars:   ....I..X
    <strong><font color="#0000ff">  Time:    Wed Apr 22 01:04:40 2009</font></strong>
      Float:   low 1.95454e+006 high 0
      Double:  6.12826e-315

Quando fazemos algo muitas vezes seguidas temos o hábito inconsciente de observar certas idiossincrasias dos dados que sempre vem e vão. No caso dos Date Stamps, sempre me veio o fato deles iniciarem com 4 e estarem prestes a "virar o contador" para 5.

Isso aos poucos - entre uma tela azul e outra - me deixou curioso a respeito de quando seria o dia fatídico em que teríamos o DateStamp 50000000, um número cabalístico em nosso sistema decimal. E, imaginem só:

    
    0:000> <font color="#0000ff">.formats 50000000</font>
    Evaluate expression:
      Hex:     00000000`50000000
      Decimal: 1342177280
      Octal:   0000000000012000000000
      Binary:  00000000 00000000 00000000 00000000 01010000 00000000 00000000 00000000
      Chars:   ....P...
    <font color="#0000ff">  Time:    Fri Jul 13 08:01:20 2012</font>
      Float:   low 8.58993e+009 high 0
      Double:  6.63124e-315

Pois é, meus amigos. O DateStamp para a virada do contador Unix se fará numa manhã de sexta. Para ser preciso, uma [sexta-feira 13](http://pt.wikipedia.org/wiki/Sexta_Feira_13).

Curioso, não? Mais curioso que isso, só sabendo que o ano que isso vai ocorrer é o igualmente fatídico [2012](http://www.youtube.com/watch?v=Hz86TsGx3fc). Felizmente antes de dezembro.
