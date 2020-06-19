---
categories: [ "code" ]
date: "2008-07-16"
tags: [ "draft",  ]
title: "O caso da função de Delay Load desaparecida"
---
Todos os projetos do Visual Studio 6 estavam compilando normalmente com a nova modificação do código-fonte, uma singela chamada a uma função.aspx) da DLL iphlpapi.dll. No entanto, ainda restava a compilação para Windows 95, um legado que não era permitido esquecer devido ao parque antigo de máquinas e sistemas operacionais de nossos clientes.

Ora, acontece que a função em questão não existe em Windows 95! O que fazer?

Essa é uma situação comum e controlada, que chega a ser quase um padrão de projeto: funções novas demais. A saída? Não chamar a função quando o sistema não for novo o suficiente. Isso pode ser resolvido facilmente com uma chamada a GetVersion.aspx).

Porém, um outro problema decorrente dessa situação é que a função chamada estaticamente cria um link de importação da DLL para o executável. Ou seja, uma dependência estática. Dependências estáticas necessitam ser resolvidas antes que o programa execute, e o carregador (loader) de programas do sistema é responsável por essa verificação.

Para verificar a existência de todas as DLLs e funções necessárias para nosso programa podemos utilizar o mundialmente conhecido Dependency Walker:


Se a função ou DLL não existe no sistema, o seguinte erro costuma ocorrer (isso depende da versão do Sistema Operacional):

Mas nem tudo está perdido!

Existe uma LIB no Visual Studio que serve para substituir a dependência estática de uma DLL pela verificação dinâmica da existência de suas funções quando, e se, for executada a função no programa.

Essa LIB contém algumas funções-chave que o Visual Studio utiliza ser for usado o seguinte parâmetro de compilação:


A função principal se chama "delayLoadHelper@8", ou seja, é uma função com convenção de chamada WINAPI (stdcall) que recebe dois parâmetros.

Isso costuma sempre funcionar, sendo que tive uma grande surpresa com os seguintes erros de compilação na versão do programa que deve ser executada em Windows 95:


Isso, é claro, depois de ter checado e rechecado a existência da LIB de Delay Load na lista de LIBs a serem lincadas:

Acontece que eu conheço algumas ferramentas que podem sempre me ajudar em situações de compilação e linque: Process Monitor e dumpbin.

O Process Monitor pode ser usado para obter exatamente a localização da LIB que estamos tentando verificar:

Após localizar o local, podemos listar seus símbolos, mais precisamente a função "delayLoadHelper":


A análise mostra que a função possui um "2" no final de seu nome, causando o erro de linque.

Essa função, pelo visto, tem mudado de nome desde o Visual C++ 6, o que fez com que LIBs mais novas não funcionassem com essa versão do Visual Studio.

Para sanar o problema, existem duas coisas que podem ser feitas:

	
  1. Usar a delayimp.lib antiga. Isso não exige nenhuma mudança no código.

	
  2. Criar uma função delayLoadHelper como wrapper. Isso exige a escrita de código. O código-fonte dessa função está disponível no diretório Include do Visual Studio, e pode ser adaptada para versões antigas.

Nessa sessão de depuração você aprendeu como usar o Process Monitor para rastrear arquivos usados na compilação e como listar símbolos de LIBs que são usadas para lincar o programa.
