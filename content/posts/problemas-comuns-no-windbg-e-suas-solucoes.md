---
categories:
- blog
date: '2012-05-27'
tags:
- draft
title: Problemas comuns no WinDbg e suas soluções
---

Depois de uma agradável manhã e tarde acompanhando o [curso de desenvolvimento de drivers do meu amigo Ferdinando](http://driverentry.com.br/blog/?page_id=16) voltei para a casa para brincar um pouco mais com o mundo kernel e voltar a encontrar problemas com o WinDbg & Cia que há mais ou menos 1 ano atrás não tinha.

Pesquisando por um problema específico envolvendo PDBs reencontrei o [blogue do Ken Johnson](http://www.nynaeve.net/), MVP Microsoft e analista por profissão e diversão, é conhecido por suas excelentes contribuições no mundo da depuração de sistema (notadamente WinDbg). Existe um post específico que ele escreveu para economizar tempo com problemas que ocorrem de vez em quando em uma sessão ou outra de depuração, mas nunca paramos tempo o suficiente para resolver.

Além de outros, ele lista alguns que particularmente já aconteceram comigo ou com colegas de depuração:

**O WinDbg demora um tempo absurdo para processar o carregamento dos módulos e está usando tempo máximo de processamento em apenas uma CPU.**

Isso ocorre porque existem breakpoints ainda  não resolvidos. Resolva deixando apenas esses tipos de breakpoints que são absolutamente necessários, pois cada vez que um módulo é carregado o depurador precisa fazer o parser de cada um deles para verificar se ele já consegue resolve-lo.

Às vezes, porém, existe algum lixo nos workspaces carregados por ele que permanecem mesmo depois de apagarmos todos os breakpoints inúteis ou reiniciar o sistema. Em último caso, sempre podemos apagar o workspace do registro, em **HKCU\Software\Microsoft\Windbg\Workspaces**.

**O WinDbg continua demorando décadas para analisar o carregamento, mas agora nem consome tanta CPU assim.**

Isso ocorre porque na cadeia de paths para procurar por símbolos existe algum endereço de rede/internet errado que faz com que ele tenha que caminhar em falso diversas vezes. Esse e outros erros de símbolos sempre poderão ser analisados através do universal **!sym noisy**, que imprime todo tipo de informação útil do que pode dar errado durante um .reload explícito (eu digitei) ou implícito (lazy reload).

**O WinDbg continua recusando carregar um símbolo que eu sei que existe e sei que é válido.**

Talvez ele exista, mas por algum motivo foi copiado corrompido para o symbol server. Mais uma vez, **!sym noisy** nele e deve acontecer algum erro de **E_PDB_CORRUPT**. Nesse caso, apague o PDB culpado e tente de novo.

E, como brinde, um grande aliado da produtividade: **como evitar que o WinDbg bloqueie seu PDB enquanto você precisa constantemente recompilar seu driver:**

.reload -u modulo

Fonte: Blog do [Nynaeve](http://www.nynaeve.net/?p=164).