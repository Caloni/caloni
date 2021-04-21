---
date: "2007-11-15"
title: "SDelete"
tags: [ "code" ]
---
Minha vida tem que ser portátil. Existem pelo menos três lugares diferentes onde costumo ficar com um computador (não o mesmo). Por causa disso, os dados mais relevantes e que precisam fazer parte do meu sistema biológico eu carrego comigo pra cima e pra baixo em meu PenDrive e MP3Player.

Até aí tudo bem. Quer dizer, mais ou menos. Dados relevantes costumam ser sensíveis, e busco sempre manter todos os arquivos sensíveis encriptados ou com uma senha específica do programa que o abre. O grande problema mesmo é que eu sei que operações no sistema de arquivos costumam deixar lastros do que já foi escrito um dia, e que é possível reaver esses dados com um pouco de persistência e sorte. É nessa hora que entra a praticidade do SDelete, uma ferramenta da SysInternals.

Desde a versão NT o Windows segue as diretivas de segurança do C2, o que entre outras coisas quer dizer que o a reutilização de um objeto no sistema operacional será protegida. Um objeto aqui está para representar recursos da máquina em geral, como páginas de memória e setores do disco. Quando um programa pede um setor de disco livre (ou uma página de memória) para uso próprio, o Windows apaga qualquer conteúdo remanescente naquele espaço de memória, evitando assim que exista uma maneira do atacante obter dados de terceiros (e.g. arquivos protegidos ou memória do sistema) sem autorização.

![Novo setor do Windows](/img/windows-new-sector.gif)

Ou seja, desde que o Windows esteja no comando, os dados escritos por um programa não estarão disponíveis ao usuário por meio do reaproveitamento dos setores. Ficou claro?

Se ficou claro, deve ter notado o "desde que o Windows esteja no comando". Essa é uma condição sine qua non, mas que nem sempre é verdadeira. Um atacante que tenha acesso físico ao dispositivo de armazenamento (e.g. meu PenDrive) pode certamente usar outro sistema operacional (ou até mesmo o Windows em condições especiais) e vasculhar os dados que eu já apaguei, pois estes, como mostra a figura, não são apagados de fato até que um programa peça o espaço ocupado por eles.

![Apagando arquivo no Windows](/img/windows-delete-file.gif)

Para esse tipo de problema eu costumo usar um programinha esperto chamado SDelete (de Secure Delete). O que ele faz é zerar os setores não usados, da mesma forma com que o Windows faz quando um programa pede um setor não usado. Para isso, basta especificar um ou mais arquivos: sdelete <nome-do-arquivo>.

Uma outra coisa que ele faz, muito útil quando comecei a usá-lo, é apagar todos os setores não usados que existem no disco inteiro (ou uma pasta inteira). Com isso podemos começar uma vida nova. Apenas tome muito cuidado nessa hora para especificar o comando, pois um errinho no comando pode realmente fazer você começar uma vida nova: sdelete -c -s p.

O SDelete segue o padrão DOD 5220.22-M, o que quer dizer que ele está dentro das especificações da indústria que garantem a confidencialidade dos dados apagados. Além do mais, você pode especificar quantas "passadas" nos setores você deseja, para evitar aqueles ataques mais rebuscados em que é analisada a impedância das trilhas físicas de um disco magnético para obter os dados que uma vez estavam lá. É claro que isso não deve valer muito a pena se você está usando um PenDrive com memória flash =).
