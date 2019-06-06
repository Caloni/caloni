---
date: "2011-04-28"
title: Houaiss 1.3
categories: [ "code" ]
---
### Notificação

Os problemas relacionados com acesso negado durante a conversão/construção do dicionário foram corrigidos na novíssima versão disponível para download no linque abaixo.

	
  * [Download Houaiss2Babylon v1.3](/images/houaissparababylon1.31.zip)

Para os que estão desenvolvendo soluções baseadas na minha solução (como o [Houaiss para Kindle](http://www.caloni.com.br/houaiss-no-kindle)), segue o linque para download do último branch.

	
  * [Download do código-fonte do Houaiss2Babylon v1.3](/images/houaissparababylon-src1.zip)

### Explicação

Erroneamente imaginando que a falta de acesso tinha alguma coisa a ver com a escrita de arquivos no disco, ou até mesmo com a execução de processos, descobri depurando (o bom e velho depurador) que a origem do acesso negado estava na função [AssignProcessToJobObject](http://msdn.microsoft.com/en-us/library/ms681949(v=vs.85).aspx). Misteriosamente, no Windows 7, ao chamar essa função ocorre esse erro, **independente da execução ser como administrador ou não**.

Como já está se tornando tradição de uns tempos pra cá, a solução veio de [um artigo do Stack Overflow](http://stackoverflow.com/questions/89588/assignprocesstojobobject-fails-with-access-denied-error-when-running-under-the), cuja melhor solução foi exatamente a que eu segui: inserir o manifesto do UAC e usar a flag CREATE_BREAKAWAY_FROM_JOB.

Agora é só esperar pelo próximo bug =)
