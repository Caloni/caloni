---
categories: [ "code" ]
date: "2014-02-27"
tags: [ "draft", "projects" ]
title: "Houaiss para Babylon em Python!"
---
O Fabio Montefuscolo expandiu mais ainda o acesso do conversor Houaiss para Babylon implementando uma versão em Python, uma linguagem que estou aprendendo a adorar. Tudo é mais simples, rápido e direto em Python, e o código que ele escreveu utiliza todo esse potencial:

    #!/usr/bin/python2
    # -*- coding: utf-8 -*-
    
    #
    # Coloque esse script na pasta com os arquivos dhx.
    # O resultado estarÃ¡ em iso-8859-1
    #
    
    #
    # Segui o tutorial em /conversor-de-houaiss-para-babylon-parte-1
    #
    
    import os
    
    files = os.listdir('.')
    
    for arq in files:
        if not arq.endswith('dhx'):
            continue
    
        print 'Abrindo "%s"' % arq
        origin = open(arq, 'r')
        target = open('%s.txt' % arq, 'w+')
    
        char = origin.read(1)
        while char:
            byte = ord(char) + 0x0B
            new_char = chr(byte % 256)
            target.write(new_char)
            char = origin.read(1)
    
        origin.close()
        target.close()
    

