---
categories: [ "code" ]
date: "2010-11-08"
tags: [ "draft",  ]
title: "Patch de emergência"
---
Após um projeto muito bem sucedido, entregue no prazo e homologado em tempo recorde, você e sua equipe estão aproveitando suas devidas férias nas Bahamas, tomando água de coco na sombra de uma palmeira e apreciando a beleza natural da região. Ambas as belezas. =)

Mas eis que liga o seu gerente para o celular vermelho que te entregou no caso de emergências críticas e te avisa que um problema crítico foi detectado em um serviço crítico: o detector de pares. Consegue ver o erro?

Oh, meu Deus!

Com toda a calma do mundo, você saca o seu netbook, baixa a versão homologada do controle de fonte e descobre facilmente o problema, gerando um patch e recompilando o projeto.


Feliz da vida, avisa o seu chefe que a única coisa que precisam trocar é o serviço crítico. Parar, trocar o arquivo, reiniciar o serviço. Simples.

Porém, ele lhe avisa que esse é um serviço crítico, que não pode parar por nenhum segundo sequer. A atualização terá que ser feita sem parar o ciclo ininterrupto de pares/ímpares chegando do gerador de números randômicos.

Mais uma vez calmo da vida, você diz que isso é coisa de criança. Tudo que precisa fazer é atualizar a versão certa na memória. O arquivo poderá ser renomeado e, quando o serviço puder ser reiniciado, a versão nova será executada. Enquanto isso, o patch na memória bastará para corrigir o problema e não causar nenhum momento inoperante.

Tudo que você precisa é abrir o processo pelo WinDbg, encontrar a versão defeituosa e substituir os bytes certos.

Nota: O parâmetro -pv permite depurar um processo de forma não-invasiva, mas as threads serão suspensas. Já com -pvr podemos depurar de forma não-invasiva e ainda conseguir manter as threads do processo rodando.

Analisando o disassembly da função nova e antiga podemos perceber que o tamanho delas não mudou (bom sinal), mas o uso dos registradores e a lógica interna teve uma alteração significativa (mau sinal):


Podemos começar escrevendo a função nova da memória do processo de teste para um arquivo, e lendo em seguida para cima da função antiga. Só que para isso temos que nos certificar que os endereços que referenciam para fora da função sejam os mesmos. Nesse caso, felizmente, são.


Em seguida iremos sobrescrever a função antiga no processo em execução. Para evitar crashes é vital que tenhamos certeza que a função não estará sendo executada nesse momento. No nosso caso basta aguardar a entrada na função Sleep da API, que dorme por 3 segundos, tempo suficiente para a atualização.


Atualizada a função, apenas nos lembramos de renomear o arquivo antigo e atualizar o novo para evitar reativar o problema. Agora podemos voltar para a apreciação das belezas da natureza...
