---
date: "2018-07-14"
tags: [ "code", "draft",  ]
title: "Python27, protobuf, py2exe e buildexe"
---
Para quem está tentando compilar um executável usando py2exe e protobuf, #ficadica: desista. Ele não vai funcionar ou se funcionar vai dar trabalho. Em vez disso melhor usar buildexe (através do pacote cxfreeze), que é um esquema marotinho que permite configurar tudo e há apenas um patchzinho que precisa ser feito.

Para entender como as coisas dão errado primeiro vamos instalar os requisitos de um pacote fictício em um ambiente virtualizado do Python (para evitar mexer na instalação padrão):


Depois instalamos os requisitos de nosso pacote fictício:


Agora vem a hora do erro. O protobuf que foi instalado possui um pequeno bug que impede que o buildexe obtenha essa dependência corretamente na hora de gerar o executável:


Para fazer funcionar há um pequeno patch: criar um arquivo \\init\\.py dentro da pasta google onde está instalado o pacote do protobuf:


Após essa pequena operação já será possível gerar o executável com sucesso:


Agora ao listarmos os executáveis gerados encontraremos nosso amigo fictício:


NOTA: conteúdo do arquivo setup.py:


