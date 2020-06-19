---
categories: [ "code" ]
date: "2017-02-06"
tags: [ "draft",  ]
title: "Android protobuf, mock configurável"
---
A comunicação oferecida pelo Protocol Buffers, uma maneira otimizada de codificar mensagens em alto nível, é uma das formas mais ideais de realizar a ponte entre cliente e servidor quando se fala de aplicativos mobile. A solução já suporta inúmeras linguagens, desde C++ (a linguagem oficial) até Java, passando por Python e .NET. Um mesmo arquivo de definição pode ser usado entre diferentes tipos de tecnologia. Este artigo mostra o caminho das pedras para compilar o protobuf para Android e de quebra mostra como é fácil fazer um mock de servidor local em uma configuração local com o gerenciador de builds do Android.

Antes de tudo é preciso saber que estou usando Windows. Provavelmente as coisas são mais simples no Linux, mas fazer o quê. De qualquer forma, a estrutura mantida pelo projeto do Protobuf para Visual Studio é boa, e compilei sem problemas a solução.

Mas, você deve estar se perguntando: se é para Android, por que C++? Bom, uma vez que você baixou os fontes do protobuf é necessário gerar o compilador. Você poderia baixar um binário compilado, mas usar direto dos fontes garante que os unit tests estão todos alinhados e que não haverão problemas de versão.

Os guias contidos nos READMEs espalhados pelo fonte, começando pelo primeiro exigido na página do GitHub, são muito bem explicados. Não deve ser nenhum problema segui-los, desde que se atente em colocar os caminhos necessários no path, como a localização do JDK (que pode ser o que vem no Android Studio, mesmo) e abrir um prompt com as variáveis de ambiente para a compilação via Visual Studio. Eu recomendo baixar uma versão estável entre as releases, e pode já baixar a 3 em diante, que contém um monte de features novas e legais.

Depois de compilar o protoc e colocá-lo no devido lugar, há uma questão importante: a versão em Java usa um gerenciador de build do Apache que funciona muito naquelas para Windows, dando erro nos testes e na instalação. Minha solução foi simplesmente usar a segunda opção descrita no README: compilar o Descriptor.proto e com ele gerar todos os .java necessários para sua compilação. Com isso fica até mais simples montar no projeto Android uma solução mais enxuta, apenas com as classes necessárias (no meu caso, pelo menos o JsonFormat e dependências).

A grande vantagem do Android Studio é que ele já escaneia os diretórios do projeto, sendo apenas necessário copiar os fontes e ele já integra no projeto. A partir daí os imports funcionam e ele compila tudo junto. Resolvido.

Para a parte do mock eu recomendo usar o sistema de variáveis do Gradle. Ele mantém uma lista de variáveis em um formato específico no arquivo app/build.gradle:


Você pode jogar direto o valor que deseja, mas há uma solução ainda mais elegante que usa um arquivo apartado chamado local.properties, onde é ideal não jogar no controle de fonte, e de onde todo desenvolvedor pode customizar. No caso de ServerMockData, ele pode ser um json com sua mensagem protobuf já certinha para uso, como se esses fossem os dados do server:


Isso pode estar errado (parênteses demais), mas você entendeu a ideia. É possível jogar um json nesse arquivo e depois o Android e o Gradle irão jogá-lo diretament em uma classe estática, a BuildConfig:


A partir dessa string é possível obter rapidamente a mensagem equivalente:


DICA: O Android Studio tem um botão esperto em sua interface onde, depois de alterado o local.properties, é possível refazer o BuildConfig.

E com isso podemos ter o protocol buffers e um sistema de mock simples e prático para a depuração e testes locais com nosso app que vai revolucionar o mundo =)
