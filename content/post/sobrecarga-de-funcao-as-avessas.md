---
categories: [ "code" ]
date: "2012-05-20"
tags: [ "draft",  ]
title: "Sobrecarga de função às avessas"
---
> Navegando pelo Archive.org, que possibilita viajar no tempo e encontrar coisas enterradas que seria melhor deixar por lá, consegui encontrar um post que se perdeu na dobra espaço-temporal entre o old-fashioned Caloni.com.br (com direito à velha joaninha psicodélica, desenho do meu amigo t@z) e o finado CThings. No final, consegui matar a marmota, chegar a 80 milhas por hora e voltar para o presente. Enjoy it!

Alguém já se perguntou se é possível usar sobrecarga de função quando a diferença não está nos parâmetros recebidos, mas no tipo de retorno? Melhor dizendo, imagine que eu tenha o seguinte código:


É um uso sensato de sobrecarga. Mas vamos supor que eu queira uma sintaxe mais intuitiva, com o retorno sendo atribuído à variável:


Voltando às teorias de C++, veremos que o código acima NÃO funciona. Ou, pelo menos, não deveria. Só pelo fato das duas funções serem definidas o compilador já reclama:


Correto. O tipo de retorno não é uma propriedade da função que exclua a ambigüidade. Apenas a assinatura pode fazer isso (que são os tipos dos parâmetros recebidos pela função).

Pois bem. Não podemos fazer isso utilizando funções ordinárias. Então o jeito é criar nosso próprio "tipo de função" que dê conta do recado:


Pronto. Agora podemos "chamar" a nossa função criando uma nova instância e atribuindo o "retorno" a wstring ou à nossa GUID struct:


Uma vez que criamos um novo tipo, e considerando que este tipo é, portanto, diferente dos tipos wstring e GUID já existentes, devemos simplesmente converter nosso novo tipo para cada um dos tipos de retorno desejados:


E isso conclui a solução meio esquizofrênica de nossa sobrecarga às avessas:


Eis o fonte completo:


Voltando à pergunta original: penso que, com criatividade e C++, nada é impossível =)
