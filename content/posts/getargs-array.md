---
date: "2020-08-04"
categories: [ "code", "ccpp" ]
title: "GetArgs v. Array"
---
Algumas pessoas ficam chateadas quando não se programa usando Boost para tudo. E por isso eu continuo escrevendo código simples e funcional para meu blogue. Esse código vai continuar funcionando por mais cem anos e o código da Boost vai explodir antes que seus filhos nasçam.

    /** Interpreta argumentos 
      da linha de comando 
      com suporte a arrays.

    @author Caloni
    @date 2020-08
    */
    #include <stdlib.h>
    #include <string.h>
    
    const char** GetArgArray(
      char* argv[], const char* arg)
    {
    	char** ret = NULL;
    	size_t cur_off = 0;
    
    	while (*++argv)
    	{
    		if (strcmp(*argv, arg) == 0)
    		{
    			if (*(argv + 1))
    			{
    				char* new_arg = *(argv + 1);
    				ret = 
              (char**)
              realloc(ret, (cur_off + 2) 
                * sizeof(char*));
    				ret[cur_off++] = new_arg;
    				ret[cur_off] = NULL;
    			}
    		}
    	}
    
    	return (const char**)
        ret;
    }

Esta versão do meu famigerado parser de argumentos vindos do argc e argv atende uma necessidade que tive recentemente em um projeto de teste: obter um array de argumento. Um array de argumentos é o mesmo argumento repetido n vezes se transformando em um array para ser consumido como tal. Para essa versão será necessário uma segunda função, especializada, que faça o serviço.

Alterei meu código mágico, simples e rápido para parsear linha de comando em C para suportar arrays. Na correria do projeto foi algo igualmente simples e rápido, embora com alguns truques interessantes de se aprender sobre libc. Basicamente o que ele faz é varrer o array argv construindo seu próprio filtrado apenas com os argumentos que interessam. Ele aloca e realoca a memória para esse array de ponteiros para char usando a função padrão realloc, que consegue fazer a alocação inicial e realocações mantendo o conteúdo da memória original.

Durante o laço é mantido um offset que é incrementado a cada novo argumento. Caso não exista nenhum argumento o retorno será NULL. O aprendizado de libc aqui fica por conta do uso do realloc para simplificar realocação, algo que C++ não possui até hoje (se você quiser fazer as coisas apenas no modo C++ com new e delete) e que depende de abstrações da STL como containers para fazê-lo.
