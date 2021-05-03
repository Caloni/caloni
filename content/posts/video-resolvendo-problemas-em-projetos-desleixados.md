---
categories:
- code
date: '2016-09-01'
tags:
- draft
title: 'Vídeo: Resolvendo problemas em projetos desleixados'
---

Quem nunca teve que mexer em um projeto cheio de bugs de compilação, péssima organização, documentação e nomes de funções, classes e argumentos? Que você acaba de baixar em sua máquina e ele não compila (e você não tem a mínima noção por quê). Que a equipe que trabalha com você ouviu falar do projeto, mas nunca arregaçou as mangas e organizou. Que tal fazer isso agora?

Nesse vídeo eu exploro alguns dos erros mais comuns de projetos desleixados. Esses projetos em que o programador só se preocupa em entregar as coisas, e deixa os problemas de manutenção para o próximo trouxa que irá mexer com ele. Esse rapaz ou moça não usa a metologia PMF, que eu expliquei no artigo anterior. PMF quer dizer entregar as coisas com qualidade. Eles usam uma outra metodologia que também é simples, mas que traz gravíssimos problemas a médio e longo prazo (a despeito de ser divertida):

Pra começar, projetos que não compilam ou cheio de warnings são um sinal de que há algo de pobre no reino do GitHub. Ou é algo feito nas coxas ou é um projeto mal mantido ou é fruto de programação instintiva, que não pensa nas consequências de seus atos.

Depois, o sujeito usa headers com nomes complicados, inclui 2.653 headers diferentes (e duplicados) quando usa apenas dois, inclui headers do boost com nomes estranhos sem dar dica alguma de onde vieram. Cria funções que recebem s1 e s2 (e se chamam func2). Enfim, o pacote completo de desleixadas.

E por último, mas não menos importante: INCLUI BINÁRIOS NO GIT! TEMPORÁRIOS!

Pensando bem, meu exemplo fictício está bonito demais perto do que existe por aí. Bom, ele tem poucas linhas. É tudo questão de tempo e (des)empenho.