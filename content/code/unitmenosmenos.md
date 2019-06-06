---
date: "2016-09-05"
title: "unit-menos-menos"
categories: [ "code" ]
---
Fazer o setup inicial de testes unitários em seu projeto C++ pode ser algo enfadonho se você precisa baixar e compilar uma lib do Google ou do Boost. Há uma alternativa mais leve e bem direta, que um dia apareceu nesses CodeProject da vida, mas que hoje está, até onde eu vi, no [GitHub](https://github.com/gcross/unit--).

E como se faz para começar a montar os testes unitários? Bom, suponha que você tenha um projeto qualque que já compila, roda e faz alguma coisa de útil:

![](http://i.imgur.com/HjYVkyp.png)

Apenas crie um projeto do lado, console, ou copie e cole o projeto, mas use os arquivos-fonte do projeto original. Dessa forma ele irá compilar com os fontes que estão sendo modificados/compilados.

![](http://i.imgur.com/NT2C1SC.png)

Apenas se lembra de não incluir o módulo que contém o int main. Esse módulo deve ficar apartado do projeto principal.

Depois basta incluir apenas um arquivo do projeto unit--, que é seu cpp principal.

![](http://i.imgur.com/P8bEvns.png)

Com isso existirá um main lá dentro, definido em algum lugar. E tudo o que você precisa fazer é ir criando seus testes em outro arquivo fonte gerado para isso. O corpo e o formato dos unit cases é bem simples. Note que tudo que você fez para já sair testando seu projeto foi copiar um projeto já existente e inserir um módulo de outro projeto. Tudo compilando junto e já podemos fazer os primeiros testes do programa original (desde, claro, que ele seja testável, algo primordial):

```
// Precisamos definir uma suíte de testes.
testSuite(DayToDayTests)

// Se eu digito uma linha, ela deve estar no arquivo daytoday.txt.
testCase(GetUmaLinha, DayToDayTests)
{
    //...
    bool lineOk = TestAlgumaCoisa();
    assertTrue(lineOk);
}

// Se eu digito duas linhas, ambas devem estar no arquivo daytoday.txt.
testCase(GeraDuasLinhas, DayToDayTests)
{
    //...
    bool lineOk = TestOutraCoisa();
    assertTrue(lineOk);
}
```

E assim por diante. O resultado é que quando você roda o executável de teste, ele execute toda a bateria e já te entregue todos os casos que você deseja testar, sem frescura:

```
......
OK
Total 6 test cases
0 sec.
Press any key to continue . . .
```

E voilà! Sistema de teste unitário pronto e rodando. Agora cada nova situação de erro ou que você precise validar, basta escrever um novo teste. Se esse projeto ir se tornando algo muito maior, a transição para testes unitários mais parrudos é apenas um regex. No momento, foque em codificar e testar muito bem o que está fazendo.
