---
categories:
- draft
- blog
date: 2019-05-06 22:23:40-03:00
desc: Como funciona a interface entre unit tests em C++ e o Visual Studio?
title: Visual Studio Unit Test (C++)
---

Desde o Visual Studio 2015 há suporte a unit tests em C++ automatizado na IDE. Porém, a partir do VS 2017 15.5 o suporte aumentou drasticamente, vindo embutidos os suportes para as bibliotecas de teste Google Test, Boost.Test e CTest. Além, é claro, do Microsoft Unit Testing Framework for C++, o caseiro da M$.

Além disso, é possível você mesmo integrar o Visual Studio com outra lib de testes. Mas para que gastar tempo? Várias integrações já estão disponíveis no [Visual Studio Marketplace](https://marketplace.visualstudio.com/). Ligue já!

OK, parei com o merchan. Até porque não ganho nada com isso. Vamos ao código.

Pelo Wizard do VS podemos criar para um projeto C++ qualquer um projeto de teste. No momento estou vendo os tipos de projeto Native Unit Test e Google Test.

![](https://i.imgur.com/Gk5fDHB.png)

Este é nosso projeto de exemplo:

```c++
#include "CalculatorTabajara.h"

int soma(int x, int y)
{
	return x + y;
}

int subtrai(int x, int y)
{
	return x - y;
}

int multiplica(int x, int y)
{
	return x * y;
}

int divide(int x, int y)
{
	return x / y;
}

int main()
{
}
```

Para conseguir testar o projeto principal adicione-o como referência.

![](https://i.imgur.com/TbFrxIr.png)

Após isso basta incluir algum header que contenha os tipos, funções, classes e métodos que deseja testar e vá criando métodos de teste dentro da classe de exemplo:

```c++
#include "pch.h"
#include "CppUnitTest.h"
#include "..\CalculatorTabajara.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestaSoma)
		{
			int z = soma(3, 2);
			Assert::AreEqual(z, 5);
		}

		TEST_METHOD(TestaSubtracao)
		{
			int z = subtrai(3, 2);
			Assert::AreEqual(z, 1);
		}

		TEST_METHOD(TestaMultiplicacao)
		{
			int z = multiplica(3, 2);
			Assert::AreEqual(z, 6);
		}

		TEST_METHOD(TestaDivisao)
		{
			int z = divide(3, 2);
			Assert::AreEqual(z, 1);
		}
	};
}
```

Agora abrindo o jogo para você, amigo programador C++ que gosta de saber tudo que ocorre debaixo dos panos:

 - Um projeto Unit Test é apenas uma DLL com uns códigos de template.
 - Esse código já adiciona a lib de unit test da Microsoft e cria uma classe com exemplo de uso.
 - Adicione todo código do projeto original que ele precisa para compilar.

Por isso eu tirei a tranqueira de precompiled header do projeto de unit test, retirei a referência (sugestão do tutorial da Microsoft) e apenas adicionei o mesmo cpp para ser compilado.

Agora mais mágica: se você abrir a janela Test Explorer ele irá encontrar seus testes e enumerá-los!

![](https://i.imgur.com/1ZVjQ4D.png)

Se você já programou um pouco em Windows com C++ já deve saber o truque: como o Unit Test é uma DLL ela simplesmente exporta os símbolos necessários para que o Visual Studio encontre o que precisa. O básico que um plugin dos velhos tempos faz: exportar interfaces com um pouco de reflection.

![](https://i.imgur.com/en6DWQp.png)

Se você habilitar Undecorate C++ Functions no Dependency Walker verá que ele exporta justamente uma espécie de reflection, na forma de structs:

![](https://i.imgur.com/jiBQxZ4.png)

E se você prestar atenção na ordem de exportação desse símbolos verá que o primeiro se chama GetTestClassInfo. Acabou a magia, não é mesmo?

Os headers e fontes do CppUnitTest ficam em paths do Visual Studio como VC\Auxiliary\VS\UnitTest, nas pastas include e lib. Nele é possível dar uma olhada no significado das macros e das classes disponibilizadas. Logo abaixo das macros, no arquivo principal, é possível ver como funciona o reflection:

```c++
namespace Microsoft{ namespace VisualStudio {namespace CppUnitTestFramework
{

	struct ClassMetadata
	{
		const wchar_t *tag;
		const unsigned char *helpMethodName;
		const unsigned char *helpMethodDecoratedName;
	};

	struct MethodMetadata
	{
		const wchar_t *tag;
		const wchar_t *methodName;
		const unsigned char *helpMethodName;
		const unsigned char *helpMethodDecoratedName;
		const wchar_t *sourceFile;
		int lineNo;
	};

	struct ModuleAttributeMetadata
	{
		enum AttributeType { MODULE_ATTRIBUTE };
		const wchar_t *tag;
		const wchar_t *attributeName;
        //...
```

É uma lib pequena e elegante que permite uma interação não apenas com a IDE, como poderia ser automatizada por um script, uma vez que sabe-se o funcionamento interno e algumas interfaces.