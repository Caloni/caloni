---
categories:
- draft
- blog
date: '2015-07-28'
title: Você sabe o que está usando no seu código?
---

Quando se mexe com C++ em múltiplos fontes logo vem aquela bagunça do versionamento e do compartilhamento de código. LIBs, DLLs, COMs (de Component Object Model, da Microsoft). É difícil a partir de um binário saber quais os fontes envolvidos em sua construção, a não ser que você os amarre através de um sistema automatizado de build onde todos os binários devem ser obrigatoriamente compilados (e suas dependências, claro).

Porém, há maneiras mais descentralizadas de se trabalhar. Alguém poderia simplesmente colocar a versão em cada CPP e atualizá-la, assim como comentários de histórico, toda vez que alguma mudança for feita:

```cpp
/** Estou começando esse meu CPP.
*
* @desc Esse CPP fará mágicas nunca antes tentadas,
* e portanto tende a ser perigoso para os padawans
* mais chegados em um coletor de lixo.
*
* @version 0.0.1
*
* @remark Estou usando Version Semantics logo acima.
*/
```

OK, esse já é um modelo interessante, embora totalmente descartável se você já usa um sistema de build atrelado a um controle de fonte, já que você automaticamente já terá um número mágico para relacionar seus binários: o revno de seu commit (ou seus commits, no caso de mais de um repositório).

Uma versão um pouco mais... "binária", seria inserir uma string no próprio fonte com essa versão, e talvez até o nome de seu módulo/lib/etc:

static const char* LIB_VERSION = "minhalib 0.0.1";

Dessa forma, por pior que seja a situação do controle de seus binários, sempre haverá a possibilidade de procurar a string lá dentro.

![Strings na minha lib]({{ site.baseurl }}public/images/screenshots/strings-minha-lib.png)

Ops, esqueci que nesses compiladores modernos __o que você não usa não será incluído no binário final__. Isso quer dizer que se quisermos que essas strings de identificação de dependências apareça no binário compilado precisamos pelo menos dar a impressão de que ele esteja sendo usado:

```cpp
class Using
{
public:
    Using(const char* name)
    {
        static const char* st_UsingCollection = name;
    }
};

static const Using st_Using("using minhalib 0.0.1");
```

Agora uma variável estática do módulo deverá ser inicializada como um objeto da classe Using e irá jogar em uma variável estática dentro do construtor. Se ela será usada fica a dúvida do compilador, que deixa tudo como está. Ou seja, ganhamos nossa string no binário:

```cpp
#include "Using.h"

static const Using st_Using("using minhalib 0.0.1");

int main()
{
}
```

![Strings na minha lib]({{ site.baseurl }}public/images/screenshots/strings-minha-lib-ok.png)

Uma solução mais genérica pode ser aplicada utilizando as famigeradas macros e...

O quê?!?!?!??! VOCÊ DISSE MACROS?!???!? TÁ MALUCO??!??!

Sim. Macros. São inofensivas se você usar direito.

E se reclamar vai ter goto.

```cpp
// Using.h
#pragma once 
#define USING_FILE(version) static const Using st_Using ## __LINE__("using file " __FILE__ " " version)
#define USING_CLASS(name, version) static const Using st_Using ## __LINE__("using class " #name " " version)
#define USING_LIB(name, version) static const Using st_Using ## __LINE__("using lib " #name " " version)
#define USING_FUNCTION(version) static const Using st_Using ## __LINE__("using function " __FUNCTION__ " " version)

class Using
{
public:
    Using(const char* name)
    {
        static const char* st_UsingCollection = name;
    }
};
```

A ideia é que qualquer pedaço de código, seja um conjunto de CPPs que você chama de LIB, ou um CPP que você compila em diferentes projetos (talvez em cópias diferentes ainda sendo usadas), ou até aquela função-chave, ou classe-chave. Na verdade, quando eu digo pedaço de código, é pedaço mesmo. Está livre para você imaginar e rotular o que quiser. Depois você consegue dar uma geral no resultado:

```cpp
// File1.cpp
#include "Using.h"

USING_LIB(extralib, "0.0.1");

void ImportantFunction()
{
    USING_FUNCTION("0.3.1");
}

// File2.cpp
#include "Using.h"

USING_FILE("0.0.1");

// File3.cpp
#include "Using.h"

USING_CLASS(ImportantClass, "1.3.4");
class ImportantClass
{
public:
};

#include "Using.h"

USING_LIB(lib1, "0.0.1");
```

![Todas as strings do meu projeto]({{ site.baseurl }}public/images/screenshots/all-strings-using.png)

Com esse simples mecanismo que não gasta mais do que algumas chamadas de assembly no início da lib (antes do main) e o espaço ocupado na memória pelas strings somadas (menos de 1KB, provavelmente) você tem em suas mãos uma poderosa ferramenta de análise de como os binários estão sendo gerados pela sua equipe remota, ou por qual configuração foi usada na máquina de build para gerar aquela DLL com aquele problema antigo, ou porque algo que funcionava parou de funcionar e nada foi mexido (isso nunca acontece, não é mesmo?).

_O código dessa brincadeira está no meu repositório de [samples](https://github.com/Caloni/samples/tree/master/Using) do GitHub._