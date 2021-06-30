---
categories:
- blog
date: '2020-08-24'
title: CPU Fritando com Intel Turbo Boost
---

É a segunda vez que isso acontece e esqueci quando foi a primeira. O cooler do notebook começa a assoprar que nem louco e em poucos minutos o computador desliga. O processo se repete, sempre que faço alguma atividade que exige mais processamento. Baixo o HW Monitor da CPUID e verifico que a CPU está alcançando limites acima de 90 graus celsius, e para segurança ela se auto-desliga. A solução? Ir em opções de energia do SO e trocar o limite máximo que a CPU pode ser usada de 100% para 99%. Isso mesmo, apenas abaixe um por cento. Com isso você está desabilitando o Intel Turbo Boost, que aparentemente não conhece limites físicos e sai fritando a CPU quando é necessário. Mas isso desgasta os chips e destrói a vida útil do sistema. E minha máquina já é rápida o suficiente para conseguir viver sem mais um Boost na minha vida.