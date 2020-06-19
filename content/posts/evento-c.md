---
categories: [ "code" ]
date: "2010-08-16"
tags: [ "draft",  ]
title: "Evento C++"
---
Esse fim-de-semana houve o tão falado evento C++, com a presença de dezenas de pessoas, algo que eu sinceramente não esperava. O bom desse evento foi saber que existem tantas pessoas interessadas em manter contato com quem gosta e pratica essa linguagem e também em saber que o nível técnico das palestras estão de alto para avançado.

Infelizmente em nenhuma das duas palestras práticas (minha e do Fernando) houve participação interativa, e ninguém que eu saiba abriu meu pacote-surpresa com os dumps a serem analisados. De qualquer forma, minha palestra ficou bagunçada pelo excesso de conteúdo e falta de tempo, o que me fez dar boas risadas ao ouvir no twitter que minha palestra foi mais um brainstorm. A intenção não era essa, claro, mas meu claro despreparo para muito conteúdo gerou essa impressão. Espero que do pouco que consegui explicar alguém tenha achado utilidade.

E, pelo jeito, futuramente irei aplicar essa mesma metodologia brainstorm em um videocast, que ainda não decidi como irei preparar. A ideia é analisarmos alguns dumps em conjunto e, para os que acompanharem online, a interatividade de perguntas & respostas.

Mas enquanto isso não acontece vamos dar uma olhada no que tínhamos no pacote-surpresa.


Como foi visto na palestra, uma pilha nesse estado demonstra claramente alguma variável que estourou e corrompeu o resto da pilha de chamadas. Na hora de voltar para a função chamadora, o endereço usado foi o endereço reescrito por lixo, e daí temos o "crash-pattern" Stack Trash.


A thread ativa no momento do dump aguardava por outra thread. Listando todas as threads do processo temos a primeira e a segunda, que tenta entrar em um critical section. Quando vemos que aquele CS estava sendo bloqueado pela primeira thread vemos claramente se tratar de um dead lock.


O disassemble da instrução inválida tenta escrever claramente em cima do endereço zerado (edx + eax). Dessa forma fica fácil saber que esse tipo de escrita não é permitido, constituindo nosso famosíssimo AV.


Esse foi meio de brinde. Uma exceção de breakpoint (int 3, ntdll!DbgBreakPoint) lançada sem um depurador atachado implica em derrubamento do processo, pois é uma exceção como outra qualquer. O programador deve ter esquecido um DebugBreak ou algo que o valha no código de produção, que acabou sendo executado.

Essa foi a DLL encontrada no cliente quando ocorreu o problema relatado na imagem, também em anexo. Isso foi demonstrado na palestra com a ajuda do meu script que carrega DLLs, além de um pouco de sorte. Podemos analisar esse caso com mais calma em outro artigo. Acho que já falei demais por aqui.
