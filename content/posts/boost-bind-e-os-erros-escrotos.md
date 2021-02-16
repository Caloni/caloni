---
date: 2018-10-01T16:34:25-03:00
title: "Boost.Bind e os Erros Escrotos"
tags: [ "draft", "blog" ]
desc: "Um pequeno desabafo quando encontramos aqueles erros odiáveis de compilação da Boost (em um exemplo simples)."
---
Estou voltando a programar algumas coisas no boost. Algo que eu perdi ao me isolar do movimento de modernização do C++ foi a capacidade brilhante da biblioteca boost em encapsular e abstrair conceitos de engenharia de software de maneira portável e mantendo a filosofia por trás da STL, que ainda é a melhor maneira de trabalhar algoritmos já criada em qualquer linguagem de programação séria.

Isso não quer dizer que a **linguagem C++** está indo para um bom caminho. Muito pelo contrário. Uma miríade de questões semânticas dividem opiniões e nunca resolvem de fato problemas do mundo real. Verdadeiros arcabouços masturbatórios, o comitê da linguagem se debate em vão quando tenta buscar maneiras de tornar uma linguagem arcaica em um exemplo de expressividade.

Isso às vezes não importa muito para o dia-a-dia, mas outras vezes importa. Veja o caso da biblioteca **Boost.Bind**, uma das mais antigas a entrar para o projeto. Sua função é simples: expandir o conceito do `std::bind` para quantos argumentos for necessário. Isso foi criado na época com a ajuda de inúmeros overloads da função (em modo template), mas hoje é possível fazer com variadic templates. Seu uso é simples, intuitivo, direto, e resolve muitos problemas de encaixe de código:

```c++
#include <iostream>
#include <boost/bind.hpp>

template<class Handler>
void CallHandler(Handler&& handler)
{
    handler();
}

void handler1(int x, int y)
{
    std::cout << "handler1: x=" << x << ", y=" << y << std::endl;
}

int main()
{
    CallHandler(boost::bind(handler1, 10, 20));
}
```

No entanto, o que era para ser um uso simples e direto de uma feature bem-vinda ao cinto de utilidades do programador C++ se transforma em um pesadelo quando as coisas não se encaixam tão bem:

```c++
#include <iostream>
#include <boost/bind.hpp>

template<class Handler>
void CallHandler(Handler&& handler)
{
    handler();
}

void handler1(int x, int y)
{
    std::cout << "handler1: x=" << x << ", y=" << y << std::endl;
}

void handler2_fail(int x, int y, int z)
{
    std::cout << "handler1: x=" << x << ", y=" << y << ", z=" << z << std::endl;
}

int main()
{
    CallHandler(boost::bind(handler1, 10, 20));
    CallHandler(boost::bind(handler2_fail, 10, 20));
}
```

Vou plotar aqui todas as mensagens de erro para sentir o drama:

```
1>------ Build started: Project: boost_bind_result_type_error, Configuration: Debug Win32 ------
1>boost_bind_result_type_error.cpp
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\bind.hpp(75): error C2825: 'F': must be a class or namespace when followed by '::'
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\bind.hpp(1284): note: see reference to class template instantiation 'boost::_bi::result_traits<R,F>' being compiled
1>        with
1>        [
1>            R=boost::_bi::unspecified,
1>            F=void (__cdecl *)(int,int,int)
1>        ]
1>c:\projects\caloni\static\samples\boost_bind_result_type_error\boost_bind_result_type_error.cpp(23): note: see reference to class template instantiation 'boost::_bi::bind_t<boost::_bi::unspecified,void (__cdecl *)(int,int,int),boost::_bi::list2<boost::_bi::value<T>,boost::_bi::value<T>>>' being compiled
1>        with
1>        [
1>            T=int
1>        ]
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\placeholders.hpp(54): note: see reference to class template instantiation 'boost::arg<9>' being compiled
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\placeholders.hpp(53): note: see reference to class template instantiation 'boost::arg<8>' being compiled
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\placeholders.hpp(52): note: see reference to class template instantiation 'boost::arg<7>' being compiled
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\placeholders.hpp(51): note: see reference to class template instantiation 'boost::arg<6>' being compiled
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\placeholders.hpp(50): note: see reference to class template instantiation 'boost::arg<5>' being compiled
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\placeholders.hpp(49): note: see reference to class template instantiation 'boost::arg<4>' being compiled
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\placeholders.hpp(48): note: see reference to class template instantiation 'boost::arg<3>' being compiled
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\placeholders.hpp(47): note: see reference to class template instantiation 'boost::arg<2>' being compiled
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\placeholders.hpp(46): note: see reference to class template instantiation 'boost::arg<1>' being compiled
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\bind.hpp(75): error C2510: 'F': left of '::' must be a class/struct/union
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\bind.hpp(75): error C3646: 'type': unknown override specifier
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\bind.hpp(75): error C4430: missing type specifier - int assumed. Note: C++ does not support default-int
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\bind.hpp(1284): error C2039: 'type': is not a member of 'boost::_bi::result_traits<R,F>'
1>        with
1>        [
1>            R=boost::_bi::unspecified,
1>            F=void (__cdecl *)(int,int,int)
1>        ]
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\bind.hpp(1284): note: see declaration of 'boost::_bi::result_traits<R,F>'
1>        with
1>        [
1>            R=boost::_bi::unspecified,
1>            F=void (__cdecl *)(int,int,int)
1>        ]
1>Done building project "boost_bind_result_type_error.vcxproj" -- FAILED.
========== Build: 0 succeeded, 1 failed, 0 up-to-date, 0 skipped ==========
```

Este é o erro encontrado usando o último Visual Studio (2017 15.9.0 Preview 2.0) e o Boost 1.68.0. A primeira linha deveria significar alguma coisa (que é para onde todo programador C++ deve olhar):

```
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\bind.hpp(75): error C2825: 'F': must be a class or namespace when followed by '::'
```

Mas não. Se olharmos para o código-fonte onde ocorreu o problema, a caixa de encaixe perfeito se quebra:

![](https://i.imgur.com/MsRp03e.png)

O que isso quer dizer? O que aconteceu? Onde que eu errei?

Claro que ao final da longa listagem de erros (que se torna ainda mais longa, dependendo de quantos argumentos sua função tem) há alguma luz no fim do túnel:

```
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\bind.hpp(1284): error C2039: 'type': is not a member of 'boost::_bi::result_traits<R,F>'
1>        with
1>        [
1>            R=boost::_bi::unspecified,
1>            F=void (__cdecl *)(int,int,int)
1>        ]
1>c:\libs\vcpkg\installed\x86-windows\include\boost\bind\bind.hpp(1284): note: see declaration of 'boost::_bi::result_traits<R,F>'
1>        with
1>        [
1>            R=boost::_bi::unspecified,
1>            F=void (__cdecl *)(int,int,int)
1>        ]
```

Mas claro que essa luz pode estar ofuscada quando os tipos dos argumentos são templates de templates de templates... enfim. Deu pra entender onde o caos consegue chegar quando se trata de harmonizar uma biblioteca perfeita com uma linguagem em constante construção.
