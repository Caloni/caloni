---
date: "2015-05-06"
title: Analisando erros pelo filtro do File Monitor
categories: [ "code" ]
---
![](http://i.imgur.com/evEhysq.png)

As ferramentas da SysInternals fazem a gente economizar um tempo considerável na resolução de problemas. Não que elas sejam indispensáveis. Tudo que elas fazem é encurtar o caminho entre a análise de um _bug_ e sua resolução, o que acaba sendo muito se considerarmos que programação é 20% codificação e 80% transpiração. Ela é um atalho para muitas coisas, desde achar uma ordem de _includes_ no _header_ errada durante a compilação ou descobrir que por que um processo morreu durante o login.

Curiosamente ambos os exemplos que citei são de uma mesma ferramenta: [Process Monitor](https://technet.microsoft.com/en-us/sysinternals/bb896642.aspx), ou carinhosamente procmon. Ele é um filho de duas ferramentas hoje extintas, FileMon e RegMon (acho que não preciso explicar o que ambas faziam). Todas são baseadas em drivers que escutam eventos do sistema operacional e um aplicativo que mastiga essa informação e as filtra de diferentes e criativas formas.

## Depurando um instalador muito sacana

A __SoSo Company__ é uma empresa criada na China e que possui programadores muito bons. Eles são altamente especializados em fazer instaladores, e nas horas vagas ainda fritam pastéis de frango (ou "flango", como os nativos costumam chamar). Porém, alguma coisa está acontecendo com uma nova versão do instalador que está dando erro ao rodar o aplicativo após atualizado.

![](http://i.imgur.com/vkepNDl.png)

Isso só acontece em algumas máquinas, na maioria delas tudo funciona perfeitamente. Tanto que esse erro só foi encontrado depois de centenas máquinas terem sido atualizadas. E o primeiro a descobrir esse erro foi um cliente muito importante para a Soso. Entre as máquinas desse cliente muito importante, o erro foi acontecer justamente na máquina do CEO da empresa. (Qualquer semelhança com a vida real não é mera coincidência.)

O analista Juquinha, do suporte técnico terceirizado na Índia sul-americana, foi chamado para dar uma olhada nesse problema. Como os chineses não confiam em um não-comedor de pastel de flango, Juquinha não terá acesso ao código-fonte do produto, mas poderá dar uma espiada no instalador. Ei-lo:

```cpp
int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Happy installing...\n";
	CreateDirectory(L"C:\\soso", NULL);
	CopyFile(L"myapp.exe", L"c:\\soso\\myapp.exe", FALSE);
	CopyFile(L"mydll.dll", L"c:\\soso\\mydll.dll", FALSE);
	CopyFile(L"myanotherapp.exe", L"c:\\soso\\myanotherapp.exe", FALSE);
	std::cout << "Everything just got fine =)\n";

	return 0;
}
```

Ahhh, bom. O instalador copia tudo e não verifica erro nenhum. Afinal de contas, o que pode dar errado, não é mesmo?

Vamos agora dar uma olhada no código do aplicativo, coisa que nosso analista não terá a oportunidade.

O produto é constituído de três binários: __myapp.exe__, __myanotherapp.exe__ e __mydll.dll__. Os dois executáveis usam a DLL (no bom sentido). Cada um deles chama a DLL para realizar algumas operações.

```cpp
// mypp.exe v. 1
int _tmain(int argc, _TCHAR* argv[])
{
	if (HMODULE mydll = LoadLibrary(L"mydll.dll"))
	{
		void(*func)() = (void(*)()) GetProcAddress(mydll, "Version1");
		if (func)
			func();
		else
			std::cout << "Error undefinable and indescritable\n";
	}

	return 0;
}

// mypp.exe v. 2
int _tmain(int argc, _TCHAR* argv[])
{
	if (HMODULE mydll = LoadLibrary(L"mydll.dll"))
	{
		void(*func)() = (void(*)()) GetProcAddress(mydll, "Version2");
		if (func)
			func();
		else
			std::cout << "Error undefinable and indescritable\n";
	}

	return 0;
}

// myanotherapp.exe v. 1 e 2
int _tmain(int argc, _TCHAR* argv[])
{
	if (HMODULE mydll = LoadLibrary(L"mydll.dll"))
	{
		getchar();
	}
	return 0;
}
```

Na DLL há apenas uma função exportada: Version1. Quer dizer, na versão sendo atualizada foi criada uma nova função, a Version2. Vejamos a versão final:

```cpp
void Version1()
{
	std::cout << "Version 1\n";
}

void Version2()
{
	std::cout << "Version 2\n";
}
```

Como já vimos, o instalador da SoSo não está muito preocupado em capturar erros. Haja o que houver, o mundo continua maravilhoso. Porém, depois da atualização esse erro explodiu na máquina do diretor. E agora?

![](/images//imgur.com/a1ViOEO)

Sem saber muito bem o que fazer, mas com a possibilidade de testar a situação em uma nova máquina (de outro diretor), Juquinha resolveu rodar novamente o instalador, mas dessa vez com a companhia do ProcMon.

Depois disso, para efeito de comparação, rodou o instalador em uma máquina qualquer onde a atualização funciona.

![](http://i.imgur.com/5U2yc9W.png)

_Dica: Quando for comparar muitos eventos (ex: milhares), em vez de olhar um por um é mais fácil exportar para um CSV e deixar um comparador como o [WinMerge}(http://winmerge.org/) fazer o serviço. No entanto, para comparar muitas informações, algumas colunas precisam ser eliminadas, como o horário de execução dos eventos e o PID dos processos._

E voilà! Parece que alguém está bloqueando a atualização de mydll, embora myapp conseguisse ser atualizado (logo concluímos que não é ele).

Agora, se Juquinha é um analista de nível 1, ele precisará compartilhar suas descobertas com outras pessoas da equipe. Para isso, basta duplo-clicar em um evento e usar o botão de cópia:

![](http://i.imgur.com/fBfaruI.png)

O resultado é um texto com todas as informações necessárias para uma análise aprofundada.

```
Date & Time:	2015-05-08 20:29:52
Event Class:	File System
Operation:	CreateFile
Result:	SHARING VIOLATION
Path:	C:\soso\mydll.dll
TID:	1512
Duration:	0.0000458
Desired Access:	Generic Read/Write, Delete, Write DAC
Disposition:	OverwriteIf
Options:	Sequential Access, Synchronous IO Non-Alert, Non-Directory File
Attributes:	A
ShareMode:	None
AllocationSize:	65,024
```

OK, mas onde está o problema? Bom, aqui começa a [pesquisa](http://lmgtfy.com/?q=CreateFile+SHARING+VIOLATION), mas se você já programou para Windows API já há algum tempo sabe que alguém abriu esse arquivo antes com um modo de compartilhamento incompatível com uma escrita (que é o que o nosso instalador tenta fazer). Para saber quem é o culpado, mais uma ferramenta da SysInternals vem a calhar: [Process Explorer](https://technet.microsoft.com/en-us/sysinternals/bb896653.aspx) (eu ia dizer __handle.exe__, mas ele não funcionou em meus testes).

![](http://i.imgur.com/vXB5VW8.png)

Nesse caso o culpado se mostrou mais próximo do que imaginávamos. O myanotherapp.exe fica bloqueando a dll no momento da atualização! Na verdade, o grande culpado foi mesmo o programador desse instalador, que sequer tem ideia das centenas de erros que podem ocorrer durante uma instalação/atualização. Azar do suporte técnico desse produto =/
