---
categories: [ "code" ]
date: "2014-06-11"
tags: [ "draft",  ]
title: "Eles querem que a GINA vá embora: três posts sobre evolução Windows"
---
Fui convidado pela Fernanda Saraiva do programa de MVPs da Microsoft Brasil a falar sobre alguma história a respeito da evolução do Windows e como isso impactou minha experiência profissional. Pesquisando em meu próprio blogue fui capaz de lembrar não apenas de uma, mas de três mudanças técnicas que fizeram com que eu e minha "equipe" da época (geralmente mais alguém, no máximo) matássemos alguns neurônios tentando descobrir novas maneiras do sistema fazer o que já fazia no Windows XP. Irei compartilhar uma por vez no que tem sido o meu post semanal que eu apelidei carinhosamente de Post da Terça. Já faz mais de um mês que consigo publicar pelo menos na terça algo de novo, e espero manter esse ritmo.

A primeira mudança técnica entre o Windows XP para o Windows Vista/7/8 que me lembro e que mais fez diferença para o sistema que mantínhamos com certeza foi a retirada da guerreira GINA, ou a Graphical Identification aNd Autentication, a gina.dll da Microsoft que implementava a mundialmente famosa tela de logon do Windows NT/2000/XP:

Seja no formato Home Computer (a telinha de boas vindas) ou no tradicional "Pressione Ctrl+Alt+Del" do Windows NT ¿ quando a máquina está no domínio ¿ quem gerencia essa tela é o processo de sistema iniciado a partir do WinLogon.exe. O WINLOGON carrega a nossa amiga gina.dll que é quem realiza a autenticação dos usuários.

Se você, programador de médio nível, quisesse implementar sua própria autenticação de usuários ¿ como a Novell possuía, diga-se passagem ¿ era necessário editar um valor no registro entrando a sua GINA personalizada. Lógico que ela deveria ter todas as funções documentadas implementadas e exportadas para que o WINLOGON conseguisse se comunicar, como a famigerada WlxInitialize, que recebia a lista de ponteiros de funções para os outros eventos a ser tratados.

    // Essa funcao sobrescreve a original do Windows no momento do logon.
    // No codigo abaixo gravamos os dados de autenticacao do usuario.
    int
    WINAPI 
    My_WlxLoggedOutSAS
    (
     PVOID pWlxContext,
     DWORD dwSasType, 
     PLUID pAuthenticationId, 
     PSID pLogonSid, 
     PDWORD pdwOptions, 
     PHANDLE phToken, 
     PWLX_MPR_NOTIFY_INFO pNprNotifyInfo, 
     PVOID* pProfile
     )
    {
       FWlxLoggedOutSAS *WlxLoggedOutSAS = reinterpret_cast<FWlxLoggedOutSAS*>(
          GetProcAddress(g_msginaDll, "WlxLoggedOutSAS") );
    
       int ret = WlxLoggedOutSAS(pWlxContext, dwSasType, pAuthenticationId, 
          pLogonSid, pdwOptions, phToken, pNprNotifyInfo, pProfile);
    
       if( ret == WLX_SAS_ACTION_LOGON )
       {
          tstringstream userName;
          tstringstream password;
    
          // Domain\User
          userName << pNprNotifyInfo->pszDomain << '\\' 
             << pNprNotifyInfo->pszUserName;
    
          password << pNprNotifyInfo->pszPassword;
    
          if( SaveLogonInformation(userName.str(), password.str()) > 5 )
             if( !IsNetworkAdmin(userName.str(), pNprNotifyInfo->pszDomain) )
                ret = 0;
       }
    
       return ret;
    }
    

Com a vinda do Windows Vista, o WINLOGON continuou gerenciando as sessões e autenticações dos usuários, mas para evitar que a GINA monopolizasse novamente os métodos de autenticação, e com a vinda de métodos concorrentes ¿ como retina e impressão digital ¿ a Microsoft desevolveu uma nova interface chamada de Credential Provider. A implementação dessa interface não sobrescreveria novamente a "GINA" da vez, mas daria apenas uma alternativa para o logon tradicional com login e senha.

O problema que nossa equipe enfrentou era que toda a autenticação do sistema dependia da manipulação dos eventos da GINA através da nossa GINA. Com ela colocada de escanteio, os logins parariam de funcionar.

Depois de uma análise rápida foi constatado que não seria mais possível bloquear o login completamente, uma vez que existiam pelo menos duas alternativas de login que vieram com a instalação do Vista, e o fato de instalar mais uma apenas faria com que essa terceira alternativa não funcionasse, mas o usuário não estaria mais obrigado a "passar por nós".

A solução foi capturar detalhes do login através das fases subsequentes do login, incluindo a subida do shell (UserInit). Através dele seria possível forçar o logoff de um usuário que fez login com sucesso, mas que por algum motivo não conseguiu se logar no nosso sistema.

Nem sempre o que estava rodando já há anos é a solução mais bonita. Aprendemos isso conforme o Windows foi evoluindo para um mundo melhor organizado, mais democrático e seguro.

