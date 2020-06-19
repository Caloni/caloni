---
categories: [ "code" ]
date: "2015-05-06"
tags: [ "draft",  ]
title: "Analisando erros pelo filtro do File Monitor"
---
As ferramentas da SysInternals fazem a gente economizar um tempo considerável na resolução de problemas. Não que elas sejam indispensáveis. Tudo que elas fazem é encurtar o caminho entre a análise de um bug e sua resolução, o que acaba sendo muito se considerarmos que programação é 20% codificação e 80% transpiração. Ela é um atalho para muitas coisas, desde achar uma ordem de includes no header errada durante a compilação ou descobrir que por que um processo morreu durante o login.

Curiosamente ambos os exemplos que citei são de uma mesma ferramenta: Process Monitor, ou carinhosamente procmon. Ele é um filho de duas ferramentas hoje extintas, FileMon e RegMon (acho que não preciso explicar o que ambas faziam). Todas são baseadas em drivers que escutam eventos do sistema operacional e um aplicativo que mastiga essa informação e as filtra de diferentes e criativas formas. Vamos utilizá-lo depurando um instalador muito sacana.

A SoSo Company é uma empresa criada na China e que possui programadores muito bons. Eles são altamente especializados em fazer instaladores, e nas horas vagas ainda fritam pastéis de frango (ou "flango", como os nativos costumam chamar). Porém, alguma coisa está acontecendo com uma nova versão do instalador que está dando erro ao rodar o aplicativo após atualizado.


Isso só acontece em algumas máquinas, na maioria delas tudo funciona perfeitamente. Tanto que esse erro só foi encontrado depois de centenas máquinas terem sido atualizadas. E o primeiro a descobrir esse erro foi um cliente muito importante para a Soso. Entre as máquinas desse cliente muito importante, o erro foi acontecer justamente na máquina do CEO da empresa. (Qualquer semelhança com a vida real não é mera coincidência.)

O analista Juquinha, do suporte técnico terceirizado na Índia sul-americana, foi chamado para dar uma olhada nesse problema. Como os chineses não confiam em um não-comedor de pastel de flango, Juquinha não terá acesso ao código-fonte do produto, mas poderá dar uma espiada no instalador. Ei-lo:


Ahhh, bom. O instalador copia tudo e não verifica erro nenhum. Afinal de contas, o que pode dar errado, não é mesmo?

Vamos agora dar uma olhada no código do aplicativo, coisa que nosso analista não terá a oportunidade.

O produto é constituído de três binários: myapp.exe, myanotherapp.exe e mydll.dll. Os dois executáveis usam a DLL (no bom sentido). Cada um deles chama a DLL para realizar algumas operações.


Na DLL há apenas uma função exportada: Version1. Quer dizer, na versão sendo atualizada foi criada uma nova função, a Version2. Vejamos a versão final:


Como já vimos, o instalador da SoSo não está muito preocupado em capturar erros. Haja o que houver, o mundo continua maravilhoso. Porém, depois da atualização esse erro explodiu na máquina do diretor. E agora?

Sem saber muito bem o que fazer, mas com a possibilidade de testar a situação em uma nova máquina (de outro diretor), Juquinha resolveu rodar novamente o instalador, mas dessa vez com a companhia do ProcMon.

Depois disso, para efeito de comparação, rodou o instalador em uma máquina qualquer onde a atualização funciona.

Dica: Quando for comparar muitos eventos (ex: milhares), em vez de olhar um por um é mais fácil exportar para um CSV e deixar um comparador como o [WinMerge}(http://winmerge.org/) fazer o serviço. No entanto, para comparar muitas informações, algumas colunas precisam ser eliminadas, como o horário de execução dos eventos e o PID dos processos.

E voilà! Parece que alguém está bloqueando a atualização de mydll, embora myapp conseguisse ser atualizado (logo concluímos que não é ele).

Agora, se Juquinha é um analista de nível 1, ele precisará compartilhar suas descobertas com outras pessoas da equipe. Para isso, basta duplo-clicar em um evento e usar o botão de cópia. O resultado será um texto com todas as informações necessárias para uma análise aprofundada.


OK, mas onde está o problema? Bom, aqui começa a pesquisa, mas se você já programou para Windows API já há algum tempo sabe que alguém abriu esse arquivo antes com um modo de compartilhamento incompatível com uma escrita (que é o que o nosso instalador tenta fazer). Para saber quem é o culpado, mais uma ferramenta da SysInternals vem a calhar: Process Explorer (eu ia dizer handle.exe, mas ele não funcionou em meus testes).

Através da opção de menu Find, Find Handle or DLL o culpado se mostrou mais próximo do que imaginávamos. O myanotherapp.exe fica bloqueando a dll no momento da atualização! Na verdade, o grande culpado foi mesmo o programador desse instalador, que sequer tem ideia das centenas de erros que podem ocorrer durante uma instalação/atualização. Azar do suporte técnico desse produto =/
