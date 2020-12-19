---
date: "2015-05-06"
tags: [ "code" ]
title: "Analisando Erros Pelo Filtro do File Monitor"
---
As ferramentas da SysInternals fazem a gente economizar um tempo considerável na resolução de problemas. Não que elas sejam indispensáveis. Tudo que elas fazem é encurtar o caminho entre a análise de um bug e sua resolução, o que acaba sendo muito se considerarmos que programação é 20% codificação e 80% transpiração. Ela é um atalho para muitas coisas, desde achar uma ordem errada de includes no header durante a compilação ou descobrir que por que um processo morreu durante o login.

Curiosamente ambos os exemplos que citei são de uma mesma ferramenta: [Process Monitor], ou carinhosamente chamado de procmon. Ele é um filho de duas ferramentas hoje extintas, FileMon e RegMon (acho que não preciso explicar o que ambas faziam). Todas são baseadas em drivers que escutam eventos do sistema operacional e um aplicativo que mastiga essa informação e as filtra de diferentes e criativas formas. Vamos utilizá-lo depurando um instalador muito sacana.

A SoSo Company é uma empresa criada na China e que possui programadores muito bons. Eles são altamente especializados em fazer instaladores, e nas horas vagas ainda fritam pastéis de frango (ou "flango", como os nativos costumam chamar). Porém, alguma coisa está acontecendo com uma nova versão do instalador que está dando erro ao rodar o aplicativo após atualizado. Isso só acontece em algumas máquinas, na maioria delas tudo funciona perfeitamente. Tanto que esse erro só foi encontrado depois de centenas de máquinas terem sido atualizadas (oh, não).

O primeiro a descobrir esse erro foi um cliente muito importante para a SoSo, e entre as máquinas desse cliente muito importante o erro foi acontecer justamente na máquina do CEO da empresa. (Qualquer semelhança com a vida real não é mera coincidência.)

O analista Juquinha do suporte técnico terceirizado na Índia sul-americana foi chamado para dar uma olhada nesse problema. Como os chineses não confiam em um não-comedor de pastel de flango Juquinha não terá acesso ao código-fonte do produto, mas poderá dar uma espiada no instalador, que faz algo parecido com o código abaixo:

    print("Happy installing...");
    CreateDir("/soso");
    CpFile(L"soso.exe");
    CpFile(L"soso.dll");
    CpFile(L"soso_ui.exe");
    print("All light =)");

O instalador copia tudo e não verifica erro nenhum; afinal de contas, o que pode dar errado, não é mesmo? Haja o que houver, o mundo continua maravilhoso. Porém, depois da atualização esse erro explodiu na máquina do diretor. E agora?

Sem saber muito bem o que fazer, mas com a possibilidade de testar a situação em uma nova máquina (de outro diretor), Juquinha resolveu rodar novamente o instalador, mas dessa vez com a companhia do ProcMon. Depois disso, para efeitos de comparação, rodou o instalador em uma máquina qualquer onde a atualização funciona. Ciente de que o ProcMon por padrão captura centenas de milhares de eventos e mostra na tela, Juquinha filtra os eventos pelos quais mais interessam e exporta-os para um arquivo CSV. Com isso ele pode agora usar um comparador de arquivos como o [WinMerge] para terminar o serviço. No entanto, para conseguir comparar muitas informações de máquinas distintas, tenha em mente que algumas colunas precisam ser eliminadas, como o horário de execução dos eventos e o PID dos processos.

Depois de muito fuçar nessa comparação eis que nosso herói encontra um evento-chave, que ocorre apenas na máquina do diretor:

    Date: 2015-05-08 20:29:52
    Class: File System
    Operation: CreateFile
    Result: SHARING VIOLATION
    Path: /soso/soso.dll
    TID: 1512
    Duration: 0.0000458
    Desired Access: RWD
    Disposition: OverwriteIf
    Options: Seq, Sync IO, NDF
    Attributes: A
    ShareMode: None
    AllocationSize: 65,024

E voilà! Parece que alguém está bloqueando a atualização de soso.dll, embora soso.exe conseguisse ser atualizado (logo concluímos que não é ele).

Se Juquinha é analista de nível 1 ele precisará compartilhar suas descobertas com outras pessoas da equipe. Para isso, basta duplo-clicar o evento no ProcMon e usar o botão de cópia. O resultado será um texto com todas as informações necessárias para uma análise mais aprofundada.

OK, mas onde está o problema? Bom, aqui começa a pesquisa, mas se você já programou para Windows API já há algum tempo sabe que alguém abriu esse arquivo antes com um modo de compartilhamento incompatível com uma escrita (que é o que o nosso instalador tenta fazer). Para saber quem é o culpado, mais uma ferramenta da SysInternals vem a calhar: [Process Explorer] (eu ia dizer handle.exe, mas ele não funcionou em meus testes).

No Process Explorer existe uma opção no menu chamada Find, Find Handle or DLL, onde o culpado se mostra rapidamente. No caso em questão (fictício, mas com uma ponta de verdade) o culpado foi o soso_ui.exe, que fica bloqueando a dll no momento da atualização! Na verdade, o grande culpado foi mesmo o programador desse instalador, que sequer tem ideia das centenas de erros que podem ocorrer durante uma atualização. Azar do suporte técnico desse produto.

[Process Explorer]: https://docs.microsoft.com/en-us/sysinternals/downloads/process-explorer
[Process Monitor]: https://docs.microsoft.com/en-us/sysinternals/downloads/procmon
[WinMerge]: http://winmerge.org
