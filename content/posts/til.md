---
date: "2020-12-08"
link: "https://www.reddit.com/r/todayilearned/"
tags: [ "blog", "lists" ]
title: "TIL: Today I Learned"
---
Se você guardar o mínimo de conhecimento que aprendeu em um dia de sua vida e relembrá-lo ao longo dos anos não vai perceber qualquer diferença, pois com a internet fica fácil recuperar o conhecimento com nova pesquisa. No entanto, na internet está também você e seu conhecimento em forma de posts, comentários, podcasts ou qualquer tipo de conteúdo que você produziu. Não custa manter a rotina de gravar o que foi aprendido em um dia para tentar capturar a essência de cada um deles. Quem sabe algo de esclarecedor sobre nós mesmos não pode surgir disso.

 - 2021-04-21: meu blogue não é um blogue, mas um [jardim digital].

 - 2020-08-07: ao usar ponto (.) antes de rodar um comando no terminal Linux é possível definir variáveis de ambiente. Com isso consigo definir o ambiente para fazer cross compiling em Golang no Linux para Windows, gravando as variáveis em um arquivo executável "export GOOS=windows; export GOARCH=amd64; etc" e chamando com ". meu_arquivo" no terminal.

 - 2020-10-22: para desabilitar expiração de senhas no Oracle o comando `alter user user_name identified by new_password account unlock;` resolve. Para as senhas não expirarem novamente em ambiente de desenv é só usar o comando `ALTER PROFILE "DEFAULT" LIMIT PASSWORD_VERIFY_FUNCTION NULL;` uma vez no banco.

 - 2020-10-22: para apagar tags dos posts é possível usar o seguinte comando `sed -e "s/\[ \"tag\"[,]*/[/" -e "s/[,]* \"tag\" ]/ ]/" -e "s/, \"tag\", /, /"`.

 - 2020-10-26: para dar sleep em C++ moderno com resolução de milissegundos é `std::this_thread::sleep_for(std::chrono::milliseconds(200));`. É tão intuitivo que achei preciso anotar.

 - 2020-11-21: para eliminar qualquer nova-linha em uma string C após ler uma linha da entrada usar uma desconhecida função padrão: `buffer[strcspn(buffer, "\r\n")] = 0;`.

 - 2020-12-08: é possível abrir uma VPN pelo WSL e direcionar a porta RDP de uma máquina remota para uma porta local no Windows e acessar máquinas via RDP em uma porta local. Para a VPN uso o Openvpn. Para o redirect um projeto no GitHub chamado [rinetd].

[rinetd]: https://github.com/boutell/rinetd
[jardim digital]: https://joelhooks.com/digital-garden
