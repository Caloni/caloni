---
date: "2020-04-05"
link: "https://gist.github.com/Caloni/fd22d49ad7e9c046120d98876c8cad38"
categories: [ "code" ]
title: "Code Jam 2020"
---
O Code Jam esse ano terminou rápido para mim. Estou enferrujado? Nem tanto. Apenas dei menos atenção ao evento no seu início, mas apesar de me concentrar nas últimas 11 horas não tive um resultado satisfatório, obtendo 24 pontos ao total, o que não me dá direito para o torneio, que exige pelo menos 30.

Minha abordagem no primeiro problema foi o feijão com arroz de ir lendo os valores e verificando para cada novo elemento da linha se havia repetição nos valores já lidos da mesma linha. Eu me compliquei na hora de fazer a mesma coisa para as colunas, pois inseri essa checagem dentro do loop da linha, evitando, assim, sempre a última coluna. Foi a parte que mais perdi tempo útil de todo o torneio (não li todos os exercícios antes).

O segundo problema foi o mais simples de todos para mim. Entendendo o enunciado, em que o título dá uma dica valiosa sobre o comportamento do algoritmo (aninhado), foi só usar a mesma lógica que nós programadores usamos na hora de aninhar parênteses.

O terceiro exercício me parecia fácil no começo. Desenhei na minha janela um esboço da ideia inicial, que era manter um registro de todos os minutos de um dia e a cada nova tarefa popular cada minuto. Meu erro principal foi não considerar que todos os minutos de uma tarefa devem estar sob a responsabilidade de apenas uma pessoa. Corrigido isso, meu código passou nos poucos testes disponíveis no problema, mas não passou na hora de submeter. Estou sem saber até agora o que fiz de errado.

E, por fim, o último foi o mais divertido porque envolveu mexer em ambiente. O script iterativo do Google não funcionou direito no Windows, mas depois de uns testes no WSL percebi que o erro mesmo é não dar flush nos printf do meu lado. Sempre haverá problemas de buffer em stdin/stdout.

De qualquer forma, não consegui resolver mais do que 10 bits. Já estava ficando tarde e eu me perdi em digressões de como tornar o código maleável para adivinhar mais que duas viradas quânticas. Deixei esse código experimental de lado e fui ler o próximo.

Apenas li o enunciado. Ele falava sobre o quadrado latino, assim como o problema original. E como tive dores de cabeça por causa desse primeiro exercício, e faltava apenas uma hora e meia para terminar a prova, dei por satisfeito mais um ano brincando de programar.
