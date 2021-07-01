---
categories:
- code
date: '2020-06-21'
tags:
- ccpp
title: C++ Co Routines
---

Entre os gêneros mais famosos do cinema e da programação está o terror, esse estado mental que se caracteriza pelo medo ou pela aversão a uma situação que envolve a perda de controle. Nesse quesito se encaixam as novas corrotinas que serão adotadas pelo padrão C++.

No último Caloni Bode Cast Live Privado, aqueles que não estão publicados no YouTube, conversei com um amigo por mais uma vez (já perdi a conta quantas foram) sobre a famigerada implementação, mas acho que dessa vez detectei melhor o que torna essa nova biblioteca de C++ tão repugnante para os amantes de boas soluções de engenharia e do padrão da linguagem.

A primeira ressalva diz respeito à alocação dinâmica. Ao usar esse modelo de rotinas cooperativas o programador é obrigado a alocar espaço para o estado dinamicamente, o que fere duas premissas da linguagem: o controle absoluto do modelo de execução para o programador e a certeza que ele irá apenas pagar em performance o que ele usar. Se os fãs da linguagem fossem religiosos, eles diriam agora que esta não foi uma decisão muito cristã do comitê.

Eu continuo defendendo que a linguagem C seja usada caso surjam contra-indicações na prática da STL.