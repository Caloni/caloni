---
date: "2011-04-28"
title: Houaiss 1.3
categories: [ "blog" ]
---
### Notificação

Os problemas relacionados com acesso negado durante a conversão/construção do dicionário foram corrigidos na novíssima versão disponível para download no linque abaixo.

	
  * Download Houaiss2Babylon v1.3

Para os que estão desenvolvendo soluções baseadas na minha solução (como o Houaiss para Kindle, segue o linque para download do último branch.

	
  * Download do código-fonte do Houaiss2Babylon v1.3

### Explicação

Erroneamente imaginando que a falta de acesso tinha alguma coisa a ver com a escrita de arquivos no disco, ou até mesmo com a execução de processos, descobri depurando (o bom e velho depurador) que a origem do acesso negado estava na função AssignProcessToJobObject. Misteriosamente, no Windows 7, ao chamar essa função ocorre esse erro, **independente da execução ser como administrador ou não**.

Como já está se tornando tradição de uns tempos pra cá, a solução veio de um artigo do Stack Overflow, cuja melhor solução foi exatamente a que eu segui: inserir o manifesto do UAC e usar a flag CREATE_BREAKAWAY_FROM_JOB.

Agora é só esperar pelo próximo bug =)
