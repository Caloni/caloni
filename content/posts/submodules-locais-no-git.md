---
date: "2017-05-28"
title: "Como acessar submódulos no git inacessíveis?"
tags: [ "draft", "blog" ]
---
Quando projetos remotos usam submodules é possível que algum deles seja acessível apenas através de chaves criptográficas. Isso exige que os sub-projetos necessários para fazer funcionar seu projeto podem estar fora do seu alcance e acesso, o que irá gerar durante seus comandos __pull__ recursivos erros de ssh (publickey access).

A solução é ler a documentação e descobrir que é possível editar o arquivo .git/config para mudar a url de um submódulo inacessível pela forma do .gitmodules. Eis um exemplo de arquivo config dentro do .git:

```txt
[submodule "sbrubles"]
	url = git@github.com:user/project.git
```

Você pode localmente alterar o endereço ssh deste submodule para algo que todos têm acesso ou só você tem acesso, como uma pasta local ou o endereço https:

```txt
[submodule "sbrubles"]
	url = https://github.com/user/project.git
```

Note que isso não irá interferir em nada no repositório localizado remotamente do projeto. Dessa forma diferentes membros da equipe podem usar diferentes formas de acessar um submódulo.
