---
categories: [ "code" ]
date: "2010-10-26"
tags: [ "draft",  ]
title: "FormatMessage para... dumies?"
---
Já foi comentado em alguns círculos de ótimos programadores que a função da Win32 API FormatMessage é uma das criaturas mais bizarras já criadas.

O objetivo da FormatMessage é formatar uma string, assim como sprintf, mas voltado mais a escrever uma descrição de um código de erro. Sendo assim ela é essencial para que o usuário não receba um número no lugar de uma explicação de por que a operação falhou.

Os códigos de erro que ela se propõe a formatar podem ser os erros padrões descritos em winerror.h ou qualquer outro código cuja explicação esteja em algum módulo carregado pelo processo (DLL ou o próprio executável). Isso nos dá a liberdade de, por exemplo, criar uma DLL apenas com códigos e descrições dos erros dos nossos produtos.

Para que seja criada a mensagem final, uma definição de mensagem é requirida como entrada, que pode vir do próprio chamador ou da já mencionada tabela de erros de algum módulo qualquer. No caso de querermos a descrição de um erro de sistema (em winerror.h, retornado por GetLastError ou similares) a definição da mensagem já está embutida no sistema, bastando para nós passarmos o código.

É importante lembrar que, como estamos falando de uma descrição de erro, ou seja, de um texto, este pode vir em diversos idiomas, sendo que é nossa obrigação também definir para qual idioma desejamos traduzir nosso código de erro, sendo também nossa obrigação, no caso de mensagens específicas do nosso programa, fornecer o modelo da mensagem nos idiomas que formos suportar.

O resto da função funciona mais ou menos como o sprintf, cuspindo a mensagem-modelo em uma saída formatada de acordo com os parâmetros de entrada.

    
    DWORD WINAPI FormatMessage(
       __in      DWORD dwFlags,
       __in_opt  LPCVOID lpSource,
       __in      DWORD dwMessageId,
       __in      DWORD dwLanguageId,
       __out     LPTSTR lpBuffer,
       __in      DWORD nSize,
       __in_opt  va_list *Arguments
    );

As flags do parâmetro dwFlags mudam radicalmente o funcionamento da rotina, o que me lembra de outra figura bizarra: o realloc da biblioteca padrão.

No caso do FormatMessage, a variável dwFlags se divide em dois para especificar dois grupos de opções distintos. A parte maior contém as opções armazenadas tradicionalmente como um mapa de bits, enquanto o byte menos significativo define como será tratada a saída final, com respeito às novas linhas e qual será a largura máxima de uma linha na saída.

O parâmetro mais polêmico é o que possui vários significados. No caso de lpSource, existem dois significados possíveis:

    
  1. FORMAT_MESSAGE_FROM_HMODULE. Ele é um HANDLE para um módulo.

    
  2. FORMAT_MESSAGE_FROM_STRING. Ele é um ponteiro para string.

Isso explica por que essas duas flags são exclusivas: ou uma ou outra. Mesmo que a flag FORMATMESSAGEFROMSYSTEM seja usada, a função tentará achar a definição da mensagem no módulo especificado por lpSource primeiro, antes de ir buscar nas tabelas do sistema.

Chamado de dwMessageId, esse é o argumento onde podemos passar um código de GetLastError ou nossos próprios códigos de erro. Se já tivermos uma string em lpSource, no entanto, não faz sentido existir um código de erro.

Para definir o idioma é usado o mesmo sistema de resources: monta-se uma DWORD com MAKELANGID que contém informações do idioma primário e secundário. Se quisermos usar o idioma padrão do sistema (99% dos casos) basta passarmos o retorno de MAKELANGID(LANGNEUTRAL, SUBLANGNEUTRAL).

Mais um argumento polêmico. Se a flag FORMATMESSAGEALLOCATEBUFFER, lpBuffer não é um buffer, mas um ponteiro que será preechido com um endereço de memória alocada usando a função API LocalAlloc. Isso quer dizer que, após usar a mensagem formatada, devemos desalocar essa memória com LocalFree.

Por outro lado, se o buffer for nosso, então seu tamanho deve ser especificado no próximo argumento, nSize.

Só que nem o parâmetro que especifica o tamanho do buffer é simples, assim. Se for especificado a flag FORMATMESSAGEALLOCATEBUFFER, em vez de não fazer sentido esse argumento, ele significa o número MÍNIMO de caracteres que devem ser alocados, independente do tamanho da mensagem.

Obs.: Lembre-se que são caracteres, e não bytes. Se estivermos programando em UNICODE o número de bytes dobra.

Essa seria uma lista simples de argumentos valist que, para quem já fez funções ao estilo printf sabe muito bem usar. A lógica da função determina que os valores "%1", "%2" e assim por diante dentro da definição de mensagem sejam trocados por estes argumentos.

Se eles são strings terminadas em nulo (interpretação padrão), inteiros ou estruturas específicas, isso vai depender da mensagem que está sendo formatada, o que é outro if a ser lembrado na hora de formatar mensagens do sistema.

Também é importante lembrar que, uma vez chamada a função, o conteúdo de valist não pode ser usado novamente se não for reinicializado com vaend seguido de vastart.

Agora, se todo esse negócio de vasbrubles é muito complicado pra você, é possível passar um array de DWORDPTRs com o uso da flag FORMATMESSAGEARGUMENTARRAY.

Se tudo der certo e você passar todos os argumentos certinhos, o retorno é o número de caracteres armazenados no buffer de saída, independente dele ter sido alocado dinamicamente ou não. Ah, sim, excluindo o nulo terminador.

