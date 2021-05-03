---
categories:
- draft
- blog
date: '2013-04-02'
title: Depuração na nuvem com o novo Visual Studio
---

Uma das novidades do futuro Visual Studio pouco comentada ainda em fóruns por seu caráter sigiloso e ainda em testes (mas que pode facilmente ser observada pela engenharia reversa dos binários do Visual C++) é a possibilidade de depurar trechos de código "na nuvem", ou seja, dentro dos gigantescos servidores de clusters de serviços de escalabilidade da Amazon, do Google e, claro, da Microsoft.

[![new-mobile-project](http://i.imgur.com/Otu88WE.png)](/images/new-mobile-project.png)

Já é conhecido que será possível inserir comentários no código-fonte com o formato @nickname e incluir na listagem de bugs o estilo das #hashtags para que programadores vinculados à sua rede social possam enxergar referências a outros programadores e verificar o Developer TrendTopics, como um #blame-joel-on-software. Porém, o que poucos sabem, é que será também possível depurar as APIs de redes sociais em tempo real. Ou seja, caso seja usado o método Twitter::Tweet(), logo após o retorno da chamada será possível aguardar por uma resposta dos usuários envolvidos:

    
    Twitter::Tweet
    push ebp
    mov ebp, esp
    000007f9`bd590000 call __internal_tweet
    000007f9`bd5900ac call _checkesp
    000007f9`bd5900af ...
    000007f9`bd5900ff ...
    000007f9`bd59015f <span style="color: #ff0000;">call __internal_wait_for_replies</span>
    000007f9`bd59017f pop esp
    ...

Ou seja, logo será possível além de perder horas navegando em saites de rede social perder também horas depurando os comentários e respostas das pessoas nessas redes direto do Visual Studio. É a Microsoft pensando nos programadores que gostam de <del>perder tempo</del> se envolver com pessoas (ainda que virtuais) e discussões acaloradas sobre tópicos irrelevantes e absurdos (ainda que virtuais).