---
date: 2018-04-24T13:17:57-03:00
title: "Lista Ligada; tá ligado?"
categories: [ "code" ]
---
Uma lista ligada é uma lista de alguma coisa. Essa alguma coisa podem ser inteiros, strings ou estruturas inteiras. Independente do que for, você vai precisar de uma estrutura. Sabe por quê? Porque existe além dos dados em si mais uma informação que você precisará guardar em cada elemento de sua lista: **o próximo elemento**.

Sua estrutura pode ser simples e direta. Digamos uma lista ligada de idades vai ter o endereço do próximo elemento e o dado propriamente dito deste elemento (a idade):

```
struct Element
{
    Element* next; // proximo elemento de sua lista
    int age; // a idade de alguem
};
```

A primeira coisa que você precisa ter em sua lista é onde ela começa. Isso pode ser uma variável especial que não é usada para nada exceto indicar qual o primeiro elemento da sua lista (esse, sim, um elemento). Ele pode ser simplesmente um ponteiro para o próximo (no caso o primeiro) elemento:

![](https://i.imgur.com/PTZOB72.png)

```
Element* g_head = NULL; // este eh o inicio de tudo
```

Este ponteiro começa em NULL porque a lista está vazia. Mas assim que inserirmos um item ele deixará de ser nulo:

![](https://i.imgur.com/0I1wSXc.png)

```
Element* InsertElement(Element* next)
{
    Element* ret = new Element;
    ret->next = NULL;
    if( next != NULL )
        next->next = ret;
    return ret;
}
```

![](https://i.imgur.com/0RsyYKi.png)

A única coisa que liga um elemento ao outro é o membro next:

```
if( next != NULL )
    next->next = ret;
```

Geralmente adicionamos um novo elemento no meio de uma lista, e por isso não nos preocupamos aqui com o membro next sobrescrito (que obviamente é NULL). Porém, para um resultado mais genérico podemos verificar se ele de fato é NULL. Se não for ele se tornará o next do elemento inserido (o que quer dizer que ele não será o último!):

![](https://i.imgur.com/omD6IlR.png)

```
if( next != NULL )
{
    if( next->next != NULL )
        ret->next = next->next; // isso pode confundir a cabeca de muita gente...
    next->next = ret;
}
```

Se formos sempre inserir um novo elemento no final também é interessante termos um ponteiro para o último elemento:

```
Element* g_head = NULL; // este eh o inicio de tudo
Element* g_last = NULL; // e este eh o final
```

É preciso prestar atenção quando temos muitas variáveis sobrando no código. Caso você esteja com sua lista ligada vazia, por exemplo, g_head e g_last precisam ser atualizados!

```
if( g_head == NULL )
{
    g_head = InsertElement(NULL);
    g_last = g_head;
}
```

Se a lista não estiver vazia apenas o g_last deve ser atualizado.

```
if( g_head == NULL )
{
    g_head = InsertElement(NULL);
    g_last = g_head;
}
else
{
    Element* e = InsertElement(g_last);
    g_last = e->next;
}
```

### Removendo elementos

Remover é a parte mais complicada de uma lista ligada, pois temos que atualizar o elemento de trás (se houver):

![](https://i.imgur.com/bZajm9o.png)

```
void RemoveElement(Element* prev)
{
    Element* next = prev->next->next;
    delete prev->next;
    prev->next = next;
}
```

Não parece tão complicado. Mas imagine que para realizar esta façanha você terá que encontrar o elemento que quer apagar, mas mantendo o elemento anterior em outra variável.

Este artigo está incompleto de propósito, pois é preciso pensar antes de implementar uma solução. Para que você precisa de uma lista ligada, pra começo de conversa?
