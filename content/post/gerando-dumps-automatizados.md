---
categories: [ "code" ]
date: "2010-08-26"
tags: [ "draft",  ]
title: "Gerando dumps automatizados"
---
Agora que a temporada das telas azuis passou estou às voltas com o nosso sistema de detecção de crashes, além de alguns dumps e logs pra relaxar de vez em quando.

Fiquei impressionado com a simplicidade com que podemos capturar qualquer exceção que ocorra em um programa, independente da thread, e gravar um minidump com o contexto exato em que o problema ocorreu. O uso da função API SetUnhandledExceptionFilter aliado com a já citada na palestra MiniDumpWriteDump pode agilizar muito a correção de crashes triviais como Access Violation.

A mágica é tão bela que resolvi gravar um vídeo do que ocorreu quando compilei e testei o programa abaixo. Note que o tamanho do arquivo de dump ficou em torno dos 10 KB, ridículos nessa era de barateamento de espaço.


Espero com isso aliviar a carga pesada de A.V.s que sempre aparece quando menos se espera. Cuidar de toneladas de código legado exige algumas pitadas de automatização nos lugares certos. Como já dizia meu primeiro chefe: se a mente não pensa...
