---
categories:
- code
date: '2010-03-15'
tags:
- draft
title: Convivendo entre TodoList e Microsoft Project
---

O próximo artigo sobre escovação de bits ainda está no forno. Tirar férias (de 40 dias) é uma escassez de ideias! No momento, posso explicar a facilidade que tive para continuar usando o TodoList para gerenciar minha equipe e ainda assim sincronizar nossas tarefas em um cronograma do Microsoft Project.

As razões de eu usar o TodoList são meio óbvias: ele faz tudo que eu preciso para organizar minhas tarefas do dia-a-dia e é portátil. Enquanto isso, o Project, além de não ser portátil (eu preciso levar comigo o instalador de 200 MB? E Instalar?) possui um formato difícil de mudar, já que foi feito para projetar o mundo e não para ser compartilhado facilmente.

Mas vamos lá. Tudo que precisamos é de uma edição atual do TodoList e do Microsoft Project. A primeira coisa que devemos fazer é exportar as tarefas que queremos do TodoList para um CSV padrão, usando as colunas que gostaríamos de importar para o Project:

Depois vem a parte complicada, mas nem tanto. Abrimos o projeto para onde queremos importar essas tarefas e escolhemos a opção Abrir novamente, só que dessa vez selecionando o nosso amigo tarefas-exportadas.CSV.

Só que antes de importarmos, calma lá. Temos que criar uma nova coluna que irá guardar os IDs das tarefas do TodoList, para que nas próximas importações consigamos mesclar os dados já existentes. Portanto, crie uma nova coluna (pode ser qualquer NúmeroX não-alocado ainda) com um nome significativo.

Agora podemos partir para a importação. Imaginando que seja a primeira, vamos criar um mapeamento inicial para essa primeira migração:

Na hora de escolher quem é que, só precisamos definir quais colunas no Project correspondem a quais colunas do TodoList, e lembrar de alocar o ID na nossa coluna especial.

Mais alguns Next da vida e pronto! Temos nossas tarefas devidamente importadas.

Mas é claro que todo esse trabalho não valeria a pena se tivéssemos que (arght) mexer no Project. Para evitar esse trabalho impuro, continuamos atualizando o andamento dos projetos no nosso pequeno, leve e sagaz TodoList e, quando precisarmos, é só importarmos novamente os dados, só que dessa vez usando um mapa já salvo (siga os screenshots acima) e marcando nosso ID do TodoList como chave. Dessa forma as tarefas já importadas são apenas atualizadas, e não criadas novamente. Esse é o famoso "pulo do gato" (que eu ouvia matinalmente na minha época de office-boy).

Depois de eu pesquisar toda essa trama, descobri que o uso do Project não será necessário. Sorte minha. Agora, se você não tiver sorte...