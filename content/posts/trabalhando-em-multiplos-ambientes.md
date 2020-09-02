---
date: "2010-12-27"
tags: [ "code", "draft",  ]
title: "Trabalhando em múltiplos ambientes"
---
Existem diversas maneiras de se trabalhar com o Bazaar. Eu já havia definido como fazer na máquina de desenvolvedor para modificar o mesmo código-fonte em projetos paralelos, onde basicamente tenho um branch principal conectado no servidor (assim todo commit vai pra lá) e crio branches paralelos e desconectados para fazer quantos commits eu tenho vontade durante o desenvolvimento. Após todas as mudanças e testes básicos, atualizo o branch principal (com mudanças dos meus colegas) e faço o merge com o branch paralelo onde fiz todas as mudanças. Antes de subir com o commit final, ainda realizo um build de teste local, se necessário.

Nos casos em que eu trabalho em casa (ou em outro ambiente), posso fazer basicamente a mesma coisa, só que meu branch paralelo é copiado para outra máquina:


Geralmente o que faço depois é compactar a pasta gerada (se desejar, use uma senha forte nesse passo), fazer uma cópia para um PenDrive e descompactar na máquina que irei trabalhar.


Terminado o trabalho naquela máquina, geralmente gero um branch novo (para limpar o diretório) e recompacto a solução, copio para o Pendrive, e descompacto na máquina da empresa. O resto do caminho é como se eu tivesse feito as modificações na própria máquina:

