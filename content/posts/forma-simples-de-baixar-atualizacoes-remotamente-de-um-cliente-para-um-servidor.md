---
categories: [ "code" ]
date: "2017-03-23"
tags: [ "draft",  ]
title: "Forma simples de baixar atualizações remotamente de um cliente para um servidor"
---
A forma mais simples e rápida para subir um servidor de arquivos é usar o file server embutido do python:


Para que não seja necessário instalar o Python no servidor é possível transformar essa chamada em um executável, com todas suas dependências embutidas:


Esse script pode ser compilado pela ferramenta py2exe, instalável pelo próprio Python. É necessário criar um arquivo setup.py na mesma pasta do script e através desse script gerar uma pasta dist com o script "compilado" e pronto para ser executado.


Pelo prompt de comando executar o seguinte comando que irá gerar a pasta dist:


Uma vez gerada a pasta, renomear para fileserver e copiar no servidor em qualquer lugar (ex: pasta-raiz). Executar de qualquer pasta que se deseja tornar acessível via browser ou qualquer cliente http:


Para testar basta acessar o endereço via browser.

Do lado cliente há ferramentas GNU como curl e wget para conseguir baixar rapidamente qualquer arquivo via HTTP. Para máquinas com Power Shell disponível há um comando que pode ser usado:


Porém, caso não seja possível usar o Power Shell o pacote básico do wget do GnuWin32, de 2MB, já consegue realizar o download.


E assim com poucas linhas de código já é possível iniciar um client/servidor via http que fornece arquivos de atualização. A própria versão do pacote e detalhes podem estar disponíveis na mesma pasta.

