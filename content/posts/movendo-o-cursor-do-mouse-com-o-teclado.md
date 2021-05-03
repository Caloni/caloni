---
categories:
- code
date: '2007-07-26'
title: Movendo o cursor do mouse com o teclado
---

Bom, vamos deixar de papo furado e "codar". Para essa primeira tentativa iremos desenvolver um programa que move o cursor do mouse quando pressionada uma tecla de atalho e voltar à sua posição original quando pressionada outra tecla.

> Nota de desculpas: eu sei que estou sendo rabugento demais com o mouse. Já é o segundo artigo que escrevo falando como evitar o mouse e isso deve realmente irritar os fãs desse ponteirinho irritante.

Como eu já havia dito anteriormente, uso o mouse quando necessário. Quando ele não é necessário ele fica clicando inconscientemente no Windows Explorer, já que utilizo a configuração de clique único, onde as pastas e arquivos ficam selecionáveis apenas pousando o cursor sobre eles. Eu gosto dessa configuração, exceto pelo comportamento desagradável que ocorre quando mudo para a janela do Windows Explorer e meu mouse ganha vida própria, selecionando alguma pasta ou arquivo e mudando meu foco de seleção.

Portanto, o objetivo desse programa é simples e direto: mover o mouse para um canto enquanto eu uso meu teclado. Nada mais, nada menos. Para isso iremos registrar alguns atalhos globais no Windows. Para registrar atalhos globais no Windows utilizamos a função do Windows API RegisterHotKey e é o que estou usando no [código]. O importante aqui é saber que iremos ser avisados do pressionamento das teclas que registrarmos por meio dessa função através do loop de mensagens da thread que chamar a função.

Um loop de mensagens é a maneira definida pelo Windows para avisar as aplicações dos eventos que ocorrerem no sistema que são relevantes para as suas janelas. Teremos chance de observar isso mais vezes, mas por enquanto basta ter uma visão geral do fluxo de mensagens que ocorre quando digitarmos a nossa tecla de atalho.

![Ilustração do loop de mensagens no Windows para input do usuário](/img/windows_loop_mensagens_input.gif)

Como você pode ver o [código] não tem muitos segredos. Para registrar os atalhos, usamos a função RegisterHotKey. Para manipular os eventos usamos o tal loop de mensagens e manipulamos a mensagem WM_HOTKEY de acordo com a tecla pressionada. Para mover o mouse usamos a função SetCursorPos (e para armazenar a posição atual GetCursorPos). Por fim, para ler configurações de um .ini usamos a função GetPrivateProfileInt. Abaixo um exemplo desse arquivo texto:

    [HideCursor]
    DisableX=600
    DisableY=0

Você acha que os atalhos "WinKey + Del", "WinKey + Insert" e "WinKey + End" foram uma má escolha para essa função de esconder o mouse? Concordo. Fiz de propósito. Que tal customizar o programa para que as teclas sejam lidas do arquivo de configuração HideCursor.ini?

[código]: /code/registerhotkey.cpp