---
date: "2014-04-24"
title: 2048 motivos para não programar
categories: [ "blog" ]
---
[![2048](http://i.imgur.com/LpkzLQH.jpg)](/images/13989736784_92d49267fe_o.jpg)

Pronto, posso programar em paz. O jogo 2048 é uma lástima para todos os trabalhadores intelectuais que dependem de suas mentes para produzir algo que preste. Ele gerou mais posts no Hacker News do que a moda dos bitcoins (talvez não) e mais projetos no GitHub do que a busca para a cura do câncer (talvez não). (Obviamente que este post vai gerar [mais um commit Python no repositório de artigos](https://github.com/Caloni/Caloni.com.br).)

Não sou fã de jogos, e dos poucos que participei logo parei (exceções honrosas: Portal e Portal 2, esses malditos). Posso dizer o mesmo de 2048, a versão de uma espécie de jogo já conhecido feita pelo italiano [Gabriele Cirulli](http://gabrielecirulli.github.io/2048/) em um fds para ele descobrir se seria capaz de fazê-lo. Ele fez e o jogo e de quebra o índice de produtividade mundial cair.

Houve pelo menos dois projetos de I.A. para resolver o problema que consiste em dobrar números múltiplos de 2 em um quadrado 4 x 4 até que se consiga o quadrado com o valor 2048 (e além). O artigo de [Nicola Pezzotti](http://diaryofatinker.blogspot.it/2014/03/an-artificial-intelligence-for-2048-game.html) explica o mais efetivo deles, de autoria de [Robert Xiao](https://github.com/nneonneo/2048-ai) (eu acho). O programa desenvolvido por Xiao otimiza o tabuleiro do jogo guardando-o em um inteiro de 64 bits, deixando 4 bits para cada casa, mais que o suficiente para que seja armazenada a potência de 2 localizada no quadrado (o limite fica sendo de 2 ** 16, ou 65536). Ao rodar a versão executável console ele imprime cada posição do tabuleiro em um formato fácil de ser lido, como este:

    
    Move #69, current score=584
     1356
     0051
     0012
     0000

Como pode-se perceber, cada número diferente de zero contém a potência de dois que ocupa a casa (1 é igual a 2, 5 é igual a 2 ** 5 = 32 e assim por diante). Para alinhar corretamente o tabuleiro os números estão impressos em hexadecimal, ou seja, os valores válidos vão de 0 a f (15).

Isso já seria o suficiente para desvendar os movimentos da I.A., mas nada como um apelo visual. Que tal um vídeo?

http://youtu.be/GVTCej6zwAk

Feito com a ajuda de um tabuleiro-template e um pouco do poder Python+PIL:

```python
from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw
from itertools import islice

TilePositions = [
        [32, 216], [153, 216], [274, 216], [395, 216],
        [32, 339], [153, 339], [274, 339], [395, 339],
        [32, 461], [153, 461], [274, 461], [395, 461],
        [32, 584], [153, 584], [274, 584], [395, 584]
	]
TileSize = 106

def LoadTemplate():
	img = Image.open('2048.png')
	draw= ImageDraw.Draw(img)
	return img, draw

def DrawBoard(board):
	img, draw = LoadTemplate()
	bigFont = ImageFont.truetype('DejaVuSans-Bold.ttf', 48)
	smallFont = ImageFont.truetype('DejaVuSans-Bold.ttf', 24)
	dbgFont = ImageFont.truetype('DejaVuSans-Bold.ttf', 8)
	for r in range(len(board)):
		for c in range(len(board[r])):
			number = 2 ** board[r][c]
			if number > 1:
				tileX, tileY = TilePositions[r*4 +c][0], TilePositions[r*4 +c][1]
				font = smallFont if number > 64 else bigFont
				text = str(number)
				textW, textH = draw.textsize(text, font=font)
				x, y = tileX + (TileSize - textW) / 2, tileY + (TileSize - textH) /2
				dbgText = str(tileX) + ' + (' + str(TileSize) + ' - ' + str(textW) + ') / 2'
                                draw.text((x, y), text, (0,0,0), font=font)
	return img

def ReadNextBoard(f):
	lines = [lines for lines in islice(f, 4)]
	if (len(lines)) == 4:
		board = [
			[ int(lines[0][0], 16), int(lines[0][1], 16), int(lines[0][2], 16), int(lines[0][3], 16) ],
			[ int(lines[1][0], 16), int(lines[1][1], 16), int(lines[1][2], 16), int(lines[1][3], 16) ],
			[ int(lines[2][0], 16), int(lines[2][1], 16), int(lines[2][2], 16), int(lines[2][3], 16) ],
			[ int(lines[3][0], 16), int(lines[3][1], 16), int(lines[3][2], 16), int(lines[3][3], 16) ]
			]
		return board
	return None

def ProcessGame(filePath):
    f = open(filePath)
    board = ReadNextBoard(f)
    boardNumber = 1
    while board:
            DrawBoard(board).save('2048-' + str(boardNumber) + '.png')
            board = ReadNextBoard(f)
            boardNumber = boardNumber + 1

```

Note que a estratégia basicamente é ordenar as casas em um lado e, assim que acumular valores o suficiente, consolidar tudo na última casa. Nem sempre isso é possível, pois uma virada de jogo pode deixar a casa com o maior valor no meio de um dos lados. Nesse caso, é interessante ver como a I.A. se sai, já que com apenas uma execução ela foi até 8192 e mais um 4096. Dá-lhe, computador!

Observação importante: para que o conversor Python funcione ele exige um arquivo que tenha _apenas_ as posições do tabuleiro dispostas como nas 4 linhas acima. Nada que um grep "^[0-9a-f][0-9a-f][0-9a-f][0-9a-f]$" na saída do jogo não resolva.

Dica: como criar seus próprios vídeos a partir de uma [porrada de PNGs](https://trac.ffmpeg.org/wiki/Create%20a%20video%20slideshow%20from%20images).

Ah, sim, se você pretende analisar a estratégia do jogo passo-a-passo, acho que é melhor você dar uma olhada no [log do jogo](https://github.com/Caloni/Caloni.com.br/tree/master/2048) (ou usá-lo para gerar seus PNGs).

Brinde: versão 2048 do [Vida de Programador](http://goistsg.github.io/2048-vdp/)!
