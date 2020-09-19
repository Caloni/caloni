---
date: "2016-09-18"
tags: [ "code", "draft", "tools" ]
title: "Usando GVim com Projetos do Visual Studio"
---
A vida dos programadores C/C++ Windows, e que geralmente precisam do Visual Studio, está um abandono total. A configuração de make dos projetos sempre foi baseada no uso de makefiles, assim como no Unix, e por isso mesmo o uso da ferramenta nmake do SDK do Windows era a maneira padrão de se compilar e ver o resultado de dentro do Vim para projetos Windows. Com o advento do .NET, do Visual Studio 2003 e dos XMLs disfarçados como arquivos de projeto e solution o uso do makefile foi paulatinamente abandonado, gerando diferentes versões de ferramentas, todas incompatíveis, para conseguir compilar um ou mais cpps e conseguir ver o resultado.

Por isso mesmo é um assunto pouco explorado nos fóruns do Stack Overflow como configurar decentemente o comando :make do Vim para conseguir realizar o ciclo "program, compile, debug" que já era feito desde a época do Amiga OS (e conhecido no manual do Vim como Quickfix). Ninguém se dá ao trabalho de usar esse modelo torto.

Houve um tempo que eu mesmo pesquisei algumas soluções, e caí no velho problema de tentar conviver com diferentes versões do Visual Studio. Deixei de lado o Vim por uns anos, e passei a usar o VsVim, um plugin que roda em várias versões do Visual Studio e utiliza o vimrc de sua instalação.

Hoje voltei a fuçar esse problema e depois de algumas horas tentando entender qual a dinâmica que deve ser seguida, cheguei a dois usos legítimos do make no Visual Studio: o modo legado, através do devenv, e o modo comportado, que usa a ferramenta MsBuild para encontrar o projeto e a solution que devem ser compilados.

A não ser que você coloque o path das ferramentas direto nos comandos (algo que não recomendo pois as coisas no Vim começam a ficar estranhas com paths com espaços, algo abundante no Windows) é preferível que você escolha qual devenv e qual msbuild deseja utilizar e definir isso na variável de sistema path. No meu exemplo estou usando o msbuild para qualquer Visual Studio acima do 2010 (como o 2015), pois já está padronizado, e como tenho projetos no VS2003 para manter, escolhi deixar o devenv.com com ele.

_Note que essa configuração, para ficar persistente, precisa ser definida através do Painel de Controle ou Propriedades do Sistema. Google for it._

Depois de configurado, qualquer projeto deve ser compilável em 2003 pela linha de comando (através do devenv.com). E mesma forma, projetos 2010+ devem usar o msbuild. Tirando essa facilidade, as coisas no Vim para msbuild rodam particularmente bem. Basta alterarmos o makeprg da seguinte maneira: ":set makeprg=msbuild\ /nologo\ /v:q\ /property:GenerateFullPaths=true<CR>".

As opções específicas são para gerar o path completo, as barras invertidas são por causa dessa mania do Vim de dar pau quando tem espaço em tudo.

A partir dessa configuração já é possível compilar um projeto estando em sua pasta. Para o Visual Studio 2003 (ou qualquer um usando o devenv.com) é necessário mudar esse comando para o uso do devenv: ":set makeprg=devenv\ %\ /build\ Debug<CR>".

Sim, temos que escolher uma configuração (o msbuild já escolhe por você). E note que ele usa o arquivo atual (%) para compilar. Isso quer dizer que isso irá exigir do usuário de Vim abrir o sln ou o vcproj e executar o :make a partir daí. De qualquer forma, ele funciona também.

Note que em nenhum dos casos erros conseguirão ser capturados para irmos direto no ponto do código-fonte onde ele está. Para isso funcionar, em nosso último passo, é necessário configurar o errorformat para que ele tenha um padrão que funcione com ambas as ferramentas. Depois de testar um pouco, cheguei nesse formato: "set errorformat=%f(%l)%m". Talvez isso mude no futuro, pois sabe como é a Microsoft com suporte a linha de comando. Este formato pega também os warnings, mas fazer o quê. Você não quer conviver com warnings em seu código pelo resto da vida, né? =)

E para navegar na lista é como o resultado de comandos como :vimgrep. :cnext e :cprevious vão para frente e para trás na lista, sempre pulando para o ponto no código onde está o erro.

Como deu pra perceber, para conseguir usar o msbuild e o devenv ao mesmo tempo você seria obrigado a trocar o makeprg sempre que precisasse. Para facilitar seu uso, nada como fazer um mapeamento de atalhos com o uso do comando map do vim.
