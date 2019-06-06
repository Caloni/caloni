---
date: "2008-01-16"
title: Encontrando as respostas do Flash Pops
categories: [ "code" ]
---
[![Flash Pops](http://i.imgur.com/nwYAF4Q.png)](/images/flash-pops.png)Existe uma [série de jogos](http://www2.uol.com.br/flashpops/jogos/) no sítio da UOL onde você deve acertar o nome de filmes, programas de televisão, entre outros, que vão da [década de 40](http://www.imdb.com/title/tt0034583/) até a [atualidade](http://www.imdb.com/title/tt0109830/). É divertido e viciante fazer pesquisa na internet para encontrar os resultados, ainda mais quando já se é viciado em cinema. Ficamos jogando, eu e minha namorada, por semanas a fio. Quase chegamos a preencher tudo, e por um bom tempo ficamos travados para terminar. Então começamos a apelar para o [Google](http://www.google.com) e o [IMDB](http://www.imdb.com) até os limites do razoável. Nesse fim de semana, por exemplo, chegamos a assistir um filme de madrugada onde tocou rapidamente um trecho de uma das músicas que faltava no jogo sobre televisão. No dia seguinte procuramos a [trilha sonora do filme](http://www.imdb.com/title/tt0140688/soundtrack), ouvimos [faixa a faixa](http://www.amazon.com/exec/obidos/ASIN/B000007T6B/internetmoviedat/) e procuramos [o nome da música](http://www.google.com/search?q=) no Google, para finalmente encontrar [o resultado](http://www.imdb.com/title/tt0088559/).

Essa foi a última resposta "honesta". Depois resolvi apelar para o WinDbg =)

#### Procurando na memória

A primeira coisa que pensei a respeito desse jogo foi que ele não seria tão ingênuo a ponto de colocar as respostas em texto aberto, do contrário, qual seria a graça, certo? Errado! Bom, no final das contas, um passo-a-passo bem simples me levou a encontrar a lista de respostas.

A primeira coisa a fazer é carregar o jogo na memória do navegador. Em seguida, seguindo meu raciocínio inicial, digitei a primeira resposta do jogo.

[![Flash Pops (Filmes 1)](http://i.imgur.com/uuBC9fi.png)](/images/flash-pops-jogo.png)

A partir daí, podemos "atachar" o WinDbg no processo do navegador e rastrear a memória do processo.

    
    windbg -pn firefox.exe

[![GPF Now!](http://i.imgur.com/57ydjgF.gif)](/images/gpfnow.gif)

[](/images/win-pan.mp3)Então, como eu dizia, não faça isso em casa enquanto estiver digitando um artigo de seu blogue dentro do navegador. Ele vai travar!

    
    windbg %programfiles%\Mozilla Firefox\firefox.exe

OK. A primeira coisa é procurar pela string digitada, na esperança de achar a estrutura que escreve as respostas de acordo com a digitação. Isso pode ser feito facilmente graças ao WinDbg e ao [artigo de Volker von Einem](http://voneinem-windbg.blogspot.com/2007/06/scan-full-process-memory-for-pattern.html) que ensina como procurar strings por toda a memória de um processo (mais tarde iremos também usar o comando-bônus do comentário de Roberto Farah).

    
    0:017> s -a 0 0fffffff "caca fantasmas"
    0575f458  63 61 63 61 20 66 61 6e-74 61 73 6d 61 73 00 63  caca fantasmas.c
    057fb950  63 61 63 61 20 66 61 6e-74 61 73 6d 61 73 00 00  caca fantasmas..

Interessante. Dois resultados. Olhando o primeiro deles, vemos que encontramos o que queríamos sem nem  mesmo tentar quebrar alguma chave de criptografia.

    
    0:017> db 0575f458
    0575f458  63 61 63 61 20 66 61 6e-74 61 73 6d 61 73 00 63  caca fantasmas.c
    0575f468  61 63 61 2d 66 61 6e 74-61 73 6d 61 73 00 63 61  aca-fantasmas.ca
    0575f478  c3 a7 61 20 66 61 6e 74-61 73 6d 61 73 00 63 61  ..a fantasmas.ca
    0575f488  c3 a7 61 2d 66 61 6e 74-61 73 6d 61 73 00 67 68  ..a-fantasmas.gh
    0575f498  6f 73 74 62 75 73 74 65-72 73 00 41 72 72 61 79  ostbusters.Array
    0575f4a8  00 6d 75 73 31 00 6a 61-6d 65 73 20 62 6f 6e 64  .mus1.james bond
    0575f4b8  00 30 30 37 00 6d 75 73-32 00 6d 69 73 73 69 6f  .007.mus2.missio
    0575f4c8  6e 20 69 6d 70 6f 73 73-69 62 6c 65 00 6d 69 73  n impossible.mis

O segundo, porém, não parece uma lista de respostas, mas sim a resposta que acabamos de digitar no navegador.

    
    0:017> db 057fb950
    057fb950  63 61 63 61 20 66 61 6e-74 61 73 6d 61 73 00 00  caca fantasmas..
    057fb960  5f 6c 65 76 65 6c 30 2f-6d 75 73 36 32 3a 6d 00  _level0/mus62:m.
    057fb970  00 00 00 00 24 44 82 05-20 40 82 05 32 3a 6d 00  ....$D.. @..2:m.
    057fb980  00 00 00 00 6c 49 82 05-68 45 82 05 00 00 00 00  ....lI..hE......
    057fb990  00 00 00 00 b4 4e 82 05-b0 4a 82 05 00 00 00 00  .....N...J......
    057fb9a0  00 00 00 00 24 74 85 05-20 70 85 05 00 00 00 00  ....$t.. p......
    057fb9b0  00 00 00 00 6c 79 85 05-68 75 85 05 00 00 00 00  ....ly..hu......
    057fb9c0  70 6f 72 63 65 6e 74 6f-00 63 65 72 74 61 73 00  porcento.certas.

Para se certificar, rodamos novamente o navegador, apagamos a resposta e refazemos a busca.

    
    0:017> g
    (864.dc0): Break instruction exception - code 80000003 (first chance)
    eax=7ffda000 ebx=00000001 ecx=00000002 edx=00000003 esi=00000004 edi=00000005
    eip=7c901230 esp=03c3ffcc ebp=03c3fff4 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=0038  gs=0000             efl=00000246
    ntdll!DbgBreakPoint:
    7c901230 cc              int     3
    0:017> s -a 0 0fffffff "caca fantasmas"
    0575f458  63 61 63 61 20 66 61 6e-74 61 73 6d 61 73 00 63  caca fantasmas.c

De fato, a lista de respostas é tudo que encontramos.

#### Usando o .foreach (e uma nova busca)

Assim como no [artigo sobre carregamento de DLLs arbitrárias](http://www.caloni.com.br/carregando-dlls-arbitrarias-pelo-windbg-parte-2),  vamos usar o muito útil comando **.foreach**, que caminha em uma lista de resultados de um comando para executar uma lista secundária de comandos. Apenas para relembrar, a sintaxe do foreach é a seguinte:

    
    .foreach [Options] ( <font color="#ff0000">Variable</font>  { <font color="#0000ff">InCommands</font> } ) { <font color="#008000">OutCommands</font> }

	
  * Variable. Um nome que usamos no OutCommands. Representa cada _token_ do resultado de InCommands.

	
  * InCommands. Um ou mais comandos que executamos para gerar uma saída na tela. Essa saída será usada em OutCommands, onde Variable é substituído por cada _token_ da saída.

	
  * OutCommands. Um ou mais comandos executados usando a saída na tela de InCommands.

#### O que é um _token_?

Para o .foreach, um _token_ é uma string separada por espaço(s). A saída dos comandos do WinDbg nem sempre vai gerar algo que podemos usar diretamente, como no caso da busca que fizemos inicialmente. Apenas para demonstração, vamos imprimir todos os _tokens_ da saída de nosso comando.

    
    .foreach ( answerList { s -a 0 0fffffff "caca fantasmas" } ) { .echo answerList }

    
    <font color="#ff6600">0575f458</font>
    <font color="#808000">63</font>
    <font color="#ff6600">61</font>
    <font color="#808000">63</font>
    <font color="#ff6600">61</font>
    <font color="#808000">20</font>
    <font color="#ff6600">66</font>
    <font color="#808000">61</font>
    <font color="#ff6600">6e-74</font>
    <font color="#808000">61</font>
    <font color="#ff6600">73</font>
    <font color="#808000">6d</font>
    <font color="#ff6600">61</font>
    <font color="#808000">73</font>
    <font color="#ff6600">00</font>
    <font color="#808000">63</font>
    <font color="#ff6600">caca</font>
    <font color="#808000">fantasmas.c</font>

Isso acontece porque ele utilizada cada palavra separada por espaços da saída da busca.

    
    <font color="#ff6600">0575f458 </font><font color="#808000">63 </font><font color="#ff6600">61 </font><font color="#808000">63 </font><font color="#ff6600">61 </font><font color="#808000">20 </font><font color="#ff6600">66 </font><font color="#808000">61 </font><font color="#ff6600">6e-74 </font><font color="#808000">61 </font><font color="#ff6600">73 </font><font color="#808000">6d </font><font color="#ff6600">61 </font><font color="#808000">73 </font><font color="#ff6600">00 </font><font color="#808000">63 </font><font color="#ff6600">caca </font><font color="#808000">fantasmas.c</font>

Por isso usamos a flag **[1]**, que faz com que o comando imprima **apenas o endereço** onde ele encontrou a string.

    
    0:017> s -[1]a 0 0fffffff "caca fantasmas"
    0x0575f458

#### Imprimindo a tabela de respostas

Enfim, vamos ao que interessa. Para imprimir todas as strings que representam as respostas, podemos simplesmente, no OutCommands, fazer uma nova busca por string, só que dessa vez genérica, dentro de uma faixa razoável (digamos, 4KB).

    
    0:006> .foreach ( answerList { s -[1]a 0 0fffffff "caca fantasmas" } ) { s -sa answerList L1000 }
    059ff458  "caca fantasmas"
    059ff467  "caca-fantasmas"
    059ff47a  "a fantasmas"
    059ff48a  "a-fantasmas"
    059ff496  "ghostbusters"
    059ff4a3  "Array"
    059ff4a9  "mus1"
    059ff4ae  "james bond"
    059ff4b9  "007"
    059ff4bd  "mus2"
    059ff4c2  "mission impossible"
    059ff4d5  "missao impossivel"
    059ff4e7  "miss"
    059ff4ed  "o impossivel"
    059ff4fa  "missao imposs"
    059ff509  "vel"
    059ff50d  "miss"
    059ff513  "o imposs"
    059ff51d  "vel"
    059ff521  "mus3"
    059ff526  "carruagens de fogo"
    059ff539  "charriots of fire"
    059ff54b  "chariots of fire"
    ...

Bom, vou parar o _dump_ por aqui, já que, entre os leitores, pode haver quem queria se divertir primeiro do jeito certo =)

#### A solução

Vimos que o jogo é facilmente quebrável porque armazena as respostas em texto claro. Uma solução alternativa seria utilizar um **_hash_ com colisão próxima de zero**. Com isso bastaria trocar as respostas possíveis por _hashs_ possíveis e armazená-los no lugar. Quando o usuário digitasse, tudo que o programa precisaria mudar era gerar um _hash_ a partir da resposta do usuário e comparar com o _hashs_ das respostas válidas.

[![Flash Pops Seguro](http://i.imgur.com/yovlNra.gif)](/images/flash-pops.gif)

Por uma incrível coincidência, esse truquezinho eu aprendi com meu amigo [Thiago](http://codebehind.wordpress.com/) há poucos dias, que está lendo [Reversing](http://compare.buscape.com.br/categoria?id=3482&lkout=1&kw=Reversing+Secrets+of+Reverse+Engineering&site_origem=1293522). Simples, porém funcional.
