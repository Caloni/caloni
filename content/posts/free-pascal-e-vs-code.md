---
categories:
- code
date: '2019-03-09'
tags:
- draft
title: Free Pascal e VS Code
---

Agora que o VS Code é a ferramenta universal para todas as plataformas e linguagens imagináveis, acreditem ou não, há até plugin para Pascal. Ao instalar a extensão mantida por Alessandro Fragnani você recebe o intelisense e algumas dicas durante erros de programação.

A própria integração com o Free Pascal Compiler, o compilador open source de Pascal multiplataforma, já é mostrada na Home desse plugin. É só seguir os modelos e alterar de acordo com o que pede o VS Code (que está sendo atualizado constantemente).

Após isso o Terminal, Run Build Task exibe a opção de rodar o fpc.exe para seu programa e a compilação sai perfeita ou ele aponta os erros direto no fonte. O programa resultante pode ser executado por fora ou dentro do VS Code e tudo OK.

PS: Se quiser depurar é possível gerar informação de debug para o gdb via a flag -g, ou apenas usar o velho writeln('passou por aqui'). Alguns dizem que o segundo uso algumas vezes é conveniente. Faz sentido se é um programa de faculdade.

Bons programas verdadeiramente estruturados! (Pascal, diferente de C, permite procedures aninhadas, passando o self durante as chamadas internas; isso, sim, é linguagem bem desenhada).