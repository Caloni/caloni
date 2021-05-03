---
categories:
- code
date: '2020-04-09'
title: Callback Hell
---

Foi aprendendo sobre kernel do Windows que eu descobri que a linguagem C suporta todas as abstrações que um homem crescido precisa para desenvolver sistemas. Também aprendi que você precisa ser um homem crescido para saber usar direito.

A linguagem C possui 32 palavras-chave e nenhuma parafusadeira elétrica. Existe um motivo para isso: fazer tudo na mão desenvolve o caráter. Se não desenvolve, pelo menos escancara a má pessoa que você é.

Olhe para o sistema de callbacks, por exemplo. É uma ferramenta poderosa. Com ponteiros de função e endereços de estrutura você pode chamar quem você quiser a hora que quiser. Há tantas possibilidades que é muito fácil errar.

Aí que surge o famigerado Callback Hell.

Esse termo se popularizou através da linguagem Javascript por causa que em Javascript é muito fácil deixar a coisas pra depois. Você deixa seu callback pra ser chamado uma outra hora e esquece dele. E ele faz o mesmo. E mais uma vez. E de novo. Você entendeu a ideia.

No final das contas, depurar código Javascript escrito por outra pessoa seria uma sala no inferno reservada para aqueles programadores que acharam durante a vida que resolveriam todos os problemas do mundo até às 18:00. Tudo que eles precisavam fazer era criar mais um pequeno callback no finalzinho daquela função. Como se diz em [Go Horse Power], "commit e era isso".

A linguagem C permite você fazer a mesma coisa. Basta que o endereço da estrutura que você passou como contexto do seu callback tenha um ponteiro de função que vai ser chamado passando mais um membro dessa estrutura como contexto, que irá conter outro ponteiro de função que... você entendeu a ideia.

No final das contas, depurar um código em C escrito por uma pessoa que evita resolver problemas de arquitetura criando mais um callback deve demonstrar como existem pessoas sem caráter que sabem declarar um ponteiro de função. Cuidado com essas pessoas. Elas podem te levar até uma salinha reservada no inferno.

[Go Horse Power]: /extreme-go-horse