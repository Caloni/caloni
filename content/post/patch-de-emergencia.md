---
date: "2010-11-08"
title: Patch de emergência
categories: [ "code" ]
---
Após um projeto muito bem sucedido, entregue no prazo e homologado em tempo recorde, você e sua equipe estão aproveitando suas devidas férias nas Bahamas, tomando água de coco na sombra de uma palmeira e apreciando a beleza natural da região. Ambas as belezas. =)

![Club-med-beach-governors-harbour-eleuthera-bahamas](http://i.imgur.com/ggKPJuT.jpg)]

Mas eis que liga o seu gerente para o celular vermelho que te entregou no caso de emergências críticas e te avisa que um problema crítico foi detectado em um serviço crítico: o detector de pares. Consegue ver o erro?

![Detector de Pares](http://i.imgur.com/wHctVe6.png)

<blockquote>_Oh, meu Deus!_</blockquote>

Com toda a calma do mundo, você saca o seu netbook, baixa a versão homologada do controle de fonte e descobre facilmente o problema, gerando um patch e recompilando o projeto.

```cpp
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void DoProcess()
{
	int nextNumber = rand() % 1000;
	//bool even = nextNumber % 2;
	bool even = !(nextNumber % 2);
	printf("%d => %s\n", nextNumber, even ? "even" : "odd");
}

int main()
{
	srand( time(0) );

	while( true )
	{
		DoProcess();
		Sleep(3000);
	}
}

 

```

Feliz da vida, avisa o seu chefe que a única coisa que precisam trocar é o serviço crítico. Parar, trocar o arquivo, reiniciar o serviço. Simples.

Porém, ele lhe avisa que esse é um serviço crítico, que não pode parar por nenhum segundo sequer. A atualização terá que ser feita sem parar o ciclo ininterrupto de pares/ímpares chegando do gerador de números randômicos.

Mais uma vez calmo da vida, você diz que isso é coisa de criança. Tudo que precisa fazer é atualizar a versão certa na memória. O arquivo poderá ser renomeado e, quando o serviço puder ser reiniciado, a versão nova será executada. Enquanto isso, o patch na memória bastará para corrigir o problema e não causar nenhum momento inoperante.

Tudo que você precisa é abrir o processo pelo WinDbg, encontrar a versão defeituosa e substituir os bytes certos.

![Corrigindo versão](http://i.imgur.com/zrZQir4.png)

<blockquote>_Nota: O parâmetro -pv permite depurar um processo de forma não-invasiva, mas as threads serão suspensas. Já com -pvr podemos depurar de forma não-invasiva e ainda conseguir manter as threads do processo rodando._</blockquote>

Analisando o disassembly da função nova e antiga podemos perceber que o tamanho delas não mudou (bom sinal), mas o uso dos registradores e a lógica interna teve uma alteração significativa (mau sinal):

    
    Função antiga: bool even = nextNumber % 2;
    test    edx,edx
    setne   al
    mov     byte ptr [ebp-1],al
    movzx   ecx,byte ptr [ebp-1]
    test    ecx,ecx
    je      criticalservice!DoProcess+0x3f (0040105f)
    
    Função nova: bool even = !(nextNumber % 2);
    neg     edx
    sbb     edx,edx
    inc     edx
    mov     byte ptr [ebp-1],dl
    movzx   eax,byte ptr [ebp-1]
    test    eax,eax
    je      criticalservice!DoProcess+0x3f (0040105f)

Podemos começar escrevendo a função nova da memória do processo de teste para um arquivo, e lendo em seguida para cima da função antiga. Só que para isso temos que nos certificar que os endereços que referenciam para fora da função sejam os mesmos. Nesse caso, felizmente, são.

    
    0:001> .writemem c:\tests\newfunc.dat criticalservice!DoProcess 0040107e
    Writing 5f bytes.

Em seguida iremos sobrescrever a função antiga no processo em execução. Para evitar crashes é vital que tenhamos certeza que a função não estará sendo executada nesse momento. No nosso caso basta aguardar a entrada na função Sleep da API, que dorme por 3 segundos, tempo suficiente para a atualização.

![Live Patch!](http://i.imgur.com/bMI63Ka.png)

    
    0:000> .readmem c:\tests\newfunc.dat criticalservice!DoProcess 0040107e
    Reading 5f bytes.

Atualizada a função, apenas nos lembramos de renomear o arquivo antigo e atualizar o novo para evitar reativar o problema. Agora podemos voltar para a apreciação das belezas da natureza...
