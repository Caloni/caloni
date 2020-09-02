---
date: "2011-01-04"
tags: [ "code", "draft",  ]
title: "Dependência pedindo carona"
---
Mesmo as vezes que você não queira, algumas dependências pedem carona e o compilador deixa entrar. Daí mesmo que você não use uma função API, ela acaba te atazanando a vida.

Foi o caso da ToolHelp32 no Windows NT 4.

Quando compilamos, cada CPP vira uma coleção de funções que serão usadas, mais tarde, pelo linker, para juntar a bagunça. Para mais detalhes dessa fascinante história, recomendo o fantástico artigo sobre Os diferentes erros na linguagem C, seção Linkedição.

Para as dependências localizadas fora do executável final, por exemplo, as DLLs do sistema, o linker cria uma entrada no formato padrão de executável que adiciona essa dependência extra que será resolvida na hora do programa rodar, quando o loader do sistema operacional terá que fazer um linker on-the-fly, catando todas as DLLs e funções necessárias para colocar o bichinho no ar.

Dessa forma, quando existirem unresolved externals fora do executável final, o responsável por dar o erro é o loader do sistema:

Isso significa que o seu processo não poderá ser executado, pois faltam funções no ambiente que ele depende.

Um recurso muito útil para ver essas funções é o Dependency Walker, meu amigo de infância:

"Mas, Caloni, eu nem uso essa função! Como ela pode ser necessária?"

Pois é. As coisas nem sempre acabam sendo como o esperado. Se você possuir uma LIB, por exemplo, e nela existirem duas funções, como abaixo, e você se limitar a usar em seu programa apenas a primeira, todas as dependências da segunda também irão parar no executável final.



Acontece que o nosso amigo linker gera uma lista de dependências por módulo (CPP), e não por função. Dessa forma, tudo que vier é lucro.

Só que às vezes é prejuízo, também. Quando usamos um SO da época do guaraná com rolha, como o Windows NT 4, por exemplo, não conseguimos usar um programa porque este possuía uma função moderninha nunca usada, mas que estava dentro de um CPP junto de uma função comportada, usando apenas APIs documentadas no primeiro papiro da Microsoft.

Sempre existe. Nesse caso, migrarmos as funções moderninhas para um segundo CPP, recompilarmos a LIB e a dependência milagrosamente desaparecerá!



Agora a aplicação poderá rodar em paz naquele que é, como diz meu amigo, um sistema operacional de ponta... da outra ponta!
