---
date: "2008-08-13"
tags: [ "code", "draft",  ]
title: "Quando o navegador não quer largar um arquivo"
---
De vez em quando gosto muito de um vídeo que estou assistindo. Gosto tanto que faço questão de guardar para assistir mais vezes depois. O problema é que o meu Firefox ou, para ser mais técnico, o plugin de vídeo que roda em cima do meu navegador, não permite isso. Ele simplesmente cria um arquivo temporário para exibir o vídeo e logo depois o apaga, utilizando uma técnica muito útil da função CreateFile, que bloqueia o acesso do arquivo temporário e apaga-o logo após o uso:




Muito bem. Isso quer dizer que é possível abrir um arquivo que mais ninguém pode abrir (nem para copiar para outro arquivo), e ao mesmo tempo garante que quando ele for fechado será apagado. Isso parece uma ótima proteção de cópia não-autorizada para a maioria das pessoas.

Infelizmente, tudo isso roda sob limites muito restritos: um navegador, rodando em user mode, usando APIs bem definidas e facilmente depuráveis.

Antes de iniciar a reprodução do vídeo, e conseqüentemente a criação do arquivo temporário, podemos atachar uma instância do nosso depurador do coração e colocar um breakpoint onde interessa:



Nesse momento podemos dar uma boa olhada nos parâmetros 4 e 6 da função para ver se trata-se realmente da proteção prevista (na verdade, prevista, nada; esse é um artigo baseado em uma experiência passada; vamos imaginar, contudo, que estamos descobrindo essas coisas como na primeira vez).


Como podemos ver, o modo de compartilhamento do arquivo é nenhum. Entre os flags definidos no sexto parâmetro, está o de apagar o arquivo ao fechar o handle, como pude constatar no header do SDK:

Nesse caso, a solução mais óbvia e simples foi deixar esse bit desabilitado, não importando se o modo de compartilhamento está desativado. Tudo que temos que fazer é assistir o vídeo mais uma vez e fechar a aba do navegador. O arquivo será fechado, o compartilhamento aberto, e o arquivo, não apagado.


E agora posso voltar a armazenar meus vídeos favoritos.
