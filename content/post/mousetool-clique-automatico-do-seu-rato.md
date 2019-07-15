---
date: "2008-05-21"
title: 'MouseTool: clique automático do seu rato'
categories: [ "blog" ]
---
Bem, como a maioria de você já sabe, eu realmente não gosto de _mouses_. Apesar disso respeito os usuário que usam-no e até gostam dele. Essa é a razão por que estou escrevendo mais uma vez sobre isso. Dessa vez, irei mostrar um programa que eu uso todos os dias: MouseTool, para os usuários que  não usam o ](http://www.codinghorror.com/blog/000825.html)_[mouse, _mas gostam dele.

!MouseTool no tray.

Existem algumas outras opções como arrastar-e-soltar e clique-duplo, ambas disponíveis pelo próprio programa através de atalhos do teclado ou mudança de estado, situação onde o usuário antes pousa o ponteiro sobre a ação desejada e depois pousa o ponteiro sobre o alvo, dessa forma alternando entre os três modos.

O MouseTool originalmente foi uma ferramente de fonte aberto. Isso significa que a última versão do código-fonte está disponível, certo? **Errado. **Na verdade, eu não consegui, por mais que tentasse achar,  a versão para baixar do código.

Felizmente meu amigo Marcio.

#### Como usar um código-fonte de terceiros

Vamos aproveitar o código-fonte e mostrar como explorar um código não escrito por nós. Normalmente as primeiras coisas a fazer são: baixar o arquivo compactado e descompactá-lo dentro de uma nova pasta. Dessa forma encontramos o arquivo de projeto (nesse caso, MouseTool.dsw) e tentamos abri-lo.

Normalmente programadores de projetos de fonte aberto estão acostumados a obter os arquivos-fonte, modificá-los, publicá-los e assim por diante. Porém isso não é quase nunca verdade para programadores Windows de aplicativos estritamente comerciais. É necessário se reajustar à nova cultura para aproveitar os benefícios da política de fonte aberto.

Por exemplo, dados os arquivos-fonte, nós podemos explorar algumas partes interessantes de coisas que gostaríamos de fazer em nossos próprios programas. São trechos pequenos de código que fazem coisas úteis que gastaríamos algumas horas/dias para pesquisar na internet e achar a resposta procurada. Através de um projeto de fonte aberto, conseguimos usar um programa e ao mesmo tempo aprender seu funcionamento. E a principal parte é: nós temos o fonte, mas não os direitos autorais.

Clique nos liques abaixo para baixar o programa, e faça bom uso dele.

	
  * Código-fonte do MouseTool 

	
  * Binários do MouseTool 

####  Atualização

MouseTool agora tem uma versão Linux em um projeto no Source Forge! Seu nome é GMouseTool, projeto criado por Márcio de Oliveira.

	
  * Página Inicial do ](http://gmousetool.sourceforge.net/)[GMouseTool 

#### Usando o MouseTool direto do Bazaar

Aproveitando que estou usando o Bazaar como controlador de fontes em meus projetos, (re)publiquei o MouseTool no formato de um repositório projeto Bazaar de gelo. Ele pode ser obtido no endereço abaixo:

http://code.launchpad.net/mtool

Para baixá-lo através do Bazaar, use o seguinte comando:

    
    bzr clone http://code.launchpad.net/mtool mtool

Será criada uma pasta chamada mtool, com todo o histórico (um) de modificações. Bom proveito.
