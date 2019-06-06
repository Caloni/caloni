---
date: "2017-03-14"
title: "Entrando na zona com Windows"
categories: [ "code" ]

---
**Update 2019-03-20: Adicionando programa para fazer tela cheia no Windows e retirados detalhes que não uso mais.**

Um [artigo anterior](/entrando-na-zona-com-vim) havia dado umas dicas de como transformar o Vim em uma ferramenta para toda obra, com isso limitando as distrações quando se está em um computador, e com isso facilitando a entrada e a permanência no estado de fluidez de produtividade que conhecemos como "flow", ou estar na zona. Agora é a vez do Windows.

O Windows 10 já vem com atalhos pré-instalados assim que você loga nele. Tem browser, navegador de arquivos, notícias, e uma caralhada de coisas inúteis que ficam se mexendo na tela, chamando sua atenção, distraindo sobre o que é mais importante.

Mas é possível arrancar tudo isso e deixar na barra de tarefas pinado apenas as coisas realmente vitais para o uso do computador de trabalho, geralmente o terminal, o navegador (pesquisa, emails, etc) e o editor (não necessariamente o Vim).

### Otimizando o terminal

O terminal do Windows, o Command Prompt, ou cmd para os íntimos, sofreu algumas mudanças ultimamente. Entre elas há a transparência, o que o tornou cool, e a tela cheia (atalho Alt+Enter), o que o tornou ideal como ferramenta de navegação para programadores (melhor do que o explorer, que virou um penduricalho de atalhos inúteis também). Você pode ativá-lo já entrando na tela cheia e com o code page de sua preferência (o meu é 65001, que é o utf8) usando esse pequeno programa:

```c++
#include <iostream>
#include <windows.h>

#pragma comment(lib, "user32")

int main()
{
    if( ! SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE | CONSOLE_WINDOWED_MODE, NULL) )
    {
        // Se falhas com GLE 120 (função não suportada) usar função abaixo.
        ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    }
    system("chcp 65001");
}

```

### Configurando o git para controlar o fonte rapidamente

Os comandos do git são muito verbose. Duas letras já seriam suficiente (o Windbg manipula seu programa com apenas uma...). Para otimizar a digitação no git crie uns aliases em seu HOME\.gitconfig:

```
[user]
	name = Wanderley Caloni
	email = wanderley.caloni@bitforge.com.br
[alias]
	st = status
	br = branch
	ci = commit
	co = checkout
[core]
	editor = c:/Programs/Vim/vim80/gvim.exe
	autocrlf = true
	excludesfile = C:\\Users\\Caloni\\.gitignore
	fileMode = false
```

### Atalhos da barra iniciar

Agora, através dos atalhos Win+1, 2, 3... pode-se abrir e alternar entre os aplicativos principais do seu dia-a-dia, que devem ficar "pinados" na barra de tarefas. Os meus atualmente são três: terminal (1 cmd), editor (2 vim) e browser (3 chrome). Não é necessário colocar coisas como Visual Studio, já que minha navegação é feita rapidamente pelo terminal para o projeto que irei mexer. Com isso o foco fica restrito a apenas uma coisa: o que você tem que fazer hoje? =)
