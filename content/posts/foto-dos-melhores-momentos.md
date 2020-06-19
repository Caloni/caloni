---
categories: [ "code" ]
date: "2010-08-12"
tags: [ "draft", "debug" ]
title: "Foto dos melhores momentos"
---
Mais um quebra-cabeças antes da nossa palestra, esse "baseado em fatos reais".

A história é a seguinte: o cliente instalou uma versão nova do produto em algumas máquinas que, ato contínuo, começaram a apresentar telas azuis constantemente. Como essas máquinas tinham que ser usadas pelos funcionários, a administradora rapidamente desinstalou essa versão buguenta, e logo em seguida pediu por uma correção.

Até aí tudo bem. O problema maior era que ninguém havia capturado dump de nada.

Por isso pedi encarecidamente por qualquer fragmento de tela azul (minidumps) que pudessem ainda estar nas máquinas afetadas. Dito isso, ela confessou que havia voltado a imagem padrão nesses equipamentos para que os funcionários pudessem voltar ao trabalho rapidamente. Só que sem dump eu não conseguiria trabalhar rapidamente.

Mas eis que no dia seguinte ela me liga, comentando que um funcionário, empolgado (?) pela tela azul em sua máquina, havia tirado uma foto da mesma para "recordação". Sem nenhuma cerimônia, então, pedi rapidamente que ela conseguisse essa foto para a minha coleção. A foto que ela me manda é exatamente a que está no início desse artigo (clique na foto para ampliá-la), apenas censurado o nome do driver, o que não vem ao caso. Assim que a recebi pude constatar o problema direto no código-fonte, corrigi-lo e enviar uma nova versão, que após alguns dias de testes se revelou bem sucedida.

A questão é: como eu resolvi o problema? Como você teria procedido nessa situação?

A resposta para esse enigma também contará pontos para nossa brincadeira com o livro Windows Internals, como foi explicado no artigo anterior. Vamos lá, Sherlock!
