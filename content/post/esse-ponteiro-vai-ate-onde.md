---
categories: [ "code" ]
date: "2011-01-17"
tags: [ "draft",  ]
title: "Esse ponteiro vai até onde?"
---
Brincando com obtenções e conversões de SIDs, tive uma pequena dificuldade de usar a função ConvertStringSidToSid, de Sddl.h. Seu objetivo é receber uma string-SID no formato usado pela ferramenta PsGetSid e retornar uma sequência de bytes de tamanho arbitrário, que é o SID como o sistema o enxerga. Como ela retorna apenas o ponteiro final, do tipo PSID, o que parece fácil pode se tornar tricky se quisermos copiar o SID binário para algum buffer na pilha, já que não sabemos o número de bytes no buffer de origem. Tudo que sabemos é que, após o uso, devemos desalocar essa memória retornada pela API com outra API: LocalFree.

Ora, mesmo que não venhamos a escrever nessa memória de tamanho obscuro, não é de bom tom ler além da conta. Não há garantias que o que estiver após o SID é seguro. Pode até ser o final de uma página de  memória, por exemplo, e o seu programa capota por causa de um singelo "Memory could not be read". Que coisa sem graça!

[](/images/SXf7NsR.png)

Sempre que me vejo com problemas desse tipo procuro informações primeiro  no próprio MSDN, segundo na cabeça e terceiro no Google. Nesse caso em  específico a cabeça deu um jeito, pois imaginei que houvesse alguma  forma de pegar o tamanho da memória alocada através das funções Local (se a API precisa de LocalFree para desalocar sua memória, é óbvio que  ela usou LocalAlloc para alocá-la, mesmo que não tenhamos o código-fonte  para comprovar).

A partir de LocalHandle posso obter o HANDLE para a memória alocada localmente. Com esse handle a API me dá outra função, LocalSize, de onde posso obter o tamanho da memória previamente alocada através do seu handle. Isso é ótimo, pois em um primeiro momento pensei não haver saída, como nas funções de alocação em C e C++, por exemplo.

