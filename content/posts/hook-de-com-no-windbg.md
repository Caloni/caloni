---
date: "2007-09-18"
title: Hook de COM no WinDbg
tags: [ "code" ]
---
Continuando com o tema hooks no WinDbg vamos aqui "hookear" e analisar as chamadas de métodos de um objeto COM. O que será feito aqui é o mesmo experimento feito para uma palestra de engenharia reversa que apresentei há um tempo atrás, mas com as opções de pause, rewind, replay e câmera lenta habilitadas.

Antes de começar, se você não sabe nada sobre COM, não deveria estar aqui, mas nunca é tarde para aprender. Pra começar, vamos dar uma olhada na representação da interface IUnknown em UML e em memória:

![Layout da VTable do IUnknown](/img/iunknown_disasm.png)

Como podemos ver, para implementar o polimorfismo os endereços das funções virtuais de uma classe são colocados em uma tabela, a chamada vtable, famosa tanto no COM quanto no C++. Existe uma tabela para cada classe-base polimórfica, e não para cada objeto. Se fosse para cada objeto não faria sentido deixar esses endereços "do lado de fora" do leiaute. E não seria nada simples e elegante fazer uma cópia desse objeto.

Assim, quando você chama uma função virtual de um objeto o código em assembly irá chamar o endereço que estiver na posição correspondente ao método chamado dentro da vtable. Se você chama AddRef, por exemplo, que é o segundo método na tabela, será chamado o endereço da posição número dois. Com isso, mesmo desconhecendo de que tipo é o objeto a função certa será chamada porque existe um ponteiro para essa tabela no início da interface.

Sabendo de tudo isso, agora sabemos como teoricamente proceder para colocar uns breakpoints nessas chamadas:

![Breakpoints na VTable](/img/iunknown_breakpoint.png)

Note que o breakpoint não é colocado dentro da tabela, o que seria absurdo. Uma tabela são dados e dados geralmente não são executados (eu disse geralmente). Porém, usamos a tabela para saber onde está o começo da função para daí colocar a parada nesse endereço, que por fazer parte do código da função é (quem diria!) executado.

Agora vamos sair da teoria e tentar fazer as coisas mais ou menos parecidas na prática. O nosso sorteado desse artigo foi o IMalloc, a interface de alocação de memória do COM, que existe desde a época em que não se sabia direito pra que esse tal de COM iria servir. O IMalloc é definido como se segue:

    MIDL_INTERFACE("00000002-0000-0000-C000-000000000046")
    IMalloc : public IUnknown
    {
      public:
      virtual void *STDMETHODCALLTYPE Alloc( 
        /* [in] */ SIZE_T cb) = 0;
    
      virtual void *STDMETHODCALLTYPE Realloc( 
        /* [in] */ void *pv,
        /* [in] */ SIZE_T cb) = 0;
    
      virtual void STDMETHODCALLTYPE Free( 
        /* [in] */ void *pv) = 0;
    
      virtual SIZE_T STDMETHODCALLTYPE GetSize( 
        /* [in] */ void *pv) = 0;
    
      virtual int STDMETHODCALLTYPE DidAlloc( 
        void *pv) = 0;
    
      virtual void STDMETHODCALLTYPE HeapMinimize(void) = 0;
    };

Nesse experimento, como iremos interceptar quando alguém aloca ou desaloca memória, nossos alvos são os métodos Alloc e Free. Para saber onde eles estão na tabela, é só contar, começando pelos métodos do IUnknown, que é de quem o IMalloc deriva. Se houvessem mais derivações teríamos que contar da primeira interface até a última. Portanto: QueryInterface um, AddRef dois, Release três, Alloc quatro, Realloc cinco, Free seis. OK. Contar foi a parte mais fácil.

Agora iremos precisar interceptar primeiro a função que irá retornar essa interface, pois do contrário não saberemos onde fica a vtable. Nesse caso, a função é a ole32!CoGetMalloc. Muitas vezes você irá usar a ole32!CoCreateInstance(Ex) ou a CoGetClassObject diretamente na DLL que pretende interceptar. Outras vezes, você receberá o ponteiro em alguma ocasião diversa. O importante é conseguir o ponteiro de alguma forma.

Nesse exemplo iremos obter o ponteiro através de um aplicativo de teste trivial, ignorando todas aquelas proteções antidebugging que podem estar presentes no momento da reversa, feitos por alguém que lê meu blog (quanta pretensão!):

    /** @brief A stupid sample to 
      show WinDbg COM hooking! */
    #include <windows.h>
    #include <objbase.h>
    #include <objidl.h>
     
    int main()
    {
      CoInitialize(NULL);
      IMalloc* malloc = 0;
    
      if( CoGetMalloc(1, &malloc) == 0 )
      {
        if( void* pAlloc 
          = malloc->Alloc(0x1000) )
        {
          malloc->Free(pAlloc);
        }
    
        malloc->Release();
      }
    
      CoUninitialize();
    } 

Vamos fazer de conta que é desnecessário dizer como se compila o fonte acima.

    
    cl /c imalloc-hook.cpp
    link imalloc-hook.obj ole32.lib

Agora é só depurar!

