---
date: "2020-06-04"
tags: [ "blog" ]
title: "Azure Missing Lines: Submodules no Git (SSH Version)"
---
É curioso como os problemas mais triviais não são resolvidos em ferramentas feitas para resolver esses problemas. No Azure Pipelines existe um fluxo padrão para configurar um build em que você primeiro cria uma tarefa para obter o código de um repositório git remoto e em seguida configura, compila e empacota através de uma máquina chamada de agente. O problema surge logo nesses primeiros passos, para desespero do iniciante.

Para se autenticar no repositório remoto é claro que a ferramenta irá se integrar por algum endpoint com o serviço, seja BitBucket, GitHub ou outros. Uma conta desse serviço é usada e o acesso está liberado. Porém, se o repositório possui submodules, e estes foram configurados como acessos via ssh, a automação do Azure já para de funcionar neste momento.

A causa desse bug é simples: não existe ambiente para as chaves SSH estarem configuradas antes de existir um agente (uma máquina) onde o build irá acontecer. A correção, felizmente, também é simples, apesar de inapropriada: primeiro deve-se baixar o repo sem submodules, instalar a chave SSH, e apenas agora iniciar e atualizar os submodules.
