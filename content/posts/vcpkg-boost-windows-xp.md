---
date: "2019-09-16"
tags: [ "draft", "code", "draft",  ]
title: "Vcpkg: Boost para Windows XP"
---
Quem programa em C++ no Brasil geralmente precisa estar preparado para manter velharias. Boa parte do parque de máquinas das empresas usam Windows, e não estou falando de Windows 10, mas muitas vezes XP. Apesar da Microsoft ter largado uma das melhores versões do seu SO para trás, milhares de máquinas ainda rodam esse bichinho, e muitos programadores precisam manter e desenvolver em nome da compatibilidade.

Porém, o desenvolvimento de libs C++ foram aos poucos largando o suporte ao XP (em C isso não existe muito, pois é mais fácil ser portável em C), pois muitos mecanismos de SOs modernos surgiram depois, como um mutex light ou mutex apenas de read. E como eles olham para o mercado global, o Brasil acaba ficando para trás.

E isso inclui a Boost, o famoso conjunto de bibliotecas usado pelos engenheiros que gostam de complicar seu código. O suporte oficial a XP da Boost acabou na 1.60, mas é possível compilar, se você quiser, versões mais novas, como a 1.68, que usaremos neste artigo. Com ela é possível gerar uma versão compatível com Windows XP usando o builder da Boost e alguns parâmetros mágicos, como toolset e define.

O parâmetro toolset usa no caso a versão compatível para XP do conjunto de compilação do Visual Studio 2015, e o define BOOSTUSEWINAPIVERSION é colocado para suportar pelo menos Windows XP. Já o stagedir seria apenas para separar a compilação padrão para a que suporta XP e é opcional para manter duas compilações distintas. Importante lembrar que, apesar da Microsoft ter extinto o suporte a XP, até o Visual Studio mais novo possui um toolset, compilador e libs para Windows, que suporte o sistema operacional.

Esses mesmos parâmetros usados no build da Boost podem ser usados dentro do vcpkg, o compilador de pacotes multiplataforma da Microsoft. Como esperado, as libs do vcpkg compilam usando tudo do último em sua máquina: Boost, Visual Studio e o suporte ao último Windows (no caso do pacote da Boost, não, se usa o Windows Vista em diante). Mas você pode e deve modificar os ports padrões sempre que necessário. Este artigo explica como fazer partindo do zero sem receita de bolo. Vamos escanear o problema e resolvê-lo. Para isso vamos usar um exemplo bem simples da Boost.Log, que possui dependências mais novas que o Windows XP.

O status inicial e inocente de um projeto que deseja rodar para XP em Visual Studio 2015 (nosso caso de uso, poderia ser o VS mais novo) é criar um projeto que usa Boost.Log pelo wizard, instalar, se ainda não estiver instalado, o Boost.Log no vcpkg, e acabou. Só que não.

Existem erros no meio do caminho que geralmente acontecem por dois motivos. O primeiro é quando rodamos um executável de 64 bits em um ambiente 32, mas este não é o caso. O segundo é quando rodamos um executável que possui alguma DLL faltando ou funções específicas de alguma DLL, que é o caso. Para descobrir as dependências de um executável basta rodar o comando dumpbin de dentro de um terminal com as ferramentas do Visual Studio disponíveis.

Dependências de APIs relacionadas com o SRWLock dizem respeito ao Slim Read/Write Lock do Windows, implementado a partir do Windows Vista. A primeira coisa a ser descoberta pelo programador é: quem está usando essas funções? Se não está no seu próprio código, provavelmente está em uma das libs linkadas. E uma dessas libs com certeza é o Boost.Log, pelo include no código.

Note as linhas onde ::InitializeSRWLock é chamado. O escopo global indica que há uma dependência estática entre essa função API e o executável se essa parte do código for compilada, o que pode ser descoberto através da IDE do Visual Studio abrindo os arquivos e verificando se a parte onde há essas chamadas fica "cinza" (há defines que impedem essa parte de compilar), ou depurando e inserindo breakpoints nessa parte, que deverá ser chamada. O dumpbin poderia ser usado de novo caso houvesse símbolos para explorar o uso dessas funções de dentro do executável, mas por padrão a compilação do Boost não gera símbolos, tornando a tarefa ingrata, pois estará tudo em assembly sem tradução para o fonte.

Se analisarmos onde BOOSTUSEWINAPIVERSION é definido descobriremos que ele é um reflexo do famigerado WIN32WINNT, que é o define que o Windows usa para determinar qual a versão mínima que o executável deve rodar. Windows Vista é 0x0600, Windows XP é 0x0501 (com SP 2 em diante 0x0502). Isso quer dizer que devemos compilar nosso projeto indicando que pretendemos rodar em Windows XP.

E aí começam os problemas de linker.

Aparentemente a própria lib Boost.Log estará entrando em contradição com ela mesma, pois há usos dos métodos new e delete, por exemplo, entre vários. A análise da lib compilada irá nos revelar que esses nomes realmente não existem. Não há nenhum símbolo com esse namespace. Precisamos agora averiguar de onde ele vem através de algumas ferramentas como dumpbin ou direto no código-fonte do Boost. O Boost precisa ser compilado com certo define para Windows XP. Do contrário ele deve conter o namespace v2smtnt6 em sua lib. Mudando o define no nosso projeto ele irá apenas mudar a definição nos headers, mas não na lib já compilada.

Mas para isso precisamos descobrir como o Boost é compilado no vcpkg. Sabemos que ele utiliza arquivos cmake dentro de cada subpasta em port, que junto de uma série de scripts já disponíveis pela ferramenta irá executar ações de compilação, instalação, etc. De dentro do Boost.Log encontramos alguns arquivos para analisar.

Não há nada que indique a versão do Windows, mas há um include de boost-modular-build.cmake que parece útil.

Há muito mais coisa nesse cmake, incluindo definição de toolset e os define de WIN32WINNT, que está como 0x602, ou seja, acima do Windows XP. No entanto, esses flags são da compilação do Visual Studio, e não do b2.exe, o compilador do Boost. Como vimos no início do artigo, são os parâmetros para o b2.exe que precisam ser modificados. Ao analisar sua execução de dentro do próprio cmake podemos verificar que há uma variável com essas opções, o bmOPTIONS. O que faz muito sentido.

Me parece que o segredo é inserir ou modificar os argumentos dessa variável e as libs da Boost estarão automagicamente modificadas. Me parece isso hoje, horas e horas depois de analisar o build do vcpkg. Mas vou lhe economizar essas horas. Podemos realizar essa mudança pontualmente no boost-modular-build-helper, mas também devemos recompilá-lo, o que inclui suas dependências e toda a bagaça.

Eu sei, é triste, mas mais uma caneca de café, uma partidinha de xadrez, e está pronta a recompilação. Fun fact: antigamente a compilação do Boost te dava essa dica de ir fazer café.

Depois de muito trabalho voilà! Não há mais dependências das APIs muito novas e conseguimos executar nosso programa em Windows XP. Mas, mais importante que isso, o que aprendi nessa brincadeira:

 - A verificar os símbolos importados por um executável usando `dumpbin`, se certificando de que ele poderá rodar em SOs mais antigos.
 - A buscar pelo uso de funções novas pelos fontes compilados pelo vcpkg.
 - A analisar o build do vcpkg para poder modificá-lo e ser compatível com o ambiente que precisamos.
