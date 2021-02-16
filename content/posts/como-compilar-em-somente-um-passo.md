---
date: "2009-05-25"
title: Como compilar em somente um passo
tags: [ "draft", "blog" ]
---
Uma das primeiras perguntas do [teste do Joel](http://brazil.joelonsoftware.com/Articles/TheJoelTest.html) é saber se você pode compilar todo o projeto em apenas um passo. Essa é uma **questão essencial** e um desafio para muitas equipes. Perdem-se horas sagradas para gerar um novo Release.

Compilação automática geralmente está disponível nas ferramentas de desenvolvimento. Se você estiver usando o Visual Studio, por exemplo, é possível fazer isso com uma linha:

    
    devenv minha-solução.sln /Rebuild Release

Se não for exatamente o que você precisa, basta fazer uma [pesquisa de quinze minutos](http://www.google.com/search?q=visual%20studio%20automatic%20build) e encontrar os parâmetros corretos. O objetivo é: **eu rodo esse comando em cima do projeto inteiro em uma máquina zerada e ele simplesmente compila**.

#### Múltiplas soluções

É lógico que ter apenas um _solution/workspace_ para guardar projetos médios e grandes é inviável. Demora para carregar no ambiente e possuem dezenas de dependências. Isso já foi tentado duas vezes nas duas empresas em que trabalhei e não funcionou. Talvez por isso seja necessário criar um _script_ que rode o comando acima para todas as soluções do projeto, o que não muda muito o _modus operandi_ da coisa:

    
    call :Build ..\Libraries\Libraries.sln
    call :Build ..\Services\Services.sln
    call :Build ..\Drivers\Drivers.sln
    call :Build ..\Tools\Tools.sln
    goto :eof

    
    :Build
    echo %1...
    devenv "%1" /Rebuild Release
    exit /b %errorlevel%

Note que meu script usa a [estrutura padronizada dos diretórios de um projeto](http://www.caloni.com.br/projeto-modelo), onde cada tipo de componente tem sua pasta e solução.

Aos poucos você pode ir colocando "frescurinhas" em seu build (executa Debug e Release, roda automatizado no servidor, faz testes unitários, incrementa o número da versão, ...), mas algumas premissas sempre se mantêm:

	
  * Deve ser possível compilar o projeto inteiro em um passo

	
  * Deve ser possível usar qualquer máquina de desenvolvimento para isso

Regras simples de ser seguidas se você usar sempre a máxima do [KISS](http://en.wikipedia.org/wiki/KISS_principle).
