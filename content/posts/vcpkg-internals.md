---
date: 2018-09-12
title: "Vcpkg Internals: como o gerenciador de pacotes da M$ funciona por dentro (e como fazer seu próprio pacote!)"
categories: [ "draft", "code" ]
desc: "Visual Studio, Visual Code, package, CMake, triple."
---
Depois de entender mais ou menos como funciona o vcpkg é hora de realmente entrar no código e entender qual a grande sacada dessa ferramenta da Microsoft.

### Depurando o projeto

Uma das formas mais divertidas de entender o funcionamento de um fonte é compilar e sair depurando. E foi o que eu fiz. Através dos step ins e step outs foi possível ter as primeiras impressões de em qual pé está o projeto, além de pegar boas ideias para meu próprio código.

Por exemplo, no começo do programa encontrei uma saída simples e eficaz de como tratar entrada e saída (ou só saída) de dentro de um terminal:

```
SetConsoleCP(CP_UTF8);
SetConsoleOutputCP(CP_UTF8);
```

Com tudo UTF-8 a vida fica mais fácil.

Outro ponto interessante é que o fonte é muito C++ moderno, com direito a inclusive usar headers ainda experimentais, como o <filesystem> (C++ 17). Ele usa também um conjunto de paths sobre onde estão as coisas (instalação, pacotes, etc). Há muito código no vcpkg que são módulos independentes que soam como retrabalho de coisas comuns, como [parseamento de argumentos](/getarg) (e a já citada transformação em UTF-8), mas o objetivo do projeto é ser independente de tudo. Do contrário ele não seria um bom gerenciador de pacotes.

O arquivo vcpkg\installed\vcpkg\status contém em formato texto simples o status de todos os pacotes instalados (se foi instalado com sucesso ou não, etc). A pasta vcpkg\ports contém todos os pacotes, instalados ou não. O início de tudo é o executável na pasta-raiz após compilado, vcpkg.exe, feito em C++ e que realiza todas as bruxarias para montar a hierarquia de pastas e arquivos em texto. Tudo é tão simples e baseado em arquivos de texto que vejo que a M$ finalmente se rendeu ao jeito unix de fazer as coisas (mais conhecido como o jeito certo).

### Triplets

