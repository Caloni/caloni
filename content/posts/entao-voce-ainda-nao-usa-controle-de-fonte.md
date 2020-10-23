---
date: "2010-11-02"
tags: [ "code", "draft" ]
title: "Então você ainda não usa controle de fonte?"
---

Não há nada de errado nisso. Projetos robustos com uma equipe moderada ¿ 5 a 10 programadores ¿ precisam desse tipo de organização, e tornam a resolução dos problemas do dia-a-dia mais problemática sem esse controle. A questão reside para o programador solitário ou a equipe minúscula ¿ 2 a 4 programadores. Esses geralmente questionam o custo-benefício de terem o trabalho de configurar e manter mais um sistema. Além disso, isso implica em uma mudança de grandes proporções em cada membro da equipe: uma mudança cultural.

Portanto, a primeira decisão que deve ser tomada pelo programador que quer mudar as coisas é instalar um controle de fonte moderno para seus projetos caseiros. Quando digo moderno, digo distribuído.Distribuído porque 1) é possível começar desde já com três comandos simples, 2) quando alguém copia a pasta do projeto está levando todo o histórico junto e 3) pastas duplicadas são branches distintos que podem interagir no futuro.

Os três comandos simples não são nada do outro mundo: criar o repositório, adicionar arquivos e fazer commit.

Dica: Um commit é uma maneira de dizer ao controle de fonte: "já modifiquei o que tinha pra modificar, então mande tudo que tenho de novo para o controle". 

Tanto faz qual controle você pretende usar. No meu exemplo usarei o Bazaar, que é a ferramenta que uso no dia-a-dia com minha pequena equipe e serve bem para programadores solitários também. Basicamente para ter o Bazzar instalado basta baixá-lo, next next e finish.

Marcar para usar o PATH pode ser uma boa pra quem é fã de linha de comando.

Apesar de existirem firulas gráficas, gosto de usar o Bazaar na linha de comando porque faz você pensar direito antes de fazer commits, mas esteja livre para experimentar a maneira que achar melhor.

Isso vale para qualquer projeto que você esteja trabalhando. Pela linha de comando, navegue até o diretório do projeto. Digite os comandos abaixo seguidos de enter:

	
  1. bzr init

	
  2. bzr add

	
  3. bzr commit -m "Primeiro commit no controle de fonte"

Pronto! Você está oficialmente com seu projeto dentro de um controle de fonte.


Os passos seguintes seguem o mesmo padrão, exceto o passo 1, que é substituído pelo seu trabalho:

	
  1. trabalho

	
  2. bzr add

	
  3. bzr commit -m "Comentário sobre modificação que fiz"


Basicamente, sim. É claro que um controle de fonte não se baseia apenas em commits. Existem arquivos a serem ignorados (os obj da vida) e eventualmente algum trabalho paralelo ou com mais programadores. No futuro poderá comparar versões diferentes do código. Porém, apenas seguindo essa simples receita acima você já pode se gabar de ter um controle de fontes confiável em seus projetos. Já estará se aproveitando desse controle no futuro, quando aprender mais sobre ele.
