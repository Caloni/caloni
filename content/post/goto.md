---
date: 2019-05-28T18:21:20-03:00
title: "C Resolve Tudo: goto"
categories: [ "code" ]
desc: "Usos úteis do goto na linguagem C"
---
Para quem decide usar a linguagem C para resolver tudo, a gota da água é o `goto`. Ele é flexível, cabe em (quase) qualquer ponto do código e tem 1001 utilidades. O goto é o bombril da engenharia de software.

O uso mais simples dessa importante construção da linguagem é pular de um ponto para outro do código em que esses pontos não estão diretamente relacionados, como geralmente ocorre, como sair de um laço, não entrar em um `if` ou selecionar um `case` do `switch` (lembrando que no caso do `case` do `switch` ele é no fundo um `goto` disfarçado).

```c
#include <stdio.h>

main(int argc, char* argv[])
{
    if( argc != 5 ) /* espero quatro+um (o programa) argumentos */
        goto usage;
    /*
    do something 
    do something else
    more to do
    and more
    and more
    and more
    and more
    too much lines
    ...
    finished
    */
    return 0;

    usage:
    printf("How to use: %s one two three four\n", argv[0]);
    return 1;
}
```

```
c:\Projects\goto>cl goto.c
Microsoft (R) C/C++ Optimizing Compiler Version 19.22.27706.1 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.

goto.c
Microsoft (R) Incremental Linker Version 14.22.27706.1
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:goto.exe
goto.obj

c:\Projects\goto>goto.exe
How to use: goto.exe one two three four

c:\Projects\goto>
```

Claro que esse uso é trivial demais para valer a pena uma troca de fluxo tão desestruturada. Há formas mais úteis de desviar o fluxo padrão. No exemplo acima bastaria colocar todo o código que se segue dentro do grupo pertencente ao `if` e o `goto` seria desnecessário.

Mas, por exemplo, imagine que precisamos nos desfazer de recursos na ordem inversa ao qual vão sendo adquiridos. Pode-se aninhar indefinidamente `ifs` ou usar um bloco de código de _unwinding_ que vai fechando os recursos na ordem inversa e inicia sua chamada dependendo de onde ocorreu o erro. Código é melhor para ilustrar:

```c
#include <stdio.h>

main(int argc, char* argv[])
{
    FILE *f1, *f2, *f3, *f4, *f5;

    if( ! (f1 = fopen("f1.txt", "r")) ) goto end;
    if( ! (f2 = fopen("f2.txt", "r")) ) goto end_f1;
    if( ! (f3 = fopen("f3.txt", "r")) ) goto end_f2;
    if( ! (f4 = fopen("f4.txt", "r")) ) goto end_f3;
    if( ! (f5 = fopen("f5.txt", "r")) ) goto end_f4;

    /*
    code
    ...
    code
    */

    printf("closing f5\n");
    fclose(f5);
    end_f4: printf("closing f4\n"); fclose(f4);
    end_f3: printf("closing f3\n"); fclose(f3);
    end_f2: printf("closing f2\n"); fclose(f2);
    end_f1: printf("closing f1\n"); fclose(f1);
    end: ;
    /* obs: esse ponto-e-virgula final se deve ao fato que os labels do goto 
    rotulam um comando; logo, se ha um label, deve haver um comando logo
    depois (mesmo que seja nulo, no caso de ponto-e-virgula). */
}
```

```
c:\Projects\goto>cl goto2.c
Microsoft (R) C/C++ Optimizing Compiler Version 19.22.27706.1 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.

goto2.c
Microsoft (R) Incremental Linker Version 14.22.27706.1
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:goto2.exe
goto2.obj

c:\Projects\goto>goto2

c:\Projects\goto>touch f1.txt

c:\Projects\goto>goto2
closing f1

c:\Projects\goto>touch f2.txt

c:\Projects\goto>goto2
closing f2
closing f1

c:\Projects\goto>touch f3.txt f4.txt f5.txt

c:\Projects\goto>goto2
closing f5
closing f4
closing f3
closing f2
closing f1

c:\Projects\goto>
```

Esse estilo de liberação de recursos é muito usado em códigos de kernel e software mais básico, pois simplifica a visualização e aumenta a flexibilidade. Compare com a versão estruturada:

```c
#include <stdio.h>

main(int argc, char* argv[])
{
    FILE *f1, *f2, *f3, *f4, *f5;

    if( f1 = fopen("f1.txt", "r") )
    {
        if( f2 = fopen("f2.txt", "r") )
        {
            if( f3 = fopen("f3.txt", "r") )
            {
                if( f4 = fopen("f4.txt", "r") )
                {
                    if( f5 = fopen("f5.txt", "r") )
                    {
                        /*
                           code
                           ...
                           code
                         */
                        printf("closing f5\n");
                        fclose(f5);
                    }
                    printf("closing f4\n"); fclose(f4);
                }
                printf("closing f3\n"); fclose(f3);
            }
            printf("closing f2\n"); fclose(f2);
        }
        printf("closing f1\n"); fclose(f1);
    }
}
```

```
c:\Projects\goto>cl nogoto2.c
Microsoft (R) C/C++ Optimizing Compiler Version 19.22.27706.1 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.

nogoto2.c
Microsoft (R) Incremental Linker Version 14.22.27706.1
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:nogoto2.exe
nogoto2.obj

c:\Projects\goto>nogoto2
closing f5
closing f4
closing f3
closing f2
closing f1

c:\Projects\goto>rm f5.txt

c:\Projects\goto>nogoto2
closing f4
closing f3
closing f2
closing f1

c:\Projects\goto>rm f4.txt

c:\Projects\goto>nogoto2
closing f3
closing f2
closing f1

c:\Projects\goto>rm f3.txt f2.txt f1.txt

c:\Projects\goto>nogoto2

c:\Projects\goto>
```

