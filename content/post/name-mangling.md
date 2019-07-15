---
date: "2009-07-13"
title: Name mangling
categories: [ "code" ]
---
. Isso é o que chamamos [name mangling.

Em dois projetos usando Visual C++ 2008 e Borland C++ Builder 5 (última versão que funciona direito) eu fiz uma exportação da função soma em linguagem C (o fonte é um .c). Veja o resultado:

name-mangling-borland-c.png

name-mangling-vcpp-c.png

Já usando a linguagem C++ (o fonte é um .cpp) temos outro resultado totalmente diferente para nossas duas funções soma descritas no artigo anterior:

name-mangling-borland-cpp.png

name-mangling-vcpp-cpp.png

. Se apenas entender que você não conseguirá juntar classes VC++ e Builder usando **[dllexport** para tudo quanto é lado, então terminamos por aqui.
