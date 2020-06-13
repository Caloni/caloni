---
categories: [ "code" ]
date: "2008-07-14"
tags: [ "draft",  ]
title: "Segunda versão do Houaiss2Babylon"
---
Depois de vários comentários (na época que o saite tinha comentários) de pessoas tendo problemas em converter seus dicionários Houaiss para o formato Babylon, resolvi criar vergonha na cara e dar uma pequena melhora na versão beta do conversor.

Agora a maioria dos erros que houver será descrita por uma mensagem no seguinte formato:

O primeiro erro acima ocorre principalmente se não houver algum Houaiss instalado que o programa possa detectar. Resolva este problema fazendo uma busca no Buscapé.

Abaixo segue a função criada para exibir essas mensagens:

    void MessageError(DWORD err, PCSTR msg, ...)
    {
    	CHAR errBuffer[100];
    	CHAR msgBuffer[ERR_STR_BUF_SIZE];
    	va_list vaList;
    
    	va_start(vaList, msg);
    	vsprintf(msgBuffer, msg, vaList);
    	va_end(vaList);
    
    	sprintf(errBuffer, " Erro de sistema número %d.", (int) err);
    	strcat(msgBuffer, errBuffer);
    
    	MessageBox(NULL, msgBuffer, STR_PROJECT_NAME, MB_OK | MB_ICONERROR);
    }
    
     
    

Se você notou, a função acima pode receber um número de argumentos variáveis para formatar a string da mensagem principal do erro, além de exibir seu código. Essa mágica pode ser feita usando-se o cabeçalho padrão "stdarg.h". Através dele temos acesso ao tipo valist, que representa uma lista de argumentos variáveis.

Pela convenção de chamada da linguagem C (e C++), quem desmonta a pilha é o chamador. Sendo assim, a função chamada não precisa conhecer o número de argumentos com que foi chamado.

A função de formatação de string é uma variante do conhecidíssimo printf, na versão que recebe um tipo valist. Muito útil para formatação de logs.

A versão beta do Houaiss2Babylon está para sair. Não estarei mais atualizando o saite do projeto no LaunchPad. Aguardem por mais novidades no próprio blogue.
