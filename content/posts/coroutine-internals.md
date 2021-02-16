---
date: 2018-09-18
title: "Coroutine Internals"
tags: [ "draft", "code" ]
desc: "Visual Studio, Boost.Coroutine, debug/depuração, crash analysis."
---
Uma corrotinas é um mecanismo de troca de contexto onde apenas uma thread está envolvida. Ela me faz lembrar do Windows 3.0, não exatamente por não existirem threads (e não existiam mesmo), mas pelo caráter cooperativo dos diferentes códigos.

Só que no caso do Windows se a rotina de impressão travasse todo o sistema congelava.

A volta das corrotinas via C++ moderno ocorre, para variar, no Boost. E a arquitetura é simples: mantenha um histórico das stacks das diferentes tasks da thread. Vamos pegar o caso mais simples da Boost.Coroutine para analisar:

```cpp
#define BOOST_COROUTINES_NO_DEPRECATION_WARNING // Já existe uma nova versão de Coroutine, a 2, e a 1 está sendo abandonada.
#include <boost/coroutine/all.hpp>
#include <iostream>

using namespace boost::coroutines;

void cooperative(coroutine<void>::push_type &sink)
{
    std::cout << "Hello";
    sink();
    std::cout << "world";
}

int main()
{
    coroutine<void>::pull_type source{ cooperative };
    std::cout << ", ";
    source();
    std::cout << "!\n";
}
```

Se você já é um programador esperto já deve ter percebido que na saída do prompt será impresso "Hello, world!", com a vírgula no meio sendo impressa pela função main e as duas palavras da ponta pela função cooperative, ainda que ela seja chamada apenas uma vez.

Note que falei chamada porque se a stack não retornou da função ela não terminou ainda seu trabalho. Não houve o "return". Outra forma de entender isso é que ela é chamada aos poucos. Enfim, deixo para você a discussão semântica. O fato é que a saída é "Hello, world":

