---
date: "2017-02-08"
tags: [ "code", "draft",  ]
title: "Pacotes perdidos do NuGet em projetos C++ no Visual Studio"
---
É muito bom (para quem gosta) usar a IDE e viver feliz sem precisar se preocupar em digitar comandos estranhos no prompt. Porém, essa vida acaba quando ocorre o primeiro erro inexplicável, aquele tipo de erro que não importa onde você olhe, não há nada para olhar. Até você apelar para ferramentas de macho.

Que nem hoje de manhã, quando fui inocentemente baixar uma versão limpa do tiodb e após baixar todos os pacotes do NuGet, o gerenciador de pacotes do Visual Studio (inclusive para C++, agora) acusou a falta do boost, sendo que ele havia acabado de baixá-lo.

Os pacotes do projeto ficam todos na raiz do diretório da solução na sub-pasta packages. Observando o que foi baixado lá, verifiquei que a versão do boost estava ok: ele havia baixado a 1.61 como pedido, mas o erro dizia respeito justamente a um desses pacotes.


O maior problema disso é que não há muitas opções na IDE que resolvam. O arquivo packages.config deveria manter essas dependências, o que de fato ele faz. As opções do projeto (as abinhas do Visual Studio onde ficam as configurações) não possuem nada relacionado ao NuGet.


Então não tem jeito. Há algo de podre dentro desse projeto e o próprio Visual Studio não vai resolver. Grep nele!


Note (e é preciso prestar atenção!) que o projeto server/tio/tioserver.vcxproj referencia a pasta packages como se ela existisse dentro do projeto. Porém, como já sabemos, ela existe na raiz da solution, que fica duas pastas "para trás". Isso nos indica que talvez o NuGet ainda não esteja tão redondo e que um possível teste é mudar esses valores na mão e ver o que acontece.



Recarregado o projeto no Visual Studio após a intervenção cirúrgica, tudo voltou a funcionar. A lição de hoje é: nunca confie completamente em uma IDE. Às vezes o bom e velho grep e o bom e velho editor de sua escolha podem resolver uma situação.
