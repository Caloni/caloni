---
categories: [ "code" ]
date: "2008-06-21"
tags: [ "draft",  ]
title: "É possível carregar duas DLLs gêmeas no mesmo processo?"
---
Um dos últimos artigos de Dmitry Vostokov, e tenho que falar assim porque o cara escreve muito em pouco tempo, fala sobre os perigos de termos uma mesma DLL carregada duas vezes em um único processo, muitas vezes em versões diferentes. Para os observadores atentos como Dmitry esse é um perigo que muitas vezes temos que estar preparados. Para os espertinhos de plantão, a resposta padrão seria: "não vou me preocupar, porque o contador de instâncias cuida disso".

Será mesmo tão simples?

Vamos supor um caso bem simples e plausível, que é exatamente o mesmo do artigo do Crash Dump Analysis: um produto qualquer possui dois pontos em que ele carrega a mesma DLL. Contudo, no primeiro ponto é usado um caminho relativo, dentro da pasta DLL; na segunda chamada é usado o caminho atual. Se existir de fato duas DLLs, mesmo que idênticas, nesses lugares, então teremos duas instâncias da "mesma DLL" carregadas no processo.

O código do aplicativo apenas tenta carregar a DLL em dois lugares distintos e exibe o endereço para onde elas foram mapeadas em nosso processo de teste:

    #include <windows.h>
    #include <stdio.h>
    
    int main()
    {
    	HMODULE dll1 = LoadLibrary(".\\DLL\\DLL.dll");
    	HMODULE dll2 = LoadLibrary(".\\DLL.dll");
    
    	printf("First DLL: %p\nSecond DLL: %p",
    			dll1, dll2);
    
    	return 0;
    }
    

A DLL é uma DLL trivial:

    #include <windows.h>
    
    BOOL WINAPI DllMain(HINSTANCE inst, DWORD reason, PVOID reserv)
    {
    	return TRUE;
    }

Vamos aos testes.

Nesse caso, ambos os retornos serão nulos, que é o natural e esperado quando a DLL não pode ser encontrada nos lugares especificados pelo sistema e pelo aplicativo.

    
    K:\Docs\Projects>cl app.c
    Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.42 for 80x86
    Copyright (C) Microsoft Corporation.  All rights reserved.
    app.c
    Microsoft (R) Incremental Linker Version 8.00.50727.42
    Copyright (C) Microsoft Corporation.  All rights reserved.
    /out:app.exe
    app.obj
    K:\Docs\Projects>app
    First DLL: 00000000
    Second DLL: 00000000
    K:\Docs\Projects>

No segundo caso, a DLL é carregada com sucesso se usado o caminho relativo, pois o caminho atual faz parte da lista de caminhos que o sistema percorre para encontrá-la. A primeira chamada deve falhar.

    
    K:\Docs\Projects>cl /LD dll.c
    Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.42 for 80x86
    Copyright (C) Microsoft Corporation.  All rights reserved.
    dll.c
    Microsoft (R) Incremental Linker Version 8.00.50727.42
    Copyright (C) Microsoft Corporation.  All rights reserved.
    /out:dll.dll
    /dll
    /implib:dll.lib
    dll.obj
    K:\Docs\Projects>app
    First DLL: 00000000
    Second DLL: 10000000
    K:\Docs\Projects>

No caso problemático, a mesma DLL é carregada em dois endereços distintos da memória do mesmo processo, o que pode causar sérios problemas dependendo do código envolvido.

    
    K:\Docs\Projects>mkdir DLL
    K:\Docs\Projects>copy dll.dll DLL
    1 arquivo(s) copiado(s).
    K:\Docs\Projects>app
    First DLL: 10000000
    Second DLL: 00350000
    K:\Docs\Projects>

Apesar do mundo parecer injusto, temos uma segunda regra que podemos usar para aqueles casos onde a idiotisse já foi feita:

Vamos supor que estamos no meio de uma mudança bem radical no produto e queremos ter certeza que qualquer chamada à nossa DLL irá invocar unicamente a que estiver dentro do caminho do produto (caminho atual). Para esse caso o Windows permite uma saída muito interessante, que é o uso de um arquivo com o nome do aplicativo mais o sufixo ".local". Se esse arquivo existir, de acordo com o MSDN.aspx), então qualquer chamada à DLL irá ter sempre a prioridade do caminho atual.

    
    K:\Docs\Projects>copy con app.exe.local
    ^Z
    1 arquivo(s) copiado(s).
    K:\Docs\Projects>app
    First DLL: 10000000
    Second DLL: 10000000
    K:\Docs\Projects>

Tente evitar a replicação do mesmo arquivo em diversos lugares. Quando eu digo "mesmo arquivo" me refiro ao mesmo nome de DLL, embora não necessariamente a mesma versão. Isso pode evitar algumas dores de cabeça futuras. E muitas, muitas horas de depuração.
