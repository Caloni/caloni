---
date: 2019-07-10T00:08:25-03:00
title: "Como Publicar Seu Blog Em Hugo Para Ebook"
categories: [ "code" ]
desc: "Dicas de como publicar o conteúdo que você escreve em um formato simples de guardar."
---
Eu publico meu blog inteiro de tempos em tempos para um ebook que construo formatando primeiro em html através de um tema do [Hugo](https://gohugo.io/), o parser de blog que estou usando no momento porque ele suporta 2500 posts sem reclamar. É uma receita simples de sucesso se você precisar ter todo seu conteúdo indexado para rápida referência ou leitura cronológica.

A primeira coisa a ser feita é preparar um tema para formatar seu html. Eu já tenho um [linkado no meu blogue](https://github.com/Caloni/book/tree/f1663ad104f51459fe7d17e9ce1e0305901330b4) e que precisa apenas formatar o index.html, pois todo o conteúdo e índices estarão lá. Segue um exemplo atual que uso. Ele possui índice alfabético, inclusão de um arquivo-diário que mantenho, listagem das categorias (com índices para cada uma delas) e listagem cronológica (e link para pular direto para o conteúdo).

```html
<!DOCTYPE html>
  <head>
    <title>Blogue do Caloni</title>
    <meta http-equiv="content-type" content="text/html; charset=utf8">
  </head>
  <body style="min-height:100vh;display:flex;flex-direction:column">
    <section class="section" style="flex:1">
      <div class="container">
        <div class="columns">
          <div class="column">
            <h2 id="begin" style="page-break-before: always;">Índices</h2>
            <ul>
              <li><a href="#daytoday">DayToDay</a></li>
              <li><a href="#idx">Alfabético</a></li>
              <ul>
                <li>{{ $letters := split "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "" }}
                  {{ range $letters }}
                    <a href="#letter{{ . }}">{{ . }}</a>
                  {{ end }}
                </li>
              </ul>
              <li><a href="#cat">Categorias</a></li>
              <ul>
                {{ range $key, $value := .Site.Taxonomies.categories }}
	               <li><a href="#{{ $key }}">{{ $key | humanize }}({{ len $value }})</a></li>
                {{ end }}
              </ul>
              <li><a href="#posts">Data (ir para Conteúdo)</a></li>
              <ul>
                {{ range .Site.RegularPages }}
                    <li><a href="#{{ .UniqueID }}">{{ .Title }} </a></li>
                {{ end }}
              </ul>
            </ul>
            <h2 id="daytoday" style="page-break-before: always;">DayToDay</h2>
            <pre> {{readFile "..\\caloni.txt"}} </pre>
            <h2 id="idx" style="page-break-before: always;">Índice Alfabético</h2>
            <ul>
            <!-- create a list with all uppercase letters -->
            {{ $letters := split "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "" }}
            <!-- range all pages sorted by their title -->
            {{ range .Data.Pages.ByTitle }}
              <!-- get the first character of each title. Assumes that the title is never empty! -->
              {{ $firstChar := substr .Title 0 1 | upper }}
              <!-- in case $firstChar is a letter -->
              {{ if $firstChar | in $letters }}
                <!-- get the current letter -->
                {{ $curLetter := $.Scratch.Get "curLetter" }}
                <!-- if $curLetter isn't set or the letter has changed -->
                {{ if ne $firstChar $curLetter }}
                  <!-- update the current letter and print it -->
                  {{ $.Scratch.Set "curLetter" $firstChar }}
                  <h3 id="letter{{ $firstChar }}">{{ $firstChar }}</h3>
                {{ end }}
                <li><a href="#{{ .UniqueID }}">{{ .Title }}</a></li>
              {{ end }}
            {{ end }}
            </ul>
            <h2 id="cat" style="page-break-before: always;">Índice por Categoria</h2>
            <ul>
            {{ range $taxonomyname, $taxonomy := .Site.Taxonomies }}
              {{ if eq "categories" $taxonomyname }}
                {{ range $key, $value := $taxonomy }}
                  <h3 id="{{ $key }}">{{ $key | humanize }}</h3>
                    <ul>
                      {{ range $value.Pages }}
                        <li><a href="#{{ .UniqueID }}">{{ .Title }} </a></li>
                      {{ end }}
                    </ul>
                {{ end }}
              {{ end }}
            {{ end }}
            </ul>
            <h2 id="posts" style="page-break-before: always;">Conteúdo</h2>
            {{ range .Site.RegularPages }}
              <h3 style="page-break-before: always" id="{{ .UniqueID }}">{{ .Title }}</h3> {{ dateFormat "2006-01-02" .Date }} {{ .Content }}
              {{ partial "taglist.html" . }}
            {{ end }}
            </div>
            <br>
          </div>
        </div>
      </div>
    </section>
  </body>
</html>
```

Como eu uso Kindle eu construo a partir desse html um arquivo .mobi, mas creio ser simples de construir qualquer outro formato através desse html final. No caso do Kindle preciso de alguns arquivos para usar o [kindlegen](https://www.amazon.com/gp/feature.html?ie=UTF8&docId=1000765211) (a ferramenta da Amazon) que mantenho na pasta `static` do hugo, como o `.ncx` e o `.opf` (além da capa, `cover.jpg`). Uso uma batch muito pequena para fazer todos os passos e copiar o `.mobi` resultante para meu Kindle (conectado por um cabo USB e com um drive montado em K:).

```bat
rem @echo off
hugo -D --theme book --destination book
pushd book
rem iconv -f UTF-8 -t LATIN1 index.html > book.html
cp index.html book.html
kindlegen.exe book.opf -o caloni.mobi
if exist k:\ copy /y caloni.mobi k:\documents
popd
```

Importante lembrar que a codificação do hugo (utf8) deve bater com a codificação esperada pelo gerador de ebook. Que me lembre não há muito mais segredos. Basta escrever e de vez em quando rodar o script novamente =)
