---
categories:
- code
date: '2008-03-04'
title: Iteradores não são constantes
---

Um bug que já encontrei uma dúzia de vezes entre os novatos da STL é a utilização de iteradores como se eles não fossem mudar nunca. Porém, a verdade é bem diferente: iteradores se tornam inválidos sim, e com muito mais freqüência do que normalmente se imagina. Entre as situações em que iteradores podem mudar estão as seguintes:

 - Inserção de novo elemento no contêiner
 - Remoção de novo elemento no contêiner
 - Redimensionamento no tamanho do contêiner

Por exemplo, o tradicional código do exemplo abaixo contém o tradicional erro de iterador inválido:

    for( container::iterator it = obj.begin(); it != obj.end(); ++it )
    {
      if( it->member == 0 ) // condição para apagar elemento
      {
        obj.erase(it);  // a partir daqui it é inválido,
                        // e não adianta incrementá-lo
      }
    }

Para operações como essa, o retorno geralmente nos dá uma dica de para onde vamos na varredura do contêiner. No caso do método erase, o retorno é o próximo iterador válido, ou o final (retornado pelo método end). Um código mais esperto gera um erro mais sutil:

    for( container::iterator it = obj.begin(); it != obj.end(); ++it )
    {
      if( it->member == 0 ) // condição para apagar elemento
      {
        it = obj.erase(it); // ótimo, atualizou it. só
                            // que se ele for o final,
                            // será incrementado
      }
    }

Algo de errado irá acontecer apenas se o elemento removido for o último localizado no contêiner.

Esse é um erro comum para os acostumados com outros tipos de iteração (ex: ponteiros) e que não estudaram os princípios básicos da STL, entre eles o da reutilização de algoritmos. Se fosse usado este princípio, nada disso teria acontecido:

    struct remove_if_zero
    {
      bool operator() (ObjElement& element)
      {
        return element->member == 0;
      }
    };
    
    obj.remove_if( remove_if_zero() ); // pronto!

Quando precisamos fazer algo nos elementos de um contêiner STL, é quase certo que existirá um algoritmo genérico para essa tarefa, seja no próprio contêiner ou na forma de função (<algorithm>). Nunca se esqueça disso na hora de desenvolver seus próprios algoritmos e não precisará reinventar a roda todos os dias.