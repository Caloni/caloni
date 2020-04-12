---
date: "{{ now.Format "2006-01-02" }}"
title: "{{ replace .TranslationBaseName "-" " " | title }}"
tags: [ "blog" ]
desc: "{{ replace .TranslationBaseName "-" " " | title }}"
---
