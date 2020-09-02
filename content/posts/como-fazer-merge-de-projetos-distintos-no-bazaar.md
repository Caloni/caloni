---
date: "2008-06-16"
tags: [ "code", "draft", "tools" ]
title: "Como fazer merge de projetos distintos no Bazaar"
---
O problema foi o seguinte: Nós iniciamos o controle de fonte pelo Bazaar na parte Linux do projeto, já que ela não iria funcionar pelo Source Safe, mesmo. Dessa forma apenas um braço do projeto estava no controle de fonte e o resto não.

No segundo momento da evolução decidimos começar a migrar os projetos para o Bazaar, inclusive a parte daquele projeto que compila no Windows. Maravilha. Ambos sendo controlados é uma beleza, não é mesmo?

Até que veio o dia de juntar.

O processo de merge de um controle de fonte supõe que os branches começaram em algum ponto em comum; do contrário não há como o controlador saber as coisas que mudaram em paralelo. Pois é achando a modificação ancestral, pai de ambos os branches, que ele irá medir a dificuldade de juntar as versões novamente. Se não existe ancestral, não existe análise. Como exemplificado na figura:

Acontece que existe um plugin esperto que consegue migrar revisões (commits) entre branches sem qualquer parentesco. Não me pergunte como ele faz isso. Mas ele faz. E foi assim que resolvemos o problema dos branches órfãos.

Para instalar o plugin do rebase, basta baixá-lo e copiar sua pasta extraída com um nome válido no Python (rebase, por exemplo). A partir daí os comandos do plugin estão disponíveis no prompt do Bazaar, assim como a instalação de qualquer plugin que cria novos comandos.


O comando que usamos foi o replay, que não é comando principal do plugin, mas que resolve esse problema de maneira quase satisfatória. Como era tudo o que tínhamos, valeu a pena.

O processo que usei foi de usar esse comando n vezes para buscar revisões de um branch e colocar no outro. Um grande problema com ele é que ao encontrar merges no branch origem ele se perde e o usuário tem que fazer as modificações "na mão". Deu um pouco de trabalho, mas conseguimos migrar nossos commits mais importantes e deixar o projeto inteiro, Linux+Windows, em um branch só.



