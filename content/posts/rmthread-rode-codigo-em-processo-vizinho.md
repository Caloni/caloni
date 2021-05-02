---
date: "2008-01-28"
title: "RmThread: rode código em processo vizinho"
categories: [ "code" ]
---
Aproveitando que utilizei a mesma técnica semana passada para desenvolver um vírus para Ethical Hacking, republico aqui este [artigo que já está mofando no Code Projet], mas que espero que sirva de ajuda pra muita gente que gosta de fuçar nos internals do sistema. Boa leitura!

RmThread é um projeto que fiz baseado em uma das três idéias do artigo de Robert Kuster em "Three Ways to Inject Your Code into Another Process". No entanto, não utilizei código algum. Queria aprender sobre isso, pesquisei pela internet, e me influenciei pela técnica CreateRemoteThread com LoadLibrary. O resto foi uma mistura de "chamada de funções certas" e MSDN.

O projeto que fiz é útil para quem precisa rodar algum código em um processo vizinho, mas não quer se preocupar em desenvolver a técnica para fazer isso. Quer apenas escrever o código que vai ser executado remotamente. O projeto de demonstração, RmThread.exe, funciona exatamente como a técnica citada anteriormente. Você diz qual o processo a ser executado e a DLL a ser carregada, e ele inicia o processo e carrega a DLL em seu contexto. O resto fica por conta do código que está na DLL.

Para fazer a DLL, existe um projeto de demonstração que se utiliza de uma técnica que descobri para fazer rodar algum código a partir da execução de DllMain sem ficar escravo de suas limitações (você só pode chamar com segurança funções localizadas na kernel32.dll).

Existem três funções que poderão ser utilizadas pelo seu programa:

    /** Run process and get rights for running remote threads. */
    HANDLE CreateAndGetProcessGodHandle(LPCTSTR lpApplicationName, LPTSTR lpCommandLine);
    
    /** Load DLL in another process. */
    HMODULE RemoteLoadLibrary(HANDLE hProcess, LPCTSTR lpFileName);
    
    /** Free DLL in another process. */
    BOOL RemoteFreeLibrary(HANDLE hProcess, HMODULE hModule); 

Eis a rotina principal simplificada demonstrando como é simples a utilização das funções:

    //...
    // Start process and get handle with powers.
    hProc = CreateAndGetProcessGodHandle(tzProgPath, tzProgArgs);
    
    if( hProc != NULL )
    {
      // Load DLL in the create process context.
      HMODULE hDll = RemoteLoadLibrary(hProc, tzDllPath);
    
      if( hDll != NULL )
        RemoteFreeLibrary(hProc, hDll);
    
      CloseHandle(hProc);
    }
    //... 

A parte mais complicada talvez seja o que fazer quando a sua DLL é carregada. Considerando que ao ser chamada em seu ponto de entrada, o código da DLL possui algumas limitações (uma já citada; para mais, vide a ajuda de DllMain no MSDN), fiz uma "execução alternativa", criando uma thread na função DllMain:

    BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
    {
      switch( ul_reason_for_call )
      {
        case DLL_PROCESS_ATTACH:
        {
          DWORD dwThrId;
    
          // Fill global variable with handle copy of this thread.
    
          BOOL bRes =
          DuplicateHandle(GetCurrentProcess(),
            GetCurrentThread(),
            GetCurrentProcess(),
            g_hThrDllMain,
            0,
            FALSE,
            0);
    
          if( bRes == FALSE )
            break;
    
          // Call function that do the useful stuff with its DLL handle.
          CloseHandle(CreateThread(NULL,
            0,
            RmThread,
            (LPVOID) LoadLibrary(g_tzModuleName),
            0,
            dwThrId));
            }
          break;
          //... 

A função da thread, por sua vez, é esperar pela finalização da thread DllMain (temos o handle dessa thread armazenado em g_hThrDllMain), fazer o que tem que fazer, e retornar, liberando ao mesmo tempo o handle da DLL criado para si:

    /**
    * Sample function, called remotely for RmThread.exe.
    */
    DWORD WINAPI RmThread(LPVOID lpParameter)
    {
      HMODULE hDll = (HMODULE) lpParameter;
      LPCTSTR ptzMsg = _T("Congratulations! You called RmThread.dll successfully!");
    
      // Wait DllMain termination.
      WaitForSingleObject(g_hThrDllMain, INFINITE);
    
      //TODO: Put your remote code here.
      MessageBox(NULL,
        ptzMsg,
        g_tzModuleName,
        MB_OK : MB_ICONINFORMATION);
    
      // Do what the function name says.
      FreeLibraryAndExitThread(hDll, 0);
    } 

A marca TODO é aonde seu código deve ser colocado (você pode tirar o MessageBox, se quiser). Como DllMain já foi previamente executada, essa parte do código está livre para fazer o que quiser no contexto do processo vizinho.

Um detalhe interessante é que é necessária a chamada de FreeLibraryAndExitThread. Do contrário, após chamar FreeLibrary, o código a ser executado depois (um simples return) estaria em um endereço de memória inválido, já que a DLL não está mais carregada. O resultado não seria muito agradável.

Um problema chato (que você poderá encontrar) é que, se a DLL não for carregada com sucesso, não há uma maneira trivial de obter o código de erro da chamada de LoadLibrary. Uma vez que a thread inicia e termina nessa função API, o LastError se perde. Alguma idéia?

[artigo que já está mofando no Code Projet]: http://www.codeproject.com/KB/threads/RmThread.aspx
