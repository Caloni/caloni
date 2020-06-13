---
categories: [ "code" ]
date: "2018-01-25"
tags: [ "draft", "ccpp", "debug" ]
title: "Como Achar Erros no Printf via Dump"
---
Às vezes, e apenas às vezes, é útil ter um dump do processo que acabou de capotar e ter um singelo backup do pdb (arquivo de símbolos) dos binários envolvidos nessa tragédia. Com alguns cliques pontuais e uma análise simples da stack, da variável e do código envolvido é possível chegar em um veredito sem muitas controversas se foi isso mesmo que gerou o crash. No caso peguei hoje um caso assim.

Abrir um dump (dmp) pode ser feito pelo Visual Studio, Windbg ou sua ferramenta de análise favorita. Mais importante que isso é carregar seus símbolos adequadamente. Com o dump e símbolos abertos é possível analisar a stack de chamadas, o que nos revela que há um problema em uma função de Log. Como se trata de uma versão release não há muita informação da pilha, que pode fazer parte de uma stack modificada (otimização de código). Portanto, tudo que vier é lucro. Como variáveis.

    void Log(const char* szForma, ...)
    {
      code code code
      code code code
      code code code
      code code code
    ->code code code
      code code code
    }
    
    stack:
    
    msvcr100.dll!xxx
    msvcr100.dll!xxx
    msvcr100.dll!xxx
    module.dll!InternalLog(...)
    module.dll!Log(...)
    module.dll!ThreadStart(...)
    kernel32!xxx

Demos sorte e é possível ver o que tem na variável de format, a mais importante de uma função de log estilo printf, pois geralmente é ela a responsável pelas dores de cabeça infernais.

    windbg:
    
    >da szFormat
    "Connected to server; connecting to queue %s"

Através dessa string é possível buscar no código usando grep, vim ou até o Visual Studio. Com isso reduzimos nosso escopo de busca ao mínimo.

    220     Log("Connection Failed");
    220     break;
    220   }
    220 }
    220 else Log("Connected to server; connecting to queue %s");
    220                                                       ^
    220                                                       |

E voilà! Temos uma chamada de log que teoricamente teria que passar uma string C, mas não passa nada. Isso quer dizer que a função de printf irá procurar na pilha pelo endereço de uma string, mas irá encontrar um endereço aleatório. Lendo esse endereço, que tem ótimas chances de ser inválido, ele irá capotar. Para dores de cabeças mais intensas, ele irá capotar aleatoriamente (ou na máquina do chefe, o mais provável).

E assim terminamos mais uma sessão simples e rápida de debug. Quer dizer, simples e rápida para quem tem 20 anos de experiência nessas coisas. Os estagiários devem ter ficado de cabelos em pé.
