---
categories:
- code
date: '2016-06-04'
tags:
- draft
title: 'Palestra: Stack Overflow'
---

Há umas semanas (sim, estava enrolado para falar sobre isso) ministrei uma nova palestra lá em Sorocaba. Cheguei no meio de uma greve de ônibus, o que atrasou o evento em uma hora e me deu tempo de sobre para pensar nas desgraças que serão cidades próximas da capital crescendo desordenadamente graças às regulações estatais.

Mas divago.

A ideia da palestra foi do meu amigo Alan Silva (a.k.a. jumpi), e era para a SEMANA DA COMPUTAÇÃO E TECNOLOGIA -- mas nada tem a ver com computação, nem tecnologia, mas com oportunidade de emprego de estagiários para empresas corporativistas da área. O foco era sair da mesmisse que os representantes de R.H. fazem em falar de cultura, visão, valores e outras besteiras e falar um pouco mais de bits e bytes, algo que falta a essa geração.

Meu público era muito, muito jovem, e foquei erroneamente em conceitos muito, muito antigos para eles, então não tenho muita certeza se fui útil. De qualquer forma, foi um prazer falar sobre engenharia da computação atrelado a ataque na pilha de execução (sim, um salto enorme para baixo, do R.H. para a placa de memória RAM).

O conteúdo e a palestra está no GitHub e a palestra em si pode ser vista logo abaixo; a apresentação do conteúdo está mais abaixo, e peço desculpas por não ter tido tempo de apresentar todo ele (mesmo com quase duas horas):

http://www.slideshare.net/slideshow/embedcode/key/qRb4TSKjnf8Wx

PS: Ah, esqueci. Também fiz um vídeo para complementar o conteúdo da palestra. Segue:

https://www.youtube.com/embed/kSKQQDTBRXQ?list=PLa0QVTprDkHBz6fjuzy4kU1iTLUnRWkeW

Um StackOverflow é definido pela escrita em uma região não autorizada de memória. Stack overflow, overrun, etc, não interessando a nomenclatura "oficial", o importante aqui é como um bug de acesso à memória pode permitir acesso exclusivo a regiões de memória que não estariam disponíveis para um atacante se não fosse por esse bug.

No exemplo do código deste projeto, um usuário fictício utiliza um código que possui controle de acesso, mas também possui um bug: ele escreve em uma região da memória inadvertidamente. Dessa forma, é possível explorar essa falha no código para escrever um novo endereço de retorno na pilha (stack), ganhando acesso, dessa forma, a código que não estaria disponível em situações normais de temperatura e pressão.

Para explorar esse tipo de falha, primeiro devemos entender a execução do código na arquitetura que se pretende atacar, além de alguns conceitos específicos do sistema operacional alvo.

 - UML: Mundo real aplicado a engenharia.
 - Programação: Codificação do mundo real.
 - Assembly: Ponte entre ser humano e máquina.
 - 1's e 0's: Codificação lógica do computador.
 - Impulsos elétricos: Voltamos para o mundo real.
 - Qubit: Voltamos para a Matrix.
 - ("IBM disponibiliza computador quântico para público")

 - Mais abstrações: Memória Virtual, Threads, I/O.

 - Movimentação de memória (mov, lea)
 - Cálculos matemáticos (add, div)
 - Meta-comandos (push, pop, ret, jmp)

 - Registradores (e[abcd]x, [bs]sp, eip)
 - Endereço Virtual ([Kernel|User] Space)
 - Endereço Físico (RAM, ROM, Storage, placas)

 - Qual o sentido de apontar para a próxima instrução?
 - R: Saber onde continuar a execução.
 - Demo: Chamada de função.
 - Demo: Retorno de função.

 - Qual o sentido de existir uma stack?
 - R: Conseguir chamar funções.
 - Demo: Chamada de função.
 - Demo: Passagem de argumentos.
 - Demo: Retorno de função.

 - Escalonamento de threads
 - Virtualização da memória
 - Controle de acesso
 - Paginação
 - Plug and Play
 - Windows NT
 - Dave Cutler
 - xBox One
 - Hypervisor

 - Thread: Uma ilusão satisfatória.
 - Fibers, Co-Routines, Cores, Pipe Line, Branch Prediction.
 - Computação Quântica: Hackeando o Universo.

 - Python, F#, Lambdas C++11, Métodos, Função Virtual.
 - Bloco de memória chama... Outro bloco de memória 

 - [[[C]]]]decl e Std(?)call (M$).
 - Demo: Função em C sendo chamada.
 - Demo: Função da Microsoft sendo chamada.
 - Ou: Porque o printf precisa ser cdecl.

 - Page Tables, PTEntries, Page Fault, Memory Map.
 - Demo: Process Explorer.

 - 2 bits: Quatro possibilidades.
 - Read-Only Memory, Execute Memory.

 - Ah, vamos para o BAR: Base Address Randomization.
 - Demo: Ver se isso funciona, mesmo.

 - ESP Verification.
 - Buffer overrun.
 - 0xCCCCCCCCCCCCCCCCCCCCC