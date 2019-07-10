---
date: "2007-08-07"
title: História do Windows - parte 3.51
categories: [ "blog" ]
---
**A história**

Nos anos 90, a relação IBM/Microsoft era muito próxima por causa do desenvolvimento do OS/2, o projeto de um novo sistema operacional. As empresas cooperavam entre si e tinham acesso uma ao código da outra. A Microsoft desejava avançar seu desenvolvimento no Windows, enquanto a IBM desejava que todo trabalho futuro fosse baseado em OS/2. Para resolver essa tensão, as duas combinaram que a IBM iria desenvolver o OS/2 versão 2.0 para substituir o OS/2 versão 1.3 e o Windows v3.0, enquanto a Microsoft iria desenvolver um novo sistema operacional, o OS/2 versão 3.0 para depois suceder ao OS/2 anterior. É lógico que esse acordo foi por água abaixo.

[![Exemplo de tela do OS/2, da IBM](http://i.imgur.com/3evUgy8.png)](http://upload.wikimedia.org/wikipedia/en/f/f0/Nt351excel.png)

A relação IBM/Microsoft foi terminada. A IBM continuou a desenvolver o OS/2 v2.0 enquanto a Microsoft mudou o nome de seu ainda não lançado OS/2 v3.0 para Windows NT. O Windows NT foi tão massivamente promovido que a maioria das pessoas nem se deu conta que ele era um OS/2 redesenhado. Ambas as empresas obtiveram os direitos de utilizarem as tecnologias do OS/2 e do Windows que foram desenvolvidas até a quebra do acordo.

A IBM lançou a versão 2.0 do OS/2 no início dos anos 90. O sistema foi uma grande melhora sobre o antigo OS/2 v1.3. Apresentava um novo sistema de janelas orientado a objetos (o Workplace Shell) para substituir o Presentation Manager, um novo sistema de arquivos (o HPFS) para substituir o sistema FAT utilizado pelo DOS e Windows e aproveitou todas as vantagens das capacidades 32 bits do processador 386 da Intel. Ele também rodava programas DOS e Windows 3.0, uma vez que a IBM tinha acesso e direito a essas duas tecnologias.

Para concorrer com a IBM, a Microsoft lançou o Windows 3.1, com pequenas melhorias à sua versão anterior, a 3.0.

[![Microsoft Office 97 rodando em cima do Windows NT 3.51](http://upload.wikimedia.org/wikipedia/en/f/f0/Nt351excel.png)](http://upload.wikimedia.org/wikipedia/en/f/f0/Nt351excel.png)

A Microsoft continuou a desenvolver o Windows NT. A empresa requeriu os serviços de Dave Cutler, um dos chefes arquitetos da VMS na Digital Equipment Corporation (hoje parte da Compaq) para desenvolver o NT dentro de um projeto de sistema operacional mais capaz. Cutler estava desenvolvendo um seguimento para o VMS na DEC chamado Mica, e quando a DEC desistiu do projeto ele acabou trazendo para a Microsoft sua especialidade nesse sistema e algum engenheiros do projeto com ele. A DEC acreditava que ele usara parte do código do Mica no Windows NT e acabou processando a Microsoft. A empresa de Gates teve que eventualmente pagar 150 milhões para a DEC, além de concordar em suportar o chip Alpha CPU da DEC na plataforma NT.

Sendo um sistema operacional completamente novo, Windows NT sofreu com questões de compatibilidade com hardware e software geralmente usados na época. Ele era também concentrado em recursos, o que o deixava aceitável apenas para máquinas maiores e mais caras. Tanto que inicialmente foi dirigido a servidores de rede, workstations e máquinas de desenvolvimento de software. Por causa disso, a maioria dos usuário foi incapaz de migrar para a plataforma NT. E o Windows NT ainda estava projetado graficamente como o Windows 3.1, o que era inferior ao OS/2 Workplace Shell. Em resposta, a Microsoft começou a desenvolver um sucessor para o Windows 3.1, um projeto de codinome Chicago. Chicago tinha por objetivo apresentar uma nova GUI que competisse com o OS/2 Workplace Shell. Ele também foi projetado para ser de 32 bits e suportar execução multitarefa, como o OS/2 e o Windows NT. Só algumas partes do Chicago, entretanto, foram convertidas para 32 bits, e o resto permaneceu em 16. A Microsoft argumentou que a conversão total iria atrasar em muito o projeto, o que acabaria por encarecê-lo além do limite.

Para Chicago, foi desenvolvida uma nova API para substituir a de 16 bits do Windows anterior. Essa API foi chamada de Win32, e a outra renomeada para Win16. Houveram 3 ramificações: uma para o Chicago, outra para o NT e uma terceira chamada Win32s, que foi um subconjunto para o Windows 3.1 garantir a compatibilidade retroativa das versões. Também foi pensado num mínimo de compatibilidade entre o Chicago e o Windows NT, mesmo que os dois possuissem duas arquiteturas radicalmente diferentes.

Em setembro de 1994 é lançada o Windows NT 3.5. A versão Workstation substituiu o Windows NT 3.1 e a versão Server o Windows NT 3.1 Advanced Server.

**O projeto**

Como todo projeto de sucesso, a primeira coisa a ser feita é definir os objetivos principais. No caso do Windows NT não foi diferente. É importante para nós sabermos que objetivos eram esses e como eles foram mudando de acordo com o momento histórico de forma a analisarmos as conseqüências. Em outubro de 1988, os objetivos do novo sistema operacional eram os seguintes:

	
  * <strike>Compatibilidade com OS/2</strike>

	
  * Segurança

	
  * Suporte a POSIX

	
  * Multiprocessamento

	
  * Rede integrada

	
  * Confiabilidade

Como o Windows 3.0 fez um sucesso enorme, a compatibilidade nativa passou a ser do próprio Windows caseiro, sendo o OS/2 sendo implementado como um mero subsistema. Subsistema no Windows basicamente quer dizer ambiente virtual de execução de processos feitos para rodar em outro sistema operacional. Essa maneira de suportar processos de outros sistemas operacionais foi usado tanto para o OS/2 quanto para o Windows 16 bits, o MS-DOS e aplicativos POSIX.

O tempo do projeto foi inicialmente estimado em pouco mais de dois anos. Ao final, quatro anos e meio se passaram até a chegada do primeiro _release_, que era grande e lento para as máquinas da época. Assim foi iniciado o projeto Daytona, que teve como novos objetivos tornar a nova versão do NT mais rápida e confiável. Foi lançada então a versão 3.51.

**A arquitetura**

O Windows NT é um sistema operacional de 32 bits. Isso quer dizer, entre outras coisas, que ele suporta duas propriedades fundamentais dos sistemas operacionais modernos: **modo protegido de execução** e **memória virtual**. O modo protegido de execução permite a divisão entre a parte confiável do sistema operacional (_kernel mode_) e a parte não-confiável, que não possui acesso às instruções privilegiadas (_user mode_). A memória virtual abstrai a memória física e permite isolamento de memória entre aplicativos, evitando que um programa invada a memória do outro.

Além disso, foi criada uma camada de abstração do _hardware_ (HAL, _Hardware Abstraction Layer_)_ _que livrou boa parte do código de ter sido escrito em _assembly_, fazendo assim que ele fosse facilmente portável. A figura abaixo demonstra a divisão básica entre os componentes do sistema, tanto do _kernel mode _quanto do _user mode_:

[![Arquitetura do Windows NT](http://i.imgur.com/HARIMUp.gif)](/images/windows-nt-architecture.gif)

**Para conhecer mais**

	
  * [Inside Microsoft Windows NT](http://compare.buscape.com.br/categoria?lkout=1&id=3482&kw=Inside+WindowsNT+Solomon&site_origem=1293522), by David Solomon

	
  * [Inside Microsoft Windows 2000](http://compare.buscape.com.br/categoria?lkout=1&id=3482&kw=Inside+Windows+2000+0735610215&site_origem=1293522), by David Solomon

	
  * [Windows Internals](http://compare.buscape.com.br/categoria?lkout=1&id=3482&kw=Windows+Internals+Russinovich&site_origem=1293522), by Mark Russinovich

	
  * [Outros artigos sobre a história do windows](http://www.caloni.com.br/search/historia%20do%20windows%20-%20parte)