Se der errado a função retorna zero. É possível obter o erro através de GetLastError, o que muito provavelmente será 87 nas primeiras vezes que você usar essa função.

Pensou que acabaria por aqui? E qual o significado das sequências de escape dentro da mensagem-modelo? O formato básico para inserção de um argumento segue o padrão %n!format-string!.

Onde n é o número que identifica o argumento, como já vimos, e format-string é um espaço reservado para identificarmos o tipo do argumento e como ele aparecerá na mensagem de saída.

Existe uma longa explicação sobre o uso de controladores de largura e precisão da saída formatada e sua localização na lista de argumentos, cujo número irá depender se estamos usando valist ou array de DWORDPTRs, sendo que alguns problemas podem surgir se repetirmos esses números de inserção. Em dois momentos da explicação o artigo seja a sugerir que seja usada a função StringCchPrintf, primeiro por que FormatMessage não suporta formatação de ponto flutuantes, e segundo, porque, mesmo que seja possível formatar valores de 64 bits, seria mais fácil se você usasse outra função.

Ainda existe um uso específico para "%0", que é evitar quebra de linha durante a formatação da mensagem, inclusive no final. Esse uso entra em conflito com o nosso flag quando este determina um número máximo de caracteres por linha.

Ainda existe "de bônus" outras strings para preencher limitações que o próprio printf possui, como %%, %t, etc.

Como os programadores habituados com ataques de stack overrun devem deduzir, uma mensagem-modelo mal intencionada pode conter sequências de inserção que não existem na formatação habitual, forçando o vazamento de bytes na string final, o que pode forçar ataques planejados. Como o próprio artigo diz, usar um código de erro arbitrário retornado por uma API qualquer e usar FormatMessage sem a flag FORMATMESSAGEIGNOREINSERTS pode levar a resultados desastrosos.

Esse também é um bônus da MSDN, que te presenteia com exemplos de código tão fantasiosos quanto a própria função, veja o primeiro exemplo, por exemplo:

    #include windows.h
    #include stdio.h
    
    void main(void)
    {
        LPWSTR pMessage = L%1!.s! %4 %5!s!;
        DWORD_PTR pArgs[] = { (DWORD_PTR)4, (DWORD_PTR)2, (DWORD_PTR)LBill,   %1!.s! refers back to the first insertion string in pMessage
             (DWORD_PTR)LBob,                                                 %4 refers back to the second insertion string in pMessage
             (DWORD_PTR)6, (DWORD_PTR)LBill };                                %5!s! refers back to the third insertion string in pMessage
        const DWORD size = 100+1;
        WCHAR buffer[size];
    
        if (!FormatMessage(FORMAT_MESSAGE_FROM_STRING  FORMAT_MESSAGE_ARGUMENT_ARRAY,
                           pMessage, 
                           0,
                           buffer, 
                           size, 
                           (va_list)pArgs))
        {
            wprintf(LFormat message failed with 0x%xn, GetLastError());
            return;
        }
    
         Buffer contains   Bi Bob   Bill.
        wprintf(LFormatted message %sn, buffer);
    }
     
    

Depois ele chega a reimplementar o exemplo usando valist, o que é muito interessante, mas... bom, deixa pra lá. Vamos fazer nosso próprio teste.

Esse é o uso clássico: precisamos de uma descrição de um código de erro para o usuário; um código Win32. A chamada para esse tipo de uso pode ser encapsulada em uma função mais simples:

    #define _CRT_SECURE_NO_WARNINGS // quanta frescura...
    #include <tchar.h>
    #include <windows.h>
    #include <string>
    
    using namespace std;
    
    wstring GetErrorDescription(DWORD errNumber)
    {
    	wstring ret;
    	bool msgOk = false;
    	LPVOID lpMsgBuf = NULL;
    
    	if( FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER // aloque pra mim (não sei o tamanho)
    		| FORMAT_MESSAGE_FROM_SYSTEM // descrição do erro está no sistema
    		| FORMAT_MESSAGE_IGNORE_INSERTS, // ignora os inserts pra não sofrer com hackerzinhos
    		NULL, // sem fonte:
    		errNumber, // a fonte é o código de erro
    		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // idioma padrão
    		(LPTSTR)&lpMsgBuf,// isso é um ponteiro para um ponteiro para um buffer que será alocado
    		0, // nada disso
    		NULL // e nem disso
    		) > 0 ) // maior que zero quer dizer "beleza!"
    	{
    		if( lpMsgBuf ) // só pra...
    		{
    			ret = (PCWSTR) lpMsgBuf; // ok, vamos usar essa string
    			msgOk = true;
    			LocalFree(lpMsgBuf); // não precisamos mais da memória alocada
    		}
    	}
    
    	if( ! msgOk ) // alguma coisa não deu certo
    	{
    		wchar_t msgBuf[100]; // o suficiente
    		_snwprintf(msgBuf, 100, L"Unknown error (code %d)", errNumber);
    		ret = msgBuf;
    	}
    
    	return ret;
    }
    
    int CALLBACK wWinMain(HINSTANCE, HINSTANCE, PWSTR errNumberStr, int)
    {
    	int errNumber = _wtoi(errNumberStr);
    	wstring errDesc = GetErrorDescription(errNumber);
    	MessageBox(NULL, errDesc.c_str(), L"GetLastError", MB_OK | MB_ICONINFORMATION);
    	return errNumber;
    }
     
    

Existem milhares de forma de usar essa função, como você deve ter percebido pelos parâmetros. Não seja tímido: se você conhece algum truquezinho esperto e quer compartilhar com os usuários da FormatMessage, essa é a hora!
