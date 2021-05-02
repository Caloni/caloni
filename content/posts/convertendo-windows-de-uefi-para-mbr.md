---
date: "2017-02-13"
categories: [ "code", "draft",  ]
title: "Convertendo Windows de UEFI para MBR"
---
Quando você pesquisa sobre isso no Google o que mais encontra é ferramentas "gratuitas" que prometem fazer a conversão ou algo do gênero. No entanto, há um procedimento simples em que o próprio Windows pode corrigir os problemas oriundos da conversão do boot UEFI/GPT. Depois, é claro, que você usar uma outra ferramenta esperta open-source =)

Entre as diferentes distros do Linux há uma chamada SystemRescueCD que é cheia dos paranauê para manutenção de micros. Entre eles há uma ferramenta chamada testdisk que tem a "proeza" de sair buscando partições perdidas e reescrever o MBR (seja o código ou a tabela de partições). É uma ferramenta simples, interativa e ágil. É ela que deve ser usada para resgatar as partições da máquina após configurar a BIOS para voltar a bootar no modo legacy.

Depois de feita essa manipulação é a vez do CD do Windows, que deverá estar em mãos porque o Windows simplesmente não irá mais bootar. A instalação feita através do modo UEFI não instala o BOOTMGR, o gerenciador de boots do Windows. Isso porque ele não é usado, já que é a partição UEFI que se torna responsável por gerenciar o boot dos SOs presentes.

Mas isso não significa que essa instalação do Windows está perdida. Através de dois boots com o CD, ambos escolhendo o modo de restauração (Repair e Repair at Startup) é possível fazer com que o Windows ache o problema (o bootmgr faltando) e "conserte" a instalação.

No primeiro boot o Windows irá achar um problema inicial na própria instalação, no segundo boot ele já encontra a instalação. E, acreditem só, ele descobre que o BOOTMGR está faltando!

E a partir daí a partição UEFI se torna inútil, embora ainda exista no início do HD, já que o boot legacy usa o velho esquema de usar o código da MBR e a partir daí chamar a partição ativa, que agora será a Windows.

Essa manipulação do boot pode dar algum trabalho, mas é gratuita e com todos os passos devidamente documentados. E não há mágica: reconstrução da MBR seguido de restauração de um SO pré-existente (Windows, no caso).
