---
categories:
- reviews
date: '2021-06-06'
tags:
- recipes
- food
title: Em busca da pizza perfeita
---

Agora que me sinto confortável com minha [massa básica de pão rústico] é hora de voltar para o projeto pizza de longa fermentação caseira. A [última massa que trabalhei], a receita de Pizza Crust do site King Arthur Baking, estava semi-aprovada depois de um teste rápido cujo resultado de fato ficou crocante por fora e macia por dentro. Para quem gosta de massa fina é possível deixar mais baixa e para os fãs da grossa é só deixar crescer. Há, portanto, uma boa faixa de experimentação para todos os gostos.

Existe a versão da [mesma receita com fermento natural] no site, mas mesmo com o fermento instantâneo o truque para desenvolver aroma é deixar fermentar lentamente na geladeira, de 4 a 24h, podendo se estender dependendo do uso do fermento. O uso do azeite é primordial para separar do molho e manter a crocância.

Um problema com essa versão que tive foi a forma de sovar, que por usar batedeira entendi que precisava de uma boa sova para sua maciez. Pensando em um modelo mais viável no momento comecei a buscar no mesmo site uma versão sem sovar e descobri duas versões candidatas: a [No-Knead Pizza Crust] e a [Artisan No-Knead Pizza Crust]. A primeira receita parece mais direta ao ponto, mas sua alta hidratação me deixou intimidado. Já a versão Artisan possui menos hidratação (apesar de alta) e poderia dar certo com uma farinha comum de mercado, que é meu objetivo, e ainda de quebra não necessita de trabalhar a massa. Apenas deixar o tempo passar.

E a partir dela há mais três links úteis para entender melhor o processo, com imagens e vídeos, e como converter a receita para usar fermento natural (o objetivo final):

 - [The best pizza you'll ever make], versão original do blogue de Julia Reed.
 - [Um vídeo do processo] de dobra após a fermentação inicial.
 - Mais [um vídeo de Martin Bakes] preparando e assando pizzas.
 - [Como adicionar fermento natural a receitas], um guia super-completo e fundamental.

Com toda essa munição lida, o primeiro passo é preparar a primeira massa de teste, versão reduzida, com fermento instantâneo, apenas mantendo as proporções, e ver o que acontece no forno. O tempo da longa fermentação é de 24 horas em temperatura ambiente, mas a própria Julia Reed disse que uma versão de 16 horas ficou mais suave para combinar com os toppings. Vou buscar um meio termo, embora meu primeiro teste seja realmente a textura da massa e a tentativa de moldá-la.

Preocupado e curioso a respeito das proporções entre farinha, água e fermento, e tentando entender o porquê do mesmo princípio se aplicar a receitas aparentemente tão diferentes quanto pão e pizza, coletei as proporções dessas receitas para começar a entender a dinâmica na prática e experimentar novas proporções porventura. Fiz uma listinha em Python:

{'pao': {'fermento': 227, 'agua': 340, 'farinha': 602, 'alimentado': True, 'instantaneo': 4.5, 'sal': 15}, 'pizza': {'fermento': 227, 'agua': 155, 'farinha': 300, 'instantaneo': 1.5, 'sal': 6}, 'pizza_sem_sovar': {'fermento': 0, 'agua': 340, 'farinha': 362, 'instantaneo': 0.75, 'sal': 6}, 'pizza_sem_sovar_artisan': {'fermento': 0, 'agua': 185, 'farinha': 250, 'instantaneo': 0.375, 'sal': 8, 'acucar': 2}}

O código abaixo fiz para imprmir as proporções:

```py
def proporcao(recipe):
	print('agua:', '{:.2f}%'.format(100.0 * recipe['agua'] / recipe['farinha']))
	print('fermento:', '{:.2f}%'.format(100.0 * recipe['fermento'] / recipe['farinha']), '(alimentado)' if 'alimentado' in recipe else '(sem alimentar)')
	if 'instantaneo' in recipe:
		print('instantaneo:', '{:.2f}%'.format(100.0 * recipe['instantaneo'] / recipe['farinha']))
	print('sal:', '{:.2f}%'.format(100.0 * recipe['sal'] / recipe['farinha']))
	if 'acucar' in recipe:
		print('acucar:', '{:.2f}%'.format(100.0 * recipe['acucar'] / recipe['farinha']))

for name, recipe in recipes.items():
	print(name)
	print('ingredientes:', recipe)
	proporcao(recipe)
	print('---')
```

```
pao
ingredientes: {'fermento': 227, 'agua': 340, 'farinha': 602, 'alimentado': True, 'instantaneo': 4.5, 'sal': 15}
agua: 56.48%
fermento: 37.71% (alimentado)
instantaneo: 0.75%
sal: 2.49%
---
pizza
ingredientes: {'fermento': 227, 'agua': 155, 'farinha': 300, 'instantaneo': 1.5, 'sal': 6}
agua: 51.67%
fermento: 75.67% (sem alimentar)
instantaneo: 0.50%
sal: 2.00%
---
pizza_sem_sovar
ingredientes: {'fermento': 0, 'agua': 340, 'farinha': 362, 'instantaneo': 0.75, 'sal': 6}
agua: 93.92%
fermento: 0.00% (sem alimentar)
instantaneo: 0.21%
sal: 1.66%
---
pizza_sem_sovar_artisan
ingredientes: {'fermento': 0, 'agua': 185, 'farinha': 250, 'instantaneo': 0.375, 'sal': 8, 'acucar': 2}
agua: 74.00%
fermento: 0.00% (sem alimentar)
instantaneo: 0.15%
sal: 3.20%
acucar: 0.80%
```

[massa básica de pão rústico]: /pao-rustico
[última massa que trabalhei]: https://www.kingarthurbaking.com/recipes/pizza-crust-recipe
[mesma receita com fermento natural]: https://www.kingarthurbaking.com/recipes/sourdough-pizza-crust-recipe
[No-Knead Pizza Crust]: https://www.kingarthurbaking.com/recipes/no-knead-pizza-crust-recipe
[Artisan No-Knead Pizza Crust]: https://www.kingarthurbaking.com/recipes/artisan-no-knead-pizza-crust-recipe
[The best pizza you'll ever make]: https://www.kingarthurbaking.com/blog/2015/01/05/best-pizza-youll-ever-make
[Um vídeo do processo]: https://www.kingarthurflour.com/videos/baking-skills/how-to-stretch-and-fold-pizza-dough
[um vídeo de Martin Bakes]: https://www.kingarthurbaking.com/videos/martin-bakes-at-home/sourdough-pizza
[Como adicionar fermento natural a receitas]: https://www.kingarthurbaking.com/blog/2015/10/29/adding-sourdough-recipe