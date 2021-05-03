---
categories:
- code
date: '2019-11-13'
title: DTLS Simples... simples?
---

O protocolo DTLS, grosso modo, é um addon do TLS, que é a versão mais nova e segura do SSL. Só que em vez de usar por baixo o TCP, que garante entrega na ordem certa dos pacotes, além de outras garantias, o UDP é permitido. Ou seja, datagramas. Em teoria essa forma de usar TLS é uma versão mais light, com menos overhead e menos tráfico de banda. E a pergunta que tento responder aqui é: será que isso é verdade?

A primeira tarefa é conseguir compilar e rodar um sample DTLS. Estou usando Windows como sistema operacional alvo (requisitos de projeto). Para criar um sample client/server de DTLS usando a biblioteca OpenSSL (no momento na versão 1.1.1d) precisei de alguns passos de setup, conforme especificados no [tutorial do próprio OpenSSL]. O repositório [DTLS-Examples], disponível no GitHub, possui alguns starts para começarmos a compilar e rodar um pouco de código, mas nem tudo são flores na hora de rodar para Windows.

O exemplo que peguei, [dtlsudpecho.c], como diz o nome, usa DTLS em cima de UDP. As funções de setup e de definição de callbacks e settings do OpenSSL são configuradas de acordo com o esperado, mas por algum motivo quando a conexão entre um server e um client é estabelecida o server dispara vários listenings e a conexão estabelecida pelo client permanece sem escrita e leitura.

Após compilar o OpenSSL e antes de iniciar os testes gerei os certificados, e analisando a troca de pacotes pelo Wire Shark descobri um erro no handshake envolvendo fragmentação. Tentando descobrir o motivo encontrei alguns issues no GitHub a respeito de problemas no OpenSSL, e a solução era definir um MTU (Maximum Transmission Unit) em vez de deixar o OpenSSL usar o default, que é pequeno demais para poder enviar as mensagens do handshake de uma só vez, requisito do protocolo.

Isso corrigiu o envio do ClientHello, mas após isso o handshake entrou em loop no envio do resto das mensagens até retornar com erro. Do roteiro descrito pela [RFC] faltam as mensagens Finished após ChangeCipherSpec, o que terminaria o fluxo, mas por algum motivo o Finished nunca chega em nenhum dos lados, e as mensagens a partir de ServerHello se repetem até o retorno de erro de conexão (SSLERRORSSL). O Sequence Number do server e client indicam que apesar da troca de mensagens estar ocorrendo existe um loop.

Encontrei um gist que acompanha passo a passo o setup necessário da biblioteca. Ao pesquisar mais a respeito encontrei um artigo de [Christopher A. Wood], que também está explorando esse protocolo usando OpenSSL e que é o autor do primeiro repositório de exemplo de DTLS, que falha não por não funcionar, mas por estar usando TCP em vez de UDP ao usar a flag SOCKSTREAM em vez de SOCKDGRAM na criação do socket.

Depois de muito analisar o protocolo desenhando cada pacote na janela do escritório resolvi abandonar essa miríade de detalhes e dar um passo atrás, usando o próprio openssl.exe compilado com os parâmetros abaixo. E, surpreso, mas nem tanto (afinal de contas, a compilação do OpenSSL passou pelos testes pós-build) eu consigo executar o protocolo DTLS em UDP IPV4 sem nenhuma falha.

O passo seguinte foi entender o código e as diferenças com os samples que havia tentado fazer funcionar da única maneira que penso ser possível: depurando. Sem conseguir navegar em todos os detalhes do fonte do OpenSSL recompilei o projeto com full debug alterando as flags de compilação no Makefile gerado para Windows (/Od e /Zi ajudam) e iniciei os dois modos acima depurando em duas instâncias do Visual Studio. Encontrei uma ou outra chamada à biblioteca OpenSSL que não havia notado ainda, mas nada que parece fazer a diferença.

Mas nenhuma dessas mudanças fez efeito no projeto de teste. O próximo passo seria copiar cada chamada feita à lib OpenSSL pelo openssl.exe e colar no projeto de teste para descobrir onde está o pulo do gato que nenhum dos samples na internet parece ter encontrado (ao menos para Windows), mas há uma solução preguiçosa que é muito mais efetiva e testada: usar os fontes da própria pasta apps do projeto OpenSSL.

O próximo e último passo é customizar o código-fonte base no qual a OpenSSL valida o protocolo DTLS para o uso que pretendo fazer para ele: um executador de processos remoto.

[Christopher A. Wood]: https://datatracker.ietf.org/person/Christopher%20A.%20Wood
[DTLS-Examples]: https://github.com/nplab/DTLS-Examples
[RFC]: https://tools.ietf.org/html/rfc6347
[dtlsudpecho.c]: https://github.com/nplab/DTLS-Examples/blob/master/src/dtls_udp_echo.c 
[tutorial do próprio OpenSSL]: https://wiki.openssl.org/index.php/Compilation_and_Installation#Windows