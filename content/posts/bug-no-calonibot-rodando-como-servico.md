---
categories:
- code
date: '2020-05-10'
title: Bug no Calonibot Rodando Como Serviço
---

Esse não é o primeiro bug, nem será o último, mas serve de lição. Se quiser rodar um daemon no seu raspberrypi que atualize seu repo git de tempos em tempos ele poderá falhar, já que que roda em conta de root e essa conta não possui suas credenciais. Nem deveria, para ser sincero...

Uma maneira de tornar a leitura de seu repo relativamente segura é entregar credenciais de somente leitura para seu serviço. Foi o que eu fiz no caso do calonibot, que atualiza seu próprio repositório de tempos em tempos porque nele está contido o index.xml principal do site para ele realizar uma busca mais completa quando você pedir a ele (que é atualizado sempre que publico um novo artigo).

Para que isso funcione para repositórios configurados com chave ssh você terá que copiar essa chave para o diretório /root/.ssh, como se fosse a home do seu usuário. Depois de feito isso reinicie o serviço e ele deverá funcionar como novo.