---
date: "2018-09-18"
tags: [ "code", "draft",  ]
title: "Coroutine Internals"
---
Uma corrotinas é um mecanismo de troca de contexto onde apenas uma thread está envolvida. Ela me faz lembrar do Windows 3.0, não exatamente por não existirem threads (e não existiam mesmo), mas pelo caráter cooperativo dos diferentes códigos.

Só que no caso do Windows se a rotina de impressão travasse todo o sistema congelava.

A volta das corrotinas via C++ moderno ocorre, para variar, no Boost. E a arquitetura é simples: mantenha um histórico das stacks das diferentes tasks da thread. Vamos pegar o caso mais simples da Boost.Coroutine para analisar:


Se você já é um programador esperto já deve ter percebido que na saída do prompt será impresso "Hello, world!", com a vírgula no meio sendo impressa pela função main e as duas palavras da ponta pela função cooperative, ainda que ela seja chamada apenas uma vez.

Note que falei chamada porque se a stack não retornou da função ela não terminou ainda seu trabalho. Não houve o "return". Outra forma de entender isso é que ela é chamada aos poucos. Enfim, deixo para você a discussão semântica. O fato é que a saída é "Hello, world".


Depurando encontramos a stack de cooperative, que nos indica que ela não partiu do main, apesar de ter sido chamada através da construção de coroutine pulltype. O método sink chamado logo após imprimir "Hello" deve colocar essa rotina para dormir, voltando o controle para main.

Analisando como isso é feito vemos que o depurador do Visual Studio está fazendo caquinha, pois rodando passo-a-passo voltei para a mesma função cooperative sem passar pelo main. No entanto, a vírgula ", " foi impressa.


Para conseguirmos depurar diferentes rotinas dentro da mesma thread é imperativo entendermos como o mecanismo de troca de contexto funciona por baixo dos panos. Para isso nada como depurar as próprias trocas de contexto.


O tamanho total da stack reservada no Windows é de 1 MB, mas a granuralidade padrão é de 64 KB ("que é suficiente para qualquer um" - Gates, Bill). Então é por isso que quando o Boost aloca uma stack com atributos padrões esse é o tamanho que vemos (65536).

> The default size for the reserved and initially committed stack memory is specified in the executable file header. Thread or fiber creation fails if there is not enough memory to reserve or commit the number of bytes requested. The default stack reservation size used by the linker is 1 MB. To specify a different default stack reservation size for all threads and fibers, use the STACKSIZE statement in the module definition (.def) file. The operating system rounds up the specified size to the nearest multiple of the system's allocation granularity (typically 64 KB). To retrieve the allocation granularity of the current system, use the GetSystemInfo function.



Detalhe curioso de arquitetura x86 (32 bits): na hora de alocar, o sp (stack pointer) aponta para o final da pilha. Isso porque no x86 a pilha cresce "para baixo".

Logo em seguida, no topo da pilha, é empilhado o objeto da corrotina:


Bom, entrando mais a fundo na implementação de corrotinas do Boost, temos o objeto pullcoroutineimpl, que possui flags, ponteiro para exceção e o contexto do chamador e do chamado para se localizar.


O coroutinecontext possui elementos já conhecidos de quem faz hook de função: trampolins. Ou seja, funções usadas para realizar saltos incondicionais de um ponto a outro do código independente de contexto. Na minha época de hooks isso se fazia alocando memória na heap e escrevendo o código assembly necessário para realizar o pulo, geralmente de uma colinha de uma função naked (funções naked não possuem prólogo e epílogo, que são partes do código que montam e desmontam contextos dentro da pilha, responsável pela montagem dos frames com ponto de retorno, variáveis locais, argumentos).


A função que faz a mágica do pulo do gato é a pull, que muda o estado da rotina para running e realiza o salto de contexto. Vamos analisar essa parte com muita calma.


Quem desfaz a mágica, "desempilhando" o contexto para voltar ao chamador da corrotina (através do contexto apenas, não da pilha) é a função push.


Com os dados disponíveis nos objetos de contexto (no exemplo do main, a variável source) é possível pelo Windbg analisar qualquer tipo de stack com o comando k.

A variável de uma coroutine contém o contexto do chamador e do chamado. Quando houver a necessidade de explorar uma pilha não-ativa é preciso obter o valor de sp através dessa variável. Ela fica um pouco escondida, mas está lá. Acredite.

Usando o comando k = BasePtr StackPtr InstructionPtr passando o conteúdo de sp como o stack pointer o Windbg deve mostrar a pilha de todas as formas possíveis (especificar se terá FPO, mostrar código-fonte, argumentos, etc). Para a demonstração live fica bom ter um loop "eterno" para poder repetir a análise quantas vezes forem necessárias:



DICA: É importante detachar do processo, mesmo que estejamos analisando em modo não-invasivo, porque a porta de Debug pode ser ocupada e o Visual Studio vai ficar pra sempre esperando receber eventos de debug que ele não vai mais receber.

Após rodarmos novamente o programa ele pára no main. Podemos atachar com o WinDbg quantas vezes precisarmos:

