---
date: "2010-04-21"
title: Por que Long Pointer
categories: [ "draft", "code" ]
---
Esse artigo continua a explicação sobre [os typedefs arcaicos](http://www.caloni.com.br/typedef-arcaico), já que ainda falta explicar por que diabos os ponteiros da Microsoft começam com LP. Tentei explicar para [minha pupila](http://www.caloni.com.br/basico-do-basico-ponteiros) que, por ser código dos anos 80, as pessoas usavam LP para tudo, pois os CDs ainda não estavam tão difundidos.

    
    <span style="color: #808000;">/** @brief Para instanciar um Bozo. @date 1982-02-21 */ 
    typedef struct _BOZO { 
       char helloMsg[100]; /* definir para "alô, criançada, o bozo chegou..." */ 
       float currentTime; /* definir para 5e60 */ 
    }
     BOZO, <strong><span style="text-decoration: underline;"><span style="color: #ff0000;">*LP</span></span></strong>BOZO;</span>

    
    <strong><span style="color: #339966;">/** @brief Para instanciar um Pokemon. @date 1996-03-01 */</span> 
    <span style="color: #0000ff;">typedef</span> <span style="color: #0000ff;">struct</span> <span style="color: #808080;">_PIKACHU</span> 
    <span style="color: #ff00ff;">{</span> 
    </strong><strong><span style="color: #0000ff;"> char</span> <span style="color: #808080;">helloMsg</span><span style="color: #ff00ff;">[</span><span style="color: #00ccff;">100</span><span style="color: #ff00ff;">]</span>; <span style="color: #339966;">// setar para "pika, pika pikachuuuuuuu..."</span> 
    <span style="color: #0000ff;"> int </span><span style="color: #808080;">pokemonID</span><span style="color: #ff00ff;">;</span> <span style="color: #339966;">// setar para </span><span style="color: #ff00ff;">24</span> 
    <span style="color: #ff00ff;">}
    </span><span style="color: #808080;">PIKACHU</span><span style="color: #ff00ff;">,</span> <span style="color: #ff0000;"><span style="text-decoration: underline;">*CD</span></span>PIKACHU<span style="color: #ff00ff;">;</span></strong>

Não colou. Então vou tentar explicar do jeito certo.

Antigamente, as pessoas mandavam cartas umas para as outras. Carta, para você, caro leitor de quinze anos, era um e-mail implementado em hardware.

Para mandar um e-mail, usamos o nome da pessoa e o domínio em que seu e-mail é endereçado, ex: nome-da-pessoa@dominio.com.br. Para mandar uma carta usamos duas informações básicas: o nome da rua e o número da casa.

[![Endereço de uma carta](http://i.imgur.com/OhPq5ZX.png)](/images/endereco-da-carta.png)

Consequentemente enviamos dois comandos ao carteiro: meu amigo, vá para a rua tal. Chegando lá, encontre o número 1065.

Considere que estamos falando do mesmo bairro ou cidade, o que na minha analogia seria um computador e sua memória. Para enviar cartas para outros bairros em outras cidades (outros computadores em outras redes) teríamos que informar também outros dados, como nome da cidade e CEP.

[![Encontrando o caminho](http://i.imgur.com/qI5DrM5.png)](/images/getting-right-on-street.png)

Nesse exemplo também podemos usar o Juquinha do bairro para entregar a carta e economizarmos 10 centavos.

Agora, repare que interessante: em uma rua, cabem no máximo N casas. Se você tentar construir mais casas vai acabar invadindo o espaço de outra rua.

E, já que estamos falando do endereço do destinatário, já podemos relevar que esse endereço constitui um ponteiro em nossa analogia. Se você está usando dois dados para informar o endereço, então estamos falando de um ponteiro longo, long pointer, ou LP!

[![Relação Segmento x Offset com Rua x Número](http://i.imgur.com/C7Rfuqi.png)](/images/relacao-endereco-carta-segmento-offset.png)

#### Long Pointers

Na terminologia Intel para as plataformas 16 bits, a memória do computador era acessível através de segmentos (ruas) e offsets (números), que eram pedaços da memória onde cabiam no máximo N bytes. Para conseguir mais bytes é necessário alocar memória em outro segmento (outra rua).

Os ponteiros que conseguiam fazer isso eram chamados de long pointers, pois podiam alcançar uma memória mais "longa". Os ponteiros que apenas endereçavam o offset (número) eram chamados, em detrimento, short pointers, pois podiam apenas apontar para a memória do seu segmento (rua).

Ora, se seu destinatário está na mesma rua que você, tudo que você tem a dizer ao Juquinha é: "Juquinha, seu moleque, entrega essa carta no número 1065, e vai rápido!". Nesse caso você está usando um short pointer.

Porém, no exemplo que demos, o destinatário está em outra rua. Se o Juquinha entregar a carta no número 1065, mas na rua errada, estará errando o destinatário. Por isso é que você deve usar um long pointer e falar para o Juquinha do segmento!

[![Se perdendo nas ruas](http://i.imgur.com/2BO8tJv.png)](/images/getting-lost-on-streets.png)

"Juquinha, seu moleque safado, entrega essa carta no Segmento 0xAC89, Offset 0x496E. E vê se anda logo!"

Essa frase era muito usada nos anos 80, com seus 16 bits e tudo mais.

#### Voltando ao Windows

Com toda essa analogia, fica fácil perceber que o Windows não cabe em uma rua só. Seus aplicativos precisam de muitas ruas para rodar. Isso exige que todos seus ponteiros sejam long, pois do contrário o Juquinha estará entregando as cartas sempre nos endereços errados. Dessa forma, foi estipulado o typedef arcaico padrão para todos os tipos da API que usasse LP (Long Pointer) como prefixo:

    
    typedef unsigned long WORD, *LPDWORD;
    typedef const char* LPCSTR;
    typedef <coloque-seu-tipo-aqui> APELIDO, *LPAPELIDO;

E é por isso que, historicamente, todos os ponteiros para os apelidos da API Win32 possuem sua contraparte LP.

Com a era 32 bits (e mais atualmente 64 bits) os endereços passaram a ser flat, ou seja, apontam para qualquer lugar na memória. Se eu quisesse continuar minha analogia falaria que é o equivalente a uma coordenada GPS, também muito na moda, e que pode apontar para qualquer lugar do planeta. Eu, por exemplo, já trabalhei <del>trabalho</del> perto das coordenadas [-23.563596,-46.653885](http://maps.google.com.br/maps?f=q&source=s_q&hl=pt-BR&geocode=&q=av.+paulista,+sao+paulo&ie=UTF8&hq=&hnear=Av.+Paulista+-+S%C3%A3o+Paulo&z=15), o que eu costumo dizer que fica bem próximo do Paraíso =).

#### Largando velhos hábitos

De uns anos pra cá, existem novos typedefs nos headers que permitem o uso dos apelidos Win32 apenas com um P inicial.

    
    typedef unsigned long WORD, *LPDWORD, *PDWORD;
    typedef const char *LPCSTR, *PCSTR;
    typedef <coloque-seu-tipo-aqui> APELIDO, *LPAPELIDO, *PAPELIDO;

A escolha é livre. Assim como com o typedef arcaico.
