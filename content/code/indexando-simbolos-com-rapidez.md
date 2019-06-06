---
date: "2015-10-28"
title: "Indexando símbolos com rapidez"
categories: [ "code" ]
---
Trabalhar com inúmeros projetos de diferentes clientes e diferentes binários pode ser uma loucura. Quando o mundo é Windows, algumas medidas precisam ser padronizadas para evitar a perda de informação durante todo o processo de desenvolvimento, testes, deploy e manutenção.

A respeito do deploy e manutenção, um dos principais é manter o código sempre atualizado, limpo e asseado, além de estar dentro de pelo menos um controle de fonte, de preferência distribuído ([Mercurial](http://caloni.com.br/guia-basico-de-controle-de-codigo-mercurial), [Git](http://caloni.com.br/depurando-ate-o-fim-do-mundo-e-de-volta-de-novo-source-server-com-github), [Bazaar](http://caloni.com.br/guia-basico-de-repositorios-no-bazaar)).

Porém, voltando ao mundo Windows, os fontes não são apenas a única fonte de preocupação e zelo. Os binários também são importante. Binários eu digo os EXEs, DLLs geradas, além dos seus símbolos (PDBs), que contém o mapa entre aquele monte de 1s e 0s e o código-fonte de onde ele saiu.

Nós da [BitForge](http://www.bitforge.com.br) costumamos pelo menos indexar binários com fonte, através dos resources do binário. Como isso é feito? Basicamente editando o arquivo RC na parte da versão do binário e inserindo o hash do commit usado para gerar aquele binário. Com isso qualquer binário produzido possui seu pai ("use the source, Luke!"). Usamos um script em Python muito simples e muito eficaz para isso, que indexa .NET e C++ (através do Visual Studio, mas não está com muitas amarras de ambiente):

```python
rc_new_content = re.sub(u'^.*ProductVersion.*$', product_version_string, rc_original_content, flags=re.MULTILINE)
rc_new_content = re.sub(u'^.*FILEVERSION.*$', file_version_string, rc_new_content, flags=re.MULTILINE)
```

Quando algum binário parar na máquina de algum cliente em algum lugar do universo, basta olhar para os detalhes pelo Windows Explorer, e ele estará lá:

![](http://i.imgur.com/mogZt3n.png)

Através desse a2f3c... podemos capturar o commit exato de onde saiu o binário. Tudo, é claro, confiando no procedimento de toda a equipe: apenas gerar um binário a partir de um commit publicado.

Você também pode exibir a versão dos binários em uma pasta através das colunas do Windows Explorer:

![](http://i.imgur.com/vfY2oan.png)

### Indexando símbolos e binários

Outro detalhe de binários é que eles vivem sendo sobrescritos. Todo "Project, Build" sobrescreve o binário anterior, que pode ter sido justamente o enviado para o cliente. Se o cliente não possuir nenhum procedimento de armazenamento de versões dos binários gerados (às vezes ele nem precisa, essa é nossa função) não há como obter os símbolos de binários que podem gerar problemas futuros (todo _software_ tem bug).

Para resolver isso, o mínimo que se deve fazer é super-simples e nada difícil: crie uma pasta em algum lugar, nomeie essa pasta seu servidor de símbolos, a cada novo binário que será entregue, indexe o binário e os seus símbolos. Como? Com o ["Debugging Tools for Windows"](https://msdn.microsoft.com/en-us/library/windows/hardware/ff551063(v=vs.85).aspx), como dizia um amigo meu, é mamão com açúcar:

```
"c:\Tools\DbgTools(x86)\symstore" add /r /f <MINHA-PASTA-COM-BINÁRIOS> /s c:\Tools\Symbols /t "IndexSymbols"
```

Essa e outra técnicas de indexar fontes e binário você pode ver no meu [projeto](https://github.com/Caloni/GitIndex), [artigo](http://caloni.com.br/depurando-ate-o-fim-do-mundo-e-de-volta-de-novo-source-server-com-github), [palestra](http://caloni.com.br/ccppbr-rio-12/) e [vídeo de demonstração](https://www.youtube.com/watch?v=mZewxqlFShA). Se você for cego, ainda tem a vantagem da áudio-narração do vídeo. Brincadeira, ainda não temos isso.

### Simplificando

Com o poder do Windows Explorer, desde o Windows 95 podemos otimizar nossas tarefas nos baseando na extensão dos arquivos que estamos lidando. No caso do indexador de símbolos, eu simplesmente utilizo uma batch que contém exatamente a linha acima (com a diferença de %1 no lugar de <MINHA-PASTA-COM-BINÁRIOS>) que eu chamo direto do Explorer através de um comando que inseri no registro. Eis o comando:

```
Windows Registry Editor Version 5.00

[HKEY_CLASSES_ROOT\dllfile\shell\Index Symbols]

[HKEY_CLASSES_ROOT\dllfile\shell\Index Symbols\command]
@="cmd.exe /c c:\\tools\\indexsymbols.bat  \"%1\""
```

Você pode baixar um arquivo reg [aqui](/download/index-symbols.reg), copiar as linhas acima em um .reg que você gerar, ou simplesmente seguir o passo-a-passo dessas linhas e gerar seu próprio registro. Após feito isso, surgirá um novo comando para qualquer DLL que você clicar com o outro botão do mouse:

![](http://i.imgur.com/tvCCYcm.png)

Você também pode gerar o mesmo comando para EXEs, bastando realizar o mesmo passo-a-passo na pasta **exefile** em vez de **dllfile**.

Procedimentos como esse devem ser uma coisa simples, não difícil. Programadores e pessoas são preguiçosas, e precisam de algum incentivo. E nesse caso, o incentivo é: o que você vai fazer quando der um crash com um binário que você não sabe de onde veio nem qual fonte foi usado para compilá-lo? Pois é.
