---
date: "2016-01-10"
title: "Classe, objeto, contexto"
categories: [ "draft", "code" ]
---
Para entender conceitos simples em C++, como métodos de uma classe, ajuda muito seguir o raciocínio dos programadores C e como eles lidavam com o tipo de problema que C++ resolve elegantemente implementando um novo compilador com uma nova linguagem.
Tomemos, por exemplo, métodos. Um método é uma função chamada dentro de um contexto. Qual o contexto? O objeto. Ou seja, uma instância específica de uma classe, que é um molde para se fazer alguma coisa.

```cpp
int main()
{
   MinhaClasse obj;
   obj.MeuMetodo(); // o contexto é obj, uma instância de MinhaClasse
}
```

Para obter esse contexto, existe uma palavra-chave reservada dentro dos métodos que é o __this__, que está tão incrustado na linguagem que não precisa ser usado explicitamente: quando referenciamos alguma propriedade (ou um outro método) da classe, só pelo fato de estarmos dentro de um método o compilador já entende que se trata do mesmo objeto, ou mesmo contexto.

```cpp
class MinhaClasse
{
public:
   void MeuMetodo();
   void MeuOutroMetodo();
   int MinhaPropriedade;
};

void MinhaClasse::MeuMetodo()
{
   MinhaPropriedade = 42; // ou seja: this->MinhaPropriedade = 42;
   MeuOutroMetodo(); // ou seja: this->MeuOutroMetodo();
}
```

E contexto nesse sentido nada mais é que um endereço na memória para alguma coisa que nos interessa. Tal qual uma função API do Windows -- tal qual [FindFirstFile](https://msdn.microsoft.com/en-us/library/windows/desktop/aa364418(v=vs.85).aspx) -- que recebe ou retorna uma __struct__ com o que precisamos, esse geralmente é o contexto procurado.

```cpp
WIN32_FIND_DATA findData;
HANDLE findH = FindFirstFile("*.txt", &findData);

if( findH != INVALID_HANDLE_VALUE )
{
   if( findData.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED )
   {
//...
```

![](http://i.imgur.com/l5RSlmW.context.gif)

No caso de nós, que escrevemos uma "classe", o contexto é recebido "de fora":

```cpp
HANDLE MyFindFirstFile(const char* pattern, LPWIN32_FIND_DATA findData)
{
   //...
   findData->dwFileAttributes = FILE_ATTRIBUTE_ENCRYPTED;
   //...
```

Tal como uma __struct__ que definimos, ela vira o contexto. Da mesma forma, um objeto de uma classe em C++ é esse contexto. Podemos fazer a mesma coisa em C, com o trabalho adicional de especificar o "this" (isto é, o ponteiro para o contexto/struct):

```cpp
struct MinhaClasse
{
    int MinhaPropriedade;
};

void MinhaClasse_MeuMetodo(MinhaClasse* pThis)
{
   pThis->MinhaPropriedade = 42;
   ///@todo Chamar pThis->MeuOutroMetodo();
}
```

Em um próximo post vamos ver como fazer para chamar MeuOutroMetodo a partir de uma estrutura em C.
