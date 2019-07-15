---
date: "2010-08-03"
title: Como achar o código-fonte sem símbolos
categories: [ "code" ]
---
Continuo escovando bits. Dessa vez de forma mais nervosa. Se trata de um serviço que trava durante seu stop. Um colega muito esperto do suporte gerou um dump para mim, tornando as coisas mais fáceis. O problema era que não havia símbolos nem código-fonte que batessem exatamente com aquela compilação de 2004. Solução? Analisar as pilhas das threads restantes.

É sabido que esse serviço responde requisições de milhares de máquinas em um período curto de tempo, então por isso a primeira coisa que me atentei foi verificar quantas threads haviam:

    
    0:000> ~*
    .  0  Id: 4c8.30c Suspend: 1 Teb: 7ffde000 Unfrozen
          Start: *** WARNING: Unable to verify checksum for Service.exe
    *** ERROR: Module load completed but symbols could not be loaded for Service.exe
    Service+0xc60c (0040c60c)
          Priority: 0  Priority class: 32  Affinity: f
       1  Id: 4c8.4d8 Suspend: 1 Teb: 7ffdd000 Unfrozen
          Start: ADVAPI32!AccessCheckByTypeResultListAndAudit(...)
          Priority: 0  Priority class: 32  Affinity: f
       2  Id: 4c8.580 Suspend: 1 Teb: 7ffdc000 Unfrozen
          Priority: 0  Priority class: 32  Affinity: f
       3  Id: 4c8.adc Suspend: 1 Teb: 7ffd9000 Unfrozen
          Start: rtutils!TraceServerThread (778321fe)
          Priority: 0  Priority class: 32  Affinity: f
       4  Id: 4c8.f1c Suspend: 1 Teb: 7ffa5000 Unfrozen
          Start: rpcrt4!ThreadStartRoutine (77d37e70)
          Priority: 0  Priority class: 32  Affinity: f
    ...
     1426  Id: 4c8.1464 Suspend: 1 Teb: 7fa0c000 Unfrozen
          Start: rpcrt4!ThreadStartRoutine (77d37e70)
          Priority: 0  Priority class: 32  Affinity: f
     1427  Id: 4c8.144c Suspend: 1 Teb: 7fa0b000 Unfrozen
          Start: rpcrt4!ThreadStartRoutine (77d37e70)
          Priority: 0  Priority class: 32  Affinity: f
     1428  Id: 4c8.12dc Suspend: 1 Teb: 7fa09000 Unfrozen
          Start: rpcrt4!ThreadStartRoutine (77d37e70)
          Priority: 0  Priority class: 32  Affinity: f
     1429  Id: 4c8.1410 Suspend: 1 Teb: 7fa08000 Unfrozen
          Start: rpcrt4!ThreadStartRoutine (77d37e70)
          Priority: 0  Priority class: 32  Affinity: f

1430 

    
    Id: 4c8.143c Suspend: 1 Teb: 7fa06000 Unfrozen
          Priority: 0  Priority class: 32  Affinity: f

São muitas.

Analisar essa quantidade absurda de threads seria um saco. Além de inútil. Foi por isso deus inventou a função **!uniqstack**, que encontra automagicamente quais threads estão com a pilha duplicada.

    
    0:000> !uniqstack
    Processing 1431 threads, please wait
    
    .  0  Id: 4c8.30c Suspend: 1 Teb: 7ffde000 Unfrozen
          Start: Service+0xc60c (0040c60c)
          Priority: 0  Priority class: 32  Affinity: f
    ChildEBP RetAddr
    0012f9f8 7c586381 NTDLL!ZwReadFile+0xb
    0012fa6c 7c2dd578 KERNEL32!ReadFile+0x181
    ...
    0012fff0 00000000 KERNEL32!BaseProcessStart+0x3d
    
    .  1  Id: 4c8.4d8 Suspend: 1 Teb: 7ffdd000 Unfrozen
          Start: ADVAPI32!AccessCheckByTypeResultListAndAudit(...)
          Priority: 0  Priority class: 32  Affinity: f
    ChildEBP RetAddr
    00cefec0 7c59a0a2 NTDLL!ZwWaitForSingleObject+0xb
    ...
    00cf000c 007a0000 0x1366e0
    00cf000c 00000000 0x7a0000
    
    .  2  Id: 4c8.580 Suspend: 1 Teb: 7ffdc000 Unfrozen
          Priority: 0  Priority class: 32  Affinity: f
    ChildEBP RetAddr
    010efe24 77d59815 NTDLL!ZwReplyWaitReceivePortEx+0xb
    ...
    010effec 00000000 KERNEL32!BaseThreadStart+0x52
    
    .  3  Id: 4c8.adc Suspend: 1 Teb: 7ffd9000 Unfrozen
          Start: rtutils!TraceServerThread (778321fe)
          Priority: 0  Priority class: 32  Affinity: f
    ChildEBP RetAddr
    0150fd20 7c59a26d NTDLL!ZwWaitForMultipleObjects+0xb
    ...
    0150ffec 00000000 KERNEL32!BaseThreadStart+0x52
    ...
    .1430  Id: 4c8.143c Suspend: 1 Teb: 7fa06000 Unfrozen
          Priority: 0  Priority class: 32  Affinity: f
    ChildEBP RetAddr
    6665f0dc 7c59a0a2 NTDLL!ZwWaitForSingleObject+0xb
    ...
    6665ffec 00000000 KERNEL32!BaseThreadStart+0x52
    
    Total threads: 1431
    Duplicate callstacks:

