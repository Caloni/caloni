---
categories:
- code
date: '2013-11-07'
tags:
title: Ponto Flutuante Afundando
---

Quando armazenamos valores monetários em doubles seus cálculos conseguem manter a precisão e na maioria das vezes o ajuste de precisão funciona. Porém, encontrei alguns casos onde a subtração de dois valores fazia "perder" um centavo (ou comparações exatas) justamente pela limitação da precisão do ponto flutuante. Nesse exemplo os valores são 2.358,93 - 1.386,93, que em uma conta de padaria (mas correta) dá 972,00 ([até a Calc do Windows](http://www.codinghorror.com/blog/2009/01/if-you-dont-change-the-ui-nobody-notices.html) e [o Excel](http://dqsoft.blogspot.com.br/2007/09/ser-que-o-excel-2007-desaprendeu.html) funcionam), mas pelo Visual Studio 2010 chega perto, mas erra o alvo:

```
#include <iostream>

int main()
{
	double d1 = 2358.93;
	double d2 = 1386.93;
	double d3 = d1 - d2;

	std::cout << "d1: " << d1 << "\n";
	std::cout << "d2: " << d2 << "\n";
	std::cout << "d1 - d2 = 3d: " << d3 << "\n";

	// comparando armazenamentos que diferem
	std::cout << "d3 == 972.0: " << std::boolalpha << ( d3 == 972.0 ) << "\n";

	// comparando armazenamentos similares
	std::cout << "d1 == 2358.93: " << std::boolalpha << ( d1 == 2358.93 ) << "\n";
	std::cout << "d2 == 1386.93: " << std::boolalpha << ( d2 == 1386.93 ) << "\n";
}

```

Isso ocorre porque sua representação dentro da variável double é diferente de 272.0 do outro double. Depurando vemos mais claramente:

[![Ponto Flutuante Afundando](http://i.imgur.com/TnsgAlZ.png)](/images/10726640115_76bdf8a8eb_o.png)

Ou seja, quando fazemos a subtração de d2 em d1, nossa precisão raspa um pouquinho e escapa pela beirada:

    
    d1 2358.9299999999998
    d2 1386.9300000000001
    ======================
    d3 971.999999999999777
    ||||||
    Esse é o valor "desejado".

Na comparação com o valor redondo aparece a falha, mas note que isso não ocorre com os outros valores d1 e d2, já que o armazenamento adquire o mesmo formato:

[![Ponto Flutuante Afundando (2)](http://i.imgur.com/mqHh0wA.png)](/images/10726739335_b353225b51_o.png)

##### Corrigindo o incorrigível

Há uma forma de arredondamento [já disponível no C99](http://stackoverflow.com/questions/8316509/difference-dev-cpp-and-microsoft-visual-c-math-h) (mas não no Visual Studio 2010) que pode ser útil para esses casos. A única coisa que é preciso fazer é arredondar os valores antes do cálculo:

```
#include <iostream>

double round(double r)
{
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

int main()
{
	double d1 = 2358.93;
	double d2 = 1386.93;
	double d3 = round(d1) - round(d2);

	std::cout << "d1: " << d1 << "\n";
	std::cout << "d2: " << d2 << "\n";
	std::cout << "d1 - d2 = 3d: " << d3 << "\n";
	std::cout << "d3 == 972.0: " << std::boolalpha << ( d3 == 972.0 ) << "\n";
}

```

É uma decisão arbitrária essa de arredondar para cima, mas se for adotada em todo o sistema (e já fazendo parte de um padrão, no caso, o C99), não deverão existir problemas de interpretação de cálculos entre os componentes.

O mercado financeiro agradece =).

**UPDATE**

Não estou de acordo com o armazenamento de valores monetários em doubles em vez de inteiros pelo simples motivo que **não há moedas no sistema financeiro com unidades que se dividem ad infinitum**. Por consequência, existe sempre uma unidade básica e indivisível (que no caso do Brasil é o centavo de real). Ou seja, como o objetivo é contar o total dessas unidades **que não se dividem**, o uso de inteiros é brainless.

**UPDATE 2**

Existe uma discussão exatamente sobre isso no [Grupo C/C++ Brasil](https://groups.google.com/forum/#!topic/ccppbrasil/uzn6i0PJi8UEu), que recomendo a leitura, o que me levou a escrever o post. Particularmente, sigo o raciocínio do Pedro Lamarão.
