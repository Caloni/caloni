---
date: 2018-07-14T14:11:43-03:00
title: "Python27, protobuf, py2exe e build_exe"
categories: [ "code" ]
---
Para quem está tentando compilar um executável usando py2exe e protobuf, #ficadica: desista. Ele não vai funcionar ou se funcionar vai dar trabalho. Em vez disso melhor usar build_exe (através do pacote cx_freeze), que é um esquema marotinho que permite configurar tudo e há apenas um patchzinho que precisa ser feito.

Para entender como as coisas dão errado primeiro vamos instalar os requisitos de um pacote fictício em um ambiente virtualizado do Python (para evitar mexer na instalação padrão):

```
D:\>cd deploy

D:\deploy>virtualenv python27
New python executable in D:\deploy\python27\Scripts\python.exe
Installing setuptools, pip, wheel...done.

D:\deploy>
```

Depois instalamos os requisitos de nosso pacote fictício:

```
D:\deploy>python27\Scripts\activate.bat

(python27) D:\deploy>pushd d:\src\MyFictionalPackage

(python27) d:\src\MyFictionalPackage>pip install -r requirements.txt
Collecting cx-Freeze==5.1.1 (from -r requirements.txt (line 1))
  Using cached https://files.pythonhosted.org/packages/ba/d7/e5a699abbc04df31d28750bd4f7715f75452c57c6ea7f05acff0bc26873d/cx_Freeze-5.1.1-cp27-cp27m-win32.whl
Collecting protobuf==3.6.0 (from -r requirements.txt (line 2))
  Using cached https://files.pythonhosted.org/packages/85/f8/d09e4bf21c4de65405ce053e90542e728c5b7cf296b9df36b0bf0488f534/protobuf-3.6.0-py2.py3-none-any.whl
Collecting pyodbc==4.0.23 (from -r requirements.txt (line 3))
  Using cached https://files.pythonhosted.org/packages/fe/0c/3fa53bf0f1779ef3e3a81e474d1e8db924b7398dc12f2fe9b2c9f1bf392d/pyodbc-4.0.23-cp27-cp27m-win32.whl
Collecting six==1.11.0 (from -r requirements.txt (line 4))
  Using cached https://files.pythonhosted.org/packages/67/4b/141a581104b1f6397bfa78ac9d43d8ad29a7ca43ea90a2d863fe3056e86a/six-1.11.0-py2.py3-none-any.whl
Requirement already satisfied: setuptools in d:\deploy\python27\lib\site-packages (from protobuf==3.6.0->-r requirements.txt (line 2)) (40.0.0)
Installing collected packages: cx-Freeze, six, protobuf, pyodbc
Successfully installed cx-Freeze-5.1.1 protobuf-3.6.0 pyodbc-4.0.23 six-1.11.0

(python27) d:\src\MyFictionalPackage>
```

Agora vem a hora do erro. O protobuf que foi instalado possui um pequeno bug que impede que o build_exe obtenha essa dependência corretamente na hora de gerar o executável:

```
(python27) d:\src\MyFictionalPackage>python setup.py build_exe
running build_exe
Traceback (most recent call last):
  File "setup.py", line 19, in <module>
    executables=exe
  File "D:\deploy\python27\lib\site-packages\cx_Freeze\dist.py", line 349, in setup
    distutils.core.setup(**attrs)
  File "c:\programs\python27\Lib\distutils\core.py", line 151, in setup
    dist.run_commands()
  File "c:\programs\python27\Lib\distutils\dist.py", line 953, in run_commands
    self.run_command(cmd)
  File "c:\programs\python27\Lib\distutils\dist.py", line 972, in run_command
    cmd_obj.run()
  File "D:\deploy\python27\lib\site-packages\cx_Freeze\dist.py", line 219, in run
    freezer.Freeze()
  File "D:\deploy\python27\lib\site-packages\cx_Freeze\freezer.py", line 616, in Freeze
    self.finder = self._GetModuleFinder()
  File "D:\deploy\python27\lib\site-packages\cx_Freeze\freezer.py", line 340, in _GetModuleFinder
    finder.IncludeModule(name)
  File "D:\deploy\python27\lib\site-packages\cx_Freeze\finder.py", line 651, in IncludeModule
    namespace = namespace)
  File "D:\deploy\python27\lib\site-packages\cx_Freeze\finder.py", line 351, in _ImportModule
    raise ImportError("No module named %r" % name)
ImportError: No module named 'google.protobuf'

(python27) d:\src\MyFictionalPackage>
```

Para fazer funcionar há um pequeno patch: criar um arquivo \_\_init\_\_.py dentro da pasta google onde está instalado o pacote do protobuf:

```
(python27) d:\src\MyFictionalPackage>dir d:\deploy\python27\Lib\site-packages\google
 Volume in drive D is SYSTEM
 Volume Serial Number is 5C08-36EE

 Directory of d:\deploy\python27\Lib\site-packages\google

14/07/2018  14:15    <DIR>          .
14/07/2018  14:15    <DIR>          ..
14/07/2018  14:15    <DIR>          protobuf
               0 File(s)              0 bytes
               3 Dir(s)  102.341.001.216 bytes free

(python27) d:\src\MyFictionalPackage>copy con d:\deploy\python27\Lib\site-packages\google\\_\_init\_\_.py
^Z
        1 file(s) copied.

(python27) d:\src\MyFictionalPackage>dir d:\deploy\python27\Lib\site-packages\google
 Volume in drive D is SYSTEM
 Volume Serial Number is 5C08-36EE

 Directory of d:\deploy\python27\Lib\site-packages\google

14/07/2018  14:19    <DIR>          .
14/07/2018  14:19    <DIR>          ..
14/07/2018  14:15    <DIR>          protobuf
14/07/2018  14:19                 0 __init__.py
               1 File(s)              0 bytes
               3 Dir(s)  102.341.001.216 bytes free

(python27) d:\src\MyFictionalPackage>
```

