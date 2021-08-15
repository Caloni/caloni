---
categories:
- code
date: '2017-02-08'
tags:
title: Pacotes perdidos do NuGet em projetos C++ no Visual Studio
---

É muito bom (para quem gosta) usar a IDE e viver feliz sem precisar se preocupar em digitar comandos estranhos no prompt. Porém, essa vida acaba quando ocorre o primeiro erro inexplicável, aquele tipo de erro que não importa onde você olhe, não há nada para olhar. Até você apelar para ferramentas de macho.

Que nem hoje de manhã, quando fui inocentemente baixar uma versão limpa do [tiodb](https://github.com/tiodb/tiodb) e após baixar todos os pacotes do [NuGet](https://docs.microsoft.com/pt-br/nuget/consume-packages/overview-and-workflow), o gerenciador de pacotes do Visual Studio (inclusive para C++, agora) acusou a falta do boost, sendo que ele havia acabado de baixá-lo:

![](http://i.imgur.com/HUp5S4K.png)

![](http://i.imgur.com/IfVDNN9.png)

![](http://i.imgur.com/Yi8kVgC.png)

Os pacotes do projeto ficam todos na raiz do diretório da solução na sub-pasta packages. Observando o que foi baixado lá, verifiquei que a versão do boost estava ok: ele havia baixado a 1.61 como pedido, mas o erro dizia respeito justamente a um desses pacotes.

```
C:\Projects\tiodb>dir /b packages
boost.1.61.0.0
boost_chrono-vc140.1.61.0.0
boost_date_time-vc140.1.61.0.0
boost_filesystem-vc140.1.61.0.0
boost_program_options-vc140.1.61.0.0
boost_regex-vc140.1.61.0.0
boost_system-vc140.1.61.0.0
boost_thread-vc140.1.61.0.0
```

O maior problema disso é que não há muitas opções na IDE que resolvam. O arquivo packages.config deveria manter essas dependências, o que de fato ele faz. As opções do projeto (as abinhas do Visual Studio onde ficam as configurações) não possuem nada relacionado ao NuGet.

```
<?xml version="1.0" encoding="utf-8"?>
<packages>
  <package id="boost" version="1.61.0.0" targetFramework="native" />
  <package id="boost_chrono-vc140" version="1.61.0.0" targetFramework="native" />
  <package id="boost_date_time-vc140" version="1.61.0.0" targetFramework="native" />
  <package id="boost_filesystem-vc140" version="1.61.0.0" targetFramework="native" />
  <package id="boost_program_options-vc140" version="1.61.0.0" targetFramework="native" />
  <package id="boost_regex-vc140" version="1.61.0.0" targetFramework="native" />
  <package id="boost_system-vc140" version="1.61.0.0" targetFramework="native" />
  <package id="boost_thread-vc140" version="1.61.0.0" targetFramework="native" />
</packages>
```

Então não tem jeito. Há algo de podre dentro desse projeto e o próprio Visual Studio não vai resolver. Grep nele!

```
C:\Projects\tiodb>grep -r -i "boost.*1.61" --include=*proj .
./server/tio/tioserver.vcxproj:    <Import Project="packages\boost.1.61.0.0\build\native\boost.targets" Condition="Exists('packages\boost.1.61.0.0\build\native\boost.targets')" />
./server/tio/tioserver.vcxproj:    <Error Condition="!Exists('packages\boost.1.61.0.0\build\native\boost.targets')" Text="$([System.String]::Format('$(ErrorText)', 'packages\boost.1.61.0.0\build\native\boost.targets'))" />
...
```

Note (e é preciso prestar atenção!) que o projeto server/tio/tioserver.vcxproj referencia a pasta packages como se ela existisse dentro do projeto. Porém, como já sabemos, ela existe na raiz da solution, que fica duas pastas "para trás". Isso nos indica que talvez o NuGet ainda não esteja tão redondo e que um possível teste é mudar esses valores na mão e ver o que acontece.

```
gvim server\tio\tioserver.vcxproj
:%s/packages\\boost/..\\..\\packages\\boost/g
:wq
```

![](http://i.imgur.com/BLUS8XJ.png)

```
1>------ Build started: Project: tioclientdll, Configuration: Debug x64 ------
2>------ Build started: Project: tioserver, Configuration: Debug x64 ------
2>  tioserver.vcxproj -> C:\Projects\tiocoin\tiodb\server\tio\..\..\bin\x64\Debug\tio.exe
2>  tioserver.vcxproj -> ..\..\bin\x64\Debug\tio.pdb (Full PDB)
========== Build: 2 succeeded, 0 failed, 3 up-to-date, 0 skipped ==========
```

Recarregado o projeto no Visual Studio após a intervenção cirúrgica, tudo voltou a funcionar. A lição de hoje é: nunca confie completamente em uma IDE. Às vezes o bom e velho grep e o bom e velho editor de sua escolha podem resolver uma situação.
