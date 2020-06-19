---
categories: [ "code" ]
date: "2009-09-09"
tags: [ "draft",  ]
title: "O boot no Windows: pré-NTLDR"
---
Conforme fui estudando para recordar os momentos sublimes do boot do Windows me deparei com o artigo mais "espetaculoso" de todos os tempos sobre esse assunto, parte integrante do livro Windows Internals e escrito pelo nada mais nada menos Mark Russinovich: Boot Process, no capítulo 5, "Startup and Shutdown".

O meu primeiro artigo sobre o boot sem Windows foi 80% escrito com o que eu já sabia de cabeça de tanto mexer na MBR  e de tanto depurar o processo de boot em 16 bits. Os artigos posteriores seriam escritos com uma pitada do que sei mais a "inspiração" da minha pesquisa. Apesar de não parecer pouco para os que não sabem inglês, deixa a desejar para os que sabem (boa parte dos meus leitores, imagino).

Nesse caso decidi salpicar a explicação com uma boa dose de reversing para aproveitarmos a caminhada e fuçarmos um pouco no funcionamento interno dos componentes de boot e ver no que dá. Antes de começar, porém, aviso que este não é um tratado sobre o sistema de boot. Eu diria que é apenas o resultado de algumas mexidas inconsequentes pelo disassembly do código de boot. Espero encontrar alguém tão curioso (ou mais) do que eu que compartilhe o que achou de todo esse processo. Antes de mais nada um mapinha para vermos até onde chegamos:

Pelo visto esse foi só o começo. O próximo passo é saber como do setor de boot chegamos ao NTLDR. O que não é nenhum segredo, uma vez que o NTLDR é um arquivo que fica na pasta raiz do sistema de arquivos. Como todos sabemos, qualquer assembly 16 bits de 400 bytes de tamanho consegue ler um arquivo de 250 KB na memória e executá-lo.

Se o NTLDR não conseguir ser encontrado, o seguinte erro será exibido:

Que usuário merece ver isso?

Bom, se ele soubesse analisar o assembly do setor de boot, seria fácil entender essa mensagem. E analisar o assembly é simples demais, quase tão simples quanto entender a mensagem acima. Tudo que precisamos é do programa Debug 16 bits, como o que já vem com o Windows ou aquele mais turbinado do FreeDOS.

Podemos usar o Debug 16 bits para abrir o setor de boot salvo em algum arquivo e analisá-lo. Esse "salvo em algum arquivo" nós podemos obter usando o HxD, um sofware bom demais que eu uso quase todos os dias da minha vida, ou para analisar os primeiros setores do disco ou ler arquivos binários que caem na minha caixa de e-mails.

Eu não vou explicar como salvar um setor do disco em um arquivo. Pelamordedeus, isso é fácil demais. É só fuçar que se acha um jeito.

Se bem que, como esse é um quase-tutorial, vão abaixo apenas algumas dicas:

(1) no primeiro setor do disco de boot, podemos encontrar a tabela de partições;

(2) nessa tabela, a partição ativa é a que começa com 0x80;

(3) existe um campo onde é possível obter o offset de onde está o primeiro setor dessa partição (em setores);

(4) uma simples conversão de Little Endian e de hexadecimal para decimal nos retorna o número do setor que precisamos;

(5) o próprio HxD nos consegue levar para esse setor, de onde podemos selecioná-lo e salvá-lo em um arquivo!

Isso é tudo o que você precisa para fazer engenharia reversa do setor de boot. Bom divertimento!

Existem duas formas que conheço para analisar o disassembly de um setor de boot pelo Debug. Para os que gostam de aventuras radicais (RPG em modo texto?) existe a análise dinâmica, que consiste em digitar no prompt do DOS o comando Debug e o nome do arquivo salvo com o setor de boot. O primeiro comando u irá desmontar os primeiros bytes do setor (e, portanto, as primeiras instruções). Eu costumo fazer isso para uma visão geral de cinco minutos.

A segunda forma de análise que exixte é para os preguiçosos que não conseguem fazer tudo no mesmo dia e optam por salvar o dump do disasssembly em um segundo arquivo. Para realizar essa proeza usando o Debug não é preciso mais que três neurônios:

(1) digite em um arquivo chamado u.bat o seguinte conteúdo:


(2) rode o debug como a linha abaixo:


(3) Pronto! Temos um a.asm com toda a saída do setor de boot. Agora podemos analisá-la e editá-la:



Se fuçarmos por um tempo esse código podemos encontrar várias coisas interessantes, como por exemplo a mensagem que é exibida quando o setor de boot não contém a assinatura padrão 0x55 0xAA em seu final:

 Outra coisa interessante é encontrar a sub-rotina que carrega blocos e blocos de conteúdo do disco na memória, utilizando-se para isso da interrupção 0x13 função 0x42: a leitura estendida!


Enfim, todo esse assembly para fazer apenas uma coisa: achar o NTLDR na diretório-raiz da partição onde estamos, carregá-lo na memória e executá-lo. O que se passa a partir daí é o que iremos abordar na futura continuação. Não perca!
