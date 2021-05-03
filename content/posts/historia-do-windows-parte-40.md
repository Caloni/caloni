---
categories:
- code
date: '2007-09-04'
title: História do Windows - parte 4.0
---

Em meio a uma febre de consumismo, no dia 24 de agosto de 1995, foi lançado a revolução no sistema gráfico da Microsoft: a interface do Windows 95. Ela foi considerada muito mais amigável que suas versões anteriores. Ainda possuía a vantagem de não necessitar mais de uma instalação prévia do DOS, passou a suportar nomes de arquivos longos, incluir suporte a TCP/IP e dial-up networking integrados. Muitas mudanças foram feitas no sistema em si, como a passagem para 32 bits (como já vimos, parcial) e o novo conceito de threads, que é o que veremos com mais detalhes neste artigo.

![Desktop do Windows 95](/img/windows_95.png)

> Bem, o "novo conceito" de threads já havia sido implementado no Windows NT desde o seu rascunho e já existia no início do projeto, mas não no velho Windows 3.1 de 16 bits, que foi a versão anterior ao 95. Parte dos requisitos do sistema foi que ele seria compatível com o NT no nível de aplicativo, o que de fato aconteceu.

Para esse milagre da multiplicação das threads acontecer a Microsoft foi obrigada a portar boa parte do código de 16 bits para 32 e entrar em modo protegido. Mesmo assim, um legado razoável do MS-DOS permaneceu debaixo dos panos suportando o novo sistema operacional através de suas interrupções e código residente. Ou seja, havia ainda partes do SO rodando em modo real.

Com o lançamento da nova versão do NT foi necessário modernizar a interface para ser compatível com o Windows 95, o que fez com que o Windows 4.0 fosse mais bonitinho. No entanto, o núcleo dos dois sistemas era completamente diferente. Enquanto um era 32 bits puro desde o primeiro int main, o outro era um sistema de compatibilidade para fornecer um Windows caseiro que fosse vendável e desse à Microsoft o retorno financeiro esperado. Deu certo por um bom tempo, até a chegada do Windows XP, que uniu as duas famílias de sistemas operacionais, pois descontinuou o Windows ME e tornou o Windows 2000 Professional mais amigável para o uso geral.

E como funciona o sistema de threads? Uma thread é uma linha de execução de código. Ser um sistema multithreading significa que ele permite que múltiplas linhas de execução de código rodem em paralelo e, dependendo do número de processadores, ao mesmo tempo.

Porém, em uma plataforma com apenas um processador, como é natural supor, apenas uma thread roda de cada vez. Para dar a impressão de rodar ao mesmo tempo o tempo de execução das threads é dividido entre elas, de forma que aparentemente todas elas rodam ao mesmo tempo. Essa unidade de divisão do tempo de execução é conhecido como quantum, ou Time Slice, e é caracterizado como o tempo em que uma thread fica rodando até que outra thread tome o seu lugar, ou seja, ocorra uma troca de contexto (switch context). Quando uma thread é criada ela ganha seu primeiro time slice (se não iniciar suspensa) e divide o tempo de processamento com outras threads que executam no mesmo processador.

![Arquitetura multithreading](/img/threads_architecture.gif)

Para exemplificar o uso de threads imagine um programa que quebra senhas por força bruta. Funciona assim: enquanto uma thread fica cuidando das mensagens da janela, como digitação e movimentação do mouse e janela, uma segunda thread irá ficar constantemente tentanto descobrir sua senha digitada por tentativa e erro. Toda vez que é alterado um caractere na senha, a thread quebradora reinicia seu trabalho.

![PwdBreaker](/img/threads_pwdbreaker.png)

Todo programa inicia com uma thread que roda seu int main. A criação de uma nova thread é feita através da chamada da função API CreateThread.

    void StartBruteForceThread()
    {
      g_bruteForceThread = CreateThread(NULL, 
        0, 
        BruteForceThread, 
        NULL, 
        0, 
        &g_bruteForceThreadId);
    }

Para quem está acompanhando [a série de artigos sobre o Windows] deve lembrar que assim como na criação de janelas, na criação de uma thread é passada uma função de callback. Só que diferente de uma função de janela, essa função não é executada na mesma thread que criou a janela, mas é um novo "int main" para uma nova linha de execução, que irá rodar em paralelo com a primeira. Essa segunda linha de execução termina quando retornamos dessa função, que no nosso exemplo é nunca, mas poderia ser quando fosse terminada sua tarefa.

![CreateThread exemplificada](/img/threads_pwdbreaker_windows.png)

Bom, acho que para explicar o uso de um sistema multithreading em um artigo só não basta. Mas para explicar por que sua senha deve ter mais de três caracteres, acho que é o bastante. Até a próxima.

[a série de artigos sobre o Windows]: /historia-do-windows