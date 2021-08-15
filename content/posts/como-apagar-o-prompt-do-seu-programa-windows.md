---
categories:
- code
date: 2018-01-23 20:40:50-02:00
tags:
title: Como Apagar o Prompt do seu Programa Windows
---

Geralmente se cria um projeto console/prompt quando há a necessidade de interfacear com o usuário com o uso da tela preta, saída padrão, etc. E no caso do Windows também há a possibilidade de criar um programa Win32 onde não há prompt, pois a função do programa ou é ser invisível ou criar, sabe como é, janelas. Mas nenhum dos dois possibilita ambos ao mesmo tempo. Este snippet permite que você faça isso.

```
void check_console() 
{
  HWND console = GetConsoleWindow(); // obtém a janela do console atual
  if (! console) return; // se não tiver, paciência
  unsigned long pid; // vamos pegar o pid do processo relacionado a este console
  if (! GetWindowThreadProcessId(console, &pid)) return; // se não der, paciência também
  if (GetCurrentProcessId() != pid) return; // se não formos nós os que criamos este prompt deixa quieto
  FreeConsole(); // somos nós que criamos: desaloca o console e já eras
}

int main()
{
    check_console();
}
```

Para isso funcionar você criar um projeto console no Visual Studo. Essa opção está no Linker, System:

![](https://i.imgur.com/uWYtwqL.png)

E voilà!
