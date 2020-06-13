---
categories: [ "code" ]
date: "2019-11-13"
tags: [ "draft",  ]
title: "DTLS Simples... simples?"
---

O protocolo DTLS, grosso modo, é um addon do TLS, que é a versão mais nova e segura do SSL, só que em vez de usar por baixo o TCP, que garante entrega na ordem certa dos pacotes, além de outras garantias, o UDP é permitido. Ou seja, datagramas. Em teoria essa forma de usar TLS é uma versão mais light, com menos overheadh e tráfico de banda. E a pergunta que tento responder aqui é: será que isso é verdade?

A primeira tarefa é conseguir compilar e rodar um sample DTLS para Windows, que é meu sistema operacional alvo. Para criar um sample client/server de DTLS usando a biblioteca OpenSSL (no momento 1.1.1d) precisei de alguns passos de setup, conforme especificado neste tutorial. O repositório DTLS-Examples possui alguns starts para começarmos a compilar e rodar um pouco de código, mas nem tudo são flores na hora de rodar para Windows.

O exemplo que peguei, dtlsudpecho.c, como diz o nome, usa DTLS em cima de UDP. As funções de setup e de definição de callbacks e settings do OpenSSL são configuradas de acordo com o esperado, mas por algum motivo quando a conexão entre um server e um client é estabelecida o server dispara vários listenings e a conexão estabelecida pelo client permanece sem escrita e leitura.

Após compilar o OpenSSL e antes de iniciar os testes gerei os certificados:

    openssl req -x509 -newkey rsa:2048 -days 3650 -nodes -keyout client-key.pem -out client-cert.pem
    openssl req -x509 -newkey rsa:2048 -days 3650 -nodes -keyout server-key.pem -out server-cert.pem

