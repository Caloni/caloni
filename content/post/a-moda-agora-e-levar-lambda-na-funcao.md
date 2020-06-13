---
categories: [ "code" ]
date: "2014-03-28"
tags: [ "draft",  ]
title: "A moda agora é levar lambda na função"
---

A nova moda de programar C++ nos últimos anos com certeza é usar lambda. Mas, afinal, o que é lambda? Bom, pra começar, é um nome muito feio.

O que esse nome quer dizer basicamente é que agora é possível criar função dentro de função. Não só isso, mas passar funções inteiras, com protótipo, corpo e retorno, como parâmetro de função.

Isso significa que finalmente os algoritmo da STL vão ser úteis e não um "pain in the ass".

Por exemplo, antes, tínhamos que fazer o seguinte malabarismo para mexer com arrays/vetores/listas:

    #include "Common.h"
    #include <algorithm>
    #include <vector>
    #include <string>
    
    void NewYearMail(Employee& employee)
    {
    	// isso só tem duas linhas, mas poderia ter... 10!
    	employee.age += 1;
    	SendMail(employee);
    }
    
    int main()
    {
    	std::vector<Employee> employees; // um bando de empregados
    	GetAnniversaryEmployees(employees);
    	std::for_each(employees.begin(), employees.end(), NewYearMail);
    }
    

Imagine que para cada interação devíamos criar uma função que manipulasse os elementos do vetor.

Uma alternativa que costumava utilizar era a de roubar na brincadeira e criar um tipo dentro da função (permitido) e dentro desse tipo criar uma função (permitido):

    #include "Common.h"
    #include <algorithm>
    #include <vector>
    #include <string>
    
    int main()
    {
    	struct NewYearMail { void operator()(Employee& employee)
    	{
    		employee.age += 1;
    		SendMail(employee);
    	}}; // note o final com chaves-duplas, fechando a função e a struct
    
    	std::vector<Employee> employees; // um bando de empregados
    	GetAnniversaryEmployees(employees);
    	std::for_each(employees.begin(), employees.end(), NewYearMail());
    }
    

Apesar disso gerar INTERNALCOMPILERERROR em muitos builds com o Visual Studio 2003 (e o rápido, mas anos noventa, Visual Studio 6) na maioria das vezes o código compilava e rodava sem problemas. No entanto, deixava um rastro sutil de gambi no ar...

Agora isso não é mais necessário. Desde o Visual Studio 2010 (que eu uso) a Microsoft tem trabalhado essas novidades do padrão no compilador, e aos poucos podemos nos sentir mais confortáveis em usar essas modernices sem medo. Por exemplo:

    #include "Common.h"
    #include <algorithm>
    #include <vector>
    #include <string>
    
    int main()
    {
    	std::vector<Employee> employees; // um bando de empregados
    	GetAnniversaryEmployees(employees);
    
    	std::for_each(employees.begin(), employees.end(), &
    	{
    		employee.age += 1;
    		SendMail(employee);
    	}); // note o final com chave e parêntese, fechando a função e a chamada do for_each
    }
    

"Caraca, mas o que é esse código alienígena?", diria alguém como eu alguns anos atrás (talvez até meses). Bom, nada vem de graça em C++ e dessa vez houve algumas mudanças meio drásticas na sintaxe para acomodar o uso dessa lambida inline.

    #include <algorithm>
    #include <iostream>
    
    int main()
    {
    	int arrayDeInts[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    
    	std::for_each( // estou chamando uma função aqui
    		&arrayDeInts[0], &arrayDeInts[10], // começo e final (begin e end para STL)
    		[&] // opa! sintaxe nova. os [] dizem que começa uma função lambida e 
    			//o & diz que posso acessar todo mundo
    
    		(int umInt) // depois dos []s vem o formato de recebimento de parâmetros de uma função
    			// (no caso, como é um array de ints, o parâmetro para o for_each tem que ser um int)
    
    		{ // iniciamos a função dentro da chamada do for_each
    
    			std::cout << umInt << ' '; // podemos acessar umInt, arrayDeInts 
    			// e qualquer variável da função ou objeto (se fosse um objeto)
    
    		} // finalizamos a função dentro da chamada do for_each
    
    	); // e precisamos fechar a chamada do for_each depois dessa suruba toda
    
    }

E não é só isso. Tem muito mais esquisitices de onde veio essa.
