import chess.pgn
import io
import sys
import urllib.request

def getpgn(path):
    if path.find("http") == 0:
        response = urllib.request.urlopen(path)
        data = response.read()
        text = data.decode('utf-8')
        return io.StringIO(text)
    else:
        return open(path)

def printpgn(pgn):
    game = chess.pgn.read_game(pgn)
    while game:
        board = game.board()
        print(game, '\n')
        print(board, '\n')
        for move in game.mainline_moves():
            board.push(move)
            print(move, '\n')
            print(board, '\n')
        game = chess.pgn.read_game(pgn)

for arg in sys.argv[1:]:
    pgn = getpgn(arg)
    printpgn(pgn)
