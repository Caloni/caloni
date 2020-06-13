---
categories: [ "code" ]
date: "2020-03-17"
tags: [ "draft",  ]
title: "Projeto Hu Cpp: Not Fast Enough"
---
Continuando minhas aventuras em tentar ser mais rápido que o Hugo, fiz uma versão que gera um html porco com os parágrafos obtidos no parser porco de markdown, rodando em cima dos meus 2740 posts. Este é o código novo:

    void WriteFileToHtml(File& file)
    {
    	string htmlFileName = string(file.fileName);
    
    	htmlFileName.replace(htmlFileName.size() - 2, 2, "html");
    	ofstream ofs(htmlFileName);
    
    	if (ofs)
    	{
    		ofs << "<html><head><title>" << htmlFileName << "</title></head><body>\n";
    		for (size_t i = 0; i < file.paragraphs.size(); ++i)
    		{
    			string paragraph(file.paragraphs[i].begin, file.paragraphs[i].end);
    			ofs << "<p>" << paragraph << "</p>\n\n";
    		}
    		ofs << "</body></html>\n";
    	}
    }

Lembrando o resultado do Hugo no post passado:

    C:\Users\caloni\Projects\caloni>hugo
    Building sites …
                       |  EN
    -------------------+-------
      Pages            | 2765
      Paginator pages  |    0
      Non-page files   |    0
      Static files     | 1748
      Processed images |    0
      Aliases          |    0
      Sitemaps         |    1
      Cleaned          |    0
    
    Total in 16527 ms

Agora executando o meu programinha caseiro (b.bat é uma batch que executa todos os posts usando o comando for do Windows; ptime é uma versão Windows do time do Linux, que mede performance na execução de um programa).

    C:\Users\caloni\Projects\caloni\content\post>ptime b.bat
    
    ptime 1.0 for Win32, Freeware - http://www.pc-tools.net/
    Copyright(C) 2002, Jem Berkes <jberkes@pc-tools.net>
    
    ===  b.bat ===
    
    Execution time: 89.573 s

Noventa segundos para 2700 posts! É uma vergonha! Programadores C++/Boost/Asio, vamos nos matar.
