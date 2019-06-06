---
date: 2017-09-26T10:21:02-03:00
title: "C++ Moderno Arranca os Cabelos por Você (std::move e classes simples)."
categories: [ "code" ]
---
Um dos [últimos posts](https://groups.google.com/forum/#!topic/ccppbrasil/-AC9U7J-0Zg) no grupo CCPPBR do Thiago Adams chama mais uma vez a atenção para a complexidade infinita que linguagens como C++ estão preferindo tomar. Esta é a geração que irá sofrer as dores de compatibilidade com o passado mais que todas as outras que virão.

Isso porque mudanças pontuais que vão sendo aplicadas na linguagem e biblioteca, como *move semantics*, não cabe mais em exemplos de livrinhos de C++ para iniciantes da década de 90:

```cpp
#include <string.h>
#include <stdlib.h>
#include <memory>

struct X
{
    char * pString = 0;
    X() {}
    X(const char* s)
    {
        pString = _strdup(s);
    }
    ~X()
    {
        free(pString);
    }
};

int main()
{
    X x1;
    const X x2("a");
    x1 = std::move(x2);

    return 0;
}
```

Neste singelo exemplo, que está errado by design, a classe X não se preocupa em proteger-se de cópias simples. Mas o programador também não se protege da ignorância e usa **std::move** como se ele magicamente movesse referências const, o que é absurdo.

![Imgur](https://i.imgur.com/zi5GJxE.png)

A questão, porém, não é sobre qual é o problema no código, mas os aspectos de design de C++ que podem levar futuros programadores a se depararem com o mesmo problema em versões multicamadas de complexidade. Este é um exemplo óbvio, mas até quando será?

Esta crítica pode levar (pelo menos) para dois diferentes caminhos:

 - O funcionamento do std::move não é intuitivo e pode levar a erros semânticos ("se usar o move estou movendo referências"); programador não conhece o funcionamento por completo.
 - Em C++ o esforço de manter uma classe é muito maior hoje do que em 98/03 ("tomar cuidado com reference, const reference, rvalue reference..."); isso concordo; as mudanças são bem-intencionadas, mas a linguagem é velha com alguns esqueletos que podem começar a balançar.

C++, assim como o Brasil, desde o começo nunca foi para amadores. Hoje em dia ele é impossível. Ouço galera falar que está ficando lindo, mas, francamente, está virando é um ninho de cobras. Mantenedores de bibliotecas, se não estão já arrancando os cabelos, deveriam começar.

Mas talvez com C++ 17+ os cabelos passem a cair sozinho...
