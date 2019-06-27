---
title: "URI Online Judge em C: 1001"
categories: [ "code" ]
date: 2019-06-25
desc: "Fazendo exercícios de escola em C para explicar conceitos básicos da linguagem."
img: "https://i.imgur.com/qcXHxFc.png"
draft: true
---
O exercício mais básico do site [URI Online Judge](https://www.urionlinejudge.com.br/judge/pt) que você poderá encontrar é [ler dois números e imprimir a soma](https://www.urionlinejudge.com.br/judge/pt/problems/view/1001). Há muitas coisas que podemos aprender por um programa que resolva esse exercício que poderá servir para outros mais complexos:

 - Estrutura básica de um programa em C.
 - Leitura de inteiros do prompt de comando.
 - Impressão de saída no prompt de comando.

Há alguns conhecimentos extra que gostaria de passar, também:

 - Depuração do código.
 - Endereços e ponteiros.
 - Disassembly do programa.

# O Problema

Leia 2 valores inteiros e armazene-os nas variáveis A e B. Efetue a soma de A e B atribuindo o seu resultado na variável X. Imprima X conforme exemplo apresentado abaixo. Não apresente mensagem alguma além daquilo que está sendo especificado e não esqueça de imprimir o fim de linha após o resultado, caso contrário, você receberá "Presentation Error".

## Entrada

A entrada contém 2 valores inteiros.

## Saída

Imprima a mensagem "X = " (letra X maiúscula) seguido pelo valor da variável X e pelo final de linha. Cuide para que tenha um espaço antes e depois do sinal de igualdade, conforme o exemplo abaixo.


| Exemplos de Entrada | Exemplos de Saída |
| ------------------- | ----------------- |
| 10 <br> 9           | X = 19            |
| -10 <br> 4          | X = -6            |
| 15 <br> -7          | X = 8             |


## Estrutura básica de um programa em C

Todo programa em C para executar deve possuir pelo menos uma função definida. Essa função, por convenção (pode ser alterado de acordo com o ambiente) tem o nome especial `main`. Tudo que você colocar dentro dessa função será executada no início, e apenas ela será executada, do começo ao fim, e o programa termina, o que quer dizer que para chamar outras funções você deverá fazer dentro dela ou indiretamente através de uma função chamada por ela. Mas você não precisa se preocupar com isso agora, pois o exercício é simples e apenas o `main` irá bastar. No entanto, para concluir o exercício será necessário chamar funções já escritas e disponíveis na biblioteca de funções C (`libc`).

No entanto, vamos começar olhando para sua estrutura básica:

```c
int main()
{
}
```

E é isso. Ao compilar esse programa essa função `main` será chamada e executará todo o código contido dentro dela, irá retornar para o ambiente criado para sua execução (geralmente criado pela `libc` antes de chegar no `main`) e o programa irá terminar. No momento todo o código contido dentro dela é nenhum, e ela deveria retornar um inteiro aleatório contido na pilha de chamadas de acordo com o padrão C89 e 0 no caso do padrão C99, pois sequer estamos retornando algo para quem nos chamou, embora por definição `main` deva retornar um inteiro (`int`).

Vamos, então, pelo menos retornar algo útil para o ambiente de execução de nosso programa:

```c
int main()
{
    return 0;
}
```

Agora o nosso programa em C está retornando o valor `0` para o ambiente de execução. Geralmente se usa o inteiro retornado para detectar algum erro na execução do programa. Zero indica que não há nenhuma erro. Logo, nossa execução foi um sucesso =)

Mas nosso exercício ainda não terminou. Está apenas começando, na verdade.

## Leitura de inteiros do prompt de comando

Para interagir com o mundo externo, seja o prompt de comando onde esse programa irá executar, é necessário alguma função que faça uma ponte entre nós, o programa, e o sistema operacional, responsável por mostrar coisas na tela, ler a entrada do teclado, mover o mouse, acessar o disco, etc. A linguagem C não possui em si nada que faça essa ponte, mas seu padrão define um grupo de funções previamente criadas e compiladas que deve estar disponível no ambiente de compilação e tem seu comportamento bem definido, de forma que podemos usar essas funções para fazer coisas úteis e se comunicar com o mundo externo.

Para ler entrada do prompt de comando podemos usar a função padrão `scanf`

```c
int scanf(const char *format, ...);
```

Acima podemos ver como está definida a assinatura do scanf. Essa assinatura pode ser encontrada no header padrão `stdio.h`. Apenas precisamos incluir ele e já é possível chamar `scanf`. Porém, antes de chamar é preciso entender como chamar.

O `scanf` é uma função que recebe um número de argumentos variável. Isso é o que quer dizer os três pontinhos após o parâmetro format. O primeiro parâmetro, chamado de format, esse sim, precisa ser passado. Ele é um const char*, o que quer dizer o endereço de  um char, mas na prática é uma string C: o endereço para o início de um array de chars terminado em zero.

Agora, eis a parte complexa, que muitos programadores iniciantes nunca entenderão e preferem não entender: os outros argumentos que podem ser passados dependem do que a string C passada em format irá conter. Existe um protocolo de comunicação entre a função `scanf` e quem chama. Quem chama deve saber como passar um format direito.

E como se passa ele direito? Bom, você precisa dizer através da string em format quais os tipos das variáveis que pretende preencher, e para preenchê-las você passa como próximos argumentos os endereços dessas variáveis.

## Impressão de saída no prompt de comando


## Depuração do código


## Endereços e ponteiros


## Disassembly do programa