Analisando a troca de pacotes pelo Wire Shark descobri um erro no handshake envolvendo fragmentação.

    No. Time Source Destination Protocol Length Info
     10 2019-10-14 12:31:35.476498 127.0.0.1 127.0.0.1 DTLSv1.0 243 Client Hello
     11 2019-10-14 12:31:35.476652 127.0.0.1 127.0.0.1 DTLSv1.0 80 Hello Verify Request
     12 2019-10-14 12:31:35.476756 127.0.0.1 127.0.0.1 DTLSv1.0 260 Client Hello (Fragment)
     13 2019-10-14 12:31:35.476793 127.0.0.1 127.0.0.1 DTLSv1.0 60 Client Hello (Reassembled)
     14 2019-10-14 12:31:36.476196 127.0.0.1 127.0.0.1 DTLSv1.0 260 Client Hello[Reassembly error,
     15 2019-10-14 12:31:36.476249 127.0.0.1 127.0.0.1 DTLSv1.0 60 Client Hello[Reassembly error,
     16 2019-10-14 12:31:38.476407 127.0.0.1 127.0.0.1 DTLSv1.0 260 Client Hello[Reassembly error,
     17 2019-10-14 12:31:38.476541 127.0.0.1 127.0.0.1 DTLSv1.0 60 Client Hello[Reassembly error,
     19 2019-10-14 12:31:42.476444 127.0.0.1 127.0.0.1 DTLSv1.0 260 Client Hello[Reassembly error,
    ...

Tentando descobrir o motivo encontrei alguns issues no GitHub a respeito de problemas no OpenSSL, e a solução era definir um MTU (Maximum transmission unit) em vez de deixar o OpenSSL usar o default, que é pequeno demais para poder enviar as mensagens do handshake de uma só vez, requisito do protocolo.

    SSL_CTX_set_options(ctx, SSL_OP_NO_QUERY_MTU); // IMPORTANT: before SSL_new
    ssl = SSL_new(ctx);
    
    SSL_set_mtu(ssl, 1500);
    BIO_ctrl(bio, BIO_CTRL_DGRAM_SET_MTU, 1500, NULL);

Isso corrigiu o envio do ClientHello, mas após isso o handshake entrou em loop no envio do resto das mensagens até retornar com erro.

    No. Time Source Destination Protocol Length Info
    
     11780 2019-10-14 16:49:21.672786 127.0.0.1 127.0.0.1 DTLSv1.2 118 Server Hello
     11781 2019-10-14 16:49:21.672890 127.0.0.1 127.0.0.1 DTLSv1.2 1016 Certificate
     11782 2019-10-14 16:49:21.672941 127.0.0.1 127.0.0.1 DTLSv1.2 353 Server Key Exchange
     11783 2019-10-14 16:49:21.672985 127.0.0.1 127.0.0.1 DTLSv1.2 1016 Certificate
     11784 2019-10-14 16:49:21.673035 127.0.0.1 127.0.0.1 DTLSv1.2 111 Certificate Request
     11785 2019-10-14 16:49:21.673053 127.0.0.1 127.0.0.1 DTLSv1.2 57 Server Hello Done
     11786 2019-10-14 16:49:21.673114 127.0.0.1 127.0.0.1 DTLSv1.2 90 Client Key Exchange
     11787 2019-10-14 16:49:21.673161 127.0.0.1 127.0.0.1 DTLSv1.2 317 Certificate Verify
     11788 2019-10-14 16:49:21.673207 127.0.0.1 127.0.0.1 DTLSv1.2 46 Change Cipher Spec
     11789 2019-10-14 16:49:21.673263 127.0.0.1 127.0.0.1 DTLSv1.2 93 Encrypted Handshake Message
     11804 2019-10-14 16:50:21.673036 127.0.0.1 127.0.0.1 DTLSv1.2 1016 Certificate
    
     11805 2019-10-14 16:50:21.673121 127.0.0.1 127.0.0.1 DTLSv1.2 118 Server Hello
     11806 2019-10-14 16:50:21.673158 127.0.0.1 127.0.0.1 DTLSv1.2 1016 Certificate
     11807 2019-10-14 16:50:21.673199 127.0.0.1 127.0.0.1 DTLSv1.2 353 Server Key Exchange
     11808 2019-10-14 16:50:21.673229 127.0.0.1 127.0.0.1 DTLSv1.2 111 Certificate Request
     so on...

Do roteiro descrito pela RFC faltam as mensagens Finished após ChangeCipherSpec, o que terminaria o fluxo, mas por algum motivo o Finished nunca chega em nenhum dos lados, e as mensagens a partir de ServerHello se repetem até o retorno de erro de conexão (SSLERRORSSL). O Sequence Number do server e client indicam que apesar da troca de mensagens estar ocorrendo existe um loop.

Encontrei um gist que acompanha passo a passo o setup necessário da biblioteca. Ao pesquisar mais a respeito encontrei um artigo de Christopher A. Wood que também está explorando esse protocolo usando OpenSSL e que é o autor do primeiro repositório de exemplo de DTLS, que falha não por não funcionar, mas por estar usando TCP em vez de UDP ao usar a flag SOCKSTREAM em vez de SOCKDGRAM na criação do socket.

Depois de muito analisar o protocolo desenhando cada pacote na janela do escritório resolvi abandonar essa miríade de detalhes e dar um passo atrás, usando o próprio openssl.exe compilado com os parâmetros abaixo. E, surpreso, mas nem tanto (afinal de contas, a compilação do OpenSSL passou pelos testes pós-build) eu consigo executar o protocolo DTLS em UDP IPV4 sem nenhuma falha:

    c:\Projects\Project1>openssl
    OpenSSL> s_server -4 -dtls -cert certs/server-cert.pem -key certs/server-key.pem
    Using default temp DH parameters
    ACCEPT
    -----BEGIN SSL SESSION PARAMETERS-----
    MFsCAQECAwD+/QQCwDAEAAQwb1UxP7ZeFQKcICmi1dDeS2k51i0yUa2uOkJYDgtu
    ap/goWNPAYkdc3P8ADlBW3xToQYCBF3JwWaiBAICHCCkBgQEAQAAAK0DAgEB
    -----END SSL SESSION PARAMETERS-----
    Shared ciphers:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:DHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:DHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:DHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-SHA384:ECDHE-RSA-AES256-SHA384:DHE-RSA-AES256-SHA256:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA256:DHE-RSA-AES128-SHA256:ECDHE-ECDSA-AES256-SHA:ECDHE-RSA-AES256-SHA:DHE-RSA-AES256-SHA:ECDHE-ECDSA-AES128-SHA:ECDHE-RSA-AES128-SHA
    Signature Algorithms: ECDSA+SHA256:ECDSA+SHA384:ECDSA+SHA512:Ed25519:Ed448:RSA-PSS+SHA256:RSA-PSS+SHA384:RSA-PSS+SHA512:RSA-PSS+SHA256:RSA-PSS+SHA384:RSA-PSS+SHA512:RSA+SHA256:RSA+SHA384:RSA+SHA512:ECDSA+SHA224:ECDSA+SHA1:RSA+SHA224:RSA+SHA1:DSA+SHA224:DSA+SHA1:DSA+SHA256:DSA+SHA384:DSA+SHA512
    Shared Signature Algorithms: ECDSA+SHA256:ECDSA+SHA384:ECDSA+SHA512:Ed25519:Ed448:RSA-PSS+SHA256:RSA-PSS+SHA384:RSA-PSS+SHA512:RSA-PSS+SHA256:RSA-PSS+SHA384:RSA-PSS+SHA512:RSA+SHA256:RSA+SHA384:RSA+SHA512:ECDSA+SHA224:ECDSA+SHA1:RSA+SHA224:RSA+SHA1:DSA+SHA224:DSA+SHA1:DSA+SHA256:DSA+SHA384:DSA+SHA512
    Supported Elliptic Curve Point Formats: uncompressed:ansiX962_compressed_prime:ansiX962_compressed_char2
    Supported Elliptic Groups: X25519:P-256:X448:P-521:P-384
    Shared Elliptic groups: X25519:P-256:X448:P-521:P-384
    ---
    No server certificate CA names sent
    CIPHER is ECDHE-RSA-AES256-GCM-SHA384
    Secure Renegotiation IS supported
    a
    b
    c

    OpenSSL> s_client -4 -dtls
    CONNECTED(00000124)
    depth=0 C = AU, ST = Some-State, O = Internet Widgits Pty Ltd
    verify error:num=18:self signed certificate
    verify return:1
    depth=0 C = AU, ST = Some-State, O = Internet Widgits Pty Ltd
    verify return:1
    ---
    Certificate chain
     0 s:C = AU, ST = Some-State, O = Internet Widgits Pty Ltd
       i:C = AU, ST = Some-State, O = Internet Widgits Pty Ltd
    ---
    Server certificate
    -----BEGIN CERTIFICATE-----
    MIIDazCCAlOgAwIBAgIUYOjmm3NHvT8FQAz/4wvbfv6ykKswDQYJKoZIhvcNAQEL
    BQAwRTELMAkGA1UEBhMCQVUxEzARBgNVBAgMClNvbWUtU3RhdGUxITAfBgNVBAoM
    GEludGVybmV0IFdpZGdpdHMgUHR5IEx0ZDAeFw0xOTEwMjgxNDU2MDdaFw0yOTEw
    MjUxNDU2MDdaMEUxCzAJBgNVBAYTAkFVMRMwEQYDVQQIDApTb21lLVN0YXRlMSEw
    HwYDVQQKDBhJbnRlcm5ldCBXaWRnaXRzIFB0eSBMdGQwggEiMA0GCSqGSIb3DQEB
    AQUAA4IBDwAwggEKAoIBAQCt2SElEZkqsoZAE3f+UBCgq/rwskTOVMD79g3AG23b
    HLX4ClXXu2ahoQMA38GpnwotEMUsltrWeItABpGkQL6oPVBvEJDi8mzS4trzI5Cg
    qHMsIfq63x4HtdJI2Zs30ichCWkSj3qXNSlbe1uuNC8/oRWkfCGQC/8XfdCfTAnq
    DZAVRnWVfVRJu78VokzSB+Rmj+UODzGFdZiVdDFRuDw7ZR6a30UYOpi3uwOAIwcI
    PwbyZg/frqtvSjME63ZhV50jVZOxvABq7mG9S6jhHhKBVgbwwBorTGbv5RURFB8c
    bEiIAg6VQrhsTEYi7M2neRhYjN19h19yz0ejP1NpazCFAgMBAAGjUzBRMB0GA1Ud
    DgQWBBS0NNpwAZpmVcalqQnHXW5L26NDhzAfBgNVHSMEGDAWgBS0NNpwAZpmVcal
    qQnHXW5L26NDhzAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQCQ
    qah3mYWeJIeSn1z6eFk8/mbPZIEb/0XaJOe3jcjXpelJ3AjBn4r/bLtA3etIfGL9
    WO7F8d3zPxTjxMYUFp7iw7Sr46t5b24aaVftRf+mhq3YNcIh/W13e3LUH3WiVYrB
    GWI8vJYDXkj8H3l4vO4lsEp6Isaz8wWQu4Cn/9GNfWURkrxO0vJGqUghPiWzc7eh
    uzRRAsOazupAGaPMxUsbYmG0bnFT73ZzVbPSgEW0/WjXPHy8WScMtns905nLbUVY
    r4UfKT+FORmrewj+BWQ0UB0ZEkRtV2YW1t8G/cBKXkpN/GKmYkp/y4+xp938lRIX
    T+onWnAAo2kiqHxrLGOB
    -----END CERTIFICATE-----
    subject=C = AU, ST = Some-State, O = Internet Widgits Pty Ltd
    
    issuer=C = AU, ST = Some-State, O = Internet Widgits Pty Ltd
    
    ---
    No client certificate CA names sent
    Peer signing digest: SHA256
    Peer signature type: RSA-PSS
    Server Temp Key: X25519, 253 bits
    ---
    SSL handshake has read 1806 bytes and written 661 bytes
    Verification error: self signed certificate
    ---
    New, TLSv1.2, Cipher is ECDHE-RSA-AES256-GCM-SHA384
    Server public key is 2048 bit
    Secure Renegotiation IS supported
    Compression: NONE
    Expansion: NONE
    No ALPN negotiated
    SSL-Session:
        Protocol  : DTLSv1.2
        Cipher    : ECDHE-RSA-AES256-GCM-SHA384
        Session-ID: 1D5361970DA157A70164F826FEFB7CE08B9A36A4DB0A831DE0801958ECF7D026
        Session-ID-ctx:
        Master-Key: 6F55313FB65E15029C2029A2D5D0DE4B6939D62D3251ADAE3A42580E0B6E6A9FE0A1634F01891D7373FC0039415B7C53
        PSK identity: None
        PSK identity hint: None
        SRP username: None
        TLS session ticket lifetime hint: 7200 (seconds)
        TLS session ticket:
        0000 - 40 c9 90 ed 5c ec 1c 9d-7f cc 69 2c 92 f1 13 c6   @...\.....i,....
        0010 - c2 68 a5 66 d3 e0 69 e2-96 7b 5c b9 7e b9 fa a9   .h.f..i..{\.~...
        0020 - 52 59 a8 58 b3 37 ca f7-22 42 66 a0 8a d9 71 f2   RY.X.7.."Bf...q.
        0030 - ec e0 dd 9c 2e c2 01 8a-14 d9 65 48 a2 70 e4 cd   ..........eH.p..
        0040 - 1a b7 56 54 af 32 08 46-9e 7e 60 64 3e 07 3e 51   ..VT.2.F.~`d>.>Q
        0050 - 92 82 c1 a3 36 a1 6e f8-bf 45 12 f9 f0 af 70 73   ....6.n..E....ps
        0060 - ea f3 82 34 59 72 98 c2-8e bd 15 f3 65 1c 9f b9   ...4Yr......e...
        0070 - 69 46 eb bb 78 3c 71 1d-2c 58 79 49 07 24 ea ac   iF..x<q.,XyI.$..
        0080 - 18 51 2e 01 a6 8b 53 94-f0 f0 65 4e ec fc fa 99   .Q....S...eN....
        0090 - e3 c5 00 9b 03 4e 46 7e-e8 dd f6 bd 8d 3c 4c 02   .....NF~.....<L.
    
        Start Time: 1573503334
        Timeout   : 7200 (sec)
        Verify return code: 18 (self signed certificate)
        Extended master secret: yes
    ---
    a
    b
    c

O passo seguinte foi entender o código e as diferenças com os samples que havia tentado fazer funcionar da única maneira que penso ser possível: depurando. Sem conseguir navegar em todos os detalhes do fonte do OpenSSL recompilei o projeto com full debug alterando as flags de compilação no Makefile gerado para Windows (/Od e /Zi ajudam) e iniciei os dois modos acima depurando em duas instâncias do Visual Studio. Encontrei uma ou outra chamada à biblioteca OpenSSL que não havia notado ainda, mas nada que parece fazer a diferença.

    // from s_server.c
    SSL_CTX_clear_mode(ctx, SSL_MODE_AUTO_RETRY);
    SSL_CTX_set_quiet_shutdown(ctx, 1);
    SSL_CTX_sess_set_cache_size(ctx, 128);
    
    // client has to authenticate
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_CLIENT_ONCE, dtls_verify_callback);
    // s_server.c version
    SSL_CTX_set_verify(ctx, 0, dtls_verify_callback);

Mas nenhuma dessas mudanças fez efeito no projeto de teste. O próximo passo seria copiar cada chamada feita à lib OpenSSL pelo openssl.exe e colar no projeto de teste para descobrir onde está o pulo do gato que nenhum dos samples na internet parece ter encontrado (ao menos para Windows), mas há uma solução preguiçosa que é muito mais efetiva e testada: usar os fontes da própria pasta apps do projeto OpenSSL.

O próximo e último passo é customizar o código-fonte base no qual a OpenSSL valida o protocolo DTLS para o uso que pretendo fazer para ele: um executador de processos remoto.
