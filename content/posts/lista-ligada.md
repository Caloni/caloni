---
categories:
- code
- blog
date: '2018-04-24'
tags:
- lists
title: Lista Ligada; tá Ligado?
---

Uma lista ligada é uma lista de alguma coisa onde os elementos se ligam um no outro, ou seja, um elemento tem a referência do próximo. O tipo dos elementos de uma lista ligada pode ser inteiros, strings ou estruturas inteiras. Independente do que for, você vai precisar de uma estrutura. Sabe por quê? Porque existe além dos dados em si mais uma informação que você precisará guardar em cada elemento de sua lista: o próximo elemento. E é daí que surge a ligação da lista ligada.

    struct Node
    {
      int number;
      struct Node* next;
    };

Sua estrutura pode ser simples e direta. Digamos uma lista ligada de números vai ter o número que esse elemento armazena e o endereço para o próximo elemento. Em C guardamos o endereço de uma variável usando um ponteiro para o mesmo tipo de elemento (no caso um struct Node).

O elemento mais importante de sua lista ligada é o primeiro elemento, pois sem ele você não consegue mais voltar ao início. Isso pode ser uma variável especial que não é usada para nada exceto indicar qual o primeiro elemento da sua lista. Essa variável não pode mudar, pois precisamos sempre ter uma referência para o início da lista, a não ser que o primeiro elemento seja removido (veremos adiante). Ele pode ser simplesmente um ponteiro para o "próximo" elemento,que no caso o primeiro elemento.

  struct Node* head = NULL;

Este ponteiro começa em NULL porque a lista está vazia. Mas assim que inserirmos um item ele deixará de ser nulo.

    struct Node* node = 
      (struct Node*) malloc(
        sizeof(struct Node)
      );
  
    node->number = 10;
    node->next = NULL;
    head = node;

Pronto, agora a lista não está mais vazia e a cabeça da lista aponta para o primeiro elemento. Note que você precisa sempre inicializar o membro next com NULL, uma vez que ele é o último elemento da lista e não possui próximo.

Para inserir um novo elemento você pode inseri-lo no começo, no fim ou no meio de sua lista. No começo é o mais fácil, pois já temos o endereço do primeiro elemento.

    struct Node* node = 
      (struct Node*) malloc(
        sizeof(struct Node)
      );
  
    node->number = 10;
    node->next = next;
    head = node;

Para inserir um novo elemento no final da lista você terá que percorrê-la até achar o próximo elemento cujo membro next é igual a NULL, o que quer dizer que não há mais próximo. Nesse caso é importante saber se a lista está vazia. Se estiver basta atualizar a cabeça da lista e está pronto (como já visto).

    struct Node* lnode = head;
  
    if( ! lnode )
    {
      head = node;
    }
    else
    {
      while( lnode->next )
        lnode = lnode->next;
      lnode->next = node;
    }

Se formos sempre inserir um novo elemento no final também é interessante termos um ponteiro para o último elemento (o tail), que também pode ser um ponteiro e começa com NULL. Quando for inserido o primeiro elemento ele também será o último, então devem ser atualizados os ponteiros head e tail com o mesmo valor.

    struct Node* tail = NULL;

É preciso prestar atenção quando temos muitas variáveis com o estado de sua lista sobrando no código. Cada atualização na lista envolve atualizar todos os endereços envolvidos. Preste atenção sempre na hora que estiver escrevendo e depurando seu código ou se arrependerá por horas a fio em um fim-de-semana perdido.

Acho que remover elementos da lista ligada é a parte mais complicada, pois temos que atualizar o elemento anterior, se houver, para que o próximo dele seja o próximo do próximo.

    void del(struct Node* node)
    {
      struct Node* pnode = NULL;
      struct Node* cnode = head;
  
      while( cnode )
      {
        if( cnode == element )
          break;
        pnode = cnode;
        cnode = cnode->next;
      }
  
      if( cnode == element )
      {
        if( pnode )
        {
          pnode->next = 
            cnode->next;
        }
        else
        {
          head = 
            cnode->next;
        }
      }
    }

Para simplificar programação, depuração e análise de problemas a lista duplamente ligada, apesar de ser uma estrutura mais complexa, acaba nos dando mais controle sobre os elementos de uma lista. Mas este é assunto para próximo post.