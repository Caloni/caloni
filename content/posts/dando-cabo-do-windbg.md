---
categories:
- code
date: '2014-06-18'
link: https://farm6.staticflickr.com/5510/14191895328_44a2ec8338_z.jpg
tags:
title: Dando cabo do WinDbg
---

Na semana passada falei sobre a ideia de comentar algumas mudanças entre o Windows XP e o novo mundo Vista/7/8/ que fizeram com que adaptássemos algum código que obviamente não funcionaria mais. Falamos sobre a famigerada GINA (ou famiGINADA), e agora apenas vou comentar brevemente sobre o sistema de boot, que também mudou.

Na verdade, pouca coisa mudou, mas foi o suficiente para dar problemas na hora de usar o WinDbg. Tradicionalmente, o boot era gerenciado no Windows através de um arquivo localizado na raiz da partição ativa (configuração da MBR) chamado bootini. Dentro dele temos uma estrutura semelhante a um .INI (duh), onde a informação que vemos lá podia ser configurada nas configurações do Computador no Windows XP.

Hoje em dia esse arquivo nem existe mais, o que pode dar um friozinho na barriga ("caramba, não vai mais bootar!!"). Agora, para sistemas baseados em BIOS há uma pasta Boot na raiz e um arquivo chamado bcd. Para os mais moderninhos, baseados em EFI, ele fica na partição EFI. Ah, EFI é Extensible Firmware Interface, e faz parte da especificação da UEFI (Universal blá blá blá), mais ou menos um padrão que define como deve ser feita a comunicação entre hardware e sistema operacional.

Para a edição desse novo arquivo (ou partição) é necessário que seja usada a ferramenta BCDEdit no Windows. É ela que agora configura qual partição está ativa e, mais importante para escovadores de bits, qual pode ser depurada pela porta serial através do WinDbg.

Porta serial? Mas que coisa antiga, hein? Pois é, muita coisa mudou desde o Windows Vista, mas algumas coisas precisam permanecer... compatíveis.

Mas... se você precisar:
