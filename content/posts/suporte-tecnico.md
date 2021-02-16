---
date: "2010-11-05"
title: Suporte técnico
tags: [ "draft", "blog" ]
---
Máquina com parte do registro corrompida, notadamente alguma sub-chave de HKEY_CLASSES_ROOT. Resultado: ao rodar um script que abre uma segunda janela e tenta usar seu método focus é exibida a seguinte mensagem:

![Erro de automação?](http://i.imgur.com/IGR3VJC.png)
_"<Mensagem do cliente> - A classe não dá suporte para automação"_
Abaixo um exemplo simples para ter uma ideia em JS:

    
    var win = window.open('minha_url_do_coracao.htm');
    win.focus(); // aqui dá o erro

A primeira coisa que se faz nesse caso é pesquisar no Google por pessoas que já tiveram esse problema. A [maioria](http://www.google.com/search?q=class+does+not+support+automation) dizia ser necessária registrar novamente as DLLs do navegador/shell, coisa que fizemos à exaustão e não resolveu o problema. Também imaginamos haver relação com a versão da **SDocVw.dll** que estava alocada na lista de assemblies .NET cacheados, o chamado GAC. Ou seja, já estávamos viajando geral.

No meio dos procedimentos batidos que todos fazem a lista abaixo resume bem:

	
  * Restaurar instalação do Internet Explorer.

	
  * Atualizar Internet Explorer.

	
  * Rodar Windows Update.

	
  * Registrar novamente DLLs do Shell (ShDocVw.dll, etc).

No meio das análises não-tão-batidas que foram feitas estavam os seguintes itens:

	
  * Log de operações pelo Process Monitor da abertura do browser até o erro.

	
  * Dump gerado no momento da mensagem de erro.

	
  * Comparação de registro exportado com máquina sadia.

Nada parecia resolver o impasse, a não ser reinstalar o Windows, coisa que o cliente não queria. Dessa forma, A última tentativa não-enlouquecida de tentar descobrir a causa do problema foi usar uma VM e importar o registro exportado da máquina defeituosa.

Que não revelou a anomalia.

Partindo disso, imaginei que o que ocorria era que havia algo faltando no registro danificado, e não algo a mais. Dessa forma, realizei a seguinte operação:

	
  * Exportei o registro da máquina saudável.

	
  * Transformei a exportação em exclusão total das chaves.

	
  * Importei ambos os registros no esquema "apaga tudo cria tudo de novo".

![Exportando e importando registro](http://i.imgur.com/l7Rc7kY.png)

Problema reproduzido.

Agora restava saber qual chave exata estava faltando e o que isso impactava no comportamento do browser.

O registro exportado da VM possuía cerca de 30.000 linhas com chaves e sub-chaves. Se fosse feita a importação por partes, dividindo-se sempre pela metade e testando o acesso à página todas as vezes, teríamos no máximo que fazer uns 15 testes.

Foi esse o procedimento seguido:

	
  1. Criar snapshot com o estado inalterado do registro.

	
  2. Apagar metade do registro original exportado (máquina real).

	
  3. Arrastar metade do registro original e importá-lo (apaga chaves).

	
  4. Importar registro danificado do cliente (já na VM).

	
  5. Se deu erro de novo, repassar os passos 2 a 3.

	
  6. Se não deu erro, testar os passos 3 e 4 com a outra metade.

![Snapshots da VMWare](http://i.imgur.com/hhxZgqZ.png)

Essa série de passos foi reproduzida em menos de uma hora até chegarmos a apenas uma linha no registro:

    
    [-HKEY_CLASSES_ROOT\CLSID\{C5598E60-B307-11D1-B27D-006008C3FBFB}]

Que se revelou pertencer à DLL [dispex.dll](http://www.google.com.br/search?q=dispex.dll):

<blockquote>_"dispex.dll is a module that contains COM interfaces used by Visual Basic scripts"_</blockquote>

Pesquisando soluções de restauração achei [esse KB](http://support.microsoft.com/kb/836929) que explica que existe um aplicativo chamado McRepair que teoricamente conserta a bagunça.

Não conserta.

Porém, ao usar o Method 1 (registrar novamente a DLL) o problema foi resolvido. Exportei o registro antes e depois da operação e por algum motivo a máquina do cliente estava com o GUID das interfaces IDispatchEx e IObjectIdentity adulteradas:

    
    Antes: C5598E60-B307-11D1-B27D-006008C3FBFB}

    
    Depois: 10E2414A-EC59-49D2-BC51-5ADD2C36FEBC}

Realizei o mesmo teste com nossa DLL que gerou o problema inicial e descobri que não houve mudanças nessa parte do registro por conta dela.

Fica assim indefinida a origem do "corrompimento" dessa parte do registro, apesar de localizada.

Esse artigo é pra mostrar que não é só de ifs e elses que vive um programador =)
