---
categories:
- code
date: '2015-04-20'
tags:
title: Convenção de Chamada
---

Pergunta de um leitor:

#### Leitor: Olhe essa bizarrice em C:

```
void func()
{

}

int main()
{
   func("sbrubles");
   return 0;
}
```

#### Leitor: Embora isso seja permitido, caso você coloque "void func(void)" já não funciona mais. Por quê?

Resposta do Autor: Por que C é zoado :P

OK, a verdade é que não existem (existiam?) muitas regras de sintaxe a serem respeitadas na linguagem pelo compilador. Antigamente, se não fosse colocado nenhum tipo de retorno era como se ele fosse **int** por _default_. Da mesma forma, se não colocar parâmetros vale tudo. É como se fossem os três pontinhos do __printf__. Afinal, você não ia querer ficar repetindo os parâmetros no .c e no .h, não é mesmo :D

Isso me lembra também que havia a declaração "arcaica" da linguagem (já era arcaica antes mesmo do padrão de 1998 sair):

```
void func()
char* sbrubles; /* isso é um argumento de entrada */
{
}
```

#### Leitor: OK, entendi. Mas voltando para meu primeiro exemplo: supostamente usar um va_args pra ler "alguma coisa" certamente leria os parâmetros, certo? E este parâmetro, só fica inutilizado ou chega a dar algum problema mais sério?

Sim, sua suposição a respeito do __va_args__ faz todo sentido. E não, os parâmetros não são inutilizados justamente porque a função chamada pode fazer o que quiser que no retorno o chamador limpa a pilha (e o chamador sabe como ele empilhou os parâmetros-extra).

O __padrão de chamada__ da linguagem (lembra disso?) é __cdecl__. Isso quer dizer que o chamador é que "limpa a sujeira" depois da chamada. Isso é o que permite o "milagre" do __printf__ (oooohhh ooohh oooooohhhh... *sons de anjos*) receber n argumentos.

Só vai dar problema se definir outro padrão de chamada ou se a função chamada mexer no que não devia (se esperar outros tipos ou número de argumentos, por exemplo).

### StdArgs na mão

Agora que sabemos disso, o comportamento do __va_list__ nem deve parecer tão mágico assim. Na verdade, apenas saber que a pilha é onde estão todas as variáveis locais e os endereços de retorno das funções é o suficiente para explorar essa área de memória.

Porém, o uso canônico na linguagem C e a forma mais educada de navegar nos parâmetros extras é usando o header stdarg.h. Isso porque C é uma linguagem independente de plataforma, e _a priori_ não temos a mínima ideia de como os dados estão estruturados no computador. Essa visão das variáveis locais e etc é apenas algo que sabemos sobre a arquitetura PC (8086) porque já brincamos demais de _assembly_ e seus registradores.

```
int soma(int argc, ...);

int main()
{
	int resultado = soma(5, 2, 3, 4, 5, 6);
}

// soma.cpp
#include <stdarg.h>

int soma(int argc, ...)
{
    int ret = 0;

	va_list vl;
	va_start(vl, argc);
    while( --argc )
    {
	    int next = va_arg(vl, int);
        ret += next;
    }

	return ret;
}
```

Uma versão de quem já manja dos internals da arquitetura onde está programando e não se importa com portabilidade poderia simplesmente caminhar pela pilha a partir do endereço de argc.

```
int soma(int argc, ...)
{
	int ret = 0;
	int* argv = &argc + 1;

	while ( argc-- )
	{
		int next = *argv++;
		ret += next;
	}

	return ret;
}
```

Repetindo: isso não é bonito, apesar de simpático. No entanto, se o objetivo é explorar a arquitetura, fique à vontade para navegar pela pilha a partir do endereço das variáveis locais.
