---
categories:
- blog
date: '2008-05-19'
tags:
title: Busca do Google com atalhos
---

Eu adoro atalhos de teclado. Desde meus primeiros anos usando computadores, atalhos têm se tornado minha obsessão. Sempre faço minha pesquisa pessoal de tempos em tempos, colecionando e usando novos atalhos descobertos. Por um bom tempo eu evitei ter que usar o mouse, treinando-me para lembrar de todas as seqüências de teclas que conhecia.

Eu não tenho nada contra o uso do mouse nem as pessoas que o usam. Eu apenas não sou tão entusiástico em usar o mouse. Por algum tempo, eu até acreditei que o ponteiro do cursor estava me atrapalhando, então eu desenvolvi um programa para tirá-lo da tela (usando um atalho de teclado, claro). Porém, mais uma vez, não sou contra seu uso. Eu mesmo uso-o de vez em quando (quando eu preciso).

Até algum tempo atrás a web não era muito convidativa para usuários de atalhos. Então surgiu o Google e as suas aplicações que suportavam essa característica, o que me deu uma razão a mais para passar a usar seu cliente de e-mail e leitor de notícias sem pressionar constantemente a tecla Tab. No entanto, ainda faltava a mesma funcionalidade para seu buscador. Felizmente, isso não é mais verdade.

Ainda em teste, eu comecei a usar os novos atalhos de teclado na busca do Google disponíveis no saite Google Experimental Search. Até agora existem atalhos para próximo resultado (J), resultado anterior (K), abertura da busca (O ou Enter) e colocação do cursor na caixa de busca (/). Eles funcionam exatamente como o Gmail e o Google Reader. Eu fiquei tão empolgado com a idéia que mudei o complemento de busca do Google de dentro do meu Firefox. E agora vou contar como isso pode ser feito facilmente (nota: minhas dicas servem para usuário de Windows apenas).

Provavelmente seu complemento de busca estará em uma das duas pastas abaixo:

    %programfiles%\Mozilla Firefox\searchplugins
    %appdata%\Mozilla\Firefox\Profiles\*.default\searchplugins

O arquivo do complemento tem o nome google.xml e você pode editá-lo usando o Bloco de Notas ou qualquer outro editor de texto simples (sem formatação). Abaixo está o ponto onde você deve inserir a nova linha que irá ativar os atalhos dentro da página de buscas do Google.

    <Url type="text/html" method="GET" template="http://www.google.com/search">
    <Param name="q" value="{searchTerms}"/>
    <...>
    <Param name="esrch" value="BetaShortcuts"/> <!-- Google Shortcuts Here -->
    <!-- Dynamic parameters -->
    <...>
    </Url>

É isso aí. Agora você pode ter o melhor dos dois mundos: o melhor buscador da internete com atalhos. Existirá maneira de se tornar ainda mais produtivo?
