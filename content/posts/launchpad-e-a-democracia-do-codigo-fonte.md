---
date: "2008-06-04"
tags: [ "code", "draft", "tools" ]
title: "Launchpad e a democracia do código-fonte"
---
Após a publicação dos projetos que ando mexendo no próprio saite do Caloni.com.br, recebi uma enxurrada de downloads e quase atingi meu limite de fluxo mensal no provedor.

Devido a esse problema inesperado, irei fazer o inevitável: publicar os projetos em um repositório sério. E aproveitando que já estou usando o Bazaar, nada melhor que usar o Launchpad.net.

O Launchpad nada mais é do que um lugar onde é possível publicar seus projetos de fonte aberto para que pessoas possam ter livre acesso ao seu histórico de mudanças, assim como a liberdade de criar sua própria ramificação (branch). O esquema todo é organizado no formato comunidade, o que permite o compartilhamento não só de código, mas de bugs, traduções e, principalmente, idéias.

A idéia é uma das primeiras que usa a modalidade de controle de fonte distribuído, e permite o uso do Bazaar como o controlador oficial, ou importação de outros controles de fonte, em um processo conhecido como espelhamento. Tudo foi feito de forma a amenizar o processo de migração dos sistemas de controle de código centralizado, como CVS e Subversion.

Para ter acesso aos meus projetos iniciais é simples: basta usar o mesmo comando que é usado para obter um novo branch de um projeto do Bazaar:

	
  * MouseTool - Simulador de clique de mouse
  * Influence Board - Complemento ao Winboard que mostra a influência das peças
  * Conversor Houaiss Babylon - Converte de um dicionário para o outro



Como o Bazaar foi feito integrado com o Launchpad, também é possível usar um comando bem mais fácil:


Assim como é possível usar comandos de repositório, também é possível navegar pelo histórico de mudanças do projeto simplesmente usando os linques acima no navegador de sua preferência. E é nessa hora que começa a ficar interessante publicar seu projeto na web. Por falar nisso, que tal aprender como

Tudo que precisamos é de um login, facilmente obtido na página principal, e de registrar um projeto. Para criar o primeiro branch e fazermos alterações precisaremos também de um par de chaves pública e privada para a conexão SSH criada automaticamente pelo Bazaar. Tudo isso é facilmente possível com o uso das ferramentas do Putty, um cliente SSH para Windows.

Dessa forma os passos são os seguintes:

1.  Criar um login

2. Registrar um projeto

3. Criar um par de chaves através do PuTTYgen

ATENÇÃO
Devido a alguns problemas, recomendo que use o texto exibido na tela do gerador de chaves em vez de copiar diretamente do arquivo da chave pública para o cadastro no saite. Guarde bem essas chaves com você, pois você as usará sempre que necessário fazer uma modificação no projeto.

4. Atualizar no cadastro do saite (item "Update SSH keys")

5. Usar o Pageant para carregar a chave privada na memória

6. Use os comandos do Bazaar passando o usuário e o branch:


Simples e direto. E funciona!
