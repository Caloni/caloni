---
date: "2007-08-13"
title: GINA x Credential Provider
categories: [ "blog" ]
---
Não fui convidado a participar do tema, mas como já faz algum tempo que o rascunho deste artigo está no molho, e aproveitando que meu amigo Ferdinando resolveu [escrever sobre nossa amiga em comum](http://www.driverentry.com.br/blog/2007/08/personal-gina-tabajara.html), darei continuidade à minha empolgação sobre o [_tagging_](http://www.caloni.com.br/como-ser-um-melhor-desenvolvedor-nos-proximos-seis-meses) e largarei aqui este pequeno adendo.

Com a chegada do Windows Vista, uma velha conhecida minha e dos meus colegas deixou de fazer parte do sistema de autenticação do sistema operacional: a velha **GINA**, _**G**raphical **I**dentification a**N**d **A**utentication._

Basicamente se trata de uma **DLL que é chamada pelo WinLogon**, o componente responsável pelo famoso _Secure Attention Sequence_ (SAS), mais conhecido por **Ctrl + Alt + Del**. Ele efetua o logon do usuário, mas quem mostra as telas de autenticação, troca de senha, bloqueio da estação é a GINA. Mexi com várias GINAs há um tempo atrás: GINAs invisíveis, GINAs que autenticam _smart cards_, GINAs que autenticam pela impressão digital, e por aí vai a valsa.

**Muitas GINAs juntas só pode dar problema
**

O Windows já vem com uma GINA padrão, a **MsGina.dll**, que autentica o usuário baseada em usuário e senha e/ou _smart card. _Teoricamente o intuito original de uma GINA fornecida por terceiros era **permitir outros meios de autenticação**. Para isso o fornecedor deveria trocar todas as telas de autenticação pela equivalente de acordo com o novo tipo de autenticação (por exemplo, um campo com uma impressão digital para permitir o uso de biometria em vez de senha). Porém, um outro uso pode ser **controlar o _login_ dos usuários** baseado em outras regras além das que o Windows já fornece.

Apesar de útil, o sistema baseado em GINAs tinha um pequeno problema: permitia somente a **troca exclusiva**, ou seja, só uma GINA pode ser ativada. Se não for a da Microsoft, que seja a do fornecedor, e **apenas** a de um fornecedor. Isso começa a ficar limitado diante das novas e conflitantes maneiras que um usuário possui hoje em dia de fazer _logon_: nome e senha, íris dos olhos, impressão digital, formato do nariz e assim por diante. Todas essas autenticações deveriam estar disponíveis ao mesmo tempo para que o usuário escolha qual deles lhe convém.

Foi por isso que surgiu seu substituto natural no Windows Vista: o [Credential Provider](http://msdn.microsoft.com/msdnmag/issues/07/01/CredentialProviders/default.aspx).

**Um ambiente democrático para a coleta de credenciais**

O sistema de Credential Provider permite que inúmeras DLLs sejam registradas no sistema para receberem eventos de _logon_, seja para criar uma nova sessão (tela de boas vindas) ou apenas para se autenticar já em uma sessão iniciada, como, por exemplo, nos casos em que o [Controle da Conta do Usuário](http://msdn2.microsoft.com/en-us/library/bb648649.aspx) (UAC: _User Account Control_) entra em ação.

O sistema de coleta foi simplificado e modernizado: agora a interface não se baseia em funções exportadas, como a GINA, mas em interfaces COM disponíveis. O desenvolvedor também consegue escolher os cenários em que ele pretende entrar em ação:

	
  * Efetuar logon

	
  * Desbloquear estação

	
  * Mudar a senha

	
  * Efetuar conexão de rede (antes do logon)

Baseado no número de CPs registrados no sistema, o LogonUI (processo responsável por exibir a tela de boas vindas) irá exibir as respectivas credenciais para cada um dos CPs envolvidos no _logon_.

**Voltando à GINA**

Já que fomos brindados com um exemplo de GINA _stub_ do Ferdinando, também irei disponibilizar um outro exemplo, este um pouco mais perigoso, da época de laboratório da faculdade. Se trata igualmente de uma GINA que se aproveita da implementação da GINA original, porém na hora de autenticar um usuário ela captura os dados do _logon_ (usuário e senha) e grava em uma parte do registro acessível apenas pelo sistema (lembre-se que a GINA, por fazer parte do WinLogon, roda na conta de sistema).

> _É claro que para utilizar essa GINA, você deve possuir direitos de administração, ou conhecer alguma brecha de segurança. Eu optei pela segunda opção, já que não tinha a primeira. Podemos dizer apenas que o [artigo sobre falhas de segurança relacionadas a usuários avançados](http://blogs.technet.com/markrussinovich/archive/2006/05/01/the-power-in-power-users.aspx) do Russinovich pôde resolver meu problema._

E é isso aí. Como é que aquele cara do DriverEntry diz mesmo? Ah, sim: [have fun](/images/mscindy.7z)! =P

[![¿Saída¿ de nossa GINA stub](http://i.imgur.com/pJRxNzi.png)](/images/mscindy.png)

**Para saber mais sobre Credential Providers (e o que fazer com sua GINA)
**

	
  * [Última referência técnica](http://shellrevealed.com/files/folders/code_samples/entry1019.aspx)

	
  * [Documentação das interfaces](http://msdn2.microsoft.com/en-us/library/ms646532.aspx)

	
  * [_Download_ de exemplos](http://www.microsoft.com/downloads/details.aspx?FamilyID=B1B3CBD1-2D3A-4FAC-982F-289F4F4B9300&displaylang=en)

	
  * [Guia de migração GINA => CP](http://msdn2.microsoft.com/en-us/library/aa480152.aspx#appcomp_topic11)

