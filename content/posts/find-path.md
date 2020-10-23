---
date: "2020-07-01"
link: "https://vcpkg.readthedocs.io/en/latest/examples/installing-and-using-packages/"
tags: [ "blog" ]
title: "Find Path ou Por Que O Vcpkg Não Colocou o Path da Minha Biblioteca?"
---
Algumas bibliotecas portadas para o vcpkg, gerenciador de pacotes direto do fonte da Microsoft, não vêm exatamente como esperamos que elas venham em ambientes mais estáveis como UNIX-like. A GLib, por exemplo, uma biblioteca fenomenal se você deseja trabalhar com um framework puramente em C, está disponível pelo vcpkg através do pacote glib, mas vem encapsulado no namespace unofficial::glib::glib. Isso ocorre porque este não é um port oficial.

Se você estivesse em um ambiente UNIX precisaria fazer malabarismos com o PkgConfig, o gerenciador de pacotes do GTK (onde a GLib pertence). No entanto, depois de configurado, tudo o que precisaria fazer é incluir uma macro para os diretórios de include e outra macro para os diretórios de libraries e o programa compilaria. No caso do Windows essa macros não existem.

Lendo a documentação de como instalar o SQLite na documentação do vcpkg me deparei com uma informação até então oculta para mim: "Unlike other platforms, we do not automatically add the include directory to your compilation line by default. If you're using a library that does not provide CMake integration, you will need to explicitly search for the files and add them yourself using find_path and find_library."

Então tá. Feito isso, e rodando o cmake com o -DCMAKE_TOOLCHAIN_FILE passando o diretório de instalação do vcpkg, tudo se resolve. O solution do Visual Studio finalmente consegue encontrar os includes e libraries da glib. Ou qualquer outra biblioteca portada que você queira usar.
