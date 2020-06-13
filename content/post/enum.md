---
categories: [ "code" ]
date: "2010-05-31"
tags: [ "draft",  ]
title: "Enum"
---
Padrão C (ISO/IEC 9899:1990)
    
    6.5.2.2 enum-specifier
     enum

    
    Padrão C++ (ISO/IEC 14882:1998)
    
    type-specifier
     enum-specifier
    
    enum-specifier
     enum

Uma enumeração faz duas coisas: define um novo tipo, parecido com um inteiro, e cria uma lista de constantes com nomes significativos. A definição técnica do tipo de um enum é mais complicada, mas basicamente ele é um novo int.

Como funciona: definimos uma lista com cada elemento tendo um valor inteiro, geralmente único. Todos os nomes usados na lista passam a fazer parte do espaço de nomes atual e funcionam como constantes com o seu valor definido no início.

    enum FileType // criamos o novo tipo inteiro FileType
    {
       Binary = 1, // Binary é uma constante com valor igual a 1
       Text = 2, // Text é uma constante com seu sizeof igual a sizeof(FileType)
       Mixed = 3 // Todas as constantes da enumeração são do mesmo tipo
    };
     
    

Obs.: Os elementos que não possuem valor definido são definidos automaticamente como o valor do elemento anterior acrescidos de um. Se for o primeiro elemento, seu valor padrão é zero.

    enum Numbers
    {
       zero,  // igual a zero
       one,   // igual a um
       two,   // igual a dois
       three  // igual a tres
    };
    
    enum Hexa
    {
       JulioCesar = 1,
       Lucio = 3,
       Juan,                // Juan = 3 + 1 = 4
       Gilberto Silva = 6,
       Felipe Melo          // 6 + 1 = 7
    }; 
    

Detalhe bizarro: você sabia que, apesar da vírgula ser usada para separar valores de enumeração, ela pode também terminar uma listagem? Por algum motivo exdrúxulo (se alguém quiser explicar), um valor de enumeração foi definido de tal forma que sempre poderá existir uma vírgula terminando ele:

    enum VirgulaSafada { 
       um = 1, 
       dois, 
       tres, // o que essa vírgula no final tá fazendo aqui?
    }; 
    

Geralmente usamos enumerações para definir valores únicos (tag) em um argumento de função, ou, mais moderno, como substituto daqueles antigos defines em C para mapas de bits. Nesse último caso não usamos o tipo da enumeração, pois ele pode conter apenas um valor único definido, e não um conjunto deles:

    enum ModoDeServir
    {
       assado,
       cozido,
       frito,
       cru
    };
    
    void Cook(Prato p, ModoDeServir ms);
    
    main()
    {
       Cook(frango, cozido);
    }
    
    enum FileOpenMode
    {
       fomRead   = 0x0001,
       fomWrite  = 0x0002,
       fomOver   = 0x0004,
       fomDel    = 0x0008,
    };
    
    void OpenFile(DWORD fileOpenMode);
    
    main()
    {
       OpenFile(fomRead | fomWrite);
    } 
    

Note que usamos uma enumeração nesse último caso para termos um nome significativo para uma flag, além desse nome fazer de fato parte dos nomes do programa, e não um define que, para o compilador, não existe.

Como os tipos da enumeração passam a pertencer ao namespace atual, eles podem se misturar facilmente com todos os nomes daquele namespace. Dessa forma, é útil e bem organizado definir um prefixo para os nomes, que pode ser formado pelas iniciais do nome da enumeração, como no exemplo acima (fom = FileOpenMode).

O surgimento do enum veio como evolução de uma prática já consagrada pelo uso na linguagem C, que eram as listas de valores constantes criados através de defines com algum prefixo em comum (FILESHARE, SWSHOW, etc). Portanto, sempre que se encontrar em uma situação para criar esse tipo de lista, a enumeração é o caminho atualmente ideal.

    // A listagem abaixo pode virar um enum...
    #define FOM_READ   0x0001
    #define FOM_WRITE  0x0002
    #define FOM_OVER   0x0004
    #define FOM_DEL    0x0008
    
    // ... como este aqui!
    enum FileOpenMode
    {
       FOM_READ   = 0x0001,
       FOM_WRITE  = 0x0002,
       FOM_OVER   = 0x0004,
       FOM_DEL    = 0x0008,
    };
    
    // esse pedaço de código abaixo...
    int main()
    {
       OpenFile(path, FOM_WRITE);
    }
    
    // ... vira isso após ser pré-processado...
    int main()
    {
       OpenFile(path, 0x0002);
    }
    
    // ... mas isso se fossem usados enums...
    int main()
    {
       OpenFile(path, FOM_WRITE); // FOM_WRITE faz parte da linguagem
    }
     
    

Perguntado por um leitor sobre qual a diferença prática do último exemplo, onde temos praticamente o mesmo resultado entre usar defines e enumerações, imaginei que a mesma dúvida pode ter surgido para várias pessoas, porque é uma boa dúvida. Dá a entender que o autor deste artigo está se atentando a preciosismos da linguagem (e está mesmo!), mas à vezes as aparências enganam.

Para ilustrar melhor fiz um mais elaborado. Aqui, estamos lendo pedaços de dados que tiveram que ser alinhados com alguma "gordura".

    // alinhamento obrigatório pelo leiaute dos dados
    #define CHUNKSZ_BASE 0x5000
    
    #define CHUNKSZ_TINY   0x1000 + CHUNKSZ_BASE
    #define CHUNKSZ_SMALL  0x2000 + CHUNKSZ_BASE
    #define CHUNKSZ_MEDIUM 0x4000 + CHUNKSZ_BASE
    #define CHUNKSZ_HUGE   0x8000 + CHUNKSZ_BASE
    
    // alinhamento obrigatório pelo leiaute dos dados
    static const int chunkSizeBase = 0x5000;
    
    enum ChunkSize
    {
       chunkszTiny   = 0x1000 + chunkSizeBase,
       chunkszSmall  = 0x2000 + chunkSizeBase,
       chunkszMedium = 0x4000 + chunkSizeBase,
       chunkszHuge   = 0x8000 + chunkSizeBase,
    };
    
    // Fonte original
    int main()
    {
    	// lendo quadro pedaços de dados (tamanho médio)
       ReadChunkFromFile(file, CHUNKSZ_MEDIUM * 4);
    
    	// lendo quadro pedaços de dados (tamanho médio)
       ReadChunkFromFile(file, chunkszMedium * 4);
    }
    
    // Pós-processado
    int main()
    {
    	// lendo sei lá o que (perde alinhamento)
       ReadChunkFromFile(file, 0x4000 + CHUNKSZ_BASE * 4);
    
    	// lendo quadro pedaços de dados (tamanho médio)
       ReadChunkFromFile(file, chunkszMedium * 4);
    }
    
     
    

Aviso para os programadores mais calejados, eu omiti propositalmente os parênteses obrigatórios para qualquer define que tenha cálculos matemáticos, para ilustrar que muitas vezes o que vemos antes não é o que aparece depois.
