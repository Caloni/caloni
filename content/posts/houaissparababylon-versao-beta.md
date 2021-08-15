---
categories:
- blog
date: '2008-11-15'
tags:
title: HouaissParaBabylon versão beta
---

Depois de muitos fins-de-semana divididos em horas picadinhas de programação de lazer, está disponível em vosso saite a primeira versão para usuários do conversor do dicionário Houaiss para o aplicativo Babylon.

Foi uma longa jornada, sim, mas espero que valha a pena para quem esperou. Também espero poder receber inúmeras respostas com dúvidas, sugestões e até mesmo mais problemas que vierem a acontecer.

Segue um pequeno roteiro do funcionamento do programa, que é bem simples, aliás. Para que tudo dê certo, no entanto, é necessário que o computador onde será feita a conversão possua os três programas abaixo instalados e funcionamento corretamente:

  * Dicionário Houaiss. Testado na versão 2, deve ser instalado com opção de cópia dos arquivos no disco rígido.
  * Babylon. Testado nas versões 6 e 7. Pode ser registrado ou não.
  * Babylon Builder. O construtor dos dicionários Babylon. Apesar de ser possível construir dicionários personalizados para o Babylon, é necessário que se use esse aplicativo conversor. O HouaissParaBabylon o usa, e por isso precisa que ele esteja instalado corretamente.

Tudo isso verificado, basta então clicar no botão de Iniciar Conversão, sentar e esperar. A primeira fase envolve três passos:

  * Desencriptação do dicionário original. Isso é feito baseando-se em nossa análise de engenharia reversa.
  * Montagem do projeto de dicionário Babylon. Para isso existe um processo de interpretação do formato Houaiss, agora desencriptado, e sucessivas traduções para um projeto que o Babylon Builder irá entender.
  * Construção do dicionário Babylon. Essa parte é feita pelo Babylon Builder. Por ser o maior dicionário de português da atualidade, esse processo pode demorar bastante, e com certeza irá se tornar o maior dicionário já instalado na sua lista de dicionários do Babylon.

Na segunda fase, após toda essa movimentação de HD, existe apenas uma coisa a fazer: instalar o dicionário no Babylon.

Quem faz isso é o próprio Babylon, se devidamente instalado. Se tudo deu certo, o HouaissParaBabylon sai de fininho e deixa o usuário com o progresso da instalação do dicionário Houaiss-Babylon.

Se não for encontrado o dicionário Houaiss devidamente instalado no disco rígido, será exibida uma mensagem de erro pedindo que a instalação seja feita dessa maneira. Se, contudo, não for possível localizar a instalação do dicionário, será pedido ao usuário que diga onde ela se encontra, ou aponte para a pasta "Houaiss" em seu CD de instalação, uma dica suficiente para que a operação seja bem-sucedida.

Outros erros comuns, como o Babylon Builder não instalado, serão obviamente avisados ao usuário. Erros mais raros terão um tratamento mais genérico. No entanto, nem por isso ele está livre de solução. Ao sair de uma conversão mal-sucedida, o usuário tem a opção de exportar o log de operações que foram realizadas durante a malfadada operação. Dessa forma, ele próprio conseguirá diagnosticar o problema ou, em casos mais sérios, me enviar o resultado de suas tentativas.

E é isso. Para uma versão inicial, talvez esteja razoável. Quem confirmará serão os ansiosos usuário que, espero sinceramente, consigam seus objetivos há tempos aguardados.
