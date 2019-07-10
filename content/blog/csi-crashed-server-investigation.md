---
date: "2008-04-23"
title: 'CSI: Crashed Server Investigation?'
categories: [ "blog" ]
---
O [artigo de Jeff Dailey](http://blogs.msdn.com/ntdebugging/archive/2008/04/15/the-digital-dna-of-bugs-dump-analysis-as-forensic-science.aspx) em que ele compara a nossa atividade de "cientistas do _debugging_" com a atividade dos profissionais da análise forense é exatamente o que eu penso sobre nossa profissão. Freqüentemente assisto ao [CSI: Las Vegas](http://www.imdb.com/title/tt0247082/) e mais freqüentemente ainda uso os métodos científicos empregados pela equipe de Gil Grissom para resolver os problemas mais escabrosos que podem ocorrer em um sistema.

Jeff fez uma divertida comparação entre todas as etapas de uma análise forense com todas as etapas de nossa análise do bug. Aqui vai a tradução livre dessas etapas (em linguagem cinematográfica):

<blockquote>_São duas horas da manhã. A câmera focaliza um __pager explodindo sobre um criado-mudo... só pode querer dizer uma coisa: algo de ruim aconteceu e pessoas estão à procura de ajuda. O detetive acorda e diz para sua mulher: "Desculpe, eles precisam de mim... Eu tenho que ir"._</blockquote>

Engraçado, eu fiz a mesma coisa, só porque alguém encontrou um servidor morto.

<blockquote>_O detetive aparece na cena do crime. Todos os policiais estão confusos, então eles apenas mantém a área isolada até que os experts cheguem. Seus anos de experiência e iluminação única irão permiti-lo ver coisas que os outros não vêem._</blockquote>

Umm... Isso só me parece apenas familiar. Eu tipicamente uso Live Meeting ou Easy Assist...

<blockquote>_Usando uma combinação de ferramentas especializadas e métodos aprendidos tanto na escola quanto os aprendidos com o tempo, a evidência é coletada na cena para que seja feita uma pesquisa adicional no escritório. Testemunhas são questionadas: "Por volta de que horas isso ocorreu?", "Você ouviu algum barulho estranho", e "você viu alguém ou alguma coisa não usual". Fotos são tiradas, objetos são arquivados, fibras e amostras de DNA são coletadas._</blockquote>

Ok, então o escopo do problema está determinado e todas as informações disponíveis foram obtidas. Ummm... eu faço isso todo dia.

<blockquote>_O prefeito chama o oficial para que diga ao chefe dos detetives que nós devemos resolver este caso. Isso não pode acontecer de novo.  Nós devemos capturar o vilão!_</blockquote>

Sinta-se livre para substituir "prefeito" com qualquer figura de alto nível gerencial. Uau, isso ou é um cara mau e asqueiroso ou o _driver_ de alguém está causando [_pool corruption_](http://www.dumpanalysis.org/blog/index.php/2008/03/13/crash-dump-analysis-patterns-part-2b/) causando um servidor crítico falhar!

<blockquote>_Nós agora cortamos onde o detetive está no laboratório, usando luminárias,  procurando por evidências de DNA, refletindo sobre os fatos principais do caso, pesquisando crimes passados._</blockquote>

Eu não sei sobre você, mas eu simplesmente me refiro a isso como o **processo de depuração**.

<blockquote>_Finalmente um progresso: o DNA coletado na cena do crime identifica um suspeito que não deveria estar lá. Ao fazer uma pesquisa adicional, o suspeito tem um histórico desse tipo de atividade. O cara mau é capturado, os custos são arquivados e o caso está resolvido!_</blockquote>

Isso deve ser o mesmo que **encontrar a causa principal**, **preencher um bug**, e **lançar uma correção**.

Para finalizar, uma frase do artigo original que resume tudo:

"Ultimately that's what we do.  We are all detectives looking for the digital DNA of bugs in the wild affecting our customers.  We hunt them down using tools, expertise, and experience."

#### Atualização

Dmitry Vostokov imaginou [siglas mais imaginativas](http://www.dumpanalysis.org/blog/index.php/2008/05/22/on-csi-abbreviation/) e fiéis a todos os que depuram problemas em _software_, independente deste rodar em servidores ou máquinas de café. Além, é claro, de uma ótima dica de livro sobre análise forense. Thanks, Dmitry!
