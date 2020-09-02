---
date: "2008-05-09"
tags: [ "code", "draft",  ]
title: "Como tratar um merge no Bazaar"
---
Hoje fizemos um merge de duas versões que entraram em conflito em nosso projeto-piloto usando bzr. Isso geralmente ocorre quando alguma coisa mudou no mesmo arquivo em lugares muito próximos um do outro. Veremos um exemplo de código para ter uma idéia de quão fácil é o processo:


A execução do programa contém uma saída parecida com as linhas abaixo:


Parece que está faltando algumas quebras de linha. Além de que sabemos que nossos arquivos de entrada poderão conter até 200 caracteres por linha, o que pode gerar um desastre em nosso buffer de 100 bytes. Buffer overflow!

Para corrigir ambos os problemas foram criados dois branches, seguindo as melhores práticas de uso de um controle de fonte distribuído:


Feitas as correções devidas, o branch linebreak fica com a seguinte cara:


Em vermelho podemos notar as linhas alteradas. Uma mudança diferente foi feita para o bug do buffer overflow, em seu branch correspondente:


Agora só temos que juntar ambas as mudanças no branch principal.

Com toda razão, pensa o programador que está corrigindo o bug da quebra de linha, olhando sorrateiramente a função do meio, intocada, DoAnotherJob.

Então ele resolve fazer um pequeno fix "de brinde", desconhecendo que mais alguém andou alterando essas linhas:



Pronto. Um fonte politicamente correto! E que vai causar um conflito ao juntar essa galera. Vamos ver na seqüência:





Ops. Algo deu errado no segundo pull. O Bazaar nos diz que os branches estão diferentes, e que termos que usar o comando merge no lugar.



Usamos merge no lugar do pull e ganhamos agora um conflito no arquivo bzppilot.cpp, nosso único arquivo. Vamos ver a bagunça que fizemos?

A última coisa que um controle de fonte quer fazer é confundir ou chatear o usuário. Por isso mesmo, a maioria dos conflitos que o Bazaar encontrar nos fontes serão resolvidos usando o algoritmo "se só um mexeu, então coloca a mudança". A tabela do guia do usuário ilustra esse algoritmo em possibilidades:


conflito!!!

O ancestral é a última modificação em comum dos dois branches que estamos fazendo merge. Do ancestral pra frente cada um seguiu seu caminho, podendo existir quantas modificações quisermos.

Como podemos ver, o conflito só ocorre se ambos os usuário mexerem na mesma parte do código ao mesmo tempo. Eu disse na mesma parte do código, e não apenas no mesmo arquivo. Isso porque se a mudança for feita no mesmo arquivo, porém em locais diferentes, o conflito é resolvido automaticamente.

Em todos os conflitos de texto desse tipo, o Bazaar cria três arquivos de suporte e modifica o arquivo em conflito. Isso para cada conflito.


Podemos fazer o merge da maneira que quisermos. Se vamos usar nossa versão de qualquer jeito é só sobrescrever o arquivo.cpp pelo arquivo.cpp.THIS. Se vamos fazer troca-troca de alterações, abrimos os arquivos .THIS e .OTHER e igualamos suas diferenças, copiando-as para arquivo.cpp.

Recomendo primeiramente olhar o que o Bazaar já fez. Se houver dúvidas sobre a integridade das mudanças, comparar diretamente os arquivos THIS e OTHER.

Vamos dar uma olhada na versão criada pelo Bazaar:








Ora, vemos que ele já fez boa parte do trabalho para nós: as quebras de linha já foram colocadas e o novo define já está lá. Tudo que temos que fazer é trocar o define por 200 e tirar os marcadores, que é a junção das duas mudanças feitas no mesmo local, e que só um ser humano (AFAIK) consegue juntar:



Resolvido o problema, simplesmente esquecemos das versões .BASE, .THIS e .OTHER e falamos pro Bazaar que está tudo certo.


O controle de fonte apaga automaticamente os arquivos THIS, BASE e OTHER, mantendo o original como a mudança aceita.

Após as correções dos conflitos, temos que fazer um commit que irá ser o filho dos dois branches que estamos juntando.


A versão do branch alternativo é 1.1.1, indicando que ele saiu da revisão número 1, é o primeiro alternativo e foi o único commit. Se houvessem mais modificações neste branch, elas seriam 1.1.2, 1.1.3 e assim por diante. Se mais alguém quisesse juntar alguma modificação da revisão 1 ela seria 1.2.1, 1.3.1, 1.4.1 e assim por diante.

Um erro comum que pode acontecer é supor que o arquivo original está do jeito que deixamos e já usar o comando resolve diretamente. É preciso tomar cuidado, pois se algum conflito é detectado quer dizer que o Bazaar deixou para você alguns marcadores no fonte original, o que quer dizer que ele simplesmente não vai compilar enquanto você não resolver seus problemas.

Enfim, tudo que temos que lembrar durante um merge do Bazaar é ver os conflitos ainda não resolvidos direto no fonte e alterá-los de acordo com o problema. O resto é codificar.
