---
date: "2020-04-05"
link: "https://github.com/Caloni/golang_c"
categories: [ "code" ]
title: "Golang e C"
---
É muito difícil configurar a linguagem Go no ambiente Windows para compilar código C. O único ambiente de compilação que o projeto leva a sério são os ports do GCC, e não o Visual Studio, que seria a ferramenta nativa. Dessa forma, realizei boa parte das travessuras desse artigo em Linux, usando o WSL com a distro Ubuntu ou CentOS. Deve funcionar em qualquer Unix da vida.

A linguagem Go na versão mais nova precisa que seja definida através da cgo, o backend C do ambiente de build da linguagem, uma função trampolim, que é uma função escrita em C que irá chamar uma função escrita em Go. Essa função pode ser passada como parâmetro de callback para uma biblioteca C que quando a biblioteca C chamar esse ponteiro de função ele irá atingir a função trampolim, que por sua vez, chama a função Go, que é onde queremos chegar depois de todo esse malabarismo.

    main
     |
     C.set_callback
      |
      C.call_callback
       |
       g_callback*
        |
        GoCallback_cgo
         |
         GoCallback

Em resumo: o main em Go chama C.set_callback (função C exportada) passando o endereço do seu callback (em cgo) e em uma segunda chamada ou nessa mesma pede para chamar esse callback. O módulo em C pode ou não chamar essa função nessa thread ou mais tarde, através do ponteiro de função que estocou (g_callback). Ao chamá-la, ativará a função GoCallback_cgo, que por sua vez chamará GoCallback, essa sim, já no módulo Go (embora ambas estejam no mesmo executável, já que C e Go podem ser linkados juntos de maneira transparente.

Criei um repositório com os fontes deste artigo. Bom proveito =)
