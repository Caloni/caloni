---
categories: []
date: '2016-08-16'
tags:
- draft
title: 'Electrum: uma opção simples e rápida de manter bitcoins seguros'
---

Estava já há algum tempo pesquisando as melhores ferramentas para organizar carteiras bitcoin. E quando se fala em ter seus próprios bitcoins, a segurança deve ser prioridade número zero. Isso porque, diferente de bancos, quando você se dispõe a gerenciar seu próprio cofre, é você, e apenas você, o único responsável pela sua integridade.

Isso quer dizer que apenas uma senha protegendo sua chave privada talvez não seja necessário. Algum hacker ou programa malicioso instalado na sua máquina (como um keylogger) pode facilmente obter essa informação.

E, sim, é preciso pensar que pode haver um keylogger em cada teclado que você for usar para digitar sua bendita senha. Por isso ter uma senha segura, no caso de bitcoins, não funciona muito bem.

Além disso, há também a segurança dos próprios dados. Não de serem roubados, mas perdidos. Nesse caso, uma estratégia muito interessante, por acrescentar entropia e comodidade, são as carteiras determinísticas. Elas se baseiam em um grupo de palavras que são usadas para gerar o par de chaves pública e privada e derivar as próximas chaves de sua carteira. Com isso, basta guardar (em papel, no seu cérebro, mas nunca em software!) essas palavras que você poderá resgatar sua carteira, reproduzindo o algoritmo de derivação.

Outro ponto importante, para os mais paranóicos, é conseguir gerenciar carteiras "frias", que são carteiras que não podem ser usadas para gastar, apenas para receber. Funciona assim: você gera o seu endereço público para a transação, onde as pessoas podem depositar seus bitcoins, mas a chave privada, necessária para enviar bitcoins dessa carteira, é removida ou não está disponível. Dessa forma, ela vira uma carteira "watch-only", em que o portador só consegue verificar o saldo e as transações, mas não realizar uma (a não ser que ele assine a transação em outro computador com a chave privada, ou resgate a chave privada de algum lugar, que seria o lugar "quente").

Esse cold storage de carteiras, como é chamado, só é possível de duas maneiras: sendo você próprio um servidor da blockchain ou utilizando a infraestrutura da nuvem para validar as transações. A primeira forma é muito custosa, pois a blockchain cresce a olhos vistos, e demora hoje alguns dias para resgatar toda ela desde 2009. A segunda opção é mais rápida, mas depende da integridade dos servidores, libera mais informações sobre as transações do que devia, além de ser lento.

Dentro dessa segunda opção, porém, existe uma maneira rápida de verificar a transação sem comprometer seus dados, enviando coisas a mais para o servidor que irá validá-lo. Se chama Simple Payment Verification, e já estava prevista no paper original de Satoshi. Ela se baseia apenas em uma árvore de hashes montada justamente para compor a blockchain. Gerenciar essa informação economiza muito mais tempo e processamento, além de liberar apenas a informação essencial para os servidores validarem.

Todos esses elementos estão juntos no Electrum, uma ferramenta feita em Python que possui uma versão monolítica (um exe apenas) para Windows e que mantém as carteiras em texto plano em sua máquina. Sim, não há criptografia desnecessária. Afinal de contas, só a chave privada é que precisa ser protegida, e ela é aberta apenas durante a assinatura de uma transação, tornando todo o processo muito rápido.

Em sua página é possível tirar todas as dúvidas de como fazer uma carteira offline (fria), como apenas assinar transações, como gerenciar as carteiras, em que arquivo elas ficam, o que comem, etc. Estou usando e estou muito feliz, pois é o primeiro software que gerencia bitcoins que consegue a proeza de ser simples de usar, flexível e rápido.

Ah, e ainda possui um console em Python, para rodar seus programas =)