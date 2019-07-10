---
date: "2011-06-04"
title: Cronogramas baseados em fatos reais
categories: [ "blog" ]
---
[Já falei sobre cronogramas](http://www.caloni.com.br/cronograma) por aqui e tudo que disse ainda se aplica. Contudo, comentei brevemente sobre entender seu próprio ritmo, que, instintivamente, sabia ser verdade. Depois que [li um pouco mais sobre técnicas XP/Scrum](http://www.infoq.com/br/minibooks/scrum-xp-from-the-trenches) (que nada mais são do que formalizações do que os programadores Agile perceberam no decorrer dos seus projetos) achei uma fórmula simples para transformar o tempo estimado em tempo realista.

Vejamos o texto original (auto-plágio):

<blockquote>Regra # 5: não inclua o ócio no cronograma

Seja honesto consigo mesmo e com seu chefe: você realmente trabalha 8 horas por dia? É lógico que não! E não é nenhuma vergonha admitir isso. Todos nós temos emails para ler e responder, reuniões para presenciar e bloques importantes para acompanhar. Portanto, ignore essa conversa fiada de 8 horas e admita: não se deve contar os dias como se eles tivessem 8 horas.

Qual o valor de um dia, então? Cada um sabe o valor que deve ser decrementado desse valor simbólico de 8 horas, mas esse valor sempre será menor. Não se iluda!

</blockquote>

Exatamente. Não se iluda! Isso tem seu reflexo na metodologia Agile. Basicamente quer dizer que você precisa aplicar índices que reflitam a realidade do seu próprio ritmo. Além disso:

<blockquote>Regra # 4: uma tarefa estimada é uma tarefa completada

É muito simples ilustrar e entender esse conceito com código. Voltando ao caso da função, digamos que você consiga terminar a bendita função em exata uma hora. Você é bom, hein?

Porém, essa função ainda 1) não foi comentada,  2) não foi testada e  3) não foi testada em release.

Logo, essa é uma tarefa em que você termina o mais importante em uma hora... mas não termina tudo. Deve-se sempre considerar a tarefa por completo, pois no final de quinze tarefas vai faltar comentar e testar tudo isso, o que aumentará consideravelmente a imprevisiblidade no seu cronograma.</blockquote>

O que, novamente traduzindo, é mais um indicador a ser aplicado sobre seus números.

E o que são seus números?

Basicamente, o que a própria metodologia ensina: meça o esforço necessário para fazer código (mas é pra isso mesmo que somos contratados, não?) como se pudéssemos programar por todo esse tempo sem parar por um momento sequer (mesmo que sejam dezenas de horas). Lógico, aprenda a dividir o esforço em pequenos passos, mas estime o tempo considerando APENAS o esforço de fazer o código.

Pronto? Agora é hora de aplicar os indicadores.

### 1. Foco

Mais uma vez, admita: programadores raramente conseguem manter o foco por muito tempo. São pessoas ao redor te desviando a atenção, o tweet que salta de uma janela ou até mesmo as necessidades orgânicas que todo ser humano tem. São elementos, enfim, que, em conjunto, nunca te possibilitarão ter 100% do foco durante todo o trabalho.

Portanto, criemos um indicador: foco. Ele é um valor entre 0 e 1 e estima a porcentagem de foco que você consegue obter, em média, durante o dia. Por exemplo: eu consigo me focar 70% do dia inteiro em apenas codificar e o resto é perdido em reuniões e e-mails. OK. Esse número é, então, 0,7. Aplique sobre seu total de horas e terá o tempo real para codificar a tarefa:

Levarei 35 horas para codificar todo o processo de autenticação por reconhecimento de face, trabalhando sem parar.

    
    35 / 0.7 = 50

No entanto, como consigo apenas 70% de foco em média, sei que essa tarefa irá levar 50 horas na verdade.

### 2. Finalização

Já temos o tempo para o código ficar pronto, mas... é apenas código. Temos que reescalonar o tempo do projeto inserindo testes, retrabalho, comentários e documentação. Tudo ainda nas mãos do programador, que está ainda "aquecido" e que pode resolver retrabalhos em questões de segundos, se ninguém mais passar nada pra ele.

Mesmo assim,é um indicador importante. Sem ele, a qualidade do serviço final fica muito restrita e sensível a testes de caixa preta, gerando a revolta da equipe de testes.

Vamos supor, então, que, historicamente, essa fase tem sido, digamos, 20% do período de codificação (um chute bem otimista). Agora é fácil dizer o tempo final:

Levarei 50 horas para codificar tudo considerando o quesito foco.

    
    50 * 1,2 = 60

Porém, para poder entregar, preciso dedicar cerca de 20% aos testes, retrabalho e uma documentação mínima. Nesse caso, 60 horas é o prazo de entrega.

<blockquote>_Note que, se quiser, pode fazer a análise contrária também, tanto de um quanto de outro. Assim, se geralmente você gasta 20% a mais na codificação do que estima, então use o fator foco como 1.2 e multiplique em vez de dividir. Da mesma forma, se codificar é 60% de todo o trabalho, o fator finalização é 0.6 e deve-se dividir as horas pós-indicador de foco._</blockquote>

### Conclusão

O número de horas ficou muito maior que o esperado? Não me admira que os projetos geralmente atrasem, então. Por pior que pareça o cálculo final, ele foi construído com base na realidade. E não há nada melhor do que nos basearmos na realidade para estimar seriamente o quanto pode custar à empresa um projeto qualquer.
