---
date: "2010-04-20"
tags: [ "code", "draft",  ]
title: "Typedef arcaico"
---
A API do Windows geralmente prima pela excelência em maus exemplos. A Notação Húngara e o Typedef Arcaico são duas técnicas que, por motivos históricos, são usados a torto e a direito pelos códigos de exemplo.

Já foi escrito muita coisa sobre os prós e contras da notação húngara. Já o typedef arcaico, esse pedacinho imprestável de código, ficou esquecido, e hoje em dia traz mais dúvidas na cabeça dos principiantes em C++ do que deveria. Para tentar desobscurecer os mitos e fatos, vamos tentar explicar o que significa essa construção tão atípica, mas comum no dia-a-dia.

Vejamos um exemplo típico desse pequeno Frankenstein semântico:


Bom, eu nem sei por onde começar. Talvez pelo conceito de typedef.

Um typedef, basicamente, é um apelido. Você informa um tipo e define "outro tipo".


O tipo é tudo que fica entre o typedef e o novo nome, que deve ser um identificador válido na linguagem. Por exemplo, a empresa onde trabalho fez um typedef informal do meu nome:


Se, futuramente, eu sair da empresa e entrar outro "Wanderley alguma-coisa", será possível usar o apelido novamente, bastando alterar o typedef:


> Bom, "outro tipo" é forma de dizer. Isso é uma descrição errônea em muitos livros. De fato, o compilador enxerga o mesmo tipo com outro nome, daí chamarmos o typedef de apelido, mesmo.

 


Tipos simples são fáceis de entender porque possuem seus símbolos no mesmo lugar:


Já os tipos um pouco mais complicados permite alguma mudança aqui e acolá:


Essa liberdade da linguagem, mesmo sendo um recurso útil, pode ser bem nocivo dependendo de quem olha o código:


Em algumas formas da sintaxe, além de ser inevitável, gera bastante desconfiança:


 

Antigamente, as structs eram construções em C que definiam um agregado de tipos primitivos (ou outras structs) e que poderiam gerar variáveis desse tipo em qualquer lugar, desde que informado seu nome e que se tratasse de uma struct:


Para evitar toda essa digitação, os programadores usavam um pequeno truque criando um apelido para a estrutura, e usavam o apelido no lugar da struct (apesar de ambas representarem a mesma coisa).


ou

Com a definição da linguagem C++ padrão, e mais moderna, essa antiguidade foi removida, apesar de ainda suportada. Era possível usar apenas o nome do struct como seu tipo:


Porém, isso vai um pouco além de quando a Microsoft começou a fazer código para seu sistema operacional. Naquela época, o padrão ainda estava se formando e existia mais ou menos um consenso de como seria a linguagem C++ (sem muitas alterações do que de fato a linguagem C já era). De qualquer forma, a linguagem C imperava bem mais que C++. Dessa forma, já era bem formada a ideia de como declarar uma struct: a forma antiga.


Além do uso controverso do sublinhado para nomear entidades (que no padrão foi recomendado que se reservasse aos nomes internos da biblioteca-padrão) e do uso de MAÍUSCULASNONOME (historicamente atribuído a nomes definidos no pré-processador), o uso do typedef atracado a um struct era muito difundido. E ficou ainda mais depois que a API do Windows foi publicada com essas definições.

Ora, do mesmo jeito que é feito há vinte anos: sem typedefs. O próprio paradigma da linguagem, independente de padrões de APIs, de sistemas operacionais ou de projetos específicos já orienta o programador para entender o que o espera na leitura de um código-fonte qualquer. Qualquer pessoa que aprendeu o básico do básico sobre ponteiros e structs consegue ler o código abaixo:


Agora, para entender a forma antiga, ou você se baseou no copy&paste dos modelos Microsoftianos, ou seja, decoreba, ou você é PhD em Linguagem C/C++ e padrões históricos de linguagens legadas. Se não é, deveria começar o curso agora.


Da mesma forma, o uso de uma estrutura simples de tipos mantém a lista de nomes do seu projeto limpa e clara. Compare o visualizador de classes em projetos Windows com algo mais C++ para ter uma ideia.

É claro, essa é apenas uma sugestão. Existem vantagens em sua utilização. Existe alguma vantagem no modo antigo? Existe: a Microsoft usa, e talvez mais pessoas usem. Basta a você decidir qual deve ser o melhor caminho.

De acordo com o leitor  Adriano dos Santos Fernandes, a obrigatoriedade do nome struct após seu nome continua valendo para a linguagem C padrão, assim como no compilador GCC ocorre um erro ao tentar omiti-la. Apenas na linguagem C++ essa obrigatoriedade não existe mais.

Eu não fiz meus testes, mas confio no diagnóstico de nosso amigo. A maior falha do artigo, no entanto, é usar a linguagem C como base, quando na verdade ele deveria falar sobre o uso desses typedefs em C++. Esse erro também foi corrigido no original.
