---
date: "2007-08-13"
tags: [ "code", "draft",  ]
title: "GINA x Credential Provider"
---
Não fui convidado a participar do tema, mas como já faz algum tempo que o rascunho deste artigo está no molho, e aproveitando que meu amigo Ferdinando resolveu escrever sobre nossa amiga em comum, darei continuidade à minha empolgação sobre o tagging e largarei aqui este pequeno adendo.

Com a chegada do Windows Vista, uma velha conhecida minha e dos meus colegas deixou de fazer parte do sistema de autenticação do sistema operacional: a velha GINA, Graphical Identification aNd Autentication.

Basicamente se trata de uma DLL que é chamada pelo WinLogon, o componente responsável pelo famoso Secure Attention Sequence (SAS), mais conhecido por Ctrl + Alt + Del. Ele efetua o logon do usuário, mas quem mostra as telas de autenticação, troca de senha, bloqueio da estação é a GINA. Mexi com várias GINAs há um tempo atrás: GINAs invisíveis, GINAs que autenticam smart cards, GINAs que autenticam pela impressão digital, e por aí vai a valsa.

O Windows já vem com uma GINA padrão, a MsGina.dll, que autentica o usuário baseada em usuário e senha e/ou smart card. Teoricamente o intuito original de uma GINA fornecida por terceiros era permitir outros meios de autenticação. Para isso o fornecedor deveria trocar todas as telas de autenticação pela equivalente de acordo com o novo tipo de autenticação (por exemplo, um campo com uma impressão digital para permitir o uso de biometria em vez de senha). Porém, um outro uso pode ser controlar o login dos usuários baseado em outras regras além das que o Windows já fornece.

Apesar de útil, o sistema baseado em GINAs tinha um pequeno problema: permitia somente a troca exclusiva, ou seja, só uma GINA pode ser ativada. Se não for a da Microsoft, que seja a do fornecedor, e apenas a de um fornecedor. Isso começa a ficar limitado diante das novas e conflitantes maneiras que um usuário possui hoje em dia de fazer logon: nome e senha, íris dos olhos, impressão digital, formato do nariz e assim por diante. Todas essas autenticações deveriam estar disponíveis ao mesmo tempo para que o usuário escolha qual deles lhe convém.

Foi por isso que surgiu seu substituto natural no Windows Vista: o Credential Provider.

O sistema de Credential Provider permite que inúmeras DLLs sejam registradas no sistema para receberem eventos de logon, seja para criar uma nova sessão (tela de boas vindas) ou apenas para se autenticar já em uma sessão iniciada, como, por exemplo, nos casos em que o Controle da Conta do Usuário (UAC: User Account Control) entra em ação.

O sistema de coleta foi simplificado e modernizado: agora a interface não se baseia em funções exportadas, como a GINA, mas em interfaces COM disponíveis. O desenvolvedor também consegue escolher os cenários em que ele pretende entrar em ação:

	
  * Efetuar logon

	
  * Desbloquear estação

	
  * Mudar a senha

	
  * Efetuar conexão de rede (antes do logon)

Baseado no número de CPs registrados no sistema, o LogonUI (processo responsável por exibir a tela de boas vindas) irá exibir as respectivas credenciais para cada um dos CPs envolvidos no logon.

Já que fomos brindados com um exemplo de GINA stub do Ferdinando, também irei disponibilizar um outro exemplo, este um pouco mais perigoso, da época de laboratório da faculdade. Se trata igualmente de uma GINA que se aproveita da implementação da GINA original, porém na hora de autenticar um usuário ela captura os dados do logon (usuário e senha) e grava em uma parte do registro acessível apenas pelo sistema (lembre-se que a GINA, por fazer parte do WinLogon, roda na conta de sistema).

> É claro que para utilizar essa GINA, você deve possuir direitos de administração, ou conhecer alguma brecha de segurança. Eu optei pela segunda opção, já que não tinha a primeira. Podemos dizer apenas que o artigo sobre falhas de segurança relacionadas a usuários avançados do Russinovich pôde resolver meu problema.

	
  * Última referência técnica
  * Documentação das interfaces
  * Guia de migração GINA => CP

