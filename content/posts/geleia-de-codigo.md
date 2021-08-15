---
categories:
- blog
date: '2014-04-15'
tags:
title: Geleia de Código
---

Não costumo participar de campeonatos de programação por alguns motivos vagos: é perda de tempo (não ganho nada com isso), sou um péssimo programador (ou pasteleiro), dá preguiça (esse é o mais válido) e por aí vai o mimimi. Dessa forma, sempre passei ileso de eventos como o atual [Google Code Jam](https://code.google.com/codejam/contest/2974486/dashboard), que pretende levar a categoria de código ofuscado para um novo patamar.

No entanto, esse ano apareceram dois motivos que me levaram a gastar cinco minutos de paciência com as historinhas bestas da equipe do Google. Primeiro o Python, que desde 2013 tem renovado em mim a sensação que programar ainda é divertido (e que o pessoal da Microsoft e do padrão C++ tinham tirado de mim há muito tempo com seus compiladores cada vez mais complexos/lentos e as IDEs que demoram o tempo do cafezinho para abrir). Segundo o que move o mundo: a concorrência. Minha digníssima esposa, levada por alguns pontos-extra na faculdade (uma iniciativa até que louvável do professor), resolveu participar da primeira fase (a classificação desta fase também dava pontos).

[![jam2014](http://i.imgur.com/zXzJlL5.jpg)](/images/13878076723_dc8556a364_o.jpg)

O fato é que depois desses cinco minutos eu simplesmente não consegui parar até o minuto final das 23 horas (horário de Brasília) de domingo, quando o tempo-limite esgotou. O aspecto mais divertido do Code Jam é que há liberdade total para a ferramenta que você pretende usar: linguagens de programação, Excel, uma calculadora ou apenas seu cérebro. Você recebe uma "missão" e um arquivo de entrada e precisa cuspir um arquivo de saída de acordo com a missão. Apenas isso. O resto fica por conta da criatividade dos codadores e gambiarreiros de plantão.

Todos os exercícios levam em consideração um arquivo de entrada que possui em sua primeira linha o número de testes que serão feitos e em seguida um número determinado de linhas e parâmetros, geralmente divididos por espaço. O primeiro problema, por exemplo, apenas considerava a suposição de cartas em pequeno truque de mágica e recebia como entrada a disposição dessas cartas junto com a escolha da fileira que o participante dizia onde estava a carta escolhida.

    
    2
    1 2 3 4
    5 6 7 8
    9 10 11 12
    13 14 15 16
    3
    1 2 5 4
    3 11 6 15
    9 10 7 12
    13 14 8 16

```
import sys

f = open(sys.argv[1])
total = int(f.readline())

for case in range(0, total):
	guess1 = int(f.readline())
	row1 = None
	for i in range(1, 5):
		row = f.readline().split()
		if i == guess1:
			row1 = row
	guess2 = int(f.readline())
	row2 = None
	for i in range(1, 5):
		row = f.readline().split()
		if i == guess2:
			row2 = row
	cards = list(set(row1) & set(row2))
	if len(cards) == 1:
		print 'Case #' + str(case+1) + ': ' + cards[0]
	elif len(cards) > 1:
		print 'Case #' + str(case+1) + ': Bad magician!'
	else:
		print 'Case #' + str(case+1) + ': Volunteer cheated!'

```

O segundo exercício já envolvia um jogo bem divertido em que o jogador ficava clicando em cookies como se não houvese amanhã. Esse deu um pouco mais de trabalho, mas foi mais divertido que o primeiro.

```
import sys

def CookieClicker(farmCost, farmIncrement, cookieTarget):
	cookiePerSecond = 2.0
	bestTime = cookieTarget / cookiePerSecond # melhor tempo soh fazendo cookies
	cookieFarmTime = cookieTarget / (cookiePerSecond + farmIncrement) # melhor tempo ja com fazenda criada
	farmTime = farmCost / cookiePerSecond + cookieFarmTime # quanto vai custar fazer a fazenda e depois fazer cookies com a fazenda
	while farmTime < bestTime: # enquanto fazer a fazenda custar menos tempo que soh fazer cookies...
		bestTime = farmTime # por enquanto melhor tempo
		cookiePerSecond = cookiePerSecond + farmIncrement # novo tempo para fazer cookies (mais uma fazenda ja criada)
		farmTime = farmTime - cookieFarmTime # tiramos o tempo de soh fazer cookies para fazer mais uma fazenda
		cookieFarmTime = cookieTarget / (cookiePerSecond + farmIncrement) # novo tempo com mais uma fazenda criada
		farmTime = farmTime + farmCost / cookiePerSecond + cookieFarmTime # agora com o novo tempo de fazer outra fazenda e soh cookies
	return bestTime

f = open(sys.argv[1])
total = int(f.readline())

for case in range(1, total + 1):
    args = [float(i) for i in f.readline().split()]
    ret = CookieClicker(args[0], args[1], args[2])
    print 'Case #' + str(case) + ': ' + '{0:.7f}'.format(ret)

```

Já o terceiro... o terceiro passa. Vamos para o quarto, um dos mais instigantes, pois envolve duas regras distintas de um jogo e a otimização das melhores estratégias para ambos. Isso consumiu bem mais tempo que os outros dois iniciais, pois lembro de ter me isolado por uma hora para conseguir colocar tudo na cabeça.

```
import sys

def BestBlock(block, blocks):
	bestBlock = 0
	for i in range(len(blocks) - 1, -1, -1):
		if blocks[i] < block: break
		bestBlock = blocks[i]
	if not bestBlock:
		bestBlock = blocks[0]
	return bestBlock

def War(naomi, ken):
	naomi = sorted(naomi)
	ken = sorted(ken)
	naomiCount = 0
	while len(naomi):
		naomiBlock = naomi[-1]
		kenBlock = BestBlock(naomiBlock, ken)
		if naomiBlock > kenBlock:
			naomiCount = naomiCount + 1
		#print str(naomiBlock) + ' vs ' + str(kenBlock) + ': ' + str(naomiCount)
		naomi.remove(naomiBlock)
		ken.remove(kenBlock)
	return naomiCount

def WarCheat(naomi, ken):
	naomi = sorted(naomi)
	ken = sorted(ken)
	naomiCount = 0
	while len(naomi):
		naomiTold = 0
		naomiBlock = naomi[-1]
		bestKen = ken[-1]
		if naomiBlock > bestKen:
			naomiTold = bestKen + 0.00000001
		else:
			naomiTold = bestKen - 0.00000001
		kenBlock = BestBlock(naomiTold, ken)
		naomiBlock = BestBlock(kenBlock, naomi)
		if naomiBlock > kenBlock:
			naomiCount = naomiCount + 1
		#print str(naomiTold) + '(' + str(naomiBlock) + ') vs ' + str(kenBlock) + ': ' + str(naomiCount)
		naomi.remove(naomiBlock)
		ken.remove(kenBlock)
	return naomiCount

f = open(sys.argv[1])
total = int(f.readline())

for case in range(1, total + 1):
        f.readline()
        naomi = [float(i) for i in f.readline().split()]
        ken = [float(i) for i in f.readline().split()]
        war = War(naomi, ken)
        warCheat = WarCheat(naomi, ken)
        print 'Case #' + str(case) + ': ' + str(warCheat)+ ' ' + str(war)

```

Já o terceiro foi um fracasso total. Tentei de todas as maneiras resolver o impasse de descobrir qual disposição de um jogo de campo minado poderia ser resolvido em apenas um clique (parece o jogo oposto do viciado clicador de cookies), mas falhei miseravelmente. E desconfio o porquê. Primeiro entendo que meu perfeccionismo me impediu de realizar uma checagem padrão para exceções já conhecidas (quando há apenas uma linha ou coluna, quando há apenas um espaço sem minas, etc). Eu pensei: se o Google fez esse problema, ele deve ter bolado alguma solução genérica que independa de ifs. Bom, não que eu saiba. Depois de terminado o tempo dei uma olhada em algumas soluções dos competidores e não achei nenhuma solução que usasse algum algoritmo maluco e genérico (não achei nenhum indiano, contudo).

Eis a solução porca e mal-resolvida (alguns pontos do códido foram feitos depois de ver o código de outrem):

```
import sys

def FieldToString(field):
        ret = '\n'
	for r in field:
		for c in r:
			ret = ret + str(c)
		ret = ret + '\n'
	return ret

def CountMines(field, r, c):
        ret = 0
        row = len(field)
        col = len(field[0])
        if r < row-1 and field[r+1][c] == '*': ret = ret + 1
        if c < col-1 and field[r][c+1] == '*': ret = ret + 1
        if r > 0 and field[r-1][c] == '*': ret = ret + 1
        if c > 0 and field[r][c-1] == '*': ret = ret + 1
        if r < row-1 and c < col-1 and field[r+1][c+1] == '*': ret = ret + 1
        if r > 0 and col > 0 and field[r-1][c-1] == '*': ret = ret + 1
        if r < row-1 and c > 0 and field[r+1][c-1] == '*': ret = ret + 1
        if r > 0 and c < col-1 and field[r-1][c+1] == '*': ret = ret + 1
        return ret

def ExpandClick(field, r, c):
        if field[r][c] != '0': return

        def Expand(field, r, c):
                if field[r][c] == '.':
                        field[r][c] = str(CountMines(field, r, c))
                        ExpandClick(field, r, c)

        row = len(field)
        col = len(field[0])
        if r < row-1 and field[r+1][c] != '*':
                Expand(field, r+1, c)
        if c < col-1 and field[r][c+1] != '*':
                Expand(field, r, c+1)
        if r > 0 and field[r-1][c] != '*':
                Expand(field, r-1, c)
        if c > 0 and field[r][c-1] != '*':
                Expand(field, r, c-1)
        if r < row-1 and c < col-1 and field[r+1][c+1] != '*':
                Expand(field, r+1, c+1)
        if r > 0 and col > 0 and field[r-1][c-1] != '*':
                Expand(field, r-1, c-1)
        if r < row-1 and c > 0 and field[r+1][c-1] != '*':
                Expand(field, r+1, c-1)
        if r > 0 and c < col-1 and field[r-1][c+1] != '*':
                Expand(field, r-1, c+1)

def FieldClicker(field):
	row = len(field)
	col = len(field[0])
        for r in range(row):
                for c in range(col):
                        if field[r][c] == 'C':
                                field[r][c] = str(CountMines(field, r, c))
                                ExpandClick(field, r, c)
                                break
        return field

def FieldValidate(field):
        ret = True
	row = len(field)
	col = len(field[0])
        for r in range(row):
                for c in range(col):
                        if field[r][c] == '.':
                                ret = False
                                break
        return ret

def FieldRender(row, col, mines):
	field = []
        for i in range(row):
                field.append(['.'] * col)
        if row == 2:
                nextRow = 0
                nextCol = 0
                while mines:
                        field[nextRow][nextCol] = '*'
                        nextRow = nextRow + 1
                        if nextRow == row:
                                nextRow = 0
                                nextCol = nextCol + 1
                        mines = mines - 1
                field[0][col-1] = 'C'
        elif col == 2:
                nextRow = 0
                nextCol = 0
                while mines:
                        field[nextRow][nextCol] = '*'
                        nextCol = nextCol + 1
                        if nextCol == col:
                                nextRow = nextRow + 1
                                nextCol = 0
                        mines = mines - 1
                field[row-1][0] = 'C'
	elif row * col - mines < 3:
                nextRow = row - 1
                nextCol = 0
                while mines:
                        field[nextRow][nextCol] = '*'
                        nextCol = nextCol + 1
                        if nextCol == col:
                                nextRow = nextRow - 1
                                nextCol = 0
                        mines = mines - 1
                field[0][col-1] = 'C'
        else:
                for r in range(len(field)):
                        for c in range(len(field[0])):
                                field[r][c] = '*'
                if row * col - mines >= 9 and row >= 3 and col >= 3:
                        empties = row * col - mines
                        nextRow = 0
                        nextCol = 0
                        while empties:
                                
	return field

def Mine(row, col, mines):
        if row * col - mines == 2 and row > 1 and col > 1:
		return 'Impossible!'
	if row * col - mines == 3:
		return 'Impossible!'
	elif row * col - mines == 5:
		return 'Impossible!'
	elif row * col - mines == 7:
		return 'Impossible!'
	else:
		return FieldToString(FieldRender(row, col, mines))

f = open(sys.argv[1])
total = int(f.readline())

for case in range(1, total + 1):
        field = [int(i) for i in f.readline().split()]
        print 'Case #' + str(case) + ': ' + Mine(field[0], field[1], field[2])

#############################################################################3

def FieldRenderWrong(row, col, mines):
	field = []
	for i in range(row):
		field.append(['.'] * col)

        def GetNextRow(field, clickRow, clickCol):
                row = len(field)
                col = len(field[0])
                nextRow = 0
                nextCol = 0
                rowDist = 0
                colDist = 0
                for r in range(row):
                        for c in range(col):
                                if field[r][c] == '.':
                                        rDist = abs(r - clickRow)
                                        cDist = abs(c - clickCol)
                                        totDist = rDist + cDist
                                        currTotDist = rowDist + colDist
                                        if totDist > currTotDist:
                                                nextRow = r
                                                rowDist = rDist
                                                nextCol = c
                                                colDist = cDist
                                        else:
                                                rowCount = 0
                                                for r2 in range(row):
                                                        if field[r2][c] == '*':
                                                                rowCount = rowCount + 1
                                                colCount = 0
                                                for c2 in range(col):
                                                        if field[r][c2] == '*':
                                                                colCount = colCount + 1
                                                lastRow = rowCount == row - 1
                                                lastCol = colCount == col - 1
                                                if lastRow or lastCol:
                                                        nextRow = r
                                                        rowDist = rDist
                                                        nextCol = c
                                                        colDist = cDist
                return nextRow, nextCol

        clickRow = 0
        clickCol = col-1
	field[clickRow][clickCol] = 'C'
        nextRow, nextCol = GetNextRow(field, clickRow, clickCol)
	while mines:
		field[nextRow][nextCol] = '*'
		nextRow, nextCol = GetNextRow(field, clickRow, clickCol)
		mines = mines - 1
	return field

```

Não, eu não usei o Google para descobrir a lógica por trás do problema. Vai que os caras ficam monitorando quem fica fazendo pesquisas. E, não, tampouco usei o Bing. Não sou masoquista a esse ponto.

_PS: Bom, estou na próxima fase. Veremos o que o futuro nos espera. Esse programador foi fisgado pelo campeonato de pastéis._
