---
date: "2014-06-03"
tags: [ "code", "draft",  ]
title: "SS"
---
Uma das coisas mais cretinas e difíceis para os iniciantes em C++ é conseguir formatar strings de maneira fácil, rápida e indolor. Infelizmente, a biblioteca de printf da linguagem C está fechada para reforma, pois ela é extremamente error-prone e não-intuitiva. Porém, se a printf é não-intuitiva, o que dizer < < daqueles << sinais << de << flechinhas apontando para cout? Bem melhor, não?


A resposta é, pra variar, depende. Se você combinar com seu cérebro que o operador de shift que você aprendeu em C para cout não tem a mesma semântica, OK. No fundo eu acredito que os criadores dessa sobrecarga de operador pensaram sinceramente que hoje em dia quase ninguém conhece os operadores de shift binário, então tudo bem reaproveitá-lo de uma maneira mais miguxa.

Porém, isso depende da maneira com que você usa streams C++. Vai haver momentos de sua vida que você vai se questionar por que tiraram todo o controle, a elegância e simplicidade de um bom printf, quando os homens eram homens e sabiam configurar jumpers para instalar a nova placa EISA.


A questão dos streams fica mais complicada quando precisamos realizar atividades corriqueiras no código, como retornar uma string formatada, ou até mesmo transformar um inteiro em string.


Já pensou termos que criar uma função dessas sempre que quisermos converter números em string? Ou pior, ter que fazer o que fizemos dentro dessa função: declarar um ostringstream (um cout com buffer interno de string), usá-lo como cout e obter seu buffer interno através do método str. Tudo isso para converter um número para string.

Quando uma tarefa muito comum exige mais de dois passos para ser realizada é de bom tom criarmos algum código reutilizável, certo? Um código que trará de uma vez por todas a solução final!


O código acima serve bem ao nosso propósito de formatar strings em uma linha como um cout, mas retornar uma string no lugar. Ele é simples, ele é direto, ele tem defeitos que não vem ao caso (como não suportar endl), mas pode ser usado de maneira... simples e direta!


OK, o código de exemplo foi idiota, mas você pegou a ideia. Tudo que precisamos fazer para reutilizar essa pequena classe é definí-la (ss() resolve) e usá-la. Seu conversor de string retorna o buffer interno de ostringstream para nós como num passe de mágica.

Obs.: Com certeza deve existir uma centena de bibliotecas que implementam algo do gênero, só que melhor. Essa é a típica fica isolante para continuar trabalhando.

