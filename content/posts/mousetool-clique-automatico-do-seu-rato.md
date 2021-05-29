---
categories:
- code
date: '2008-05-21'
tags:
title: 'MouseTool: clique automático do seu rato'
---

Bem, como a maioria de vocês já sabe, eu realmente não gosto de mouses. Apesar disso, respeito os usuário que usam-no e até gostam dele. Essa é a razão por que estou escrevendo mais uma vez sobre isso. Dessa vez, irei mostrar um programa que eu uso todos os dias: MouseTool, para os usuários que  não usam o mouse, mas gostam dele.

O principal objetivo do programa é evitar de clicar no mouse, simulando um clique toda vez que o usuário pára de mover o ponteiro. E é só isso: simples, eficiente e mouseless =).

Existem algumas outras opções como arrastar-e-soltar e clique-duplo, ambas disponíveis pelo próprio programa através de atalhos do teclado ou mudança de estado, situação onde o usuário antes pousa o ponteiro sobre a ação desejada e depois pousa o ponteiro sobre o alvo, dessa forma alternando entre os três modos.

O MouseTool originalmente foi uma ferramente de fonte aberto. Isso significa que a última versão do código-fonte está disponível, certo? Errado. Na verdade, eu não consegui, por mais que tentasse achar,  a versão para baixar do código.

Felizmente meu amigo [Marcio Andrey] já havia baixado o fonte algum tempo atrás e, assim como eu, ele gostaria de torná-lo disponível para todos que gostassem de usá-lo e alterá-lo. Por isso que estou publicando-o aqui. Ele é gratuito e aberto. Façam o que quiserem com ele =).

Vamos aproveitar o código-fonte e mostrar como explorar um código não escrito por nós. Normalmente as primeiras coisas a fazer são: baixar o arquivo compactado e descompactá-lo dentro de uma nova pasta. Dessa forma encontramos o arquivo de projeto (nesse caso, MouseTool.dsw) e tentamos abri-lo. Falhando de início miseravelmente porque acredito que ninguém mais utilize a versão do Visual Studio que abre isso.

Normalmente programadores de projetos de fonte aberto estão acostumados a obter os arquivos-fonte, modificá-los, publicá-los e assim por diante. Porém isso não é quase nunca verdade para programadores Windows de aplicativos estritamente comerciais. É necessário se reajustar à nova cultura para aproveitar os benefícios da política de fonte aberto.

Por exemplo, dados os arquivos-fonte, nós podemos explorar algumas partes interessantes de coisas que gostaríamos de fazer em nossos próprios programas. São trechos pequenos de código que fazem coisas úteis que gastaríamos algumas horas/dias para pesquisar na internet e achar a resposta procurada. Através de um projeto de fonte aberto, conseguimos usar um programa e ao mesmo tempo aprender seu funcionamento. E a principal parte é: nós temos o fonte, mas não os direitos autorais.

Subi um repo no [GitHub] para baixar o programa; faça bom uso dele.

PS: MouseTool agora tem uma versão Linux em um projeto no Source Forge! Seu nome é [GMouseTool], projeto criado por Márcio de Oliveira.
	
[Marcio Andrey]: http://marcioandreyoliveira.blogspot.com/search/label/GMouseTool
[GitHub]: https://github.com/Caloni/mtool
[GMouseTool]: http://gmousetool.sourceforge.net
