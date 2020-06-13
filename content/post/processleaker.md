---
categories: [ "code" ]
date: "2008-08-21"
tags: [ "draft",  ]
title: "ProcessLeaker"
---
O artigo anterior mostrava como detectar o leak de um processo gerado pela retenção e não-liberação de handles para o Windows Explorer. O problema fora causado por um serviço malcriado. No entanto, a título de demonstração, criei um pequeno programinha sem-vergonha para fazer as coisas parecerem difíceis. No entanto o programa é bem fácil:

    #include <windows.h>
    #include <stdio.h>
    
    int main()
    {
    	DWORD pid;
    
    	while( scanf("%d", &pid) == 1 )
    	{
    		HANDLE proc = OpenProcess(SYNCHRONIZE, FALSE, pid);
    	}
    }
    
     
    

Para usá-lo, basta abrir um Gerenciador de Tarefas com opção de exibir o PID dos processos.

A partir daí, é só criar e matar várias instâncias do explorer.exe. Antes de matar um, digite o PID do novo processo no ProcessLeaker.

Para listar os processos perdidos, basta usar o comando "!process 0 0" no WinDbg depurando em kernel. O resto você já sabe.
