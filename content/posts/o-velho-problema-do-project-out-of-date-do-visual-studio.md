---
categories:
- blog
date: '2017-02-20'
tags:
title: O velho problema do project out of date do Visual Studio
---

Acho que todo mundo já passou por isso. Você compila todo o projeto bonitinho e no final, ao depurar, ele faz aquela velha pergunta: "o projeto está desatualizado: deseja compilar novamente?". Mas como assim? Eu acabei de compilar, não faz nem cinco segundos. Está quentinho, saiu do forno agora.

![](http://i.imgur.com/x9EyDDe.png)

Às vezes o Visual Studio cria umas esquisitices que se perpetuam por todas as versões. Isso tem algum sentido. Funciona mais ou menos assim a lógica do "project out of date": se existir algum arquivo cuja data/hora eu não consigo verificar eu considero que o projeto está desatualizado. Por que? Pode ser que esse arquivo tenha que ser gerado automaticamente. Pode ser que houve erro de acesso. Pode ser várias coisas, mas ainda assim faz sentido.

Exceto quando o arquivo realmente não existe.

E isso é bem comum de acontecer em um projeto com algum refactory. Você acabou movendo alguns arquivos compartilhados entre projetos, mas em algum desses projetos o arquivo ainda está sendo apontado para o path errado, onde ele não mais existe. No entanto, por se tratar de um arquivo não-necessário para a compilação (ex: um header) não há erros na compilação. Apenas nessa detecção do Visual Studio.

O problema é que não existe nenhuma dica do que está errado em condições normais de temperatura e pressão. Para conseguiu olhar mais detalhes temos que ir em __Tools, Options__ e configurar mais saída para o build. Pelo menos como __detailed__:

![](http://i.imgur.com/VxMIlQL.png)

A partir daí teremos mais saída na janela de output do build. Logo no começo (talvez pela equipe do VS saber que isso é bem comum) há uma dica de quais arquivos exige o rebuild (você pode fazer isso apenas clicanco em build do projeto que sempre acusa como out of date):

![](http://i.imgur.com/DhX7Kj9.png)

Depois de detectado o arquivo faltante, é só removê-lo ou atualizar o path. Esse erro não deve mais acontecer e agora você só precisa compilar uma vez e sair depurando.
