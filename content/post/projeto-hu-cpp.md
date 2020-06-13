---
categories: [ "code" ]
date: "2020-03-15"
tags: [ "draft",  ]
title: "Projeto Hu Cpp"
---
Utilizo o Hugo como renderizador do meu saite já faz um tempo. Depois que juntei os posts do finado Cine Tênis Verde e do meu blogue técnico a soma dos textos ultrapassou a marca dos dois mil. Atualmente levo cerca de quinze segundos para renderizar todo o saite antes de publicá-lo.

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
    
    C:\Users\caloni\Projects\caloni>

Não é uma marca ruim, considerando que estamos com quase três mil textos, e embora o leiaute do saite seja muito simples, é justamente o que eu desejo para rápido carregamento e busca. Não tenho do que reclamar.

Porém, um programador C nunca fica satisfeito com uma solução Golang.

Sabe esses pensamentos que não saem da cabeça? Estava devaneando há uns dias sobre se não seria interessante renderizar meu saite usando uma solução em C ou C++ e ver qual seria o resultado. Claro que seria uma solução in house, cheia de bugs e completamente limitado. Mas quem liga? Meu único objetivo é a diversão, e não pretendo criar um produto genérico. Hugo já satisfaz até o mais exigente dos programadores (exceto o Elias), pois resolve vários problemas do interminável conflito entre conteúdo e design.

Por falar no dito cujo, me lembrei da nossa disputa no saite Os Programadores. Era uma resolução de exercício envolvendo leitura e parseamento de um arquivo json. Tive o insight de usar algo parecido com o que desenvolvi naquela vez.

    #include <boost/iostreams/device/mapped_file.hpp>
    
    #include <fstream>
    #include <iostream>
    #include <vector>
    
    using namespace std;
    
    
    struct Chunk
    {
    	Chunk(): begin(), end() {}
    	const char* begin;
    	const char* end;
    };
    
    struct Header
    {
    	Chunk title;
    	Chunk date;
    	Chunk tags;
    	Chunk desc;
    	Chunk stars;
    	Chunk imdb;
    };
    
    typedef vector<Chunk> Paragraphs;
    
    struct File
    {
    	Header header;
    	Paragraphs paragraphs;
    };
    
    
    void ParseFile(const char* data, size_t size, File& file)
    {
    	const char* curr = data;
    	struct {
    		const char* key;
    		Chunk* value;
    	} fields[] = {
    		"title", &file.header.title,
    		"date", &file.header.date,
    		"tags", &file.header.tags,
    		"desc", &file.header.desc,
    		"stars", &file.header.stars,
    		"imdb", &file.header.imdb
    	};
    	bool insideHeader = false;
    
    	while (curr < data + size )
    	{
    		if (strncmp(curr, "---", sizeof("---") - 1) == 0)
    		{
    			insideHeader = !insideHeader;
    			curr = strchr(curr, '\n') + 1;
    			continue;
    		}
    
    		if (insideHeader)
    		{
    			for (size_t i = 0; i < sizeof(fields) / sizeof(fields[0]); ++i)
    			{
    				if (strncmp(curr, fields[i].key, strlen(fields[i].key)) == 0)
    				{
    					fields[i].value->begin = strchr(curr, '"') + 1;
    					fields[i].value->end = strchr(fields[i].value->begin + 1, '"');
    					break;
    				}
    			}
    		}
    		else if( curr[0] != '\r' )
    		{
    			Chunk paragraph;
    			paragraph.begin = curr;
    			paragraph.end = strchr(curr, '\r');
    			file.paragraphs.push_back(paragraph);
    		}
    
    		curr = strchr(curr, '\n') + 1;
    	}
    }
    
    int main(int argc, char* argv[])
    {
    	if (argc == 2)
    	{
    		const char* fileName = argv[1];
    
    		boost::iostreams::mapped_file_source fileMap;
    		fileMap.open(fileName);
    		if (fileMap.is_open())
    		{
    			const char* data = fileMap.data();
    			size_t size = fileMap.size();
    
    			File file;
    			ParseFile(data, size, file);
    
    			fileMap.close();
    		}
    	}
    	else cout << "How to use: hu <input-file>\n";
    }
    
Esse código lê um arquivo markdown e divide o header nos campos que eu utilizo e o texto em parágrafos. Esse é o começo mínimo para começar a converter os arquivos em html. Ele usa o mapeamento de arquivo em memória como no desafio 5 acima. Não precisaria, mas já que a diversão é fazer mais rápido que o Hugo, por quê não?

Meu próximo passo é pegar esse parser e converter todos os arquivos para html, da maneira mais porca possível. Quer dizer, quase da maneira mais porca. Não estou usando Pascal.
