---
date: "2019-05-06"
tags: [ "code", "draft",  ]
title: "Visual Studio Unit Test (C++)"
---
Desde o Visual Studio 2015 há suporte a unit tests em C++ automatizado na IDE. Porém, a partir do VS 2017 15.5 o suporte aumentou drasticamente, vindo embutidos os suportes para as bibliotecas de teste Google Test, Boost.Test e CTest. Além, é claro, do Microsoft Unit Testing Framework for C++, o caseiro da M$.

Além disso, é possível você mesmo integrar o Visual Studio com outra lib de testes. Mas para que gastar tempo? Várias integrações já estão disponíveis no Visual Studio Marketplace. Ligue já!

OK, parei com o merchan. Até porque não ganho nada com isso. Vamos ao código.

Pelo Wizard do VS podemos criar para um projeto C++ qualquer um projeto de teste. No momento estou vendo os tipos de projeto Native Unit Test e Google Test.

Este é nosso projeto de exemplo:


Para conseguir testar o projeto principal adicione-o como referência.

Após isso basta incluir algum header que contenha os tipos, funções, classes e métodos que deseja testar e vá criando métodos de teste dentro da classe de exemplo:


Agora abrindo o jogo para você, amigo programador C++ que gosta de saber tudo que ocorre debaixo dos panos:

 - Um projeto Unit Test é apenas uma DLL com uns códigos de template.
 - Esse código já adiciona a lib de unit test da Microsoft e cria uma classe com exemplo de uso.
 - Adicione todo código do projeto original que ele precisa para compilar.

Por isso eu tirei a tranqueira de precompiled header do projeto de unit test, retirei a referência (sugestão do tutorial da Microsoft) e apenas adicionei o mesmo cpp para ser compilado.

Agora mais mágica: se você abrir a janela Test Explorer ele irá encontrar seus testes e enumerá-los!

Se você já programou um pouco em Windows com C++ já deve saber o truque: como o Unit Test é uma DLL ela simplesmente exporta os símbolos necessários para que o Visual Studio encontre o que precisa. O básico que um plugin dos velhos tempos faz: exportar interfaces com um pouco de reflection.

Se você habilitar Undecorate C++ Functions no Dependency Walker verá que ele exporta justamente uma espécie de reflection, na forma de structs:

E se você prestar atenção na ordem de exportação desse símbolos verá que o primeiro se chama GetTestClassInfo. Acabou a magia, não é mesmo?

Os headers e fontes do CppUnitTest ficam em paths do Visual Studio como VC\Auxiliary\VS\UnitTest, nas pastas include e lib. Nele é possível dar uma olhada no significado das macros e das classes disponibilizadas. Logo abaixo das macros, no arquivo principal, é possível ver como funciona o reflection:


É uma lib pequena e elegante que permite uma interação não apenas com a IDE, como poderia ser automatizada por um script, uma vez que sabe-se o funcionamento interno e algumas interfaces.

