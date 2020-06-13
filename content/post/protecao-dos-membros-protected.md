---
categories: [ "code" ]
date: "2007-10-26"
tags: [ "draft",  ]
title: "Proteção dos membros protected"
---
Quando queremos que um membro de nossa classe seja visível apenas dentro dos métodos da classe e dentro dos métodos das classes derivadas dessa classe usamos o nível de proteção protected. Isso, é claro, não quer dizer que uma classe derivada vá ter acesso aos membros protegidos de outra:

    #include <iostream>
    
    using namespace std;
    
    class Base
    {
    protected:
    	int m_protected;
    };
    
    class Derived : public Base
    {
    public:
    	int GetProtected();
    	int GetAnotherProtected();
    };
    
    class AnotherDerived : public Base
    {
    };
    
    int Derived::GetProtected()
    {
    	return m_protected; // tudo bem. sou um Derived; tenho meus direitos!
    }
    
    int Derived::GetAnotherProtected()
    {
    	AnotherDerived anotherDeriv;
    	return anotherDeriv.m_protected; // inacessível. não estamos em AnotherDerived!
    }
    
    int main()
    {
    	Derived deriv;
    
    	deriv.GetProtected();
    	deriv.GetAnotherProtected(); // isso não vai dar certo...
    } 
    

    
    Saída:
    error C2248: 'Base::m_protected' : cannot access protected member declared in class 'Base'
    see declaration of 'Base::m_protected'
    see declaration of 'Base'

Esse é o motivo fundamental do porquê não podermos fazer isso:

    // another chance
    
    int Derived::GetAnotherProtected()
    {
    	Base base; // somos derivados dessa base, não somos?
    	return base.m_protected; // mas não é por isso que vamos acessar um membro protegido de boa.
    } 
    

Ao acessar membros protegidos é importante o tipo da expressão que está do lado esquerdo do "." ou "->". Afinal, o nível de proteção se baseia no escopo, e as classes são um escopo. É por isso que consigo acessar os membros protegidos de um outro objeto de minha classe, mesmo sendo outro objeto:

    // dentro da lei
    
    int Derived::GetAnotherProtected()
    {
    	Derived deriv; // meu irmão: typeid(deriv) == typeid(*this).
    	return deriv.m_protected; // mesmo tipo do escopo: meus direitos são preservados
    } 
    

A definição do escopo é tudo o que o compilador dispõe para saber se acessa ou não acessa um membro. Podemos ter acesso a mprotected enquanto somos do tipo Derived, mas não quando o mesmo objeto é usado como Base:

    // fora-da-lei
    
    int Derived::GetAnotherProtected()
    {
    	Base& base = *this; // os genes da minha mãe.
    	return base.m_protected; // eu não me acesso! tipo o subconsciente...
    } 
    

Essa proteção parece desnecessária - e até mesmo incoerente - quando lidamos com o mesmo objeto que acessa. Afinal, somos nós mesmos! Só que o compilador não sabe disso, e ele deve desconfiar de tudo e de todos para evitar esse tipo de "ataque":

    // espertinho, hein?
    
    int Derived::GetAnotherProtected()
    {
    	AnotherDerived anotherDeriv; // não acesso os protegidos desse aqui...
    	Base& base = anotherDeriv; // mas quem sabe se eu acessar os genes da minha mãe?
    	return base.m_protected; // nada feito =(. Também, se nem eu mesmo consegui me acessar...
    } 
    

Agora a proteção do compilador faz sentido. Parece um detalhe frívolo, mas depois que vi alguns programadores de respeito se debatendo pela "burrice" do compilador, imaginei que talvez houvesse mais pessoas com a mesma dúvida de se existe ou não um "bug na linguagem".
