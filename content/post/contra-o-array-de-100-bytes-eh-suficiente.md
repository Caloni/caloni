---
categories: [ "code" ]
date: "2018-03-11"
tags: [ "draft",  ]
title: "Contra o 'Array de 100 bytes é suficiente'"
---
Desde o C++ moderno (pós-03) o uso de arrays de tamanho fixo estão se tornando depreciados. E por um bom motivo: você nunca sabe realmente qual o tamanho que você precisa para um array de bytes até você saber. Daí a próxima grande questão é: "como gerenciar essa memória dinâmica de forma efetiva?". E a resposta moderna sempre é: "não faça isso você mesmo". Eis o porquê:


Quando lidamos com funções legadas elas se misturam de tal maneira com código novo que a merda da alocação/desalocação dinâmica manual vai se espalhando também. A não ser que a gente comece a usar o novo modelo RAII e deixe a memória ser gerenciada automaticamente:


Note que estamos obtendo o endereço do primeiro elemento do nosso vector STL porque, desde o padrão C++0x03, vetores são garantidos que serão contínuos. Essa garantia de leiaute de memória pode facilitar muitos usos de vector que estavam dependentes da implementação. O exemplo acima é apenas o mais simples deles, mas imagine que qualquer tipo de memória contígua cujo tamanho é desconhecido em tempo de compilação pode ser deixado seu gerenciamento para a STL cuidar.

Ah, e a partir do C++11 podemos usar vector::data() para obter os dados sem deferenciar o primeiro elemento. Particularmente acho mais expressiva a sintaxe dos arrays, mas fica a gosto do freguês.
