---
date: "2007-10-18"
tags: [ "code", "draft",  ]
title: "Por que minha DLL travou?"
---
Saiu um documento da Microsoft alertando sobre os perigos em colocar código no DllMain. É algo mais completo e didático do que as simples observações do help do MSDN. Vale a pena dar uma lida, especialmente por causa das explicações sobre o loader lock e seus efeitos colaterais.

O resumo da ópera é que o código do Windows chamador do DllMain das DLLs carregadas/descarregadas utiliza um objeto de acesso exclusivo (leia "mutex") para sincronizar as chamadas. O resultado é que, em um processo, apenas um DllMain é chamado em um dado momento. Esse objeto é chamado de "loader lock" na documentação da Microsoft.

O código abaixo é besta, mas representa o que já vi em muito código-fonte, e muitas vezes não consegui perceber o que estava acontecendo (tanto porque desconhecia a existência desse loader lock quanto o código estava obscuro demais pra entender mesmo). Os comentários dizem tudo:


Uma simples vítima disso pode ser um pobre executável usando uma pobremente escrita DLL, assim como no código abaixo:


Para ver o problema de lock em ação, copie os fontes da DLL e do EXEcutável e use os comandos abaixo para gerar os arquivos:


É importante sempre lembrar que a Microsoft acha feio, muito feio você ficar dependendo do DllMain pra fazer alguma coisa, **mas** admite que em alguns casos o único lugar onde podemos rodar código é no DllMain. Nesses casos - e em alguns outros - **utilize uma comunicação paralela com sua thread travadona**, por meio de um evento ou algo do gênero, antes que ela realmente saia. Com isso a thread pode ainda não ter saído, mas pode avisar a thread principal que o que ela precisava fazer já foi feito.

  1. NT Loader (MSJ Sep 99) - Matt Pietrek
  2. mgrier's WebLog - NT Loader team participant

