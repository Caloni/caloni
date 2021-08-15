---
categories:
- code
date: '2016-08-16'
tags:
title: DBAccess
---

Bancos de dados são uma dor de cabeça para o desenvolvedor acessar. Quase tão motivation killer que as configurações do .NET. Se for um programador em C++ para Windows, então, desista.

O [DBAccess](https://github.com/Caloni/DBAccess) é mais um dos códigos-fonte desenterrados dos meus backups. Esse eu usei já em vários projetos, porque é simples e rápido de usar.

```
class DBAccess
{
public:
	/// Factory para base de dados específica.
	/// @param database Pode ser "sqlite" ou "oledb".
	static DBAccess* CreateDBAccess(const std::string& database);

	typedef std::string ColumnName;
	typedef std::vector<std::string> Rows;
	typedef std::map<ColumnName, Rows> RowSet;

	virtual ~DBAccess() { }

	virtual bool Connect(const std::string& connectionString) = 0;
	virtual bool Disconnect() = 0;

	/// Executa uma instrução SQL e retorna opcionalmente os resultados (se for uma query).
	virtual bool Execute(const std::string& command, RowSet* response = 0) = 0;
};
```

Sua função é abstrair a abertura de um banco de dados, sua execução e sua saída. Para isso ele cria uma interface simples que usa STL. Por debaixo dos panos, usa OLEDB, que abstrai qualquer coisa, só precisando de instalar o driver e aprender qual [das 500 mil combinações](https://www.connectionstrings.com/) é a string de conexão correta. Para não ter que usar outras funções para coisas simples como sqlite, foi incluído seu suporte (que é mais uma tradução entre interfaces), necessitando para seu uso daquele projeto do sqlite que contém um header e um .c (pelo jeito o pessoal desse projeto também gosta de simplificar as coisas).

O código que trata o OLEDB é um pouco grande (umas 300 linhas) por conta da manipulação dos componentes COM. Porém, feito decentemente, faça uma vez e use um milhão (ainda falta fazer alguns unit tests, aliás).

```
IDataInitialize* pIDataInitialize;
IDBInitialize* pIDBInitialize;
IDBCreateSession* pIDBCreateSession;
IDBCreateCommand* pIDBCreateCommand;
```

É um bom projeto para entender o uso da minha batidíssima biblioteca de parsear argumentos argv/argc (Args.cpp/h) e a mais batidíssima ainda [biblioteca de Log](http://caloni.com.br/logs-em-servicos-e-outras-coisas), que utiliza variadic templates para se livrar da maldição dos crashs causados pela falta de tipagem do printf e derivados (em Log.cpp/h).

Além disso, observe como o uso de interface permite que os headers específicos do que tem que ser feito (e.g. oledb.h, atlbase.h, msdasc.h, sqlite.h e até windows.h) não precisa necessariamente estar presente no header da interface (oledb.h), e como o uso de um factory em um método estático da interface permite que a junção das tecnologias envolvidas fique apenas no oledb.cpp. Dessa forma, para retirar ou acrescentar novas formas de comunicação com um banco de dados é muito simples.

_PS: A publicação do __DBAccess__ foi inspirada na thread iniciada por Spagiari no [nosso grupo C/C++](https://groups.google.com/forum/#!topic/ccppbrasil/3qtvxelVrdc)._