Aliás, esse uso do `goto` é a maneira de aplicar [RAII](https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization) em C (Resource acquisition is initialization). Implícito em linguagens como C++ e seus destrutores de objetos, em C é você que precisa fazer a faxina. E se a bagunça foi feita da direita pra esquerda a faxina deve ser feita da esquerda pra direita.

Esse uso super-aninhado do código me lembra do exemplo clássico de sair de muitos loops aninhados. Apenas por didática, vamos citá-lo:

```c
#include <stdio.h>

main(int argc, char* argv[])
{
    int i, j, k;

    for( i = 0; i < 100; ++i )
    {
        for( j = 0; j < 100; ++j )
        {
            for( k = 0; k < 100; ++k )
            {
                if( k == 10 )
                    /* break... ops. no. to the outer world */
                    goto outer_world;
            }
        }
    }

    outer_world:
    ;
}
```

Comentei no começo do texto que os `cases` do `switch` são labels de goto disfarçados. E são mesmo. Um dos algoritmos mais famosos de transformação de loop chamado [Duff's device](https://en.wikipedia.org/wiki/Duff%27s_device) junta um `do-while` com `switch` e realiza uma cópia de buffer com um número de bytes variável:

```c
send(to, from, count)
register short *to, *from;
register count;
{
    register n = (count + 7) / 8;
    switch (count % 8) {
    case 0: do { *to = *from++;
    case 7:      *to = *from++;
    case 6:      *to = *from++;
    case 5:      *to = *from++;
    case 4:      *to = *from++;
    case 3:      *to = *from++;
    case 2:      *to = *from++;
    case 1:      *to = *from++;
            } while (--n > 0);
    }
}
```

O que está acontecendo no código acima: é possível inserir qualquer tipo de mudança de fluxo dentro do `switch`. Duff aproveitou essa particularidade da linguagem para produzir jumps que poderiam ser feitos em assembly. Dependendo do resto da divisão por oito o salto é realizado para um `case` diferente, que executará parte do laço até o `while` comparador final. A vantagem desse tipo de abordagem é que evita-se sair da programação estruturada, e muito menos precisa-se apelar para o assembly.

Esse código também seria possível de ser feito com o `goto` clássico, mas note que nesse caso ele fica mais verboso, pois é necessário fazer um `if` diferente para cada condição.

```c
#include <stdio.h>

send(to, from, count)
register short *to, *from;
register count;
{
    register n = (count + 7) / 8;
    if (count % 8 == 0 ) goto case_0;
    if (count % 8 == 7 ) goto case_7;
    if (count % 8 == 6 ) goto case_6;
    if (count % 8 == 5 ) goto case_5;
    if (count % 8 == 4 ) goto case_4;
    if (count % 8 == 3 ) goto case_3;
    if (count % 8 == 2 ) goto case_2;
    if (count % 8 == 1 ) goto case_1;
    case_0: do { *to++ = *from++; /* estou incrementando `to` tambem    */
    case_7:      *to++ = *from++; /* porque esta nao eh uma memoria     */
    case_6:      *to++ = *from++; /* de hardware que se auto incrementa */
    case_5:      *to++ = *from++;
    case_4:      *to++ = *from++;
    case_3:      *to++ = *from++;
    case_2:      *to++ = *from++;
    case_1:      *to++ = *from++;
            } while (--n > 0);
}

main()
{
    short to[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    short from[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int i;
    send(to, from, 10);
    for( i = 0; i < 10; ++i )
        printf("%d ", to[i]);
    printf("\n");
}
```

Caso você tenha estranhada a definição inicial da função, ela é como se definia os argumentos em linguagem C antes do padrão ANSI, com os nomes e logo em seguida a declaração das variáveis como se fossem locais (porque de fato elas são, embora sua inicialização seja feita antes da chamada). Como este código data dos anos 80 e como o padrão só foi finalizado em 89, percebe-se que ainda se usava o formato antigo no código.

Passemos para o próximo uso: código infinito. Esse é um uso clássico, e diferente do uso degenerado de laços em que a condição é sempre verdadeira (`while(true)`, `for(;;)`) usando o `goto` fica bem-documentado que o objetivo é ficar eternamente nesse loop. Um laço infinito que eu me lembro é quando dá tela azul no Windows. O código-fonte do kernel era algo mais ou menos assim:

```c
/* ... */
gerarDump();
mudarParaVga();

while( true )
    ; /* that's all, folks */
/* ... */
```

Os programadores usaram o apelo clássico do `while`. Sem motivo, pois `goto` é usado direto como RAII (já explicado acima). A maneira procedural de fazer seria assim:

```c
main()
{
    infinite:
    goto infinite;
}
```


```
c:\Projects\goto>cl goto4.c
Microsoft (R) C/C++ Optimizing Compiler Version 19.22.27706.1 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.

goto4.c
Microsoft (R) Incremental Linker Version 14.22.27706.1
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:goto4.exe
goto4.obj

c:\Projects\goto>goto4
...
...
tudo esta tao escuro...
```

Isso lembra outra utilidade do `goto` que você pode anotar no seu caderninho: ele pode voltar o fluxo, de baixo para cima.

Esse último exemplo é um dos programas C mais lindos do universo. Sua única instrução é o comando rotulado por `infinite` e referencia ele mesmo. É quase o salto incondicional do assembly, materializado na linguagem mais elegante jamais criada em nossa realidade.

PS: Código no [GitHub](https://github.com/Caloni/goto).
