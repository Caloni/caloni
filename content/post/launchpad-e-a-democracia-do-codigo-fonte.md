---
date: "2008-06-04"
title: Launchpad e a democracia do código-fonte
categories: [ "blog" ]
---
Após a publicação dos projetos que ando mexendo no próprio saite do Caloni.com.br, recebi uma enxurrada de _downloads _e quase atingi meu limite de fluxo mensal no provedor.

Devido a esse problema inesperado, irei fazer o inevitável: publicar os projetos em um repositório **sério**. E aproveitando que já estou usando o [Bazaar](http://bazaar-vcs.org/), nada melhor que usar o [Launchpad.net](https://launchpad.net/).

#### E o que é o Launchpad.net?

O Launchpad nada mais é do que um lugar onde é possível publicar seus projetos de fonte aberto para que pessoas possam ter livre acesso ao seu histórico de mudanças, assim como a liberdade de criar sua própria ramificação (_branch_). O esquema todo é organizado no formato comunidade, o que permite o compartilhamento não só de código, mas de _bugs_, traduções e, principalmente, idéias.

A idéia é uma das primeiras que usa a modalidade de controle de fonte distribuído, e permite o uso do Bazaar como o controlador oficial, ou importação de outros controles de fonte, em um processo conhecido como espelhamento. Tudo foi feito de forma a amenizar o processo de migração dos sistemas de controle de código centralizado, como CVS e Subversion.

Para ter acesso aos meus projetos iniciais é simples: basta usar o mesmo comando que é usado para obter um novo _branch_ de um projeto do Bazaar:

	
  * [MouseTool](http://www.caloni.com.br/mousetool) - Simulador de clique de mouse

	
    * 

    
    bzr branch https://code.launchpad.net/mtool

	
  * [Influence Board](http://www.caloni.com.br/influence-board) - Complemento ao Winboard que mostra a influência das peças

	
    * 

    
    bzr branch https://code.launchpad.net/infboard

	
  * [Conversor Houaiss Babylon](http://www.caloni.com.br/conversor-de-houaiss-para-babylon-parte-2) - Converte de um dicionário para o outro

	
    * 

    
    bzr branch https://code.launchpad.net/houaiss2babylon

<blockquote>

> 
> #### Atualização
> 
_Aviso de plantão. Não irei mais atualizar os projetos acima no LaunchPad, pois estou considerando reorganizar os fontes para algo mais simplificado. Aguardem por novidades no próprio blogue. _</blockquote>

Como o Bazaar foi feito integrado com o Launchpad, também é possível usar um comando bem mais fácil:

    
    bzr branch lp:project_name

Assim como é possível usar comandos de repositório, também é possível navegar pelo histórico de mudanças do projeto simplesmente usando os linques acima no navegador de sua preferência. E é nessa hora que começa a ficar interessante publicar seu projeto na _web_. Por falar nisso, que tal aprender como

#### Criar seu próprio projeto no Launchpad

Tudo que precisamos é de um _login_, facilmente obtido na página principal, e de registrar um projeto. Para criar o primeiro _branch _e fazermos alterações precisaremos também de um **par de chaves pública e privada** para a conexão SSH criada automaticamente pelo Bazaar. Tudo isso é facilmente possível com o uso das ferramentas do [Putty](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html), um cliente SSH para Windows.

Dessa forma os passos são os seguintes:

1.  Criar um _login_

2. Registrar um projeto

3. Criar um par de chaves através do [PuTTYgen](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html)

![puttygen.png](http://i.imgur.com/68VrP6x.png)

<blockquote>_ATENÇÃO
Devido a alguns problemas, recomendo que use o texto exibido na tela do gerador de chaves em vez de copiar diretamente do arquivo da chave pública para o cadastro no saite. Guarde bem essas chaves com você, pois você as usará sempre que necessário fazer uma modificação no projeto._</blockquote>

4. Atualizar no cadastro do saite (item "Update SSH keys")

5. Usar o [**Pageant** ](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html)para carregar a chave privada na memória

![pageant.png](http://i.imgur.com/dpouXXG.png)

6. Use os comandos do Bazaar passando o usuário e o branch:

    
    bzr branch lp:~seu-usuario/projeto/branch

Simples e direto. E funciona!
