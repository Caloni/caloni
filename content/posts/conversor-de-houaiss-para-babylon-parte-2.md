---
date: "2008-04-08"
title: "Conversor de Houaiss para Babylon - parte 2"
tags: [ "code" ]
---
Após algumas semanas de suspense, chegamos finalmente à nossa segunda e última parte da saga do dicionário Houaiss.

Como devem [estar lembrados], a primeira parte se dispôs a desmontar a ofuscação usada nos arquivos do dicionário para permitir nossa posterior análise, com o simples e justo objetivo de importá-lo para o Babylon, cujas funcionalidades de busca são bem superiores.

Feito isso, agora nos resta entender a estrutura interna do Houaiss para montar um conversor que irá ajudar o Babylon Builder a construir nosso Houaiss-Babylon. Simples, não?

A primeira parte de toda análise é a busca por padrões com um pouco de bom senso. O Houaiss armazena suas definições em um conjunto de arquivos de nome deahNNN.dhx (provavelmente deah de Dicionario Eletrônico Antônio Houaiss). Os NNN variam de 001 -- o maior arquivo -- até 065, com algumas poucas lacunas, em um total de 53 arquivos originais.

O nosso rústico importador fez o trabalho de desofuscar todos os 53 arquivos usando a mesma lógica encontrada pelo WinDbg: somar o valor 0x0B para cada byte do arquivo. Dessa forma foram gerados 53 arquivos novos no mesmo diretório, porém com a extensão TXT.

Partindo do bom senso, abriremos o arquivo maior, deah001.txt, e abriremos o próprio dicionário Houaiss, em busca de um padrão que faça sentido. Como poderemos ver na figura abaixo, o padrão inicial não é nem um pouco complicado.

![Houaiss Analysis](/img/houaiss-analysis.png)

As duas primeiras observações do formato do arquivo nos dizem que (1) o primeiro caractere de cada linha indica o conteúdo dessa linha, e que (2) a formatação dos caracteres é feita dentro de um par de chaves {}.

Dessa forma, podemos começar a construir nosso interpretador de arquivos do Houaiss em seu formato básico.

    #include <iostream>
    #include <string>
    
    int main()
    {
    	char cmd; // comando da linha atualmente lida
    	string line; // linha atualmente lida
    	int count = 0; // contador de palavras
    
    	while( getline(cin, line) )
    	{
    		cmd = line[0]; // guardamos o comando
    		line.erase(0, 1); // tiramos o comando da linha
    		format(line); // formatação da linha (explicações adiante)
    
    		switch( cmd ) // que comando é esse?
    		{
    		case '*': // verbete
    			++count;
    			cout << '\n' << line << '\n';
    			break;
    
    		case ':': // definição
    			cout << line << "<br>\n";
    			break;
    		}
    	}
    
    	return 0;
    }

Simples e funcional. Com esse código já é possível extrair o básico que precisamos de um dicionário: os vocábulos e suas definições.

Para conseguir mais, é necessário mais trabalho.

A formatação segue o estilo já identificado, de forma que podemos aos poucos montar um interpretador de formatação para HTML, que é o formato reconhecido pelo Babylon Builder. Podemos seguir o seguinte molde, chamado no exemplo de código anterior:

    void format(string& str)
    {
    	string::size_type pos1 = 0;
    	string::size_type pos2 = 0;
    
    	while( (pos1 = str.find('<')) != string::npos )
    		str.replace(pos1, 1, "<");
    
    	while( (pos1 = str.find('>')) != string::npos )
    		str.replace(pos1, 1, ">");
    
    	while( (pos1 = str.find('{')) != string::npos )
    	{
    		if( pos1 && str[pos1 - 1] == '\\' ) // caractere de escape
    			str.replace(pos1 - 1, 2, "{");
    		else
    		{
    			string subStr;
    
    			pos2 = str.find('}', pos1);
    
    			if( pos2 != string::npos )
    				subStr = str.substr(pos1 + 1, pos2 - pos1 - 1);
    			else
    				subStr = str.substr(pos1 + 1);
    
    			istringstream is(subStr);
    
    			string fmt;
    			string word;
    			is >> fmt;
    			getline(is, word);
    			if( word[0] == ' ' )
    			word.erase(0, 1);
    
    			if( fmt.find("\\i") != string::npos )
    				word = "<i>" + word + "</i>";
    
    			if( fmt.find("\\b") != string::npos )
    				word = "<b>" + word + "</b>";
    
    			if( fmt.find("\\f20") != string::npos )
    				word = "<font style=\"text-transform: uppercase;\">" + word + "</font>";
    
    			if( fmt.find("\\super") != string::npos )
    				word = "<font style=\"vertical-align: super;\">" + word + "</font>";
    
    			if( pos2 != string::npos )
    				str.replace(pos1, pos2 - pos1 + 1, word);
    			else
    				str.replace(pos1, pos2, word);
    		}
    	}
    }

Algumas partes ainda estão feias, eu sei. Mas, ei, isso é um código de ráquer, não é mesmo? Além do mais, se isso não é desculpa suficiente, estamos trabalhando em uma versão beta.

A partir dessas duas funções é possível dissecar o primeiro arquivo do dicionário, e assim, construirmos a primeira versão interessante do Houaiss no Babylon.

![Houaiss Babylon Installing](/img/houaiss-babylon-installing.png)

Como é normal a qualquer dicionário do Babylon, podemos instalá-lo simplesmente clicando duas vezes no arquivo (em uma máquina com Babylon previamente instalado).

![Houaiss Babylon](/img/houaiss-babylon.png)

O projeto atual está um tanto capenga, mas já desencripta os arquivos do Houaiss e gera o projeto do Babylon Builder sozinho. Em anexo já está um projeto do Babylon Builder. Basta copiar o arquivo Houaiss.txt para a pasta do projeto e gerar o projeto do Babylon.

Para os interessados em incrementar [a versão atual], sintam-se à vontade.

[estar lembrados]: /conversor-de-houaiss-para-babylon-parte-1
[a versão atual]: https://github.com/Caloni/Houaiss2Babylon
