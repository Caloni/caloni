---
categories: [ "code" ]
date: "2011-10-18"
tags: [ "debug", "tools", "draft" ]
title: "Depuração de emergência com receita de bolo no WinDbg"
---
Continuando o papo sobre o que fazer para analisar rapidamente um crash no servidor com o pacote WinDbg, na maioria das vezes a exceção lançada pelo processo está diretamente relacionada com um acesso indevido à memória, o que tem diversas vantagens sobre problemas mais complexos:

  - Possui localização precisa de onde ocorreu a violação, incluindo o nome do arquivo e a linha do código;
  - Não corrompe a pilha ou, se corrompe, não chega a afetá-la a ponto da thread ficar irreconhecível;
  - A thread que contém a janela de crash é a culpada imediata, então basta olhar a pilha.

Resumindo: basta olhar a pilha! Mas, para isso ser efetivo, precisaremos do PDB do executável que gerou o crash, pois através dele é possível puxar a tal localização da violação de acesso. Isso quer dizer que se você mantiver o executável, e DLL também é executável, juntinho com seu PDB, ou pelo menos facilmente localizável, sua vida será muito mais fácil e florida. Também significa que poderá começar a beber cerveja mais cedo.

Mesmo que em alguns momentos-surpresa apareça uma ou outra tela indesejada.

O comando mais útil na maioria desses casos é mostrar a pilha no modo verbose, usando o comando kv seguido de enter. Porém, antes disso, precisamos:
	
  1. Ajeitar o path dos símbolos;
  2. Recarregar o PDB do executável suspeito;
  3. Mostrar a pilha de todas as threads até descobrir a culpada.

Todos esses comandos podem ser vistos abaixo. São, respectivamente, .symfix, .reload e novamente o kv, com a diferença de que para todas threads.

Ops! Um pequeno desvio do curso. Estamos rodando um processo de 32 bits dentro de um SO 64 bits, no exemplo um Windows 7. Isso pode acontecer e é bom saber o que fazer nesse caso. Seguimos com os comandos .load wow64exts e .effmach x86, que irá carregar a extensão de wow64 do depurador e iniciar a tradução da stack para 32 bits.


Nosso depurador favorito acusa uma pilha que contém a função WerpReportFault. Nessa mesma thread a última linha conhecida nossa está no arquivo crashonserver.cpp:13. E essa situação, caro leitor, é dez por cento de tudo o que você precisa saber sobre WinDbg para resolver, mas que já resolve noventa por cento dos casos que irá encontrar em produção. Belo custo-benefício, não?