No gerenciador de pacotes há um conceito chamado de [triplet](https://github.com/Microsoft/vcpkg/blob/master/docs/users/triplets.md), que não é uma novidade; é uma forma de especificar um conjunto de elementos do ambiente para cross compiling utilizando um simples nome.

```
c:\Libs\vcpkg>vcpkg help triplet
Available architecture triplets:
  arm-uwp
  arm-windows
  arm64-uwp
  arm64-windows
  x64-linux
  x64-osx
  x64-uwp
  x64-windows
  x64-windows-static
  x86-uwp
  x86-windows
  x86-windows-static
  x86-windows-static-v140xp  <--- essa eu criei
```

O vcpkg já vem com alguns triplets de fábrica, mas você pode criar os seus próprios na pasta triplets, alterando várias variáveis de controle de compilação:

 - VCPKG_TARGET_ARCHITECTURE. A arquitetura alvo (x86, x64, arm, arm64).
 - VCPKG_CRT_LINKAGE. A linkagem do CRT (que é mais conhecida pelo pessoal do Zwindows; valores: dynamic, static).
 - VCPKG_LIBRARY_LINKAGE. O mesmo do CRT, mas para libs (as bibliotecas podem ignorar se elas não suportam isso).
 - VCPKG_CMAKE_SYSTEM_NAME. A plataforma alvo, que pode ser vazio (o Windows desktop padrão), WindowsStore, Darwin (Mac OSX) ou Linux.
 - VCPKG_PLATFORM_TOOLSET. O toolset do Visual Studio (mais uma coisa do Zwindows); v141, v140 são valores válidos (vazio também).
 - VCPKG_VISUAL_STUDIO_PATH. Onde está a instalação do Visual Studio (é, o vcpkg tem uma certa tendência pro Zwindows).
 - VCPKG_CHAINLOAD_TOOLCHAIN_FILE. Esse não é do Zwindows, mas do [CMake](https://cmake.org/cmake/help/v3.11/manual/cmake-toolchains.7.html); a possibilidade de escolher outro toolchain (diferente de scripts/toolchains) para o CMake.

#### VCPKG_CXX_FLAGS

Há diversas flags de compilação que podem ser especificadas direto no triplet:

 - VCPKG_CXX_FLAGS_DEBUG
 - VCPKG_CXX_FLAGS_RELEASE
 - VCPKG_C_FLAGS
 - VCPKG_C_FLAGS_DEBUG
 - VCPKG_C_FLAGS_RELEASE

#### Customização per-port

A macro do CMake PORT será interpretada pelo triplet. Isso é uma garantia de mudanças nos settings para portabilidade. Por exemplo:

```
set(VCPKG_LIBRARY_LINKAGE static)
if(PORT MATCHES "qt5-")
    set(VCPKG_LIBRARY_LINKAGE dynamic)
endif()
``` 

Que compila qualquer coisa que entre no match "qt5-\*" como dinâmico (DLLs), embora todo o resto possa ser estático.

### Integração com Visual Studio

A integração com o Visual Studio ocorre com o uso daqueles pedaços de configuração de projetos que são as abas de propriedades. Você mesmo pode criar abas de propriedade como arquivos separados do seu vcxproj para configurações comuns a mais projetos.

Para realizar a integração o comando é **vcpkg integrate install":

```
c:\Libs\vcpkg>vcpkg.exe integrate install
Applied user-wide integration for this vcpkg root.

All MSBuild C++ projects can now #include any installed libraries.
Linking will be handled automatically.
Installing new libraries will make them instantly available.

CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=c:/Libs/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

Note que as coisas para quem usa CMake são automáticas e fáceis de usar. Basta acrescentar o toolchain especificado. Já para Visual Studio...

### Behind the scene

O mecanismo envolve uma pasta do msbuild:

**C:\Program Files (x86)\MSBuild\Microsoft.Cpp\v4.0\V140\ImportBefore\Default**

Dentro dessa pasta é colocado um desses pedaços de configuração (propriedades) chamado **vcpkg.system.props**.

```
<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <!-- version 1 -->
  <PropertyGroup>
    <VCLibPackagePath Condition="'$(VCLibPackagePath)' == ''">$(LOCALAPPDATA)\vcpkg\vcpkg.user</VCLibPackagePath>
  </PropertyGroup>
  <Import Condition="'$(VCLibPackagePath)' != '' and Exists('$(VCLibPackagePath).targets')" Project="$(VCLibPackagePath).targets" />
</Project>
```

Essa diretiva usa a pasta definida pela variável de ambiente **LOCALAPPDATA** (geralmente C:\Users\<seu-usuario>\AppData\Local) para localizar um outro arquivo, o **vcpkg.user.targets**.

```
<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <Import Condition="Exists('C:\Libs\vcpkg\scripts\buildsystems\msbuild\vcpkg.targets') and '$(VCPkgLocalAppDataDisabled)' == ''" Project="C:\Libs\vcpkg\scripts\buildsystems\msbuild\vcpkg.targets" />
</Project>
```

No exemplo estou usando um vcpkg disponível na pasta c:\libs (que é basicamente um clone do repositório GitHub do vcpkg). Note que ele inclui automaticamente nos projetos do Visual Studio um target dentro dele, o **vcpkg\scripts\buildsystems\msbuild\vcpkg.targets**. Vejamos o que tem nele:

```
<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <!-- ... -->
  <ItemDefinitionGroup Condition="'$(VcpkgEnabled)' == 'true'">
    <Link>
      <AdditionalDependencies Condition="'$(VcpkgNormalizedConfiguration)' == 'Debug' and '$(VcpkgAutoLink)' != 'false'">%(AdditionalDependencies);$(VcpkgRoot)debug\lib\*.lib</AdditionalDependencies>
      <AdditionalDependencies Condition="'$(VcpkgNormalizedConfiguration)' == 'Release' and '$(VcpkgAutoLink)' != 'false'">%(AdditionalDependencies);$(VcpkgRoot)lib\*.lib</AdditionalDependencies>
      <AdditionalLibraryDirectories Condition="'$(VcpkgNormalizedConfiguration)' == 'Release'">%(AdditionalLibraryDirectories);$(VcpkgRoot)lib;$(VcpkgRoot)lib\manual-link</AdditionalLibraryDirectories>
      <AdditionalLibraryDirectories Condition="'$(VcpkgNormalizedConfiguration)' == 'Debug'">%(AdditionalLibraryDirectories);$(VcpkgRoot)debug\lib;$(VcpkgRoot)debug\lib\manual-link</AdditionalLibraryDirectories>
    </Link>
    <ClCompile>
      <AdditionalIncludeDirectories>%(AdditionalIncludeDirectories);$(VcpkgRoot)include</AdditionalIncludeDirectories>
    </ClCompile>
    <ResourceCompile>
      <AdditionalIncludeDirectories>%(AdditionalIncludeDirectories);$(VcpkgRoot)include</AdditionalIncludeDirectories>
    </ResourceCompile>
  </ItemDefinitionGroup>

  <!-- ... -->
  </Target>
</Project>
```

Note como as pastas de instalação dos pacotes do triplet selecionado são incluídas na configuração de um projeto do Visual Studio. As libs ficam na subpasta installed/<triplet>/lib, os binários em installed/<triplet>/bin, os includes em installed/<triplet>/include e assim por diante. A ramificação dos pacotes está de acordo com o basename de cada um deles.

A mágica ocorre já na hora de dar include. E é mágica desde o autocomplete até o link. Por exemplo, digamos que vamos fazer um embedded de Python usando o [exemplo do help](https://docs.python.org/3/extending/embedding.html):

![](https://i.imgur.com/7XMj026.png)

```
int main(int argc, char* argv[])
{
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    Py_SetProgramName(program);  /* optional but recommended */
    Py_Initialize();
    PyRun_SimpleString("from time import time,ctime\n"
        "print('Today is', ctime(time()))\n");
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    PyMem_RawFree(program);
    return 0;
}
```

O programa compila e linka. Para provar que ele usa a lib instalada (versão debug):

```
c:\Libs\vcpkg>dir /s /b installed\x86-windows\*python*.lib
c:\Libs\vcpkg\installed\x86-windows\debug\lib\boost_python36-vc140-mt-gd.lib
c:\Libs\vcpkg\installed\x86-windows\debug\lib\python36_d.lib
c:\Libs\vcpkg\installed\x86-windows\lib\boost_python36-vc140-mt.lib
c:\Libs\vcpkg\installed\x86-windows\lib\python36.lib

c:\Libs\vcpkg>mv c:\Libs\vcpkg\installed\x86-windows\debug\lib\python36_d.lib \Temp
```

```
1>------ Rebuild All started: Project: ConsoleApplication1, Configuration: Debug Win32 ------
1>pch.cpp
1>ConsoleApplication1.cpp
1>LINK : fatal error LNK1104: cannot open file 'python36_d.lib'
1>Done building project "ConsoleApplication1.vcxproj" -- FAILED.
========== Rebuild All: 0 succeeded, 1 failed, 0 skipped ==========
```

Se você prestou atenção ao conteúdo de msbuild\vcpkg.targets lá em cima vai ter visto que há uma condição que adiciona toda e qualquer lib como dependência adicional ao projeto compilando:

```
<AdditionalDependencies Condition="'$(VcpkgNormalizedConfiguration)' == 'Debug' and '$(VcpkgAutoLink)' != 'false'">%(AdditionalDependencies);$(VcpkgRoot)debug\lib\*.lib</AdditionalDependencies>
<AdditionalDependencies Condition="'$(VcpkgNormalizedConfiguration)' == 'Release' and '$(VcpkgAutoLink)' != 'false'">%(AdditionalDependencies);$(VcpkgRoot)lib\*.lib</AdditionalDependencies>
```

É isso que resolve o problema de saber qual o nome da lib resultante de um pacote instalado. Porém, isso não é o ideal, principalmente por dois motivos:

 1. Os nomes de configuração do projeto tem que ser Debug ou Release (maneiras de melhorar já está sendo discutido [no GitHub](https://github.com/Microsoft/vcpkg/issues/1638)).
 2. O usuário final não tem qualquer controle do que adicionar como dependência; simplesmente vai todos os pacotes instalados (mais uma discussão [no GitHub](https://github.com/Microsoft/vcpkg/issues/306)).

Porém, no momento é assim que funciona. Para o problema #1 a solução paliativa é o próprio usuário adicionar em seu msbuild as condições de sua configuração. A sugestão da thread é boa:

```
<AdditionalDependencies Condition="$(VcpkgConfiguration.StartsWith('Debug')) and '$(VcpkgAutoLink)' != 'false'">%(AdditionalDependencies);$(VcpkgRoot)debug\lib\*.lib</AdditionalDependencies>
```

Pelo menos tudo que começar com Debug (ou Release) já entraria no filtro.

**Update**: Essa sugestão já foi adicionada à última versão do vcpkg. É feita uma normalização do nome:

```
  <PropertyGroup Condition="'$(VcpkgEnabled)' == 'true'">
    <VcpkgConfiguration Condition="'$(VcpkgConfiguration)' == ''">$(Configuration)</VcpkgConfiguration>
    <VcpkgNormalizedConfiguration Condition="$(VcpkgConfiguration.StartsWith('Debug'))">Debug</VcpkgNormalizedConfiguration>
    <VcpkgNormalizedConfiguration Condition="$(VcpkgConfiguration.StartsWith('Release')) or '$(VcpkgConfiguration)' == 'RelWithDebInfo' or '$(VcpkgConfiguration)' == 'MinSizeRel'">Release</VcpkgNormalizedConfiguration>
    <VcpkgRoot Condition="'$(VcpkgRoot)' == ''">$([MSBuild]::GetDirectoryNameOfFileAbove($(MSBuildThisFileDirectory), .vcpkg-root))\installed\$(VcpkgTriplet)\</VcpkgRoot>
    <VcpkgApplocalDeps Condition="'$(VcpkgApplocalDeps)' == ''">true</VcpkgApplocalDeps>
  </PropertyGroup>
```

Assim o que seguir é Debug ou Release =).

### F5 que funciona

Um outro potencial problema dos usuários de Visual Studio para compilar e rodar projetos C++ são as dependências de binários (DLLs). É possível que um pacote seja compilado de maneira dinâmica, ou seja, com DLLs de dependência. Essas DLLs na instalação do pacote devem constar na pasta bin, mas por conta dessa pasta não fazer parte dos diretórios de sistema o depurador do Visual Studio irá carregar um executável em sua pasta de geração em que não encontrará as eventuais DLLs que ele precisa para rodar.

Para "corrigir" isso, ou melhor dizendo, contornar a experiência, também foi adicionado um comando Post Build no vcpkg.targets com um comando Power Shell que copia esses binários para a pasta de geração do projeto atual. Dessa forma o projeto pode rodar sem problemas, o usuário fica feliz e consegue terminar sua programação antes de passar para o deploy (e facilita deploys de testes, pois basta copiar a pasta de geração do executável que todas suas dependências estarão lá).

```
  <Target Name="AppLocalFromInstalled" AfterTargets="CopyFilesToOutputDirectory" BeforeTargets="CopyLocalFilesOutputGroup;RegisterOutput" Condition="'$(VcpkgEnabled)' == 'true' and '$(VcpkgApplocalDeps)' == 'true'">
    <WriteLinesToFile
    File="$(TLogLocation)$(ProjectName).write.1u.tlog"
    Lines="^$(TargetPath);$([System.IO.Path]::Combine($(ProjectDir),$(IntDir)))vcpkg.applocal.log" Encoding="Unicode"/>
    <Exec Condition="$(VcpkgConfiguration.StartsWith('Debug'))"
      Command="$(SystemRoot)\System32\WindowsPowerShell\v1.0\powershell.exe -ExecutionPolicy Bypass -noprofile -File %22$(MSBuildThisFileDirectory)applocal.ps1%22 %22$(TargetPath)%22 %22$(VcpkgRoot)debug\bin%22 %22$(TLogLocation)$(ProjectName).write.1u.tlog%22 %22$(IntDir)vcpkg.applocal.log%22"
      StandardOutputImportance="Normal">
    </Exec>
    <Exec Condition="$(VcpkgConfiguration.StartsWith('Release'))"
      Command="$(SystemRoot)\System32\WindowsPowerShell\v1.0\powershell.exe -ExecutionPolicy Bypass -noprofile -File %22$(MSBuildThisFileDirectory)applocal.ps1%22 %22$(TargetPath)%22 %22$(VcpkgRoot)bin%22 %22$(TLogLocation)$(ProjectName).write.1u.tlog%22 %22$(IntDir)vcpkg.applocal.log%22"
      StandardOutputImportance="Normal">
    </Exec>
    <ReadLinesFromFile File="$(IntDir)vcpkg.applocal.log">
      <Output TaskParameter="Lines" ItemName="VcpkgAppLocalDLLs" />
    </ReadLinesFromFile>
    <Message Text="@(VcpkgAppLocalDLLs,'%0A')" Importance="Normal" />
    <ItemGroup>
      <ReferenceCopyLocalPaths Include="@(VcpkgAppLocalDLLs)" />
    </ItemGroup>
  </Target>
```

O script executado pelo PowerShell fica em **vcpkg\scripts\buildsystems\msbuild** e recebe o TargetPath (o binário-alvo) como parâmetro e onde estão os binários instalados pelo vcpkg, e com base na saída da ferramenta dumpbin extrai as dependências do executável e as busca no diretório bin:

```
$a = $(dumpbin /DEPENDENTS $targetBinary | ? { $_ -match "^    [^ ].*\.dll" } | % { $_ -replace "^    ","" })
```

Isso é o equivalente ao uso padrão de dumpbin com grep e sed:

```
c:\Libs\vcpkg>dumpbin /DEPENDENTS  c:\...\Debug\ConsoleApplication1.exe | grep "^    .*.dll" | sed "s/^    \(.*.dll\)/\1/"
python36_d.dll
VCRUNTIME140D.dll
ucrtbased.dll
KERNEL32.dll
```

A cópia dos binários é feito com um teste simples de "path existe" com deploy:

```
if (Test-Path "$installedDir\$_") {
    deployBinary $baseTargetBinaryDir $installedDir "$_"
```

**Fato curioso**: no script do PowerShell existem alguns hacks para alguns pacotes, incluindo Qt.

### CMake for the win!

O uso do CMake permite aos usuários do vcpkg ter boas ideias apenas lendo os scripts do projeto. Se você abrir o solution vcpkg.sln dentro de toolsrc vai descobrir todos os scripts listados por lá. Há funções espertinhas como o download e extração de pacotes 7zip do Source Forge.

![](https://i.imgur.com/aOHtf5a.png)

Essa parte fica em **vcpkg/scripts/cmake**. Olhe, por exemplo, como retornar a versão do Windows SDK (vcpkg_get_windows_sdk.cmake):

```
# Returns Windows SDK number via out variable "ret"
function(vcpkg_get_windows_sdk ret)
    set(WINDOWS_SDK $ENV{WindowsSDKVersion})
    string(REPLACE "\\" "" WINDOWS_SDK "${WINDOWS_SDK}")
    set(${ret} ${WINDOWS_SDK} PARENT_SCOPE)
endfunction()
```

Assim como o esquema de triplets, tudo pode ser atualizado conforme o gosto do freguês, adicionando funções e configurações úteis em seu clone do repositório, e feitas atualizações com a versão oficial.

### Exportando instalações

O vcpkg não é apenas um ecossistema de libs compiladas e instaladas em uma pasta para serem usadas localmente. Pode ser um caminho simples e rápido para você conseguir compilar libs conhecidas e entregar para um terceiro um zip com todos os includes, libs e dependências do seu projeto.

```
c:\Libs\vcpkg>vcpkg.exe export python3 --7zip
The following packages are already built and will be exported:
    python3:x86-windows
Exporting package python3:x86-windows...
Exporting package python3:x86-windows... done
Creating 7zip archive...
Creating 7zip archive... done
7zip archive exported at: c:/Libs/vcpkg/vcpkg-export-20180912-172712.7z

To use the exported libraries in CMake projects use:
    "-DCMAKE_TOOLCHAIN_FILE=[...]/scripts/buildsystems/vcpkg.cmake"
```

### Montando seu próprio pacote

Para trabalhar em equipe é vital que todos falem a mesma língua. Uma das formas disso acontecer é usar um gerenciamento de pacotes que inclua todos os ambientes que a equipe usa. Como geralmente esses ambiente não são os mesmos, o uso de pacotes próprios do vcpkg é um plus da ferramenta que vem para somar em padronização de fontes e compilação.

Primeiro de tudo é interessante existir um local público de download dos fontes (caso o projeto seja opensource; se bem que é possível que o endereço seja apenas visível para usuários logados ou outro mecanismo de proteção).

Uma estrutura simples de lib que compila com CMake, por exemplo, deverá conter alguns arquivos mínimos:

```
c:\Libs\vcpkg>dir /s /b \Libs\bitforge
c:\Libs\bitforge\bitforge.cpp
c:\Libs\bitforge\bitforge.h
c:\Libs\bitforge\CMakeLists.txt
c:\Libs\bitforge\LICENSE
```

Um .cpp com a implementação, um .h público para o usuário acessar, uma licença de uso (LICENSE) e um arquivo CMakeLists.txt são o suficiente para demonstar o uso. Dentro do CMakeLists.txt temos as seguintes diretivas:

```
cmake_minimum_required (VERSION 3.11.2)
project(bitforge VERSION 18.9.12 LANGUAGES CXX)
add_library(bitforge STATIC bitforge.cpp)
install(TARGETS bitforge DESTINATION lib)
install(FILES bitforge.h DESTINATION include)
```

A partir de um zip na internet da pasta bitforge já é possível começar a montar seu próprio pacote:

```
c:\Libs\vcpkg>vcpkg.exe create bitforge http://caloni.com.br/release/bitforge-18.9.12.zip bitforge-18.9.12.zip
-- Downloading http://caloni.com.br/release/bitforge-18.9.12.zip...
-- Generated portfile: C:\Libs\vcpkg\ports\bitforge\portfile.cmake
-- Generated CONTROL: C:\Libs\vcpkg\ports\bitforge\CONTROL
-- To launch an editor for these new files, run
--     .\vcpkg edit bitforge
```

_Dica: você pode também testar ou implantar isso localmente usando Python:_

```
python3 -m http.server
python -m SimpleHTTPServer
```

O arquivo portfile.cmake já possui teoricamente tudo o que precisa para falhar. Há alguns caveats que podem te dar bastante dor de cabeça no começo. Por isso mesmo eu vou economizar algum tempo para você.

Em primeiro lugar, preste atenção no diretório onde estarão os fontes. É costume do template usar o mesmo nome do zip, o que nem sempre é verdade (aqui não é, não existe versão no nome da pasta zipada):

Então em vez de:

```
set(SOURCE_PATH ${CURRENT_BUILDTREES_DIR}/src/bitforge-18.9.12)
```

Isso:

```
set(SOURCE_PATH ${CURRENT_BUILDTREES_DIR}/src/bitforge)
```

O erro que deve acontecer na falta dessa mudança é o seguinte:

```
c:\Libs\vcpkg>vcpkg.exe build bitforge
-- Using cached C:/Libs/vcpkg/downloads/bitforge-18.9.12.zip
-- Configuring x86-windows
CMake Error at scripts/cmake/vcpkg_execute_required_process.cmake:56 (message):
    Command failed: ninja;-v
    Working Directory: C:/Libs/vcpkg/buildtrees/bitforge/x86-windows-rel/vcpkg-parallel-configure
    See logs for more information:
      C:\Libs\vcpkg\buildtrees\bitforge\config-x86-windows-out.log

Call Stack (most recent call first):
  scripts/cmake/vcpkg_configure_cmake.cmake:246 (vcpkg_execute_required_process)
  ports/bitforge/portfile.cmake:22 (vcpkg_configure_cmake)
  scripts/ports.cmake:71 (include)

Elapsed time for package bitforge:x86-windows: 983.4 ms
Error: Building package bitforge:x86-windows failed with: BUILD_FAILED
Please ensure you're using the latest portfiles with `.\vcpkg update`, then
submit an issue at https://github.com/Microsoft/vcpkg/issues including:
  Package: bitforge:x86-windows
  Vcpkg version: 0.0.113-nohash

Additionally, attach any relevant sections from the log files above.

c:\Libs\vcpkg>cat C:\Libs\vcpkg\buildtrees\bitforge\config-x86-windows-out.log
[1/2] cmd /c "cd .. && "C:/Libs/vcpkg/downloads/tools/cmake-3.11.4-windows/cmake-3.11.4-win32-x86/bin/cmake.exe" "C:/Libs/vcpkg/buildtrees/bitforge/src/bitforge-18.9.12" "-DCMAKE_MAKE_PROGRAM=C:/Program Files (x86)/Microsoft Visual Studio/Preview/Enterprise/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" "-DBUILD_SHARED_LIBS=ON" "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:/Libs/vcpkg/scripts/toolchains/windows.cmake" "-DVCPKG_TARGET_TRIPLET=x86-windows" "-DVCPKG_PLATFORM_TOOLSET=v141" "-DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY=ON" "-DCMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP=TRUE" "-DCMAKE_VERBOSE_MAKEFILE=ON" "-DVCPKG_APPLOCAL_DEPS=OFF" "-DCMAKE_TOOLCHAIN_FILE=C:/Libs/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION=ON" "-DVCPKG_CXX_FLAGS=" "-DVCPKG_CXX_FLAGS_RELEASE=" "-DVCPKG_CXX_FLAGS_DEBUG=" "-DVCPKG_C_FLAGS=" "-DVCPKG_C_FLAGS_RELEASE=" "-DVCPKG_C_FLAGS_DEBUG=" "-DVCPKG_CRT_LINKAGE=dynamic" "-DVCPKG_LINKER_FLAGS=" "-DCMAKE_INSTALL_LIBDIR:STRING=lib" "-DCMAKE_INSTALL_BINDIR:STRING=bin" "-G" "Ninja" "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_INSTALL_PREFIX=C:/Libs/vcpkg/packages/bitforge_x86-windows""
FAILED: ../CMakeCache.txt
cmd /c "cd .. && "C:/Libs/vcpkg/downloads/tools/cmake-3.11.4-windows/cmake-3.11.4-win32-x86/bin/cmake.exe" "C:/Libs/vcpkg/buildtrees/bitforge/src/bitforge-18.9.12" "-DCMAKE_MAKE_PROGRAM=C:/Program Files (x86)/Microsoft Visual Studio/Preview/Enterprise/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" "-DBUILD_SHARED_LIBS=ON" "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:/Libs/vcpkg/scripts/toolchains/windows.cmake" "-DVCPKG_TARGET_TRIPLET=x86-windows" "-DVCPKG_PLATFORM_TOOLSET=v141" "-DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY=ON" "-DCMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP=TRUE" "-DCMAKE_VERBOSE_MAKEFILE=ON" "-DVCPKG_APPLOCAL_DEPS=OFF" "-DCMAKE_TOOLCHAIN_FILE=C:/Libs/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION=ON" "-DVCPKG_CXX_FLAGS=" "-DVCPKG_CXX_FLAGS_RELEASE=" "-DVCPKG_CXX_FLAGS_DEBUG=" "-DVCPKG_C_FLAGS=" "-DVCPKG_C_FLAGS_RELEASE=" "-DVCPKG_C_FLAGS_DEBUG=" "-DVCPKG_CRT_LINKAGE=dynamic" "-DVCPKG_LINKER_FLAGS=" "-DCMAKE_INSTALL_LIBDIR:STRING=lib" "-DCMAKE_INSTALL_BINDIR:STRING=bin" "-G" "Ninja" "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_INSTALL_PREFIX=C:/Libs/vcpkg/packages/bitforge_x86-windows""

--- IMPORTANTE ---
CMake Error: The source directory "C:/Libs/vcpkg/buildtrees/bitforge/src/bitforge-18.9.12" does not exist.
--- IMPORTANTE ---
```

Em segundo lugar, a cópia do header é feita tanto em release quanto em debug. A compilação via vcpkg irá te avisar que tem alguma coisa errada pois está duplicado, mas já há uma linha mágica que pode ser adicionada:

```
# Fix duplicated include
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)
```

O erro que deve acontecer na falta dessa mudança é o seguinte:

```
c:\Libs\vcpkg>vcpkg.exe build bitforge
-- Using cached C:/Libs/vcpkg/downloads/bitforge-18.9.12.zip
-- Configuring x86-windows
-- Building x86-windows-dbg
-- Building x86-windows-rel
-- Performing post-build validation
--- IMPORTANTE ---
Include files should not be duplicated into the /debug/include directory. If this cannot be disabled in the project cmake, use
    file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)
--- IMPORTANTE ---
The software license must be available at ${CURRENT_PACKAGES_DIR}/share/bitforge/copyright

    file(COPY ${CURRENT_BUILDTREES_DIR}/src/bitforge/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/bitforge)
    file(RENAME ${CURRENT_PACKAGES_DIR}/share/bitforge/LICENSE ${CURRENT_PACKAGES_DIR}/share/bitforge/copyright)
Found 2 error(s). Please correct the portfile:
    c:\Libs\vcpkg\ports\bitforge\portfile.cmake
-- Performing post-build validation done
Elapsed time for package bitforge:x86-windows: 4.139 s
Error: Building package bitforge:x86-windows failed with: POST_BUILD_CHECKS_FAILED
Please ensure you're using the latest portfiles with `.\vcpkg update`, then
submit an issue at https://github.com/Microsoft/vcpkg/issues including:
  Package: bitforge:x86-windows
  Vcpkg version: 0.0.113-nohash

Additionally, attach any relevant sections from the log files above.
```

E por último, é obrigatório ter um arquivo de copyright, no caso o nosso LICENSE do projeto. O portfile.cmake já tem o comando, mas está comentado:

```
# Handle copyright
file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/bitforge RENAME copyright)
```

O erro que deve acontecer na falta dessa mudança é o seguinte:

```
c:\Libs\vcpkg>vcpkg.exe build bitforge
Your feedback is important to improve Vcpkg! Please take 3 minutes to complete our survey by running: vcpkg contact --survey
-- Using cached C:/Libs/vcpkg/downloads/bitforge-18.9.12.zip
-- Configuring x86-windows
-- Building x86-windows-dbg
-- Building x86-windows-rel
-- Performing post-build validation
--- IMPORTANTE ---
The software license must be available at ${CURRENT_PACKAGES_DIR}/share/bitforge/copyright
--- IMPORTANTE ---

    file(COPY ${CURRENT_BUILDTREES_DIR}/src/bitforge/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/bitforge)
    file(RENAME ${CURRENT_PACKAGES_DIR}/share/bitforge/LICENSE ${CURRENT_PACKAGES_DIR}/share/bitforge/copyright)
