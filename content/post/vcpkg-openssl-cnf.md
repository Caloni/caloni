---
categories: [ "code" ]
date: "2019-09-17"
tags: [ "draft",  ]
title: "Vcpkg: openssl.cnf"
---
Mais uma aventura em vcpkg. Dessa vez o projeto openssl, a biblioteca de SSL open-source multiplataforma. O vcpkg divide esse port por SO, sendo o openssl-windows o port que alterei. A alteração foi enviada como PR para a Microsoft, mas no momento está apenas no repo da BitForge.

    commit 5506984bcd69a9fba9f86f9952d6ca6518f2c746
    Author: Wanderley Caloni <wanderley.caloni@bitforge.com.br>
    Date:   Tue Sep 17 13:34:39 2019 -0300
    
        Including config file openssl.cnf in installation.
    
    diff --git a/ports/openssl-windows/portfile.cmake b/ports/openssl-windows/portfile.cmake
    index 3506be9ab..22dfe8274 100644
    --- a/ports/openssl-windows/portfile.cmake
    +++ b/ports/openssl-windows/portfile.cmake
    @@ -171,11 +171,11 @@ file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)
     file(REMOVE
         ${CURRENT_PACKAGES_DIR}/debug/bin/openssl.exe
         ${CURRENT_PACKAGES_DIR}/debug/openssl.cnf
    -    ${CURRENT_PACKAGES_DIR}/openssl.cnf
     )
    
     file(MAKE_DIRECTORY ${CURRENT_PACKAGES_DIR}/tools/openssl/)
     file(RENAME ${CURRENT_PACKAGES_DIR}/bin/openssl.exe ${CURRENT_PACKAGES_DIR}/tools/openssl/openssl.exe)
    +file(RENAME ${CURRENT_PACKAGES_DIR}/openssl.cnf ${CURRENT_PACKAGES_DIR}/tools/openssl/openssl.cnf)
    
     vcpkg_copy_tool_dependencies(${CURRENT_PACKAGES_DIR}/tools/openssl)

 O que acontece é que alguns comandos executados no openssl.exe compilado e instalado do vcpkg precisam conter o arquivo de configuração disponível, como o `genrsa`:

    >openssl genrsa -out subdomain.domain.com.key 1024
    
    WARNING: can't open config file: some_path/openssl.cnf
    Loading 'screen' into random state - done
    Generating RSA private key, 1024 bit long modulus
    .........++++++
    .........................................++++++
    unable to write 'random state'
    e is 65537 (0x10001)

A compilação do openssl-windows pelo vcpkg gera o arquivo, mas o apaga após o build. Há uma checagem pós-build no vcpkg.exe que verifica se há arquivos sobrando na estrutura de diretórios que será copiada para a pasta installed/triplet após a conclusão da instalação no módulo postbuildlint. A função checknofilesindir verifica se há arquivos sobrando nos diretórios onde eles não deveriam estar e cancela a instalação. Por isso que originalmente o openssl-windows/portfile.cmake apaga o openssl.cnf gerado na pasta raiz e na subpasta debug do build.

Minha mudança foi apenas não apagar o arquivo openssl.cnf release e movê-lo para a pasta onde está localizado o openssl.exe. Dessa forma fica simples de detectá-lo, mas ainda assim é necessário apontar para a ferramenta onde ele está, definindo a variável de ambiente OPENSSLCONF ou passando como parâmetro.
