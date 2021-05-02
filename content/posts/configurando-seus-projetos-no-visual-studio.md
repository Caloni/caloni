---
date: "2008-02-21"
categories: [ "code" ]
title: "Configurando seus projetos no Visual Studio (Multi-threaded Debug DLL /MT, /MD)"
---
Ao iniciar na arte da programação em C no Visual Studio eventualmente o programador irá querer testar seus programas rodando em outra máquina que não seja a de desenvolvimento, mandar uma versão beta para amigos, pra namorada e pro seu cachorro. Geralmente, por padrão, existem algumas dependências do programa compilado com uma DLL de runtime da versão do ambiente em que foi compilado o dito cujo, dificultando um pouco a distribuição do seu motherfucker-program.

Porém, seus "poroberemas se acabaram-se". Com o inovador configurador de projetos do Visual Studio, tudo o que você queria é possível, e ainda mais!

Nota do autor: isso não foi uma propaganda gratuita, apenas uma piada. Se fosse um verdadeiro anúncio das maravilhas do Visual Studio, eu agora estaria falando daquele tal código gerenciado e o tal do C++ CLI.

Inicialmente, se compilarmos um programa em Debug no Visual Studio 2005 teremos as seguintes dependências. kernel32 e msvcrx.dll (onde x é a versão do Visual Studio). A DLL kernel32 é nativa e sempre estará presente no Windows. Porém, a msvcr não. Ela veio junto com o pacote do Visual Studio, e se não for distribuída em outras máquinas, você não conseguirá rodar seu programa, pois isso gerará o erro de DLL não encontrada.

Bem, para resolver isso, a partir da IDE, temos que ir em Project, Properties, Configuration Properties, C/C++, Code Generation, Runtime Library.

Existem atualmente quatro tipos de runtime que você pode escolher:

 - Multi-threaded (/MT). Versão Release que não depende de DLL.
 - Multi-threaded Debug (/MTd). Versão Debug que não depende de DLL.
 - Multi-threaded DLL (/MD). Versão Release que depende de DLL.
 - Multi-threaded Debug DLL (/MDd). Versão Debug que depende de DLL.

Essas runtimes são chamada de multi-threaded porque antigamente existiam versões single-threaded dessas mesmas runtimes. Contudo, versões mais novas do Visual Studio só vêm com esse sabor mesmo.

Note que, por padrão, existem dois tipos de configuração em seu projeto: Debug (para testes) e Release (para distribuição). Convém não misturar configurações Debug com DLLs Release e vice-versa, a não ser que você tenha certeza do que está fazendo.

Pois bem. Para tirar a dependência da maldita DLL, tudo que temos que fazer é alterar a configuração, nesse caso Debug, de /MDd para /MTd. E recompilar.

E testar.

Além da dependência de DLLs, alguns casos especiais vão chiar por causa dos dados do manifesto embutidos no programa compilado. Por algum motivo que eu desconheço, o programa necessita que as DLLs estejam instaladas mesmo que no Dependency Walker não mostre nada. Nesses casos, uma arrancada do manifesto na versão Debug não fará mal algum.

Acho que esses são os únicos empecilhos iniciais para testar seu programa em outras máquinas. Sempre que ver o erro exibido no começo desse artigo, desconfie de alguma dependência que não está presente na máquina. Nessas horas, ter um Dependency Walker ou Dumpbin na mão vale ouro.
