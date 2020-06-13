---
categories: [ "code" ]
date: "2020-04-05"
tags: [ "draft",  ]
title: "Golang e C"
---
É muito difícil configurar a linguagem Go no ambiente Windows para compilar código C. O único ambiente de compilação que o projeto leva a sério são os ports do GCC, e não o Visual Studio, que seria a ferramenta nativa. Dessa forma, realizei boa parte das travessuras desse artigo em Linux, usando o WSL com a distro Ubuntu ou CentOS. Deve funcionar em qualquer Unix da vida.

A linguagem Go na versão mais nova precisa que seja definida através da cgo, o backend C do ambiente de build da linguagem, uma função trampolim, que é uma função escrita em C que irá chamar uma função escrita em Go. Essa função pode ser passada como parâmetro de callback para uma biblioteca C que quando a biblioteca C chamar esse ponteiro de função ele irá atingir a função trampolim, que por sua vez, chama a função Go, que é onde queremos chegar depois de todo esse malabarismo.

Em resumo: o main em Go chama C.setcallback (função C exportada) passando o endereço do seu callback (em cgo) e em uma segunda chamada ou nessa mesma pede para chamar esse callback. O módulo em C pode ou não chamar essa função nessa thread ou mais tarde, através do ponteiro de função que estocou (gcallback). Ao chamá-la, ativará a função GoCallbackcgo, que por sua vez chamará GoCallback, essa sim, já no módulo Go (embora ambas estejam no mesmo executável, já que C e Go podem ser linkados juntos de maneira transparente.

    +----------+
    |   main   |
    +----------+
          |
    +----------------+
    | C.set_callback |
    +----------------+
          |
    +-----------------+
    | C.call_callback |
    +-----------------+
          |
    +---------------------------+
    | g_callback (func pointer) |
    +---------------------------+
          |
    +----------------+
    | GoCallback_cgo |
    +----------------+
          |
    +------------+
    | GoCallback |
    +------------+

O módulo em Go precisa de um forward declaration para a função cgo e precisa exportar a função Go que será chamada por ela através do importantíssimo comentário export antes da função (se retirado este comentário a solução para de funcionar):

    package main
    
    import (
    	"unsafe"
    	"fmt"
    )
    
    //#cgo CFLAGS: -I.
    //#cgo LDFLAGS: -L.
    ////#cgo pkg-config: some-lib-that-uses-pkg-config
    //#include "golang_c.h"
    //void GoCallback_cgo(int result, void* vpointer, const char* cstring, struct STRUCT* cstruct); // Forward declaration
    import "C"
    
    //export GoCallback
    func GoCallback(result int, vpointer unsafe.Pointer, cstring *C.char, cstruct *C.struct_STRUCT) {
    	vpointer_to_gostring := C.GoString((*C.char)(vpointer))
        gostring := C.GoString(cstring)
        key := "empty"
        value := "empty"
        if cstruct != nil {
            key = C.GoString(cstruct.key)
            value = C.GoString(cstruct.value)
        }
    	fmt.Printf("Go: callback called; result:[%d], vpointer:[%s], cstring:[%s], cstruct:[%p], cstruct.key:[%s], cstruct.value:[%s]\n",
            result, vpointer_to_gostring, gostring, cstruct, key, value)
    }
    
    func main() {
    	string := "some string"
    	var vpointer *C.char = C.CString("some string as vpointer")
    
    	fmt.Printf("Go: setting callback at %p\n", unsafe.Pointer(C.GoCallback_cgo));
    	C.set_callback((C.Callback)(unsafe.Pointer(C.GoCallback_cgo)))
    
    	fmt.Printf("Go: calling callback at %p passing result:[%d], vpointer:[%p], cstring:[%s]\n", unsafe.Pointer(C.GoCallback_cgo), 5, unsafe.Pointer(vpointer), C.CString(string))
    	var result = C.call_callback(5, unsafe.Pointer(vpointer), C.CString(string))
    	fmt.Printf("Go: callback returned %d\n", result)
    }
    

O módulo trampolim de Go é muito simples. Além de incluir o mesmo header em C para os tipos especificados ali, ela faz uma foward declaration da função do módulo Go anterior e chama esta função, repassando a chamada para o mundo Go.

    package main
    
    /*
    #include "golang_c.h"
    
    // The gateway functions
    //
    
    void GoCallback_cgo(int result, void* vpointer, const char* cstring, struct STRUCT* cstruct) {
    	void GoCallback(int result, void* vpointer, const char* cstring, struct STRUCT* cstruct);
    	GoCallback(result, vpointer, cstring, cstruct);
    }
    */
    import "C"

Mais uma vez há algo extremamente importante nos detalhes: a chamada import "C" logo após o código dentro dos comentários desse módulo.

O resto é C padrão. O header define os tipos (inclusive do callback) e as funções exportadas:

    struct STRUCT {
        const char* key;
        const char* value;
    };
    
    typedef int (*Callback)(int /*result*/, void* /*vpointer*/, const char* /*cstring*/, struct STRUCT* /*cstruct*/);
    
    void set_callback(Callback callback);
    int call_callback(int result, void* vpointer, const char* cstring);
    
A parte C apenas implementa as funções:

    #include "golang_c.h"
    #include <stdio.h>
    
    Callback g_callback = NULL;
    
    void set_callback(Callback callback) {
        printf("C: callback set to %p\n", callback);
        g_callback = callback;
    }
    
    int call_callback(int result, void* vpointer, const char* cstring) {
        struct STRUCT s = { "key", "value" };
        if( g_callback ) {
            printf("C: calling callback at %p passing result:[%d], vpointer:[%p], cstring:[%s], cstruct:[%p]\n", g_callback, result, vpointer, cstring, &s);
            result = g_callback(result, vpointer, cstring, &s);
            printf("C: callback at %p called; result:[%d]\n", g_callback, result);
        } else {
            printf("C: no callback to call\n");
        }
        return result;
    }
    
E para exportar essas funções basta um arquivo def no projeto:

    LIBRARY
    	EXPORTS
    		set_callback
    		call_callback

O CMakeLists.txt deste projeto pode apenas especificar qual o tipo de biblioteca. Não há nada de especial na parte C. Ou seja, funciona com qualquer código que você saiba as assinaturas das funções.

    cmake_minimum_required(VERSION 2.6)
    PROJECT(GOLANG_C)
    ADD_LIBRARY(GOLANG_C SHARED golang_c.c golang_c.def)

Após compilar ambas as soluções na mesma pasta (considerando que foi criada uma subpasta onde estão esses fontes) basta executar o binário Go e ver a mágica funcionando. No meu caso, tive que executar tudo no WSL. Ainda preciso ver como configura essa bagaça de Go no Windows.

    C:\Users\caloni\blog\static\sources\golang_c>bash
    caloni@SUSE:/mnt/c/Users/caloni/blog/static/sources/golang_c$ mkdir build && cd build
    caloni@SUSE:/mnt/c/Users/caloni/blog/static/sources/golang_c/build$ cmake ..
    -- The C compiler identification is GNU 7.5.0
    -- The CXX compiler identification is GNU 7.5.0
    -- Check for working C compiler: /usr/bin/cc
    -- Check for working C compiler: /usr/bin/cc -- works
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Check for working CXX compiler: /usr/bin/c++
    -- Check for working CXX compiler: /usr/bin/c++ -- works
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /mnt/c/Users/caloni/blog/static/sources/golang_c/build
    caloni@SUSE:/mnt/c/Users/caloni/blog/static/sources/golang_c/build$ make
    Scanning dependencies of target GOLANG_C
    [ 50%] Building C object CMakeFiles/GOLANG_C.dir/golang_c.c.o
    [100%] Linking C shared library libGOLANG_C.so
    [100%] Built target GOLANG_C
    caloni@SUSE:/mnt/c/Users/caloni/blog/static/sources/golang_c/build$ go build ..
    caloni@SUSE:/mnt/c/Users/caloni/blog/static/sources/golang_c/build$ ls
    CMakeCache.txt  CMakeFiles  Makefile  cmake_install.cmake  golang_c  libGOLANG_C.so
    caloni@SUSE:/mnt/c/Users/caloni/blog/static/sources/golang_c/build$ ./golang_c
    Go: setting callback at 0x486470
    C: callback set to 0x486470
    Go: calling callback at 0x486470 passing result:[5], vpointer:[0x24937e0], cstring:[%!s(*main._Ctype_char=0x2493a10)]
    C: calling callback at 0x486470 passing result:[5], vpointer:[0x24937e0], cstring:[some string], cstruct:[0x7fffea681e80]
    Go: callback called; result:[5], vpointer:[some string as vpointer], cstring:[some string], cstruct:[0x7fffea681e80], cstruct.key:[key], cstruct.value:[value]
    C: callback at 0x486470 called; result:[0]
    Go: callback returned 0
    caloni@SUSE:/mnt/c/Users/caloni/blog/static/sources/golang_c/build$                                                                         

Criei um repositório com os fontes deste artigo. Bom proveito =)
