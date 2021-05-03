---
categories:
- code
date: '2007-11-07'
title: 'Ponteiro de método: qual this é usado?'
---

Depois de publicado o artigo anterior sobre ponteiros de métodos surgiu uma dúvida muito pertinente do autor do blogue [CodeBehind](http://codebehind.wordpress.com/), um escovador de bits disfarçado de programador .NET: qual objeto que vale na hora de chamar um método pelo ponteiro?

Isso me estimulou a desdobrar um pouco mais os mistérios por trás dos ponteiro de métodos e de membros, e descobrir os detalhes mais ocultos desse lado esotérico da linguagem.

Para entender por inteiro o que acontece quando uma chamada ou acesso utilizando ponteiros dependentes de escopo, algumas pequenas mudanças foram feitas na nossa pequena classe Rand.

    #include <iostream>
    #include <time.h>
    
    class Rand;
    typedef void (Rand::*FP)();
    typedef int Rand::*MP;
    
    class Rand
    {
    public:
      Rand()
      {
        m_num = rand() % 100;
      }
    
      int m_num;
    
      void Print()
      {
        std::cout << "this: " 
          << std::hex << this 
          << ", member: " 
          << std::dec << m_num
          << std::endl;
      }
    };
    
    /** No princípio Deus disse: 
        'int main!'
    */
    int main()
    {
      srand(time(NULL));
    
      Rand r1, r2, r3;
      FP fp = &Rand::Print;
      MP mp = &Rand::m_num;
    
      (r1.*fp)();
      (r2.*fp)();
      (r3.*fp)();
    
      std::cout << std::endl;
      
      std::cout << "this: " 
        << std::hex << &r1 
        << ", member: " 
        << std::dec << r1.*mp 
        << std::endl;
    
      std::cout << "this: " 
        << std::hex << &r2 
        << ", member: " 
        << std::dec << r2.*mp 
        << std::endl;
    
      std::cout << "this: " 
        << std::hex << &r3 
        << ", member: " 
        << std::dec << r3.*mp 
        << std::endl;
    } 

O novo código chama através do mesmo ponteiro o mesmo método (duh), mas através de três objetos diferentes. Se observarmos a saída veremos que cada instância da classe guardou um inteiro aleatório diferente para si:

    this: 0012FF6C, member: 97
    this: 0012FF5C, member: 5
    this: 0012FF60, member: 44
    
    this: 0012FF6C, member: 97
    this: 0012FF5C, member: 5
    this: 0012FF60, member: 44

Cada compilador e plataforma tem a liberdade de implementar o padrão C++ da maneira que quiser, mas o conceito no final acaba ficando quase a mesma coisa. No caso de ponteiros de métodos, o ponteiro guarda realmente o endereço da função que pertence à classe. Porém, como todo método não-estático em C++, para chamá-lo é necessário possuir um this, ou seja, o ponteiro para a instância:

![Ponteiros de método](/img/fuzzycall.gif)

Em assembly teremos algo assim:

    ; FP fp = &Rand::Print;
    lea rax,[Rand::Print]  
    mov qword ptr [fp],rax

    ; (r1.*fp)();
    lea rcx,[r1]  
    call qword ptr [fp]  

    ; (r2.*fp)();
    lea rcx,[r2]  
    call qword ptr [fp]  

    ; (r3.*fp)();
    lea rcx,[r3]  
    call qword ptr [fp]  

Além do ponteiro de métodos, também é possível no C++ apontar para membros de um dado objeto como foi feito no exemplo acima. Para tanto, como vimos no código, basta declarar um tipo de ponteiro de membro de acordo com o tipo desejado com o escopo da classe: typedef int Rand::*MP. Nesse caso, a técnica de usar o próprio enderenço não funciona, já que cada objeto possui um membro próprio em um lugar de memória próprio. Porém, assim como os ponteiros de métodos, os ponteiros de membros exigem um objeto para serem acessados, o que já nos dá a dica de onde o objeto começa. Sabendo onde ele começa, fica fácil saber onde fica o membro através do seu offset, ou seja, a distância dele a partir do início da memória do objeto. O código abaixo simplifica a obtenção de um objeto dentro da classe usando ponteiro para membros:

    MP mp = &Rand::m_num;
    int i1 = r1.*mp;
    int i2 = r2.*mp;
    int i3 = r3.*mp;

Note no assembly gerado que para isso funcionar o código precisa do offset armazenado em algum lugar. E, nada mais óbvio, o "ponteiro" de um membro de uma classe nada mais é que o offset deste membro dentro desta classe.

    ; MP mp = &Rand::m_num;
    mov dword ptr [mp],0
    
    ; int i1 = r1.*mp;
    movsxd rax,dword ptr [mp] 
    mov eax,dword ptr r1[rax] 
    mov dword ptr [i1],eax 
    
    ; int i2 = r2.*mp;
    movsxd rax,dword ptr [mp] 
    mov eax,dword ptr r2[rax] 
    mov dword ptr [i2],eax 
    
    ; int i3 = r3.*mp;
    movsxd rax,dword ptr [mp] 
    mov eax,dword ptr r3[rax] 
    mov dword ptr [i3],eax

Como podemos ver, não é nenhuma magia negra a responsável por fazer os ponteiros de métodos e de membros funcionarem em C++. Porém, eles não são ponteiros ordinário que costumamos misturar a torto e a direito. Essa distinção na linguagem é importante para manter o código "minimamente sadio".