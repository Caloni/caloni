---
date: "2007-12-13"
categories: [ "code" ]
title: "Debug remoto no C++ Builder"
---
Esse é um detalhe que pode passar despercebido da maioria da população Borland, mas o Builder, assim como o Visual Studio, possui sua suíte para depuração remota. E tudo o que você precisa fazer é instalar um pacote no cliente.

  1. No CD de instalação, existe uma pasta chamada RDEBUG.
  2. Na máquina cliente, execute o arquivo setup.exe contido nesta pasta. De preferência, não instale como um serviço (a menos que tenha um motivo).
  3. Crie uma aplicação tosca de teste (ou use uma aplicação tosca existente).
  4. Lembre-se que as DLLs do Builder não estarão disponíveis na máquina remota. Para não depender delas desabilite as opções "Use dynamic RTL" (aba Link) e "Build with runtime packages" (aba Packages) do seu projeto.
  5. Copie a aplicação para a máquina remota ou torne-a acessível através de mapeamento.
  6. Em Run, Parameters, habilite na aba Remote a opção "Debug project on remote machine"
  7. Em Remote Path especifique o path de sua aplicação visto da máquina remota.
  8. Em Remote Host especifique o nome ou o IP da máquina remota.
  9. Execute o aplicativo através do Builder (certifique-se que o cliente do Builder está rodando na máquina remota).
  10. Bom proveito!

Infelizmente essa opção não está disponível nas versões Standard do produto, assim como não está o debugging remoto no Visual Studio Express. Porém, a nova versão do Builder, renomeada para Borland Turbo C++, é gratuita a possui essa feature embutida. O único porém é que a instalação não é automatizada, e os arquivos devem ser copiados "na mão", seguindo um dos tópicos da ajuda. Melhor que nada.

Para os que utilizam o Visual Studio Express, realmente ainda não achei solução a não ser usar o bom, velho e fiel companheiro WinDbg. Não saia de casa sem ele.
