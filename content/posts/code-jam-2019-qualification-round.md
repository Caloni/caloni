---
categories:
- draft
- blog
date: 2019-04-07 15:00:26-03:00
desc: Como fiz os dois primeiros exercídios do início do Code Jam
title: Code Jam 2019 Qualification Round
---

Estou viajando e com poucas horas de acesso a um computador, mas os dois primeiros desafios do Code Jam esse ano foram tão simples que sequer precisaram de meia-hora. Isso para um chinês, campeões em campeonatos de programação, deve ser equivalente a cinco minutos com um código C enxuto. Mas estou apenas aprendendo.

## Foreground Solution

**Resuminho**: o problema é receber um número e retornar dois números cuja soma seja igual ao primeiro. A única restrição é que nesses números não poderá ter o algarismo quatro.

**Solução**: copiar como string o número para o primeiro deles e colocar zero no segundo; sempre que houver a incidência do caractere '4' trocar por '3' no primeiro número e '1' no segundo (ou a soma que lhe convier).

```c++
#include <iostream>
#include <string>

using namespace std;

void calc(string& N, string& A, string& B)
{
  for( size_t i = 0; i < N.size(); ++ i)
  {
    if( N[i] == '4' )
    {
      A.push_back('3');
      B.push_back('1');
    }
    else
    {
      A.push_back(N[i]);
      B.push_back('0');
    }
  }
}

int main()
{
  int T;
  cin >> T;
  for( int i = 0; i < T; ++ i)
  {
    string N;
    cin >> N;
    string A, B;
    calc(N, A, B);
    cout << "Case #" << i+1 << ": " << stoi(A) << " " << stoi(B) << endl;
  }   
}
```

## You can go your own way

**Resuminho**: tem que atravessar um labirinto formado por quadrados de N x N começando acima à esquerda saindo abaixo na direita. Enviar uma string com os comandos E ou S (East/South) para sair do labirinto. A pegadinha é não repetir nenhum dos comandos de uma garota que resolveu o labirinto antes.

**Solução**: essa pegadinha é o que ironicamente resolve o problema, pois basta inverter os comandos S e E da string recebida como o caminho da garota e ele nunca se repete e sai do mesmo jeito, pois é o labirinto mais fácil do mundo.

```c++
#include <iostream>
#include <string>

using namespace std;

void calc(string& P)
{
  for( size_t i = 0; i < P.size(); ++ i)
  {
      P[i] = P[i] == 'S' ? 'E' : 'S';
  }
}

int main()
{
  int T;
  cin >> T;
  for( int i = 0; i < T; ++ i)
  {
    string N, P;
    cin >> N >> P;
    calc(P);
    cout << "Case #" << i+1 << ": " << P << endl;
  }   
}
```

## Cryptopangrams (failed)

**Resuminho**: encontrar quais números primos são usados como letras do alfabeto baseado em uma sequência em que o primeiro número é a multiplicação do primo da primeira letra pela segunda, o segundo número é a multiplicação da segunda pela terceira e assim por diante.

**Solução**: tentei fazer na força bruta criando o dicionário de primos usado procurando o resto zero das divisões dos números e depois já com o alfabeto montado reproduzir as reproduções. Apesar do sample funcionar devo ter perdido pelo tempo ou um erro que não descobri.

```c++
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void calc(int N, vector<int>&LS, string& LSS)
{
    map<int, char> alpha;
    int first1 = 0, first2 = 0;

    for( int l: LS )
    {
        int na = 0;

        for( auto a: alpha)
        {
            if( l % a.first == 0 )
            {
                na = l / a.first;
                break;
            }
        }

        if( na )
        {
            alpha[na] = ' ';
            continue;
        }

        for( size_t i = 2; i < N; ++i )
        {
            if( l % i == 0 )
            {
                int na1 = l / i;
                int na2 = i;
                if( first1 == 0 )
                {
                    first1 = na1;
                    first2 = na2;
                }
                alpha[na1] = ' ';
                alpha[na2] = ' ';
                break;
            }
        }
    }

    const char Alphabet[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 
    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 
    'W', 'X', 'Y', 'Z' };

    size_t pos = 0;
    for( auto& a: alpha )
        a.second = Alphabet[pos++];

    int first = LS[1] % first1 == 0 ? first2 : first1;
    LSS.push_back(alpha[first]);

    for( int i: LS )
    {
        int second = i / first;
        char c = alpha[second];
        LSS.push_back(c);
        first = second;
    }
}

int main()
{
    int T;
    cin >> T;
    for( int i = 0; i < T; ++i)
    {
        vector<int> LS;
        int N, L;
        cin >> N >> L;
        int l;
        for( int n = 0; n < L; ++ n)
        {
            cin >> l;
            LS.push_back(l);
        }
        string LSS;
        calc(N, LS, LSS);
        cout << "Case #" << i+1 << ": " << LSS << endl;
    }
}   
```

## Dat Bae

**Resuminho**: descobrir quais bits não estão sendo retornados em um echo (ex: manda-se '1010' e recebe '010') com um limite de envios para o servidor (este é um problema interativo).

**Solução**: imaginei dividir o envio pelo número de blocos defeituosos para alternar os 0s e 1s e assim ir dividindo pela metade de acordo com as respostas até ter as posições que não estão retornando. Não cheguei a terminar o código, mas a ideia geral era que como o limite de blocos defeituosos era de 15 ou N-1 (N é o número de bits) e o máximo de chutes é 5, imaginei que a divisão de 2 elevado a 5 fosse o limite da solução.