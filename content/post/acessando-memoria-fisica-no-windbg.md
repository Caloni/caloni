---
date: "2008-05-01"
title: Acessando memória física no WinDbg
categories: [ "code" ]
---
![dimm.gif](http://i.imgur.com/OraOKS3.gif)

Como muitos devem saber, acessar memória virtual no WinDbg é coisa de criança, assim como em todo depurador decente. Se estamos falando de _kernel mode_ então, nem se fala! A memória virtual é parte integrante do sistema operacional. Podemos saber mais sobre isso lendo o artigo do Strauss sobre [gerenciamento de memória no Windows](http://www.1bit.com.br/content.1bit/weblog/borcon_talk).

Porém, existem situações, como a que passei essa semana, onde é preciso saber e alterar o conteúdo da memória de verdade, mesmo. Quando eu falo "de verdade mesmo" estou falando em acessar a memória através do seu **endereçamento real**, que conta do zero até o final da sua memória RAM, sem divisão de processos e sem proteções de acesso.

Para isso é que serve um depurador de verdade, mesmo.

#### Um pouco dos velhos tempos

No modo real, onde vivem sistemas como o MS-DOS e programas como o Turbo C, a memória é acessada através do par de coordenadas conhecido como **segmento** e _**offset**_. Entre outros motivos, isso acontece porque em um determinado momento da história o 8086 possuía 16 bits em seus registradores, mas conseguia endereçar até 640 Kbytes, o que resulta em 640 * 1024 = 655360 bytes, um número dez vezes maior do que 65536, ou 2 ^ 16, o maior número representado por 16 bits.

Dessa forma, foi necessário o uso de mais 4 bits para fazer a coisa funcionar, pois como podemos notar logo abaixo, a representação do último byte de 640 KB exige isso:

    
       10   16   16   16   16   (decimal)
       A    0    0    0    0    (hexadecimal)
       1010 0000 0000 0000 0000 (binário)

Para conseguir esses 4 bits adicionais foram usados dois registradores em conjunto, o segmento e o offset. Funciona assim: o segmento é multiplicado por 16 (ou deslocado 4 bits à esquerda) e logo depois é somado com o offset, resultando no endereçamento desejado:

    
       segmento:      0x   9022
       offset:        0x   1514

    
                      0x   9022
                      0x    1514 (+)
       endereço real: 0x   91734

Ou seja, para acessar o byte de número 595764, ou 0x91734, podemos usar o segmento 0x9022 com o offset 0x1514. A soma desses dois com o segmento deslocado irá resultado no endereço flag, ou seja, aquele que obtemos se contarmos a memória do zero até o final da RAM.

<blockquote>_Na época, a RAM não costumava ser de valores como 2GB ou até 4GB, mas em KB mesmo. Isso explica a limitação do 8086 em endereçar até 640 KB._</blockquote>

Se nós repararmos bem, veremos que esse método implica em conseguirmos acessar o mesmo byte com um conjunto de segmentos e offsets diferentes, já que a soma pode ser resultado de operandos diversos. Esse é o chamado efeito de _overlapping_ da memória segmentada, onde os programadores em assembly daquela época tinham que tomar alguns cuidados básicos para não atravessar a memória dos outros. No nosso exemplo acima, por exemplo, seria bem mais fácil chamar nosso bytezinho de segmento 0x9000, offset 0x1734.

    
       0x  9000
       0x   1734 (+)
       0x  91734

#### Tudo bem. Mas e o WinDbg?

É verdade! Então, o WinDbg possui alguns comandos extendidos e formas de representar essa memória real, atualmente limitada não mais em 640 KB, mas até onde seus pentes de RAM agüentarem. Os mais comuns são os que imitam os nossos conhecidos dumps de memória: db, dc, dd... Temos daí as extensões !db, !dc, !dd... (note a exclamação do início).

    
    windbg -kl $$ kernel debugging local

    
    lkd> !db 91734
    #   91734 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00 ................
    #   91744 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00 ................
    #   91754 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00 ................
    #   91764 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00 ................
    #   91774 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00 ................
    #   91784 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00 ................
    #   91794 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00 ................
    $$ o sinal de # no início denota memória real

Simples, assim.

<blockquote>_Infelizmente, o WinDbg não nos permite ler certas regiões da memória por conta do cacheamento feito pelo processador. Para permitir a leitura em todas as condições, existem  três flags que podem ser utilizados:_

> 
	
>   * **c** - lê da memória cacheada
> 
	
>   * **uc** - lê da memória não-cacheada
> 
	
>   * **wc** - lê da memória de escrita combinada
> 

_Nesse caso é possível, embora fique por sua conta e risco, ler qualquer memória não-cacheada usando-se a flag **uc**._</blockquote>

É possível fazer mais brincadeiras usando os comandos comuns do WinDbg e uma notação diferente da memória. No entanto, é preciso tomar alguns cuidados quando mexer com isso. É recomendado o uso de uma máquina-vítima para esses testes, e não depuração local como estou fazendo.

    
       notação  descrição                     exemplo

    
       %        endereços de 32 ou 64 bits    %6400000   (primeiro byte de 100 MB)
       &        endereço em modo real 8086    &9000:1734 (segmento 9000, offset 1734)
       #        endereço em modo real 8086    #4C        (endereço da int 0x13)

É isso aí. Não espero que você use muitas vezes essa forma de acessar memória. Só que eu usei e... nunca se sabe =)
