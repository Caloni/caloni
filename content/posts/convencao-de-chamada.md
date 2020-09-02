---
date: "2015-04-20"
tags: [ "code", "draft",  ]
title: "Convenção de Chamada"
---
Pergunta de um leitor:


Resposta do Autor: Por que C é zoado :P

OK, a verdade é que não existem (existiam?) muitas regras de sintaxe a serem respeitadas na linguagem pelo compilador. Antigamente, se não fosse colocado nenhum tipo de retorno era como se ele fosse int por default. Da mesma forma, se não colocar parâmetros vale tudo. É como se fossem os três pontinhos do printf. Afinal, você não ia querer ficar repetindo os parâmetros no .c e no .h, não é mesmo :D

Isso me lembra também que havia a declaração "arcaica" da linguagem (já era arcaica antes mesmo do padrão de 1998 sair):


Sim, sua suposição a respeito do vaargs faz todo sentido. E não, os parâmetros não são inutilizados justamente porque a função chamada pode fazer o que quiser que no retorno o chamador limpa a pilha (e o chamador sabe como ele empilhou os parâmetros-extra).

O padrão de chamada da linguagem (lembra disso?) é cdecl. Isso quer dizer que o chamador é que "limpa a sujeira" depois da chamada. Isso é o que permite o "milagre" do printf (oooohhh ooohh oooooohhhh... sons de anjos cantando) receber n argumentos.

Só vai dar problema se definir outro padrão de chamada ou se a função chamada mexer no que não devia (se esperar outros tipos ou número de argumentos, por exemplo).

Agora que sabemos disso, o comportamento do valist nem deve parecer tão mágico assim. Na verdade, apenas saber que a pilha é onde estão todas as variáveis locais e os endereços de retorno das funções é o suficiente para explorar essa área de memória.

Porém, o uso canônico na linguagem C e a forma mais educada de navegar nos parâmetros extras é usando o header stdarg.h. Isso porque C é uma linguagem independente de plataforma, e a priori não temos a mínima ideia de como os dados estão estruturados no computador. Essa visão das variáveis locais e etc é apenas algo que sabemos sobre a arquitetura PC (8086) porque já brincamos demais de assembly e seus registradores.


Uma versão de quem já manja dos internals da arquitetura onde está programando e não se importa com portabilidade poderia simplesmente caminhar pela pilha a partir do endereço de argc.


Repetindo: isso não é bonito, apesar de simpático. No entanto, se o objetivo é explorar a arquitetura, fique à vontade para navegar pela pilha a partir do endereço das variáveis locais.
