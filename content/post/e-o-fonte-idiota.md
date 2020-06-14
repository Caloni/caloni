---
categories: [ "code" ]
date: "2015-09-12"
tags: [ "draft", "essays" ]
title: "É o fonte, idiota!"
---
Saiu um artigo recente no The Old New Thing (thanks Strauss pelo tuíte) que fala sobre não misturar runtimes do C de diferentes versões do compilador (especialmente se essas versões estão separadas pelo tempo em nada mais nada menos que dezenove anos!). Concordo. Aliás, a cultura Microsoftiana do uso de binários carece em C/C++ de um fundamento que facilite o reúso e compartilhamento de código exatamente por essa incompatibilidade inerente de uma biblioteca, se não em constante evolução, em constante aprimoramento pontual (como a STL). Como compartilhar código cujo fonte esteja indisponível e cujas bibliotecas sejam incompatíveis porque o projeto não é atualizado há dois pares de anos? Fiz uma vez um artigo explicando como usar a LIBC nativa do sistema operacional (nem sei se isso funciona ainda, provavelmente não). No entanto, essa é uma solução sub-ótima para um problema latente.

É por isso que nesse caso a cultura Linux de compartilhamento do código-fonte acaba por ser a mais flexível e melhor adaptável à mudança dos tempos. Se você encontrou uma LIB que pode te ajudar, baixe e compile usando o último compilador. Se o compilador não consegue mais gerar binário sem gerar erros antes, configure os parâmetros de compilação como eram na época que a LIB foi gerada. A runtime do C (e de qualquer outro framework) que será usado é o da sua máquina. Afinal de contas, é o que faz mais sentido, não? Por que hoje existem diferentes conjuntos de DLLs de runtime de diferentes versões do Visual Studio instalados em sua máquina? Por que os instaladores precisam se preocupar em compartilhar essas DLLs corretamente?

Questões de um passado remoto que voltam a bater à porta sempre que a Microsoft resolve lançar um novo Visual Studio. E isso irá se tornar cada vez mais constante, já que versões com começo e fim bem-definidos são um conceito também antigo, quando comprávamos pela licença de uma versão específica do programa. E hoje, no modelo de assinaturas, como fica?