1092 

    
    (windbg thread #s follow):
    7, 9, 11, 12, 13, 14, 15, 17, 18, 20, 21, (...), 1428, 1429

Muitas threads duplicadas. Isso quer dizer que podemos nos focar na pilha de uma delas. Basta pegar uma.

    
    0:000> ~1429 kv

ChildEBP 

    
    RetAddr  Args to Child
    6645f334 7c59a0a2 ... NTDLL!ZwWaitForSingleObject+0xb (FPO: [3,0,0])
    6645f35c 7c57b40f ... KERNEL32!WaitForSingleObjectEx+0x71 (FPO: [Non-Fpo])
    6645f36c 004054c3 ... KERNEL32!WaitForSingleObject+0xf (FPO: [2,0,0])
    WARNING: Stack unwind information not available. Following frames may be wrong.

6645f690 004060ec ... Service+0x54c3 6645f764 77d79970 

    
    ...

Service+0x60ec6645f788 

    
    77d96460 ... rpcrt4!Invoke+0x30
    6645f7a0 77d9637a ... rpcrt4!NdrCallServerManager+0x15 (FPO: [4,0,2])
    6645fa90 77d9076f ... rpcrt4!NdrStubCall+0x200 (FPO: [Non-Fpo])
    6645faf4 7cef55fd ... rpcrt4!CStdStubBuffer_Invoke+0xc1 (FPO: [Non-Fpo])
    6645fb38 7cef58d8 ... OLE32!SyncStubInvoke+0x61 (FPO: [Non-Fpo])
    6645fb80 7ce8833d ... OLE32!StubInvoke+0xa8 (FPO: [Non-Fpo])
    6645fbe4 7ce7a711 ... OLE32!CCtxComChnl::ContextInvoke+0xbb (FPO: [Non-Fpo])
    6645fc00 7cef54e2 ... OLE32!MTAInvoke+0x18 (FPO: [Non-Fpo])
    6645fc30 7cef5c06 ... OLE32!AppInvoke+0xb5 (FPO: [Non-Fpo])
    6645fcf0 7cef3360 ... OLE32!ComInvokeWithLockAndIPID+0x297 (FPO: [Non-Fpo])
    6645fd30 77d545b1 ... OLE32!ThreadInvoke+0x1b7 (FPO: [Non-Fpo])
    6645fd68 77d39463 ... rpcrt4!DispatchToStubInC+0x32 (FPO: [Non-Fpo])
    6645fdc0 77d39337 ... rpcrt4!RPC_INTERFACE::DispatchToStubWorker+0x100 (FPO: [Non-Fpo])
    6645fde0 77d39603 ... rpcrt4!RPC_INTERFACE::DispatchToStub+0x5e (FPO: [Non-Fpo])
    6645fe10 77d4740d ... rpcrt4!RPC_INTERFACE::DispatchToStubWithObject+0xa9 (FPO: [Non-Fpo])
    6645fe44 77d47634 ... rpcrt4!OSF_SCALL::DispatchHelper+0xa1 (FPO: [Non-Fpo])
    6645fe58 77d46f3b ... rpcrt4!OSF_SCALL::DispatchRPCCall+0x121 (FPO: [Non-Fpo])
    6645fe90 77d466ac ... rpcrt4!OSF_SCALL::ProcessReceivedPDU+0x68f (FPO: [Non-Fpo])
    6645feb0 77d48730 ... rpcrt4!OSF_SCALL::BeginRpcCall+0x183 (FPO: [Uses EBP] [2,0,4])
    6645ff10 77d5154b ... rpcrt4!OSF_SCONNECTION::ProcessReceiveComplete+0x326 (FPO: [Non-Fpo])
    6645ff20 77d516b8 ... rpcrt4!ProcessConnectionServerReceivedEvent+0x1b (FPO: [7,0,0])
    6645ff74 77d514bd ... rpcrt4!LOADABLE_TRANSPORT::ProcessIOEvents+0xcd (FPO: [Non-Fpo])
    6645ff78 77d3af8d ... rpcrt4!ProcessIOEventsWrapper+0x9 (FPO: [1,0,0])
    6645ffa8 77d37e88 ... rpcrt4!BaseCachedThreadRoutine+0x4f (FPO: [Non-Fpo])
    6645ffb4 7c57b3bc ... rpcrt4!ThreadStartRoutine+0x18 (FPO: [Non-Fpo])
    6645ffec 00000000 ... KERNEL32!BaseThreadStart+0x52 (FPO: [Non-Fpo])

Através das funções de RPC e OLE32 podemos concluir que se trata de uma chamada direta para uma interface COM. Bom, existem centenas de métodos e dezenas de interfaces nesse serviço, tornando mais fácil tentar desmontar a chamada inicial que o rpcrt4 faz ao nosso módulo.

    
    0:000> ub

77d79970

    
    rpcrt4!Invoke+0x20:
    77d79960 fd              std
    77d79961 f3a5            rep movs dword ptr es:[edi],dword ptr [esi]
    77d79963 8b45f4          mov     eax,dword ptr [ebp-0Ch]
    77d79966 50              push    eax
    77d79967 669d            popf
    77d79969 669d            popf
    77d7996b 8b4508          mov     eax,

dword ptr [ebp+8]

    
    77d7996e ffd0            call    eax

Nossa função é obtida em ebp+8. Podemos obter esse endereço pelo campo **ChildEBP **da função em questão.

    
    0:000> dd

6645f788

    
    +8 l1
    6645f790  00406061
    0:000> uf 00406061
    Service+0x6061:
    00406061 55              push    ebp
    00406062 8bec            mov     ebp,esp
    00406064 81ecc8000000    sub     esp,0C8h
    0040606a 833db09f410000

cmp dword ptr [Service+0x19fb0 (00419fb0)],0

    
    00406071 751b            jne     Service+0x608e (0040608e)

Service+0x6073

    
    :
    00406073 6a00            push    0
    00406075 6860514100      push    offset Service+0x15160 (00415160)
    0040607a b9609e4100      mov     ecx,offset Service+0x19e60 (00419e60)
    0040607f e822080000      call    Service+0x68a6 (004068a6)
    00406084 8b4514          mov     eax,dword ptr [ebp+14h]
    00406087 66c7002f00      mov

word ptr [eax],2Fh

    
    0040608c eb65            jmp     Service+0x60f3 (004060f3)
    
    Service+0x608e:
    0040608e 56              push    esi
    0040608f 8b7508          mov     esi,dword ptr [ebp+8]
    00406092 837e5200        cmp     dword ptr [esi+52h],0
    00406096 7430            je      Service+0x60c8 (004060c8)
    
    Service+0x6098:
    00406098 8d8538ffffff    lea     eax,[ebp-0C8h]
    0040609e 6830514100      push    offset Service+0x15130 (00415130)
    004060a3 50              push    eax
    004060a4 e85f4d0000      call    Service+0xae08 (0040ae08)
    004060a9 59              pop     ecx
    004060aa 59              pop     ecx
    004060ab 6a00            push    0
    004060ad 8d8538ffffff    lea     eax,[ebp-0C8h]
    004060b3 50              push    eax
    004060b4 b9609e4100      mov     ecx,offset Service+0x19e60 (00419e60)
    004060b9 e8e8070000      call    Service+0x68a6 (004068a6)
    004060be 8b4514          mov     eax,dword ptr [ebp+14h]
    004060c1 66c7000a40      mov     word ptr [eax],400Ah
    004060c6 eb2a            jmp     Service+0x60f2 (004060f2)
    
    Service+0x60c8:
    004060c8 6804010000      push    104h
    004060cd 8d868c010000    lea     eax,[esi+18Ch]
    004060d3 50              push    eax
    004060d4 ff750c          push    dword ptr [ebp+0Ch]
    004060d7 ff158c304100    call    dword ptr [Service+0x1308c (0041308c)]
    004060dd 668b4510        mov     ax,word ptr [ebp+10h]
    004060e1 8bce            mov     ecx,esi
    004060e3 66894648        mov     word ptr [esi+48h],ax
    004060e7 e892f2ffff      call    Service+0x537e (0040537e)
    004060ec 8b4d14          mov     ecx,dword ptr [ebp+14h]
    004060ef 668901          mov     word ptr [ecx],ax
    
    Service+0x60f2:
    004060f2 5e              pop     esi
    
    Service+0x60f3:
    004060f3 33c0            xor     eax,eax
    004060f5 c9              leave
    004060f6 c21000          ret     10h

Note como a função compara algo com zero. Caso não seja zero ela continua. Caso contrário ela vai para um ponto que chama uma função interna e move um código de erro para um ponteiro recebido como parâmetro, o que é muito normal, se lembrarmos que as funções COM de um programa em C devem retornar o código da chamada no retorno (S_OK) e o código de erro em um lResult da vida.

```cpp
STDMETHODIMP CService::Open(<params>, PLONG *pctReturn)
{
	if( DeuErrado() )
	{
		*pctReturn = ERR_DEU_ERRADO;
		return S_OK;
	}
	//...
}
 

```

O código retornado é 2Fh, e agora temos uma boa pista para encontrar a localização no fonte. A primeira coisa é encontrar o define responsável por esse erro, o que exige um pouco de familiaridade com o sistema, pois não se trata aqui de um código Windows.

```cpp
#define OSRL_ERR	44	/* Data file serial number overflow */
#define KLEN_ERR	45	/* Key length exceeds MAXLEN parameter */
#define	FUSE_ERR	46	/* File number already in use */
#define FINT_ERR	47	/* database has not been initialized */
#define FMOD_ERR	48	/* Operation incompatible with type of file */
#define	FSAV_ERR	49	/* Could not save file */
#define LNOD_ERR	50	/* Could not lock node */
 

```

Ótimo. 2F, para os leigos (leigos? o que vocês estão fazendo aqui?), é 47 em decimal, exatamente nosso código listado acima. Com esse define podemos agora procurar no código-fonte e analisar todas as funções que retornam esse código em seu início. Para nossa sorte, existe apenas uma.

```cpp
STDMETHODIMP CService::Open(BYTE *fileName, COUNT keyNo, COUNT *pctReturn)
{
	char szMsg[200];

	// Verifica se o banco de dados foi inicializado
	if (!_Main.m_bDBInitialized)
	{
		_Main.Log("Error opening file before database to be initialized.");
		*pctReturn = FINT_ERR;
		return S_OK;
	}

	// Verifica se o arquivo já foi aberto
	if (m_pData)
	{
		sprintf(szMsg, "Error on open file \"%s\". File already opened.");
		_Main.Log(szMsg);
		*pctReturn = ERR_BLABLABLA;
		return S_OK;
	}
	//...
}
 

```

Para confirmar que não estamos sonhando, podemos dar uma olhada no parâmetro passado para a função Log antes do código retornar. A memória deverá conter uma string idêntica a do código-fonte.

    
    Service+0x6073:
    00406073 6a00            push    0
    00406075 6860514100      push    offset Service+0x15160 (

00415160

    
    )
    0040607a b9609e4100      mov     ecx,offset Service+0x19e60 (00419e60)
    0040607f e822080000      call

Service+0x68a6

    
     (004068a6)
    00406084 8b4514          mov     eax,dword ptr [ebp+14h]
    00406087 66c7002f00      mov     word ptr [eax],2Fh
    0040608c eb65            jmp     Service+0x60f3 (004060f3)
    
    0:000> da

00415160

    
    00415160  "Error opening file before databa"
    00415180  "se to be initialized."

E, agora sim, encontramos o culpado!

[![](http://i.imgur.com/gUfPM5Q.jpg)](http://annahinks.tumblr.com/post/176676889)

Mais para a frente em minha análise consegui encontrar o objeto pelo qual todas as threads esperavam. Não tive tanta sorte, pois se tratava de um mutex, e [mutexes não conseguem ser rastreados tão facilmente em user mode](http://www.debuginfo.com/articles/easywindbg.html#debugdeadlocks). Mas isso não vem ao caso. O que tentei descrever aqui foi mais ou menos o processo que você deverá seguir caso tenha que analisar um binário compilado em outras vidas. Espero que você tenha tanta sorte quanto eu.
