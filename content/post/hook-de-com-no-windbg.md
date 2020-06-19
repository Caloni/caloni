---
categories: [ "code" ]
date: "2007-09-18"
tags: [ "draft",  ]
title: "Hook de COM no WinDbg"
---
Continuando com o tema hooks no WinDbg, vamos aqui "hookear" e analisar as chamadas de métodos de um objeto COM. O que será feito aqui é o mesmo experimento feito para uma palestra de engenharia reversa que apresentei há um tempo atrás [1], mas com as opções de pause, rewind, replay e câmera lenta habilitadas.

Antes de começar, se você não sabe nada sobre COM, não deveria estar aqui, mas aqui, aqui e aqui.

Pra começar, vamos dar uma olhada na representação da interface IUnknown em UML e em memória:

Como podemos ver, para implementar o polimorfismo, os endereços das funções virtuais de uma classe são colocados em uma tabela, a chamada vtable, famosa tanto no COM quanto no C++. Existe uma tabela para cada classe-base polimórfica, e não para cada objeto. Se fosse para cada objeto não faria sentido deixar esses endereços "do lado de fora" do leiaute. E não seria nada simples e elegante fazer uma cópia desse objeto.

Assim, quando você chama uma função virtual de um objeto, o código em assembly irá chamar o endereço que estiver na posição correspondente ao método chamado dentro da vtable. Se você chama AddRef, por exemplo, que é o segundo método na tabela, será chamado o endereço da posição número dois. Com isso, mesmo desconhecendo de que tipo é o objeto a função certa será chamada, porque existe um ponteiro para essa tabela no início da interface.

Sabendo de tudo isso, agora sabemos como teoricamente proceder para colocar uns breakpoints nessas chamadas:

Note que o breakpoint não é colocado dentro da tabela, o que seria absurdo. Uma tabela são dados e dados geralmente não são executados (eu disse geralmente). Porém, usamos a tabela para saber onde está o começo da função para daí colocar a parada nesse endereço, que por fazer parte do código da função é (quem diria!) executado.

Agora vamos sair da teoria e tentar fazer as coisas mais ou menos parecidas na prática.

O nosso sorteado desse artigo foi o IMalloc, a interface de alocação de memória do COM, que existe desde a época em que não se sabia direito pra que esse tal de COM iria servir. O IMalloc é definido como se segue:


Nesse experimento, como iremos interceptar quando alguém aloca ou desaloca memória, nossos alvos são os métodos Alloc e Free. Para saber onde eles estão na tabela, é só contar, começando pelos métodos do IUnknown, que é de quem o IMalloc deriva. Se houvessem mais derivações teríamos que contar da primeira interface até a última. Portanto: QueryInterface um, AddRef dois, Release três, Alloc quatro, Realloc cinco, Free seis. OK. Contar foi a parte mais fácil.

Agora iremos precisar interceptar primeiro a função que irá retornar essa interface, pois do contrário não saberemos onde fica a vtable. Nesse caso, a função é a ole32!CoGetMalloc. Muitas vezes você irá usar a ole32!CoCreateInstance(Ex) ou a CoGetClassObject diretamente na DLL que pretende interceptar. Outras vezes, você receberá o ponteiro em alguma ocasião diversa. O importante é conseguir o ponteiro de alguma forma.

Nesse exemplo iremos obter o ponteiro através de um aplicativo de teste trivial, ignorando todas aquelas proteções antidebugging que podem estar presentes no momento da reversa, feitos por alguém que lê meu blog (quanta pretensão!):


Vamos fazer de conta que é desnecessário dizer como se compila o fonte acima.


WinDbg. Na opção "File, Open Executable" selecionamos a nossa vítima, cujo nome você escolhe na hora de compilar o fonte acima. Aqui, ele irá chamar imalloc-hook.exe. A seguir, colocamos um breakpoint na função da ole32, mandamos rodar, e esperamos a parada do código:


Maravilha. Alguém chamou a função que queríamos (quem será?). Agora podemos dar uma olhada na pilha e no protótipo da CoGetMalloc:


Como podemos ver nos parâmetros da pilha, o nosso chamador passou certinho o valor 1 no campo reservado e um ponteiro no segundo parâmetro para uma área onde, se der tudo certo, será escrito o endereço de um IMalloc, que podemos chamar carinhosamente de this. De início vemos que a variável está zerada. Agora vamos executar a função até a saída e examinar os resultados.


E não é que tudo deu certo? A variável foi preenchida, e partir dela demos uma espiadela nos endereços das funções da vtable. Nós pegamos o valor da variável que foi preenchida (o endereço da interface) e obtemos os seus primeiros 4 bytes (o endereço da vtable) e listamos o seu conteúdo (a própria vtable!). Agora basta usarmos o resultados de nossas contagens lá em cima e colocarmos os breakpoints nas funções corretas. E mandar rodar. E analisar os resultados.


Note que a função pode eventualmente ser chamada internamente (pelo próprio objeto) ou até por outro objeto que não estamos interessados em interceptar (lembre-se que os métodos de uma classe são compartilhados por todos os objetos). Por isso é importante sempre dar uma olhada no primeiro parâmetro, que é o this que obtemos primeiramente.

Com isso termina o nosso pequeno experimento de como é possível interceptar chamadas COM simplesmente contando e usando o WinDbg. OK, talvez um pouquinho a mais, mas nada de quebrar a cabeça.

Para saber mais: Engenharia Reversa para Principiantes.
