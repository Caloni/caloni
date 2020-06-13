---
categories: [ "code" ]
date: "2020-04-10"
tags: [ "draft", "projects" ]
title: "Winmock"
---
Testar sistemas com rede simulada pode ser muito complexo ou muito simples. Se for feito em C ou se os endpoints forem em C é muito simples: basta trocar as funções originais pelas suas. Como tudo em C são funções com nome bem definido e assinatura flexível (você não precisa declarar a assinatura da função, ou pode mudar no meio do caminho).

Criei este pequeno projeto de mock da winsock para exemplificar. Ele utiliza um recurso interessante da winsock, um define chamado INCLWINSOCKAPIPROTOTYPES, que pode desabilitar a publicação das assinaturas das funções de socket do header winsock2.h. E por que isso é importante? Porque essas assinaturas já possuem a informação que essas funções deverão ser importadas de uma DLL (no caso a Ws232.dll). Isso muda o nome da função C. Além disso, a convenção de chamada da API do Windows é baseada em Pascal, e não cdecl, sendo a desvantagem não existir número de argumentos variáveis na pilha. Adiante veremos como isso é útil para simplificar nosso código de mock.

Em primeiro lugar vamos montar um projeto para iniciar um client socket para exemplificar o uso da winsock. Na verdade, de qualquer UNIX socket.

    #include "client.h"
    #include <stdio.h>
    
    #pragma comment(lib, "Ws2_32.lib")
    
    int main() {
      struct CONNECTION* conn = NULL;
      if (winmock_connect("caloni.com.br", 80, &conn) == 0)
      {
        char buffer[100];
        unsigned int timeout = 10;
        if (winmock_send(conn, "ping?", sizeof("ping?")-1) > 0)
        {
          if (winmock_receive(conn, buffer, sizeof("pong!")-1, &timeout) > 0)
          {
            if (memcmp(buffer, "pong!", sizeof("pong!")-1) == 0)
            {
              printf("everything is just fine\n");
            }
          }
        }
      }
    }

