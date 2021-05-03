---
categories:
- code
date: '2020-08-04'
title: Pacotes Nuget Again
---

Agora que mexo com .net no trabalho surgem problemas de "marinheiro de primeira viagem" (na verdade já mexi com o framework, mas há muitos anos). O que me fez gastar mais horas à toa sem dúvida é o versionamento dos pacotes nuget que viram dependências simples de colocar e difíceis de mexer.

Nesse problema em específico de tratava da lib Castle.Core na versão 4.4.0. Durante a compilação tudo estava lindo e maravilhoso. Porém, na hora de rodar, a exceção de I/O dizendo que não conseguiu carregar o assembly na versão certa pula na minha frente.

Pesquisa de lá, pesquisa de cá, fuça de cá, fuça de lá, encontrei acho que pela segunda vez a solução. Se trata mesmo da versão errada sendo utilizada, mas não na compilação, mas na execução. É preciso definir a versão correta no arquivo de configuração.

Feito isso todo o mundo maravilhoso de .nerd volta a fazer sentido.