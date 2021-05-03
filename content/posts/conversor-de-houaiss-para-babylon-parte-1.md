---
categories:
- code
date: '2008-02-27'
title: Conversor de Houaiss para Babylon - parte 1
---

Este artigo é sobre desmontar e montar novamente. Iremos descobrir como as entradas do dicionário Houaiss eletrônico estão gravadas em um primeiro momento, para depois remontarmos essa informação de maneira que ela possa ser usada em outro dicionário de uso mais flexível, o Babylon. Ou seja, este não é um guia de vandalismo. Estava apenas querendo usar um dicionário de qualidade excelente em outro dicionário cuja interface é muito boa.

Considero o Houaiss o melhor dicionário da atualidade, uso todo santo dia e tenho todo o respeito por ele. Possuo uma cópia legalizada exatamente por isso. Além, é óbvio, pelo escandaloso cinismo que seria se eu, desenvolvedor de software, pirateasse os que utilizo. Porém, acredito que tudo tenha um limite: respeito os direitos de quem desenvolve o programa se o programa se dá ao respeito de ser pago. Quer dizer, eu realmente uso muito esse dicionário, e ele é útil para mim. Logo, nada mais justo do que adquiri-lo como manda a lei.

Assim como adquiri o Houaiss, também comprei o Babylon, um programa-dicionário, cuja interface permite buscar o significado das palavras lidas no computador simplesmente clicando nelas. A qualidade de seu dicionário português embutido é medíocre, mas o que ele ganha mesmo é em sua interface fácil para acessar palavras. Exatamente por faltar um dicionário em português de peso no Babylon, e eu ter adquirido outro muito melhor, quis que ambos funcionassem juntos, ou seja, acesso o Babylon e tenho o resultado adicional desse meu dicionário tupiniquim.

O Babylon possui um mecanismo para criação de dicionários chamado Babylon Builder. É muito simples e fácil de usar (além de ser gratuito). Sabendo que possuo ambas as licenças desses dois programas me sinto mais aliviado em tentar desencriptar a base de dados do primeiro para construir um dicionário para o segundo, e assim realizar meu sonho de consumo: um Babylon com um dicionário de peso!

![Licença do Houaiss](/img/houaiss-license.png)

É necessário que, na hora da instalação, seja escolhida a opção de copiar os arquivos para o disco. Estarei utilizando o path padrão de um Windows em português, que é "C:\Arquivos de Programas\Houaiss".

![Instalação do Houaiss](/img/houaiss-install.png)

A estrutura de diretórios interna da instalação é bem simples:

 - Raiz. Arquivos de ajuda, desinstalador, executável principal, etc.
 - Quadros. Figuras com conhecimentos gerais, como calendários, signos, línguas mais faladas, etc.
 - Dicionario. Provavelmente onde está todo o dicionário, cerca de 120 MB.

Se analisarmos o conteúdo dos arquivos dentro da pasta Dicionario vamos descobrir que ele se parece com "garbage nonsense", apesar de existir um certo padrão. O padrão revela que pode se tratar de uma criptografia muito simples, talvez até um simples XOR.

    for %i in (*.*) do type %i | less

![Saída dos arquivos do dicionário](/img/cmd.gif)

Sabendo que o conteúdo do dicionário está em arquivos localizados no disco, e que teoricamente o programa não deve copiar todo o conteúdo para a memória, iremos depurar o processo do dicionário de olho nas chamadas da função ReadFile quando clicarmos em uma definição de palavra.

    windbg -pn houaiss2.exe
    0:001> bp kernel32!ReadFile "dd @$csp L6" $$ Dando uma olhada nos parâmetros
    g

