---
date: "2007-09-04"
title: História do Windows - parte 4.0
categories: [ "code" ]
---
**Windows 95**

Em meio a uma febre de consumismo, no dia 24 de agosto de 1995, foi lançado a revolução no sistema gráfico da Microsoft: a interface do Windows 95. Ela foi considerada muito mais amigável que suas versões anteriores. Ainda possuía a vantagem de não necessitar mais de uma instalação prévia do DOS, passou a suportar nomes de arquivos longos, incluir suporte a TCP/IP e _dial-up networking_ integrados. Muitas mudanças foram feitas no sistema em si, como a passagem para 32 bits (como já vimos, parcial) e o novo conceito de _threads_, que é o que veremos com mais detalhes nesse artigo.

Windows 95

> _Bem, o "novo conceito" de __threads já havia sido implementado no Windows NT desde o "scratch". O conceito já existia no início do projeto, mas não no velho Windows 3. 1 de 16 bits, que foi a versão anterior ao 95. Parte dos requisitos do sistema foi que ele seria compatível com o NT no nível de aplicativo, o que de fato aconteceu. _

Para esse milagre da multiplicação das _threads_ acontecer a Microsoft foi obrigada a portar boa parte do código de 16 bits para 32 e entrar em modo protegido. Mesmo assim, um legado razoável do MS-DOS permaneceu debaixo dos panos, suportando o novo sistema operacional através de suas interrupções e código residente.

Com o lançamento da nova versão do NT, foi necessário modernizar a interface para ser compatível com o Windows 95, o que fez com que o Windows 4.0 fosse mais bonitinho. No entanto, o núcleo dos dois sistemas era completamente diferente. Enquanto um era 32 bits puro desde o primeiro int main, o outro era um sistema de compatibilidade para fornecer um Windows caseiro que fosse vendável e desse à Microsoft o retorno financeiro esperado. Deu certo por um bom tempo, até a chegada do Windows XP, que uniu as duas famílias de sistemas operacionais, pois descontinuou o Windows ME e tornou o Windows 2000 Professional mais amigável para o uso geral.

#### Como funciona o sistema de threads

Uma _thread_ é uma linha de execução de código. Ser um sistema _multithreading_ significa que ele permite que múltiplas linhas de execução de código rodem em paralelo e, dependendo do número de processadores, ao mesmo tempo.

Em uma plataforma com apenas um processador, como é natural supor, apenas uma _thread_ roda de cada vez. Contudo, o tempo de execução das _threads_ é dividido entre elas, de forma que **aparentemente** todas elas rodam ao mesmo tempo. Essa unidade de divisão do tempo de execução é conhecido como _Quantum_, ou _Time Slice._

Threads

Como podemos ver, quando uma _thread_ é criada ela ganha seu primeiro _time slice_ (se não iniciar suspensa) e divide o tempo de processamento com outras _threads_ que executam no mesmo processador.

#### Mãos ao código

Para exemplificar o uso de _threads_, resolvi fazer um programa que pode nos ser útil no futuro. Se trata de um quebrador de senhas por força bruta. Isso quer dizer que enquanto uma _thread_ fica cuidando das mensagens da janela, como digitação e movimentação, uma segunda _thread_ irá ficar constantemente tentanto descobrir sua senha digitada por tentativa e erro. Toda vez que é alterado um caractere na senha, a _thread_ quebradora reinicia seu trabalho.

PwdBreaker screenshot

Você pode baixar o código fonte, que não é muito complicado, aqui.

, que nada mais é que uma janela modal, como a mostrada pelo [MessageBox (ou até a [System.Windows.Forms.MessageBox. Para isso é necessário desenhar uma janela através de um arquivo de _resource_, com a extensão rc. Porém, podemos ver que não é difícil entender como um arquivo de _resources_ funciona:

Dialog Box no RC

Também não deve ser muita surpresa saber que uma caixa de diálogo também possui sua função de janela, que é praticamente idêntica a do CreateWindow. A diferença está mais no tratamento das mensagens.

```cpp
INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, 
							WPARAM wParam, LPARAM lParam)
{
	INT_PTR ret = TRUE;

	switch( uMsg )
	{
	case WM_INITDIALOG:
		g_singleDialogHandle = hwndDlg;
		StartBruteForceThread();
		break;
	case WM_COMMAND:
		if( LOWORD(wParam) == IDC_EDIT1 && HIWORD(wParam) == EN_CHANGE )
		{
			TCHAR pwd[MAX_PATH];

			if( GetDlgItemText(hwndDlg, IDC_EDIT1, 
				pwd, SIZEOF_ARRAY(pwd)) )
			{
				lstrcpy(g_currentPassword, pwd);
				g_currentPasswordSize = lstrlen(pwd);

				RestartBruteForceThread();
			}
		}
		break;
	case WM_CLOSE:
		EndDialog(hwndDlg, TRUE);
		break;
	default:
		ret = FALSE;
	}

	return ret;
} 

```

A surpresa maior deve ficar por conta da nova _thread_, que é criada através da função da API CreateThread:

```cpp
void StartBruteForceThread()
{
	g_bruteForceContinue = TRUE;
	g_bruteForceThread = CreateThread(NULL, 0, BruteForceThread, NULL, 
		0, &g_bruteForceThreadId);
} 

```

Assim como na criação de janelas, é passada uma função de _callback_. Só que diferente de uma função de janela, essa função não é executada na mesma _thread_ que criou a janela, mas é um novo "int main" para uma nova linha de execução, que irá rodar em paralelo com a primeira. Essa segunda linha de execução termina quando retornamos dessa função, que no nosso exemplo é nunca, mas poderia ser quando fosse terminada sua tarefa.

CreateThread exemplificada

Depois que uma _thread_ termina, existem maneiras das outras _threads _ficarem sabendo e até obterem seu código de retorno. Isso pode ser feito utilizando-se o _handle_ retornado pela função CreateThread, uma duplicação desse mesmo _handle_ ou até a obtenção de um novo _handle_ através do identificador da _thread, _o _Thread Id_ (TID).

```cpp
DWORD WINAPI ThreadProc(PVOID param)
{
	// Executing in a new thread...
	return ERROR_SUCCESS; // Exiting the function, finalizing the thread.
} 

```

Bom, acho que para explicar o uso de um sistema _multithreading_ em um artigo só não basta. Mas para explicar por que sua senha deve ter mais de três caracteres, acho que é o bastante. Até a próxima.

```cpp
while( g_bruteForceContinue )
{
	if( lstrcmp(currentPassword, breakPassword) != 0 )
	{
		IncrementPassword(breakPassword, 
			SIZEOF_ARRAY(breakPassword) - 1);
	}

	SetDlgItemText(g_singleDialogHandle, IDC_EDIT2, breakPassword);
} 

```

#### Para saber mais

    
  * Outros artigos sobre a história do windows

    
  * Windows 95: quinze anos de grandes feitos e telas azuis

