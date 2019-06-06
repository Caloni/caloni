---
date: "2008-02-21"
title: Configurando seus projetos no Visual Studio
categories: [ "code" ]
---
Ao iniciar na arte da programação em C no Visual Studio, eventualmente o programador irá querer testar seus programas rodando em outra máquina que não seja a de desenvolvimento, mandar uma versão beta para amigos, pra namorada e pro seu cachorro. Geralmente, por padrão, existem algumas dependências do programa compilado com uma DLL de _runtime_ da versão do ambiente em que foi compilado o dito cujo, dificultando um pouco a distribuição do seu _motherfucker-program_.

Porém, seus "poroberemas se acabaram-se". Com o inovador configurador de projetos do Visual Studio, tudo o que você queria é possível, e ainda mais!

<blockquote>_Nota do autor: isso não foi uma propaganda gratuita, apenas uma piada. Se fosse um verdadeiro anúncio das maravilhas do Visual Studio, eu agora estaria falando daquele tal código gerenciado e o tal do C++ CLI._</blockquote>

Inicialmente, se compilarmos um programa em Debug no Visual Studio 2005 teremos as seguintes dependências:

[![Dependências do Hello, World](http://i.imgur.com/zobevmj.png)](/images/hello-world-depends.png)

A DLL **kernel32** é nativa e sempre estará presente no Windows. Porém, a **msvcr80d** não. Ela veio junto com o pacote do Visual Studio, e se não for distribuída em outras máquinas, você não conseguirá rodar seu programa, pois isso gerará o seguinte erro:

[![Erro de dependência por causa da DLL do Visual Studio](http://i.imgur.com/Kbd7qrR.png)](/images/hello-world-error-depends.png)

Bem, para resolver isso, a partir da IDE, temos que ir em Project, Properties, Configuration Properties, C/C++, Code Generation, Runtime Library.

[![Code Generation](http://i.imgur.com/oUXU9Dc.png)](/images/vs-code-generation.png)

Existem atualmente quatro tipos de _runtime_ que você pode escolher:

	
  * **Multi-threaded (/MT)**. Versão Release que não depende de DLL.

	
  * **Multi-threaded Debug (/MTd)**. Versão Debug que não depende de DLL.

	
  * **Multi-threaded DLL (/MD)**. Versão Release que depende de DLL.

	
  * **Multi-threaded Debug DLL (/MDd)**. Versão Debug que depende de DLL.

<blockquote>_Essas runtimes são chamada de multi-threaded porque antigamente existiam versões single-threaded dessas mesmas __runtimes.  Contudo, versões mais novas do Visual Studio só vêm com esse sabor mesmo._</blockquote>

Note que, por padrão, existem dois tipos de configuração em seu projeto: Debug (para testes) e Release (para distribuição). Convém não misturar configurações Debug com DLLs Release e vice-versa, a não ser que você tenha certeza do que está fazendo.

Pois bem. Para tirar a dependência da maldita DLL, tudo que temos que fazer é alterar a configuração, nesse caso Debug, de /MDd para /MTd. E recompilar.

[![Dependências do Hello, World - parte 2](http://i.imgur.com/UAr4ynG.png)](/images/hello-world-depends2.png)

E testar.

[![Execução do Hello World com sucesso, sem dependências.](http://i.imgur.com/sMBKol2.png)](/images/hello-world-success.png)

#### Problemas com manifesto

Além da dependência de DLLs, alguns casos especiais vão chiar por causa dos dados do manifesto embutidos no programa compilado. Por algum motivo que eu desconheço, o programa necessita que as DLLs estejam instaladas mesmo que no Dependency Walker não mostre nada. Nesses casos, uma arrancada do manifesto na versão Debug não fará mal algum.

[![Manifesto Settings](http://i.imgur.com/aA8iSA5.png)](/images/manifesto-settings.png)

#### Mais problemas?

Acho que esses são os únicos empecilhos iniciais para testar seu programa em outras máquinas. Sempre que ver o erro exibido no começo desse artigo, desconfie de alguma dependência que não está presente na máquina. Nessas horas, ter um [Dependency Walker](http://www.dependencywalker.com/) na mão vale ouro.
