---
date: "2008-10-21"
title: A alça dentro do fio gerou um bloqueio da morte
categories: [ "code" ]
---
[![Mulher confusa após arrancar a maçaneta de uma porta.](/images/9477_confused_woman_holding_a_door_knob_after_it_disconnects_from_a_door.png)](/images/9477_confused_woman_holding_a_door_knob_after_it_disconnects_from_a_door.png)Estava folheando um [livro fenomenal](http://www.amazon.com/exec/obidos/ASIN/155615481X/shelfari-20) que meu amigo havia pedido emprestado para ler quando me deparei com algumas traduções (o livro estava em português) no mínimo curiosas.

Se trata do primeiro Windows Internals publicado após o lançamento da primeira versão do Windows NT, uma plataforma escrita (quase) inteiramente do zero para suplantar as versões 9x, que herdaram do DOS algumas partes indesejáveis em sistemas operacionais modernos.

Sabe-se lá por que, essa edição foi traduzida. É interessante notar que naquela época foi dado um tratamento especial a alguns termos e conceitos já comuns no dia-a-dia do programador americano, apesar de quase nenhum desses termos ter se mantido em sua versão original. Os exemplos mais gritantes são as _threads _(fios ou linhas) , os _dead locks _(bloqueios da morte) e _handles _(alças).

Apesar de não ter nada contra traduzir termos do inglês para português (e vice-versa), as coisas que mais me incomodam em tradução de livros técnicos é o fato dos tradutores:

	
  * Não se darem o trabalho de colocar ambos os termos: o original em língua estrangeira e a adaptação em português.

	
    * Ex.: "os **ponteiros** em C (**_pointers_**) são um recurso rico e necessário para a escrita de programas de baixo/médio nível".

	
  * Não manterem uma mesma tradução durante todo o livro, esbanjando um festival de sinônimos que complicam bastante a compreensão semântica do conteúdo.

	
    * Ex.:
(em um capítulo) "... é muito importante inicializar seus **ponteiros** antes de usá-los".
(em outro capítulo) "... sabe-se que a pior desgraça para um programador C são os famigerados **apontadores** selvagens".

	
  * Traduzirem o código-fonte, quase sempre mal e porcamente. Um exemplo notável é o [famoso livro de algoritmos em C da O'Reilly](http://compare.buscape.com.br/categoria?id=3482&lkout=1&kw=Dominando+Algoritmos+em+C+O%27Reilly&site_origem=1293522), que mesmo na nova edição com uma errata de 49 itens foi possível detectar mais erros. O exemplo abaixo consta no item 46 da edição de 2000 (Editora Ciência Moderna):

	
    * 

    
          if (opos > 0) {
    
             if ((temp = (unsigned char *)realloc(orig, opos + 1)) == NULL) {
    
                bitree_destroy(tree);
                free(tree);
                free(<font color="#ff0000">original</font>);
                return -1;
    
             }
    
             <font color="#ff0000">orig </font>= temp;
    
             }
    
    // Se vai errar o código, <strong>não traduza</strong>!
    // É importante notar que no original <strong>não consta</strong> esse erro.

	
  * Não entenderem que um termo usado pelo autor na verdade é um vocábulo com significado especial para as pessoas que trabalham no ramo. Isso é pior do que não colocar a versão em inglês, pois dá a impressão que não existe significado a ser explicado.

	
    * Ex.:
(antes do capítulo sobre _threads_): "... quando um **fio **espera o outro e vice-versa, acontece o terrível **bug **da **trava da morte**".

<blockquote>_Esses exemplos, salvo o exemplo do livro de algoritmos, foram criados para ilustrar os tipos de erros mais comuns em traduções de livros técnicos, e não estão relacionados com qualquer livro em específico._</blockquote>

[![Homem tentando enfiar um fio na agulha.](http://i.imgur.com/56bgzq0.png)](/images/9349_man_trying_to_thread_a_sewing_needle.png)Então o que era inicialmente para ajudar as pessoas que estão iniciando alguns conceitos acaba por prejudicar ainda mais o aprendizado, gerando aquele tipo de confusão que só com ajuda extra (internet, professor, colega) pode ser resolvida.

Assim como no vocabulário comum corrente, em que existem palavras dificilmente adaptáveis ou traduzíveis em um termo comum, como _shopping_ e _show_,  no meio técnico desabrocham as mais variadas expressões estrangeirísticas. Algumas são muito difíceis de encontrar seu primo lusófono, como _link_ e _login_. Outros, no entanto, exageram um pouco as coisas, a ponto de conjugarmos um verbo em inglês usando nosso sistema gramatical ("se você *stopar* o *debugador* vai *crashear* todo o sistema, porque esse _software_ tá *bugado*!").

O fato é que não há escapatória para quem trabalha nessa área, e no fundo isso é uma coisa boa, pois é da leitura técnica em inglês que podemos estender o nosso conhecimento além das barreiras do .br e encontrar conteúdo extremamente interessante (e inédito em nossa língua) para aprender. Se não estivéssemos abarrotados de estrangeirismos talvez fosse um pouco mais difícil fazer o _switch_ entre essas duas linguagens.

[](http://i.imgur.com/kCIXlt1.png)

[![Homem de negócios juntando os dois elos de uma corrente gigante.](http://i.imgur.com/kCIXlt1.png)](/images/3673_businessman_linking_a_chain_together.png)
