---
categories: [ "code" ]
date: "2020-04-05"
tags: [ "draft",  ]
title: "Golang e C"
---
É muito difícil configurar a linguagem Go no ambiente Windows para compilar código C. O único ambiente de compilação que o projeto leva a sério são os ports do GCC, e não o Visual Studio, que seria a ferramenta nativa. Dessa forma, realizei boa parte das travessuras desse artigo em Linux, usando o WSL com a distro Ubuntu ou CentOS. Deve funcionar em qualquer Unix da vida.

A linguagem Go na versão mais nova precisa que seja definida através da cgo, o backend C do ambiente de build da linguagem, uma função trampolim, que é uma função escrita em C que irá chamar uma função escrita em Go. Essa função pode ser passada como parâmetro de callback para uma biblioteca C que quando a biblioteca C chamar esse ponteiro de função ele irá atingir a função trampolim, que por sua vez, chama a função Go, que é onde queremos chegar depois de todo esse malabarismo.

Em resumo: o main em Go chama C.setcallback (função C exportada) passando o endereço do seu callback (em cgo) e em uma segunda chamada ou nessa mesma pede para chamar esse callback. O módulo em C pode ou não chamar essa função nessa thread ou mais tarde, através do ponteiro de função que estocou (gcallback). Ao chamá-la, ativará a função GoCallbackcgo, que por sua vez chamará GoCallback, essa sim, já no módulo Go (embora ambas estejam no mesmo executável, já que C e Go podem ser linkados juntos de maneira transparente.


O módulo em Go precisa de um forward declaration para a função cgo e precisa exportar a função Go que será chamada por ela através do importantíssimo comentário export antes da função (se retirado este comentário a solução para de funcionar):


O módulo trampolim de Go é muito simples. Além de incluir o mesmo header em C para os tipos especificados ali, ela faz uma foward declaration da função do módulo Go anterior e chama esta função, repassando a chamada para o mundo Go.


Mais uma vez há algo extremamente importante nos detalhes: a chamada import "C" logo após o código dentro dos comentários desse módulo.

O resto é C padrão. O header define os tipos (inclusive do callback) e as funções exportadas:

A parte C apenas implementa as funções:

E para exportar essas funções basta um arquivo def no projeto:


O CMakeLists.txt deste projeto pode apenas especificar qual o tipo de biblioteca. Não há nada de especial na parte C. Ou seja, funciona com qualquer código que você saiba as assinaturas das funções.


Após compilar ambas as soluções na mesma pasta (considerando que foi criada uma subpasta onde estão esses fontes) basta executar o binário Go e ver a mágica funcionando. No meu caso, tive que executar tudo no WSL. Ainda preciso ver como configura essa bagaça de Go no Windows.


Criei um repositório com os fontes deste artigo. Bom proveito =)
