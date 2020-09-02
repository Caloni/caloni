---
date: "2007-10-26"
tags: [ "code", "draft",  ]
title: "Proteção dos membros protected"
---
Quando queremos que um membro de nossa classe seja visível apenas dentro dos métodos da classe e dentro dos métodos das classes derivadas dessa classe usamos o nível de proteção protected. Isso, é claro, não quer dizer que uma classe derivada vá ter acesso aos membros protegidos de outra:



Esse é o motivo fundamental do porquê não podermos fazer isso:


Ao acessar membros protegidos é importante o tipo da expressão que está do lado esquerdo do "." ou "->". Afinal, o nível de proteção se baseia no escopo, e as classes são um escopo. É por isso que consigo acessar os membros protegidos de um outro objeto de minha classe, mesmo sendo outro objeto:


A definição do escopo é tudo o que o compilador dispõe para saber se acessa ou não acessa um membro. Podemos ter acesso a mprotected enquanto somos do tipo Derived, mas não quando o mesmo objeto é usado como Base:


Essa proteção parece desnecessária - e até mesmo incoerente - quando lidamos com o mesmo objeto que acessa. Afinal, somos nós mesmos! Só que o compilador não sabe disso, e ele deve desconfiar de tudo e de todos para evitar esse tipo de "ataque":


Agora a proteção do compilador faz sentido. Parece um detalhe frívolo, mas depois que vi alguns programadores de respeito se debatendo pela "burrice" do compilador, imaginei que talvez houvesse mais pessoas com a mesma dúvida de se existe ou não um "bug na linguagem".
