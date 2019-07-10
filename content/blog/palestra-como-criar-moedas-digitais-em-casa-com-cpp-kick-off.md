---
date: "2017-02-19"
title: "Palestra: como criar moedas digitais em casa com C++ (kick-off)"
categories: [ "blog" ]

---
Esta palestra tem como objetivo ensinar o que são moedas digitais, como o bitcoin, e cada passo necessário o algoritmo e implementação para torná-la real. Será utilizado C++ como a linguagem-base e o foco está mais na implementação do que na matemática ou no algoritmo. Assim como foi criado o bitcoin, o importante a aprender é como unir diferentes tipos de conhecimento e tecnologia em torno de um objetivo único, simples e prático.

![](http://i.imgur.com/TAunJPB.png)

A partir da criação da moeda surge a necessidade de facilitar o seu uso, um problema recorrente em todas as mais de 700 moedas digitais existentes no mercado e no laboratório, incluindo o bitcoin. Após a palestra teremos uma discussão de como levar a tecnologia ao usuário comum.

### Construindo os princípios básicos

Para nossa moeda digital utilizaremos um sistema simples, rápido e prático para subir informações na memória de um nó (server) e repassar essas informações para outros nós, o tiodb. Este projeto mantém contêineres STL na memória da maneira mais enxuta possível e eles são acessíveis através do protocolo mais simples possível utilizando uma gama de linguagens (C, C++, Python, .NET).

A primeira coisa é compilar o projeto tiodb, que irá disponibilizar alguns binários em sua saída:

 - __tio.exe__ é o executável central cuja instância mantém contêineres na memória;
 - __InteliHubExplorer.exe__ é uma interface simples para navegar por esses contêineres;
 - __tioclient.dll__ é a biblioteca dinâmica que pode ser usada por clientes para acessar o tio.

Podemos rodar o tio deixando ele usar os parâmetros padrão ou alterar número da porta e outros detalhes. Vamos executar da maneira mais simples:

```cmd
C:\Projects\tiocoin\tiodb\bin\x64\Debug>tio
Tio, The Information Overlord. Copyright Rodrigo Strauss (www.1bit.com.br)
Starting infrastructure...
Saving files to C:/Users/Caloni/AppData/Local/Temp
Listening on port 2605
Up and running!
```

OK, tio rodando e ativo. Podemos navegar já pelos seus contêineres usando o InteliHubExplorer:

![](http://i.imgur.com/YJZ7wxC.png)

Por convenção os contêineres seguem um padrão de nomes que se assemelha a uma hierarquia de diretórios, e os nomes que começam com underline são internos/reservados. O contêiner __meta__/sessions, por exemplo, contém uma lista simples das conexões ativas deste nó.

A partir do servidor funcionando é possível criar novos contêineres e mantê-los, adicionando, atualizando e removendo itens. A partir dessas modificações outros clientes podem receber notícias dessas modificações e tomar suas próprias decisões.

Vamos criar e popular um contêiner inicial de transações com  um GUID zerado, e a partir dele vamos adicionando novas "transações". Também iremos permitir o monitoramento dessas transações.

```cpp
try
{
    tio::Connection conn;
    conn.Connect(server, port);

    if (args.find("--build") != args.end())
    {
        tio::containers::list<string> transactionsBuilder;
        transactionsBuilder.create(&conn, "transactions", "volatile_list");
        transactionsBuilder.push_back("{00000000-0000-0000-0000-0000000000000");
    }
    else if (args.find("--add") != args.end())
    {
        tio::containers::list<string> transactionsAdd;
        transactionsAdd.create(&conn, "transactions", "volatile_list");
        string newTransaction = NewGuid();
        if( newTransaction.size())
            transactionsAdd.push_back(newTransaction);
        else
            cout << "Error creating transaction\n";
    }
    else if (args.find("--monitor") != args.end())
    {
        tio::containers::list<string> transactionsMonitor;
        transactionsMonitor.open(&conn, "transactions");
        transactionsMonitor.subscribe([](auto container, auto containerEvt, auto key, auto value)
                {
                int eventCode = stoi(containerEvt);

                switch (eventCode)
                {
                case TIO_COMMAND_PING:
                cout << "Ping!\n";
                break;

                case TIO_EVENT_SNAPSHOT_END:
                cout << "Snapshot end\n";
                break;

                case TIO_COMMAND_PUSH_BACK:
                cout << "New transaction " << value << " inserted\n";
                break;

                default:
                cout << "Unknown event " << hex << eventCode << " with key " << dec << key << " and with value " << value;
                break;
                }
                });
        while (true)
        {
            conn.WaitForNextEventAndDispatch(0);
            Sleep(1000);
        }
    }
    else
    {
        tio::containers::list<string> transactionsReader;
        transactionsReader.open(&conn, "transactions");
        for( size_t transactionIdx = 0; transactionIdx < transactionsReader.size(); ++transactionIdx )
            cout << "Transaction " << transactionsReader.at(transactionIdx) << endl;
    }

    break; // just testing and developing...
}
catch (tio::tio_exception& e)
{
    Log("Connection error: %s", e.what());
    break;
}
catch (std::runtime_error& e)
{
    Log("Runtime error: %s", e.what());
    break;
}
catch (...)
{
    Log("Catastrophic error");
    break;
}
```

Após executar esse código passando o argumento "--build" e atualizarmos o IntelihubExplorer poderemos ver o novo contêiner e seu conteúdo:

![](http://i.imgur.com/3Mhj2lE.png)

É possível ler o código rodando o mesmo programa sem passar o argumento "--build":

![](http://i.imgur.com/CxdmZhy.png)

Agora imagine que exista um cliente da tiocoin que está monitorando as transações deste servidor para verificar a partir de qual momento uma transação foi aceita (supondo que este contêiner possui as transações aceitas):

![](http://i.imgur.com/kLrPawv.png)

Voilà! Agora temos um sistema inicial com um contêiner que irá manter os IDs de supostas transações de nossa moeda digital. Está compilando e está rodando, e em cima disso poderemos ir adicionando as funcionalidades.

Atenção: você poderá encontrar o repositório do tiocoin [aqui](https://github.com/bitforgebr/tiocoin).
