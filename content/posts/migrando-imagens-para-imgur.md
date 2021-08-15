---
categories:
- blog
date: 2017-07-28 18:28:07-03:00
tags:
title: Migrando Imagens Para Imgur
---

Depois de migrar meus blogues para o [Hugo](https://gohugo.io) decidi deixar o repositório mais magro migrando as imagens para um serviço de imagens. O [imgur](http://imgur.com/) me pareceu uma solução simples com uma interface rápida (e uma API Python). Para realizar essa tarefa você vai precisar das ferramentas de sempre: grep, sed, python, vim. E lá vamos nós.

Meu primeiro passo foi realmente limpar a pasta de imagens, eliminando as que não estavam sendo usadas. A pasta de imagens ficou se acumulando por anos, e muitas imagens foram sendo carregadas através dos Wordpress da vida e plugins que deram resize nas imagens, gerando várias cópias no processo. Tudo inútil e dispendioso.

```
dir /b imagens\*.* > images.bat
rem transformar cada linha de images.bat em:
rem grep -c imagem.png all.md
images.bat > result.log
rem a partir do vim juntar o resultado das linhas e apagar os resultados não-zerados
rem imagem-found.png
rem 1
rem imagem-not-found.png
rem 0
v/^[0-9]/j
v/0$/d
rem pronto; agora é só rodar o result.log como bat
```

O principal problema de subir tudo para o imgur é que os nomes dos arquivos irão mudar e perder a referências usadas no texto. Para conseguir renomear os arquivos dentro dos artigos é necessário conectar no serviço do imgur e através dele obter o nome original do arquivo, disponível na propriedade __name__:

```
import auth

client = auth.authenticate()
f = open('images.txt')
imgs = f.readlines()
for img in imgs:
    img = img.strip('\n')
    imgur = client.get_image(img)
    origname = imgur.link[imgur.link.find(img):].replace(img, imgur.name)
    print origname, '=>', img

```

Executando este script será possível gerar um log no formato __<nome-original-do-arquivo> => <id-da-imagem-usado-pelo-imgur>__. O ID deles também é usado para link direto da imagem, de onde virá o comando sed que vai substituir nos artigos os nomes originais pelo link do imgur:

```
sed -i "s/<nome-original-do-arquivo>/http\/\/:\/<link-da-imagem-no-imgur>/<id-do-imgur>.<extensao>/" *.md
```

Lembrar de apagar o all.md. Ele só foi usado para gerar a saída mais simples do grep.
