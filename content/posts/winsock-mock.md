---
categories: [ "code" ]
date: "2020-04-10"
link: "https://github.com/Caloni/winmock"
tags: [ "draft", "projects" ]
title: "Winmock"
---
Testar sistemas com rede simulada pode ser muito complexo ou muito simples. Se for feito em C ou se os endpoints forem em C é muito simples: basta trocar as funções originais pelas suas. Como tudo em C são funções com nome bem definido e assinatura flexível (você não precisa declarar a assinatura da função, ou pode mudar no meio do caminho).

Criei este pequeno projeto de mock da winsock para exemplificar. Ele utiliza um recurso interessante da winsock, um define chamado INCLWINSOCKAPIPROTOTYPES, que pode desabilitar a publicação das assinaturas das funções de socket do header winsock2.h. E por que isso é importante? Porque essas assinaturas já possuem a informação que essas funções deverão ser importadas de uma DLL (no caso a Ws232.dll). Isso muda o nome da função C. Além disso, a convenção de chamada da API do Windows é baseada em Pascal, e não cdecl, sendo a desvantagem não existir número de argumentos variáveis na pilha. Adiante veremos como isso é útil para simplificar nosso código de mock.

Em primeiro lugar vamos montar um projeto para iniciar um client socket para exemplificar o uso da winsock. Na verdade, de qualquer UNIX socket.


Esse código pode ser testado diretamente do Blogue do Caloni. Só que não. Ele não está apto no momento a retornar o conhecido ack do IRC. Um dia talvez. Mas no momento não. As funções com o prefixo winmock estão no projeto C client que usa as funções de socket para se comunicar com o servidor. Alguns snippets:


As funções C do winsock/socket, connect, send, recv, select, etc, são apenas funções C cujos nomes são conhecidíssimos. Elas são linkadas com programas que usam alguma biblioteca de socket. Nada impede que nós mesmos sobrescrevamos essas funções para implementá-las nós mesmos em nosso programa. É isso o que nosso projeto de unittest integrado faz, usando o define já citado para evitar que as funções winsock tomem o lugar.


A linha mais importante é "adddefinitions(-DINCLWINSOCKAPIPROTOTYPES=0)", que irá manter as assinaturas do header da winsock longe da compilação.


Tanto a INCLWINSOCKAPIPROTOTYPES quanto a INCLWINSOCKAPITYPEDEFS podem ser muito úteis para incluir algumas coisas do header, mas não todas. E como os protótipos das funções winsock não estão disponíveis, podemos implementar as nossas:


Com isso o linker irá usar nossas funções em vez da lib de winsock, e na execução podemos simular eventos e operações de rede. Para flexibilizar para que cada teste monte seu ambiente transformamos a implementação em chamadas de ponteiros de função que podem ser trocadas. Por padrão preenchemos esses ponteiros com uma função que não faz nada. Note que com a convenção de chamadas de C não precisamos especificar os argumentos e funções com diferentes tipos e números de parâmetros podem chamar a mesma função.



Agora é possível escrever um sistema de simulação do Blogue do Caloni que retorna o ack que precisamos para que o teste funcione.

extern "C" {
}

using namespace std;

static string lastsend;

extern "C" {

  int select_default(int nfds, fd_set FAR* readfds, fd_set FAR* writefds, fd_set FAR* exceptfds, const struct timeval FAR* timeout)
  {
  }

  int getaddrinfo_default(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA* pHints, PADDRINFOA* ppResult)
  {
  }

  int send_default(SOCKET s, const char FAR* buf, int len, int flags)
  {
  }

  int recv_default(SOCKET s, char FAR* buf, int len, int flags)
  {


  }
}

class clientTest : public ::testing::Test {
protected:
  clientTest() {
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
  }
}

Uma observação importante sobre getaddrinfo: ele não possui esse salvaguarda de define e irá dar erro no linker de redefinição. Porém, apenas se incluirmos o header onde ele é definido. Podemos nos proteger com o mesmo define no código-fonte original do client:


Durante a compilação do unittest warnings como os abaixo aparecerão, mas não se preocupe, pois sabemos o que estamos fazendo.


Para se divertir brincando de rede de mentirinha, baixe o projeto completo.
