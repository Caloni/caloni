---
categories: [ "code" ]
date: "2008-10-15"
tags: [ "draft", ]
title: "Como usar WTL com o ATL do DDK"
---

No entanto, num belo dia, qual não foi minha surpresa ao notar umas pastinhas chamadas atl21, atl30 e atl71 dentro da distribuição do WDK (o finado DDK, renomeado sabe-se-lá-por-quê)? Pelo visto, tem alguém arrastando coisa errada pra onde não devia nos instaladores de Seattle. Esses estagiários!

O fato é que eles fizeram isso, e agora é possível ter o WTL mais novo compilado com o WDK. E nem é tão difícil assim.

A primeira coisa a fazer é obter o tal doWDK. Para variar um pouco, agora existe um processo de registro antes de obter acesso ao download, mais ou menos nos termos da Borland para baixar o Builder / Turbo / Developer Studio.

Aliás, para os que baixaram esses produtos gratuitos da Borland versão C++ e não funcionou em algumas máquinas, como foi o meu caso, está disponível para baixar uma versão mais nova; dessa vez não vi nenhum problema na compilação e depuração. Ainda.

Após instalado, em qualquer lugar da sua escolha, configure no seu Visual Studio Express o caminho de onde se encontra a pasta atl71 (ou a 30, ou a 21). Aproveite também para colocar a pasta do WTL e o diretório de LIBs:

Isso vai fazer com que pelo menos os exemplos que vêem com o WTL compilem.

No entanto, você verá o seguinte erro durante a compilação dos recursos:


Para resolver esse problema, remova a inclusão do arquivo de manifesto no arquivo RC:


Depois dessa alteração, deve ainda existir o seguinte erro de linquedição:


Esse problema ocorre porque as funções de alocação e desalocação de memória da ATL estão em outra LIB que os exemplos da WTL desconhecem. Para resolver, basta incluir essa nova dependência:


E pronto! Agora temos todo o poder das 500 milhões de classes da ATL aliadas à ilimitada flexibilidade das classes de janelas da WTL.

	
  * Explicando a sopa de letrinhas da programação C/C++ para Windows: WTL

	
  * WTL for MFC Programmers

