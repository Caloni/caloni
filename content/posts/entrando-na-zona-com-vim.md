---
date: "2017-01-05"
title: "Entrando na zona com Vim"
categories: [ "draft", "blog" ]

---
Se você é programador é bem provável que já tenha ouvido falar em [Flow] [1] ou [The Zone] [2]. Se for leitor assíduo do Hacker News, então, nem se fala. De qualquer forma, uma das maneira mais produtivas do programador programar é entrar na famosa "zona". É lá que muito de nós nascemos. Lembra a primeira vez que mexeu em um computador ou afim e ficou tão obcecado que não viu o tempo passar? Pois bem. Você esteve na zona. E estar nela é um bom lugar para trabalhar.

Na zona, principalmente resolvendo problemas complexos, o importante é poder construir uma estrutura em sua mente com a ajuda de alguns aparatos, como um caderno de anotações, stickers, lousa ou seu editor preferido. Meu editor preferido para navegar (flow) por um código é sem sombra de dúvida o Vim, pois ele é apenas uma tela que preenche todo meu campo de visão e possui comandos em que eu consigo facilmente acessar o conteúdo que preciso relembrar. Quando estou obtendo o diagnóstico de um log, por exemplo, posso rapidamente ir construindo um modelo mental da solução navegando entre arquivos de log e código-fonte através de tags e buscas em regex.

A primeira vantagem do Vim em relação a outros editores é sua capacidade de abrir arquivos grandes. Um log de 1GB pode ser um desafio para um Notepad da vida, e até para um Visual Studio, mas no Vim tudo que você precisa é de memória disponível. E mesmo que não tenha, o Windows se vira bem no gerenciamento de swap (ou Linux, tanto faz).

Para navegar no código, existem duas técnicas que não necessitam de nenhum plugin. A primeira é a busca por regex, que pode ser feita com os comandos [:vimgrep](http://vimdoc.sourceforge.net/htmldoc/quickfix.html#:vimgrep) ou [:grep](http://vimdoc.sourceforge.net/htmldoc/quickfix.html#:grep), sendo que o primeiro busca em um padrão de arquivos (usando wildcard) e o segundo dentro dos buffers já abertos (útil se você já tiver uma sessão ativa; mais sobre isso depois).

```vim
" No Vim não é necessário digitar o comando completo; note que esse wildcard busca pastas recursivamente
:vimg /regex/ \Projects\SomeProject\**\*.cpp

" Isso busca em todos os buffers abertos cujo arquivo tem a extensão de C++
:grep regex *.cpp
```

O bom é que, no caso de logs, se você buscar por expressões unívocas, isso já fica no histórico de seus comandos e você pode usar quando quiser para voltar para esses logs (ou se você for maluco e guardar de cabeça seus marks, pode criar um mark de vez).

A segunda técnica de navegar no código é através das tags que são montadas pela ferramenta ctags. Ela é genérica o suficiente para suportar várias linguagens, mas pode ser usada até para qualquer sequência de palavras. Há plugins que realizam essa varredura do fonte automática, mas particularmente não gosto de encher meu Vim de plugins, sendo que o único que uso que me lembro é o [MRU](http://www.vim.org/scripts/script.php?script_id=521) (porque o Vim ainda não suporta algo do gênero internamente). De qualquer forma, tudo que eu preciso fazer para atualizar as tags de um projeto é abrir o readme do projeto (que geralmente fica na pasta raiz) e rodar meu atalho.

```vim
" Roda recursivamente e otimiza para C++ e Python.
map <S-F5> :!ctags --tag-relative=yes --recurse --c++-kinds=+p --python-kinds=-i --fields=+iaS --extra=+q<CR>
" Busca pelo arquivo tags na pasta atual e vai subindo a hierarquia.
set tags=tags;
```

Isso vai gerar um arquivo ctags na pasta do projeto que será usada automaticamente para procurar pelas tags que eu preciso. O pulo do gato na verdade é o ponto-e-vírgula após o nome do arquivo ao setar a variável tags. Isso faz com que o Vim não busque apenas o arquivo tags na pasta atual, mas em toda hierarquia. Então se você estiver na pasta Projects\SomeProject\Folder1\Folder2\Folder3\File.cpp e tiver gerado o arquivo tags na pasta SomeProject para todo o projeto, ao usar o comando de busca de tag ele eventualmente vai abrir esse arquivo tags, pois ele vai procurando em Folder3, Folder2, Folder1 e cai em SomeProject.

Como no Windows o atalho padrão do comando tag do Vim não funciona também preciso fazer uma pequena adaptação técnica (e de quebra já uso para navegar nos próximos resultados):

```vim
map <C-K> <C-]>
" O bom é que o first e o next ficam um do lado do outro.
map <C-J> :tnext<CR>
```

Depois de dar uma olhada no log, encontrar os métodos que você precisa analisar, seu fluxo, etc, você terá um monte de buffers relevantes abertos nas linhas relevantes. Seria muito bom se tudo isso pudesse ser guardado em um estado para que você continue amanhã ou em sua próxima sessão de flow. Para isso existe o comando [:mksession](http://vimdoc.sourceforge.net/htmldoc/starting.html#:mksession).

```vim
" Salva estado atual dos buffers
:mksession \temp\analise.vim
" Restaura um estado salvo anteriomente
:so \temp\analise.vim
```

O comando [:source](http://vimdoc.sourceforge.net/htmldoc/repeat.html#:source) roda um script vim que possui comandos guardados. Ele é um arquivo texto semelhante ao vimrc.

Basicamente é isso. Tudo o que você precisa em sua análise de fonte e de log se encontra na ponta de seus dedos. Não é necessário abrir nenhuma pasta nem terminal. Simplesmente navegue através do Vim para descobrir o problema e seja feliz em sua zona.

[1]: https://en.wikipedia.org/wiki/Flow_(psychology)
[2]: https://hn.algolia.com/?query=the%20zone
