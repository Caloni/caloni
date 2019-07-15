---
date: 2018-03-11T16:25:56-03:00
title: "Contra o 'Array de 100 bytes é suficiente'"
categories: [ "code" ]
---
Desde o C++ moderno (pós-03) o uso de arrays de tamanho fixo estão se tornando depreciados. E por um bom motivo: você nunca sabe realmente qual o tamanho que você precisa para um array de bytes até você saber. Daí a próxima grande questão é: "como gerenciar essa memória dinâmica de forma efetiva?". E a resposta moderna sempre é: "não faça isso você mesmo". Eis o porquê:

```
#include <string.h>
#include <iostream>

char* LegacyFunction()
{ 
    char* ret = (char*) malloc(100);
    strcpy(ret, "old old string");
    return ret;
}

void WideStringFunction(wchar_t* mbString)
{
    std::wcout << mbString << L'\n';
}

int main()
{
    char* legacyString = LegacyFunction();
    size_t legacyLen = strlen(legacyString);
    wchar_t* convertedString = new wchar_t[legacyLen+1]; // espalhando a merda de alocar dinamicamente
    mbstowcs(convertedString, legacyString, legacyLen+1);
    WideStringFunction(convertedString);
    free(legacyString);
    free(convertedString); // espalhando a merda de desalocar manualmente
}
```

Quando lidamos com funções legadas elas se misturam de tal maneira com código novo que a merda da alocação/desalocação dinâmica manual vai se espalhando também. A não ser que a gente comece a usar o novo modelo RAII e deixe a memória ser gerenciada automaticamente:

```
#include <string.h>
#include <iostream>
#include <vector>

char* LegacyFunction()
{ 
    char* ret = (char*) malloc(100);
    strcpy(ret, "old old string");
    return ret;
}

void WideStringFunction(wchar_t* mbString)
{
    std::wcout << mbString << L'\n';
}

int main()
{
    char* legacyString = LegacyFunction();
    size_t legacyLen = strlen(legacyString);
    std::vector<wchar_t> convertedString(legacyLen+1); // a STL que se vira pra alocar
    mbstowcs(&convertedString[0], legacyString, legacyLen+1);
    WideStringFunction(&convertedString[0]);
    free(legacyString);
    // a STL que se vira pra desalocar convertedString
}
```

Note que estamos obtendo o endereço do primeiro elemento do nosso vector STL porque, desde o padrão C++0x03, [__vetores são garantidos que serão contínuos__](https://herbsutter.com/2008/04/07/cringe-not-vectors-are-guaranteed-to-be-contiguous/). Essa garantia de leiaute de memória pode facilitar muitos usos de vector que estavam dependentes da implementação. O exemplo acima é apenas o mais simples deles, mas imagine que qualquer tipo de memória contígua cujo tamanho é desconhecido em tempo de compilação pode ser deixado seu gerenciamento para a STL cuidar.

Ah, e a partir do C++11 podemos usar vector::data() para obter os dados sem deferenciar o primeiro elemento. Particularmente acho mais expressiva a sintaxe dos arrays, mas fica a gosto do freguês.
