---
date: "2010-04-21"
tags: [ "code", "draft",  ]
title: "Por que Long Pointer"
---
Esse artigo continua a explicação sobre os typedefs arcaicos, já que ainda falta explicar por que diabos os ponteiros da Microsoft começam com LP. Tentei explicar para minha pupila que, por ser código dos anos 80, as pessoas usavam LP para tudo, pois os CDs ainda não estavam tão difundidos.



Não colou. Então vou tentar explicar do jeito certo.

Antigamente, as pessoas mandavam cartas umas para as outras. Carta, para você, caro leitor de quinze anos, era um e-mail implementado em hardware.

Para mandar um e-mail, usamos o nome da pessoa e o domínio em que seu e-mail é endereçado, ex: nome-da-pessoa@dominio.com.br. Para mandar uma carta usamos duas informações básicas: o nome da rua e o número da casa.

Consequentemente enviamos dois comandos ao carteiro: meu amigo, vá para a rua tal. Chegando lá, encontre o número 1065.

Considere que estamos falando do mesmo bairro ou cidade, o que na minha analogia seria um computador e sua memória. Para enviar cartas para outros bairros em outras cidades (outros computadores em outras redes) teríamos que informar também outros dados, como nome da cidade e CEP.

Nesse exemplo também podemos usar o Juquinha do bairro para entregar a carta e economizarmos 10 centavos.

Agora, repare que interessante: em uma rua, cabem no máximo N casas. Se você tentar construir mais casas vai acabar invadindo o espaço de outra rua.

E, já que estamos falando do endereço do destinatário, já podemos relevar que esse endereço constitui um ponteiro em nossa analogia. Se você está usando dois dados para informar o endereço, então estamos falando de um ponteiro longo, long pointer, ou LP!

Na terminologia Intel para as plataformas 16 bits, a memória do computador era acessível através de segmentos (ruas) e offsets (números), que eram pedaços da memória onde cabiam no máximo N bytes. Para conseguir mais bytes é necessário alocar memória em outro segmento (outra rua).

Os ponteiros que conseguiam fazer isso eram chamados de long pointers, pois podiam alcançar uma memória mais "longa". Os ponteiros que apenas endereçavam o offset (número) eram chamados, em detrimento, short pointers, pois podiam apenas apontar para a memória do seu segmento (rua).

Ora, se seu destinatário está na mesma rua que você, tudo que você tem a dizer ao Juquinha é: "Juquinha, seu moleque, entrega essa carta no número 1065, e vai rápido!". Nesse caso você está usando um short pointer.

Porém, no exemplo que demos, o destinatário está em outra rua. Se o Juquinha entregar a carta no número 1065, mas na rua errada, estará errando o destinatário. Por isso é que você deve usar um long pointer e falar para o Juquinha do segmento!

"Juquinha, seu moleque safado, entrega essa carta no Segmento 0xAC89, Offset 0x496E. E vê se anda logo!"

Essa frase era muito usada nos anos 80, com seus 16 bits e tudo mais.

Com toda essa analogia, fica fácil perceber que o Windows não cabe em uma rua só. Seus aplicativos precisam de muitas ruas para rodar. Isso exige que todos seus ponteiros sejam long, pois do contrário o Juquinha estará entregando as cartas sempre nos endereços errados. Dessa forma, foi estipulado o typedef arcaico padrão para todos os tipos da API que usasse LP (Long Pointer) como prefixo:


E é por isso que, historicamente, todos os ponteiros para os apelidos da API Win32 possuem sua contraparte LP.

Com a era 32 bits (e mais atualmente 64 bits) os endereços passaram a ser flat, ou seja, apontam para qualquer lugar na memória. Se eu quisesse continuar minha analogia falaria que é o equivalente a uma coordenada GPS, também muito na moda, e que pode apontar para qualquer lugar do planeta. Eu, por exemplo, já trabalhei perto das coordenadas -23.563596,-46.653885, o que eu costumo dizer que fica bem próximo do Paraíso =).

De uns anos pra cá, existem novos typedefs nos headers que permitem o uso dos apelidos Win32 apenas com um P inicial.


A escolha é livre. Assim como com o typedef arcaico.
