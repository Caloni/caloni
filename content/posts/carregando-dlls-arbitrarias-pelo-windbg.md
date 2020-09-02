---
date: "2007-11-23"
tags: [ "code", "draft",  ]
title: "Carregando DLLs arbitrárias pelo WinDbg"
---
Durante meus testes para a correção de um bug me deparei com a necessidade de carregar uma DLL desenvolvida por mim no processo depurado. O detalhe é que o processo depurado é de terceiros e não possuo o fonte. Portanto, as opções para mim mais simples são:

	
  * Usar o projeto RmThread para injetar a DLL (nesse caso iniciando o processo através dele).
  * Fazer um módulo _wrapper_ para uma DLL qualquer e ser carregado de brinde.
  * Usar o WinDbg e brincar um pouco.

Por um motivo desconhecido a terceira opção me pareceu mais interessante =).

A seqüência mais simples para carregar uma DLL através do WinDbg é chamar kernel32!LoadLibrary através de um código digitado na hora, o que podemos chamar de live assembly (algo como "assembly ao vivo"). Porém, essa simples seqüência contém um pouco mais que uma dúzia de passos.

Primeiro devemos parar a execução, voltar para um ponto seguro do código e armazenar o local seguro em um registrador temporário (o WinDbg tem 20 deles, $t0 até $t19).



Parada a execução em um local seguro e armazenado o IP, em seguida podemos alocar memória para entrar o código em assembly da chamada, além do seu parâmetro, no caso o path da DLL a ser carregada.


Note que estamos usando a versão ANSI do LoadLibrary, aquela que termina com A. Sendo assim, escrevemos uma string ANSI como parâmetro usando o comando eza.

O último passo é chamar a função previamente "editada". Para isso basta mudarmos o endereço da próxima instrução para o começo de nosso código e mandar executar, pois ele irá parar automaticamente no breakpoint que definimos "na mão", o int 3 digitado. Após a execução devemos voltar o ponteiro usando nosso backup no registrador $t0.


Como pudemos ver pela saída, a DLL foi carregada e agora temos a possibilidade de chamar qualquer código que lá esteja. Como fazer isso? Provavelmente usando o mesmo método aqui aplicado. Live-assembly é o que manda 8).