![](https://i.imgur.com/bPO1fFa.png)

Vamos depurar.

![](https://i.imgur.com/WJeFtYq.png)

Oh, oh! A stack de cooperative nos indica que ela não partiu do main, apesar de ter sido chamada através da construção de coroutine<void>::pull_type. O método sink chamado logo após imprimir "Hello" deve colocar essa rotina para dormir, voltando o controle para main. Vamos ver como isso é feito.

<div class="auto-resizable-iframe"><div><iframe frameborder="0" allowfullscreen="1" src="https://www.youtube.com/embed/xoAxig6vdTM"></iframe></div></div>

Oh, não. O depurador do Visual Studio está fazendo caquinha, pois rodando passo-a-passo voltei para a mesma função cooperative sem passar pelo main. No entanto, a vírgula ", " foi impressa.

![](https://i.imgur.com/S1Ywlhl.png)

Para conseguirmos depurar diferentes rotinas dentro da mesma thread é imperativo entendermos como o mecanismo de troca de contexto funciona por baixo dos panos. Para isso nada como depurar as próprias trocas de contexto.

```cpp
typedef void ( * coroutine_fn)( push_coroutine< void > &);

explicit pull_coroutine( coroutine_fn fn, attributes const& attrs = attributes() )
{
    // create a stack-context
    stack_context stack_ctx;
    stack_allocator stack_alloc;
    // allocate the coroutine-stack
    stack_alloc.allocate( stack_ctx, attrs.size);
    BOOST_ASSERT( 0 != stack_ctx.sp);
    // typedef of internal coroutine-type
    typedef detail::pull_coroutine_object<
        push_coroutine< void >, void, coroutine_fn, stack_allocator
    >                                       object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            boost::forward< coroutine_fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
    impl_->pull();
}
```

O tamanho total da stack reservada no Windows é de 1 MB, mas a granuralidade padrão é de 64 KB ("que é suficiente para qualquer um" - Gates, Bill). Então é por isso que quando o Boost aloca uma stack com atributos padrões esse é o tamanho que vemos (65536).

> The default size for the reserved and initially committed stack memory is specified in the executable file header. Thread or fiber creation fails if there is not enough memory to reserve or commit the number of bytes requested. The default stack reservation size used by the linker is 1 MB. To specify a different default stack reservation size for all threads and fibers, use the STACKSIZE statement in the module definition (.def) file. The operating system rounds up the specified size to the nearest multiple of the system's allocation granularity (typically 64 KB). To retrieve the allocation granularity of the current system, use the GetSystemInfo function.

![](https://i.imgur.com/0dMVf0k.png)

_Detalhe curioso de arquitetura x86 (32 bits): na hora de alocar, o sp (stack pointer) aponta para o final da pilha. Isso porque no x86 a **pilha cresce "para baixo"**._

```cpp
ctx.sp = static_cast< char * >( limit) + ctx.size;
```
Logo em seguida, no topo da pilha, é empilhado o objeto da corrotina:

```cpp
typedef pull_coroutine_object<push_coroutine, coroutine_fn, stack_allocator> object_t;
void * sp = static_cast<char*>(stack_ctx.sp) - sizeof( object_t);
impl_ = new (sp) object_t(boost::forward<coroutine_fn>(fn), attrs, detail::preallocated(sp, size, stack_ctx), stack_alloc); 
```

Bom, entrando mais a fundo na implementação de corrotinas do Boost, temos o objeto **pull_coroutine_impl**, que possui flags, ponteiro para exceção e o contexto do chamador e do chamado para se localizar.

```cpp
template<>
class pull_coroutine_impl< void > : private noncopyable
{
protected:
    int                     flags_;
    exception_ptr           except_;
    coroutine_context   *   caller_;
    coroutine_context   *   callee_;
```

O **coroutine_context** possui elementos já conhecidos de quem faz hook de função: trampolins. Ou seja, funções usadas para realizar saltos incondicionais de um ponto a outro do código independente de contexto. Na minha época de hooks isso se fazia alocando memória na heap e escrevendo o código assembly necessário para realizar o pulo, geralmente de uma colinha de uma função naked (funções naked não possuem prólogo e epílogo, que são partes do código que montam e desmontam contextos dentro da pilha, responsável pela montagem dos frames com ponto de retorno, variáveis locais, argumentos).

```cpp
// class hold stack-context and coroutines execution-context
class BOOST_COROUTINES_DECL coroutine_context
{
private:
    template< typename Coro >
    friend void trampoline( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_void( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_pull( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_push( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_push_void( context::detail::transfer_t);

    preallocated            palloc_;
    context::detail::fcontext_t     ctx_;
```

A função que faz a mágica do pulo do gato é a pull, que muda o estado da rotina para running e realiza o salto de contexto. Vamos analisar essa parte com muita calma.

```cpp
inline void pull()
{
    BOOST_ASSERT( ! is_running() );
    BOOST_ASSERT( ! is_complete() );

    flags_ |= flag_running;
    param_type to( this);
    param_type * from(
            static_cast< param_type * >(
                caller_->jump(
                    * callee_,
                    & to) ) );
    flags_ &= ~flag_running;
    if ( from->do_unwind) throw forced_unwind();
    if ( except_) rethrow_exception( except_);
}
```

Quem desfaz a mágica, "desempilhando" o contexto para voltar ao chamador da corrotina (através do contexto apenas, não da pilha) é a função push.

```cpp
inline void push()
{
    BOOST_ASSERT( ! is_running() );
    BOOST_ASSERT( ! is_complete() );

    flags_ |= flag_running;
    param_type to( this);
    param_type * from(
            static_cast< param_type * >(
                caller_->jump(
                    * callee_,
                    & to) ) );
    flags_ &= ~flag_running;
    if ( from->do_unwind) throw forced_unwind();
    if ( except_) rethrow_exception( except_);
}
```

Com os dados disponíveis nos objetos de contexto (no exemplo do main, a variável source) é possível pelo Windbg analisar qualquer tipo de stack com o comando **k**.

![](https://i.imgur.com/mDcM4jk.png)

A variável de uma coroutine contém o contexto do chamador e do chamado. Quando houver a necessidade de explorar uma pilha não-ativa é preciso obter o valor de **sp** através dessa variável. Ela fica um pouco escondida, mas está lá. Acredite.

![](https://i.imgur.com/uQ7WYl8.png)

Usando o comando `k = BasePtr StackPtr InstructionPtr` passando o conteúdo de sp como o stack pointer o Windbg deve mostrar a pilha de todas as formas possíveis (especificar se terá FPO, mostrar código-fonte, argumentos, etc). Para a demonstração live fica bom ter um loop "eterno" para poder repetir a análise quantas vezes forem necessárias:

```cpp
void cooperative(coroutine<void>::push_type &sink)
{
    while( g_stopAll == false )
    {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
        sink();
        std::cout << "Hello";
        boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
        sink();
        std::cout << "world";
    }
}

int main()
{
    coroutine<void>::pull_type source{ cooperative };

    while( g_stopAll == false )
    {
        source();
        std::cout << ", ";
        source();
        std::cout << "!\n";
    }
}
```

![](https://i.imgur.com/bBIzRrm.png)

```
0:000> ~kvn
 # ChildEBP RetAddr  Args to Child              
00 00b707c4 00f39668 00b708c8 075d31e5 00b70a08 coroutines_cooperative!cooperative+0xa0 (FPO: [Non-Fpo]) (CONV: cdecl) [c:\projects\caloni\static\samples\coroutines_cooperative\coroutines_cooperative.cpp @ 19] 
01 00b70910 00f18b5b cdcdcdcd cdcdcdcd 00f01fd2 coroutines_cooperative!boost::coroutines::detail::pull_coroutine_object<boost::coroutines::push_coroutine<void>,void,void (__cdecl*)(boost::coroutines::push_coroutine<void> &),boost::coroutines::basic_standard_stack_allocator<boost::coroutines::stack_traits> >::run+0xf8 (FPO: [Non-Fpo]) (CONV: thiscall) [c:\libs\vcpkg\installed\x86-windows\include\boost\coroutine\detail\pull_coroutine_object.hpp @ 281] 
*** ERROR: Symbol file could not be found.  Defaulted to export symbols for C:\Projects\caloni\static\samples\coroutines_cooperative\Debug\boost_context-vc141-mt-gd-x32-1_67.dll - 
02 00b70a08 54261075 0075f4f0 0075f528 ffffffff coroutines_cooperative!boost::coroutines::detail::trampoline_pull<boost::coroutines::detail::pull_coroutine_object<boost::coroutines::push_coroutine<void>,void,void (__cdecl*)(boost::coroutines::push_coroutine<void> &),boost::coroutines::basic_standard_stack_allocator<boost::coroutines::stack_traits> > >+0x9b (FPO: [Non-Fpo]) (CONV: cdecl) [c:\libs\vcpkg\installed\x86-windows\include\boost\coroutine\detail\trampoline_pull.hpp @ 42] 
WARNING: Stack unwind information not available. Following frames may be wrong.
03 00b70a14 ffffffff 77c49ec1 cdcdcdcd cdcdcdcd boost_context_vc141_mt_gd_x32_1_67!make_fcontext+0x75
...
0a 00b70a30 00000000 00000000 00000000 00b70a48 coroutines_cooperative!boost::coroutines::detail::pull_coroutine_object<boost::coroutines::push_coroutine<void>,void,void (__cdecl*)(boost::coroutines::push_coroutine<void> &),boost::coroutines::basic_standard_stack_allocator<boost::coroutines::stack_traits> >::`vftable'
.detach
```

_Dica: É importante detachar do processo, mesmo que estejamos analisando em modo não-invasivo, porque a porta de Debug pode ser ocupada e o Visual Studio vai ficar pra sempre esperando receber eventos de debug que ele não vai mais receber._

Após rodarmos novamente o programa ele pára no main. Podemos atachar com o WinDbg quantas vezes precisarmos:

```
0:000> ~*kvn

.  0  Id: 1b50.a58 Suspend: 1 Teb: 00b8c000 Unfrozen
 # ChildEBP RetAddr  Args to Child              
00 00cff9cc 00f3cc8e 00000001 030b6998 030b84d8 coroutines_cooperative!main+0x9a (FPO: [Non-Fpo]) (CONV: cdecl) [c:\projects\caloni\static\samples\coroutines_cooperative\coroutines_cooperative.cpp @ 32] 
01 00cff9e0 00f3cb27 3c5cdfac 00f02a9a 00f02a9a coroutines_cooperative!invoke_main+0x1e (FPO: [Non-Fpo]) (CONV: cdecl) [f:\dd\vctools\crt\vcstartup\src\startup\exe_common.inl @ 78] 
02 00cffa3c 00f3c9bd 00cffa4c 00f3cd08 00cffa60 coroutines_cooperative!__scrt_common_main_seh+0x157 (FPO: [Non-Fpo]) (CONV: cdecl) [f:\dd\vctools\crt\vcstartup\src\startup\exe_common.inl @ 288] 
03 00cffa44 00f3cd08 00cffa60 760f8654 00b89000 coroutines_cooperative!__scrt_common_main+0xd (FPO: [Non-Fpo]) (CONV: cdecl) [f:\dd\vctools\crt\vcstartup\src\startup\exe_common.inl @ 331] 
04 00cffa4c 760f8654 00b89000 760f8630 af8d0600 coroutines_cooperative!mainCRTStartup+0x8 (FPO: [Non-Fpo]) (CONV: cdecl) [f:\dd\vctools\crt\vcstartup\src\startup\exe_main.cpp @ 17] 
05 00cffa60 77c24a47 00b89000 7348514c 00000000 KERNEL32!BaseThreadInitThunk+0x24 (FPO: [Non-Fpo])
06 00cffaa8 77c24a17 ffffffff 77c49ee4 00000000 ntdll!__RtlUserThreadStart+0x2f (FPO: [SEH])
07 00cffab8 00000000 00f02a9a 00b89000 00000000 ntdll!_RtlUserThreadStart+0x1b (FPO: [Non-Fpo])
```