Após essa pequena operação já será possível gerar o executável com sucesso:

```
(python27) d:\src\MyFictionalPackage>python setup.py build_exe
running build_exe
copying D:\deploy\python27\lib\site-packages\cx_Freeze\bases\Console.exe -> build\exe.win32-2.7\MyFictionalPackage.exe
copying C:\WINDOWS\SYSTEM32\python27.dll -> build\exe.win32-2.7\python27.dll
*** WARNING *** unable to create version resource
install pywin32 extensions first
writing zip file build\exe.win32-2.7\lib\library.zip

  Name                      File
  ----                      ----
m BUILD_CONSTANTS
m Objects_pb2               d:\src\MyFictionalPackage\Objects_pb2.py
P Scripts                   d:\src\MyFictionalPackage\Scripts\__init__.py
m StringIO                  c:\programs\python27\Lib\StringIO.py
m UserDict                  D:\deploy\python27\lib\UserDict.py
m __builtin__
m __future__                c:\programs\python27\Lib\__future__.py
m __main__
m __startup__               D:\deploy\python27\lib\site-packages\cx_Freeze\initscripts\__startup__.py
m _abcoll                   D:\deploy\python27\lib\_abcoll.py
m _codecs
m _codecs_cn
m _codecs_hk
m _codecs_iso2022
... lots and lots of dependencies ...
m unittest.result           c:\programs\python27\Lib\unittest\result.py
m unittest.runner           c:\programs\python27\Lib\unittest\runner.py
m unittest.signals          c:\programs\python27\Lib\unittest\signals.py
m unittest.suite            c:\programs\python27\Lib\unittest\suite.py
m unittest.util             c:\programs\python27\Lib\unittest\util.py
m warnings                  D:\deploy\python27\lib\warnings.py
m weakref                   c:\programs\python27\Lib\weakref.py
m zipimport
m zlib

Missing modules:
? _emx_link imported from os
? ce imported from os
? fcntl imported from subprocess
? google.protobuf._use_fast_cpp_protos imported from google.protobuf.internal.api_implementation
? google.protobuf.enable_deterministic_proto_serialization imported from google.protobuf.internal.api_implementation
? google.protobuf.internal._api_implementation imported from google.protobuf.internal.api_implementation
? google.protobuf.internal.use_pure_python imported from google.protobuf.internal.api_implementation
? google.protobuf.pyext._message imported from google.protobuf.descriptor, google.protobuf.internal.api_implementation, google.protobuf.pyext.cpp_message
? ordereddict imported from google.protobuf.json_format
? org.python.core imported from copy, pickle
? os.path imported from os, pkgutil, shlex
? os2 imported from os
? os2emxpath imported from os
? posix imported from os
? pwd imported from posixpath
? riscos imported from os
? riscosenviron imported from os
? riscospath imported from os
This is not necessarily a problem - the modules may not be needed on this platform.

copying c:\programs\python27\DLLs\_hashlib.pyd -> build\exe.win32-2.7\lib\_hashlib.pyd
copying C:\WINDOWS\SYSTEM32\python27.dll -> build\exe.win32-2.7\lib\python27.dll
copying c:\programs\python27\DLLs\_socket.pyd -> build\exe.win32-2.7\lib\_socket.pyd
copying c:\programs\python27\DLLs\_ssl.pyd -> build\exe.win32-2.7\lib\_ssl.pyd
copying c:\programs\python27\DLLs\bz2.pyd -> build\exe.win32-2.7\lib\bz2.pyd
copying D:\deploy\python27\lib\site-packages\pyodbc.pyd -> build\exe.win32-2.7\lib\pyodbc.pyd
copying c:\programs\python27\DLLs\select.pyd -> build\exe.win32-2.7\lib\select.pyd
copying c:\programs\python27\DLLs\unicodedata.pyd -> build\exe.win32-2.7\lib\unicodedata.pyd

(python27) d:\src\MyFictionalPackage>
```

Agora ao listarmos os executáveis gerados encontraremos nosso amigo fictício:

```
(python27) d:\src\MyFictionalPackage>dir /s /b *.exe
d:\src\MyFictionalPackage\build\exe.win32-2.7\MyFictionalPackage.exe

(python27) d:\src\MyFictionalPackage>
```

**Nota**: conteúdo do arquivo setup.py:

```py
import sys
import os
from cx_Freeze import setup, Executable

exe = [
        Executable('MyFictionalPackage.py')
]

option = { 'build_exe' : {
        'path' : sys.path.append(os.getcwd()),
        'includes' : ['google.protobuf', 'pkgutil', 'pyodbc', 'decimal'],
    }
}

setup(name = "teste_cx_Freeze",
        version = "0.1",
        description = "",
        options = option,
        executables=exe
)

(python27) d:\src\MyFictionalPackage>
```

