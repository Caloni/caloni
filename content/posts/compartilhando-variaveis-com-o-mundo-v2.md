---
date: "2008-02-01"
title: Compartilhando variáveis com o mundo v2
tags: [ "draft", "code" ]
---
<blockquote>_Nota de desempenho: esse artigo finaliza (finalmente) a republicação de todos os artigos do antigo blogue. Isso quer dizer que a partir de agora eu sou obrigado a trabalhar, e, se quiser manter meu ritmo atual, vou ter que fazer mais do que cinco cliques do mouse._</blockquote>

Como todas as coisas que fazemos e pensamos depois, descobrimos que **sempre existe uma outra maneira de fazer a mesma coisa**. Se é melhor ou não, pode ser uma questão de gosto, estética, objetivos de vida, etc. Com a [implementação das variáveis mapeadas globais](http://www.caloni.com.br/compartilhando-variaveis-com-o-mundo) não foi diferente. Bem, é isso que se espera fazer com código experimental: experimentos. E deu no que deu: SharedVar versão 2.0 alpha Enterprise Edition.

#### POO na cabeça

Quando comentei no final do artigo anterior que existem pessoas que só conseguem gerar código dentro de uma classe, não estava brincando. Existem linguagens, inclusive, que suportam apenas o paradigma de orientação a objetos, e levam isso muito a sério. C++ com certeza **não** é uma dessas linguagens, o que quer dizer que você tem a **liberdade e a responsabilidade** de tomar o melhor caminho para determinado problema.

Nessa segunda solução do nosso programa alocador de variáveis globais, pra variar, vamos utilizar uma classe. E pra entrar de vez no mundo POO vamos utilizar de quebra tratamento de erro orientado a exceções. Como vamos notar, aplicadas adequadamente, essas duas características da linguagem conseguirão um código mais simples de entender, embora não se possa dizer o mesmo da implementação "_under the hood_".

```cpp
/** Classe helper para as nossas funções de alocação de variáveis
compartilhadas com o mundo. */
template<typename T>
class SharedVar
{
public:
	// se conseguir, parabéns; senão, retorna BUM!
	SharedVar(PCTSTR varName)
	{
		m_memPointer = 0;
		m_memHandle = AllocSharedVariable(&m_memPointer, varName);

		if( ! m_memHandle || ! m_memPointer )
			throw GetLastError();
	}

	// libera recursos alocados para a variável
	~SharedVar()
	{
		FreeSharedVariable(m_memHandle, m_memPointer);
	}

	T& operator * ()
	{
		return *m_memPointer;
	}

private:
	// não vamos nos preocupar com isso agora
	SharedVar(const SharedVar& obj);
	SharedVar& operator = (const SharedVar& obj);

	T* m_memPointer;
	HANDLE m_memHandle;
}; 

```

Como podemos notar, em programação "nada se cria, tudo se reutiliza". Reutilização é boa quando podemos **acrescentar características adicionais ao código sem deturpar seu objetivo original**. E isso é bom.

Note que nossa classe tenta fazer as coisas logo no construtor, já que seu único objetivo é representar uma variável da memória cachê. Se ela não for bem-sucedida em sua missão, ela explode, porque não há nada que ela possa fazer para **garantir a integridade do objeto** sendo criado e ela não tem como saber qual o melhor tratamento de erro para o usuário da classe. Geralmente o melhor - ou pelo menos o mais adequado - é o tratamento que o usuário dá ao seu código, porque o **usuário da classe é que deve saber o contexto de execução do seu código**.

Bem, como o código agora está em uma classe e o erro é baseado em exceção, o código cliente muda um pouco:

```cpp
/** Exemplo de como usar as funções de alocação de memória compartilhada
AllocSharedVariable, OpenSharedVariable e FreeSharedVariable.
*/
int _tmain(int argc, PTSTR argv[])
{
	try
	{
		// passou algum parâmetro: lê a variável compartilhada e exibe
		if( argc > 1 )
		{
			system("pause");

			// array de 100 TCHARs
			SharedVar<TCHAR [100]> sharedVar(_T(SHARED_VAR));

			_tprintf(_T("Frase secreta: \'%s\'\n"), *sharedVar);
			_tprintf(_T("Pressione <enter> para retornar..."));
			getchar();
		}
		else // não passou parâmetro: escreve na variável 
		// compartilhada e chama nova instância
		{
			// array de 100 TCHARs
			SharedVar<TCHAR [100]> sharedVar(_T(SHARED_VAR));

			PTSTR cmd = new TCHAR[ _tcslen(argv[0]) + 10 ];
			_tcscpy(cmd, _T("\""));
			_tcscat(cmd, argv[0]);
			_tcscat(cmd, _T("\" 2"));

			_tcscpy(*sharedVar,
			_T("Vassora de sa, vassora de su, vassora de tuturuturutu!"));
			_tsystem(cmd);

			delete [] cmd;
		}
	}
	catch(DWORD err)
	{
		_tprintf(_T("Erro %08X.\n"), err);
	}

	return 0;
} 

```

Existem duas mudanças significativas: 1. a variável sozinha já representa a memória compartilhada; 2. o tratamento de erro agora é centralizado em apenas um ponto. Se pra melhor ou pior, eu não sei. Tratamento de exceções e classes são duas "modernisses" que podem ou não se encaixar em um projeto de desenvolvimento. Tudo vai depender de tudo. Por isso a melhor saída depende de como será a entrada.
