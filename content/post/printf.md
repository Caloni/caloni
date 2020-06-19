---
categories: [ "code" ]
date: "2020-06-18"
tags: [ "ccpp" ]
title: "Printf"
---
Entre os segredos escondidos das funções básicas da lib padrão da linguagem C o printf e o scanf lideram o ranking. O printf possui a capacidade de alinhamento de colunas das string impressas com tamanho variável. Sabia disso? Pois é, isso não se ensina nas escolas.

A impressão básica de uma string passada como argumento com printf deve ser feita usando na string de formatação "%s". Agora, se você colocar um sinal de menos entre esses dois caracteres essa string será alinhada à esquerda. Mas o que é direita e esquerda se o tamanho usado pela impressão vai ser exatamente o tamanho da string? Aí é que entra o especificador de tamanho, logo após o opcional sinal de menos e antes do s que determina o tipo string. Dessa forma a string de formatação final para uma string variável alinhada à esquerda em uma coluna de trinta caracteres de tamanho seria "%-30s".

Porém, existe um problema com essa abordagem: a string variável pode ter mais de trinta caracteres. Nesse caso existe mais uma opção "escondida" do printf, que é especificar esse trinta em um argumento passado junto dos valores. Para isso basta trocar o número por asterisco e passar o tamanho como se passa qualquer outro valor à função, seguindo a ordem de recebimento. Por exemplo, um printf("%-30s", "minha_string") poderia virar printf("%-*s", 30, "minha_string"). Note que agora o tamanho trinta não está mais fixo no código e pode ser uma variável inteira.

Fiz um exemplo bem sucinto, que pede o nome das branches master e slave de um controle de fonte e imprime as duas no final, alinhando o nome das branches à esquerda e o número de commits de cada uma à direita, incluindo um header.


	    clean_stdin_buffer();

Executando com nomes pequenos de branches essa será a saída formatada:



Executando com nomes maiores de branches o alinhamento ainda é respeitado:


É assim que o printf resolve esse tipo de problema de saída formatada: de maneira simples e elegante, sem inventar moda nem querer "revolucionar" a computação.
