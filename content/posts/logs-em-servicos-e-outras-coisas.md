---
date: "2015-06-05"
title: Logs em serviços (e outras coisas)
tags: [ "draft", "code" ]
---
![](http://i.imgur.com/p9kH1LW.jpg)

Já uso logs há muito tempo. Me lembro muito bem que quando programava em BASIC o "passou por aqui" já era útil. Depois de fazer muitas bibliotecas super-flexíveis de escrita em saídas diferentes, níveis configuráveis e uso do mais complexo ao mais banal, cheguei à seguinte conclusão:

```cpp
Log("Quero um log mais simples possível (de preferência ", 15, " vezes mais simples)");
```

Vou tentar defender meu ponto de vista.

Esse [artigo do Dr. Dobbs](http://www.drdobbs.com/cpp/a-lightweight-logger-for-c/240147505) explica de uma maneira bem completa como fazer uma lib de log leve e configurável. O que eu peguei desse exemplo foi a forma mais C++ de formatar as linhas, deixando para trás o estilão printf que depois de variadic templates já está datado.

```cpp
#include <iostream>
#include <sstream>

inline void Log(std::ostringstream& os)
{
	std::cout << os.str() << std::endl;
}

template<typename First, typename...Rest >
void Log(std::ostringstream& os, First parm1, Rest...parm)
{
	os << parm1;
	Log(os, parm...);
}

template<typename...Rest >
void Log(Rest...parm)
{
	std::ostringstream os;
	LogHeader(os);
	Log(os, parm...);
}
```

Por que eu acho a minha versão mais legal (não valendo falar que foi porque eu fiz):

 - É mais simples ainda, tem poucas linhas e pode ser copiada sem peso na consciência. Pode até estar em um header que o overhead é mínimo.
 - Não requer configuração de arquivo, debug output, named pipe, etc. Isso tem a ver com o uso de cada um. O próximo motivo explica melhor isso.
 - Se for executado em um prompt já exibe as informações para serem filtradas; se for executado como um serviço encapsulo a saída.

Encapsular a saída e o comportamento de um serviço hoje em dia é algo banal. Há diversos programas que fazem isso para você, sendo desnecessário programar toda aquela parte de comunicação com o Windows. O [cara do DriverEntry](http://driverentry.com.br/blog/?p=461) (vulgo o kernel-mode programmer motta-focka Fernando) fez um aplicativo que faz isso, que é simples de usar e continua funcionando no Windows 8.1. Atualmente uso um outro encontrado pelo igualmente fodástico [Rodrigo Strauss](https://nssm.cc/): o Non Sucking Service Manager (seu nome já explica por que defendo utilizar o mínimo possível das firulas da Microsoft).

Além de ser extremamente flexível e não ter falhado nas vezes que o utilizei, o NSSM consegue redirecionar a saída do aplicativo que encapsula como um serviço para um arquivo e rotacionar o arquivo por tamanho ou data (ou reexecução do serviço):

![](http://i.imgur.com/v12mGG3.png)

Abaixo uma receitinha básica para configurar seu aplicativo:

```
nssm.exe install MyService C:\Path\MyService.exe <args>
nssm set MyService AppStdout C:\Path\Logs\MyService.log
nssm set MyService AppStderr C:\Path\Logs\MyService.log
nssm set MyService AppRotateFiles 1
nssm set MyService AppRotateOnline 1
nssm set MyService AppRotateBytes 10485760
```

_(para quem está se perguntando, 10485760 bytes são 10 MB.)_

Com essa forma de fazer serviços, há uma dupla vantagem:

 - Retirar todo o código para lidar com o Service Manager do Windows das suas mãos.
 - Continuar tendo um aplicativo que roda pelo prompt e já imprime seu comportamento (e pode ser redirecionado também).

E ainda uma vantagem-bônus:

 - Você pode executar programas-filho que o redirect para o log vai funcionar do mesmo jeito.

### Bônus final

Acho que cada um deve escrever no seu header o que achar melhor para depurar seus programas. No entanto, acho válido compartilhar quais são as informações que tem sido úteis para mim:

```cpp
inline void LogHeader(std::ostringstream& os)
{
	SYSTEMTIME st;
	char buffer[48] = "";

	GetLocalTime(&st);

	sprintf_s(buffer, "%04d-%02d-%02d %02d:%02d:%02d %04X.%04X %08X ",
		st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond,
		GetCurrentProcessId() & 0xFFFF, GetCurrentThreadId() & 0xFFFF,
		GetLastError());

	os << buffer;
}
```
