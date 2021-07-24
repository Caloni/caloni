---
categories:
- code
date: '2020-06-13'
link: https://gist.github.com/Caloni/368a8ce88206c13aac6ca27a56975af2
title: Historical Price
---

Havia um job esta semana de um assunto que me encanta desde a época de investidor: base histórica de cotações. Estamos falando de ações da Bovespa. Na época que era investidor frequente mantinha uma base que era atualizada por um programinha em Java (esqueci o nome), mas nunca tive certeza se os ajustes feitos pelo programa eram os corretos. Surgiu agora a possibilidade de eu realizar código que converte uma base histórica recebida com um minuto por linha em campos divididos por ponto-e-vírgula (o CSV do Windows) para candles de várias periodicidades. E isso justo agora que ando estudando awk. Então não deu outra: usei esta linguagem clássica como ferramenta para esta conversão.

O código ficou, em minha humilde opinião, elegante e pequeno, pois se aproveita da composição das periodicidades. Ou seja, o período de cinco minutos é a consolidação de cinco linhas de um minuto, mas a de quinze minutos não são quinze linhas de um minuto, mas três de cinco minutos, que já estão sendo calculados a cada cinco linha. E assim por diante. Usando os arrays associativos do awk é possível manter o estado de cada candle até o momento de gerar a saída desejada, que no exemplo que codifiquei ficou como um comando SQL de insert em um banco fictício que grava cada tipo de candle em uma tabela.

O uso de um array por candle simplificou o código, pois ao criar uma função que manipula o candle que está finalizando e o próximo eu posso simplesmente passá-los como argumentos. Dessa forma eu só preciso compor os filtros de linhas de acordo com o resto da divisão do seu número. No exemplo inicial, o candle de cinco minutos está finalizando quando RN é igual a cinco ou múltiplos de cinco, enquanto um novo candle se inicia em múltiplos de seis.