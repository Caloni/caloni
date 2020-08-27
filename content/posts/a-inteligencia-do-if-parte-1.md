---
categories: [ "code" ]
date: "2007-06-18"
tags: [ "draft", "learning", "kernel",  ]
title: "A inteligência do if - parte 1"
---
No nível mais baixo, podemos dizer que as instruções de um computador se baseiam simplesmente em cálculos matemáticos e manipulação de memória. E entre os tipos de manipulação existe aquela que muda o endereço da próxima instrução que será executada. A essa manipulação damos o nome de salto.

O salto simples e direto permite a organização do código em subrotinas e assim seu reaproveitamento, o que economiza memória, mas computacionalmente é inútil, já que pode ser implementado simplesmente pela repetição das subrotinas. O que eu quero dizer é que, do ponto de vista da execução, a mesma seqüência de instruções será executada. Pense no fluxo de execução de uma rotina que chama várias vezes a mesma subrotina:

    sub:
      code
      ret

    routine:
      code
      call sub
      code
      call sub
      code
      call sub

Ela é, na prática, equivalente à uma rotina que contém várias cópias da subrotina na memória, uma seguida da outra.

    routine:
      code
      sub:
        code
      code
      sub:
        code
      code
      sub:
        code

A grande sacada computacional, motivo pelo qual hoje os computadores hoje são tão úteis para os seres humanos, é a invenção de um conceito chamado salto condicional. Ou seja, não é um salto certo, mas um salto que será executado caso a condição sob a qual ele está subordinado for verdadeira:

    code
    if cond:
      call sub
    code
    if cond:
      call sub
    code
    if cond:
      call sub
    code

Os saltos condicionais, vulgarmente conhecidos como if, permitiram às linguagens de programação possuírem construções de execução mais sofisticadas: laços, iterações e seleção de caso. Claro que no fundo todas essas construções não passam de um conjunto formado por saltos condicionais e incondicionais. Peguemos o while e seu bloco, por exemplo. A construção em uma linguagem de programação possui uma condicional seguido de um bloco de código que se repete enquanto a condicional for verdadeira:

    while condition:
      code

Enquanto para o programador dessa fictícia linguagem existe um controle de execução no início que determina quando o código deixará de ser executado repetidamente, para o compilador o while não passa de um salto no final do bloco para o começo de um if.

    label:
    if condition:
      code
      jump label

O for, por outro lado, possui tradicionalmente em seu início três operações: inicialização, condição e incremento. O código começa executando a inicialização e verifica a condição uma primeira vez. Após executado o bloco de código condicionado ao for o incremento será executado e mais uma vez a condição verificada. Caso seja verdadeira novamente o bloco de código volta a executar, para no final executar o incremento e verificar a condição, e assim por diante.

    for: i = 0; i < 10; i++
      code

Vendo do ponto de vista do compilador que irá transformar esta lógica em código de máquina, o for não passa de um contador que é incrementado a cada iteração com um salto incondiconal no final do bloco de código executado.

    i = 0
    label:
      if i < 10:
        code
        i++
        jump label

O switch-case, ou seleção, filtra um determinado valor em comparações de igualdade (a condição) em série. Quando é encontrada alguma igualdade verdadeira o código atrelado é executado e o código imediatamente seguinte ao switch é executado.

    switch i:
      case 0:
        code
      case 1:
        code
      case 2:
        code
      default:
        code

Essa lógica embutida nas linguagens de programação são convertidas pelo compilador em vários ifs seguidos e unidos por um else, o que torna a comparação exclusiva. No final de cada bloco de código existe um salto incondicional para o final da construção.

    if i = 0:
      code
      jump label
    elif i = 1:
      code
      jump label
    elif i = 2:
      code
      jump label
    else:
      code
    label:

Neste artigo aprendemos como todas as construções de uma linguagem de programação podem ser convertidas em um conjunto de saltos, condicionais e incondicionais. Em um próximo artigo veremos como o salto condicional pode ser implementado apenas com operações matemáticas (afinal, é só isso que temos em um computador; qualquer computador).