Abra o WinDbg. Na opção "File, Open Executable" selecionamos a nossa vítima, cujo nome você escolhe na hora de compilar o fonte acima. Aqui ele irá chamar imalloc-hook.exe. A seguir, colocamos um breakpoint na função da ole32, mandamos rodar, e esperamos a parada do código:

    0:000> bp ole32!CoGetMalloc
    0:000> bl
    0 e 774ddcf8 0001 (0001) 0:**** ole32!CoGetMalloc
    0:000> g
    Breakpoint 0 hit
    ModLoad: 76360000 7637d000 C:WINDOWSsystem32IMM32.DLL
    ...
    ModLoad: 746e0000 7472b000 C:WINDOWSsystem32MSCTF.dll
    eax=0012ff7c ebx=00000000 ecx=775e67f0 edx=775e67f0 esi=00000001 edi=00403374
    eip=774ddcf8 esp=0012ff70 ebp=0012ffc0 iopl=0 nv up ei pl zr na pe nc
    cs=001b ss=0023 ds=0023 es=0023 fs=003b gs=0000 efl=00000246
    ole32!CoGetMalloc:
    774ddcf8 8bff mov edi,edi

Maravilha. Alguém chamou a função que queríamos (quem será?). Agora podemos dar uma olhada na pilha e no protótipo da CoGetMalloc:
    
    HRESULT CoGetMalloc(DWORD dwMemContext, LPMALLOC *ppMalloc);

    0:000> dd esp L3
    0012ff70 0040101d 00000001 0012ff7c
    0:000> dd poi(esp+8) L1
    0012ff7c  00000000

Como podemos ver nos parâmetros da pilha o nosso chamador passou certinho o valor 1 no campo reservado e um ponteiro no segundo parâmetro para uma área onde, se der tudo certo, será escrito o endereço de um IMalloc, que podemos chamar carinhosamente de this. De início vemos que a variável está zerada. Agora vamos executar a função até a saída e examinar os resultados.
    
    0:000> bp /1 /c @$csp @$ra;g
    Breakpoint 1 hit
    eax=00000000 ebx=00000000 ecx=775e6034 edx=775e67f0 esi=00000001 edi=00403374
    eip=0040101d esp=0012ff7c ebp=0012ffc0 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    IMalloc+0x101d:
    0040101d 85c0         test    eax,eax
    0:000> dd 0012ff7c L1  ; o endereço da variável
    0012ff7c  775e6034     ; o endereço da interface
    0:000> dd 775e6034 L1  ; onde está a vtable?
    775e6034  775e600c     ; o endereço da vtable
    0:000> dd 775e600c
    775e600c  77562cfb 774dcf29 774dcf29 774dd00d ; a vtable ! ! !
    775e601c  774dd665 774dcfe8 774dd400 77562d46 ; a vtable ! ! !
    775e602c  77562d6e 775e6034 775e600c 774c0000 ; a vtable ! ! !
    775e603c  00000000 00000000 00154d70 774cbff4
    775e604c  00000000 00000000 00000000 00000000
    ...

E não é que tudo deu certo? A variável foi preenchida, e partir dela demos uma espiadela nos endereços das funções da vtable. Nós pegamos o valor da variável que foi preenchida (o endereço da interface) e obtemos os seus primeiros 4 bytes (o endereço da vtable) e listamos o seu conteúdo (a própria vtable!). Agora basta usarmos o resultados de nossas contagens lá em cima e colocarmos os breakpoints nas funções corretas. E mandar rodar. E analisar os resultados.

    0:000> bp 774dd00d ".echo IMalloc::Alloc"
    0:000> bp 774dcfe8 ".echo IMalloc::Free"
    0:000> g
    IMalloc::Alloc
    eax=775e6034 ebx=00000000 ecx=775e600c edx=774dd00d esi=00000001 edi=00403374
    eip=774dd00d esp=0012ff70 ebp=0012ffc0 iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    ole32!IsValidIid+0xe4:
    774dd00d 8bff            mov     edi,edi
    0:000> dd esp L3
    0012ff70  <strong>00401031 775e6034 00001000</strong> ; o this é nosso, e foi pedido para alocar 4KB (0x1000)
    0:000> bp /1 /c @$csp @$ra;g ; Step Out para pegar o retorno
    Breakpoint 3 hit
    eax=001597f0 ebx=00000000 ecx=7c9106eb edx=00150608 esi=00000001 edi=00403374
    eip=00401031 esp=0012ff7c ebp=0012ffc0 iopl=0         nv up ei pl nz na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000206
    IMalloc+0x1031:
    00401031 85c0            test    eax,eax
    0:000> reax
    eax=001597f0 ; esse é o endereço da memória alocada
    g
    IMalloc::Free
    eax=774dcfe8 ebx=00000000 ecx=775e6034 edx=775e600c esi=00000001 edi=00403374
    eip=774dcfe8 esp=0012ff70 ebp=0012ffc0 iopl=0         nv up ei pl nz na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000206
    ole32!IsValidIid+0xbf:
    774dcfe8 8bff            mov     edi,edi
    0:000> dd esp L3
    0012ff70  <strong>00401041 775e6034 001597f0</strong> ; nosso this e endereço alocado (pedindo pra desalocar)
    g ; é isso aí

Note que a função pode eventualmente ser chamada internamente (pelo próprio objeto) ou até por outro objeto que não estamos interessados em interceptar (lembre-se que os métodos de uma classe são compartilhados por todos os objetos). Por isso é importante sempre dar uma olhada no primeiro parâmetro, que é o this que obtemos primeiramente.

Com isso termina o nosso pequeno experimento de como é possível interceptar chamadas COM simplesmente contando e usando o WinDbg. OK, talvez um pouquinho a mais, mas nada de quebrar a cabeça.
