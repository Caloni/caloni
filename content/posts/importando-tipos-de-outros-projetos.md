---
categories: [ "code" ]
date: "2010-01-11"
tags: [ "draft",  ]
title: "Importando tipos de outros projetos"
---
A engenharia reversa das entranhas do kernel não tem limites se você sabe o que está fazendo. No entanto, algumas facilidades do depurador podem ajudar a minimizar o tempo que gastamos para analisar uma simples estrutura. Por exemplo, o Process Environment Block de um processo específico.


O comando !peb traz inúmeras informações sobre essa estrutura. Mas talvez estivéssemos interessados em coisas não mostradas por esse comando, mas que existem na estrutura.

Nesse caso, podemos criar um projeto vazio que contenha a definição da estrutura como acreditamos que esteja na versão do kernel que estamos depurando.

Compilamos e geramos um PDB (arquivo de símbolos) que contém a definição desse tipo. Tudo que precisamos fazer agora é carregar esse símbolo na sessão que estivermos depurando.

É claro que nosso executável não vai existir na sessão de kernel local, mas isso não importa. Podemos usar qualquer módulo carregado e usá-lo como host de nosso conjunto de símbolos:


Depois que o símbolo foi carregado em nosso módulo de mentirinha, tudo que temos a fazer é alterar o contexto do processo atual (para que os endereços de user mode façam sentido) e moldar nossa memória com o comando dt, usando o tipo importado do símbolo carregado.


Para que isso funcione, a estrutura definida tem que bater offset por offset com os dados na memória, o que envolve alinhamento (se lembre do pragma pack) e versionamento corretos. Se isso não ocorrer, logo aparecerá algum lixo nos membros da estrutura que não fará sentido. Se isso ocorrer, detecte onde o lixo começa e verifique se o membro existe nessa versão do sistema operacional, ou se o alinhamento está de acordo com o módulo analisado.

Acho que não é preciso dizer que isso não serve apenas para kernel mode =)
