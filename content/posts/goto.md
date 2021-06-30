---
categories:
- code
date: '2019-05-28'
title: 'C Resolve Tudo: goto'
---

Para quem decide usar a linguagem C para resolver tudo, a gota da água é o goto. Ele é flexível, cabe em (quase) qualquer ponto do código e tem 1001 utilidades. O goto é o bombril da engenharia de software.

O uso mais simples dessa importante construção da linguagem é pular de um ponto para outro do código em que esses pontos não estão diretamente relacionados, como geralmente ocorre, como sair de um laço, não entrar em um if ou selecionar um case do switch (lembrando que no caso do case do switch ele é no fundo um goto disfarçado).

    if( argc != 5 )
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
    printf("How to use: ...");
    return 1;

Claro que esse uso é trivial demais para valer a pena uma troca de fluxo tão desestruturada. Há formas mais úteis de desviar o fluxo padrão. No exemplo acima bastaria colocar todo o código que se segue dentro do grupo pertencente ao if e o goto seria desnecessário.

Mas, por exemplo, imagine que precisamos nos desfazer de recursos na ordem inversa ao qual vão sendo adquiridos. Pode-se aninhar indefinidamente ifs ou usar um bloco de código de unwinding que vai fechando os recursos na ordem inversa e inicia sua chamada dependendo de onde ocorreu o erro. Código é melhor para ilustrar:

    FILE *f1, *f2, *f3, *f4, *f5;
    
    if( ! (f1 = fopen()) )
      goto end;
    if( ! (f2 = fopen()) )
      goto end_f1;
    if( ! (f3 = fopen()) )
      goto end_f2;
    if( ! (f4 = fopen()) )
      goto end_f3;
    if( ! (f5 = fopen()) )
      goto end_f4;
    
    /*
    code
    ...
    code
    */
    
    printf("closing f5\n");
    fclose(f5);
    end_f4: 
      fclose(f4);
    end_f3: 
      fclose(f3);
    end_f2: 
      fclose(f2);
    end_f1: 
      fclose(f1);
    end: ;

Esse ponto-e-virgula final se deve ao fato que os labels do goto rotulam um comando; logo, se ha um label, deve haver um comando logo depois (mesmo que seja nulo, no caso de ponto-e-virgula). Esse estilo de liberação de recursos é muito usado em códigos de kernel e software mais básico, pois simplifica a visualização e aumenta a flexibilidade. Compare com a versão estruturada:

    if( f1 = fopen() )
    {
      if( f2 = fopen() )
      {
        if( f3 = fopen() )
        {
          if( f4 = fopen() )
          {
            if( f5 = fopen() )
            {
              /*
                 code
                 ...
                 code
               */
              fclose(f5);
            }
            fclose(f4);
          }
          fclose(f3);
        }
        fclose(f2);
      }
      fclose(f1);
    }

Aliás, esse uso do goto é a maneira de aplicar RAII em C (Resource acquisition is initialization). Implícito em linguagens como C++ e seus destrutores de objetos, em C é você que precisa fazer a faxina. E se a bagunça foi feita da direita pra esquerda a faxina deve ser feita da esquerda pra direita.

Esse uso super-aninhado do código me lembra do exemplo clássico de sair de muitos loops aninhados. Apenas por didática, vamos citá-lo:

    for( ; ; )
    {
      for( ; ; )
      {
        for( ; ; )
        {
          if( condition )
            goto outer_world;
        }
      }
    }
    
    outer_world: ;

Comentei no começo do texto que os cases do switch são labels de goto disfarçados. E são mesmo. Um dos algoritmos mais famosos de transformação de loop chamado Duff's device junta um do-while com switch e realiza uma cópia de buffer com um número de bytes variável:

    send(to, from, count)
    register short *to, *from;
    register count;
    {
      register n = (count + 7) / 8;
      switch (count % 8) {
      case 0: do { *to = *from++;
      case 7: *to = *from++;
      case 6: *to = *from++;
      case 5: *to = *from++;
      case 4: *to = *from++;
      case 3: *to = *from++;
      case 2: *to = *from++;
      case 1: *to = *from++;
        } while (--n > 0);
      }
    }

O que está acontecendo no código acima: é possível inserir qualquer tipo de mudança de fluxo dentro do switch. Duff aproveitou essa particularidade da linguagem para produzir jumps que poderiam ser feitos em assembly. Dependendo do resto da divisão por oito o salto é realizado para um case diferente, que executará parte do laço até o while comparador final. A vantagem desse tipo de abordagem é que evita-se sair da programação estruturada, e muito menos precisa-se apelar para o assembly.

Esse código também seria possível de ser feito com o goto clássico, mas note que nesse caso ele fica mais verboso, pois é necessário fazer um if diferente para cada condição.

    register n = (count + 7) / 8;
    if (count % 8 == 0 ) 
      goto case_0;
    if (count % 8 == 7 ) 
      goto case_7;
    if (count % 8 == 6 ) 
      goto case_6;
    if (count % 8 == 5 ) 
      goto case_5;
    if (count % 8 == 4 ) 
      goto case_4;
    if (count % 8 == 3 ) 
      goto case_3;
    if (count % 8 == 2 ) 
      goto case_2;
    if (count % 8 == 1 ) 
      goto case_1;
    case_0: do { *to++ = *from++;
    case_7: *to++ = *from++;
    case_6: *to++ = *from++;
    case_5: *to++ = *from++;
    case_4: *to++ = *from++;
    case_3: *to++ = *from++;
    case_2: *to++ = *from++;
    case_1: *to++ = *from++;
    } while (--n > 0);

Caso você tenha estranhada a definição inicial da função, ela é como se definia os argumentos em linguagem C antes do padrão ANSI, com os nomes e logo em seguida a declaração das variáveis como se fossem locais (porque de fato elas são, embora sua inicialização seja feita antes da chamada). Como este código data dos anos 80 e como o padrão só foi finalizado em 89, percebe-se que ainda se usava o formato antigo no código.

Passemos para o próximo uso: código infinito. Esse é um uso clássico, e diferente do uso degenerado de laços em que a condição é sempre verdadeira (while(true), for(;;)) usando o goto fica bem-documentado que o objetivo é ficar eternamente nesse loop. Um laço infinito que eu me lembro é quando dá tela azul no Windows. O código-fonte do kernel era algo mais ou menos assim:

    gerarDump();
    mudarParaVga();
    
    while( true )
      ; /* that's all, folks */

Os programadores usaram o apelo clássico do while. Sem motivo, pois goto é usado direto como RAII (já explicado acima). A maneira procedural de fazer seria assim:

    infinite:
    goto infinite;

Isso lembra outra utilidade do goto que você pode anotar no seu caderninho: ele pode voltar o fluxo, de baixo para cima. Esse último exemplo é um dos programas C mais lindos do universo. Sua única instrução é o comando rotulado por infinite e referencia ele mesmo. É quase o salto incondicional do assembly, materializado na linguagem mais elegante jamais criada em nossa realidade.