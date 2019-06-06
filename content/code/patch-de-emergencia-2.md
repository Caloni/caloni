---
date: "2010-11-09"
title: Patch de emergência 2
categories: [ "code" ]
---
No artigo anterior fizemos um patch rapidinho na memória se aproveitando de um Sleep nojento que o código nos forneceu.

E se não houvesse Sleep?

As chances de estarmos escrevendo no momento em que a função está sendo executada são tremendas, de forma que não poderíamos sobrescrevê-la sem correr o risco de um crash.

Uma solução alternativa para isso é alocar um novo pedaço de memória para a versão corrigida e trocar o endereço de chamada na função main.

    
    windbg criticalservice3.exe
    
    0:000> uf DoProcess
    criticalservice3!DoProcess [s:\docs\artigos\criticalservice3.cpp @ 8]:
        8 00401020 55              push    ebp
       ...
       12 0040107d 5d              pop     ebp
       12 0040107e c3              ret
    0:000> .writemem <font color="#008000">DoProcess.func</font> 00401020 0040107e
    Writing <font color="#0000ff">5f bytes</font>.

    
    windbg -pvr -pn criticalservice2.exe
    
    0:000> .dvalloc 0x5f
    Allocated 1000 bytes starting at 00030000
    0:000> .readmem <font color="#008000">DoProcess.func</font> 00030000 <font color="#0000ff">L5f</font>
    Reading <font color="#0000ff">5f bytes</font>.
    0:000> uf 00030000
    00030000 55              push    ebp
    ...
    0003005d 5d              pop     ebp
    0003005e c3              ret

Antes de trocarmos o endereço dentro do main precisamos "consertar" a função copiada. Ela está usando as funções globais rand e printf, e as chamadas usam offsets relativos. Como agora a função está em outro offset, temos que reconstruir as chamadas:

    
    00401026 e8da000000      call    criticalservice3!rand (00401105)
    00030006 e8da000000      call    000300e5
    
    0:000> a 00030006
    00030006 call 0x00401105
    call 0x00401105
    0003000b 
    
    00401073 e852000000      call    criticalservice3!printf (004010ca)
    00030053 e852000000      call    000300aa
    
    0:000> a 00030053
    00030053 call 0x004010ca
    call 0x004010ca
    00030058

Agora a função está pronta para ser usada.

    
    0:000> uf 00030000
    00030000 55              push    ebp
    00030001 8bec            mov     ebp,esp
    00030003 83ec0c          sub     esp,0Ch
    00030006 e8fa103d00      call    criticalservice2!rand (00401105)
    0003000b 99              cdq
    ...
    0003004e 6828a04000      push    offset criticalservice2!GetSystemInfo
    00030053 e872103d00      call    criticalservice2!printf (004010ca)
    00030058 83c40c          add     esp,0Ch
    0003005b 8be5            mov     esp,ebp
    0003005d 5d              pop     ebp
    0003005e c3              ret
    
    0:000> uf main
    criticalservice2!main [s:\docs\artigos\criticalservice2.cpp @ 16]:
       16 00401080 55              push    ebp
    ...
    criticalservice2!main+0x1f [s:\docs\artigos\criticalservice2.cpp @ 21]:
       21 0040109f e861ffffff      call    criticalservice2!ILT+0(?DoProcessYAXXZ) (00401005)
       22 004010a4 ebf0            jmp     criticalservice2!main+0x16 (00401096)

É nessa parte que trocaremos o endereço o endereço 00401005 pela memória alocada. Note que essa escrita é muito rápida e o programa lê esse endereço por muito pouco tempo se compararmos com todas as intruções que são executadas. No entanto, essa escrita não é atômica, e mesmo que as chances sejam extremamente remotas, ainda assim pode haver uma colisão no acesso à essa parte.

É salutar rezar por 10 segundos.

    
    0:000> a 0040109f
    0040109f call 0x00030000
    call 0x00030000
    004010a4

E voilà! A partir do momento em que digitei o call seguido de <enter>, a função nova já começou a operar em cima do processo ainda rodando. Se quisermos voltar a função antiga, sem problemas:

    
    0:000> a 0040109f
    0040109f call 0x00401005
    call 0x00401005
    004010a4

Não façam isso em casa, crianças ;)
