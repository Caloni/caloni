---
date: "2008-10-21"
tags: [ "code", "essays",  ]
title: "A alça dentro do fio gerou um bloqueio da morte"
---
Estava folheando um livro fenomenal que meu amigo havia pedido emprestado para ler quando me deparei com algumas traduções (o livro estava em português) no mínimo curiosas.

Se trata do primeiro Windows Internals publicado após o lançamento da primeira versão do Windows NT, uma plataforma escrita (quase) inteiramente do zero para suplantar as versões 9x, que herdaram do DOS algumas partes indesejáveis em sistemas operacionais modernos.

Sabe-se lá por que, essa edição foi traduzida. É interessante notar que naquela época foi dado um tratamento especial a alguns termos e conceitos já comuns no dia-a-dia do programador americano, apesar de quase nenhum desses termos ter se mantido em sua versão original. Os exemplos mais gritantes são as threads (fios ou linhas), os dead locks (bloqueios da morte) e handles (alças).

Apesar de não ter nada contra traduzir termos do inglês para português (e vice-versa), algumas coisas incomodam em tradução de livros técnicos.

Com essa informação, que pode ser usada apenas nos primeiros usos da palavra, agradaria gregos e troianos. Abaixo um exemplo.

> "os ponteiros em C (pointers) são um recurso rico e necessário para a escrita de programas de baixo/médio nível".

Por exemplo, ler um dado capítulo:

> "... é muito importante inicializar seus ponteiros antes de usá-los."

E, depois de se acostumar com o termo, ler em outro capítulo:

> "... sabe-se que a pior desgraça para um programador C são os famigerados apontadores selvagens."

Um exemplo notável é o famoso livro de algoritmos em C da O'Reilly, que mesmo na nova edição com uma errata de 49 itens foi possível detectar mais erros. O exemplo abaixo consta no item 46 da edição de 2000 (Editora Ciência Moderna):

    if (opos > 0)
    {
        if ( (temp = (unsigned char *)
            realloc(orig, opos + 1)) == NULL)
        {
            bitree_destroy(tree);
            free(tree);
            free(original); /* original??? */
            return -1;
        }
    
        orig = temp;
    }

Obs.: importante notar que no original não consta esse erro da variável original. Entendeu? Entendeu?

Isso é pior do que não colocar a versão em inglês, pois dá a impressão que não existe significado a ser explicado. Por exemplo, ver antes do capítulo sobre threads:

> "... quando um fio espera o outro e vice-versa, acontece o terrível bug da trava da morte."

Para quem não descobriu o que foi escrito no original, se trata de um deadlock, cujo termo inclusive é usado no seu original na Wikipédia em português.

Esses exemplos, salvo o exemplo do livro de algoritmos, foram criados para ilustrar os tipos de erros mais comuns em traduções de livros técnicos, e não estão relacionados com qualquer livro em específico. Então o que era inicialmente para ajudar as pessoas que estão iniciando alguns conceitos acaba por prejudicar ainda mais o aprendizado, gerando aquele tipo de confusão que só com ajuda extra (internet, professor, colega) pode ser resolvida.

Assim como no vocabulário comum corrente, em que existem palavras dificilmente adaptáveis ou traduzíveis em um termo comum, como shopping e show, no meio técnico desabrocham as mais variadas expressões estrangeirísticas. Algumas são muito difíceis de encontrar seu primo lusófono, como link e login. Outros, no entanto, exageram um pouco as coisas, a ponto de conjugarmos um verbo em inglês usando nosso sistema gramatical (se você "stopar" o "debugador" vai "crashear" todo o sistema, porque esse software tá "bugado"!).

O fato é que não há escapatória para quem trabalha nessa área, e no fundo isso é uma coisa boa, pois é da leitura técnica em inglês que podemos estender o nosso conhecimento além das barreiras do ponto com ponto br e encontrar conteúdo extremamente interessante (e inédito em nossa língua) para aprender. Se não estivéssemos abarrotados de estrangeirismos talvez fosse um pouco mais difícil fazer o switch entre essas duas linguagens. Entendeu? Switch? Entendeu?