Ao clicar na definição de "programa-fonte", o breakpoint é ativado:

    0012fa70  0040a7a9 00000200 08bbf1d0 00000200 0012fa80  0012fa88 00000000
    eax=0012fa88 ebx=00000200 ecx=00000200 edx=08bbf1d0 esi=08bbf1d0 edi=00000200
    eip=7c80180e esp=0012fa70 ebp=0012facc iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    kernel32!ReadFile:
    7c80180e 6a20            push    20h
    
    $$ dados acima:
    $$  - O buffer de saída é 08bbf1d0 
    $$  - O número de bytes lidos é 200

    0:000> db 08bbf1d0 L80
    08bbf1d0  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    08bbf1e0  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    08bbf1f0  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    08bbf200  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    08bbf210  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    08bbf220  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    08bbf230  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
    08bbf240  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................

    0:000> bp /1 @$ra "db 08bbf1d0 L80"
    0:000> g
    08bbf1d0  1f 65 67 64 5c 67 56 62-56 22 5b 64 63 69 5a 02  .egd\gVbV"[dciZ.
    08bbf1e0  ff 38 68 23 62 23 02 ff-59 70 51 5e 15 68 4d 4d  .8h#b#..YpQ^.hMM
    08bbf1f0  72 02 ff 49 5e 63 5b 02-ff 2f 65 67 64 5c 67 56  r..I^c[../egd\gV
    08bbf200  62 56 15 59 5a 15 58 64-62 65 6a 69 56 59 64 67  bV.YZ.XdbejiVYdg
    08bbf210  15 5a 62 15 68 6a 56 15-5b 64 67 62 56 15 64 67  .Zb.hjV.[dgbV.dg
    08bbf220  5e 5c 5e 63 56 61 21 15-56 63 64 69 56 59 64 15  ^\^cVa!.VcdiVYd.
    08bbf230  65 5a 61 64 15 65 67 64-5c 67 56 62 56 59 64 67  eZad.egd\gVbVYdg
    08bbf240  15 5a 62 15 6a 62 56 15-61 5e 63 5c 6a 56 5c 5a  .Zb.jbV.a^c\jV\Z
    eax=00000001 ebx=00000200 ecx=7c801898 edx=7c90eb94 esi=08bbf1d0 edi=00000200
    eip=0040a7a9 esp=0012fa88 ebp=0012facc iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    Houaiss2+0xa7a9:
    0040a7a9 85c0            test    eax,eax

Depois da leitura, não temos muitas alternativas a não ser fazer o tracking de chamadas até que o mesmo buffer esteja desencriptado. Esse é o caminho natural das coisas, mas poderia haver complicações secundárias, como uma cópia de buffer antes de seu uso. Estou usando passos simples porque realmente foi muito simples descobrir o segredo da ofuscação.

    0:000> p
    Houaiss2+0xa7ab:
    0040a7ab 7507            jne     Houaiss2+0xa7b4 (0040a7b4)              [br=1]
    0:000> p
    Houaiss2+0xa7b4:
    0040a7b4 8b0424          mov     eax,dword ptr [esp]  ss:0023:0012fa88=00000200
    0:000> p
    Houaiss2+0xa7b7:
    0040a7b7 5a              pop     edx
    0:000> p
    Houaiss2+0xa7b8:
    0040a7b8 5f              pop     edi
    0:000> p
    Houaiss2+0xa7b9:
    0040a7b9 5e              pop     esi
    0:000> p
    Houaiss2+0xa7ba:
    0040a7ba 5b              pop     ebx
    0:000> p
    Houaiss2+0xa7bb:
    0040a7bb c3              ret
    0:000> p
    Houaiss2+0xb9062:
    004b9062 8945f8          mov     dword ptr [ebp-8],eax ss:0023:0012fac4=00000000
    0:000> p
    Houaiss2+0xb9065:
    004b9065 0375f8          add     esi,dword ptr [ebp-8] ss:0023:0012fac4=00000200
    0:000> p
    Houaiss2+0xb9068:
    004b9068 807b1900        cmp     byte ptr [ebx+19h],0       ds:0023:090cf1f9=01
    0:000> p
    Houaiss2+0xb906c:
    004b906c 7410            je      Houaiss2+0xb907e (004b907e)             [br=0]
    0:000> p
    Houaiss2+0xb906e:
    004b906e 8b4df8          mov     ecx,dword ptr [ebp-8] ss:0023:0012fac4=00000200
    0:000> p
    Houaiss2+0xb9071:
    004b9071 8b933c200300    mov     edx,dword ptr [ebx+3203Ch] ds:0023:0910121c=00000000
    0:000> p
    Houaiss2+0xb9077:
    004b9077 8bc3            mov     eax,ebx
    0:000> p
    Houaiss2+0xb9079:
    004b9079 e8eef9ffff      call Houaiss2+0xb8a6c (004b8a6c)

    0:000> p
    Houaiss2+0xb9

    0:000> db 08bbf1d0 L80
    08bbf1d0  2a 70 72 6f 67 72 61 6d-61 2d 66 6f 6e 74 65 0d  *programa-fonte.
    08bbf1e0  0a 43 73 2e 6d 2e 0d 0a-64 7b 5c 69 20 73 58 58  .Cs.m...d{\i sXX
    08bbf1f0  7d 0d 0a 54 69 6e 66 0d-0a 3a 70 72 6f 67 72 61  }..Tinf..:progra
    08bbf200  6d 61 20 64 65 20 63 6f-6d 70 75 74 61 64 6f 72  ma de computador
    08bbf210  20 65 6d 20 73 75 61 20-66 6f 72 6d 61 20 6f 72   em sua forma or
    08bbf220  69 67 69 6e 61 6c 2c 20-61 6e 6f 74 61 64 6f 20  iginal, anotado
    08bbf230  70 65 6c 6f 20 70 72 6f-67 72 61 6d 61 64 6f 72  pelo programador
    08bbf240  20 65 6d 20 75 6d 61 20-6c 69 6e 67 75 61 67 65   em uma linguage

Pois bem. Logo depois de chamar a função Houaiss2+0xb8a6c magicamente o buffer incompreensível se transformou no início da definição da palavra "programa-fonte". Como não temos o programa-fonte do Houaiss, teremos que descer mais um nível no "assemblão", mesmo. Note que a saída abaixo se repete porque reexecutei os passos anteriores para cair na mesma condição.

    Houaiss2+0xb9079:
    004b9079 e8eef9ffff      call    Houaiss2+0xb8a6c (004b8a6c)
    0:000> t

    eax=08bbf1a0 ebx=08bbf1a0 ecx=00000200 edx=00000000 esi=00000200 edi=02fe8661
    eip=004b8a6c esp=0012fa98 ebp=0012facc iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    Houaiss2+0xb8a6c:
    004b8a6c 53              push    ebx
    0:000> p
    eax=08bbf1a0 ebx=08bbf1a0 ecx=00000200 edx=00000000 esi=00000200 edi=02fe8661
    eip=004b8a6d esp=0012fa94 ebp=0012facc iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    Houaiss2+0xb8a6d:
    004b8a6d 03ca            add     ecx,edx
    0:000> p
    eax=08bbf1a0 ebx=08bbf1a0 ecx=00000200 edx=00000000 esi=00000200 edi=02fe8661
    eip=004b8a6f esp=0012fa94 ebp=0012facc iopl=0         nv up ei pl nz na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000206
    Houaiss2+0xb8a6f:
    004b8a6f 49              dec     ecx
    0:000> p
    eax=08bbf1a0 ebx=08bbf1a0 ecx=000001ff edx=00000000 esi=00000200 edi=02fe8661
    eip=004b8a70 esp=0012fa94 ebp=0012facc iopl=0         nv up ei pl nz ac pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000216
    Houaiss2+0xb8a70:
    004b8a70 2bca            sub     ecx,edx
    0:000> p
    eax=08bbf1a0 ebx=08bbf1a0 ecx=000001ff edx=00000000 esi=00000200 edi=02fe8661
    eip=004b8a72 esp=0012fa94 ebp=0012facc iopl=0         nv up ei pl nz na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000206
    Houaiss2+0xb8a72:
    004b8a72 7c12            jl      Houaiss2+0xb8a86 (004b8a86)             [br=0]
    0:000> p
    eax=08bbf1a0 ebx=08bbf1a0 ecx=000001ff edx=00000000 esi=00000200 edi=02fe8661
    eip=004b8a74 esp=0012fa94 ebp=0012facc iopl=0         nv up ei pl nz na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000206
    Houaiss2+0xb8a74:
    004b8a74 41              inc     ecx
    0:000> p
    eax=08bbf1a0 ebx=08bbf1a0 ecx=00000200 edx=00000000 esi=00000200 edi=02fe8661
    eip=004b8a75 esp=0012fa94 ebp=0012facc iopl=0         nv up ei pl nz ac pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000216
    Houaiss2+0xb8a75:
    004b8a75 33db            xor     ebx,ebx
    0:000> p
    eax=08bbf1a0 ebx=00000000 ecx=00000200 edx=00000000 esi=00000200 edi=02fe8661
    eip=004b8a77 esp=0012fa94 ebp=0012facc iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    Houaiss2+0xb8a77:
    004b8a77 8a5c1030        mov     bl,byte ptr [eax+edx+30h]  ds:0023:08bbf1d0=1f
    0:000> p
    eax=08bbf1a0 ebx=0000001f ecx=00000200 edx=00000000 esi=00000200 edi=02fe8661
    eip=004b8a7b esp=0012fa94 ebp=0012facc iopl=0         nv up ei pl zr na pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000246
    Houaiss2+0xb8a7b:
    004b8a7b 83c30b          add ebx,0Bh
    0:000> p
    eax=08bbf1a0 ebx=0000002a ecx=00000200 edx=00000000 esi=00000200 edi=02fe8661
    eip=004b8a7e esp=0012fa94 ebp=0012facc iopl=0         nv up ei pl nz ac po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000212
    Houaiss2+0xb8a7e:
    004b8a7e 885c1030        mov     byte ptr [eax+edx+30h],bl ds:0023:08bbf1d0=1f
    0:000> p
    eax=08bbf1a0 ebx=0000002a ecx=00000200 edx=00000000 esi=00000200 edi=02fe8661
    eip=004b8a82 esp=0012fa94 ebp=0012facc iopl=0         nv up ei pl nz ac po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000212
    Houaiss2+0xb8a82:
    004b8a82 42              inc edx
    0:000> p
    eax=08bbf1a0 ebx=0000002a ecx=00000200 edx=00000001 esi=00000200 edi=02fe8661
    eip=004b8a83 esp=0012fa94 ebp=0012facc iopl=0         nv up ei pl nz na po nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000202
    Houaiss2+0xb8a83:
    004b8a83 49              dec ecx
    0:000> p
    eax=08bbf1a0 ebx=0000002a ecx=000001ff edx=00000001 esi=00000200 edi=02fe8661
    eip=004b8a84 esp=0012fa94 ebp=0012facc iopl=0         nv up ei pl nz ac pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000216
    Houaiss2+0xb8a84:
    004b8a84 75ef            jne
    Houaiss2+0xb8a75 (004b8a75)             [br=1]
    0:000> p
    eax=08bbf1a0 ebx=0000002a ecx=000001ff edx=00000001 esi=00000200 edi=02fe8661
    eip=004b8a75 esp=0012fa94 ebp=0012facc iopl=0         nv up ei pl nz ac pe nc
    cs=001b  ss=0023  ds=0023  es=0023  fs=003b  gs=0000             efl=00000216
    Houaiss2+0xb8a75:
    004b8a75 33db            xor     ebx,ebx
    ...

Estamos diante de um loop, que, ao analisar o valor de ecx, sabemos que se repete 0x200 vezes, que é exatamente o número de bytes lidos pela função ReadFile. Coincidência? Seria, se não estivesse bem no meio do loop a referência ao próprio buffer usado na leitura (08bbf1d0).

Acredito que para todo profissional de engenharia reversa a parte mais emocionante é a descoberta do grande segredo por trás do desafio, o porquê das coisas estarem como estão e o que fazer para desfazer a mágica da segurança: a chave!

    Houaiss2+0xb8a7b:
    004b8a7b 83c30b          add ebx,0Bh

Note que essa operação é realizada para cada byte lido do buffer usado na leitura do arquivo. Conseqüentemente, não é difícil de imaginar que o valor 0x0B é a chave usada para ofuscar o dicionário em arquivo, subtraindo esse valor de cada byte. Para desfazer a ofuscação, portanto, basta adicionar novamente o mesmo valor, que é exatamente o que faz a instrução assembly acima, e o meu singelo código de desofuscação do dicionário Houaiss abaixo:

    #define _CRT_SECURE_NO_DEPRECATE
    #include <windows.h>
    #include <stdio.h>
    
    //#define HOUAISS_PATH "C:\\Projects\\Temp\\HouaissReader\\Houaiss\\"
    
    int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR cmdLine, int)
    {
    	CHAR HOUAISS_PATH[MAX_PATH] = { };
    
    	sscanf(cmdLine, "-p \"%[^\"]s", HOUAISS_PATH);
    
    	if( HOUAISS_PATH[0] == 0 )
    	{
    		MessageBox(NULL, "How to use:\r\nHouCalc.exe -p \"C:\\HouaissPath\\\"", 
    			"Houaiss Decipher v. alpha", 0);
    		return 0;
    	}
    
    	for( int fileIdx = 1; fileIdx < 64; ++fileIdx )
    	{
    		CHAR path1[MAX_PATH];
    		CHAR path2[MAX_PATH];
    
    		sprintf(path1, "%sdeah%03d.dhx", HOUAISS_PATH, fileIdx);
    		sprintf(path2, "%sdeah%03d.txt", HOUAISS_PATH, fileIdx);
    
    		HANDLE file1 = CreateFile(path1, GENERIC_READ, FILE_SHARE_READ,
    			NULL, OPEN_EXISTING, 0, NULL);
    
    		HANDLE file2 = CreateFile(path2, GENERIC_READ | GENERIC_WRITE, 0,
    			NULL, CREATE_ALWAYS, 0, NULL);
    
    		if( file1 != INVALID_HANDLE_VALUE && file2 != INVALID_HANDLE_VALUE )
    		{
    			DWORD fileSize = GetFileSize(file1, NULL);
    
    			if( SetFilePointer(file2, fileSize, NULL, FILE_BEGIN) )
    			{
    				SetEndOfFile(file2);
    
    				HANDLE map1 = CreateFileMapping(file1, NULL, PAGE_READONLY, 0, 0, NULL);
    				HANDLE map2 = CreateFileMapping(file2, NULL, PAGE_READWRITE, 0, 0, NULL);
    
    				if( map1 && map2 )
    				{
    					PBYTE view1 = (PBYTE) MapViewOfFile(map1, FILE_MAP_READ, 0, 0, 0);
    					PBYTE view2 = (PBYTE) MapViewOfFile(map2, FILE_MAP_WRITE, 0, 0, 0);
    
    					if( view1 && view2 )
    					{
    						for( DWORD i = 0; i < fileSize; ++i )
    						{
    							view2[i] = view1[i] + 0x0B;
    						}
    					}
    
    					if( view1 )
    						UnmapViewOfFile(view1);
    					if( view2 )
    						UnmapViewOfFile(view2);
    				}
    
    				if( map1 )
    					CloseHandle(map1);
    				if( map2 )
    					CloseHandle(map2);
    			}
    		}
    
    		if( file1 )
    			CloseHandle(file1);
    		if( file2 )
    			CloseHandle(file2);
    	}
    
    	return 0;
    }

Parte da mágica já foi feita, talvez a mais importante e divertida. Daqui pra lá deixaremos o WinDbg de lado e analisaremos o formato em que o texto do dicionário é armazenado, ignorando sua ofuscação básica, que não é mais um problema. Como o artigo já está extenso o suficiente, vou deixar a continuação dessa empreitada para uma futura publicação.