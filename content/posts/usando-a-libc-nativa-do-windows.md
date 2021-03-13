---
date: "2007-11-21"
title: "Usando a libc nativa do Windows"
tags: [ "code" ]
---
Por padrão, todo projeto no Visual Studio depende da libc. Isso quer dizer que, mesmo que você não use nem um mísero printf em todos os projetos criados, está atrelado a essa dependência. Em tempos onde fazer um "Hello World" pode custar 56 KB em Release - Visual Studio 2005, configuração padrão sem "buffer security check" - vale a pena economizar alguns KBytes que não se vão usar. Principalmente se essa possibilidade existe desde o cavernoso Windows 95.

Crie um novo projeto console Win32 vazio (File, New, Project, blá blá blá) e coloque um código de Hello, World nele. Configure para ele usar uma runtime estática e veja o tamanho do executável gerado.  Aqui após configurar um projeto ordinário que compila um executável console ordinário que não depende de runtimes novas (exceto a kernel32.dll) meu arquivo está com 96 KB.

    #include <stdio.h>
    
    int main()
    {
      puts("oi, mundo!\n");
    } 

Desde o Windows 95, existe uma DLL na pasta de sistema chamada msvcrt.dll com a maioria das funções da libc disponíveis para link dinâmico. Só que, com o uso padrão do Visual C++, é usada sempre a biblioteca que vem junto com o ambiente, com suas trocentas funções (e consequentes bytes enche-linguiça). Porém, é possível utilizar diretamente a msvcrt.dll distribuída no diretório do sistema se criarmos uma LIB de importação para ela.

Tudo que você precisa fazer é gerar um msvcrt.def com as funções exportadas por essa dll usando o comando dumpbin.exe /exports msvcrt.dll e gerar uma lib de importação com o comando lib.exe passando no parâmetro /DEF o arquivo gerado. Abaixo um exemplo de como deve estar esse arquivo antes do comando lib /def:msvcrt.def:

    LIBRARY msvcrt
    EXPORTS
    _CrtCheckMemory
    _CrtDbgBreak
    ...
    wprintf_s
    wscanf
    wscanf_s
    
Depois desse último passo geramos a LIB que precisávamos e agora só falta integrar com o projeto. Copie o msvcrt.lib para o diretório do projeto e configure no projeto esse arquivo na lista de LIBs a serem incluídas (Properties, Linker, Input, Additional Dependencies). Lembre-se de ignorar todas as LIBs padrão (Linker, Input, Ignore All Default Libraries). Para evitar unresolved external em frescuras de segurança ignore as firulas de checagem (C/C++, Code Generation, Buffer Security Check, e Basic Runtime Checks em Debug). Antes de mais nada deixe explícito o nome da função de entrada de seu programa para main, pois do contrário ele irá usar um bootstrap que inicia a libc (Linker, Advanced, Entry Point), compile e linke. E voilà!
    
E agora o tamanho final de nosso executável passou para espantosos 3 KB! Isso a princípio parece ótimo e dá vontade de usar em todos os projetos, mas existe um porém ainda não resolvido: as limitações da falta de um runtime. Essa é uma solução bem bobinha que não tem nada a ver com uma solução profissional 100% garantida e com suporte técnico 24 horas. Algumas coisas não vão funcionar, como inicialização de variáveis estáticas, exceções, redirecionamento de entrada/saída, etc. Contudo, para projetos simples e pequenos, isso não deverá ser um problema. No entanto, eu não garanto qualquer coisa que advier de compilações inspiradas neste artigo. 
