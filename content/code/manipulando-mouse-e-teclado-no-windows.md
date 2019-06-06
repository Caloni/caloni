---
date: 2018-07-04T13:44:40-03:00
title: "Manipulando Mouse e Teclado no Windows"
categories: [ "code" ]
---
Uma forma extremamente bem comportada que o Windows tem para manipular entrada de mouse e teclado são as funções API BlockInput/SendInput. Enquanto uma bloqueia todos os eventos de input vindo de todos os lugares do sistema, o outro consegue enviar inputs apenas por software. Imagine a peça que você pode pregar em seus amigos.

No entanto, estas funções não são para amadores. É preciso entender o que são threads, por exemplo, pois apenas a thread que chamou BlockInput pode depois chamar SendInput com sucesso. Além disso, apenas essa thread pode desbloquear novamente os inputs chamando BlockInput novamente, mas dessa vez passando FALSE em seu único parâmetro. E de qualquer forma, uma vez que o programa que chamou BlockInput com TRUE morreu o sistema detecta e tudo volta ao normal.

Essas funções API podem ser úteis para interação remota, por exemplo, quando um usuário não consegue realizar uma operação e ele pode mais atrapalhar do que ajudar você pode bloquear os inputs dele e emular seus próprios cliques de mouse e teclado pela rede.

Nota: usar essas APIs na própria máquina pode ser bem frustrante. Tenha sempre em mãos uma VM de teste.

Funções citadas neste texto:

 - [BlockInput](https://msdn.microsoft.com/en-us/library/windows/desktop/ms646290(v=vs.85).aspx)
 - [SendInput](https://msdn.microsoft.com/en-us/library/windows/desktop/ms646310(v=vs.85).aspx)

