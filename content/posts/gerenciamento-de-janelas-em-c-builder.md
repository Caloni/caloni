---
date: "2007-12-11"
tags: [ "code", "draft",  ]
title: "Gerenciamento de janelas em C++ Builder"
---
As janelas criadas no C++ Builder são equivalentes às janelas criadas pela API, com o detalhe que a VCL gerencia tudo automaticamente. Isso não quer dizer que não podemos tomar controle de tudo. Quer dizer que não precisamos.

Abra o Builder. Um projeto padrão é criado. Agora no menu File, vá em New, Form. Isso adicionará um novo formulário ao projeto padrão. Pronto! Temos dois formulários. Agora se formos dar uma passeada no WinMain, vemos que o código para iniciar a VCL se alterou conforme a música:


Porém, se rodarmos a aplicação nesse momento, podemos notar que o programa exibe apenas a janela correspondente ao primeiro formulário. De fato, ao chamar o método Application->Run(), apenas o primeiro form criado é exibido. Isso não significa, é claro, que o segundo form não tenha sido criado. Para demonstrar como ele está lá, coloque o seguinte evento no clique de um botão do Form1:


Agora ao clicar do botão a janela correspondente ao formulário número 2 também aparece. Podemos fechá-la e abri-la quantas vezes quisermos que o aplicativo continua rodando. Apenas ao fechar a janela no. 1 o aplicativo realmente encerra. Esse comportamento segue o mesmo padrão da função main() na forma clássica das linguagens C/C++:


Podemos, também como em C/C++ padrão, finalizar explicitamente a aplicação chamando o método Application->Terminate. O MainForm em tempo de execução é uma propriedade de somente leitura de Application. Em tempo de design, ele pode ser alterado pela ordem de criação dos formulários no código ou pela IDE em Project, Options, Forms. Lá você também escolhe quais forms serão criados automaticamente.

Esse funcionamento e automação na criação de janelas da VCL foi feita para facilitar a vida do programador. Contudo, nunca estamos presos a somente isso. As maneiras das coisas funcionarem apenas refletem o uso mais comum no ambiente e não tem como função limitar a criatividade do desenvolvedor.

Para exemplificar, vamos inverter as coisas. Coloque um botão no segundo formulário que finalize o programa de maneira explítica:


Agora, no evento de OnClose (acho que você conhece o Object Inspector, não? Bom, se não conhece, talvez isso mereça um artigo à parte) do TForm1 insira o seguinte código:


Pronto! Agora você decide onde termina e onde acaba sua aplicação.

Se dermos uma olhada bem de perto no que acontece por dentro de um aplicativo que usa a VCL descobriremos que o método Run de Application nada mais é que o loop de mensagens que já conhecemos.

Para analisarmos melhor o que ocorre nos internals da coisa, criei um projeto simplista que possui dois forms, ambos com quatro botões: 1) mostrar o outro form, 2) esconder a si mesmo, 3) fechar a si mesmo e 4) terminar aplicação. Os dois formulários são tão parecidos que desconfio que sejam gêmeos.

Além disso, iremos precisar do nosso velho e fiel amigo WinDbg, o que o trás de volta à cena do crime depois de alguns artigos de jejum.

> 
> #### Não fique de fora!
> 
Para saber mais sobre o WinDbg e dar suas "WinDbgzadas", dê uma olhada em alguns artigos interessantes sobre depuração usando WinDbg.

A primeira coisa que um loop de mensagens deveria fazer seria chamar a função GetMessage, que obtém a primeira mensagem em espera na fila de mensagens da thread chamadora. Portanto, vamos dar uma olhada nas chamadas dessa função:


E o resultado é... nada! Mesmo mexendo com a janela e apertando seus botões não há uma única ocorrência do GetMessage. Bruxaria? Programação oculta?

Nem tanto. Uma alternativa ao GetMessage, que captura a primeira mensagem da fila de mensagens e a retira, é o PeekMessage, que captura a primeira mensagem da fila, mas mantém a mensagem na fila. Por algum motivo, os programadores da Borland fizeram seu loop de mensagens usando PeekMessage.



Agora, sim!

Analisando os parâmetros da função PeekMessage podemos obter algumas informações interessantes sobre uma mensagem, como seu código e a janela destino:


Podemos bater essas informações com as do aplicativo Spy++, que captura janelas e suas mensagens:


Normalmente esses dois rodando juntos podem causar alguns conflitos internos. Por isso, quando for usar o Spy++, procure desabilitar seus breakpoints. Após mexer no Spy++, feche-o antes de continuar depurando.

Como podemos ver, nesse caso a janela encontrada foi justamente a que não aparece: TApplication! Sim, a classe principal da VCL é representada em runtime por uma janela escondida, que controla algumas mensagens específicas da aplicação.

Tem tudo a ver! Mais do que simplesmente programar interfaces, esses conhecimentos permitem fazer a análise de qualquer aplicativo que possua um loop de mensagens. O importante descoberto aqui é que o C++ Builder, assim como o .NET, o Java e o "próximo framework gerenciado", não pode escapar da fatal realidade de que, para exibir janelas, o aplicativo deverá dançar a música da API Win32.


