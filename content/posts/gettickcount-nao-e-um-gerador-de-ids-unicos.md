---
categories: [ "code" ]
date: "2012-06-25"
tags: [ "draft",  ]
title: "GetTickCount não é um gerador de IDs únicos"
---
Muitas vezes uma solução intuitiva não é exatamente o que esperamos que seja quando o código está rodando. Gerar IDs únicos, por exemplo. Se você analisar por 5 minutos pode chegar à conclusão que um simples GetTickCount, que tem resolução de clock boa e que se repete apenas depois de 50 dias pode ser um ótimo facilitador para gerar IDs exclusivos durante o dia.

Porém, nada como código para provar que estamos errados:


O motivo do GetTickCount retornar números iguais remete tanto ao fato que o espaço de tempo entre uma execução e outra pode ser muito pequeno quanto ao fato de várias threads podem ser executadas efetivamente ao mesmo tempo em ambientes de dois ou mais cores.

Já o motivo do InterlockedIncrement funcionar sempre é porque aqui estamos usando uma solução de incremento atômico, ou seja, usamos a mesma base contadora e incrementamos ela em uma operação que não pode ocorrer ao mesmo tempo com outra thread.

O que aprendemos aqui? Que por mais que seja intuitiva uma solução, nunca podemos nos basear nas nossas falhas cabeças. Um computador está aí não apenas para ser mais rápido, mas para ser assertivo em nossas elucubrações. Nesse sentido, é o nosso companheiro vulcaniano.