Found 1 error(s). Please correct the portfile:
    c:\Libs\vcpkg\ports\bitforge\portfile.cmake
-- Performing post-build validation done
Elapsed time for package bitforge:x86-windows: 4.188 s
Error: Building package bitforge:x86-windows failed with: POST_BUILD_CHECKS_FAILED
Please ensure you're using the latest portfiles with `.\vcpkg update`, then
submit an issue at https://github.com/Microsoft/vcpkg/issues including:
  Package: bitforge:x86-windows
  Vcpkg version: 0.0.113-nohash

Additionally, attach any relevant sections from the log files above.
```

Basicamente isso é o que você precisa para começar a construir seu pacote:

```
c:\Libs\vcpkg>vcpkg.exe build bitforge
-- Using cached C:/Libs/vcpkg/downloads/bitforge-18.9.12.zip
-- Configuring x86-windows
-- Building x86-windows-dbg
-- Building x86-windows-rel
-- Installing: C:/Libs/vcpkg/packages/bitforge_x86-windows/share/bitforge/copyright
-- Performing post-build validation
-- Performing post-build validation done
Elapsed time for package bitforge:x86-windows: 4.224 s
```

O próximo passo é instalar:

```
c:\Libs\vcpkg>vcpkg.exe install bitforge
The following packages will be built and installed:
    bitforge[core]:x86-windows
