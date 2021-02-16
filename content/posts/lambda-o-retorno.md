---
date: "2014-04-08"
title: "Lambda: o Retorno!"
tags: [ "draft", "code" ]
---
[![Lambda: o Retorno](http://i.imgur.com/Hrbu1ue.jpg)](/images/13717451604_33225e217c_o.jpg)

Na última vez que foi abordado o tema "lambda na ferida" falamos brevemente sobre como C++ agora permite criar funções dentro de funções. Hoje vamos apenas falar que aquela construção bizarra que criamos fica ainda mais bizarra se precisarmos retornar alguma coisa dessa função ou usá-la mais de uma vez.

O padrão do lambda é supor que sua função embutida e enlatada não precisa retornar nada, o que torna a sintaxe mais simples: é um void AlgumaCoisa(argumentos). No entanto, para algoritmos como o find_if isso não funciona, então é necessário retornar algo. E, no caso de find_if, chamá-lo mais de uma vez pode ser feito facilmente criando uma variável lambda:

```cpp
#include "Common.h"
#include <algorithm>
#include <vector>
#include <string>

int main()
{
	std::vector<Employee> employees; // um bando de empregados
	std::string currentDate = GetCurrentDate();

	// definindo uma função, como quem não quer nada, dentro de uma função
	auto FindByBithDate = [&](Employee& employee)->bool // <-- tipo de retorno
	{
		return employee.birthDate == currentDate;
	};

	GetEmployees(employees);

	auto findIt = std::find_if(employees.begin(), employees.end(), FindByBithDate);

	while( findIt != employees.end() )
	{
		SendMail(*findIt);
		findIt = std::find_if(findIt + 1, employees.end(), FindByBithDate);
	}
}

```

O tipo de retorno que colocamos através de uma flechinha é obrigatória? De fato, não. Se eu omiti-la vai funcionar do mesmo jeito porque o único ponto de saída da minha função retorna um bool.

Esses compiladores estão ficando cada vez mais espertos.
