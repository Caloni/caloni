---
categories: [ "code" ]
date: "2016-11-29"
tags: [ "draft",  ]
title: "Quantos handles sua aplicação está abrindo?"
---
Mesmo que você não programe em C/C++, mas programe para Windows (ex: .NET), sempre há a possibilidade de seu programa estar causando leaks de handles indefinidamente, o que não se traduz em aumento significativo de memória alocada para seu processo, mas é, sim, um problema a ser tratado.

Como isso pode ser causado? Bom, em C/C++ sempre é mais simples de entender esses conceitos. Um código simples que se esquece de fechar o handle usando CloseHandle ou a função equivalente do recurso obtido já seria o suficiente. O último bug que eu encontrei em um código desses comete o clássico erro de sair no meio da função, deixando os recursos alocados:

    DWORD ClassicHandleLeak()
    {
    	DWORD ret = 0;
    	HKEY hKey;
    
    	if ( RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Something", 
    		0, GENERIC_READ, &hKey) == ERROR_SUCCESS )
    	{
    		DWORD retSz = sizeof(ret);
    
    		if (RegQueryValueEx(hKey, L"SomeValue", NULL, NULL, 
    			(PBYTE) &ret, &retSz) == ERROR_SUCCESS)
    		{
    			// success!
    			return ret;
    		}
    
    		RegCloseKey(hKey);
    	}
    
    	return ret;
    }

No exemplo acima quando as coisas dão certo elas também dão errado, já que o retorno do valor no meio da função evita que o HANDLE armazenado em hKey seja desalocado.

E como fazer para descobrir esse tipo de leak?

O HandleLeaker é apenas um exemplo de aplicação que realiza o leak de um handle por segundo. Ele tenta (e consegue) abrir um handle para seu próprio processo, e deixa o handle aberto (programas em Win32 API não são muito bons em RAII).

    int main()
    {
    	while (true)
    	{
    		HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId());
    		Sleep(1000);
    	}
    }

O Perfmon(.msc) está aí no Windows já faz algumas versões (quase todas). Tudo que você precisa para executá-lo é executar o comando perfmon no diálogo de execução (Start, Run) ou encontrar o atalho para perfmon.msc. Na busca do Windows 8/10 também é possível encontrá-lo pelo nome.

Ao executá-lo a primeira coisa que ele monitora é o processamento da máquina. Podemos eliminar ou esconder esse indicador direto na lista abaixo da ferramenta.

Existem incontáveis contadores no Perfmon. Para o que precisamos vamos em Process e escolhemos o contador de Handles.

Depois de um tempo o Perfmon irá exibir o histórico que determina para onde está indo o seu contador.

Se os valores do seu contador estão fora da faixa do histórico é possível ajustar a escala nas propriedades.

Se a frequência for muito menor do que um handle por segundo (isso acontece, principalmente com serviços que rodam por dias/semanas/meses), é possível mudar também pelas propriedades, mas gerais.

A mudança que fizemos captura o dado monitorado de dez em dez segundos e realiza essa operação por 600 segundos (10 minutos), até repetir o gráfico de histórico.

Outra forma de verificar como andam os handles da máquina é usando a já famosa ferramenta da SysInternals. Através das inúmeras colunas que ela fornece existe o contador de handles de cada processo, através do qual é possível verificar quais são os processos com mais handles abertos.

Se seu programa for um handle hog, vai conseguir até ver esse leak acontecendo em tempo real (como o nosso programa mal-educado).

E como encontrar o código-fonte responsável por esse leak? Mais detalhes em um próximo post.