Esse código pode ser testado diretamente do Blogue do Caloni. Só que não. Ele não está apto no momento a retornar o conhecido ack do IRC. Um dia talvez. Mas no momento não. As funções com o prefixo winmock estão no projeto C client que usa as funções de socket para se comunicar com o servidor. Alguns snippets:

    int winmock_connect(const char* host, short port, struct CONNECTION** connection)
    {
        /*...*/
      conn.socket = (SOCKET) socket(AF_INET, SOCK_STREAM, 0);
      if (conn.socket < 0)
      {
        printf("Can't create socket\n");
        return -1;
      }
    
      sprintf(port_string, "%d", port);
      memset(&hints, 0, sizeof(hints));
      hints.ai_family = AF_INET;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_protocol = IPPROTO_TCP;
      result = getaddrinfo(host, port_string, &hints, &addr_result);
    
      if (addr_result == NULL ) {
        printf("Can't resolve server name.\n");
        return -1;
      }
      serv_addr = *(struct sockaddr_in*) addr_result->ai_addr;
      freeaddrinfo(addr_result);
    
      if (connect(conn.socket,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        /*...*/
    
    
    int winmock_send(struct CONNECTION* connection, const void* buffer, unsigned int len) {
      int ret = send(connection->socket, (const char*)buffer, len, 0);
        /*...*/
    
    
    int winmock_receive(struct CONNECTION* connection, void* buffer, int len, const unsigned* timeout_in_seconds) {
        /*...*/
          ret = select(0, &recvset, NULL, NULL, (timeout_in_seconds ? &tv : NULL));
        /*...*/  
        ret = recv(connection->socket, char_buffer + received, len - received, 0);

As funções C do winsock/socket, connect, send, recv, select, etc, são apenas funções C cujos nomes são conhecidíssimos. Elas são linkadas com programas que usam alguma biblioteca de socket. Nada impede que nós mesmos sobrescrevamos essas funções para implementá-las nós mesmos em nosso programa. É isso o que nosso projeto de unittest integrado faz, usando o define já citado para evitar que as funções winsock tomem o lugar.

    add_subdirectory("${PROJECT_SOURCE_DIR}/submodules/googletest" "submodules/googletest")
    
    macro(package_add_test TESTNAME)
        add_executable(${TESTNAME} ${ARGN})
        target_link_libraries(${TESTNAME} gtest gmock gtest_main ${TESTNAME}_lib)
        gtest_discover_tests(${TESTNAME} WORKING_DIRECTORY ${PROJECT_DIR} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}")
        set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
    endmacro()
    
    add_definitions(-DINCL_WINSOCK_API_PROTOTYPES=0)
    package_add_test(client_test client_unittest.cpp)
    add_library(client_test_lib STATIC client_mock.c ../client/client.c)
    target_include_directories(client_test PRIVATE)

A linha mais importante é "adddefinitions(-DINCLWINSOCKAPIPROTOTYPES=0)", que irá manter as assinaturas do header da winsock longe da compilação.

    /* winsock2.h */
    /*...*/
    #ifndef INCL_WINSOCK_API_PROTOTYPES
    #define INCL_WINSOCK_API_PROTOTYPES 1
    #endif
    
    #ifndef INCL_WINSOCK_API_TYPEDEFS
    #define INCL_WINSOCK_API_TYPEDEFS 0
    #endif
    
    /*...*/
    #if INCL_WINSOCK_API_PROTOTYPES
    WINSOCK_API_LINKAGE
    _Must_inspect_result_
    SOCKET
    WSAAPI
    accept(
        _In_ SOCKET s,
        _Out_writes_bytes_opt_(*addrlen) struct sockaddr FAR * addr,
        _Inout_opt_ int FAR * addrlen
        );
    #endif /* INCL_WINSOCK_API_PROTOTYPES */
    
    #if INCL_WINSOCK_API_TYPEDEFS
    typedef
    _Must_inspect_result_
    SOCKET
    (WSAAPI * LPFN_ACCEPT)(
        _In_ SOCKET s,
        _Out_writes_bytes_opt_(*addrlen) struct sockaddr FAR * addr,
        _Inout_opt_ int FAR * addrlen
        );
    #endif /* INCL_WINSOCK_API_TYPEDEFS */

Tanto a INCLWINSOCKAPIPROTOTYPES quanto a INCLWINSOCKAPITYPEDEFS podem ser muito úteis para incluir algumas coisas do header, mas não todas. E como os protótipos das funções winsock não estão disponíveis, podemos implementar as nossas:

    #if !INCL_WINSOCK_API_PROTOTYPES
    SOCKET socket(int af, int type, int protocol)
    {
      return socket_mock(af, type, protocol);
    }
    
    int send(SOCKET s,  const char FAR* buf,  int len,  int flags)
    {
      return send_mock(s, buf, len, flags);
    }
    
    int select(  int nfds,  fd_set FAR* readfds,  fd_set FAR* writefds,  fd_set FAR* exceptfds,  const struct timeval FAR* timeout)
    {
      return select_mock(nfds, readfds, writefds, exceptfds, timeout);
    }
    
    int recv(  SOCKET s,  char FAR* buf,  int len,  int flags)
    {
      return recv_mock(s, buf, len, flags);
    }
    #endif /* !INCL_WINSOCK_API_PROTOTYPES */

Com isso o linker irá usar nossas funções em vez da lib de winsock, e na execução podemos simular eventos e operações de rede. Para flexibilizar para que cada teste monte seu ambiente transformamos a implementação em chamadas de ponteiros de função que podem ser trocadas. Por padrão preenchemos esses ponteiros com uma função que não faz nada. Note que com a convenção de chamadas de C não precisamos especificar os argumentos e funções com diferentes tipos e números de parâmetros podem chamar a mesma função.

    #include "client_mock.h"
    
    int stub_mock() { return 0; }

    SOCKET(*socket_mock)(int af, int type, int protocol) = stub_mock;
    int (*send_mock)(SOCKET s, const char FAR* buf, int len, int flags) = stub_mock;
    int (*select_mock)(int nfds, fd_set FAR* readfds, fd_set FAR* writefds, fd_set FAR* exceptfds, const struct timeval FAR* timeout) = stub_mock;
    int (*recv_mock)(SOCKET s, char FAR* buf, int len, int flags) = stub_mock;
    

Agora é possível escrever um sistema de simulação do Blogue do Caloni que retorna o ack que precisamos para que o teste funcione.

extern "C" {
}

using namespace std;

static string lastsend;

extern "C" {

  int select_default(int nfds, fd_set FAR* readfds, fd_set FAR* writefds, fd_set FAR* exceptfds, const struct timeval FAR* timeout)
  {
    return 1;
  }

  int getaddrinfo_default(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA* pHints, PADDRINFOA* ppResult)
  {
    static struct addrinfo addr_result = {};
    static struct sockaddr sock_addr = { };
    addr_result.ai_addr = &sock_addr;
    *ppResult = &addr_result;
    return 0;
  }

  int send_default(SOCKET s, const char FAR* buf, int len, int flags)
  {
    string msg(buf, len);
    last_send = msg;
    return len;
  }

  int recv_default(SOCKET s, char FAR* buf, int len, int flags)
  {
    char pong[] = "pong!";

    if (last_send == "ping?")
    {
      if (len == sizeof("pong!") - 1 )
      {
        strcpy(buf, pong);
        return len;
      }
    }

    return 0;
  }
}

class clientTest : public ::testing::Test {
protected:
  clientTest() {
    getaddrinfo_mock = getaddrinfo_default;
    select_mock = select_default;
    send_mock = send_default;
    recv_mock = recv_default;
  };

  ~clientTest() override {
  }

  void SetUp() override {
  }

  void TearDown() override {
  }

  // your stuff
};

TESTF(clientTest, ConnectSendReceive)
{
  struct CONNECTION* conn = NULL;
  if (winmock_connect("caloni.com.br", 80, &conn) == 0)
  {
    char buffer[100];
    unsigned int timeout = 10;
    if (winmock_send(conn, "ping?", sizeof("ping?")-1) > 0)
    {
      if (winmock_receive(conn, buffer, sizeof("pong!")-1, &timeout) > 0)
      {
        if (memcmp(buffer, "pong!", sizeof("pong!")-1) == 0)
        {
          printf("everything is just fine\n");
        }
      }
    }
  }
}

Uma observação importante sobre getaddrinfo: ele não possui esse salvaguarda de define e irá dar erro no linker de redefinição. Porém, apenas se incluirmos o header onde ele é definido. Podemos nos proteger com o mesmo define no código-fonte original do client:

    #include <winsock2.h>
    #if INCL_WINSOCK_API_PROTOTYPES
    #include <ws2tcpip.h>
    #endif

    
Durante a compilação do unittest warnings como os abaixo aparecerão, mas não se preocupe, pois sabemos o que estamos fazendo.

    client.c(75,22): warning C4013: 'getaddrinfo' undefined; assuming extern returning int
    client.c(84,13): warning C4013: 'connect' undefined; assuming extern returning int
    client.c(98,16): warning C4013: 'send' undefined; assuming extern returning int
    client.c(144,13): warning C4013: 'recv' undefined; assuming extern returning int

Para se divertir brincando de rede de mentirinha, baixe o projeto completo.
