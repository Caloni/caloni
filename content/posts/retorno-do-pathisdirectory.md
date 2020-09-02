---
date: "2008-09-10"
tags: [ "code", "draft",  ]
title: "Retorno do PathIsDirectory"
---
Estava eu outro dia programando aquele código esperto "para ontem" quando me deparei com uma situação no mínimo inusitada. Ao testar se um caminho recebido era de fato um diretório.aspx) me foi retornado pela API um valor diferente de TRUE. E diferente de FALSE!

De acordo com a documentação, o retorno deveria ser TRUE caso o caminho enviado à função fosse de fato um diretório. Caso contrário, o retorno deveria ser FALSE.

Note que existem apenas dois valores possíveis para essa função. Porém, o valor retornado não é 1, o equivalente ao define TRUE, mas sim 0x10 (16 em hexadecimal). O simples exemplo abaixo deve conseguir reproduzir a situação (Windows XP Service Pack 3):


Isso quer dizer apenas que o código abaixo vai funcionar,


o código abaixo vai funcionar


e o código abaixo não vai funcionar:


E, pior, o código abaixo também não vai funcionar!


Pesquisando um pouco descobri uma boa discussão sobre o tema, e inclusive que outras pessoas descobriram o interessante detalhe que para pastas normais o retorno é 0x10, mas para compartilhamentos o retorno é 0x1.

O problema ocorre por causa da maneira que a função determina se o caminho é um diretório ou não. Uma simples vistoria sobre a função nos revela o detalhe crucial:


Ou seja, para pastas locais a função simplesmente usa a conhecidíssima GetFileAttributes.aspx), que retorna o flag 0x10 setado caso se trate de uma pasta, de acordo com a documentação:

"The attributes can be one or more of the following values.




Aqui termina nossa dúvida sobre o pequenino bug na documentação. E isso nos lembra também que é sempre bom comparar as coisas da melhor maneira possível. E essa melhor maneira em se tratando de ifs é supor apenas dois valores binário: ou é zero ou é não-zero.
