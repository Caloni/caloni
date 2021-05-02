---
date: "2019-09-17"
link: "/code/vcpkg-openssl-cnf.patch"
categories: [ "code" ]
title: "Vcpkg: openssl.cnf"
---
Mais uma aventura em vcpkg. Dessa vez o projeto openssl, a biblioteca de SSL open-source multiplataforma. O vcpkg divide esse port por SO, sendo o openssl-windows o port que alterei. A alteração foi enviada como PR para a Microsoft, mas no momento está apenas no repo da BitForge.

O que acontece é que alguns comandos executados no openssl.exe compilado e instalado do vcpkg precisam conter o arquivo de configuração disponível, como o genrsa. A compilação do openssl-windows pelo vcpkg gera o arquivo, mas o apaga após o build. Há uma checagem pós-build no vcpkg.exe que verifica se há arquivos sobrando na estrutura de diretórios que será copiada para a pasta installed/triplet após a conclusão da instalação no módulo postbuildlint. A função checknofilesindir verifica se há arquivos sobrando nos diretórios onde eles não deveriam estar e cancela a instalação. Por isso que originalmente o openssl-windows/portfile.cmake apaga o openssl.cnf gerado na pasta raiz e na subpasta debug do build.

Minha mudança foi apenas não apagar o arquivo openssl.cnf release e movê-lo para a pasta onde está localizado o openssl.exe. Dessa forma fica simples de detectá-lo, mas ainda assim é necessário apontar para a ferramenta onde ele está, definindo a variável de ambiente OPENSSLCONF ou passando como parâmetro.
