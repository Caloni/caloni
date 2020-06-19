---
categories: [ "code" ]
date: "2008-02-27"
tags: [ "draft",  ]
title: "Conversor de Houaiss para Babylon - parte 1"
---
Este artigo é sobre desmontar e montar novamente. Iremos descobrir como as entradas do dicionário Houaiss eletrônico estão gravadas em um primeiro momento, para depois remontarmos essa informação de maneira que ela possa ser usada em outro dicionário de uso mais flexível, o Babylon. Ou seja, este não é um guia de vandalismo. Estava apenas querendo usar um dicionário de qualidade excelente em outro dicionário cuja interface é muito boa.

Considero o Houaiss o melhor dicionário da atualidade, uso todo santo dia e tenho todo o respeito por ele. Possuo uma cópia legalizada exatamente por isso. Além, é óbvio, pelo escandaloso cinismo que seria se eu, desenvolvedor de software, pirateasse os que utilizo. Porém, acredito que tudo tenha um limite: respeito os direitos de quem desenvolve o programa se o programa se dá ao respeito de ser pago. Quer dizer, eu realmente uso muito esse dicionário, e ele é útil para mim. Logo, nada mais justo do que adquiri-lo como manda a lei.

Assim como adquiri o Houaiss, também comprei o Babylon, um programa-dicionário, cuja interface permite buscar o significado das palavras lidas no computador simplesmente clicando nelas. A qualidade de seu dicionário português embutido é medíocre, mas o que ele ganha mesmo é em sua interface fácil para acessar palavras. Exatamente por faltar um dicionário em português de peso no Babylon, e eu ter adquirido outro muito melhor, quis que ambos funcionassem juntos, ou seja, acesso o Babylon e tenho o resultado adicional desse meu dicionário tupiniquim.

O Babylon possui um mecanismo para criação de dicionários chamado Babylon Builder. É muito simples e fácil de usar (além de ser gratuito). Sabendo que possuo ambas as licenças desses dois programas me sinto mais aliviado em tentar desencriptar a base de dados do primeiro para construir um dicionário para o segundo, e assim realizar meu sonho de consumo: um Babylon com um dicionário de peso!

É necessário que, na hora da instalação, seja escolhida a opção de copiar os arquivos para o disco. Estarei utilizando o path padrão de um Windows em português, que é "C:\Arquivos de Programas\Houaiss".

A estrutura de diretórios interna da instalação é bem simples:

  * Raiz. Arquivos de ajuda, desinstalador, executável principal, etc.
  * Quadros. Figuras com conhecimentos gerais, como calendários, signos, línguas mais faladas, etc.
  * Dicionário. Provavelmente onde está todo o dicionário, cerca de 120 MB.

Se analisarmos o conteúdo dos arquivos dentro da pasta Dicionario vamos descobrir que ele se parece com "garbage nonsense", apesar de existir um certo padrão. O padrão revela que pode se tratar de uma criptografia muito simples, talvez até um simples XOR.

Sabendo que o conteúdo do dicionário está em arquivos localizados no disco, e que teoricamente o programa não deve copiar todo o conteúdo para a memória, iremos depurar o processo do dicionário de olho nas chamadas da função ReadFile.aspx) quando clicarmos em uma definição de palavra.

Ao clicar na definição de "programa-fonte", o breakpoint é ativado:



Depois da leitura, não temos muitas alternativas a não ser fazer o tracking de chamadas até que o mesmo buffer esteja desencriptado. Esse é o caminho natural das coisas, mas poderia haver complicações secundárias, como uma cópia de buffer antes de seu uso. Estou usando passos simples porque realmente foi muito simples descobrir o segredo da ofuscação.




Pois bem. Logo depois de chamar a função Houaiss2+0xb8a6c magicamente o buffer incompreensível se transformou no início da definição da palavra "programa-fonte". Como não temos o programa-fonte do Houaiss, teremos que descer mais um nível no "assemblão", mesmo.

(Note que reexecutei os passos anteriores para cair na mesma condição)



Estamos diante de um loop, que, ao analisar o valor de ecx, sabemos que se repete 0x200 vezes, que é exatamente o número de bytes lidos pela função ReadFile. Coincidência? Seria, se não estivesse bem no meio do loop a referência ao próprio buffer usado na leitura (08bbf1d0).

Acredito que para todo profissional de engenharia reversa a parte mais emocionante é a descoberta do grande segredo por trás do desafio, o porquê das coisas estarem como estão e o que fazer para desfazer a mágica da segurança: a chave!


Note que essa operação é realizada para cada byte lido do buffer usado na leitura do arquivo. Conseqüentemente, não é difício de imaginar que o valor 0x0B é a chave usada para ofuscar o dicionário em arquivo, subtraindo esse valor de cada byte. Para desfazer a ofuscação, portanto, basta adicionar novamente o mesmo valor, que é exatamente o que faz a instrução assembly acima, e o meu singelo código de desofuscação do dicionário Houaiss abaixo:


Parte da mágica já foi feita, talvez a mais importante e divertida. Daqui pra lá deixaremos o WinDbg de lado e analisaremos o formato em que o texto do dicionário é armazenado, ignorando sua ofuscação básica, que não é mais um problema. Como o artigo já está extenso o suficiente, vou deixar a continuação dessa empreitada para uma futura publicação.
