---
categories:
- code
date: '2019-09-07'
tags:
- draft
title: 'Vcpkg: Atualizando Lib Asio'
---

Hoje tive que compilar a versão 1.13.0 do Asio para Windows, mas o vcpkg não suporta essa versão ainda, apesar de suportar uma versão (1.12.2.2). Daí entra os problemas que todo programador Windows tem para manter bibliotecas de terceiro compilando em seu ambiente, mas agora com o vcpkg isso nem é tão difícil assim. Vamos lá.

Primeiro de tudo, os pacotes disponíveis no vcpkg podem não ser os disponíveis no branch oficial, que é apenas uma base, que está sendo atualizado e mantido por uma equipe grande que responde os issues, é verdade, mas nem sempre possui as versões que precisamos no dia-a-dia. Para adicionar ou modificar os pacotes deve-se mexer na pasta port do projeto. Dentro dela há uma pasta para cada pacote disponível.

É lá que fica a pasta asio, com seus quatro arquivos: asio-config.cmake, CMakeLists.txt, CONTROL e portfile.cmake. No CONTROL temos o sumário do pacote (nome, descrição, versão), no asio-config.cmake a receita CMake para fazer o build e em CMakeLists.txt como instalar. Isso varia de pacote para pacote, mas no caso de libs como a asio ela fica no GitHub, então em algum lugar nas instruções de instalação (aqui no caso em portfile.cmake) você irá encontrar o uso da função vcpkgfromgithub.

Essa função irá obter os fontes baixando pela referência master do git, mas poderia ser outro branch ou tag. Para trocar a versão para a 1.13-0, por exemplo, existe uma tag para isso. Tudo que você precisa é mudar em HEADREF, mas para ficar mais bonito mude em REF também (além de atualizar o CONTROL, que contém informações sobre o pacote que o vcpkg irá exibir para o usuário). De início o SHA512 do download irá falhar, mas assim que você rodar o vcpkg install asio ele irá cuspir qual o hash correto. Daí é só atualizar no arquivo e rodar novamente. Feito isso o pacote é baixado, compilado e instalado exatamente como a versão 1.12.