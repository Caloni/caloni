---
date: "2017-03-23"
title: "Forma simples de baixar atualizações remotamente de um cliente para um servidor"
categories: [ "code" ]

---
A forma mais simples e independente de código para efetuar essa tarefa para Windows é no servidor subir um file server em qualquer porta disponível, e a forma de file server mais simples que existe é o embutido em qualquer instalação Python:

```cmd
python -m SimpleHTTPServer
```

Para que não seja necessário instalar o Python no servidor é possível transformar essa chamada em um executável e suas dependências standalone:

```py
import SimpleHTTPServer
import SocketServer

PORT = 8000

Handler = SimpleHTTPServer.SimpleHTTPRequestHandler

httpd = SocketServer.TCPServer(("", PORT), Handler)

print "serving at port", PORT
httpd.serve_forever()
```

Esse script pode ser compilado pela ferramenta py2exe, instalável pelo próprio Python. É necessário criar um arquivo setup.py na mesma pasta do script e através desse script gerar uma pasta dist com o script "compilado" e pronto para ser executado.

```py
from distutils.core import setup
import py2exe

setup(console=['fileserver.py'])
```

Pelo prompt de comando executar o seguinte comando que irá gerar a pasta dist:

```cmd
python setup.py py2exe
```

Uma vez gerada a pasta, renomear para fileserver e copiar no servidor em qualquer lugar (ex: pasta-raiz). Executar de qualquer pasta que se deseja tornar acessível via browser ou qualquer cliente http:

```cmd
cd c:\tools
c:\fileserver\fileserver.exe
```

Para testar basta acessar o endereço via browser:

![](http://i.imgur.com/hSnmzqv.png)

### Lado cliente

Do lado cliente há ferramentas GNU como curl e wget para conseguir baixar rapidamente qualquer arquivo via HTTP. Para máquinas com Power Shell disponível há um comando que pode ser usado:

```cmd
powershell wget http://127.0.0.1:8000/Procmon.exe -OutFile Procmon.exe
```

Porém, caso não seja possível usar o Power Shell o [pacote básico do wget do GnuWin32](http://gnuwin32.sourceforge.net/packages/wget.htm), de 2MB, já consegue realizar o download.

```
c:\Temp\bitforge\wget>dir
 Volume in drive C is SYSTEM
 Volume Serial Number is 5C08-36EE

 Directory of c:\Temp\bitforge\wget

23/03/2017  13:25    <DIR>          .
23/03/2017  13:25    <DIR>          ..
03/09/2008  17:49         1.177.600 libeay32.dll
14/03/2008  19:21         1.008.128 libiconv2.dll
06/05/2005  16:52           103.424 libintl3.dll
03/09/2008  17:49           232.960 libssl32.dll
31/12/2008  11:03           449.024 wget.exe

c:\Temp\bitforge\wget>wget http://127.0.0.1:8000/Procmon.exe
SYSTEM_WGETRC = c:/progra~1/wget/etc/wgetrc
syswgetrc = c:/progra~1/wget/etc/wgetrc
--2017-03-23 13:44:13--  http://127.0.0.1:8000/Procmon.exe
Connecting to 127.0.0.1:8000... connected.
HTTP request sent, awaiting response... 200 OK
Length: 2046608 (2,0M) [application/x-msdownload]
Saving to: `Procmon.exe'

100%[===================================================================================================================================>] 2.046.608   --.-K/s   in 0,006s

2017-03-23 13:44:13 (348 MB/s) - `Procmon.exe' saved [2046608/2046608]

c:\Temp\bitforge\wget>
```

E assim com poucas linhas de código já é possível iniciar um client/servidor via http que fornece arquivos de atualização. A própria versão do pacote e detalhes podem estar disponíveis na mesma pasta.

