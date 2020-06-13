---
categories: [ "code" ]
date: "2008-06-26"
tags: [ "draft",  ]
title: "Primeiros passos na documentação de código-fonte usando Doxygen"
---
Comentários são essenciais em um código-fonte bem feito. O código pode até fazer milagres, salvar vidas e multiplicar pães, mas se não tiver um apóstolo eficiente que escreva um evangelho para ele, as pessoas não vão conseguir usar!

OK, a analogia foi horrível.

Bom, já que é pra fazer comentários, porque não fazê-los de uma forma que seja possível extrair todo esse texto diretamente do fonte e transformá-lo em documentação? Dessa forma você evita ter que abrir o Word (arght!) e evita que a documentação fique desatualizada quando o documentador do seu projeto for embora da empresa.

Vocês não têm documentador no projeto? Ah, tá. Bem-vindo ao grupo.

O Doxygen é uma ferramenta que consegue extrair comentários do seu código-fonte, formatados ou não, e transformar em arquivos html, doc, chm, etc. O resultado é muito impressionante, pois ele é capaz de interpretar algumas linguagens (como C++) e mostrar a hierarquia de classes e funções.

Ele não obriga que o desenvolvedor formate corretamente os comentários, mas ao fazer isso podemos descrever o funcionamento exato de funções de interface, como o que cada parâmetro significa, o valor de retorno, algumas observações quanto ao uso, etc.

Aprender a usar Doxygen é muito fácil. Ele possui uma ajuda com vários exemplos com os quais podemos começar a programar um código auto-documentado.

Por ser uma ferramenta bem flexível, são permitidos inúmeros formatos para se auto-documentar o código. Vou descrever como eu faço, mas pode ser que outro formato lhe agrade mais. Para conhecê-los, dê uma olhada no manual.

A primeira coisa a saber sobre comentários de documentação é que eles devem vir sempre ANTES do elemento que estamos comentando. Por exemplo, uma classe:

    
    /** Nova classe de exemplo
    *
    * Essa classe é um exemplo de como utilizar o Doxygen
    */
    class ClasseDeExemplo
    {
       // ...
    };

Note que o comentário inicia com um duplo asterisco "/". Isso indica ao Doxygen que vem documentação por aí.

Observe que seria mais simples que o Doxygen pegasse todo e qualquer comentário e transformasse em documentação. No entanto, existem comentários que não devem ser publicados, pois são muito específicos do funcionamento interno da função. Dessa forma o programa-documentador lhe dá a liberdade de fazer comentários documentáveis e não-documentáveis.

Também existe um outro formato bem popular, usado pelo pessoal do Java, que são os comentários que se iniciam com três barras:

    
    ///
    /// Nova classe de exemplo
    ///
    /// Essa classe é um exemplo de como utilizar o Doxygen
    /// E esse comentário é equivalente ao anterior
    ///
    class ClasseDeExemplo
    {
       // ...
    };

Além desse estilo de comentário, existem campos-chave que podemos colocar. Para definir um campo-chave, uma forma válida é usar o arroba seguido do seu nome, e a descrição. Eis um exemplo cheio deles:

    
    /** @brief Função de exemplo
    *
    * Essa função tem por objetivo exemplificar o uso do Doxygen
    *
    * @param firstParam Serve como primeiro parâmetro da função
    * @param[out] anotherParam Esse é outro parâmetro que recebemos
    *
    * @return Se der erro, retorna -1. Se der tudo certo, 0.
    *
    * @remarks Essa função não pode ser chamada antes de ChamaEuPrimeiro.
    */
    int FuncaoDeExemplo(int firstParam, int anotherParam)
    {
       // ...
    }

Vejamos:

	
  * brief. Serve como descrição inicial e sucinta do que a função faz. Mais explicações podem existir depois dessa primeira linha introdutória.

	
  * param. Descreve o objetivo de um parâmetro, assim como se ele é de entrada ou saída.

	
  * return. Explica os diversos retornos que a função pode ter.

	
  * remark. Observações especiais que podem ajudar quem chama a função.

Existem diversos outros tipos de marcadores e com certeza você encontrará muita utilidade em outros. No entanto, esse é o basico que todo desenvolvedor do seu time deve saber para já começar a documentar suas funções.

	
  * Usando o Doxygen (Parte 1 e Parte 2) - Daniel Quadros