Starting package 1/1: bitforge:x86-windows
Building package bitforge[core]:x86-windows...
-- Using cached C:/Libs/vcpkg/downloads/bitforge-18.9.12.zip
-- Configuring x86-windows
-- Building x86-windows-dbg
-- Building x86-windows-rel
-- Installing: C:/Libs/vcpkg/packages/bitforge_x86-windows/share/bitforge/copyright
-- Performing post-build validation
-- Performing post-build validation done
Building package bitforge[core]:x86-windows... done
Installing package bitforge[core]:x86-windows...
Installing package bitforge[core]:x86-windows... done
Elapsed time for package bitforge:x86-windows: 4.239 s

Total elapsed time: 4.239 s

c:\Libs\vcpkg>dir /s /b installed\x86-windows\bitforge.*
c:\Libs\vcpkg\installed\x86-windows\debug\lib\bitforge.lib
c:\Libs\vcpkg\installed\x86-windows\include\bitforge.h
c:\Libs\vcpkg\installed\x86-windows\lib\bitforge.lib
c:\Libs\vcpkg\installed\x86-windows\share\bitforge
```

E voilá! Agora o include está disponível, as funções estão disponíveis, o link está funcionando e seu pacote pode ser compartilhado com toda a empresa. Basta copiar a pasta ports/bitforge ou adicioná-la no repositório por um commit.

![](https://i.imgur.com/XeeD4Se.png)

