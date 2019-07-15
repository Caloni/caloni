---
date: {{ .Date }}
title: "{{ replace .TranslationBaseName "-" " " | title }}"
categories: [ "cinemaqui" ]
imdb: "0000000"
draft: "true"
---

<hr>
"{{ replace .TranslationBaseName "-" " " | title }}" (País, Ano), escrito por <roteirista>, dirigido por <diretor>, com <atores>.
<h2>Trailer - {{ replace .TranslationBaseName "-" " " | title }}</h2>
