---
date: "2011-03-23"
tags: [ "code", "draft", "tools" ]
title: "Bazaar com Subversion"
---
Para pessoas que ficaram viciadas em commits curtos e todo o histórico do fonte na própria máquina, foi uma surpresa descobrir que com o uso do plugin bzr-svn (já incluso no pacote de instalação), consigo ainda utilizar o Bazaar, mesmo que agora esteja trabalhando com um branch do Subversion.

Na verdade, melhor ainda: o bzr-svn baixa o SVN trunk com todo o histórico na máquina local, como se fosse um branch do próprio Bazaar, e permite a criação de branches desconectados para pequenos commits e o merge final para o servidor SVN.

E o melhor de tudo: não há segredo. Tudo que precisa fazer é instalar o Bazaar e fazer um get/co com o endereço do branch SVN que o plugin se vira sozinho para detectar que se trata do Subversion. (Se for um branch protegido, o usuário e senha serão pedidos durante o processo).


