---
categories:
- draft
- blog
date: '2016-10-05'
title: Guardando senhas com Vim
---

Eu já sabia que havia um sistema de criptografia de arquivos no Vim. Isso pode ser útil para textos secretos, ou para enviar qualquer bobagem para outra pessoa que sabe de uma senha que só vocês conhecem. Porém, o método default de criptografia dele não me animava. O pkzip é usa um algoritmo fraco, e os inúmeros programas que quebram zips encriptados estão aí para demonstrar. Além do mais, o blowfish da versão 7 do Vim tem problemas em gerar seu salt que favorece ataques de força bruta [tão baratos quanto um XOR](https://dgl.cx/2014/10/vim-blowfish). E é aí que entra em cena o Vim 8.

A nova versão do meu editor favorito não apresenta o defeito do algoritmo blowfish anterior, ou apresenta, mas dessa vez fornece uma versão atualizada (claro que, por razões de compatibilidade, foram mantidos os algoritmos anteriores).

O que eu gosto no modelo do Vim de encriptar arquivos é que eles são encriptados apenas na escrita, e na leitura o usuário deve digitar a senha. Se a senha não correponder ao que foi usado para encriptá-lo, não há mensagem de erro: o editor irá simplesmente exibir o lixo gerado pela sua senha errada. Isso gera uma situação vantajosa e uma perigosa.

A vantajosa é que não há como automatizar um brute force em cima de arquivos encriptados pelo Vim, pois não há muitos sinais de que o arquivo foi desencriptado. Claro, por amostragem de texto é possível saber se a senha foi ou não satisfatória, mas a beleza está em não existir nada específico na estrutura do editor que diga se a senha foi ou não bem sucedida.

A perigosa é que uma vez que você digite a senha errada, muito cuidado com o lixo que você verá no seu buffer. Se por força do hábito for salvar o conteúdo, poderá perder o conteúdo do arquivo original, que estava encriptado com uma senha que você conhecia, mas que agora foi salvo após ter sido desencriptado com a senha errada. Ou seja, não há como reaver o conteúdo original a não ser com muito suor.

O mais prático de tudo é usar esse modelo de arquivo encriptado pelo Vim para salvar senhas. Um arquivo de senhas pode ser tão simples quando login/senha de todas as senhas que você deseja guardar, e tão bem protegido quanto a força de sua senha master. Nada mais, nada menos. De quebra, um arquivo pequeno cujo backup pode ser sincronizado instantaneamente na nuvem (usando Google Drive, Dropbox ou One Drive), ou até mantido em um controle de fonte (embora ele seja tratado como binário).

Se você gostou desse modelo, seguem os comandos para pesquisar (:help <comando>):

```
; define o algoritmo que será usado para encriptar arquivo
:set cm=blowfish2

; define senha de criptografia ao salvar arquivo
:X
```

Este post foi inspirado em meu próprio uso do Vim, mas mais inspirado ainda depois de ler [o artigo da invert](https://invert.svbtle.com/using-vim-as-a-password-manager).