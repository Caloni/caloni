---
date: "2019-04-07"
tags: [ "code", "draft" ]
title: "Code Jam 2019 Qualification Round"
---
Estou viajando e com poucas horas de acesso a um computador, mas os dois primeiros desafios do Code Jam esse ano foram tão simples que sequer precisaram de meia-hora. Isso para um chinês, campeões em campeonatos de programação, deve ser equivalente a cinco minutos com um código C enxuto. Mas estou apenas aprendendo.

Resuminho: o problema é receber um número e retornar dois números cuja soma seja igual ao primeiro. A única restrição é que nesses números não poderá ter o algarismo quatro.

Solução: copiar como string o número para o primeiro deles e colocar zero no segundo; sempre que houver a incidência do caractere '4' trocar por '3' no primeiro número e '1' no segundo (ou a soma que lhe convier).


Resuminho: tem que atravessar um labirinto formado por quadrados de N x N começando acima à esquerda saindo abaixo na direita. Enviar uma string com os comandos E ou S (East/South) para sair do labirinto. A pegadinha é não repetir nenhum dos comandos de uma garota que resolveu o labirinto antes.

Solução: essa pegadinha é o que ironicamente resolve o problema, pois basta inverter os comandos S e E da string recebida como o caminho da garota e ele nunca se repete e sai do mesmo jeito, pois é o labirinto mais fácil do mundo.


Resuminho: encontrar quais números primos são usados como letras do alfabeto baseado em uma sequência em que o primeiro número é a multiplicação do primo da primeira letra pela segunda, o segundo número é a multiplicação da segunda pela terceira e assim por diante.

Solução: tentei fazer na força bruta criando o dicionário de primos usado procurando o resto zero das divisões dos números e depois já com o alfabeto montado reproduzir as reproduções. Apesar do sample funcionar devo ter perdido pelo tempo ou um erro que não descobri.


Resuminho: descobrir quais bits não estão sendo retornados em um echo (ex: manda-se '1010' e recebe '010') com um limite de envios para o servidor (este é um problema interativo).

Solução: imaginei dividir o envio pelo número de blocos defeituosos para alternar os 0s e 1s e assim ir dividindo pela metade de acordo com as respostas até ter as posições que não estão retornando. Não cheguei a terminar o código, mas a ideia geral era que como o limite de blocos defeituosos era de 15 ou N-1 (N é o número de bits) e o máximo de chutes é 5, imaginei que a divisão de 2 elevado a 5 fosse o limite da solução.
